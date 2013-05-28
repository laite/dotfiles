<html>
<head>
<title>Laskurin nollaus</title>
</head>
<body>
<p>
<?php

session_start();

// nollataan laskuri, jos se on voimassa
if (isset($_SESSION['laskuri']))
{
	$_SESSION['laskuri'] = NULL;
	echo "Vierailu-laskurin nollaus on suoritettu. ";
}
else
{
	echo "Vierailu-laskuria ei löytynyt. ";
}

?>
<a href="5.php" alt="palaa takaisin">Palaa laskuri-sivulle</a>
</p>
</body>
</html>
