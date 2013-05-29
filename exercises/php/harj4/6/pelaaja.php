<?php

class Pelaaja 
{
	private $nimi;
	private $elinvoima;
	public $VAKIO = "vakiolausahdus!";

	//pelaajalla voi olla esine-olioita. Pelaaja on koosteolio.
	private $reppu = array();

	function __construct() 
	{
		$this->nimi = "Frogomir";
		$this->elinvoima = 10;
		//$this->reppu = new Esine[10];//10 esinettä menee reppuun
	}

	public function arvoLuku() 
	{
		$luku = rand(0,4);
		return $luku;
	}

	public function iske($v)
	{
		$iskuvoima = $this->arvoLuku();
		$vihollinen = $v->getNimi();
		print "$this->nimi iskee vihollista $vihollinen voimalla $iskuvoima!<br />";
		$v->setElinvoima($v->getElinvoima() - $iskuvoima);
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

	public function otaEsine($e, $i) 
	{
		$this->reppu[$i] = $e;
	}

	public function katsoEsineet() 
	{
		foreach ($this->reppu as $index => $value) 
		{
			$value->tulosta();
		}
	}
}
?>
