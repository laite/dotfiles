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

/*
 *
 * Battle status logger
 *
 */

var BattleStatus = function() {
    this.text = [];

    this.reset = function() {
	this.text = [];
    }

    this.draw = function() {
	document.getElementById("statusLine").innerHTML = "";

	for (var i = 0; i < this.text.length; i++)
	    document.getElementById("statusLine").innerHTML += this.text[i]+"<br/>";
    }

    this.add = function(text) {
	/* we add new text on the beginning and remove from the end */
	if (this.text.length >= globals.LOG_LINES) {
	    this.text.pop();
	}

	this.text.unshift(text);

	this.draw()
    }
}

exports.battleStatus = new BattleStatus();

/*
 *
 * Engine
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

exports.updateCursorState = function(cursor_pos,activeMonster) {

    var dist = this.getDistance(cursor_pos, activeMonster.position);
    var cursor_state = globals.CursorState.ALLOWED;

    if (dist > activeMonster.moveRange) {
	cursor_state = globals.CursorState.DISALLOWED;
    }
    else {
	var monsterInTile = this.getTileState(cursor_pos);
	if (monsterInTile === globals.TileState.OCCUPIED) {
	    if (this.getMonsterAt(cursor_pos).family != activeMonster.family)
		cursor_state = globals.CursorState.ATTACK;
	}
	else {
	    cursor_state = globals.CursorState.ALLOWED;
	}
    }

    return cursor_state;
}

/* drawCursor gets parameters x and y as tiles */
exports.drawCursor = function(surface, position, state) {

    var cursor_size = 0;
    var [x, y] = position;

    if (state !== globals.CursorState.ACTIVE_MONSTER) {
	x *= globals.TILE_SIZE;
	y *= globals.TILE_SIZE;
	x = Math.max(x, (cursor_size/2));
	x = Math.min(x, globals.CANVAS_WIDTH-globals.TILE_SIZE-(cursor_size/2));
	y = Math.max(y, (cursor_size/2));
	y = Math.min(y, globals.CANVAS_HEIGHT-globals.TILE_SIZE-(cursor_size/2));
    }

    var col = "rgba(128, 255, 128, 0.2)";

    if (state === globals.CursorState.DISALLOWED)
	col = "rgba(255, 255, 255, 0.2)";
    else if (state === globals.CursorState.ATTACK)
	col = "rgba(255, 0, 0, 0.3)";
    else if (state === globals.CursorState.ACTIVE_MONSTER)
	col = "rgba(0, 255, 128, 0.3)";

    draw.rect(surface, col, new gamejs.Rect([x,y,globals.TILE_SIZE,globals.TILE_SIZE]), cursor_size);
}

exports.drawActiveMonsterTile = function(surface, position) {
    this.drawCursor(surface, position, globals.CursorState.ACTIVE_MONSTER);
}

exports.randomPersonality = function(arr) {
    var i = Math.floor(arr.length * Math.random());
    return arr[i];
}

var addRow = function(item, value) {
    return "<tr><td>" + item + "</td><td>" + value + "</td></tr>";
    //return item + " " + value + "<br/>";
}

exports.drawStats = function(monster, enemy) {

    if (monster !== null) {
	var health = monster.hp + " (" + Math.round(100*monster.hp/monster.maxhp) + "%)";

	document.getElementById("mt1Name").innerHTML = monster.name;
	document.getElementById("mt1Family").innerHTML = monster.family;
	document.getElementById("mt1Speed").innerHTML = monster.speed;
	document.getElementById("mt1Health").innerHTML = health;
	document.getElementById("mt1MeleeDamage").innerHTML = monster.getDamageString(globals.WeaponStyle.MELEE);
	document.getElementById("mt1RangedDamage").innerHTML = monster.getDamageString(globals.WeaponStyle.RANGED);
    }

    if (enemy !== null) {
	var health = enemy.hp + " (" + Math.round(100*enemy.hp/enemy.maxhp) + "%)";

	document.getElementById("mt2Name").innerHTML = enemy.name;
	document.getElementById("mt2Family").innerHTML = enemy.family;
	document.getElementById("mt2Speed").innerHTML = enemy.speed;
	document.getElementById("mt2Health").innerHTML = health;
	document.getElementById("mt2MeleeDamage").innerHTML = enemy.getDamageString(globals.WeaponStyle.MELEE);
	document.getElementById("mt2RangedDamage").innerHTML = enemy.getDamageString(globals.WeaponStyle.RANGED);
	document.getElementById("monsterTable2").style.display = 'block';
    }
    else
    {
	console.log("HIDE!");
	document.getElementById("monsterTable2").style.display = 'none';
    }

}

/*
 *
 *
 * Engine initialization
 *
 *
 */

