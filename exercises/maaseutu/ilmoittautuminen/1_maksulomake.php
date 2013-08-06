<?php

global $wpdb;

/*
 *
 * Tallennetaan lomakkeen tiedot kantaan
 *
 */

$taulukko = "ilmoittautujat_test";
$ryhma_id = $_GET['ryhma_id'];

if (!isset($_POST['ilmoittaudu'])) {
    // something's wrong
    print("Something's terribly wrong!");
    die();
}
else {

    // tallennetaan tieto riviksi, indeksit vastaavat taulukon sarakkeita
    // (taulun ID tulee automaattisesti auto_increment - attribuutista johtuen)
    $rivi = array (
	'nimi' => $_POST['nimi'],
	'lahiosoite' => $_POST['osoite'],
	'postinumero' => $_POST['postinumero'],
	'paikkakunta' => $_POST['postitoimipaikka'],
	'puhelinnumero' => $_POST['puhnro'],
	'sahkoposti' => $_POST['email'],
	'laktoositon' => $_POST['laktoositon'],
	'gluteeniton' => $_POST['gluteeniton'],
	'maidoton' => $_POST['maidoton'],
	'kasvis' => $_POST['kasvis'],
	'muuta' => $_POST['muuta'],
	'maksettu' => 0,
	'ryhma_id' => $_GET['ryhma_id']
    );

    // lisätään rivi tietokantaan
    // insert() - funktio ottaa sisäänsä 'raakaa' tekstiä ja huolehtii syötetyn datan tietoturvasta itse
    $wpdb->insert($taulukko, $rivi);
}


/*
 *
 * Listataan ryhma_id:n mukaiset ilmoittautujat
 *
 */


$query = "SELECT nimi FROM ". $taulukko ." WHERE (ryhma_id = " . $ryhma_id . ");";
$tulokset = $wpdb->get_results($query);

$hinta = 0;

if ($tulokset)
{
    print "<h3>Ilmoittautuneet henkilöt</h3>";
    foreach ( $tulokset as $rivi ) {
	// asetetaan ryhmä_id:ksi tietokannasta löytynyttä arvoa yksi suurempi
	print $rivi->nimi . "<br/>";

	$hinta += 30;
    }
}
else {
    // periaatteessa meidän ei pitäisi tänne päätyä, sillä olemme juuri ilmoittaneet ainakin yhden henkilön
    print "Jokin meni vikaan. :(";
}

?>

<div>

<form action="http://localhost/wordpress/?page_id=2&ryhma_id=<?php print $ryhma_id; ?>" method="post">
<input type="submit" name="lisaa" value="Lisää uusi osallistuja"/>
</form>

</div>

<?php

/*
 *
 * Lasketaan verkkomaksut oy:n vaatimat jupakkeet 
 *
 */

// hinta must be shown as XX.YY exactly, e.g. "50.00"
$hinta = number_format($hinta, 2);

// lasketaan md5-summa
// TODO: Muokkaa oikeat arvot sit kun saadaan ei-testitunnukset!
$md5summa = md5("6pKF4jkv97zmqBJ3ZL8gUw5DfT2NMQ|13466|$hinta|$ryhma_id|||EUR|http://ksmaaseutugaala.fi|http://ksmaaseutugaala.fi|||S1|||||");
$md5summa = strtoupper($md5summa);
?>

<form id="payment">
  <input type="hidden" name="MERCHANT_ID" value="13466" />
  <input type="hidden" name="AMOUNT" value="<?php print $hinta; ?>" />
  <input type="hidden" name="ORDER_NUMBER" value="<?php print $ryhma_id; ?>" />
  <input type="hidden" name="CURRENCY" value="EUR" />
  <input type="hidden" name="RETURN_ADDRESS" value="http://ksmaaseutugaala.fi" />
  <input type="hidden" name="CANCEL_ADDRESS" value="http://ksmaaseutugaala.fi" />
  <input type="hidden" name="TYPE" value="S1" />
  <input type="hidden" name="AUTHCODE" value="<?php print $md5summa;?>" />

  <input type="submit" value="Siirry maksamaan" />
</form>

<script type="text/javascript" src="//payment.verkkomaksut.fi/js/payment-widget-v1.0.min.js"></script>
<script type="text/javascript">
SV.widget.initWithForm('payment', {charset:'UTF-8'});
</script>
