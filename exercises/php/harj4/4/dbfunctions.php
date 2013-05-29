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

//mysqli_connect -funktiolla otetaan yhteys tietokantapalvelimeen.

    $yhteys = mysqli_connect($host, $username, $password) or die("Yhteyttä tietokantapalvelimeen 
	ei voida muodostaa<br>" . mysqli_error($yhteys));

//mysqli_select_db -funktiolla otetaan yhteys haluttuun tietokantaan.

    mysqli_select_db($yhteys, $database) or die("Tietokannan valinta epäonnistui<br>"
                    . mysqli_error($yhteys));

    return $yhteys;
}

function close($yhteys) {
    mysqli_close($yhteys);
}

/* list_table() näyttää kaikki tiedot taulusta $table
  Se on hyvin uudelleenkäytettävä funktio. Voi
  käyttää suoraan erilaisten taulujen kanssa koska
  laskee taulun sarakkeiden määrän. */

function list_table($table, $yhteys) {

    //valitaan kaikki data taulusta
    $sql = "select * from $table order by ID";
    $result = mysqli_query($yhteys, $sql);

	print_results($result);
}

/* search_table etsii taulusta halutulla nimellä (joko etu- tai sukunimi, hardcoded) */

function search_table($table, $yhteys, $hakusana)
{
	$sql = "SELECT * FROM $table WHERE (FirstName LIKE '%$hakusana%' OR LastName LIKE '%$hakusana%')";
	$result = mysqli_query($yhteys, $sql);

	if (($result === FALSE) OR ($result->num_rows == 0))
	{
		echo "Ei tuloksia hakusanalla $hakusana!";
		return;
	}

	print_results($result);
}

/* fetch_row palauttaa halutun rivin taulukkomuodossa */

function fetch_row($table, $yhteys, $id)
{
	// haetaan tulosjoukko ID:n perusteella
	$sql = "SELECT ID,FirstName,LastName,Email,Address FROM $table WHERE (ID = $id)";
	$result = mysqli_query($yhteys, $sql);

	// jos tuloksena on mitä tahansa muuta kuin tismalleen yksi rivi, on jokin mennyt vikaan
	if (($result === FALSE) OR ($result->num_rows != 1))
	{
		echo "Ei tuloksia halutulla id:llä! ($id)!";
		return;
	}

	// tallennetaan rivin arvot taulukkoon (järjestys tulee SQL-kyselylausekkeesta)
	$rivi = mysqli_fetch_row($result);
	$tulos = array( 'id' => $rivi[0], 'fname' => $rivi[1], 'lname' => $rivi[2], 'email' => $rivi[3], 'address' => $rivi[4]);

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
    $result = mysqli_query($yhteys, $sql) or die("Tiedon lisäys tauluun ei onnistu.<br>" . mysqli_error());
    header('Location: read.php');
}

/* print_results huolehtii tulosten näyttämisestä taulukkomuodossa (ottaa attribuuttina mysql-resultin) */

function print_results($result)
{
    print "<html><body>";
    print "<table border='1' cellspacing='5' cellpadding='5'>";

    //poimitaan taulusta rivejä niin kauan kuin niitä on
    while ($row = mysqli_fetch_row($result)) {
        //lasketaan sarakkeiden määrä
        $total_cols = count($row);
        $i = 0;
        print "<tr>";
        //tehdään sarakkeita niin monta kuin niitä on
        while ($i < $total_cols) {
            print "<td>";
            //tulostetaan sisältö sarakkeisiin
            print $row[$i];
            print "</td>";
            //otetaan tietueen id talteen
            $id = $row[0];
            $i++;
        }
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

    /* Lisätään tiedot kantaan suorittamalla sql-lause 
      mysqli_query()-funktion avulla. Koska kyseessä insert-lause,
      $result -muuttujaan ei tule tässä tapauksessa tulosdataa vaan
      tieto siitä onnistuiko lauseen suoritus. Tässä sitä tietoa ei
      käytetä mihinkään. */

    $result = mysqli_query($yhteys, $sql) or die("Tiedon lisäys tauluun ei onnistu.<br>"
                    . mysqli_error());
    header('Location: read.php');
}

/* delete_row poistaa tietueen taulusta */

function delete_row($table, $yhteys, $poistettava_id)
{
    $sql = "DELETE FROM $table WHERE ID = $poistettava_id";
    $result = mysqli_query($yhteys, $sql);
}
?>
