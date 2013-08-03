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


var cursor_x = 0, cursor_y = 0;

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
	this.name = "Monster!";

	// call superconstructor (Monster is derived from Sprite)
	Monster.superConstructor.apply(this, arguments);

	// speed varies between (1, 10)
	this.speed = Math.ceil(10 * Math.random());

	// passive image
	this.image = gamejs.image.load(this.image_name + ".png");

	// rect shows the position and dimensions of monster
	this.rect = new gamejs.Rect(rect, [globals.TILE_SIZE, globals.TILE_SIZE]);

	// destination is used while traveling
	this.destination = [0, 0];

	// monster.x and monster.y show tile monster is currently on
	[this.x,this.y] = war.getTile(rect);


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
	this.moveTo = function(x, y) {
		if (this.state !== globals.MonsterState.ACTIVE)
			return;

		war.setTileState(this.x, this.y, globals.TileState.EMPTY);
		war.setTileState(x, y, globals.TileState.OCCUPIED);
		this.destination = [x, y];
		this.changeState(globals.MonsterState.MOVING);

		console.log("Monster",this.id,"is on its way!");
	}

	/* activate sets monster as 'active' one on battlefield */
	this.activate = function() {
		console.log("Monster", this.id, "just became active");
		this.image = gamejs.image.load(this.image_name + "_active.png");
	}

	/* deactivate passivates the monster */
	this.deactivate = function() {
		console.log("Monster", this.id, "was de-activated");
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

	console.log("Created monster", this.id, "(speed:", this.speed, ")");

	return this;
};


/*
 * Derivative monster classes
 */


var Orc = function(rect, id) {
	this.image_name = "images/orc";
	Monster.call(this, rect, id);

	this.name = "Orc";
}

var Octopus = function(rect, id) {
	this.image_name = "images/octopus";
	Monster.call(this, rect, id);

	this.name = "Octo-Monster";
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
			this.x = this.destination[0];
			this.y = this.destination[1];
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

	var lastUnit = -1;

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

	//lastUnit = war.getCurrentUnit();


	/*
	 * Event handling
	 */


	gamejs.onEvent(function(event) {

		/* Mouse movement */
		if (event.type === gamejs.event.MOUSE_MOTION) {
			/* If we are on canvas, draw rectangle on current tile */
			if (mainSurface.rect.collidePoint(event.pos)) {

				[cursor_x, cursor_y] = war.getTilePixels([event.pos[0], event.pos[1]]);

				cursor_x = Math.max(cursor_x, 2.5);
				cursor_x = Math.min(cursor_x, globals.CANVAS_WIDTH-globals.TILE_SIZE-2.5);
				cursor_y = Math.max(cursor_y, 2.5);
				cursor_y = Math.min(cursor_y, globals.CANVAS_HEIGHT-globals.TILE_SIZE-2.5);
			}
		}

		/* Mouse clicking */
		if (event.type === gamejs.event.MOUSE_UP) {
			
			// TODO: make sure only clicks on game area are registered
			// (after status area is implemented, that is)
			if (mainSurface.rect.collidePoint(event.pos)) {
				
				var [click_x, click_y] = war.getTile([event.pos[0], event.pos[1]]);
				var tileState = war.getTileState([click_x, click_y]);
				console.log("x:", click_x, "y:", click_y, "state:", tileState);

				if (tileState === globals.TileState.EMPTY) {
					gMonsters.sprites()[war.getCurrentUnit()].moveTo(click_x, click_y);
				}
			}
		}
	});

	
	/*
	 * Main loop
	 */


	/* msDuration = time since last tick() call */
	gamejs.onTick(function(msDuration) {

		if (war.getCurrentUnit() != lastUnit) {
			lastUnit = war.getCurrentUnit();
			gMonsters.sprites()[lastUnit].changeState(globals.MonsterState.ACTIVE);
		}
		/*
		 * Drawing stuff
		 */

		// update the monsters
		gMonsters.update(msDuration);

		// clear
		mainSurface.fill("#efefef");
		
		// draw ground first, then monsters
		gGroundTiles.draw(mainSurface);
		gMonsters.draw(mainSurface);

		// then "cursor"
		draw.rect(mainSurface, "#006600", new gamejs.Rect([cursor_x,cursor_y,globals.TILE_SIZE,globals.TILE_SIZE]), 5);
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
