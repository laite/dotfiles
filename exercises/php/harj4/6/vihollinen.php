<?php
/**
 *
 * @author TuiTo
 * 
 * Vihollinen-luokasta on tehty my�s luokka josta voidaan vain peri�
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


	//t�st� voisi tehd� staattisen metodin joka haetaan aina tarvittaessa
	//esim. ulkoisesta stattisesta luokasta (funktiokirjasto)
	//T�llaisenaan metodi on omana jokaisella vihollisoliolla, mik� on oikeastaan turhaa
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
