<?php
include("dbfunctions.php");

// jos me saamme get-metodilla id:n, olemme muokkaamassa tietuetta
if (isset($_GET['id']))
{
	$yhteys = connect();

	// rivi on taulukko, jossa form name toimii indeksinä
	$rivi = fetch_row("osoitelista", $yhteys, $_GET['id']);

	echo $rivi['fname'];
	close($yhteys);
}
// jos lomakkeelta on lähetetty päivitettyä tietoa eikä cancel-nappia ole painettu
else if (isset($_POST['fname']) && isset($_POST['lname']) && isset($_POST['email']) && isset($_POST['address']) && (!isset($_POST['cancel'])))
{
	$yhteys = connect();
	update_row("osoitelista", $yhteys, array( 'id' => $_POST['id'], 'fname' => $_POST['fname'], 'lname' => $_POST['lname'], 'email' => $_POST['email'], 'address' => $_POST['address'] ));
	close($yhteys);
	header("Location: read.php");
	die();
}
// muussa tapauksessa palaamme 'näyttö'-sivulle
else
{
	header("Location: read.php");
	die();
}
?>
<html>
<head>
<title>Muokkaa tietuetta <?php echo $_GET['id']; ?></title>
</head>
<body>

<form name="address" method="post" action="<?php echo ($_SERVER['PHP_SELF']); ?>">
	<table border="0" cellspacing="0" cellpadding="2">
		<input type="hidden" name="id" value="<?php echo $_GET['id'] ?>">
		<tr> 
			<td>Sukunimi:</td>
			<td><input type="text" name="lname" size="40" value="<?php echo $rivi['lname']; ?>"></td>
		</tr>
		<tr> 
			<td>Etunimi: </td>
			<td><input type="text" name="fname" size="40" value="<?php echo $rivi['fname']; ?>"></td>
		</tr>
		<tr> 
			<td>Sähköposti:</td>
			<td><input type="text" name="email" size="40" value="<?php echo $rivi['email']; ?>"></td>
		</tr>
		<tr>
			<td>Osoite:</td>
			<td><input type="text" name="address" size="40" value="<?php echo $rivi['address']; ?>"></td>
		</tr>
		<tr> 
			<td></td>
			<td><div align="right">
				<input type="submit" name="submit" value="Lähetä"><input type="submit" name="cancel" value="Peruuta">
			</div></td>
		</tr>
	</table>
</form>

</body>
</html>
