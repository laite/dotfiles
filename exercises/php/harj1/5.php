<html>
	<head>
		<link rel="stylesheet" type="text/css" href="5.css">
		<title>Viisi</title>
	</head>
	<body>
		<p>
		<table border="1">
<?php 
for ($i = 0; $i != 5; ++$i)
{
	// $i%2 palauttaa 0 tai 1, riippuen onko $i pariton vai parillinen
	echo "<tr class=\"row".($i%2)."\"><td>Tämä on rivi ".$i."</td></tr>";
}

?>
		</table>
		</p> 
	</body>	
</html>
