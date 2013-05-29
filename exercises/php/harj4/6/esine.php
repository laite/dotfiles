<?php
/*
 * Esine on kantaluokka josta voidaan peri� erilaisia esineit�
 * Tehd��n siit� abstrakti eli siit� ei voi luoda olioita vaan
 * pelk�st��n peri� uusia luokkia.
 *
 */
abstract class Esine
{
    protected $nimi;
    protected $indeksi;
    private $onkoSyotava;

    function __construct($nimi, $indeksi, $onkoSyotava)
	{
        $this->nimi = $nimi;
        $this->onkoSyotava = $onkoSyotava;
        $this->indeksi = $indeksi;
    }

    public function getNimi()
	{
        return $this->nimi;
    }

    public function setNimi($nimi)
	{
        $this->nimi = $nimi;
    }

	public function isOnkoSyotava()
	{
        return $this->onkoSyotava;
    }

    public function setOnkoSyotava($onkoSyotava) {
        $this->onkoSyotava = $onkoSyotava;
    }

    public function getIndeksi() {
        return $this->indeksi;
    }

    public function setIndeksi($indeksi) {
        $this->indeksi = indeksi;
    }

	public function tulosta() 
	{
        $numero = $this->getIndeksi() + 1;
        print ("$numero. $this->nimi <br />");
    }
}
?>
