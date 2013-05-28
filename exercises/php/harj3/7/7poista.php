<?php
session_start();

// suoritetaan vain, mikäli saamme tuote-arvon
if ((isset($_GET['tuote'])) && (isset($_SESSION['ostoskori'])))
{
	// napataan muuttujat siistimpään muotoon
	$poistettava = $_GET['tuote'];
	$ostoskori = $_SESSION['ostoskori'];

	// katsotaan, onko tuote korissa
	// mikäli on, poistetaan se sieltä
	if (array_key_exists($poistettava, $ostoskori))
		unset($ostoskori[$poistettava]);

	// tallennetaan (mahdollisesti) muuttunut ostoskori takaisin sessio-muuttujaan
	$_SESSION['ostoskori'] = $ostoskori;
}

// siirrytään takaisin ostoskoriin
header("Location: 7.php");

?>
