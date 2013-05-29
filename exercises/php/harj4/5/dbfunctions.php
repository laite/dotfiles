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

/* list_table() näyttää kaikki tiedot taulusta $table
  Se on hyvin uudelleenkäytettävä funktio. Voi
  käyttää suoraan erilaisten taulujen kanssa koska
  laskee taulun sarakkeiden määrän. */

function list_table($table, $yhteys) {

    //valitaan kaikki data taulusta
    $sql = "select * from $table order by ID";

	// tulosten saaminen PDO:lla on varsin suoraviivaista
    $result = $yhteys->prepare($sql);
	$result->execute();

	print_results($result);
}

/* search_table etsii taulusta halutulla nimellä (joko etu- tai sukunimi, hardcoded) */

function search_table($table, $yhteys, $hakusana)
{
	$sql = "SELECT * FROM $table WHERE (FirstName LIKE '%$hakusana%' OR LastName LIKE '%$hakusana%')";
	$result = $yhteys->prepare($sql);
	$result->execute();

	print_results($result);
}

/* fetch_row palauttaa halutun rivin taulukkomuodossa */

function fetch_row($table, $yhteys, $id)
{
	$sql = "SELECT ID,FirstName,LastName,Email,Address FROM $table WHERE (ID = $id)";
	$result = $yhteys->prepare("$sql");
	$result->execute();
	
	// TODO: rivien määrä pitää olla täsmälleen yksi?
	
	// tallennetaan rivin arvot taulukkoon (järjestys tulee SQL-kyselylausekkeesta)
	$rivi = $result->fetch();
	$tulos = array( 'id' => $rivi["ID"], 'fname' => $rivi["FirstName"], 'lname' => $rivi["LastName"],
	   'email' => $rivi["Email"], 'address' => $rivi["Address"]);

	// palautetaan taulukko
	return $tulos;
}

/* update_row päivittää tiedot halutulle id:lle tietokantaan */

function update_row($table, $yhteys, $uudet)
{
	// $uudet on taulukko, jossa indeksinä on muuttujan ns. lyhytnimi
	$id = $uudet['id'];
	$fname = $uudet['fname'];
	$lname = $uudet['lname'];
	$email = $uudet['email'];
	$address = $uudet['address'];

	// päivitetään uudet arvot vain halutulla ID:llä
    $sql = "UPDATE $table SET FirstName='$fname', LastName='$lname', Email='$email', Address='$address' WHERE ID=$id"; 
	$result = $yhteys->prepare($sql);
	$result->execute();

    header('Location: read.php');
}

/* print_results huolehtii tulosten näyttämisestä taulukkomuodossa */

function print_results($result)
{
    print "<html><body>";
    print "<table border='1' cellspacing='5' cellpadding='5'>";

    //poimitaan taulusta rivejä niin kauan kuin niitä on
	while ($row = $result->fetch()) 
	{
		$id = $row["ID"];
		$fname = $row["FirstName"];
		$lname = $row["LastName"];
		$email = $row["Email"];
		$address = $row["Address"];
		
        print "<tr><td>$id</td>";
        print "<td>$fname</td>";
        print "<td>$lname</td>";
        print "<td>$email</td>";
        print "<td>$address</td>";

        print "<td>[<a href='edit.php?id=$id'>Muokkaa</a> | <a href='delete.php?id=$id'>Poista</a>]</td>";
        print "</tr>";
    }
    print "</table></body></html>";

}
/* add_row_to_table() ei ole niin yleiskäyttöinen kuin
  list_table(), vaan se toimii vain osoitelista-taulun kanssa. */

function add_row_to_table($table, $yhteys) {

    $fname = addslashes($_POST['fname']);
    $lname = addslashes($_POST['lname']);
    $email = addslashes($_POST['email']);
    $address = addslashes($_POST['address']);


    $sql = "INSERT INTO $table SET FirstName='$fname', 
  LastName='$lname', Email='$email', Address='$address'";

	$result = $yhteys->prepare($sql);
	$result->execute();
    header('Location: read.php');
}

/* delete_row poistaa tietueen taulusta */

function delete_row($table, $yhteys, $poistettava_id)
{
    $sql = "DELETE FROM $table WHERE ID = $poistettava_id";
	$result = $yhteys->prepare($sql);
	$yhteys->execute();
}
?>
