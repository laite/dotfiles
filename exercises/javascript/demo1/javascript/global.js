/*
 * global.js
 *
 */

exports.Monsters;
exports.attackIcon;

exports.TILE_SIZE = 64;
exports.TILE_AMOUNT = 10;

exports.CANVAS_HEIGHT = 640;
exports.CANVAS_WIDTH = 640;
exports.GAME_AREA_HEIGHT = 640;
exports.GAME_AREA_WIDTH = 640;

exports.AMOUNT_OF_MONSTERS = 3;
exports.ATTACK_ICON_DURATION = 500;
exports.RANGED_ATTACK_ICON_DURATION = 750;
exports.MAGIC_ATTACK_ICON_DURATION = 1000;

exports.LOG_LINES = 10;

/* 
 * "Enumerators"
 *
 * These are not consts, so tread carefully when using!
 *
 */

exports.MonsterState = {
    INACTIVE : 0,
    ACTIVE : 1,
    MOVING : 2,
	ATTACKING : 3,
	MOVING_AFTER_ATTACK : 4
};

exports.TileState = {
	EMPTY : 0,
	OCCUPIED : 1,
	BLOCKED : 2
};

exports.CursorState = {
	ALLOWED : 0,
	DISALLOWED : 1,
	ATTACK : 2,
	ACTIVE_MONSTER : 3
};

/* controllers */
exports.Controller = {
	HUMAN : 0,
	AI : 1
};

/*
 * Monster personalities and tactical preferences
 */

/* MonsterSpeed acts as a modifier when calculating individual monsters speed and moveRate */
exports.MonsterSpeed = {
	VERY_SLOW : 0,
	SLOW : 1,
	NORMAL : 2,
	QUICK : 3,
	VERY_QUICK : 4
}

/* Personality defines monsters actions on battlefield */
exports.MonsterPersonality = {
	IMMOBILE : 0,
	CAREFUL : 1,
	INDIVIDUAL : 2,
	BERSERK : 3
}

exports.MonsterEndurance = {
	VERY_WEAK : 0,
	WEAK : 1,
	NORMAL : 3,
	TOUGH : 5,
	VERY_TOUGH : 8,
	EXTREMELY_TOUGH : 12,
	GODLIKE : 20
}

exports.WeaponStyle = {
	MELEE : 0,
	RANGED : 1,
	MAGIC : 2
}
