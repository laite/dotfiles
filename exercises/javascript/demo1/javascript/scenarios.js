var war = require('war');
var globals = require('global');
var monster = require('monster');

var gamejs = require('gamejs');

exports.loadScenario = function(scenario) {

    /* Ground */

    globals.GroundTiles = new gamejs.sprite.Group();

    /* All scenarios have randomized ground for now */
    for (var y=0; y<globals.TILE_AMOUNT; y++) {
	for (var x=0; x<globals.TILE_AMOUNT; x++) {
	    // there's a 15% chance that tile is lava */
	    var blocked = (Math.random() > 0.15)? globals.TileState.EMPTY : globals.TileState.BLOCKED;
	    globals.GroundTiles.add(new war.Ground([x*globals.TILE_SIZE, y*globals.TILE_SIZE], blocked));
	}
    }

    /* Monsters */
    globals.Monsters = new gamejs.sprite.Group();

    /* Make sure that families get spawned correctly */
    globals.familyList = [];

    /* Clear possible effect/attack animations */
    globals.attackOn = false;
    globals.effectOn = false;

    /* 
     * Scenario 1: 
     *
     * Orcs (human controlled)
     * Octopi (AI)
     *
     */
    if (scenario == 1) {
	/* 8 orcs */
	for (var i=0; i < 8; i++) {
	    var monsterType = Math.random()*10;
	    if (monsterType < 7)
		globals.Monsters.add(new monster.Orc(globals.Controller.HUMAN, "Human"));
	    else
		globals.Monsters.add(new monster.ToughOrc(globals.Controller.HUMAN, "Human"));
	}
	/* 8 octo-monsters */
	for (var i=0; i < 8; i++) {
	    globals.Monsters.add(new monster.Octopus(globals.Controller.AI));
	}

    }

    /* 
     * Scenario 2: 
     *
     * 5 Orcs (human)
     * 5 octopi (human)
     * 1 Evileye (AI)
     *
     */
    else if (scenario == 2) {
	/* 5 orcs */
	for (var i=0; i < 5; i++) {
	    var monsterType = Math.random()*10;
	    if (monsterType < 7)
		globals.Monsters.add(new monster.Orc(globals.Controller.HUMAN, "Human"));
	    else
		globals.Monsters.add(new monster.ToughOrc(globals.Controller.HUMAN, "Human"));
	}
	/* 5 octo-monsters */
	for (var i=0; i < 5; i++) {
	    globals.Monsters.add(new monster.Octopus(globals.Controller.HUMAN, "Human"));
	}

	globals.Monsters.add(new monster.Evileye(globals.Controller.AI));
    }

    /* 
     * Scenario 3: 
     *
     * Default factions
     *
     * Random amounts:
     * 25% orcs
     * 25% tough orcs
     * 45% octopus
     * 5% evil eye
     *
     */

    else {
	for (var i=0; i < (20); i++)
	{
	    var monsterType = Math.random()*20;
	    if (monsterType < 5)
		globals.Monsters.add(new monster.Orc(globals.Controller.AI));
	    else if (monsterType < 10)
		globals.Monsters.add(new monster.ToughOrc(globals.Controller.AI));
	    else if (monsterType < 19)
		globals.Monsters.add(new monster.Octopus(globals.Controller.AI));
	    else
		globals.Monsters.add(new monster.Evileye(globals.Controller.AI));
	}

    }


    /* attackIcon */
    globals.attackIcon = new war.AttackIcon([0,0]);

}
