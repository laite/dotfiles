<?php

/*
 * Sormus extends esine eli laajentaa sit� 
 * ja perii esineen attribuutit ja metodit
 * 
 * Sormuksella on uusia vain sille ominaisia
 * ominaisuuksia eli taikavoima ja hinta
 * 
 * Jos kaikilla esineill� on hinta, sen voisi laittaa
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
     * super -avainsanalla jolloin niit� ei tarvitse m��ritt��
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
		// $this->nimi haetaan Esine-luokasta, jossa se on m��ritelty protected-tyyppiseksi
		// $this->hinta on vain Sormus-luokan sis�ll� n�kyv� muuttuja
        print ("$numero. $this->nimi (arvo $this->hinta kr)<br />");
	}
}
?>
