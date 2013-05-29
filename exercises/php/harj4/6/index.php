<html><head>
<title>Let's play a game</title>
<meta charset="utf-8" />
</head>
<body>
<?php

// http on tilaton protokolla, nämä on ladattava joka kerta uudestaan
include("esine.php");
include("vihollinen.php");
include("vihollisentoiminnot.php");
include("goblin.php");
include("orkki.php");
include("pelaaja.php");
include("sormus.php");
include("voimajuoma.php"); 

// tallennetaan tarvittavat objektit sessio-muuttujaan
session_start();

if (!isset($_GET['phase']))
{
	//Pelaaja, Orkki ja Sormus ovat pelin olioita
	$p = new Pelaaja();
	$o = new Orkki("Örkki", 8);
	$s = new Sormus(10,100,"Mahtisormus", 0, false);
	//Esine e = new Esine("Jokuesine", 1, false); //Olion luonti ei onnistu koska Esine on abstrakti luokka
	
	$_SESSION['pelaaja'] = $p;
	$_SESSION['orkki'] = $o;
	$_SESSION['sormus'] = $s;

	print ("Kävelet metsässä ja näet mielenkiintoisen esineen: " . $s->getNimi()."<br/>");
	print ("Otatko sen mukaasi?<br />");
	print '<a href="index.php?phase=1&answer=1">Kyllä</a><br /><a href="index.php?phase=1&answer=2"> Ei</a>';
	die();
}
else
{
	$p = $_SESSION['pelaaja'];
	$o = $_SESSION['orkki'];
	$s = $_SESSION['sormus'];
}

if ($_GET['phase'] == 1)
{
	$vastaus = $_GET['answer'];
	if ($vastaus == 1) 
	{
		$p->otaEsine($s, 0);
		print "Repussasi ovat seuraavat esineet:<br />";
		$p->katsoEsineet();
	}
	else
	{
		print "Jätit esineen sikseen.<br />";   
	}

	print '<a href="index.php?phase=2">Jatka matkaa</a>';
}
else if ($_GET['phase'] == 2)
{
	if (isset($_GET['nollaa']))
	{
		$_SESSION['taistelija1'] = new Pelaaja();
		$_SESSION['taistelija2'] = new Orkki("Uusi örkki", 8);
	}
	else
	{
		$_SESSION['taistelija1'] = $p;
		$_SESSION['taistelija2'] = $o;
	}
	print "Metsästä kuuluu kummallista ääntä!<br />";
	print '<a href="taistelu.php?init=1">Mene katsomaan</a>';
}
?>
</body>
</html>
