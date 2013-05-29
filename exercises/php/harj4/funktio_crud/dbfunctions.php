<?php
/*
  dbfunctions.php sisältää muutaman itse tehdyn funktion tietokannan käsittelyyn.
  Niitä voi tehdä tänne lisää.
 */

function connect() {

    $username = "tunnus";
    $password = "salasana";
    $host = "localhost";
    $database = "kanta";

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
    $sql = "select * from $table order by id";
    $result = mysqli_query($yhteys, $sql);
    print "<html><body>";
    print "<table border='1' cellspacing='1' cellpadding='2'>";

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
        print "<td>[<a href='update.php?id=$id'>Muokkaa</a>
  |<a href='delete.php?id=$id'>Poista</a>]</td>";
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
?>