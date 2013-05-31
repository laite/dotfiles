<?php

// hakusana kulkee pt_kaytto.js:n kautta
$value = $_GET['hakusana'];

$db = mysqli_connect("localhost","laite","goblinsPHP", "laite") or die ("Yhteyttä kantaan ei saatu"); 

//valitaan sellaisten arvojen sisältö, joiden otsikkoihin hakusana täsmää
$query = "SELECT Sisalto FROM h5t3 where Otsikko LIKE '%$value%'";
$result = mysqli_query($db, $query);

// tarkastetaan tulokset
if (mysqli_num_rows($result) == 0) {
	$msg = "Ei sivuja halutulla hakusanalla!";
} 
else {
    $row = mysqli_fetch_row($result);

	// valitsemme aina vain ensimmäisen hakutuloksen
	$msg = $row[0];
}

// tulostetaan tulos ruudulle (ajax huolehtii siitä, että se menee oikeaan paikkaan)
echo $msg; 
?>
