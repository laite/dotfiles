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

var war = require('war');


/*
 * Initial members
 */


var cursor_x = 0, cursor_y = 0;

console.log(war.name());


/*
 * Sprite classes
 */

var Monster = function(rect, id) {

	this.id = id;

	// call superconstructor
	Monster.superConstructor.apply(this, arguments);
	this.speed = 80 + (40 * Math.random());

	var state = globals.MonsterState.INACTIVE;

	this.image = gamejs.image.load("images/monster.png");

	// rect shows the position of monster
	this.rect = new gamejs.Rect(rect, [globals.TILE_SIZE, globals.TILE_SIZE]);

	[this.x,this.y] = war.getTile(rect);
	/*
	 * Monster public functions
	 */

	// moveTo gets destination in terms of tiles, aka. [0..globals.TILE_AMOUNT]
	this.moveTo = function(x, y) {
		this.destination = [x, y];
		this.changeState(globals.MonsterState.MOVING);
	}
	this.activate = function() {
		console.log("Monster", this.id, "just became active");
		this.image = gamejs.image.load("images/monster_active.png");
	}

	this.deactivate = function() {
		console.log("Monster", this.id, "was de-activated");
		this.image = gamejs.image.load("images/monster.png");
	}

	this.getState = function() {
		return this.state;
	}

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

var Ground = function(rect) {
	Ground.superConstructor.apply(this, arguments);
	this.image = gamejs.image.load("images/tile.png");

	this.rect = new gamejs.Rect(rect, [globals.TILE_SIZE, globals.TILE_SIZE]);

	return this;
};

// inherit (actually: set prototype)
gamejs.utils.objects.extend(Monster, gamejs.sprite.Sprite);
gamejs.utils.objects.extend(Ground, gamejs.sprite.Sprite);

Monster.prototype.update = function(msDuration) {

	if (this.getState() === globals.MonsterState.MOVING) {

		// moveIp, move in place
		this.rect.moveIp(0, this.speed * (msDuration/1000));

		/* Check boundaries */
		if (this.rect.top+this.rect.height > globals.CANVAS_HEIGHT) {
			this.rect.top = globals.CANVAS_HEIGHT-this.rect.height-1;
			this.speed *= -1;
		} else if (this.rect.top < 0 ) {
			this.rect.top = 0;
			this.speed *= -1;
		}
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


	/*
	 * Sprites
	 */


	/* Monsters */

	var gMonsters = new gamejs.sprite.Group();

	for (var i=0; i < (globals.AMOUNT_OF_MONSTERS); i++)
		gMonsters.add(new Monster([i*globals.TILE_SIZE, 0], i));

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

	gMonsters.sprites()[war.getCurrentUnit()].changeState(globals.MonsterState.ACTIVE);


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

				// check if there's a monster here
				var monstersHere = gMonsters.collidePoint(event.pos);
				if (monstersHere.length > 0) {
					monstersHere[0].changeState(globals.MonsterState.ACTIVE);
				}
				else {
					gMonsters.forEach(function(monster) {
						monster.speed *= -1;
					});
				}
				console.log("click");
			}
		}
	});

	
	/*
	 * Main loop
	 */


	/* msDuration = time since last tick() call */
	gamejs.onTick(function(msDuration) {

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


gamejs.preload(['images/monster.png']);
gamejs.preload(['images/monster_active.png']);
gamejs.preload(['images/tile.png']);


/* Go! */
gamejs.ready(main);
