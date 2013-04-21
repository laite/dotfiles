<html>
<head>
	<title>tht2:1</title>
</head>
<body>
<p>
<?php $sivu_numero = $_GET['sivunro'];
		include ("header.txt");
?>
</p><p>
	<?php
		include ("sivu".$sivu_numero.".txt");
	?>
	</p><p>
	<?php
		include ("footer.txt");
	?>
</p> 
</body>	
</html>
