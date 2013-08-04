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
	this.tiles = [globals.TILE_AMOUNT];

	for (var i=0; i<globals.TILE_AMOUNT;i++) {
		this.tiles[i] = [];
		for (var j=0; j<globals.TILE_AMOUNT;j++) {
			this.tiles[i].push({ state: globals.TileState.EMPTY, monster : null});
		}
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
	if ((!arr instanceof Array) || (arr.length < 2))
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
	var [x, y] = [Math.abs(p1[0]-p2[0]), Math.abs(p1[1]-p2[1])];

	/* 
	 * Movement cost for vector is (longer side) + (shorter side / 2)
	 * division is rounded down
	 */
	var distance = Math.max(x, y) + Math.floor(Math.min(x,y)*0.5);

	return distance;
}

/* drawCursor gets parameters x and y as tiles */
exports.drawCursor = function(surface, position, state) {

	var cursor_size = 0;
	var [x, y] = position;

	x *= globals.TILE_SIZE;
	y *= globals.TILE_SIZE;
	x = Math.max(x, (cursor_size/2));
	x = Math.min(x, globals.CANVAS_WIDTH-globals.TILE_SIZE-(cursor_size/2));
	y = Math.max(y, (cursor_size/2));
	y = Math.min(y, globals.CANVAS_HEIGHT-globals.TILE_SIZE-(cursor_size/2));

	var col = "rgba(128, 255, 128, 0.2)";

	if (state === globals.CursorState.DISALLOWED)
		col = "rgba(255, 255, 255, 0.2)";
	else if (state === globals.CursorState.ATTACK)
		col = "#880000";

	draw.rect(surface, col, new gamejs.Rect([x,y,globals.TILE_SIZE,globals.TILE_SIZE]), cursor_size);
}

exports.randomPersonality = function(arr) {
	var i = Math.floor(arr.length * Math.random());
	return arr[i];
}

/*
 *
 *
 * Engine initialization
 *
 *
 */

exports.initUnits = function() {

	/*
	 * We calculate order of units based on their speed
	 * so that fastests units go first
	 *
	 * Resulting order array is engine.units
	 */

	var speeds = [];
	var i = 0;

	globals.Monsters.forEach(function(monster) {
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

exports.initTiles = function() {

	/*
	 * We need to know where monsters are on the map
	 * and which tiles are empty
	 *
	 * Array of tiles is engine.tiles
	 */

	for (var i=0; i<globals.TILE_AMOUNT; i++) {
		for (var j=0; j<globals.TILE_AMOUNT; j++) {
			engine.tiles[i][j]['state'] = globals.TileState.EMPTY;
		}
	}

	globals.Monsters.forEach(function(monster) {
		var [x, y] = monster.position;

		engine.tiles[x][y]['state'] = globals.TileState.OCCUPIED;
		engine.tiles[x][y]['monster'] = monster.id;
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

	console.log("Next unit:",engine.units[engine.currentUnit],engine.currentUnit, engine.units.length);
	return engine.units[engine.currentUnit];
}

exports.getCurrentUnit = function() {
	return engine.units[engine.currentUnit];
}

// TODO: error checking?
exports.getTileState = function(arr) {
	return engine.tiles[arr[0]][arr[1]]['state'];
}

exports.setTileState = function(arr, state, id = null) {
	var [x,y] = arr;

	engine.tiles[x][y]['state'] = state;
	engine.tiles[x][y]['monster'] = id;
	console.log("Tile [",x,",",y,"] has state:", state);
}

exports.getTileMonsterID = function(arr) {
	return engine.tiles[arr[0]][arr[1]]['monster'];
}

/*
 *
 *
 * Artificial Intelligence
 *
 *
 */

exports.findNearestEnemy = function(monster) {
	found = null;
	distance = 1000;

	for (var i=0; i < engine.tiles.length; i++) {
		for (var j=0; j < engine.tiles[i].length; j++) {
			if (engine.tiles[i][j]['monster'] 
				&& (monster.family != globals.Monsters.sprites()[engine.tiles[i][j]['monster']].family)
				&& (this.getDistance(monster.position, [i,j]) < distance)) {
					distance = this.getDistance(monster.position, [i,j]);
					found = [i,j];
			}
		}
	}
	return found;
}

exports.doAI = function(monster) {
	console.log("AI:",monster.name,monster.id,monster.position);
	nearestEnemy = this.findNearestEnemy(monster);

	var Action = { ATTACK_MELEE : 0, ATTACK_RANGER : 1, ATTACK_SPELL : 2,
			GATHER_AROUND : 3, DEFEND_WEAK : 4, 
			DO_NOTHING : 99};

	if (nearestEnemy) {
		console.log("Nearest enemy:",nearestEnemy,this.getDistance(monster.position, nearestEnemy));

		/* by default, we attack with our hands and claws. */
		var action = Action.ATTACK_MELEE;
		var distance = this.getDistance(monster.position, nearestEnemy);


		if (monster.personality === globals.MonsterPersonality.IMMOBILE) {
			if (distance == 1)
				action = Action.ATTACK_MELEE;
			else if (monster.weapon === globals.WeaponStyle.MELEE)
				action = Action.DO_NOTHING;
			else if (moster.weapon === globals.WeaponStyle.RANGED)
				action = Action.ATTACK_RANGED;
			else if (moster.weapon === globals.WeaponStyle.MAGIC) {
					// cast a spell
			}
		}
		else if (monster.personality === globals.MonsterPersonality.CAREFUL) {
			if (distance == 1)
				action = Action.ATTACK_MELEE;
			else if (monster.weapon === globals.WeaponStyle.MELEE) {
				action = (distance > monster.moveRange)? Action.GATHER_AROUND : Action.ATTACK_MELEE;
			}
			else if (monster.weapon === globals.WeaponStyle.RANGED) {
				action = Action.ATTACK_RANGED;
			}
			else if (monster.weapon === globals.WeaponStyle.MAGIC) {
				action = Action.ATTACK_MAGIC;
			}
		}
		else if (monster.personality === globals.MonsterPersonality.INDIVIDUAL) {
			//monster.skipTurn();
		}
		else if (monster.personality === globals.MonsterPersonality.BERSERK) {
			//monster.skipTurn();
		}
		else {
			console.error("Something's wrong with personalities!")
		}


		if (action === Action.ATTACK_MELEE) {
			if (distance <= monster.moveRange) {
				//monster.skipTurn();
			}
			else {
				//monster.skipTurn();
				//monster.moveTowards(monster.position);
			}
		}
		else {
			//monster.skipTurn();
		}
	}

	monster.skipTurn();
}
