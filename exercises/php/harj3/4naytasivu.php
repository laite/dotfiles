<html>
<head>
<title>naytasivu</title>
</head>
<body>
<p>
<a href="4.php">Muokkaa sivua</a> - 
<a href="4naytasivu.php">Näytä sivu</a> 

<!--Tekstitiedosto tuodaan sivulle-->
<?php 

session_start();

if ($_SESSION['login_ok'] != 1)
{
	echo "</p>Error: You must <a href=\"4index.html\">log in </a>first!";
	exit();
}
else
{
	// logout linkki näytetään vain, jos käyttäjä on kirjautunut sisään
	echo " - <a href=\"4logout.php\">Kirjaudu ulos</a></p>";
}

// sivu.txt sisällytetään vain, mikäli sessio-kirjautuminen on 1 (eli onnistunut)
include ('sivu.txt'); ?> 


</body>
</html>
