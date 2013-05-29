<?php
/**
 *
 * @author tuito
 * 
 * Rajapintaluokka (interface) määrittelee sovittuja toimintoja
 * jotka pitää toteuttaa luokassa joka toteuttaa rajapinnan
 * 
 * Tässä on siis sovittu että aina kun pelin kehittäjä luo uuden vihollisen, sen pitäisi
 * toteuttaa rajapinta VihollisenToiminnot.
 * Uudella vihollisella pitää olla metodi jolla se iskee pelaajaa. Iske-metodin toteutus jätetään
 * vihollisen luovan kehittäjän päätettäväksi. Esim. Orkki ja Goblin voivat iskeä
 * pelaajaa hieman eri tavalla tai voimalla, puhumattakaan siitä jos kyseessä ovat
 * vaikkapa Tonttu ja Lohikäärme ;-)
 */
interface VihollisenToiminnot 
{
    
//Rajapintaluokassa on metodin esittely ilman sen toteutusta
//Toteutus tehdään luokassa joka toteuttaa (implements) rajapinnan
    public function iske($p);
}
?>
