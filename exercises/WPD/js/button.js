/* button.js											*
 * Leave the page on a new window, try to resize it 	*/

var popupWindow;
var t;

function resizeWindow()
{
	if (typeof popupWindow == 'undefined')
	{
		alert("No popup window spawned yet!");
	}
	else
	{
		popupWindow.resizeTo(1200,600);
	}
}

function goSomewhereElse(where)
{
	// if there's nowhere to go, we'll use our own page as default
	where = typeof where !== 'undefined' ? where : 'http://batman.jamk.fi/~g8270/index.html';

	popupWindow = window.open(where, '', 'width=500,height=500');
}

function mypopup()
{
    mywindow = window.open("http://www.javascript-coder.com", "mywindow", "resizable=1,location=1,status=1,scrollbars=1,  width=100,height=100");
    mywindow.moveTo(700, 400);
}
