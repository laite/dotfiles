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
var scene = require('scene');

var gamejs = require('gamejs');



/*
 *
 * Main function 
 *
 */


function main() {


    /* Initial screen setup */
    gamejs.display.setMode([globals.CANVAS_WIDTH, globals.CANVAS_HEIGHT]);
    gamejs.display.setCaption("Here be monsters");

    var mainSurface = gamejs.display.getSurface();

    /*
     * Create the director and the scenes 
     */

    globals.director = new scene.Director();
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

    globals.director.start(globals.menuScene);
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
