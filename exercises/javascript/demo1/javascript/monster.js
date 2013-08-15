
var war = require('war');
var globals = require('global');

var gamejs = require('gamejs');

/*
 * Sprite classes
 */

var Monster = exports.Monster = function() {

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

    this.position = war.findNewLocation(war.getSpawnPoint(this.family));

    var rect = [this.position[0]*globals.TILE_SIZE, this.position[1]*globals.TILE_SIZE];
    this.rect = new gamejs.Rect(rect, [globals.TILE_SIZE, globals.TILE_SIZE]);

    war.setTileState(this.position, globals.TileState.OCCUPIED, this.id);

    // destination is used while traveling
    this.destination = [];


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

	globals.NEED_INIT = true;
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

	/* 
	 * findPathTo gives us an array of waypoints
	 * or [] if no path could be found.
	 */
	var destination = war.findPathTo(this.family, this.position, rect);

	if (destination.length > 0) {
	    /*
	     * If we are returning from melee attack, we don't set tile occupation here
	     */
	    if (this.getState() !== globals.MonsterState.MOVING_AFTER_ATTACK) {
		war.setTileState(this.position, globals.TileState.NOT_OCCUPIED);
	    }
	    this.changeState(globals.MonsterState.MOVING);

	    /* we have to make sure monster doesn't move past it's range */
	    if (this.moveRange < destination.length)
		destination = destination.slice(0, this.moveRange);

	    /* a_star gives us destination even if it's occupied/blocked, so we 
	     * cut off the path until we find a free spot (or run out of points)
	     */
	    var free = false;

	    while (!free && (destination.length > 0)) {
		var x = destination[destination.length-1].x;
		var y = destination[destination.length-1].y;

		var isEmpty = war.isTileEmpty([x, y]);
		var isOccupied = war.isTileOccupied([x, y]);

		/* If tile is empty and non-occupied, there's no problem moving there */
		if ((isEmpty) && (!isOccupied)) {
		    free = true;
		}
		/* Tile is also considered free if there's an enemy; that means we attack it */
		else if ((isOccupied) && (this.family !== war.getMonsterAt([x, y]).family)) {
		    free = true;
		}
		/* Otherwise we cut off last destination point as unfit */
		else {
		    destination = destination.slice(0, destination.length-1);
		}
	    }

	    /* At this point destination may be empty */
	    this.destination = destination;
	}

	/*
	 * if we have no path, we simply sleep this turn
	 * (note that war.doAI handles ranged etc. attacking,
	 * no need to do that here) 
	 */
	if ((this.controller == globals.Controller.AI) && (destination.length == 0)) {
	    this.skipTurn();
	}
    }

    /*
     * attack() is only used for ranged attacks
     */
    this.attackRanged = function(enemy) {
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


var Orc = exports.Orc = function() {
    this.image_name = "images/orc";
    this.name = "Orc ";
    this.family = "Orcs";

    this.personality = globals.MonsterPersonality.BERSERK;
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

    Monster.call(this);
}

var ToughOrc = exports.ToughOrc = function() {
    this.image_name = "images/tough_orc";
    this.name = "Tough Orc ";
    this.family = "Orcs";

    this.personality = globals.MonsterPersonality.BERSERK;
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

    Monster.call(this);
}

var Octopus = exports.Octopus = function() {
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

    Monster.call(this);
}

var Evileye = exports.Evileye = function() {
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

    Monster.call(this);
}

// inherit (actually: set prototype)
gamejs.utils.objects.extend(Monster, gamejs.sprite.Sprite);
gamejs.utils.objects.extend(ToughOrc, Monster);
gamejs.utils.objects.extend(Evileye, Monster);
gamejs.utils.objects.extend(Orc, Monster);
gamejs.utils.objects.extend(Octopus, Monster);

Monster.prototype.update = function(msDuration) {

    /*
     * If monster is currently moving someplace (may be melee attack)
     */
    if (this.stateIs(globals.MonsterState.MOVING)) {

	/*
	 * Monster must have a destination
	 */
	if (this.destination.length == 0) {
	    console.warn(this.name + " tried to move, but has no destination!");
	    this.endTurn();
	    return;
	}

	/* Find our current position in pixels */
	var pixel_position = [this.rect.left, this.rect.top];
	/* Find where we are going */
	var newPosition = [this.destination[0].x, this.destination[0].y];
	/* In actual pixels */
	var goal = [this.destination[0].x*globals.TILE_SIZE, this.destination[0].y*globals.TILE_SIZE];
	/* Movement delta (relative) in pixels */
	var delta = [0, 0];
	/* Length of wanted movement in pixels */
	var diff = [Math.abs(goal[0]-pixel_position[0]), Math.abs(goal[1]-pixel_position[1])];

	/* If we have arrived at current destination point, but have still journey to go */
	if ((war.samePlace(pixel_position, goal)) && (this.destination.length != 0)) {
	    /* shift current location off the destination array */
	    this.destination.shift();
	}

	/* If we have arrived at current destination point AND it's our final stop */
	if ((war.samePlace(pixel_position, goal)) && (this.destination.length == 0)) {
	    /* set monsters position */
	    this.position = newPosition;

	    /* if we are on hostile tile, we launch attack */
	    if ((war.isTileOccupied(this.position)) && (war.getMonsterAt(this.position).family != this.family)) {
		/* we can use getMonsterAt since attacking monster is not yet 'positioned' here */
		this.enemy = war.getMonsterAt(this.position);
		/* stop moving, start attacking */
		this.changeState(globals.MonsterState.ATTACKING);
		/* apparently, we're going melee */
		globals.attackIcon.setMelee();
	    }
	    /* if there's no reason to get exited, we simply occupy this position and end turn */
	    else {
		war.setTileState(this.position, globals.TileState.OCCUPIED, this.id);
		this.endTurn();
	    }

	    return;
	}

	// monster moves speed*30 pixels per second (duration/1000)
	var speed = 1+Math.floor((this.speed*20) * (msDuration/1000));

	delta[0] = Math.min(speed, diff[0]);
	delta[1] = Math.min(speed, diff[1]);

	delta[0] = (pixel_position[0] > goal[0])? (-delta[0]) : (delta[0]);
	delta[1] = (pixel_position[1] > goal[1])? (-delta[1]) : (delta[1]);

	// moveIp, move in place
	this.rect.moveIp(delta[0], delta[1]);
    }
    else if (this.stateIs(globals.MonsterState.ATTACKING)) {

	if (!globals.attackOn) {

	    /* show icon on top of enemy */
	    globals.attackIcon.rect.left = this.enemy.position[0]*globals.TILE_SIZE;
	    globals.attackIcon.rect.top = this.enemy.position[1]*globals.TILE_SIZE;

	    globals.attackOn = true;
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

	    globals.stillBattling = war.areThereStillEnemies();

	    globals.attackOn = false;
	    globals.attackIcon.reset();
	} // else (globals.attackOn && globals.attackIcon.time > 1000)

	activeEnemy = war.getMonsterAt(globals.cursor_pos);
	war.drawStats(null, activeEnemy);
    } // if this.getState() === globals.MonsterState.ATTACKING
};

