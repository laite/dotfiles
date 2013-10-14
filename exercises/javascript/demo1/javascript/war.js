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
 * Ground
 *
 */

var Ground = exports.Ground = function(rect, state) {
    Ground.superConstructor.apply(this, arguments);

    this.blocked = state;
    this.occupied = false;
    this.monsterId = null;

    this.rect = new gamejs.Rect(rect, [globals.TILE_SIZE, globals.TILE_SIZE]);

    tile_x = Math.floor(this.rect.left/globals.TILE_SIZE);
    tile_y = Math.floor(this.rect.top/globals.TILE_SIZE);

    this.position = [tile_x, tile_y];

    if (state === globals.TileState.EMPTY) {
	this.image = gamejs.image.load("images/tile.png");
    }
    else if (state === globals.TileState.BLOCKED) {
	this.image = gamejs.image.load("images/tile2.png");
    }

    this.isBlocked = function() {
	return this.blocked;
    }

    this.setBlocked = function(block) {
	this.blocked = block;
	if (this.blocked === globals.TileState.EMPTY)
	    this.image = gamejs.image.load("images/tile.png");
	else if (this.blocked === globals.TileState.BLOCKED)
	    this.image = gamejs.image.load("images/tile2.png");

	console.log("Block at",this.position," changed its state. Blocked:",this.blocked);
    }

    return this;
};

var getGroundTile = function(x, y) {
    x = Math.max(Math.min(x,globals.TILE_AMOUNT-1), 0);
    y = Math.max(Math.min(y,globals.TILE_AMOUNT-1), 0);

    return globals.GroundTiles.sprites()[y*globals.TILE_AMOUNT+x];
}

var resetGroundOccupants = function() {
    globals.GroundTiles.forEach(function() {
	this.occupied = false;
	this.monsterId = null;
    });
}

/*
 *
 * AttackIcon
 *
 *
 */

var AttackIcon = exports.AttackIcon = function(rect) {
    AttackIcon.superConstructor.apply(this, arguments);

    this.originalImage = gamejs.image.load("images/attack.png");
    this.image = this.originalImage;

    this.rect = new gamejs.Rect(rect, [globals.TILE_SIZE, globals.TILE_SIZE]);
    console.log("New attackicon: ", this.rect);

    this.time = 0;
    this.scale = 1;
    this.scaleSpeed = (1/globals.ATTACK_ICON_DURATION);
    this.duration = globals.ATTACK_ICON_DURATION;

    this.origSize = [globals.TILE_SIZE, globals.TILE_SIZE];

    this.reset = function() {
	this.time = 0;
	this.scale = 1;
	this.image = this.originalImage;
    }

    this.setRanged = function() {
	this.originalImage = gamejs.image.load("images/attack_ranged.png");
	this.image = this.originalImage;
	this.scaleSpeed = (1/globals.RANGED_ATTACK_ICON_DURATION);
	this.duration = globals.RANGED_ATTACK_ICON_DURATION;
    }

    this.setMelee = function() {
	this.originalImage = gamejs.image.load("images/attack.png");
	this.image = this.originalImage;
	this.scaleSpeed = (1/globals.ATTACK_ICON_DURATION);
	this.duration = globals.ATTACK_ICON_DURATION;
    }

    this.setMagic = function() {
	this.originalImage = gamejs.image.load("images/attack_magic.png");
	this.image = this.originalImage;
	this.scaleSpeed = (1/globals.MAGIC_ATTACK_ICON_DURATION);
	this.duration = globals.MAGIC_ATTACK_ICON_DURATION;
    }

    return this;
};

gamejs.utils.objects.extend(Ground, gamejs.sprite.Sprite);
gamejs.utils.objects.extend(AttackIcon, gamejs.sprite.Sprite);

AttackIcon.prototype.update = function(msDuration) {
    if (globals.attackOn) {
	var delta = [Math.floor(this.scale*this.origSize[0]), Math.floor(this.scale*this.origSize[1])];
	this.scale += Math.floor(100*msDuration*this.scaleSpeed)/100;
	this.image = gamejs.transform.scale(this.originalImage, [Math.floor(this.scale*this.origSize[0]), Math.floor(this.scale*this.origSize[1])]);
	var size = this.image.getSize();
	delta[0] = Math.max(0, size[0] - delta[0]);
	delta[1] = Math.max(0, size[1] - delta[1]);

	this.rect = new gamejs.Rect(this.rect.left-(delta[0]/2), this.rect.top-(delta[1]/2), size[0], size[1]);
    }
}

/*
 *
 * Units
 *
 */

