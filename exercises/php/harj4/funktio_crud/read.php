<html>
    <head>
        <title>list.php</title>
    </head>
    <body>
        <p>
            <b>Tietueiden listaus </b>[<a href='create.php'>Lisää uusi tietue</a>]</p>

        <?php
        //tietueiden listaus sivulle funktioiden avulla
        include("dbfunctions.php");

        $yhteys = connect();
        list_table("osoitelista", $yhteys);
        close($yhteys);
        ?> 
    </body>
</html>