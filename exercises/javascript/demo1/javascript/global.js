/*
 * global.js
 *
 */

exports.TILE_SIZE = 64;
exports.TILE_AMOUNT = 10;

exports.CANVAS_HEIGHT = 640;
exports.CANVAS_WIDTH = 640;

exports.AMOUNT_OF_MONSTERS = 10;

/* enums */
exports.MonsterState = {
    INACTIVE : 0,
    ACTIVE : 1,
    MOVING : 2
};

exports.TileState = {
	EMPTY : 0,
	OCCUPIED : 1,
	BLOCKED : 2
};

exports.CursorState = {
	ALLOWED : 0,
	DISALLOWED : 1,
	ATTACK : 2
};

/* controllers */
exports.Controller = {
	HUMAN : 0,
	AI : 1
};

