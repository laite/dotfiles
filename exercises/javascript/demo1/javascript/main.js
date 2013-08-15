/*
 *
 * DEMO 1
 *
 * Game area
 *
 */

/*
 * Requires
 */

var globals = require('global');

var gamejs = require('gamejs');
var draw = require('gamejs/draw');
var $v = require('gamejs/utils/vectors');

var war = require('war');
var monster = require('monster');
var scene = require('scene');


/*
 *
 * Main function 
 *
 */


function main() {


    /*
     * Initial screen setup
     */


    gamejs.display.setMode([globals.CANVAS_WIDTH, globals.CANVAS_HEIGHT]);
    gamejs.display.setCaption("Example Monsters");

    var mainSurface = gamejs.display.getSurface();

    /*
     * Sprites
     */

    /* Ground */

    globals.GroundTiles = new gamejs.sprite.Group();

    for (var y=0; y<globals.TILE_AMOUNT; y++) {
	for (var x=0; x<globals.TILE_AMOUNT; x++) {
	    // there's a 25% chance that tile is lava */
	    var blocked = (Math.random() > 0.25)? globals.TileState.EMPTY : globals.TileState.BLOCKED;
	    globals.GroundTiles.add(new war.Ground([x*globals.TILE_SIZE, y*globals.TILE_SIZE], blocked));
	}
    }

    /* Monsters */

    globals.Monsters = new gamejs.sprite.Group();

    for (var i=0; i < (16); i++)
    {
	var monsterType = Math.random()*20;
	if (monsterType < 15)
	    globals.Monsters.add(new monster.Orc());
	else if (monsterType < 10)
	    globals.Monsters.add(new monster.ToughOrc());
	else if (monsterType < 19)
	    globals.Monsters.add(new monster.Octopus());
	else
	    globals.Monsters.add(new monster.Evileye());
    }

    globals.attackIcon = new war.AttackIcon([0,0]);


    /*
     * Engine initializations
     */


    war.init();
    war.battleStatus.add(war.name());



    /*
     *
     *
     *
     *
     *
     * Director
     *
     *
     *
     *
     */


    var Director = function() {
	var onAir = false;
	var activeScene = null;

	this.update = function(msDuration) {
	    if (!onAir) return;

	    if (activeScene.update) {
		activeScene.update(msDuration);
	    }
	}

	this.draw = function(display) {
	    if (activeScene.draw) {
		activeScene.draw(display);
	    }
	};

	this.handleEvent = function(event) {
	    if (activeScene.handleEvent) {
		activeScene.handleEvent(event);
	    }
	}


	this.start = function(scene) {
	    onAir = true;
	    this.replaceScene(scene);
	    return;
	};

	this.replaceScene = function(scene) {

	    if ((activeScene != null) && (activeScene.exit)) {
		activeScene.exit();
	    }

	    activeScene = scene;

	    if (activeScene.init) {
		activeScene.init();
	    }
	};

	this.getScene = function() {
	    return activeScene;
	};
	return this;
    }

    /*
     * Create the director and the scenes 
     */

    globals.director = new Director();
    globals.warScene = new scene.WarScene(globals.director, mainSurface);
    globals.endStatisticsScene = new scene.EndStatisticsScene(globals.director);
    globals.menuScene = new scene.MenuScene(globals.director);

    /*
     * Apply gamejs events to director
     */

    gamejs.onEvent(function(event) {
	globals.director.handleEvent(event);
    });


    /* msDuration = time since last tick() call */
    gamejs.onTick(function(msDuration) {
	globals.director.update(msDuration);
    });


    /*
     * Start the game
     */

    globals.director.start(globals.warScene);
}


/*
 * Preloads
 */


gamejs.preload(['images/tough_orc.png']);
gamejs.preload(['images/evileye.png']);
gamejs.preload(['images/orc.png']);
gamejs.preload(['images/octopus.png']);
gamejs.preload(['images/tile.png']);
gamejs.preload(['images/tile2.png']);
gamejs.preload(['images/attack.png']);
gamejs.preload(['images/attack_ranged.png']);
gamejs.preload(['images/attack_magic.png']);

/* Go! */
gamejs.ready(main);
