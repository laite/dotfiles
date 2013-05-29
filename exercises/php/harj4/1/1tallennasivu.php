<html>
<head>
<title>tallennasivu</title>
<meta charset="utf-8">
</head>
<body>

<?php 

include("1dbfunctions.php");
$yhteys = connect();
save_page("testi", $yhteys);
close($yhteys);

header("Location: 1naytasivu.php");

?>
</body>
</html>
