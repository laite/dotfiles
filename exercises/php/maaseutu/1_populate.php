<?php
include("db.php");

session_start();
$id = session_id();

echo "Your id is " . $id . "<br>";

$connection = connect();

add_row($connection, "population", 223, "Makkonen", "Kujalanpää", 0);
add_row($connection, "population", 223, "Tiihonen", "Kujalanpää", 0);
add_row($connection, "population", 223, "Ronka", "Kutala", 0);

close($connection);

?>
<html>
<head>
<title>Get populated!</title>
</head>
<body>
	<form action="2_formulate.php" method="post">
		<input type="submit" value="submit" name="populate" />
	</form>
</body>
</html>
