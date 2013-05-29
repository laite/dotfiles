<html>
<head>
<title>naytasivu</title>
</head>
<body>
<p><a href="1.php">Muokkaa sivua</a> - <a href="1naytasivu.php">Näytä sivu</a></p>

<?php 
include('1dbfunctions.php');

$yhteys = connect();
echo read_page("testi", 1, $yhteys);

close($yhteys);

?> 

</body>
</html>
