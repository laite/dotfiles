<html>
<head>
<title>3.php</title>
</head>
<body>

<h1>Tiedoston poisto / luominen </h1>
<p>
	<a href="3.php?method=luo">Luo tiedosto</a>
	<a href="3.php?method=poista">Poista tiedosto</a>
</p>
<p>

<?php

// Luodaan testikansio testi-kansion alle, jottei koko php-kansiolle tarvitse antaa oikeuksia kaikkeen
// uuden tiedoston polku siis tulee olemaan ./testi/testi/tiedosto.txt (missä . = /var/www/php minulla)
$KANSIO = "testi/testi";
$TIEDOSTO = "tiedosto.txt";

// poista() - funktio poistaa sekä kansion että tiedoston, mikäli ne ovat olemassa
function poista()
{
	global $KANSIO, $TIEDOSTO;

	if ((file_exists($KANSIO)) && (file_exists($KANSIO.'/'.$TIEDOSTO)))
	{
		// unlink palauttaa booleanina onnistumisen
		$boo = unlink($KANSIO.'/'.$TIEDOSTO);
		if ($boo)
		{
			echo "Destroyed file $KANSIO/$TIEDOSTO<br>";
			// myös rmdir antaa onnistumisen arvon takaisin
			$boo = rmdir($KANSIO);
			if ($boo)
				echo "Destroyed directory $KANSIO<br>";
			else
				echo "ERROR: Couldn't remove folder $KANSIO!";
		}
		else
			echo "ERROR: Couldn't remove file $TIEDOSTO!";
	}
	else
		echo "Tiedostoa ei ole olemassa!";
}

// luo() - funktio luo kansion sekä sinne tiedoston, mikäli niitä ei ole vielä olemassa
function luo()
{
	// globaalit muuttujat pitää ottaa erillisellä avainsanalla käyttöön (herätti ihmetystä hetken :P)
	global $KANSIO, $TIEDOSTO;

	if ((file_exists($KANSIO)) && (file_exists($KANSIO.'/'.$TIEDOSTO)))
		echo "Tiedosto on jo olemassa!";
	else
	{
		$boo = mkdir("$KANSIO");
		if ($boo)
		{
			echo "Created directory $KANSIO<br>";
			$boo = fopen("$KANSIO/$TIEDOSTO", "w");
			if ($boo)
				echo "Created file $KANSIO/$TIEDOSTO<br>";
			else
				echo "ERROR: Couldn't create file $KANSIO/$TIEDOSTO";
		}
		else
			echo "ERROR: Couldn't create directory $KANSIO!";
	}
}

// Main program
// Käytämme GETtiä lukemaan haluttu toiminto
if (isset($_GET['method']))
{
	if ($_GET['method'] == "poista")
		poista();
	else if ($_GET['method'] == "luo")
		luo();
	else
		echo "Kelvoton method-arvo";
}
else
	echo "Tarvitsen methodin!";

?>
</p>
</body>
</html>
