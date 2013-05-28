<?php

session_start();

// set cookie to remember our session id (for 2 days)
setcookie("sessio_id",session_id(),time() + 60 * 60 * 48);

// asetetaan kieli get-muuttujan mukaan, jos sellainen löytyy
if (isset($_GET['language']))
{
	if ($_GET['language'] == "en")
		$_SESSION['language'] = "en";
	else
		// asetetaan kieleksi suomi, jos muuttuja sisältää mitä tahansa muuta kuin 'en'
		$_SESSION['language'] = "fi";
}

// move to next page immediately
header("Location: 8show.php");
?>
