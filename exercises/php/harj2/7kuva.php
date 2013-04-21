<?php 
if (isset($_GET['leveys']) && isset($_GET['korkeus']) && isset($_GET['nelio']))
{
	// kerrotaan kyseessä olevan kuva
	header("Content-type: image/png"); 

	// tallennetaan annetut arvot helpompaan muotoon
	$xw = $_GET['leveys'];
	$yw = $_GET['korkeus'];
	$size = $_GET['nelio'];

	// tarkastetaan rajat
	if ($xw < 10 || $xw > 2000) $xw = 300;
	if ($yw < 10 || $yw > 2000) $yw = 200;
	if ($size < 1 || $size > 200) $size = 20;
	
	// luodaan kuva leveys*korkeus
	$img = imagecreatetruecolor($xw, $yw);
	
	// piirretään täyteen neliöitä
	for($y=0;$y<$yw;$y += $size){
		for($x=0;$x<$xw;$x+=$size){
			// punainen on vallitseva väri
			$r = rand(0,255);
			$g = rand(0,50);
			$b = rand(0,50);
			$color = imagecolorallocate($img, $r, $g, $b);
	
			imagefilledrectangle ($img, $x, $y, $x+$size ,$y+$size, $color);
		}
	}
	
	// viimeistelyyn sininen silaus! (alpha: 0-127)
	$shade = imagecolorallocatealpha($img, 0, 50, 100, 65);
	imagefilledrectangle($img,25,25,($xw-25),($yw-25), $shade);
	
	// mielivaltaisia, joskin taiteellisia valkoisia viivoja ristiksi
	$white = imagecolorallocatealpha($img, 255, 255, 255, 70);

	$barx = rand(0, ($xw-20));
	imagefilledrectangle($img,$barx,0,$barx+20,$yw, $white);
	
	$bary = rand(0, ($yw-20));
	imagefilledrectangle($img,0,$bary,$xw,$bary+20, $white);
	
	// lähetetään kuva selaimelle png-muodossa
	imagepng($img);
	
	// vapautetaan muistit
	imagedestroy($img);
}
 	?>
