<?php 
session_start();

// ladataan ostoskori sessio-muuttujasta, jos siellä sellainen on
if (isset($_SESSION['ostoskori']))
	$ostoskori=$_SESSION['ostoskori'];

// jos saamme post-dataa, käsittelemme sen tässä
if(isset($_POST['tuote']) && isset($_POST['lkm']))
{
	$tuote=$_POST['tuote'];
	$lkm=$_POST['lkm'];
	
	// $muuttuja:a käytetään tutkimaan, onko tuote jo aiemmin lisätty koriin
	$muuttuja = 0;

	// jos tuote on olemassa
	if ($tuote){
		// jos ostoskoria ei vielä ole, luodaan sinne uusi key-value pari tuote-lukumäärä
		if (!isset($ostoskori))
		{
			$ostoskori[$tuote]=$lkm;
		}
		// muussa tapauksessa tarkistamme onko kyseistä tuotetta jo korissa ennestään
		else
		{
			foreach($ostoskori as $t => $n){
				// jos tuote löytyy jo ennestään, lisäämme siihen lukumäärän
				// jonka saimme $_POST-muuttujalla
				if ($tuote==$t){
					$ostoskori[$t]+=$lkm;
					$muuttuja=1;
				}
			}
			// mikäli tuotetta ei korista löytynyt, lisäämme sen sinne tässä
			if (!$muuttuja) 
				$ostoskori[$tuote]=$lkm;
		}
	}
	// tallennamme ostoskorin sessio-muuttujaan
	$_SESSION['ostoskori']=$ostoskori;
}
?>
<html>
<body>

<form action="7.php" method="post">
Tuote <input type="text" name="tuote" size="20"><br>
Lkm <input type="text" name="lkm" size="20"><br>
<input type="submit" value="Lisää ostoskoriin"><br>
</form>
<?php

if ((isset($ostoskori)) && (count($ostoskori) > 0))
{
	echo "Ostoskorissasi ovat seuraavat tuotteet:<br>";

	// tulostetaan ostoskorin sisältö, sekä tuotteen poisto-linkki ruudulle
	foreach($ostoskori as $t => $n)
		echo $n." kpl ".$t." (<a href=\"7poista.php?tuote=$t\">Poista tuote</a>)<br>";

	echo '<a href="lomake.php">Osta tuotteet</a><br />';
}
else
{
	echo "Ostoskorisi on vielä tyhjä!<br>";
}
?>

</body>
</html> 
