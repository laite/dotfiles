<html>
<head>
<title>GD-harjoitus</title>
</head>
<body>

<h1>Kuva kertoo melkein tuhat sanaa</h1>

<?php
// leveys
$leveys = (isset($_POST['leveys']))? $_POST['leveys'] : 300;
$korkeus = (isset($_POST['korkeus']))? $_POST['korkeus'] : 200;
$nelio = (isset($_POST['nelio']))? $_POST['nelio'] : 10;

// parametrit lähetetään kuvalle GET-tyyppisesti
echo "<img src=\"7kuva.php?leveys=$leveys&korkeus=$korkeus&nelio=$nelio\" alt=\"harjoitus 7\" />"
?>

<form action="7.php" method="post">
	Leveys (10-2000): <input name="leveys" value="<?php echo $leveys ?>"><br/>
	Korkeus (10-2000): <input name="korkeus" value="<?php echo $korkeus ?>"><br/>
	Neliön koko (1-200): <input name="nelio" value="<?php echo $nelio ?>"><br/>
	<input type="submit" value="Laske uusi kuva!"/>
</form>
</body>
</html>
