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

    $yhteys = mysqli_connect($host, $username, $password) or die("Yhteyttä tietokantapalvelimeen 
	ei voida muodostaa<br>" . mysqli_error($yhteys));

    mysqli_select_db($yhteys, $database) or die("Tietokannan valinta epäonnistui<br>"
                    . mysqli_error($yhteys));

    return $yhteys;
}

function close($yhteys) {
    mysqli_close($yhteys);
}

function add_row($yhteys, $taulu, $id, $nimi, $osoite, $maksettu) {
	$query = "INSERT INTO $taulu SET Maksu_id='$id', Nimi='$nimi', Osoite='$osoite', Maksettu=$maksettu";

	$result = mysqli_query($yhteys, $query) or die("Tiedon lisäys tauluun ei onnistu.<br>" . mysqli_error());

}

function fetch($yhteys, $taulu, $maksu_id) {
	$query = "SELECT * FROM $table WHERE (Maksu_id = $maksu_id)";

	$result = mysqli_query($yhteys, $query);

	return $result;
}
?>
