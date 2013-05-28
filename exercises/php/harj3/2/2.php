<html>
<head>
	<title>3.2: revisiting 2.2 - now with cookies!</title>
</head>
<body>
<?php
if (isset($_POST['kielet']))
{
	// siivotaan aiemmat cookiet
	// pelkkä alempi luuppi ei riitä, sillä olemme saattaneet edellisellä kerralla
	// valita useampia kieliä kuin nyt, ja ne näkyvät virheellisesti tuloksissa
	for ($i = 0; $i != 7; ++$i)
	{
		if (isset($_COOKIE["kieli$i"]))
			setcookie("kieli$i", "");
	}

	// tallennamme uudet cookiet (indeksein 0..n)
	foreach (($_POST['kielet']) as $index => $kieli)
	{
		setcookie("kieli$index", $kieli, time()+3600);
		echo "set cookie kieli$index as $kieli";
	}

	// cookiet luetaan vain silloin, kun selain saa uutta tietoa palvelimelta.
	// tästä johtuen emme voi tulostaa niitä välittömästi käyttäen $_COOKIE:ta
	// vaan luemme ne sivulta 2showcookie.php
	echo '<meta http-equiv="refresh" content="0; URL=2showcookie.php">';
}
else
{
?>
	<h1>Mitä ohjelmointikieliä sinä osaat?</h1>
<p>
	<form method="post" action="2.php">
		<select name="kielet[ ]" multiple size="5">
			<option value="Assembly">Assembly</option>
			<option value="C">C</option>
			<option value="C++">C++</option>
			<option value="Java">Java</option>
			<option value="MUMPS">MUMPS</option>
			<option value="Perl">Perl</option>
			<option value="Python">Python</option>
		</select>
		<input type="submit" name="submit" value=Submit>
	</form>
</p> 
<?php
}
?>
</body>	
</html>
