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


/*
 * Initial members
 */


var cursor_pos = [0,0], cursor_state = globals.CursorState.ALLOWED;
var NEED_INIT = false;

/* attackOn helps in the 'attackIcon animation' showing */
var attackOn = false;
var stillBattling = true;


console.log(war.name());


/*
 * Sprite classes
 */

// TODO: take tile-coordinate instead of rect
var Monster = function(rect) {

    /*
     * Monster public members
     */

    // war.Init handles id giving
    this.id = -1;

    // call superconstructor (Monster is derived from Sprite)
    Monster.superConstructor.apply(this, arguments);

    // speed varies between (1, 10)
    // naturalSpeedTypes go from VERY_SLOW = 0 to VERY_QUICK = 4
    this.speed = 1 + Math.round(Math.random()) + Math.round(this.naturalSpeedType + (this.naturalSpeedType * Math.random()));

    // moveRange is based on speed and it's between [1,5]
    this.moveRange = Math.max(1, Math.floor(this.speed/2));

    /* VERY_WEAK : 0, WEAK : 1, NORMAL : 2, TOUGH : 3, VERY_TOUGH : 4, GODLIKE : 5 */
    this.hp = Math.round((this.endurance*10)+(this.endurance*10*Math.random()));
    this.maxhp = this.hp;

    // passive image
    this.image = gamejs.image.load(this.image_name + ".png");

    // rect shows the position and dimensions of monster
    this.rect = new gamejs.Rect(rect, [globals.TILE_SIZE, globals.TILE_SIZE]);

    // destination is used while traveling
    this.destination = [];

    // monster.position shows the tile monster is currently on
    this.position = war.getTile(rect);


    /*
     * Private members
     */


    // state of monster is private, so it won't get changed by accident
    var state = globals.MonsterState.INACTIVE;


    /*
     *
     * Monster public functions
     *
     */

    this.kill = function() {
	console.log("Killing",this.name);

	NEED_INIT = true;
	globals.Monsters.remove(this);
    }

    /* getDamage returns inflicted pain */
    this.getDamage = function(style) { 
	var damage = 0;
	for (var i=0; i<this.damage[style]; i++) {
	    damage += Math.ceil(this.damageModifier*Math.random());
	}

	if (this.hp/this.maxhp > 0.9)
	    return Math.round(damage);
	else {
	    /* If monster has under 90% health left, its inflicted damage goes down */
	    var dispersion = damage*0.1;
	    var middlePoint = damage*(this.hp/this.maxhp);
	    damage = (middlePoint - dispersion) + (2*Math.random()*dispersion);
	    return Math.round(Math.max(0, damage));
	}
    }

    /* getDamageString returns "XdY + Z" - type string */
    this.getDamageString = function(style) { 
	var string = this.damage[style] + "d" + this.damageModifier;
	if ((this.damageBonus != 0) && (style === this.weapon))
	    string += " + " + this.damageBonus;

	return string;
    }


    /*
     * moveTo gets parameter coordinates as tiles [0..globals.TILE_AMOUNT] 
     * and sets monster to motion (actual movement is done in gMonster.update()
     */
    this.moveTo = function(rect) {

	var destination = war.moveTowardsGoal(this.family, this.position, rect, this.moveRange);

	if (destination.length > 0) {
	    if (this.getState() !== globals.MonsterState.MOVING_AFTER_ATTACK) {
		war.setTileState(this.position, globals.TileState.NOT_OCCUPIED);
	    }
	    this.changeState(globals.MonsterState.MOVING);

	    /* we have to make sure monster doesn't move past it's range */
	    if (this.moveRange < destination.length)
		destination = destination.splice(1, this.moveRange);

	    /* a_star gives us destination even if it's occupied/blocked, so we 
	     * cut off the path until we find a free spot (or run out of points)
	     */
	    if (destination.length > 0) {
		var free = false;

		while (!free && (destination.length > 0)) {
		    var x = destination[destination.length-1].x;
		    var y = destination[destination.length-1].y;

		    /* tile is considered free if there's an enemy; that means we attack it */
		    if ((war.isTileEmpty([x, y])) &&
			    (!war.isTileOccupied([x, y]) || (this.family != war.getMonsterAt([x, y]).family))) {
			free = true;
		    }
		    else
			destination = destination.slice(0, destination.length-1);

		}
	    }

	    this.destination = destination;
	}
	else if (this.controller == globals.Controller.AI)
	    this.skipTurn();

	/* note that units turn continues until we get a proper destination 
	 * TODO: or turn is manually skipped */
    }

    /*
     * attack() is only used for ranged attacks
     */
    this.attackRanged = function(enemy) {
	console.log("attackRanged:",enemy.name,this.name);
	this.enemy = enemy;
	this.changeState(globals.MonsterState.ATTACKING);
	globals.attackIcon.setRanged();
    }

    /*
     * skipTurn means that monster does nothing, and next unit gets activated
     */
    this.skipTurn = function() {
	this.endTurn();
	console.log("Monster",this.name,"skipped its turn");
    }

    /*
     * endTurn makes monster inactive, and tells war that it next units turn
     */
    this.endTurn = function() {
	this.changeState(globals.MonsterState.INACTIVE);
	this.enemy = null;
	war.nextUnit();
    }

    /* activate sets monster as 'active' one on battlefield */
    this.activate = function() {
	console.log(this.name, "just became active");

	/* if this is computer controlled, it launches its ai sequence */
	if (this.controller === globals.Controller.AI) {
	    war.doAI(this);
	}
    }

    /* deactivate passivates the monster */
    this.deactivate = function() {
	console.log(this.name, "was de-activated");
	this.image = gamejs.image.load(this.image_name + ".png");
    }

    /* this.state needs a getter since it's private */
    this.getState = function() {
	return this.state;
    }

    this.stateIs = function(state) {
	return (this.state === state);
    }

    this.isActive = function() {
	return (this.state == globals.MonsterState.ACTIVE);
    }

    this.isHumanControlled = function() {
	return (this.controller === globals.Controller.HUMAN);
    }

    /* this.changeState calls appropriate methods on changing the state of monster */
    this.changeState = function(newState) { 

	if (this.state === newState)
	    return;

	this.state = newState;

	switch (this.state) {
	    case globals.MonsterState.INACTIVE:
		this.deactivate();
		break;
	    case globals.MonsterState.ACTIVE:
		this.activate();
		break;
	    default:
	}
    }

    console.log("Created", this.name, "(speed:", this.speed, "move:", this.moveRange, "hp:",this.hp,")");

    return this;
};


