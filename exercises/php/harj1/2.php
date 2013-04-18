<html>
<head>
	<title>second</title>
</head>
<body>
<p>
	<?php 
		$lastmod = date("d.m.Y @ G:i", getlastmod());
		echo "Last modified: ".$lastmod;
	?>
</p> 
</body>	
</html>
