<?php

// käytetään wordpressin omaa db-muuttujaa
global $wpdb;

// taulukon nimi
$taulukko = "aanestys";

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
	$koko_runko = "";
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

		// lisätään rivi myös $koko_runko-muuttujaan mahdollista postitusta varten
		$koko_runko .= "Nimi: ".$nimi."\nPaikkakunta: ".$paikkakunta."\nPerustelut: ".$perustelut."\nÄänestäjän nimi:".$lahettaja."\n\n\n";
	}
	// lopuksi katkaistaan taulukko
        echo "</table>";

	// annetaan käyttäjälle mahdollisuus lähettää tiedot sähköpostilla
	?>
		<form method="post" action="postitus.php">
			<input name="posti_runko" type="hidden" value="<?php echo $koko_runko ?>" />
			<input type="submit" value="Lähetä sähköpostiin" />
		</form>
	<?php
	
}

?>
