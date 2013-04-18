<html>
	<head>
		<title>yksi.neljä</title>
	</head>
	<body>
		<p>
		<table border="1">
<?php 
for ($i = 0; $i != 5; ++$i)
{
	echo "<tr class=\"row".($i%2)."\"><td>Tämä on rivi ".$i."</td></tr>";
}

?>
		</table>
		</p> 
	</body>	
</html>
