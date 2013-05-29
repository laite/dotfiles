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

// käytetään sessio-muuttujaa tietojen käsittelyssä
session_start();

function nayta_elinvoimat($t1, $t2)
{
	$nimi = $t1->getNimi();
	$voima = $t1->getElinvoima();
	print "$nimi: $voima<br />";

	$nimi = $t2->getNimi();
	$voima = $t2->getElinvoima();
	print "$nimi: $voima<br />";
}

if ((!isset($_SESSION['taistelija1'])) || (!isset($_SESSION['taistelija2'])))
{
	print "taistelijoita ei ole määrätty!<br />";
	print '<a href="index.php?phase=2&nollaa=1">Nollaa tilanne</a>';
	die();
}

$taistelija1 = $_SESSION['taistelija1'];
$taistelija2 = $_SESSION['taistelija2'];

if (isset($_GET['init']))
{
	$taistelulinkki = "Aloita taistelu!";
	print "Puun takaa hyppää ".$taistelija2->getNimi()." ja hyökkää kimppuusi!<br />";
}
else if (isset($_GET['continue']))
{
	$taistelulinkki = "Jatka taistelua!";
	$taistelija1->iske($taistelija2);
	$taistelija2->iske($taistelija1);
}

if (isset($_GET['init']) || isset($_GET['continue']))
{
	print "<h2>Taistelu!</h2>";

	nayta_elinvoimat($taistelija1, $taistelija2);
	print "<br />";

	$voima1 = $taistelija1->getElinvoima();
	$voima2 = $taistelija2->getElinvoima();

	$nimi1 = $taistelija1->getNimi();
	$nimi2 = $taistelija2->getNimi();
	if (($voima1 <= 0) && ($voima2 <= 0))
		print "Taistelun äänet hiljenevät, luonto ympärillä tasaantuu. Sekä $nimi1 että $nimi2 makaavat kuolleina.<br/>";
	else if (($voima1 > 0) && ($voima2 <= 0))
		print "Raivoisan taistelun jälkeen $nimi1 päästää voitokkaan karjahduksen ilmoille. $nimi2 on kuollut!<br />";
	else if (($voima1 <= 0) && ($voima2 > 0))
		print "$nimi2 katsoo, kuinka $nimi1 vetää viimeisen henkäyksensä, ja poistuu paikalta tyynesti.<br />";
	else
	{
		print '<a href="taistelu.php?continue=1">'.$taistelulinkki.'</a><br />';
		print '<a href="taistelu.php?escape=1">Pakene!</a><br />';
	}

	$_SESSION['taistelija1'] = $taistelija1;
	$_SESSION['taistelija2'] = $taistelija2;
}
else if (isset($_GET['escape']))
{
	$_SESSION['taistelija1'] = null;
	$_SESSION['taistelija2'] = null;
	print "Pakenit häpeällisesti.<br />";
}

print '<a href="index.php?phase=2&nollaa=1">Nollaa tilanne</a>';
?>
