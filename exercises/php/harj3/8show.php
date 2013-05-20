<html>
<head>
<title>Show up</title>
</head>
<body>

<?php

// ladataan edellinen sessio cookien avulla, mikäli sellainen löytyy
if (isset($_COOKIE['sessio_id']))
	session_id($_COOKIE['sessio_id']);

session_start();

// käytetään vakiona suomenkieltä
$lang = "fi";

// jos sessiomuuttuja on olemassa, käytetään sitä
if (isset($_SESSION['language']))
	$lang = $_SESSION['language'];

// ladataan muuttujat $selected_lang ja $favourite_sport kansallisuuden mukaan tiedostosta
include("8_".$lang.".php");
?>

<!-- haetaan tauluun arvot php-lauseilla -->
<table>
	<tr>
		<td>Kieli:</td>
		<td><?php echo $selected_lang; ?></td>
	</tr>
	<tr>
		<td>Suosikkilaji:</td>
		<td><?php echo $favourite_sport; ?></td>
	</tr>
</table>

</body>
</html>
