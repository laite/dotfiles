/* pizza.js												*
 * handles all pizza ordering form - related jscripts 	*/

// "const" variables
var kSuccessColor = "#0f0";
var kGlobalMessage = "Press <em>order</em> to confirm your pizza request.";
var kOnTheWay = "<span style=\"color:" + kSuccessColor + "\">Your pizza is on the way!</span>";

// we confirm user once if (s)he's sure - liability, you see :)
function pizzaSubmit()
{
	var submitMessage = confirm("Are you sure you have selected the pizza you like?")? kOnTheWay : kGlobalMessage;

	document.getElementById("pizzaStatus").innerHTML=submitMessage;
}

// return globalMessage to "statusbox"
function pizzaReset()
{
	document.getElementById("pizzaStatus").innerHTML=kGlobalMessage;
}

function showSliderValue(x) 
{
	var amount;

	switch(x)
	{
		case "1":
		case "2":
		case "3":
			amount = "little";
			break;
		case "4":
		case "5":
			amount = "properly";
			break;
		case "6":
		case "7":
			amount = "quite much";
			break;
		case "8":
		case "9":
			amount = "tremendously";
			break;
		case "10":
			amount = "more than you can eat";
			break;
		default:
			amount = " *WARNING*: this should be impossible!";
	}	

	document.getElementById("stuffingAmount").innerHTML = amount + " (" + x + ")";
}

function myFunction()
{
	var x;
	var r=confirm("Press a button!");

	if (r==true)
	{
		x="You pressed OK!";
	}
	else
	{
		x="You pressed Cancel!";
	}

	document.getElementById("pizzaStatus").innerHTML=x;
}
