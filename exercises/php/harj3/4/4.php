<html>
<head>
<title>muokkaasivua</title>

<?php
session_start();

if (isset($_POST['username']) && isset($_POST['password']))
{
	if (($_POST['username'] == "qwerty") && ($_POST['password'] == "qwerty"))
		$_SESSION['login_ok'] = 1; // kirjautuminen hyväksytty
	else
		$_SESSION['login_ok'] = 0;
}

if ($_SESSION['login_ok'] == 0)
{
	echo "Error: You must <a href=\"4index.html\">log in </a>first!";
	exit();
}

?>
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

<p><a href="4.php">Muokkaa sivua</a> - 
<a href="4naytasivu.php">Näytä sivu</a> - 
<a href="4logout.php">Kirjaudu ulos</a></p>

<form action="4tallennasivu.php" method="post"> 

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