/*
 * Derivative monster classes
 */


var Orc = function(rect) {
    this.image_name = "images/orc";
    this.name = "Orc ";
    this.family = "Orcs";

    this.personality = war.randomFromList([globals.MonsterPersonality.BERSERK,globals.MonsterPersonality.INDIVIDUAL]);
    this.naturalSpeedType = globals.MonsterSpeed.QUICK;
    this.endurance = globals.MonsterEndurance.TOUGH;
    this.weapon = globals.WeaponStyle.MELEE;

    this.damage = {};
    this.damage[globals.WeaponStyle.MELEE] = 7;
    this.damage[globals.WeaponStyle.RANGED] = 0;
    this.damage[globals.WeaponStyle.MAGIC] = 0;
    this.damageModifier = 3;
    this.damageBonus = 3;

    this.controller = globals.Controller.AI;

    Monster.call(this, rect);
}

var ToughOrc = function(rect) {
    this.image_name = "images/tough_orc";
    this.name = "Tough Orc ";
    this.family = "Orcs";

    this.personality = war.randomFromList([globals.MonsterPersonality.BERSERK,globals.MonsterPersonality.INDIVIDUAL]);
    this.naturalSpeedType = globals.MonsterSpeed.VERY_QUICK;
    this.endurance = globals.MonsterEndurance.VERY_TOUGH;
    this.weapon = globals.WeaponStyle.MELEE;

    this.damage = {};
    this.damage[globals.WeaponStyle.MELEE] = 7;
    this.damage[globals.WeaponStyle.RANGED] = 0;
    this.damage[globals.WeaponStyle.MAGIC] = 0;
    this.damageModifier = 6;
    this.damageBonus = 10;

    this.controller = globals.Controller.AI;

    Monster.call(this, rect);
}

