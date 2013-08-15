/*
 *
 * DEMO 1
 *
 * Game area
 *
 */

/*
 * Requires
 */

var globals = require('global');

var gamejs = require('gamejs');
var draw = require('gamejs/draw');
var $v = require('gamejs/utils/vectors');

var war = require('war');
var monster = require('monster');




console.log(war.name());


var AttackIcon = function(rect) {
    AttackIcon.superConstructor.apply(this, arguments);

    this.originalImage = gamejs.image.load("images/attack.png");
    this.image = this.originalImage;

    this.rect = new gamejs.Rect(rect, [globals.TILE_SIZE, globals.TILE_SIZE]);
    console.log("New attackicon: ", this.rect);

    this.time = 0;
    this.scale = 1;
    this.scaleSpeed = (1/globals.ATTACK_ICON_DURATION);
    this.duration = globals.ATTACK_ICON_DURATION;

    this.origSize = [globals.TILE_SIZE, globals.TILE_SIZE];

    this.reset = function() {
	this.time = 0;
	this.scale = 1;
	this.image = this.originalImage;
    }

    this.setRanged = function() {
	this.originalImage = gamejs.image.load("images/attack_ranged.png");
	this.image = this.originalImage;
	this.scaleSpeed = (1/globals.RANGED_ATTACK_ICON_DURATION);
	this.duration = globals.RANGED_ATTACK_ICON_DURATION;
    }

    this.setMelee = function() {
	this.originalImage = gamejs.image.load("images/attack.png");
	this.image = this.originalImage;
	this.scaleSpeed = (1/globals.ATTACK_ICON_DURATION);
	this.duration = globals.ATTACK_ICON_DURATION;
    }

    this.setMagic = function() {
	this.originalImage = gamejs.image.load("images/attack_magic.png");
	this.image = this.originalImage;
	this.scaleSpeed = (1/globals.MAGIC_ATTACK_ICON_DURATION);
	this.duration = globals.MAGIC_ATTACK_ICON_DURATION;
    }

    return this;
};

gamejs.utils.objects.extend(war.Ground, gamejs.sprite.Sprite);
gamejs.utils.objects.extend(AttackIcon, gamejs.sprite.Sprite);

AttackIcon.prototype.update = function(msDuration) {
    if (globals.attackOn) {
	var delta = [Math.floor(this.scale*this.origSize[0]), Math.floor(this.scale*this.origSize[1])];
	this.scale += Math.floor(100*msDuration*this.scaleSpeed)/100;
	this.image = gamejs.transform.scale(this.originalImage, [Math.floor(this.scale*this.origSize[0]), Math.floor(this.scale*this.origSize[1])]);
	var size = this.image.getSize();
	delta[0] = Math.max(0, size[0] - delta[0]);
	delta[1] = Math.max(0, size[1] - delta[1]);

	this.rect = new gamejs.Rect(this.rect.left-(delta[0]/2), this.rect.top-(delta[1]/2), size[0], size[1]);
    }
}


/*
 *
 * Main function 
 *
 */


