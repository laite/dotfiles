/* simple JS to toggle visibility of main menu */

function Toggle(id)
{
	var currentState = document.getElementById(id);
	currentState.style.display = (currentState.style.display == "none") ? "block" : "none";
}
