
var gamejs = require('gamejs');
var draw = require('gamejs/draw');

var CANVAS_HEIGHT = 640;
var CANVAS_WIDTH = 640;

var TILE_SIZE = 64;

var cursor_x = 0, cursor_y = 0;

var Monster = function(rect) {

	// call superconstructor
	Monster.superConstructor.apply(this, arguments);
	this.speed = 80 + (40 * Math.random());

	this.image = gamejs.image.load("images/monster.png");

	// rect shows the position of monster
	this.rect = new gamejs.Rect(rect, [TILE_SIZE, TILE_SIZE]);

	return this;
};

var Ground = function(rect) {
	Ground.superConstructor.apply(this, arguments);
	this.image = gamejs.image.load("images/tile.png");

	this.rect = new gamejs.Rect(rect, [TILE_SIZE, TILE_SIZE]);

	return this;
};

// inherit (actually: set prototype)
gamejs.utils.objects.extend(Monster, gamejs.sprite.Sprite);
gamejs.utils.objects.extend(Ground, gamejs.sprite.Sprite);

Monster.prototype.update = function(msDuration) {

	// moveIp = move in place
	this.rect.moveIp(0, this.speed * (msDuration/1000));
	if (this.rect.top+this.rect.height > CANVAS_HEIGHT) {
		this.speed *= -1;
		//this.image = gamejs.transform.rotate(this.originalImage, this.rotation + 180);
	} else if (this.rect.top < 0 ) {
		this.rect.top = 0;
		this.speed *= -1;
		//this.image = gamejs.transform.rotate(this.originalImage, this.rotation);
	}
};

function main() {


	/*
	 * Initial screen setup
	 */


	gamejs.display.setMode([CANVAS_WIDTH, CANVAS_HEIGHT]);
	gamejs.display.setCaption("Example Monsters");

	var mainSurface = gamejs.display.getSurface();


	/*
	 * Sprites
	 */


	/* Monsters */

	var gMonsters = new gamejs.sprite.Group();

	for (var i=0; i < (CANVAS_WIDTH/TILE_SIZE); i++)
		gMonsters.add(new Monster([i*TILE_SIZE, 0]));

	/* Ground */

	var gGroundTiles = new gamejs.sprite.Group();

	for (var i=0; i<(CANVAS_WIDTH/TILE_SIZE); i++) {
		for (var j=0; j<(CANVAS_WIDTH/TILE_SIZE); j++) {
			gGroundTiles.add(new Ground([i*TILE_SIZE, j*TILE_SIZE]));
		}
	}


	/*
	 * Event handling
	 */


	gamejs.onEvent(function(event) {

		/* Mouse movement */
		if (event.type === gamejs.event.MOUSE_MOTION) {
			/* If we are on canvas, draw rectangle on current tile */
			if (mainSurface.rect.collidePoint(event.pos)) {
				cursor_x = Math.floor(event.pos[0]/TILE_SIZE)*TILE_SIZE;
				cursor_y = Math.floor(event.pos[1]/TILE_SIZE)*TILE_SIZE;

				cursor_x = Math.max(cursor_x, 2.5);
				cursor_x = Math.min(cursor_x, CANVAS_WIDTH-TILE_SIZE-2.5);
				cursor_y = Math.max(cursor_y, 2.5);
				cursor_y = Math.min(cursor_y, CANVAS_HEIGHT-TILE_SIZE-2.5);
			}
		}

		/* Mouse clicking */
		if (event.type === gamejs.event.MOUSE_UP) {
			// check if there's a monster here
			var monstersHere = gMonsters.collidePoint(event.pos);
			if (monstersHere.length > 0) {
				monstersHere[0].speed *= -1;
			}
			else {
				gMonsters.forEach(function(monster) {
					monster.speed *= -1;
				});
			}
		}
	});

	
	/*
	 * Main loop
	 */


	// msDuration = time since last tick() call
	gamejs.onTick(function(msDuration) {

		/*
		 * Drawing stuff
		 */

		mainSurface.fill("#efefef");
		
		// update the monsters
		gMonsters.update(msDuration);

		// draw ground first, then monsters
		gGroundTiles.draw(mainSurface);
		gMonsters.draw(mainSurface);

		// then "cursor"
		draw.rect(mainSurface, "#006600", new gamejs.Rect([cursor_x,cursor_y,TILE_SIZE,TILE_SIZE]), 5);
	});
}

/**
 * M A I N
 */
gamejs.preload(['images/monster.png']);
gamejs.preload(['images/tile.png']);
gamejs.ready(main);