function main() {


    /*
     * Initial screen setup
     */


    gamejs.display.setMode([globals.CANVAS_WIDTH, globals.CANVAS_HEIGHT]);
    gamejs.display.setCaption("Example Monsters");

    var mainSurface = gamejs.display.getSurface();
    var font = new gamejs.font.Font('13px Monospace');
    var caption = new gamejs.font.Font('20px Monospace');

    var activeMonster = null, activeEnemy = null;
    var activeMonsterIndex = -1;

    /*
     * Sprites
     */

    /* Ground */

    globals.GroundTiles = new gamejs.sprite.Group();

    for (var y=0; y<globals.TILE_AMOUNT; y++) {
	for (var x=0; x<globals.TILE_AMOUNT; x++) {
	    // there's a 25% chance that tile is lava */
	    var blocked = (Math.random() > 0.25)? globals.TileState.EMPTY : globals.TileState.BLOCKED;
	    globals.GroundTiles.add(new war.Ground([x*globals.TILE_SIZE, y*globals.TILE_SIZE], blocked));
	}
    }

    /* Monsters */

    globals.Monsters = new gamejs.sprite.Group();

    for (var i=0; i < (16); i++)
    {
	var monsterType = Math.random()*20;
	if (monsterType < 15)
	    globals.Monsters.add(new monster.Orc());
	else if (monsterType < 10)
	    globals.Monsters.add(new monster.ToughOrc());
	else if (monsterType < 19)
	    globals.Monsters.add(new monster.Octopus());
	else
	    globals.Monsters.add(new monster.Evileye());
    }

    globals.attackIcon = new AttackIcon([0,0]);


    /*
     * Engine initializations
     */


    war.init();
    war.battleStatus.add(war.name());



    /*
     *
     *
     *
     *
     *
     * Director
     *
     *
     *
     *
     */


    var Director = function() {
	var onAir = false;
	var activeScene = null;

	this.update = function(msDuration) {
	    if (!onAir) return;

	    if (activeScene.update) {
		activeScene.update(msDuration);
	    }
	}

	this.draw = function(display) {
	    if (activeScene.draw) {
		activeScene.draw(display);
	    }
	};

	this.handleEvent = function(event) {
	    if (activeScene.handleEvent) {
		activeScene.handleEvent(event);
	    }
	}


	this.start = function(scene) {
	    onAir = true;
	    this.replaceScene(scene);
	    return;
	};

	this.replaceScene = function(scene) {

	    if ((activeScene != null) && (activeScene.exit)) {
		activeScene.exit();
	    }

	    activeScene = scene;

	    if (activeScene.init) {
		activeScene.init();
	    }
	};

	this.getScene = function() {
	    return activeScene;
	};
	return this;
    }

    /*
     *
     *
     * SCENE: WAR
     *
     *
     */

    var WarScene = function(director) {
	this.handleEvent = function(event)
	{
	    /* Mouse movement */
	    if (event.type === gamejs.event.MOUSE_MOTION) {
		/* If we are on canvas, draw rectangle on current tile */
		if (mainSurface.rect.collidePoint(event.pos)) {
		    globals.cursor_pos = war.getTile(event.pos);
		    globals.cursor_state = war.updateCursorState(globals.cursor_pos, activeMonster);

		    var was = activeEnemy;

		    /* activeEnemy is null if there is no monster at cursor position */
		    activeEnemy = war.getMonsterAt(globals.cursor_pos);

		    /* update sidebar status only when necessary */
		    if (activeEnemy !== was)
			war.drawStats(null, activeEnemy);
		}
	    }

	    /* Keyboard shortcuts */
	    if (event.type === gamejs.event.KEY_UP) {

		/* [s]kip turn */
		if (event.key === gamejs.event.K_s) {
		    if (activeMonster.isActive() && activeMonster.isHumanControlled())
			activeMonster.skipTurn();
		}
		/* [p]ause game */
		if (event.key === gamejs.event.K_p) {
		    director.replaceScene(endStatisticsScene);
		}
		/* [h]umanize (debug) */
		if (event.key === gamejs.event.K_h) {
		    globals.Monsters.forEach(function(monster) { 
			monster.controller = (monster.controller === globals.Controller.HUMAN)? globals.Controller.AI : globals.Controller.HUMAN;
		    })
		}
	    }

	    /* Mouse clicking */
	    if (event.type === gamejs.event.MOUSE_UP) {

		var rect = new gamejs.Rect(0,0,globals.GAME_AREA_WIDTH, globals.GAME_AREA_HEIGHT);

		/* if we are actually on game area */
		if (rect.collidePoint(event.pos)) {
		    /* skip event if activeMonster is not human-controlled, or is not active */
		    if ((!activeMonster.isActive()) || (!activeMonster.isHumanControlled()))
			return;

		    if (mainSurface.rect.collidePoint(event.pos)) {

			// get clicked tile, its state and distance from activeMonster
			var click_pos = war.getTile(event.pos);
			var dist = war.getDistance(click_pos, activeMonster.position, activeMonster.family);

			var tileState = war.isTileEmpty(click_pos);
			console.log("Click:", click_pos, "empty:", tileState, "dist:", dist);

			if ((war.isTileOccupiedByEnemy(click_pos, activeMonster.family)) && (activeMonster.weapon === globals.WeaponStyle.RANGED)) {
			    activeMonster.attackRanged(war.getMonsterAt(click_pos));
			}
			else
			    activeMonster.moveTo(click_pos);
		    }
		}
	    }
	}

	this.update = function(msDuration) {
	    if (!globals.stillBattling) {
		war.battleStatus.add(" *********************   It's all over!   ********************* ");
		director.replaceScene(endStatisticsScene);
	    }
	    else {

		if (globals.NEED_INIT) {
		    /* initializing is necessary once some poor monster dies */
		    console.log("Re-initing things");
		    war.init(war.getCurrentUnitIndex());
		}

		/* We check here if turn has changed and set new monster as active if necessary */
		if ((war.getCurrentUnit() != activeMonsterIndex) || (globals.NEED_INIT)) {
		    activeMonsterIndex = war.getCurrentUnit();
		    activeMonster = globals.Monsters.sprites()[activeMonsterIndex];
		    activeMonster.changeState(globals.MonsterState.ACTIVE);
		    /* also update cursor state for new monster */
		    globals.cursor_state = war.updateCursorState(globals.cursor_pos, activeMonster);

		    /* activeEnemy is null if there is no monster at cursor position */
		    activeEnemy = war.getMonsterAt(globals.cursor_pos);
		    war.drawStats(activeMonster, activeEnemy);
		}

		globals.NEED_INIT = false;

		/*
		 * Drawing stuff
		 */

		// update the monsters
		globals.Monsters.update(msDuration);

		// clear
		mainSurface.fill("#efefef");

		// draw ground first
		globals.GroundTiles.draw(mainSurface);

		// then "cursor"
		war.drawCursor(mainSurface, globals.cursor_pos, globals.cursor_state);

		if (activeMonster)
		    war.drawActiveMonsterTile(mainSurface, [activeMonster.rect.left, activeMonster.rect.top]);

		// on top of everything else, monsters
		globals.Monsters.draw(mainSurface);

		/* Finally, some stats */


		if (globals.attackOn) {
		    globals.attackIcon.update(msDuration);
		    globals.attackIcon.draw(mainSurface);
		}

	    } // globals.stillBattling
	}
    } // warScene

    var EndStatisticsScene = function(director) {

	this.handleEvent = function(event) {
	    /* Mouse clicking */
	    if (event.type === gamejs.event.MOUSE_UP) {
		var rect = new gamejs.Rect(0,0,globals.GAME_AREA_WIDTH, globals.GAME_AREA_HEIGHT);

		/* if we are actually on game area */
		if (rect.collidePoint(event.pos)) {
		    globals.stillBattling = true;
		    director.replaceScene(warScene);
		}
	    }
	}

	this.init = function() {
	    var box = document.getElementById("gamepaused");
	    box.style.display = "block";

	    if (!globals.stillBattling) {
		box.innerHTML = "<h1>Game over</h1>";
		box.innerHTML += ""
	    }
	    else {
		box.innerHTML = "<h1>Game paused</h1>";
		box.innerHTML += ""
	    }
	}

	this.exit = function() {
	    var box = document.getElementById("gamepaused");
	    box.style.display = "none";
	    box.innerHTML = "";
	}
    }
    var MenuScene = function(director) {

    }

    /*
     * Create the director and the scenes 
     */

    var director = new Director();
    var warScene = new WarScene(director);
    var endStatisticsScene = new EndStatisticsScene(director);
    var menuScene = new MenuScene(director);

    /*
     * Apply gamejs events to director
     */

    gamejs.onEvent(function(event) {
	director.handleEvent(event);
    });


    /* msDuration = time since last tick() call */
    gamejs.onTick(function(msDuration) {
	director.update(msDuration);
    });


    /*
     * Start the game
     */

    director.start(warScene);
}


/*
 * Preloads
 */


gamejs.preload(['images/tough_orc.png']);
gamejs.preload(['images/evileye.png']);
gamejs.preload(['images/orc.png']);
gamejs.preload(['images/octopus.png']);
gamejs.preload(['images/tile.png']);
gamejs.preload(['images/tile2.png']);
gamejs.preload(['images/attack.png']);
gamejs.preload(['images/attack_ranged.png']);
gamejs.preload(['images/attack_magic.png']);

/* Go! */
gamejs.ready(main);