var Octopus = function(rect) {
    this.image_name = "images/octopus";
    this.name = "Octo-Monster ";
    this.family = "Monsters";

    this.personality = war.randomFromList([globals.MonsterPersonality.CAREFUL,globals.MonsterPersonality.INDIVIDUAL]);
    this.naturalSpeedType = globals.MonsterSpeed.QUICK;
    this.endurance = globals.MonsterEndurance.WEAK;
    this.weapon = globals.WeaponStyle.MAGIC;

    this.damage = {};
    this.damage[globals.WeaponStyle.MELEE] = 4;
    this.damage[globals.WeaponStyle.RANGED] = 1;
    this.damage[globals.WeaponStyle.MAGIC] = 5;
    this.damageModifier = 4;
    this.damageBonus = 0;

    this.controller = globals.Controller.AI;

    Monster.call(this, rect);
}

var Evileye = function(rect) {
    this.image_name = "images/evileye";
    this.name = "Evil eye";
    this.family = "Boss";

    this.personality = globals.MonsterPersonality.IMMOBILE;
    this.naturalSpeedType = globals.MonsterSpeed.VERY_SLOW;
    this.endurance = globals.MonsterEndurance.GODLIKE;
    this.weapon = globals.WeaponStyle.RANGED;

    this.damage = {};
    this.damage[globals.WeaponStyle.MELEE] = 1;
    this.damage[globals.WeaponStyle.RANGED] = 8;
    this.damage[globals.WeaponStyle.MAGIC] = 0;
    this.damageModifier = 3;
    this.damageBonus = 0;

    this.controller = globals.Controller.AI;

    Monster.call(this, rect);
}

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

    this.origSize = this.originalImage.getSize();

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

// inherit (actually: set prototype)
gamejs.utils.objects.extend(Monster, gamejs.sprite.Sprite);
gamejs.utils.objects.extend(ToughOrc, Monster);
gamejs.utils.objects.extend(Evileye, Monster);
gamejs.utils.objects.extend(Orc, Monster);
gamejs.utils.objects.extend(Octopus, Monster);

gamejs.utils.objects.extend(war.Ground, gamejs.sprite.Sprite);
gamejs.utils.objects.extend(AttackIcon, gamejs.sprite.Sprite);

AttackIcon.prototype.update = function(msDuration) {
    if (attackOn) {
	var delta = [Math.floor(this.scale*this.origSize[0]), Math.floor(this.scale*this.origSize[1])];
	this.scale += Math.floor(100*msDuration*this.scaleSpeed)/100;
	this.image = gamejs.transform.scale(this.originalImage, [Math.floor(this.scale*this.origSize[0]), Math.floor(this.scale*this.origSize[1])]);
	var size = this.image.getSize();
	delta[0] = Math.max(0, size[0] - delta[0]);
	delta[1] = Math.max(0, size[1] - delta[1]);

	this.rect = new gamejs.Rect(this.rect.left-(delta[0]/2), this.rect.top-(delta[1]/2), size[0], size[1]);
    }
}

