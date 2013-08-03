/*
 * war.js
 *
 *
 */

var globals = require('global');
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

	for (var i=0; i<engine.units.length; i++)
		console.log(engine.units[i]);

	engine.currentUnit = engine.units[0];

	console.log("initUnits - ok");
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

	return engine.currentUnit;
}

exports.getCurrentUnit = function() {
	return engine.currentUnit;
}