var Units = function() {

    this.units = [];
    this.currentUnit = 0;

    this.getCurrentUnit = function() {
	return this.units[this.currentUnit];
    }

    this.getCurrentUnitIndex = function() {
	return this.currentUnit;
    }

    this.getUnit = function(index) {
	if (index >= this.units.length)
	    return null;
	else
	    return this.units[index];
    }

    this.reset = function() {
	this.units = [];
    }

    this.addUnit = function(id) {
	this.units.push(id);
    }

    this.sortUnits = function() {
	var speeds = [];

	for (var i=0; i<this.units.length;i++) {
	    speeds.push(getMonsterFromId(this.units[i]).speed);
	}

	function sort_index(a, b) {
	    return (speeds[a] < speeds[b])? 1 : -1;
	}

	this.units.sort(sort_index);
    }

    this.setCurrentUnit = function(unit) {
	if(typeof(unit)==='undefined') unit = 0;

	this.currentUnit = unit%this.units.length;
	console.log("currentUnit:",this.currentUnit,"units.length:",this.units.length);
    }

    this.nextUnit = function() {
	this.setCurrentUnit(this.currentUnit+1);
    }
}


var units = new Units();

/*
 *
 *
 * Helper functions
 *
 *
 */

/*
 * getSpawnPoint returns an free place for new monster 
 * Max amount of families allowed is 8 
 */
exports.getSpawnPoint = function(family) {
    var pMax = globals.TILE_AMOUNT - 1;
    var pHalf = Math.floor(pMax);
    var spawnPlaces = [[0,0], [pMax,pMax], [0,pMax], [pMax,0],[0,pHalf], [pMax,pHalf], [pHalf,0], [pHalf,pMax]];
    var familyNum = globals.familyList.indexOf(family);
    
    console.log("familynum:",familyNum);
    if (familyNum == -1) {
	globals.familyList.push(family);
	if (globals.familyList.length > 8) {
	    console.error("Too many families!");
	    return [0,0];
	}

	return spawnPlaces[globals.familyList.length-1];
    }
    else {
	return spawnPlaces[familyNum];
    }
}

/* randomFromList gets array as parameter, returns one randomly 
 * TODO: weighting using other array as second parameter
 */
var randomFromList = exports.randomFromList = function(arr) {
    var i = Math.floor(arr.length * Math.random());
    return arr[i];
}


/* getTile returns array of wanted tile index */
exports.getTile = function(arr) {
    if ((!arr instanceof Array) || (arr.length < 2))
	return [0, 0];

    tile_x = Math.floor(arr[0]/globals.TILE_SIZE);
    tile_y = Math.floor(arr[1]/globals.TILE_SIZE);

    return [tile_x, tile_y];
}

var isTileOccupiedByEnemy = exports.isTileOccupiedByEnemy = function(arr, family) {
    return ((isTileOccupied(arr)) && (getMonsterAt(arr).family != family))

}
var isTileOccupied = exports.isTileOccupied = function(arr) {
    return getGroundTile(arr[0], arr[1]).occupied;
}

var isTileBlocked = exports.isTileBlocked = function(arr) {
    return getGroundTile(arr[0], arr[1]).blocked;
}

var isTileEmpty = exports.isTileEmpty = function(arr) {
    return !(getGroundTile(arr[0], arr[1]).blocked);
}

/* getDistance takes two coordinate points and calculates the distance between them */
var getDistance = exports.getDistance = function(p1, p2, family) {
    if(typeof(family)==='undefined') family = null;
    var path = findPathTo(family, p1, p2);

    if (path.length == 0)
	return 3000;
    else
	return path.length;
}

var getRangedDistance = function(p1, p2) {
    var x = Math.abs(p1[0]-p2[0]);
    var y = Math.abs(p1[1]-p2[1]);

    return Math.max(x, y);
}

