<html>
<head>
	<title>3.1: revisiting tht2.1</title>
</head>
<body>
<p>
<?php 
include ("header.txt");
?>
</p><p>
<?php
// tallennetaan sivunumero omaan muuttujaansa
$sivu_numero = $_GET['sivunro'];

// hyväksymme vain sivunumerot 1, 2 tai 3
$pattern = '/^[1-3]$/';

// mikäli sivu_numero täsmää, näytämme kyseisen sivun
if (preg_match($pattern, $sivu_numero) == 1)
{
	include ("sivu".$sivu_numero.".txt");
}
else
	echo "Please give proper sivunro!";
?>
</p><p>
<?php
include ("footer.txt");
?>
</p> 
</body>	
</html>
