<?php

// käytetään wordpressin omaa db-muuttujaa
global $wpdb;

// taulukon nimi
$taulukko = "aanestys_2013";

/* Luetaan taulukossa oleva data muuttujaan */

// haetaan tulokset sql-kyselyllä
$tulokset = $wpdb->get_results( 
	"
	SELECT id,lahettaja,kategoria,nimi,paikkakunta,perustelut FROM $taulukko
        ORDER BY kategoria,id
	"
);

// jos kysely tuottaa tuloksia, piirretään ne ruudulle
if ($tulokset)
{
	$edellinen_kategoria = "";
	foreach ( $tulokset as $rivi )
	{
		$nimi = $rivi->nimi;
		$lahettaja = $rivi->lahettaja;
		$kategoria = $rivi->kategoria;
		$paikkakunta = $rivi->paikkakunta;
		$perustelut = $rivi->perustelut;

		// kirjoitetaan ensimmäinen otsikko
		if ($edellinen_kategoria == "")
		{
			echo "<h2>$kategoria</h2>";
			echo "<table><tr><td>Nimi</td><td>Paikkakunta</td><td>Perustelut</td></tr>";
		}
		// kategorian vaihtuessa katkaistaan taulukko ja kirjoitetaan uusi
		else if ($edellinen_kategoria != $kategoria)
		{
			echo "</table>";
			echo "<h2>$kategoria</h2>";
			echo "<table><tr><td>Nimi</td><td>Paikkakunta</td><td>Perustelut</td></tr>";
		}
		
		$edellinen_kategoria = $kategoria;
		echo "<tr><td>".$nimi."</td><td>".$paikkakunta."</td><td>".$perustelut."</td></tr>";
	}
	// lopuksi katkaistaan taulukko
        echo "</table>";
}
else
	echo "<h2>Ei vielä yhtään äänestystulosta</h2>";
?>
<form method="post" action="http://www.ksmaaseutugaala.fi/?page_id=566">
  Lähetä tiedot sähköpostiosoitteeseen: <input name="sposti_osoite" required /><input type="submit" value="Lähetä" />
</form>
