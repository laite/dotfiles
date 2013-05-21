<?php

// jos ei posti-osoitetta, palataan etusivulle
if (isset($_POST['sposti_osoite']))
{
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
		date_default_timezone_set("Europe/Helsinki");
		$kellonaika = date("Y-m-d H:i:s");
		$koko_runko = "Äänestys-tulokset ".$kellonaika."\n\n";

		foreach ( $tulokset as $rivi )
		{
			$nimi = $rivi->nimi;
			$lahettaja = $rivi->lahettaja;
			$kategoria = $rivi->kategoria;
			$paikkakunta = $rivi->paikkakunta;
			$perustelut = $rivi->perustelut;

			// kirjoitetaan kategorian vaihtuessa sen otsikko
			if (($edellinen_kategoria == "") || ($edellinen_kategoria != $kategoria))
				$koko_runko .= "\n\n*** $kategoria ***\n\n";
			
			$edellinen_kategoria = $kategoria;

			$koko_runko .= "Nimi: ".$nimi."\nPaikkakunta: ".$paikkakunta."\nPerustelut: ".$perustelut."\nÄänestäjän nimi:".$lahettaja."\n\n\n";
		}

		$to = $_POST['sposti_osoite'];
		$subject = "Äänestys-tulokset";
		$from = "aanestys@ksmaaseutugaala.fi";
		$headers = "From:".$from;

		// lopuksi lähetetään posti
		mail($to,$subject,$koko_runko,$headers);	

		echo "<h2>Sähköposti lähetetty!</h2>";
	}
	else
		echo "<h2>Ei vielä yhtään äänestystulosta, sähköpostia ei lähetetty!</h2>";
}
else
	echo "<h2>Ei sähköpostiosoitetta! Käytä raportti-sivun alalaidassa olevaa 'lähetä'-nappia.</h2>";
?>
<a href="http://www.ksmaaseutugaala.fi" alt="etusivu">Palaa etusivulle</a> <a href="http://www.ksmaaseutugaala.fi/?page_id=545" alt="raportti">Palaa raportti-sivulle</a>

