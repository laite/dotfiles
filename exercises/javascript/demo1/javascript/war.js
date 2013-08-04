/*
 * war.js
 *
 *
 */

var globals = require('global');
var gamejs = require('gamejs');
var draw = require('gamejs/draw');
var name = "WAR 0.1a";

exports.name = function() {
	return name;
};


/*
 *
 * Classes
 *
 *
 */

var Engine = function() {
	
	this.units = [];
	this.tiles = [];

	for (var i=0; i<globals.TILE_AMOUNT;i++) {
		this.tiles[i] = [globals.TILE_AMOUNT];
	}

	this.currentUnit = 0;
}


var engine = new Engine();

/*
 *
 *
 * Helper functions
 *
 *
 */


/* getTile returns array of wanted tile index */
exports.getTile = function(arr) {
	if ((!arr instanceof Array) || (arr.length != 2))
		return [0, 0];

	tile_x = Math.floor(arr[0]/globals.TILE_SIZE);
	tile_y = Math.floor(arr[1]/globals.TILE_SIZE);

	return [tile_x, tile_y];
}

/* getTilePixels returns actual start point of a TILE */
exports.getTilePixels = function(arr) {

	var [tile_x, tile_y] = this.getTile(arr);
	tile_x *= globals.TILE_SIZE;
	tile_y *= globals.TILE_SIZE;

	return [tile_x, tile_y];
}

/* getDistance takes two coordinate points and calculates the distance between them */
exports.getDistance = function(p1, p2) {
	var distance = Math.max(Math.abs(p1[0]-p2[0]), Math.abs(p1[1]-p2[1]));

	return distance;
}

/* drawCursor gets parameters x and y as tiles */
exports.drawCursor = function(surface, x, y, state) {

	var cursor_size = 3;

	x *= globals.TILE_SIZE;
	y *= globals.TILE_SIZE;
	x = Math.max(x, (cursor_size/2));
	x = Math.min(x, globals.CANVAS_WIDTH-globals.TILE_SIZE-(cursor_size/2));
	y = Math.max(y, (cursor_size/2));
	y = Math.min(y, globals.CANVAS_HEIGHT-globals.TILE_SIZE-(cursor_size/2));

	var col = "green";

	if (state === globals.CursorState.DISALLOWED)
		col = "#666";
	else if (state === globals.CursorState.ATTACK)
		col = "#880000";

	draw.rect(surface, col, new gamejs.Rect([x,y,globals.TILE_SIZE,globals.TILE_SIZE]), cursor_size);
}

/*
 *
 *
 * Engine initialization
 *
 *
 */

exports.initUnits = function(gMonsters) {

	/*
	 * We calculate order of units based on their speed
	 * so that fastests units go first
	 *
	 * Resulting order array is engine.units
	 */

	var speeds = [];
	var i = 0;

	gMonsters.forEach(function(monster) {
		engine.units.push(i++);
		speeds.push(monster.speed); 
	});

	function sort_index(a, b) {
		return (speeds[a] < speeds[b])? 1 : -1;
	}

	engine.units.sort(sort_index);
	engine.currentUnit = 0;

	console.log("initUnits - ok");
}

exports.initTiles = function(gMonsters) {

	/*
	 * We need to know where monsters are on the map
	 * and which tiles are empty
	 *
	 * Array of tiles is engine.tiles
	 */

	for (var i=0; i<globals.TILE_AMOUNT; i++) {
		for (var j=0; j<globals.TILE_AMOUNT; j++) {
			engine.tiles[i][j] = globals.TileState.EMPTY;
		}
	}

	gMonsters.forEach(function(monster) {
		var [x, y] = [monster.x, monster.y];

		engine.tiles[x][y] = globals.TileState.OCCUPIED;
	});
	
	console.log("initTiles - ok");
}

/*
 *
 *
 * Engine functions
 *
 *
 */


exports.nextUnit = function() {
	engine.currentUnit = (engine.currentUnit+1)%engine.units.length;

	console.log("Next unit:",engine.units[engine.currentUnit]);
	return engine.units[engine.currentUnit];
}

exports.getCurrentUnit = function() {
	return engine.units[engine.currentUnit];
}

// TODO: error checking?
exports.getTileState = function(arr) {
	return engine.tiles[arr[0]][arr[1]];
}

exports.setTileState = function(x, y, state) {
	engine.tiles[x][y] = state;
	console.log("Tile [",x,",",y,"] has state:", state);
}

/*
 *
 *
 * Artificial Intelligence
 *
 *
 */

exports.doAI = function(monster) {
	console.log("AI:",monster.x, monster.y);
	monster.moveTo(monster.x, monster.y - 1);
}
