<html>
<head>
<title>h3.6</title>
</head>
<body>
<h1>Funktioiden käyttöä</h1>
<?php

include("6methods.php");

$taulukko = array( 1984, 2001, 2097);

echo "<p>Taulukossa on luvut";
foreach ($taulukko as $key => $value)
	echo " ".$value;

echo "</p><p>";
echo "Suurin arvo taulukossa on ".own_max($taulukko)."<br>";
echo "Pienin arvo taulukossa on ".own_min($taulukko)."<br>";
// pyöristetään keskiarvo kahteen desimaaliin, siistimmän näköinen
echo "Taulukon lukujen keskiarvo on ".round(own_avg($taulukko),2)."<br>";
echo "</p>";
?>
</body>
</html>
