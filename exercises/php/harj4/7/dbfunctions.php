<?php
/*
  dbfunctions.php sisältää muutaman itse tehdyn funktion tietokannan käsittelyyn.
  Niitä voi tehdä tänne lisää.
 */

function connect() {
    $username = "laite";
    $password = "goblinsPHP";
    $host = "localhost";
    $database = "laite";

	try
	{
		$yhteys = new PDO("mysql:host=$host;dbname=$database", "$username", "$password");
	}
	catch (PDOException $e)
	{
		die("VIRHE: ".$e->getMessage());
	}

	// virheen sattuessa poikkeus
	$yhteys->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
	// käytetään utf-8:a mieluummin kuin putkan ehdottamaa latinia
	$yhteys->exec("SET NAMES utf8");

    return $yhteys;
}

function close($yhteys) {
	// suljetaan yhteys PDO-objektiin nollaamalla sen esiintymä
	$yhteys = null;
}

/* lisaa_ostokset on hardcodattu funktio, joka lisää lomakkeelta saavat tiedot ennalta luotuun
 * taulukkoon */

function lisaa_ostokset($yhteys, $sessio_id) 
{
	// varsinaiset ostokset sijaitsevat sessiomuuttujassa
	// start_session pitää tietysti kutsua ennen kuin kutsutaan lisaa_ostokset()-funktiota
	if (!isset($_SESSION['ostoskori']))
	{
		print "VIRHE: ostoskoria ei löydy!";
		die();
	}

	/* tallennetaan ensin asiakas - taulun tiedot */
	$table = 'asiakas';

	// toisin kuin perinteisemmän tavan kanssa, PDO:n kanssa ei tarvitse käyttää
	// addslashes():ia
    $nimi = $_POST['nimi'];
    $email = $_POST['email'];
    $address = $_POST['osoite'];

    $sql = "INSERT INTO $table SET id='$sessio_id', nimi='$nimi', email='$email', osoite='$address'";

	$result = $yhteys->prepare($sql);
	$result->execute();

	/* ja sen jälkeen ostokset php:n serialize-toimintoa hyväksi käyttäen */
	$table = 'ostokset';
	$ostokset = serialize($_SESSION['ostoskori']);

	$sql = "INSERT INTO $table SET ostoslista='$ostokset', sessionid='$sessio_id'";

	$result = $yhteys->prepare($sql);
	$result->execute();
}
?>
