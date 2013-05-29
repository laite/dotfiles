<?php
	if (isset($_POST['submit']))
	{
		// haetaan tarvittavat funktiot muokatusta dbfunctions-tiedostosta
		include("dbfunctions.php");

		// ladataan sessio ja tallennetaan sen tunnus
		session_start();
		$id = session_id();

		$yhteys = connect();

		// lisätään asiakkaan ostokset, sekä asiakas itse, tauluun
		lisaa_ostokset($yhteys,$id);

		close($yhteys);

		// lopuksi palataan alkusivulle
		header('Location: 7.php');
	}
?>

<html>
<head>
<title>Ostolomake</title>
</head>
<body>
	<form action="lomake.php" method="post">
		Nimi <input type="text" name="nimi" /><br />
		Osoite <input type="text" name="osoite" /><br />
		Sähköposti <input type="text" name="email" /><br />
		<input type="submit" name="submit" value="Lähetä" />
	</form>
</body>
</html>
