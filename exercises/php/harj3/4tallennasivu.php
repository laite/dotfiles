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

	// jos k�ytt�j� ei ole kirjautunut sessioon, lakataan sivun suorittaminen t�h�n
	exit();
}

$tiedosto="sivu.txt";

//avataan tiedosto kirjoittamista varten

$d=fopen($tiedosto,"w"); 

//lis�t��n tiedostoon muokaustilan textareasta saatu tieto jonka name="muokattu"
//stripslashes -funktio poistaa kenoviivat(\) jotka php muuten tulostaa
//heittomerkkien yms. syntaksiin kuuluien merkkien eteen.

fputs($d,stripslashes($_POST['muokattu'])); 
fclose($d);  

//siirryt��n suoraan n�ytt�m��n tallennettu sivu

echo"<meta http-equiv=refresh content='0; url=4naytasivu.php'>";
?>
</body>
</html>
