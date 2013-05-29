<?php

//mysqli_connect() -funktiolla otetaan yhteys tietokantapalvelimeen
//Oletustunnareilla: mysqli_connect("localhost","root","")  
$connection = mysqli_connect("localhost","laite","goblinsPHP")
or die("Yhdistäminen ei onnistunut" . mysqli_error($connection));

//Jos yhdistäminen onnistui, kerrotaan se käyttäjälle
if(isset($connection))
{
	echo "Yhteys MySQL-tietokantapalvelimeen toimii!";
}

//Lopuksi suljetaan yhteys
mysqli_close($connection);
?>
