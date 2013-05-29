<?php

class VoimaJuoma extends Esine 
{

	private $voima;
	private $hinta;

	function __construct($voima, $hinta, $nimi, $indeksi, $onkoSyotava) 
	{
		parent::__construct($nimi, $indeksi, $onkoSyotava);
		$this->voima = $voima;
		$this->hinta = $hinta;
	}

	public function getHinta() 
	{
		return $this->hinta;
	}

	public function setHinta($hinta) 
	{
		$this->hinta = $hinta;
	}

	public function getVoima() 
	{
		return $this->voima;
	}

	public function setVoima($voima) 
	{
		$this->voima = $voima;
	}

	public function tulosta()
	{
		//super.tulosta();
	}
}
?>
