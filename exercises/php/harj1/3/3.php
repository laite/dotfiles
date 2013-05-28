<html>
<head>
	<title>three</title>
</head>
<body>
<p>
	<?php 
		$taulu = array(2, 5, 1, 7, 3);
		sort($taulu);
		foreach ($taulu as $index => $value)
			echo "\$taulu[".$index."] = ".$value."<br>";
	?>
</p> 
</body>	
</html>
