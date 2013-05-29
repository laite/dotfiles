<?php
/**
 *
 * @author TuiTo
 * 
 * Vihollinen-luokasta on tehty myös luokka josta voidaan vain periä
 * erilaisia vihollisolioita. Vrt. Esine.
 */
abstract class Vihollinen 
{
	protected $nimi;
	private $elinvoima;

	function __construct($nimi, $elinvoima) 
	{
		$this->nimi = $nimi;
		$this->elinvoima = $elinvoima;
	}


	//tästä voisi tehdä staattisen metodin joka haetaan aina tarvittaessa
	//esim. ulkoisesta stattisesta luokasta (funktiokirjasto)
	//Tällaisenaan metodi on omana jokaisella vihollisoliolla, mikä on oikeastaan turhaa
	public function arvoLuku() 
	{
		$luku = rand(0,4);
		return $luku;
	}   

	public function getNimi() 
	{
		return $this->nimi;
	}

	public function setNimi($nimi)
	{
		$this->nimi = $nimi;
	}

	public function getElinvoima() 
	{
		return $this->elinvoima;
	}

	public function setElinvoima($elinvoima) 
	{
		$this->elinvoima = $elinvoima;
	}
}

?>
