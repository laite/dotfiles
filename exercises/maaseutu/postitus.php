<?php
	// lähetetään haluttu runko sähköpostilla php:n mail-funktiota käyttäen
	if (isset($_POST['posti_runko']))
	{
		$message = $_POST['posti_runko'];
		// TODO: vaihda oikeat osoitteet
		$to = "klingasteri@gmail.com";
		$subject = "Äänestys-tulokset";
		$from = "aanestys@ksmaaseutugaala.fi";
		$headers = "From:".$from;
		mail($to,$subject,$message,$headers);
	}

	// palataan takaisin näyttö-sivulle
	// TODO: vaihda oikea osoite
	header("Location: http://127.0.0.1/wordpress/?page_id=47");
?>
