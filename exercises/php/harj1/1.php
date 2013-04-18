<html>
<head>
	<title>Eka php-dokumentti eka.php</title>
</head>
<body>
<p>
<!-- echo tulostaa lainausmerkeissä olevan merkkijonon näytölle -->
	<?php 
		$paivays = "Nyt on ". date("d.m.Y")." klo ".date("G:i:s");
		echo $paivays;


	?>
</p> 
</body>	
</html>
