<?php

// käytetään wordpressin omaa db-muuttujaa
global $wpdb;

// taulukon nimi
$taulukko = "aanestys";

/* Luetaan taulukossa oleva data muuttujaan */

// haetaan tulokset sql-kyselyllä
$tulokset = $wpdb->get_results( 
	"
	SELECT kategoria,nimi,paikkakunta,perustelut FROM $taulukko
        ORDER BY kategoria
	"
);

if ( $tulokset )
{
	echo "<table><tr><td>Kategoria</td><td>Nimi</td><td>Paikkakunta</td><td>Perustelut</td></tr>";
	foreach ( $tulokset as $rivi )
	{
		echo "<tr><td>".$rivi->kategoria."</td><td>".$rivi->nimi."</td><td>".$rivi->paikkakunta."</td><td>".$rivi->perustelut."</td></tr>";
	}
        echo "</table>";
}

?>
