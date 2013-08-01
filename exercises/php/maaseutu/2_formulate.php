<?php
if (isset($_POST['populate']))
	die();
else
{
	session_start();
	$session_id = session_id();
}
?>
<html>
<head>
<title>Get formulated!</title>
</head>
<body>
<?php

include("db.php");
$yhteys = connect();

$table = "population";

# for testing purposes, we use stable ID
$session_id = 223;

# query database for items with current session id that are not paid
$query = "SELECT * FROM $table WHERE Maksu_id = 223";

$result = mysqli_query($yhteys, $query);

$hinta = 0;

# print each value from database (row[0] on successfull query is ID)
while ($row = mysqli_fetch_row($result)) 
{
	$hinta += 30;
	$num = count($row);
	echo "*** $row[0] ***<br/>";
	for ($i = 1; $i < $num; $i++)
		echo $row[$i] . "<br/>";
}

close($yhteys);

# hinta must be shown as XX.YY exactly, e.g. "50.00"
$hinta = number_format($hinta, 2);

# lasketaan md5-summa
$md5summa = md5("6pKF4jkv97zmqBJ3ZL8gUw5DfT2NMQ|13466|$hinta|testi1|||EUR|http://ksmaaseutugaala.fi|http://ksmaaseutugaala.fi|||S1|||||");
$md5summa = strtoupper($md5summa);
?>

<form id="payment">
  <input type="hidden" name="MERCHANT_ID" value="13466" />
  <input type="hidden" name="AMOUNT" value="<?php print $hinta; ?>" />
  <input type="hidden" name="ORDER_NUMBER" value="testi1" />
  <input type="hidden" name="CURRENCY" value="EUR" />
  <input type="hidden" name="RETURN_ADDRESS" value="http://ksmaaseutugaala.fi" />
  <input type="hidden" name="CANCEL_ADDRESS" value="http://ksmaaseutugaala.fi" />
  <input type="hidden" name="TYPE" value="S1" />
  <input type="hidden" name="AUTHCODE" value="<?php print $md5summa;?>" />

  <input type="submit" value="Siirry maksamaan" />
</form>

</body>
<script type="text/javascript" src="//payment.verkkomaksut.fi/js/payment-widget-v1.0.min.js"></script>
<script type="text/javascript">
SV.widget.initWithForm('payment', {charset:'UTF-8'});
</script>
</html>
