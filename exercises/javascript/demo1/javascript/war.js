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

exports.getMonsterAt = function(arr) { 
	var id = this.getTileMonsterID(arr);
	return globals.Monsters.sprites()[id];
}

exports.getPointTowardsGoal = function(p1, p2, range) {
	/* this shouldn't happen, but who knows */
	if ((this.getDistance(p1, p2) <= range) && (this.getTileState(p2) == globals.TileState.EMPTY))
		return p2;

	/* we start looking suitable endpoint in rectangular area which cornerpoints are p1 and p2 
	 * and select the furthest available */

	var [x0, y0] = [Math.min(p1[0], p2[0]), Math.min(p1[1], p2[1])];
	var [delta_x, delta_y] = [Math.abs(p2[0]-p1[0]), Math.abs(p2[1]-p1[1])];
	var closestPoint = 1000;
	var point = null;

	console.log("delta_x:",delta_x, "delta_y:", delta_y);

	for (var x=x0; x<=(x0+delta_x); x++) {
		for (var y=y0; y<=(y0+delta_y);y++) {
			if ((this.getDistance(p2,[x,y]) <= closestPoint) 
				&& (this.getDistance(p1,[x,y]) <= range)
				&& (this.getTileState([x,y]) == globals.TileState.EMPTY)) {
					closestPoint = this.getDistance(p2,[x,y]);
					point = [x,y];
			}
		}
	}
	console.log("Wayward point:",point);
	return point;
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

/* 
 * TODO:
 * 		better target selection
 * 		attack/magic ranges?
 */
exports.doAI = function(monster) {
	console.log("AI:",monster.name,monster.id,monster.position);
	var nearestEnemyPosition = this.findNearestEnemy(monster);

	var Action = { ATTACK : 0, GATHER_AROUND : 1, DEFEND_WEAK : 3, MOVE_CLOSER : 4, 
			CAST_SPELL : 5, DO_NOTHING : 99};

	if (nearestEnemyPosition) {
		console.log("Nearest enemy:",nearestEnemyPosition,this.getDistance(monster.position, nearestEnemyPosition));

		/* by default, we attack with our hands and claws. */
		var action = Action.ATTACK;
		var distance = this.getDistance(monster.position, nearestEnemyPosition);
		var nearestEnemy = this.getMonsterAt(nearestEnemyPosition);

		/*
		 *
		 * Decide best action
		 *
		 */

		if (monster.personality === globals.MonsterPersonality.IMMOBILE) {
			if (distance == 1)
				action = Action.ATTACK;
			else if (monster.weapon === globals.WeaponStyle.MELEE)
				action = Action.DO_NOTHING;
			else if (moster.weapon === globals.WeaponStyle.RANGED)
				action = Action.ATTACK;
			else if (moster.weapon === globals.WeaponStyle.MAGIC) {
				action = Action.CAST_SPELL;
			}
		}
		else if (monster.personality === globals.MonsterPersonality.CAREFUL) {
			if (distance == 1)
				action = Action.ATTACK;
			else if (monster.weapon === globals.WeaponStyle.MELEE) {
				action = (distance > monster.moveRange)? Action.GATHER_AROUND : Action.ATTACK;
			}
			else {
				action = Action.ATTACK;
			}
		}
		else if (monster.personality === globals.MonsterPersonality.INDIVIDUAL) {
			
		}
		else if (monster.personality === globals.MonsterPersonality.BERSERK) {
			
		}
		else {
			console.error("Something's wrong with personalities!")
		}


		/*
		 *
		 * Handle the wanted action
		 *
		 */

		if (action === Action.ATTACK) {
			console.log("Action: ATTACK");
			if (monster.weapon === globals.WeaponStyle.MELEE)
				monster.moveTo(nearestEnemyPosition);
			else // ranged || magic
				monster.attack(nearestEnemy);
		}
		else if (action === Action.GATHER_AROUND) {
			console.log("Action: GATHER_AROUND");
			monster.skipTurn();
		}
		else if (action === Action.DEFEND_WEAK) {
			console.log("Action: DEFEND_WEAK");
			monster.skipTurn();
		}
		else if (action === Action.MOVE_CLOSER) {
			console.log("Action: MOVE_CLOSER");
			monster.skipTurn();
		}
		else if (action === Action.CAST_SPELL) {
			// TODO: implement spells
			// for now, we just attack
			monster.attack(nearestEnemy);
		}
		else
			monster.skipTurn();
	}
	else {
		console.warn("Couldn't find nearest enemy!");
		monster.skipTurn();
	}
}
