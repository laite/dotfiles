
/********************************************
 * D/js/koirakamut.js						*
 * Contains javascript for Koirakamut		*
 *											*
 * (c) Markus Klinga 2012					*
 *											*
 ********************************************/

function Toggle(id)
{
	$(id).slideToggle("slow");
}

function LoginButton()
{
	alert('Valitettavasti käyttäjänimeä sekä/tai salasanaa ei tunnistettu! Oletko varmasti rekisteröitynyt?');
}

function searchDogs()
{
	alert("Haku on valitettavasti tarjolla vain rekisteröityneille käyttäjille!");
}

function CloseInfo(id)
{
	$(id).toggle();
}
