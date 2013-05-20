<?php
/* Luodaan tietokantaan taulu, jollei siellä sellaista vielä ole */

// käytetään wordpressin omaa db-muuttujaa
global $wpdb;

// taulukon nimi
$taulukko = "aanestys";

// taulukon luontikomento SQL-kielellä
$sql = "CREATE TABLE $taulukko (
  id mediumint(9) NOT NULL AUTO_INCREMENT,
  lahettaja VARCHAR(100) NOT NULL,
  aika datetime DEFAULT '0000-00-00 00:00:00' NOT NULL,
  kategoria VARCHAR(100) NOT NULL,
  nimi VARCHAR(100) NOT NULL,
  paikkakunta VARCHAR(50) NOT NULL,
  perustelut VARCHAR(1000) NOT NULL,
  UNIQUE KEY id (id)
);";

// haetaan tarvittava funktio wordpressin omista tiedostoista
require_once( ABSPATH . 'wp-admin/includes/upgrade.php' );

// ajetaan sql - luontikomento
dbDelta( $sql );


/* Sitten tallennetaan saatu tieto kyseiseen taulukkoon */

$KATEGORIOIDEN_LKM = 5;

// käydään jokainen kategoria yksitellen lävitse
for ($index = 1; $index <= $KATEGORIOIDEN_LKM; ++$index)
{
    // katsotaan, onko käyttäjä antanut jotain dataa
    if (isset($_POST['nimi'.$index]) && ($_POST['nimi'.$index] != ""))
    {
        // siirretään tieto selkeämpiin muuttujiin

	// lähettäjän nimi on ainoa, joka ei käytä index-muuttujaa
	$lahettaja = stripslashes($_POST['lahettaja']);

	// äänestetyn henkilön nimi, paikkakunta sekä perustelut
        // TODO: tsekkaa mitä tapahtuu jos POST-muuttuja on tyhjä
        $nimi = stripslashes($_POST['nimi'.$index]);
        $paikkakunta = stripslashes($_POST['paikkakunta'.$index]);
        $perustelut = stripslashes($_POST['perustelut'.$index]);

        // napataan myös kellonaika talteen
	date_default_timezone_set("Europe/Helsinki");
	$kellonaika = date("Y-m-d H:i:s");

        // kategorian nimi haetaan indeksin perusteella taulukosta
	// TODO: tarkista lopulliset nimet
        $kaikki_kategoriat = array ( 
		1 => 'Innostava maaseudun kehittäjä',
		2 => 'Oivallinen maaseututeko',
		3 => 'Onnistunut ympäristöpanostus',
		4 => 'Vuoden 2013 maatalousyritys',
		5 => 'Vuoden 2013 maaseutuyritys'
	);
        $kategoria = $kaikki_kategoriat[$index];

        // tallennetaan tieto riviksi, indeksit vastaavat taulukon sarakkeita
        // (taulun ID tulee automaattisesti auto_increment - attribuutista johtuen)
        $rivi = array ( 
		'lahettaja' => $lahettaja,
		'aika' => $kellonaika,
		'kategoria' => $kategoria,
		'nimi' => $nimi,
		'paikkakunta' => $paikkakunta,
		'perustelut' => $perustelut
	);

        // lisätään rivi tietokantaan
	// insert() - funktio ottaa sisäänsä 'raakaa' tekstiä ja huolehtii syötetyn datan tietoturvasta itse
        $wpdb->insert($taulukko, $rivi);
    }
}

?>
