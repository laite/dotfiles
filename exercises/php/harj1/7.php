<html>
	<head>
		<title>7. tulokset</title>
	</head>
	<body>
		<p>
<?php 

/*
 * main operations
 *
 */

$hinta = $_POST['keyboard'] + $_POST['mouse'] + $_POST['gamepad'];
echo $_POST['keyboard'] ." + ". $_POST['mouse'] ." + ". $_POST['gamepad']." = ".$hinta."e";

?>
		</p> 
	</body>	
</html>
