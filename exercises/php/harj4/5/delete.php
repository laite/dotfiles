<?php
include("dbfunctions.php");
if (isset($_GET['id']))
{
	echo "deleting id ".$_GET['id'];
	$yhteys = connect();
	// kutsutaan poistofunktiota, joka tekee kaiken työn
	delete_row("osoitelista", $yhteys, $_GET['id']);

	close($yhteys);
}
// siirrytään takaisin listaukseen välittömästi
header("Location: read.php");
?>
