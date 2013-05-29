<html>
    <head>
        <title>list.php</title>
    </head>
    <body>
        <p>
			<b>Tietueiden listaus </b>[<a href='create.php'>Lisää uusi tietue</a>]
		</p>
		<p>
			<form method="post" action="read.php">
			<input type="text" name="hakusana" placeholder="Hae tietueista" />
			<input type="submit" value="Hae"/>
			</form>
        <?php
        //tietueiden listaus sivulle funktioiden avulla
        include("dbfunctions.php");

        $yhteys = connect();
		
		// jos meillä on hakusana, haetaan sillä
		// muussa tapauksessa listataan kaikki tietueet
		if (isset($_POST['hakusana']))
			search_table("osoitelista", $yhteys, $_POST['hakusana']);
		else
			list_table("osoitelista", $yhteys);
        close($yhteys);
        ?> 
    </body>
</html>
