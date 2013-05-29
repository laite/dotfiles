<?php
/**
 * 
 * Orkki toteuttaa rajapinnan VihollisenToiminnot, joten sill� pit��
 * olla iske-metodi
 */
class Orkki extends Vihollinen implements VihollisenToiminnot
{
    //Orkin omia ominaisuuksia voisi tehd� t�h�n
    
    //Konstruktorissa perit��n yliluokan konstruktori
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
