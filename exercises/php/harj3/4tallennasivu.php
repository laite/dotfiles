<html>
<head>
<title>tallennasivu</title>
<meta charset="utf-8">
</head>
<body>

<?php 

session_start();

if ($_SESSION['login_ok'] != 1)
{
	echo "Error: You must log in first!";

	// jos käyttäjä ei ole kirjautunut sessioon, lakataan sivun suorittaminen tähän
	exit();
}

$tiedosto="sivu.txt";

//avataan tiedosto kirjoittamista varten

$d=fopen($tiedosto,"w"); 

//lisätään tiedostoon muokaustilan textareasta saatu tieto jonka name="muokattu"
//stripslashes -funktio poistaa kenoviivat(\) jotka php muuten tulostaa
//heittomerkkien yms. syntaksiin kuuluien merkkien eteen.

fputs($d,stripslashes($_POST['muokattu'])); 
fclose($d);  

//siirrytään suoraan näyttämään tallennettu sivu

echo"<meta http-equiv=refresh content='0; url=4naytasivu.php'>";
?>
</body>
</html>
