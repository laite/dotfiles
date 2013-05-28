<?php

function lisaaRivi($uusirivi)
{
	// luetaan vanha data
	// (tiedosto luodaan jollei sitä vielä ole)
	$tiedosto = fopen('testi/vkirja.txt', 'c+');

	if (filesize('testi/vkirja.txt') > 0)
	{
		$vanha_data = fread($tiedosto, filesize('testi/vkirja.txt'));

		// tyhjennetään vanha sisältö
		ftruncate($tiedosto, 0);
	
		// ftruncate ei vie itsestään offsetiä alkuun (kuten olisi voinut kuvitella :/)
		rewind($tiedosto);
	}
	else
		$vanha_data = ""; // initialisointi ei ole php:ssa pakollista, mutta hyvä tapa

	// kirjoitetaan uusi data ensin, lisätään vanha data sen perään
	fwrite($tiedosto, $uusirivi);
	if ($vanha_data != "")
		fwrite($tiedosto, $vanha_data);

	// suljetaan lopuksi tiedosto
	fclose($tiedosto);
}

/*Tutkitaan tuleeko lomakkeelta skriptille sen tarvitsemat arvot.*/

if (isset($_POST['nimi']) && isset($_POST['viesti'])) {

/*sijoitetaan lomakkeelta saadut muuttujat yksinkertaisemman
näköisiin muuttujiin.*/

	$nimi=$_POST['nimi'];
	$viesti=$_POST['viesti'];

/*Luodaan muuttujaan $uusirivi uusi vieraskirjamerkintä. 
 date() -funktiolla lisätään päivämäärä. strip_tags() 
 poistaa lomakkeeseen syötetyistä tiedoista HTML- 
 ja PHP-tagit jos käyttäjä on niitä syöttänyt
(voivat häiritä vieraskirjan toimintaa).*/

	$uusirivi = '<p><b>' . date('d.m.Y H:i') . ', ' .
		strip_tags($nimi) . '</b>: ' . strip_tags($viesti) .
		'</p>';

	lisaaRivi($uusirivi);
}
?>

<html>
<body>
<h3>Viestit:</h3>

<!--vkirja.txt -tiedoston sisältö tulostetaan tähän-->

<?php include ('testi/vkirja.txt'); ?>
<hr>

<!--Tässä on lomake johon viestit kirjoitetaan. Tässä tapauksessa 
  se on samassa tiedostossa kuin lomakkeen käsittelevä koodi. Jos annat 
  action-attribuutille arvon action=""
  niin lomakkeen tiedot lähetään aina tiedostolle itselleen vaikka 
  tiedoston nimi ei olisikaan 4.php -->

<form action="<?php echo $_SERVER['PHP_SELF'];?>" method="post">
  Nimesi: <input name="nimi"><br>
  Viestisi: <input name="viesti" size="50"><br>
<input type="submit" value=" Jätä viesti ">
</form>
</body>
</html>