exports.init = function(forceUnit = 0) {

    /*
     * Init map tiles
     */

    for (var index_x=0; index_x<globals.TILE_AMOUNT; index_x++) {
	for (var index_y=0; index_y<globals.TILE_AMOUNT; index_y++) {
	    engine.tiles[index_x][index_y]['state'] = globals.TileState.EMPTY;
	}
    }

    /*
     * Init units
     *
     * We calculate order of units based on their speed
     * so that fastests units go first
     *
     * Resulting order array is engine.units
     */

    var i = 0;
    var speeds = [];
    engine.units = [];

    globals.Monsters.forEach(function(monster) {
	var [x, y] = monster.position;

	monster.id = i++;
	engine.units.push(monster.id);
	speeds.push(monster.speed); 

	engine.tiles[x][y]['state'] = globals.TileState.OCCUPIED;
	engine.tiles[x][y]['monster'] = monster.id;
    });

    function sort_index(a, b) {
	return (speeds[a] < speeds[b])? 1 : -1;
    }

    engine.units.sort(sort_index);
    engine.currentUnit = forceUnit%engine.units.length;

    console.log("* INIT *");
    console.log("currentUnit:",engine.currentUnit,"units.length:",engine.units.length,"forceUnit:",forceUnit);
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

exports.getCurrentUnitIndex = function() {
    return engine.currentUnit;
}

exports.getTileState = function(arr) {
    arr[0] = Math.max(Math.min(arr[0],globals.TILE_AMOUNT-1), 0);
    arr[1] = Math.max(Math.min(arr[1],globals.TILE_AMOUNT-1), 0);

    return engine.tiles[arr[0]][arr[1]]['state'];
}

exports.setTileState = function(arr, state, id = null) {
    var [x,y] = arr;

    engine.tiles[x][y]['state'] = state;
    engine.tiles[x][y]['monster'] = id;
    console.log("Tile [",x,",",y,"] has state:", state);
}

exports.getTileMonsterID = function(arr) {
    arr[0] = Math.max(Math.min(arr[0],globals.TILE_AMOUNT-1), 0);
    arr[1] = Math.max(Math.min(arr[1],globals.TILE_AMOUNT-1), 0);

    return engine.tiles[arr[0]][arr[1]]['monster'];
}

exports.getMonsterAt = function(arr) { 
    var id = this.getTileMonsterID(arr);

    if (id === null)
	return null;
    else
	return globals.Monsters.sprites()[id];
}

exports.moveTowardsGoal = function(p1, p2, range) {
    /* if p2 is at range */
    if (this.getDistance(p1, p2) <= range) {
	/* if it's empty or if there is a hostile monster */
	if ((this.getTileState(p2) == globals.TileState.EMPTY) || 
		((this.getTileState(p2) === globals.TileState.OCCUPIED) 
		 && (this.getMonsterAt(p1).family != this.getMonsterAt(p2).family)))	
	{
	    return p2;
	}
    }	

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

exports.getRectFromRadius = function(pos, radius) {
    var x0 = pos[0]-radius, y0 = pos[1]-radius;
    var x1 = pos[0]+radius, y1 = pos[1]+radius;

    x0 = Math.min(x0, globals.TILE_AMOUNT-1); y0 = Math.min(y0, globals.TILE_AMOUNT-1);
    x0 = Math.max(x0, 0); y0 = Math.max(y0, 0);
    x1 = Math.min(x1, globals.TILE_AMOUNT-1); y1 = Math.min(y1, globals.TILE_AMOUNT-1);
    x1 = Math.max(x1, 0); y1 = Math.max(y1, 0);

    return [x0,y0,x1,y1];
}

/* findFreeTile gets rect with four points as argument */
exports.findFreeTile = function(rect) {
    if ((!rect instanceof Array) || (rect.length < 4)) {
	console.error("Invalid parameter at findFreeTile!");
	return null;
    }

    var allPoints = [];
    var found = false, foundPoint = [];
    var [x0, y0] = [Math.min(rect[0],rect[2]), Math.min(rect[1],rect[3])];
    var [x1, y1] = [Math.max(rect[0],rect[2]), Math.max(rect[1],rect[3])];

    for (var x = x0; x <= x1; x++) {
	for (var y = y0; y <= y1; y++) {
	    allPoints.push([x,y]);
	}
    }

    while (!found) {
	var i = Math.floor(allPoints.length * Math.random());
	if (this.getTileState(allPoints[i]) === globals.TileState.EMPTY) {
	    found = true;
	    foundPoint = allPoints[i];
	}
	else
	    allPoints.splice(i,1);

	if (allPoints.length == 0)
	    found = true;
    }

    if (!found)
	return null;
    else
	return foundPoint;
}

exports.findNewLocation = function(arr) {
    var found = false;
    var radius = 1;
    var newLocation = null;

    while (!found) {
	var rect = this.getRectFromRadius(arr, radius);
	newLocation = this.findFreeTile(rect);

	if ((newLocation.length !== null) || (radius > 10))
	    found = true;
	else
	    radius++;
    }

    if (newLocation === null)
	console.error("findNewLocation failed, returning null");

    return newLocation;
}

/*
 *
 *
 * Battle
 *
 *
 */

exports.samePlace = function(p1, p2) {
    return ((p1[0] == p2[0]) && (p1[1] == p2[1]));
}

exports.battle = function(id1, id2) {
    var m1 = globals.Monsters.sprites()[id1];
    var m2 = globals.Monsters.sprites()[id2];

    console.log("### BATTLE ###");
    console.log(m1.name, " vs. ", m2.name);

    /* melee attack */
    if (this.samePlace(m1.position, m2.position)) {

	/* attacker goes first */
	var m1Damage = m1.getDamage(globals.WeaponStyle.MELEE);
	console.log(m1.name,"damage:",m1Damage);
	this.battleStatus.add(m1.name + " hit " + m2.name + " for " + m1Damage + " damage!");
	m2.hp -= m1Damage;

	if (m2.hp > 0) {
	    var m2Damage = m2.getDamage(globals.WeaponStyle.MELEE);
	    console.log(m2.name,"damage:",m2Damage);
	    this.battleStatus.add(m2.name + " hit " + m1.name + " for " + m2Damage + " damage!");
	    m1.hp -= m2Damage;
	}
    }
    /* ranged attack */
    else {
	/* There is no retaliation */
	var m1Damage = m1.getDamage(globals.WeaponStyle.RANGED);
	console.log(m1.name,"damage:",m1Damage);
	m2.hp -= m1Damage;
    }
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
    console.log("AI:",monster.name,monster.position);
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
