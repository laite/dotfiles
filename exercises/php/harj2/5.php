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

if (isset($_POST['nimi']) && isset($_POST['viesti'])) 
{
	// tarkistetaan onko käyttäjä antanut captchan oikein
	// tässä harjoituksessa käytetään vain yhtä kuvaa, jossa lukee "following finding"
	if ((isset($_POST['captcha'])) && ($_POST['captcha'] == "following finding"))
	{
		$nimi=$_POST['nimi'];
		$viesti=$_POST['viesti'];
	
		// luodaan uusi rivi annetuista tiedoista
		$uusirivi = '<p><b>' . date('d.m.Y H:i') . ', ' .
			strip_tags($nimi) . '</b>: ' . strip_tags($viesti) .
			'</p>';
	
		// kutsutaan funktiota, joka lisää uuden rivin ylimmäiseksi vieraskirjaan
		lisaaRivi($uusirivi);
	}
	else
		echo ("CAPTCHA EI TÄSMÄÄ!");
}
else
	echo ("Ole hyvä ja täytä sekä nimi- että viesti-laatikko.");
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
	<img src="http://upload.wikimedia.org/wikipedia/commons/b/b6/Modern-captcha.jpg" alt="captcha"/><br/>
	Kuvavarmennus, kirjoita kuvassa näkyvä teksti: <br/>
	<input name="captcha" size="50"><br>
	<input type="submit" value=" Jätä viesti ">
</form>
</body>
</html>
