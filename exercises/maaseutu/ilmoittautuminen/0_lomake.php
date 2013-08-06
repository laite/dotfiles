<?php
/* Luodaan tietokantaan taulu, jollei siellä sellaista vielä ole */

// käytetään wordpressin omaa db-muuttujaa
global $wpdb;

// taulukon nimi
$taulukko = "ilmoittautujat_test";

// taulukon luontikomento SQL-kielellä
$sql = "CREATE TABLE $taulukko (
  id mediumint(9) NOT NULL AUTO_INCREMENT,
  ryhma_id VARCHAR(100),

  nimi VARCHAR(100) NOT NULL,
  lahiosoite VARCHAR(100) NOT NULL,
  postinumero VARCHAR(50) NOT NULL,
  paikkakunta VARCHAR(50) NOT NULL,
  puhelinnumero VARCHAR(50),
  sahkoposti VARCHAR(50),
  laktoositon INT(2),
  gluteeniton INT(2),
  maidoton INT(2),
  kasvis INT(2),
  muuta VARCHAR(1000),

  maksettu INT(2),

  UNIQUE KEY id (id)
);";

// haetaan tarvittava funktio wordpressin omista tiedostoista
require_once( ABSPATH . 'wp-admin/includes/upgrade.php' );

// ajetaan sql - luontikomento
dbDelta( $sql );


/* 
 *
 * Hankitaan ryhmäID 
 *
 */

$ryhma_id = 1;

// 1. katsotaan saadaanko ryhma_id osoiteriviltä
if (isset($_GET['ryhma_id'])) {
  $ryhma_id = $_GET['ryhma_id'];
}
// 2. muussa tapauksessa katsotaan onko tietokannassa aikaisempaa ilmoittautumista
else {
  $query = "SELECT MAX(ryhma_id) AS ryhma_id_max FROM ". $taulukko .";";
  $tulokset = $wpdb->get_results($query);
  
  if ($tulokset)
  {
    foreach ( $tulokset as $rivi ) {
	// asetetaan ryhmä_id:ksi tietokannasta löytynyttä arvoa yksi suurempi
      $ryhma_id = $rivi->ryhma_id_max + 1;
    }
  }
  // 3. Jos tietokannasta ei löydy aiempaa ryhma_id:tä, käytetään 1:stä (alkuarvo ^)
}

/* Sitten tallennetaan saatu tieto kyseiseen taulukkoon */

?>

<form action="http://localhost/wordpress/?page_id=29&ryhma_id=<?php print $ryhma_id; ?>" method="post">
    <table>
    <tr>
    <td> Nimi: </td>
    <td> <input required name="nimi" size="30" maxlength="100" /></td>
    </tr>  
    <tr>
    <td> Lähiosoite: </td>
    <td> <input required name="osoite" size="30" maxlength="100" /></td>  
    </tr>
    <tr>
    <td> Postinumero: </td>
    <td> <input required name="postinumero" size="30" maxlength="10" /></td>  
    </tr>
    <tr>
    <td> Postitoimipaikka: </td>
    <td> <input required name="postitoimipaikka" size="30" maxlength="100" /></td>  
    </tr>
    <tr>
    <td> Puhelinnumero: </td>
    <td> <input name="puhnro" size="30" maxlength="100" /></td>  
    </tr>
    <tr>
    <td> Sähköpostiosoite: </td>
    <td> <input name="email" size="30" maxlength="100" /></td>  
    </tr>
    
    <tr><td rowspan="4">Tilaan erityisruokavalion: </td>
    <td><input type="checkbox" name="laktoositon" value="1"> Laktoositon </td> </tr>
    <tr><td><input type="checkbox" name="gluteeniton" value="1"> Gluteeniton  </td> </tr>
   <tr><td><input type="checkbox" name="maidoton" value="1"> Maidoton </td> </tr>
   <tr><td><input type="checkbox" name="kasvis" value="1"> Kasvis </td> </tr>
   <tr><td> Muuta huomioitavaa: </td> </tr> 
   <tr><td colspan="2"> <textarea name="muuta" rows ="4" cols="50"> </textarea>  </td> </tr>
    </table>  
<input type="submit" value="Ilmoittaudu" size="50" name="ilmoittaudu" />

</form>
