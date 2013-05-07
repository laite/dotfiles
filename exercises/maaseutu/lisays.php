<?php
/* Luodaan tietokantaan taulu, jollei siellä sellaista vielä ole */

// käytetään wordpressin omaa db-muuttujaa
global $wpdb;

// taulukon nimi
$taulukko = "aanestys";

// taulukon luontikomento SQL-kielellä
$sql = "CREATE TABLE $taulukko (
  id mediumint(9) NOT NULL AUTO_INCREMENT,
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

$KATEGORIOIDEN_LKM = 4;

// käydään jokainen kategoria yksitellen lävitse
for ($index = 1; $index <= $KATEGORIOIDEN_LKM; ++$index)
{
    // katsotaan, onko käyttäjä antanut jotain dataa
    if (isset($_POST['nimi'.$index]))
    {
        // siirretään tieto selkeämpiin muuttujiin
        $nimi = stripslashes($_POST['nimi'.$index]);

        // TODO: tsekkaa mitä tapahtuu jos paikkakunta/perustelut on tyhjä
        $paikkakunta = stripslashes($_POST['paikkakunta'.$index]);
        $perustelut = stripslashes($_POST['perustelut'.$index]);

        // napataan kellonaika talteen
	$kellonaika = date("Y-m-d H:i:s");

        // kategorian nimi haetaan indeksin perusteella taulukosta
        $kaikki_kategoriat = array ( 1 => 'ensimmäinen', 2 => 'toinen', 3 => 'kolmas', 4 => 'neljäs' );
        $kategoria = $kaikki_kategoriat[$index];

        // tallennetaan tieto riviksi, indeksit vastaavat taulukon sarakkeita
        // (taulun ID tulee automaattisesti auto_increment - attribuutista johtuen)
        $rivi = array ( 'aika' => $kellonaika, 'kategoria' => $kategoria, 'nimi' => $nimi, 'paikkakunta' => $paikkakunta, 'perustelut' => $perustelut );

        // lisätään rivi tietokantaan
        $wpdb->insert($taulukko, $rivi);
    }
}

?>