Monster.prototype.update = function(msDuration) {

    if (this.stateIs(globals.MonsterState.MOVING)) {
	/* get direction to destination from current place */
	var position = [this.rect.left, this.rect.top];
	var newPosition = [this.destination[0].x, this.destination[0].y];
	var goal = [this.destination[0].x*globals.TILE_SIZE, this.destination[0].y*globals.TILE_SIZE];
	var delta = [0, 0];
	var diff = [Math.abs(goal[0]-position[0]), Math.abs(goal[1]-position[1])];

	if ((war.samePlace(position, goal)) && (this.destination.length != 0)) {
	    this.destination.shift();
	}

	if ((war.samePlace(position, goal)) && (this.destination.length == 0)) {
	    this.position = newPosition;

	    /* if we are on hostile tile, we launch attack */
	    if ((war.isTileOccupied(this.position)) && (war.getMonsterAt(this.position).family != this.family)) {
		this.enemy = war.getMonsterAt(this.position);
		this.changeState(globals.MonsterState.ATTACKING);
		globals.attackIcon.setMelee();
	    }
	    /* else, we end turn */
	    else {
		war.setTileState(this.position, globals.TileState.OCCUPIED, this.id);
		this.endTurn();
		console.log("Monster",this.name,"finished its journey.");
	    }
	    return;
	}

	// monster moves speed*30 pixels per second (duration/1000)
	var speed = 1+Math.floor((this.speed*20) * (msDuration/1000));

	delta[0] = Math.min(speed, diff[0]);
	delta[1] = Math.min(speed, diff[1]);

	delta[0] = (position[0] > goal[0])? (-delta[0]) : (delta[0]);
	delta[1] = (position[1] > goal[1])? (-delta[1]) : (delta[1]);

	// moveIp, move in place
	this.rect.moveIp(delta[0], delta[1]);
    }
    else if (this.stateIs(globals.MonsterState.ATTACKING)) {

	if (!attackOn) {

	    /* show icon on top of enemy */
	    globals.attackIcon.rect.left = this.enemy.position[0]*globals.TILE_SIZE;
	    globals.attackIcon.rect.top = this.enemy.position[1]*globals.TILE_SIZE;

	    attackOn = true;
	}
	else if (globals.attackIcon.time < globals.attackIcon.duration) {
	    globals.attackIcon.time += msDuration;
	}
	else {

	    if (this.enemy == null) {
		console.error(this.name, "is attacking, but has no enemy!");
		this.endTurn();
	    }


	    war.battle(this.id, this.enemy.id);

	    /* Note: It's not possible that both monsters die in the battle */

	    /* If attacker died, it's over for him */
	    if (this.hp <= 0) {
		console.log("Monster",this.enemy.name,"killed its enemy!");
		war.battleStatus.add(this.name + " was killed!");
		war.nextUnit();
		this.kill();
	    }
	    /* If attacker survived ... */
	    else {
		/* enemy is dead, so we can stay at its position (if melee-fight) */
		if (this.enemy.hp <= 0) {
		    war.battleStatus.add(this.enemy.name + " was killed!");
		    this.enemy.kill();

		    if (war.samePlace(this.position, this.enemy.position)) {
			war.setTileState(this.position, globals.TileState.OCCUPIED, this.id);
		    }
		    this.endTurn();
		    console.log("Monster",this.name,"killed its enemy!");
		}
		/* Enemy is also alive, so we need to find a new position for us (if attacked by melee) */
		else {
		    if (war.samePlace(this.position, this.enemy.position)) {
			var newLocation = war.findNewLocation(this.position);
			console.log("New location:",newLocation);
			this.changeState(globals.MonsterState.MOVING_AFTER_ATTACK);
			this.moveTo(newLocation);
		    }
		    else
			this.endTurn();
		}
	    }

	    stillBattling = war.areThereStillEnemies();

	    attackOn = false;
	    globals.attackIcon.reset();
	} // else (attackOn && globals.attackIcon.time > 1000)

	activeEnemy = war.getMonsterAt(cursor_pos);
	war.drawStats(null, activeEnemy);
    } // if this.getState() === globals.MonsterState.ATTACKING
};


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


    /* Monsters */

    globals.Monsters = new gamejs.sprite.Group();

    for (var i=0; i < (10); i++)
    {
	if (Math.random() < 0.5)
	    globals.Monsters.add(new Orc([i*globals.TILE_SIZE, 0]));
	else
	    globals.Monsters.add(new ToughOrc([i*globals.TILE_SIZE, 0]));
    }

    for (var i=0; i < (10); i++)
        globals.Monsters.add(new Octopus([i*globals.TILE_SIZE, 9*globals.TILE_SIZE]));

    //globals.Monsters.add(new Evileye([4*globals.TILE_SIZE, 4*globals.TILE_SIZE]));

    /* Ground */

    globals.GroundTiles = new gamejs.sprite.Group();

    for (var y=0; y<globals.TILE_AMOUNT; y++) {
	for (var x=0; x<globals.TILE_AMOUNT; x++) {
	    // there's a 25% chance that tile is lava */
	    var blocked = (Math.random() > 0.25)? globals.TileState.EMPTY : globals.TileState.BLOCKED;
	    globals.GroundTiles.add(new war.Ground([x*globals.TILE_SIZE, y*globals.TILE_SIZE], blocked));
	}
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
		    cursor_pos = war.getTile(event.pos);
		    cursor_state = war.updateCursorState(cursor_pos, activeMonster);

		    var was = activeEnemy;

		    /* activeEnemy is null if there is no monster at cursor position */
		    activeEnemy = war.getMonsterAt(cursor_pos);

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
			var dist = war.getDistance(click_pos, activeMonster.position);

			var tileState = war.isTileEmpty(click_pos);
			console.log("Click:", click_pos, "empty:", tileState, "dist:", dist);
			console.log (war.isTileOccupiedByEnemy(click_pos, activeMonster.family));
			console.log(activeMonster.weapon === globals.WeaponStyle.RANGED);

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
	    if (!stillBattling) {
		war.battleStatus.add(" *********************   It's all over!   ********************* ");
		director.replaceScene(endStatisticsScene);
	    }
	    else {

		if (NEED_INIT) {
		    /* initializing is necessary once some poor monster dies */
		    console.log("Re-initing things");
		    war.init(war.getCurrentUnitIndex());
		}

		/* We check here if turn has changed and set new monster as active if necessary */
		if ((war.getCurrentUnit() != activeMonsterIndex) || (NEED_INIT)) {
		    activeMonsterIndex = war.getCurrentUnit();
		    activeMonster = globals.Monsters.sprites()[activeMonsterIndex];
		    activeMonster.changeState(globals.MonsterState.ACTIVE);
		    /* also update cursor state for new monster */
		    cursor_state = war.updateCursorState(cursor_pos, activeMonster);

		    /* activeEnemy is null if there is no monster at cursor position */
		    activeEnemy = war.getMonsterAt(cursor_pos);
		    war.drawStats(activeMonster, activeEnemy);
		}

		NEED_INIT = false;

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
		war.drawCursor(mainSurface, cursor_pos, cursor_state);

		if (activeMonster)
		    war.drawActiveMonsterTile(mainSurface, [activeMonster.rect.left, activeMonster.rect.top]);

		// on top of everything else, monsters
		globals.Monsters.draw(mainSurface);

		/* Finally, some stats */


		if (attackOn) {
		    globals.attackIcon.update(msDuration);
		    globals.attackIcon.draw(mainSurface);
		}

	    } // stillBattling
	}
    } // warScene

    var EndStatisticsScene = function(director) {

	this.handleEvent = function(event) {
	    /* Mouse clicking */
	    if (event.type === gamejs.event.MOUSE_UP) {
		var rect = new gamejs.Rect(0,0,globals.GAME_AREA_WIDTH, globals.GAME_AREA_HEIGHT);

		/* if we are actually on game area */
		if (rect.collidePoint(event.pos)) {
		    stillBattling = true;
		    director.replaceScene(warScene);
		}
	    }
	}

	this.init = function() {
	    var box = document.getElementById("gamepaused");
	    box.style.display = "block";

	    if (!stillBattling) {
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
