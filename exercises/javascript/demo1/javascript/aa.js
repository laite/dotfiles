
var globals = require('globals');
var war = require('war');
var gamejs = require('gamejs');

/*
 * Sprite classes
 */

// TODO: take tile-coordinate instead of rect
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


exports.Orc = function() {
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

exports.ToughOrc = function() {
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

exports.Octopus = function() {
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

exports.Evileye = function() {
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

gamejs.utils.objects.extend(monster.Monster, gamejs.sprite.Sprite);
gamejs.utils.objects.extend(monster.ToughOrc, monster.Monster);
gamejs.utils.objects.extend(monster.Evileye, monster.Monster);
gamejs.utils.objects.extend(monster.Orc, monster.Monster);
gamejs.utils.objects.extend(monster.Octopus, monster.Monster);

