<html>
<head>
<title>More secure login</title>
</head>
<body>
<?php
if (isset($_POST['nick']) && isset($_POST['pass']))
{
	// tell php we use session var's
	session_start();

	// hyväksymme vain "qwerty"-tunnuksen/salasanan
	// huom: onnistunut kirjautuminen nollautuu, mikäli syötetään
	// väärä tunnus/salasana!
	if (($_POST['nick'] == "qwerty") && ($_POST['pass'] == "qwerty"))
		$_SESSION['login_ok'] = 1;
	else
		$_SESSION['login_ok'] = 0;

	// siirrytään salaiselle sivulle joka tapauksessa, tutkitaan
	// siellä vasta onko kirjautuminen onnistunut
	header("location: salasivu.php");
}
?>

<form action="3.php" method="post">
	Nick: <input name="nick"/><br/>
	Pass: <input name="pass"/><br/>
	<input type="submit" value="Kirjaudu" />
</form>

</body>
</html>
