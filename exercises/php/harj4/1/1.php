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

<p><a href="1.php">Muokkaa sivua</a> - <a href="1naytasivu.php">Näytä sivu</a></p>

<form action="1tallennasivu.php" method="post"> 

<?php
include("1dbfunctions.php");
// connect ottaa tietokantaan yhteyden
$yhteys = connect();
// read_page lukee halutun id:n kannasta ja palauttaa sisällön
$data = read_page("testi", 1, $yhteys);
// suljetaan yhteys kantaan
close($yhteys);
?>

<input type="hidden" name="id" value="1" />
<input type="hidden" name="nimi" value="tinymce_edit1" />

<!-- Textarea korvataan TinyMCE-editori-ikkunalla-->
<textarea name="text" rows="20" cols="80"> 
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
