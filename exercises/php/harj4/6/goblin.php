<?php
class Goblin extends Vihollinen implements VihollisenToiminnot 
{
	function __construct($nimi, $elinvoima) 
	{
		parent::__construct($nimi, $elinvoima);
	}

	public function iske($p) 
	{
		$p->setElinvoima($p->getElinvoima() - (arvoLuku() + 1));  
	}
}
?>
