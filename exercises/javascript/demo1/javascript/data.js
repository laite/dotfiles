
exports.Monster = function(rect) {

	// call superconstructor
	Monster.superConstructor.apply(this, arguments);
	this.speed = 80 + (40 * Math.random());

	this.image = gamejs.image.load("images/monster.png");

	// rect shows the position of monster
	this.rect = new gamejs.Rect(rect, [TILE_SIZE, TILE_SIZE]);

	return this;
};
