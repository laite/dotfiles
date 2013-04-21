<html>
<head>
<title>tallennasivu</title>
<meta charset="utf-8">
</head>
<body>

<?php 

$tiedosto="sivu.txt";

//avataan tiedosto kirjoittamista varten

$d=fopen($tiedosto,"w"); 

//lisätään tiedostoon muokaustilan textareasta saatu tieto jonka name="muokattu"
//stripslashes -funktio poistaa kenoviivat(\) jotka php muuten tulostaa
//heittomerkkien yms. syntaksiin kuuluien merkkien eteen.

fputs($d,stripslashes($_POST['muokattu'])); 
fclose($d);  

//siirrytään suoraan näyttämään tallennettu sivu

echo"<meta http-equiv=refresh content='0; url=6naytasivu.php'>";
?>
</body>
</html>