exports.updateCursorState = function(cursor_pos,monster) {

    var dist = getDistance(cursor_pos, monster.position, monster.family);
    var cursor_state = globals.CursorState.ALLOWED;

    if (dist > monster.moveRange) {
	cursor_state = globals.CursorState.DISALLOWED;
    }
    else {
	if (isTileOccupied(cursor_pos)) {
	    if (getMonsterAt(cursor_pos).family != monster.family)
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
    var x = position[0];
    var y = position[1];

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

var addRow = function(item, value) {
    return "<tr><td>" + item + "</td><td>" + value + "</td></tr>";
    //return item + " " + value + "<br/>";
}

exports.areThereStillEnemies = function() {
    var result = false;
    var family1 = "";

    globals.Monsters.forEach(function(monster) {
	if (family1 == "") {
	    family1 = monster.family;
	}
	else if (monster.family != family1) {
	    result = true;
	}
    });

    console.log("result:",result);
    return result;
}

exports.drawStats = function(monster, enemy) {

    if (monster != null) {
	var health = monster.hp + " (" + Math.round(100*monster.hp/monster.maxhp) + "%)";

	document.getElementById("mt1Name").innerHTML = monster.name;
	document.getElementById("mt1Family").innerHTML = monster.family;
	document.getElementById("mt1Speed").innerHTML = monster.speed;
	document.getElementById("mt1Health").innerHTML = health;
	document.getElementById("mt1MeleeDamage").innerHTML = monster.getDamageString(globals.WeaponStyle.MELEE);
	document.getElementById("mt1RangedDamage").innerHTML = monster.getDamageString(globals.WeaponStyle.RANGED);
    }

    if (enemy != null) {
	var health = enemy.hp + " (" + Math.round(100*enemy.hp/enemy.maxhp) + "%)";

	document.getElementById("mt2Name").innerHTML = enemy.name + enemy.effects.getEffectString();
	document.getElementById("mt2Family").innerHTML = enemy.family;
	document.getElementById("mt2Speed").innerHTML = enemy.speed;
	document.getElementById("mt2Health").innerHTML = health;
	document.getElementById("mt2MeleeDamage").innerHTML = enemy.getDamageString(globals.WeaponStyle.MELEE);
	document.getElementById("mt2RangedDamage").innerHTML = enemy.getDamageString(globals.WeaponStyle.RANGED);
	document.getElementById("monsterTable2").style.display = 'block';
    }
    else
    {
	document.getElementById("monsterTable2").style.display = 'none';
    }

}

/*
 *
 *
 * Initialization
 *
 *
 */

exports.init = function(forceUnit) {

    if(typeof(forceUnit)==='undefined') forceUnit = 0;

    /*
     * Init units
     *
     * We calculate order of units based on their speed
     * so that fastests units go first
     *
     * Resulting order array is units
     */

    var i = 0;
    resetGroundOccupants();
    units.reset();

    globals.Monsters.forEach(function(monster) {
	var x = monster.position[0];
	var y = monster.position[1];

	monster.id = i++;
	units.addUnit(monster.id);

	getGroundTile(x, y).occupied = globals.TileState.OCCUPIED;
	getGroundTile(x, y).monsterId = monster.id;
    });

    units.sortUnits();
    units.setCurrentUnit(forceUnit);

    console.log("* INIT *");
}

/*
 *
 *
 * public functions
 *
 *
 */


exports.nextUnit = function() {
    units.nextUnit();
}

exports.getCurrentUnit = function() {
    return units.getCurrentUnit();
}

exports.getCurrentUnitIndex = function() {
    return units.getCurrentUnitIndex();
}

exports.setTileState = function(arr, state, id) {
    if(typeof(id)==='undefined') id = null;
    var x = arr[0];
    var y = arr[1];

    if ((state === globals.TileState.OCCUPIED) || (state === globals.TileState.NOT_OCCUPIED)) {
	getGroundTile(x, y).occupied = (state === globals.TileState.OCCUPIED)? true : false;
	getGroundTile(x, y).monsterId = id;
    }
    else {
	getGroundTile(x, y).setBlocked(state);
    }
}

var getTileMonsterId = function(arr) {
    arr[0] = Math.max(Math.min(arr[0],globals.TILE_AMOUNT-1), 0);
    arr[1] = Math.max(Math.min(arr[1],globals.TILE_AMOUNT-1), 0);

    return getGroundTile(arr[0], arr[1]).monsterId;
}

var getMonsterFromId = exports.getMonsterFromId = function(id) {
    return globals.Monsters.sprites()[id];
}

var getMonsterAt = exports.getMonsterAt = function(arr) { 
    var id = getTileMonsterId(arr);

    if (id == null)
	return null;
    else
	return globals.Monsters.sprites()[id];
}

var findPathTo = exports.findPathTo = function(family, p1, p2) {

    var board = [];

    for (var i=0; i<globals.TILE_AMOUNT; i++) {
	board[i] = [];

	for (var j=0; j<globals.TILE_AMOUNT; j++) {
	    board[i][j] = isTileBlocked([i,j])? 1 : 0;
	    if (isTileOccupied([i,j])) {
		/* we can pass through the tiles that are occupied by own family */
		var monsterInTile = getMonsterAt([i, j]);
		if (monsterInTile == null)
		    console.error("findPathTo: null monsterInTile", [i, j]);

		if ((family != null) && (monsterInTile.family == family)) {
		    board[i][j] = 0;
		}
		else
		    board[i][j] = 1;

	    }	
	}
    }
    var path = a_star(p1, p2, board, globals.TILE_AMOUNT, globals.TILE_AMOUNT, true);

    return path;
}

var getRectFromRadius = function(pos, radius) {
    var x0 = pos[0]-radius, y0 = pos[1]-radius;
    var x1 = pos[0]+radius, y1 = pos[1]+radius;

    x0 = Math.min(x0, globals.TILE_AMOUNT-1); y0 = Math.min(y0, globals.TILE_AMOUNT-1);
    x0 = Math.max(x0, 0); y0 = Math.max(y0, 0);
    x1 = Math.min(x1, globals.TILE_AMOUNT-1); y1 = Math.min(y1, globals.TILE_AMOUNT-1);
    x1 = Math.max(x1, 0); y1 = Math.max(y1, 0);

    return [x0,y0,x1,y1];
}

/* findFreeTile gets rect with four points as argument */
var findFreeTile = function(rect) {
    if ((!rect instanceof Array) || (rect.length < 4)) {
	console.error("Invalid parameter at findFreeTile!");
	return null;
    }

    var allPoints = [];
    var found = false, foundPoint = [];
    var x0 = Math.min(rect[0],rect[2]);
    var y0 = Math.min(rect[1],rect[3]);
    var x1 = Math.max(rect[0],rect[2]);
    var y1 = Math.max(rect[1],rect[3]);

    console.log("Looking free tile:",[x0,y0], [x1,y1]);
    for (var x = x0; x <= x1; x++) {
	for (var y = y0; y <= y1; y++) {
	    allPoints.push([x,y]);
	}
    }

    while (!found) {
	var i = Math.floor(allPoints.length * Math.random());
	if ((isTileEmpty(allPoints[i])) && (!isTileOccupied(allPoints[i]))) {
	    found = true;
	    foundPoint = allPoints[i];
	}
	else
	    allPoints.splice(i,1);

	if (allPoints.length == 0)
	    found = true;
    }

    if (!found)
	return [];
    else
	return foundPoint;
}

exports.findNewLocation = function(arr) {
    var found = false;
    var radius = 1;
    var newLocation = null;

    while (!found) {
	var rect = getRectFromRadius(arr, radius);
	newLocation = findFreeTile(rect);

	if ((newLocation.length > 0) || (radius > 10))
	    found = true;
	else
	    radius++;
    }

    console.log("radius",radius,"newlocation",newLocation);
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
	this.battleStatus.add(m1.name + " shoots " + m2.name + " for " + m1Damage + " damage!");
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

var findSpecificMonster = function(monster, want_friend, want_weakest) {
    if(typeof(want_friend)==='undefined') want_friend = false;
    if(typeof(want_weakest)==='undefined') want_weakest = false;

    var foundList = [];
    var key = 100000;

    this.isSmaller = function(other) {
	if (want_weakest)
	    return (other.hp < key);
	else
	    return (getDistance(monster.position, other.position, monster.family) < key);
    }

    this.isEqual = function(other) {
	if (want_weakest)
	    return (other.hp == key);
	else
	    return (getDistance(monster.position, other.position, monster.family) == key);
    }

    this.isSuitableFamily = function(other) {
	if (want_friend)
	    return (monster.family === other.family);
	else
	    return (monster.family !== other.family);
    }

    this.setKey = function(other) {
	if (want_weakest) 
	    return other.hp;
	else
	    return getDistance(monster.position, other.position, monster.family);
    }

    globals.Monsters.forEach(function(other) {
	if (other.id != null) {
	    if (this.isSuitableFamily(other)) {
		if (this.isSmaller(other)) {
		    foundList = [];
		    foundList.push(other.position);
		    key = this.setKey(other);
		}
		else if (this.isEqual(other)) {
		    foundList.push(other.position);
		}
	    }
	}
    });

    var found = null;
    if (foundList.length > 0)
	found = randomFromList(foundList);

    return found;
}

var findNearestEnemyRanged = function(monster) { 
    var foundList = [];
    var key = 1000;

    globals.Monsters.forEach(function(other) {
	if (monster.id != other.id) {
	    var dist = getRangedDistance(monster.position, other.position);
	    /* we find either closest or weakest */
	    /* check if it's enemy/friend we wanted */
	    if (monster.family != other.family) {
		if (dist < key) { 
		    key = getRangedDistance(monster.position, other.position);
		    foundList = [];
		    foundList.push(other.position);
		}
		else if (dist == key)
		    foundList.push(other.position);
	    }
	}

    });

    var found = null;
    if (foundList.length > 0)
	found = randomFromList(foundList);

    console.log(found);

    return found;
}


var findNearestEnemy = function(monster) {
    return findSpecificMonster(monster, false, false);
}

var findNearestFriend = function(monster) {
    return findSpecificMonster(monster, true, false);
}

var findWeakestFriend = function(monster) {
    return findSpecificMonster(monster, true, true);
}

exports.doAI = function(monster) {
    console.log("AI:",monster.name,monster.position,monster.family);
    var nearestEnemyPosition;
    if (monster.weapon === globals.WeaponStyle.MELEE)
       nearestEnemyPosition = findNearestEnemy(monster);
    else
       nearestEnemyPosition = findNearestEnemyRanged(monster);

    var Action = { ATTACK : 0, GATHER_AROUND : 1, DEFEND_WEAK : 3,
	CAST_SPELL : 4, DO_NOTHING : 99};

    if (nearestEnemyPosition) {
	console.log("Nearest enemy:",nearestEnemyPosition,getDistance(monster.position, nearestEnemyPosition, monster.family));

	/* by default, we attack with our hands and claws. */
	var action = Action.ATTACK;
	var distance = getDistance(monster.position, nearestEnemyPosition, monster.family);
	var nearestEnemy = getMonsterAt(nearestEnemyPosition);

	if (nearestEnemy == null) {
	    console.error("nearestEnemy = null!");
	    monster.skipTurn();
	    return;
	}

	/*
	 *
	 * Decide best action
	 *
	 */

	var fate = Math.random();

	if (distance == 1) {
	    action = Action.ATTACK;
	}
	else if (monster.personality === globals.MonsterPersonality.IMMOBILE) {
	    if (monster.weapon === globals.WeaponStyle.MELEE)
		action = Action.DO_NOTHING;
	    else if (monster.weapon === globals.WeaponStyle.RANGED)
		action = Action.ATTACK;
	    else if (monster.weapon === globals.WeaponStyle.MAGIC) {
		action = Action.CAST_SPELL;
	    }
	}
	else if (monster.personality === globals.MonsterPersonality.CAREFUL) {
	    if (monster.weapon === globals.WeaponStyle.MELEE) {
		action = (distance > monster.moveRange)? Action.GATHER_AROUND : Action.ATTACK;
	    }
	    else if (monster.weapon === globals.WeaponStyle.MAGIC) {
		action = Action.CAST_SPELL;
	    }
	    else {
		action = Action.ATTACK;
	    }
	}
	else if (monster.personality === globals.MonsterPersonality.INDIVIDUAL) {
	    if (monster.weapon === globals.WeaponStyle.MAGIC) {
		action = Action.CAST_SPELL;
	    }
	    else {
		if (fate < 0.8)
		    action = Action.ATTACK;
		else 
		    action = Action.DEFEND_WEAK;
	    }
	}
	else if (monster.personality === globals.MonsterPersonality.BERSERK) {
	    if ((monster.weapon === globals.WeaponStyle.MAGIC) && (fate < 0.5)) {
		action = Action.CAST_SPELL;
	    }
	    else {
		action = Action.ATTACK;
	    }
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
	    else if (monster.weapon === globals.WeaponStyle.RANGED)
		monster.attackRanged(nearestEnemy);
	    else {
		// TODO: implement spells
		// for now, we just attack
		monster.attackRanged(nearestEnemy);
	    }
	}
	else if (action === Action.GATHER_AROUND) {
	    var nearestFriendPosition = findNearestFriend(monster);
	    var friendDistance = getDistance(monster.position, nearestFriendPosition, monster.family);

	    /* if we are close to a friend and have a bow, we'll just shoot */
	    if ((friendDistance <= 2) && (monster.weapon === globals.WeaponStyle.RANGED))
		monster.attackRanged(nearestEnemy);
	    else
		monster.moveTo(nearestFriendPosition);
	}
	else if (action === Action.DEFEND_WEAK) {
	    console.log("Action: DEFEND_WEAK");
	    monster.skipTurn();
	}
	else if (action === Action.CAST_SPELL) {
	    // TODO: implement spells
	    // for now, we just attack
	    monster.attackRanged(nearestEnemy);
	}
	else
	    monster.skipTurn();
    }
    else {
	console.warn("Couldn't find nearest enemy!");
	monster.skipTurn();
    }
}
