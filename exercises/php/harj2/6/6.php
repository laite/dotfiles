<html>
<head>
<title>muokkaasivua</title>

<!-- Liitetään TinyMCE:n JS-koodi sivulle-->
<script type="text/javascript" src="tiny_mce/tiny_mce.js"></script>
<!-- Yksinkertainen TinyMCE -editori-ikkuna korvaa textarean näillä asetuksilla-->
<script type="text/javascript">
	tinyMCE.init({
		mode : "textareas",
		theme : "simple"
	});
</script>

</head>
<body>

<p><a href="6.php">Muokkaa sivua</a> - <a href="6naytasivu.php">Näytä sivu</a></p>

<form action="6tallennasivu.php" method="post"> 

<?php
$tiedosto = "sivu.txt"; 
//avataan $tiedosto
$avattu = fopen ($tiedosto, "r"); 
//tiedosto luetaan fread-funktiolla muuttujaan $data
$data = fread ($avattu, filesize($tiedosto)); 
// suljetaan avattu tiedosto
fclose ($avattu); 
?>

<!-- Textarea korvataan TinyMCE-editori-ikkunalla-->
<textarea name="muokattu" rows="20" cols="80"> 
<?php echo $data; ?>
</textarea><br>

<input type="submit" value="tallenna">
</form>

<p>WWW-sivun muokkaus selaimella.</p>
<p>Muokkaasivua.php lukee teksitiedoston sisällön textareaan. 
Tallennasivu.php tallentaa textarean sisällön tekstitiedostoon ja heittää käyttäjän suoraan
sivulle naytasivu.php, jolle tuodaan incluuderilla tekstitiedoston sisältö.

</body>
</html>
