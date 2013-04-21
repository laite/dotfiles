<html>
<head>
<title>Hm</title>
</head>
<body>

<?php
$a = 2;

$b = ($a == 2)? '2' : (($a == 3)? '3' : '4');
$c = ($a == 2)? '2' : ($a == 3)? '3' : '4';
array_diff()
echo $b.' / '.$c;
?>

</body>
</html>
