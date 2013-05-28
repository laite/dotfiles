<html>
	<head>
		<title>tht6 tulostus</title>
	</head>
	<body>
		<p>
<?php 
function sum($a, $b)
{
	return ($a+$b);
}
function multiply($a, $b)
{
	return ($a*$b);
}

/*
 * main operations
 *
 */
if ($_POST['yhteenlasku'])
	echo $_POST['luku1']." + ".$_POST['luku2']." = ".sum($_POST['luku1'],$_POST['luku2']);
else if ($_POST['kertolasku'])
	echo $_POST['luku1']." * ".$_POST['luku2']." = ".multiply($_POST['luku1'],$_POST['luku2']);
else
	echo "something exciting is happening."
?>
		</p> 
	</body>	
</html>
