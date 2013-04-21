<html>
<head>
<title>mail</title>
</head>
<body>

<?php
	$vastaanottaja = "vastaanottaja@vastaanottajankoti.osoite";

	// implode joins all values in array with \n
	$data = implode("\n",$_POST['kielet']);

	// send them through php mail() - function
	mail($vastaanottaja, "Viestin otsikko" , $data, 'From: php@palvelin.com');
?>

</body>
</html>
