<?php

// käytämme jeditable:n tuottamaa id:tä tarkistamaan, että POST on onnistunut
if (!isset($_POST['id']))
	die("VIRHE: POST[id] puuttuu!");

// lataamme nykyisen sivun ID:n sessio-muuttujasta
session_start();

// tulostetaan virhe, ellei 'nykyistä sivua' löydy
if (!isset($_SESSION['current_page']))
	die("VIRHE: Ei nykyistä sivua!");

// sisältö saadaan jeditable:n post-muuttujasta
$current_id = $_SESSION['current_page'];
$newcontent = $_POST['value'];

// avataan yhteys kantaan
$db = mysqli_connect("localhost","laite","goblinsPHP", "laite") or die ("Yhteyttä kantaan ei saatu"); 

// päivitetään sisältö haluttuun tietueeseen
$query = "UPDATE h5t3 SET Sisalto='$newcontent' WHERE (Id = $current_id)";
$result = mysqli_query($db, $query);

// tulostetaan "uusi" tieto laatikkoon (jeditable korvaa muuten tekstin 'click to edit':llä)
echo $newcontent;
?>
