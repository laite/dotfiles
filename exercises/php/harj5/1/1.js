
function tarkasta()
{
	/* Nimi ok, sitten tarkastataan
	 * 1. että sähköposti-osoite ei ole tyhjä */
	var osoite=document.forms["keltainen_lomake"]["osoite"].value;
	if (osoite==null || osoite=="")
	{
		alert("Kirjoita osoitteesi!");
		return false;
	}
	/* 2. että se on kirjoitettu kelvolliseen muotoon */
	else
	{
		var at_position = osoite.indexOf("@");
		var dot_position = osoite.indexOf(".");
		if (at_position < 1 || dot_position < at_position + 2 || dot_position+2 >= osoite.length)
		{
			alert("Kelvoton osoite!");
			return false;
		}
	}

	/* Sukupuoli on radio-button, joten sitä ei voida tarkastaa samalla 
	 * tavoin kuin pelkkiä tekstikenttiä */
	var sukupuoli_radio = document.forms["keltainen_lomake"]["sukupuoli"];
	var sukupuoli_valid = false;

	/* Käydään jokainen radio-nappi läpi ja tarkastetaan onko se valittuna */
	for (var i = 0; i < sukupuoli_radio.length; i++)
	{
		/* Jos nappi on valittuna, asetetaan sukupuoli_valid muuttuja */
		if (sukupuoli_radio[i].type === 'radio' && sukupuoli_radio[i].checked)
			sukupuoli_valid = true;
	}

	/* Jos mikään ei ollut valittuna, annetaan virhe */
	if (!sukupuoli_valid)
	{
		alert("Valitse sukupuolesi!");
		return false;
	}

	/* Viimeiseksi tarkastetaan select-boksi
	 * .value antaa vain ensimmäisen valitun (monivalinta on mahdollista),
	 * mutta se ei kiinnosta meitä tässä vaiheessa sillä emme tee arvo(i)lla mitään */
	var uskonto = document.forms["keltainen_lomake"]["uskonto"].value;
	if (uskonto==null || uskonto=="")
	{
		alert("Valitse ainakin uskonto!");
		return false;
	}
}
