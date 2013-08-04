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

console.log(war.name());


/*
 * Sprite classes
 */

// TODO: take tile-coordinate instead of rect
var Monster = function(rect, id) {

	/*
	 * Monster public members
	 */

	// each monster has a unique id
	this.id = id;

	// call superconstructor (Monster is derived from Sprite)
	Monster.superConstructor.apply(this, arguments);

	// speed varies between (1, 10)
	// naturalSpeedTypes go from VERY_SLOW = 0 to VERY_QUICK = 4
	this.speed = 1 + Math.round(Math.random()) + Math.round(this.naturalSpeedType + (this.naturalSpeedType * Math.random()));

	// moveRange is based on speed and it's between [1,5]
	this.moveRange = Math.max(1, Math.floor(this.speed/2));

	// passive image
	this.image = gamejs.image.load(this.image_name + ".png");

	// rect shows the position and dimensions of monster
	this.rect = new gamejs.Rect(rect, [globals.TILE_SIZE, globals.TILE_SIZE]);

	// destination is used while traveling
	this.destination = [0, 0];

	// monster.position shows the tile monster is currently on
	this.position = war.getTile(rect);


	/*
	 * Private members
	 */


	// state of monster is private, so it won't get changed by accident
	var state = globals.MonsterState.INACTIVE;


	/*
	 * Monster public functions
	 */


	/*
	 * moveTo gets parameter coordinates as tiles [0..globals.TILE_AMOUNT] 
	 * and sets monster to motion (actual movement is done in gMonster.update()
	 */
	this.moveTo = function(rect) {
		if (this.state !== globals.MonsterState.ACTIVE)
			return;

		war.setTileState(this.position, globals.TileState.EMPTY);
		war.setTileState(rect, globals.TileState.OCCUPIED, this.id);
		this.destination = rect;
		this.changeState(globals.MonsterState.MOVING);

		console.log(this.name,this.id,"is on its way!","Distance: ",war.getDistance(rect,this.position));
	}

	/* activate sets monster as 'active' one on battlefield */
	this.activate = function() {
		console.log(this.name, this.id, "just became active");
		this.image = gamejs.image.load(this.image_name + "_active.png");

		/* if this is computer controlled, it launches its ai sequence */
		if (this.controller === globals.Controller.AI) {
			war.doAI(this);
		}
	}

	/* deactivate passivates the monster */
	this.deactivate = function() {
		console.log(this.name, this.id, "was de-activated");
		this.image = gamejs.image.load(this.image_name + ".png");
	}

	/* this.state needs a getter since it's private */
	this.getState = function() {
		return this.state;
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

	console.log("Created", this.name, this.id, "(speed:", this.speed, " move:", this.moveRange, ")");

	return this;
};


/*
 * Derivative monster classes
 */


var Orc = function(rect, id) {
	this.image_name = "images/orc";
	this.name = "Orc";
	this.family = "Heroes";

	this.personality = war.randomPersonality([globals.MonsterPersonality.BERSERK,globals.MonsterPersonality.INDIVIDUAL]);
	this.naturalSpeedType = globals.MonsterSpeed.QUICK;
	this.weapon = globals.WeaponStyle.MELEE;

	this.controller = globals.Controller.HUMAN;

	Monster.call(this, rect, id);
}

var Octopus = function(rect, id) {
	this.image_name = "images/octopus";
	this.name = "Octo-Monster";
	this.family = "Monsters";

	this.personality = war.randomPersonality([globals.MonsterPersonality.CAREFUL,globals.MonsterPersonality.INDIVIDUAL]);
	this.naturalSpeedType = globals.MonsterSpeed.SLOW;
	this.weapon = globals.WeaponStyle.MAGIC;

	this.controller = globals.Controller.AI;

	Monster.call(this, rect, id);
}

var Ground = function(rect) {
	Ground.superConstructor.apply(this, arguments);
	this.image = gamejs.image.load("images/tile.png");

	this.rect = new gamejs.Rect(rect, [globals.TILE_SIZE, globals.TILE_SIZE]);

	return this;
};

// inherit (actually: set prototype)
gamejs.utils.objects.extend(Monster, gamejs.sprite.Sprite);
gamejs.utils.objects.extend(Orc, Monster);
gamejs.utils.objects.extend(Octopus, Monster);

gamejs.utils.objects.extend(Ground, gamejs.sprite.Sprite);


Monster.prototype.update = function(msDuration) {

	if (this.getState() === globals.MonsterState.MOVING) {

		/* get direction to destination from current place */
		var position = [this.rect.left, this.rect.top];
		var goal = [this.destination[0]*globals.TILE_SIZE, this.destination[1]*globals.TILE_SIZE];
		var delta = [0, 0];
		var diff = [Math.abs(goal[0]-position[0]), Math.abs(goal[1]-position[1])];

		if (position[0] == goal[0] && position[1] == goal[1])
		{
			this.changeState(globals.MonsterState.INACTIVE);
			this.position = this.destination;
			war.nextUnit();
			console.log("Monster",this.name,"finished its journey.");
			return;
		}

		// monster moves speed*30 pixels per second
		var speed = 1+Math.floor((this.speed*20) * (msDuration/1000));

		delta[0] = Math.min(speed, diff[0]);
		delta[1] = Math.min(speed, diff[1]);

		delta[0] = (position[0] > goal[0])? (-delta[0]) : (delta[0]);
		delta[1] = (position[1] > goal[1])? (-delta[1]) : (delta[1]);

		// moveIp, move in place
		this.rect.moveIp(delta[0], delta[1]);
	}
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

	var activeMonster = null;
	var activeMonsterIndex = -1;

	/*
	 * Sprites
	 */


	/* Monsters */

	var gMonsters = new gamejs.sprite.Group();

	for (var i=0; i < (globals.AMOUNT_OF_MONSTERS); i++)
		gMonsters.add(new Orc([i*globals.TILE_SIZE, 0], i));
	for (var i=0; i < (globals.AMOUNT_OF_MONSTERS); i++)
		gMonsters.add(new Octopus([i*globals.TILE_SIZE, 9*globals.TILE_SIZE], i+globals.AMOUNT_OF_MONSTERS));

	/* Ground */

	var gGroundTiles = new gamejs.sprite.Group();

	for (var i=0; i<(globals.CANVAS_WIDTH/globals.TILE_SIZE); i++) {
		for (var j=0; j<(globals.CANVAS_WIDTH/globals.TILE_SIZE); j++) {
			gGroundTiles.add(new Ground([i*globals.TILE_SIZE, j*globals.TILE_SIZE]));
		}
	}


	/*
	 * Engine initializations
	 */


	war.initUnits(gMonsters);
	war.initTiles(gMonsters);


	/*
	 * Event handling
	 */


	gamejs.onEvent(function(event) {

		/* Mouse movement */
		if (event.type === gamejs.event.MOUSE_MOTION) {
			/* If we are on canvas, draw rectangle on current tile */
			if (mainSurface.rect.collidePoint(event.pos)) {
				cursor_pos = war.getTile(event.pos);

				var dist = war.getDistance(cursor_pos, activeMonster.position);

				if (dist > activeMonster.moveRange)
					cursor_state = globals.CursorState.DISALLOWED;
				else if (dist <= activeMonster.moveRange)
					cursor_state = globals.CursorState.ALLOWED;

				// TODO: handle if there's a monstrocity */
			}
		}

		/* Mouse clicking */
		if (event.type === gamejs.event.MOUSE_UP) {
			
			// TODO: make sure only clicks on game area are registered
			// (after status area is implemented, that is)
			if (mainSurface.rect.collidePoint(event.pos)) {

				// if activeMonster's not human controlled, we do nothing
				if (activeMonster.controller !== globals.Controller.HUMAN)
					return;

				// get clicked tile
				var click_pos = war.getTile(event.pos);

				// check its state and distance there
				var tileState = war.getTileState(click_pos);
				var dist = war.getDistance(click_pos, activeMonster.position);

				console.log("pos:", click_pos, "state:", tileState, "dist:", dist);

				/* if tile is empty and within reach, we move there */
				if (tileState === globals.TileState.EMPTY && dist <= activeMonster.moveRange) {
					activeMonster.moveTo(click_pos);
				}
			}
		}
	});

	
	/*
	 * Main loop
	 */


	/* msDuration = time since last tick() call */
	gamejs.onTick(function(msDuration) {

		if (war.getCurrentUnit() != activeMonsterIndex) {
			activeMonsterIndex = war.getCurrentUnit();
			activeMonster = gMonsters.sprites()[activeMonsterIndex];
			activeMonster.changeState(globals.MonsterState.ACTIVE);
		}
		/*
		 * Drawing stuff
		 */

		// update the monsters
		gMonsters.update(msDuration);

		// clear
		mainSurface.fill("#efefef");
		
		// draw ground first
		gGroundTiles.draw(mainSurface);

		// then "cursor"
		war.drawCursor(mainSurface, cursor_pos, cursor_state);

		// on top of everything else, monsters
		gMonsters.draw(mainSurface);

	});
}


/*
 * Preloads
 */


gamejs.preload(['images/orc.png']);
gamejs.preload(['images/orc_active.png']);
gamejs.preload(['images/octopus.png']);
gamejs.preload(['images/octopus_active.png']);
gamejs.preload(['images/tile.png']);


/* Go! */
gamejs.ready(main);
