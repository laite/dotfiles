<?php
/**
 *
 * @author tuito
 * 
 * Rajapintaluokka (interface) m��rittelee sovittuja toimintoja
 * jotka pit�� toteuttaa luokassa joka toteuttaa rajapinnan
 * 
 * T�ss� on siis sovittu ett� aina kun pelin kehitt�j� luo uuden vihollisen, sen pit�isi
 * toteuttaa rajapinta VihollisenToiminnot.
 * Uudella vihollisella pit�� olla metodi jolla se iskee pelaajaa. Iske-metodin toteutus j�tet��n
 * vihollisen luovan kehitt�j�n p��tett�v�ksi. Esim. Orkki ja Goblin voivat iske�
 * pelaajaa hieman eri tavalla tai voimalla, puhumattakaan siit� jos kyseess� ovat
 * vaikkapa Tonttu ja Lohik��rme ;-)
 */
interface VihollisenToiminnot 
{
    
//Rajapintaluokassa on metodin esittely ilman sen toteutusta
//Toteutus tehd��n luokassa joka toteuttaa (implements) rajapinnan
    public function iske($p);
}
?>
