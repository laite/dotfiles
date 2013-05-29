<?php

/*
 * Sormus extends esine eli laajentaa sitä 
 * ja perii esineen attribuutit ja metodit
 * 
 * Sormuksella on uusia vain sille ominaisia
 * ominaisuuksia eli taikavoima ja hinta
 * 
 * Jos kaikilla esineillä on hinta, sen voisi laittaa
 * Esine -kantaluokkaan.
 * 
 * 
 */
class Sormus extends Esine 
{
    private $taikavoima;
    private $hinta;

    /*
     * konstruktorissa voi kutsua yliluokan ominaisuuksia
     * super -avainsanalla jolloin niitä ei tarvitse määrittää
     * uudelleen.
     * 
     */
    
	function __construct($taikavoima, $hinta, $nimi, $indeksi, $onkoSyotava) 
	{
		parent::__construct($nimi, $indeksi, $onkoSyotava);
        $this->taikavoima = $taikavoima;
        $this->hinta = $hinta;
    }

    public function getHinta() {
        return $hinta;
    }

    public function setHinta($hinta) {
        $this->hinta = $hinta;
    }

    public function getTaikavoima() {
        return $taikavoima;
    }

    public function setTaikavoima($taikavoima) {
        $this->taikavoima = $taikavoima;
    }
    
	public function tulosta()
	{
        $numero = $this->getIndeksi() + 1;
		// $this->nimi haetaan Esine-luokasta, jossa se on määritelty protected-tyyppiseksi
		// $this->hinta on vain Sormus-luokan sisällä näkyvä muuttuja
        print ("$numero. $this->nimi (arvo $this->hinta kr)<br />");
	}
}
?>
