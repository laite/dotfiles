
/********************************************
 * js/visibility.js							*
 * Contains javascript for toggling 		*
 * visibility of TOC items					*
 * in WPD exercises/TOC-page				*
 *											*
 * (c) Markus Klinga 2012					*
 *											*
 ********************************************/


function Toggle(id)
{
	var currentState = document.getElementById(id);
	currentState.style.display = (currentState.style.display == "none") ? "block" : "none";
}
