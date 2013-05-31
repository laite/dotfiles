/*pt_kaytto.js on JavaScript-tiedosto jolla käytetään prototypeä. Tämä on siis yhdistävä tiedosto
  prototypen ja oman sovelluksen välissä*/

/*
   PROTOTYPEN TÄRKEIMMÄT AJAX-LUOKAT:

   Ajax.Request - suorittaa Ajax-pyynnön palvelimelta. 
   Ajax.Response - hakee vastauksen palvelimelta
   Ajax.Updater - suorittaa sekä ajax-pyynnön että hakee vastauksen. Päivitetään Ajaxilla sivun tietty alue kun käyttäjä suorittaa jonkin tapahtuman, esim. syötön lomakkeelle tai linkin painalluksen
   Ajax.PeriodicalUpdater - päivitetään Ajaxilla sivun tietty alue aina tietyin väliajoin. Aika annetaan parametrina sekunneissa. Ei siis vaadi käyttäjän toimenpiteitä.

   Eniten käytetty noista on Ajax.Updater
   Ajax.Updaterin käyttö:

   var MyAjax = new Ajax.Updater(kohde (id), lähdetiedosto (url), {method: 'post tai get', parameters: välitettävät parametrit});

*/

/*updatePage päivittää div-elementin (id=dbdata) sisällä olevan alueen.
  $F() on  prototypen funktio jolla otetaan lomakkeelta arvo. Se otetaan
  muuttujaan nimi.
  escape -funktio muuttaa saadun arvon url-enkoodattuun muotoon tiedon 
  lähetystä varten.
  */
function updatePage(){

	// tallennetaan tulokset div:iin, jonka id on "page_area"
	var target = 'page_area';
	var url = 'getPage.php';
	var pars = 'hakusana='+escape(document.getElementById("hakusana").value);

	var myAjax = new Ajax.Updater(target, url, {method: 'get', parameters: pars});
}
