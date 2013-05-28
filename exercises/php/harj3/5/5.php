<html>
<head>
<title>h3.5</title>
</head>
<body>
<h1>Sessio-laskuri</h1>
<p>
<?php

// käynnistetään sessio
session_start();

// alustetaan laskuri ensimmäisellä kerralla 1:een,
// lisätään muilla kerroilla lukua yhdellä
if (!isset($_SESSION['laskuri']))
	$_SESSION['laskuri'] = 1;
else
	$_SESSION['laskuri'] += 1;

// haetaan session tunnus
$id = session_id();

// ja tulostetaan tiedot näytölle
echo "Tämä on ". $_SESSION['laskuri'].". vierailusi tällä sivulla. Session id on ". $id." <br>";
?>
</p>
<p><a href="5unset_laskuri.php" alt="Nollaa laskuri">Nollaa laskuri</a>
</p>
</body>
</html>
