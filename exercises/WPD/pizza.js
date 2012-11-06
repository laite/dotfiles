/* pizza.js												*
 * handles all pizza ordering form - related jscripts 	*/

var globalMessage = "Press <em>order</em> to confirm your pizza request!";
var onTheWay = "Your pizza is on the making!";

// we confirm user once if (s)he's sure - liability, you see :)
function pizzaSubmit()
{
	var confirmation = confirm("Are you sure you have selected the pizza you like?");
	var submitMessage = globalMessage;
	if (confirmation == true)
	{
		submitMessage = onTheWay;
	}

	document.getElementById("pizzaStatus").innerHTML=submitMessage
}

// return globalMessage to "statusbox"
function pizzaReset()
{
	document.getElementById("pizzaStatus").innerHTML=globalMessage;
}
