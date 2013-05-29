<html>
    <head>  
        <title>create.php</title>
    </head> 
    <body>    

        <?php
        //tietueen lisäys tauluun funktioiden avulla
        include("dbfunctions.php");

         /* Jos lomakkeella on painettu poistu-nappia niin 
          siirrytään list.php -sivulle ja lopetetaan tämä skripti */
        if (isset($_POST['cancel'])) {
            header('Location: read.php');
            die();
        }
        
        /* Katsotaan ovatko tarvittavat arvot tulleet lomakkeelta */
        if (isset($_POST['fname']) && isset($_POST['lname']) && isset($_POST['email']) && isset($_POST['address'])) {

            $yhteys = connect();
            add_row_to_table("osoitelista", $yhteys);
            close($yhteys);
        }

        //Jos arvoja ei ole tullut, näytetään pelkkä lomake
        else {
            ?>

            <!--Lomake kutsuu tätä sivua eli ylläolevaa PHP-skriptiä-->
            <b>Lisää tietue osoitelistaan</b> 
            <form name="address" method="post" 
                  action="<?php echo ($_SERVER['PHP_SELF']); ?>">

                <table border="0" cellspacing="0" cellpadding="2">
                    <tr> 
                        <td>Sukunimi:</td>
                        <td><input type="text" name="lname" size="40"></td>
                    </tr>
                    <tr> 
                        <td>Etunimi: </td>
                        <td><input type="text" name="fname" size="40"></td>
                    </tr>
                    <tr> 
                        <td>Sähköposti:</td>
                        <td><input type="text" name="email" size="40"></td>
                    </tr>
                    <tr>
                        <td>Osoite:</td>
                        <td><input type="text" name="address" size="40"></td>
                    </tr>
                    <tr> 
                        <td></td>
                        <td><div align="right">
                                <input type="submit" name="submit" value="Lähetä"><input 
                                    type="submit" name="cancel" value="Poistu"></div></td>
                    </tr>
                </table>
            </form>

            <?php           
        }
        ?>
    </body>
</html>
