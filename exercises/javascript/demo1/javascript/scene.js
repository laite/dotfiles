var war = require('war');
var globals = require('global');
var monster = require('monster');
var scenario = require('scenarios');

var gamejs = require('gamejs');


/*
 *
 *
 * Director
 *
 *
 */


exports.Director = function() {
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

var WarScene = exports.WarScene = function(director, mainSurface) {
    this.init = function() {
	/* If there's no ongoing battle, we init everything from the start */
	if (!globals.stillBattling) {
	    console.log("Re-initializing battlefield!");

	    /* If no scenario is selected, we fall */
	    if (globals.selectedScenario == -1) {
		console.error("No scenario selected!");
		director.replaceScene(globals.menuScene);
		// XXX: necessary?
		return;
	    }

	    // scenario loader takes care of initializing ground and monsters
	    scenario.loadScenario(globals.selectedScenario);

	    /*
	     * Engine initializations
	     */

	    war.init();

	    globals.stillBattling = true;
	    console.log(war.name());
	}
    }

    this.handleEvent = function(event)
    {
	/* Mouse movement */
	if (event.type === gamejs.event.MOUSE_MOTION) {
	    /* If we are on canvas, draw rectangle on current tile */
	    if (mainSurface.rect.collidePoint(event.pos)) {
		globals.cursor_pos = war.getTile(event.pos);
		globals.cursor_state = war.updateCursorState(globals.cursor_pos, globals.activeMonster);

		var was = globals.activeEnemy;

		/* globals.activeEnemy is null if there is no monster at cursor position */
		globals.activeEnemy = war.getMonsterAt(globals.cursor_pos);

		/* update sidebar status only when necessary */
		if (globals.activeEnemy !== was)
		    war.drawStats(null, globals.activeEnemy);
	    }
	}

	/* Keyboard shortcuts */
	if (event.type === gamejs.event.KEY_UP) {

	    /* [s]kip turn */
	    if (event.key === gamejs.event.K_s) {
		if (globals.activeMonster.isActive() && globals.activeMonster.isHumanControlled())
		    globals.activeMonster.skipTurn();
	    }
	    /* [p]ause game */
	    if (event.key === gamejs.event.K_p) {
		director.replaceScene(globals.endStatisticsScene);
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
		/* skip event if globals.activeMonster is not human-controlled, or is not active */
		if ((!globals.activeMonster.isActive()) || (!globals.activeMonster.isHumanControlled()))
		    return;

		if (mainSurface.rect.collidePoint(event.pos)) {

		    // get clicked tile, its state and distance from globals.activeMonster
		    var click_pos = war.getTile(event.pos);
		    var dist = war.getDistance(click_pos, globals.activeMonster.position, globals.activeMonster.family);

		    var tileState = war.isTileEmpty(click_pos);
		    var occupied = "false";
		    if (war.isTileOccupied(click_pos)) {
			occupied = war.getMonsterAt(click_pos).name + war.getMonsterAt(click_pos).id;
		    }
		    console.log("Click:", click_pos, "empty:", tileState, "occupied:", occupied, "dist:", dist);

		    if ((war.isTileOccupiedByEnemy(click_pos, globals.activeMonster.family)) && (globals.activeMonster.weapon === globals.WeaponStyle.RANGED)) {
			globals.activeMonster.attackRanged(war.getMonsterAt(click_pos));
		    }
		    else
			globals.activeMonster.moveTo(click_pos);
		}
	    }
	}
    }

    this.update = function(msDuration) {
	if (!globals.stillBattling) {
	    war.battleStatus.add(" *********************   It's all over!   ********************* ");
	    director.replaceScene(globals.endStatisticsScene);
	}
	else {

	    if (globals.NEED_INIT) {
		/* initializing is necessary once some poor monster dies */
		console.log("Re-initing things");
		war.init(war.getCurrentUnitIndex());
	    }

	    /* We check here if turn has changed and set new monster as active if necessary */
	    if ((war.getCurrentUnit() != globals.activeMonsterIndex) || (globals.NEED_INIT)) {
		globals.activeMonsterIndex = war.getCurrentUnit();
		globals.activeMonster = globals.Monsters.sprites()[globals.activeMonsterIndex];
		globals.activeMonster.changeState(globals.MonsterState.ACTIVE);
		/* also update cursor state for new monster */
		globals.cursor_state = war.updateCursorState(globals.cursor_pos, globals.activeMonster);

		/* globals.activeEnemy is null if there is no monster at cursor position */
		globals.activeEnemy = war.getMonsterAt(globals.cursor_pos);
		war.drawStats(globals.activeMonster, globals.activeEnemy);
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

	    if (globals.activeMonster)
		war.drawActiveMonsterTile(mainSurface, [globals.activeMonster.rect.left, globals.activeMonster.rect.top]);

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

var EndStatisticsScene = exports.EndStatisticsScene = function(director) {

    this.handleEvent = function(event) {

	/* Mouse clicking */
	if (event.type === gamejs.event.MOUSE_UP) {
	    var rect = new gamejs.Rect(0,0,globals.GAME_AREA_WIDTH, globals.GAME_AREA_HEIGHT);

	    /* if we are actually on game area */
	    if (rect.collidePoint(event.pos)) {

	    }
	}

	if (event.type === gamejs.event.KEY_UP) {
	    /* [p]ause game */
	    if (event.key === gamejs.event.K_p) {
		director.replaceScene(globals.warScene);
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

var MenuScene = exports.MenuScene = function(director) {

    this.init = function() {
	var box = document.getElementById("mainmenu");
	box.style.display = "block";
    }

    this.exit = function() {
	var box = document.getElementById("mainmenu");
	box.style.display = "none";
    }

    this.handleEvent = function(event) {
	if (event.type === gamejs.event.MOUSE_UP) {
	    var selected = -1;
	    var click = event.pos;
	    
	    // we must compensate for html page margin here (sigh)
	    click[0] += 30; click[1] += 30;

	    for (var i=1; i<=3; i++) {
		var rect = document.getElementById("scn"+i).getBoundingClientRect();
		if (rect.left <= click[0] && rect.right >= click[0] && rect.top <= click[1] && rect.bottom >= click[1])
		    selected = i;
	    }

	    if (selected != -1) {
		globals.selectedScenario = selected;
		director.replaceScene(globals.warScene);
	    }
	}

	if (event.type === gamejs.event.KEY_UP) {
	    /* XXX: debug only */
	    if (event.key === gamejs.event.K_p) {
		director.replaceScene(globals.warScene);
	    }

	}
    }

    this.update = function(msDuration) {

    }
}

