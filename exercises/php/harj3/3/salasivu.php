<?php

session_start();

if ($_SESSION['login_ok'] != 1)
	echo "VIRHE: Et ole kirjautunut!";
else
	echo "Tervetuloa, tässä salainen sanoma.";
?>
