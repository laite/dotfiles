<?php
/**
 * 
 * Orkki toteuttaa rajapinnan VihollisenToiminnot, joten sillä pitää
 * olla iske-metodi
 */
class Orkki extends Vihollinen implements VihollisenToiminnot
{
    //Orkin omia ominaisuuksia voisi tehdä tähän
    
    //Konstruktorissa peritään yliluokan konstruktori
	function __construct($nimi, $elinvoima) 
	{
		parent::__construct($nimi, $elinvoima);
    }

   /* 
    * iske -metodin toteutus
    */
	public function iske($p) 
	{
		$iskuvoima = $this->arvoLuku();
		$vihollinen = $p->getNimi();
		print "$this->nimi iskee vihollista $vihollinen voimalla $iskuvoima!<br />";
		$p->setElinvoima($p->getElinvoima() - $iskuvoima);  
    } 
}
?>
