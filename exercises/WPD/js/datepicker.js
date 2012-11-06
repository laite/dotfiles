/* datepicker.js										*
 * set current date to input date picker on site load 	*/

function zeroPad(num, places) {
  var zero = places - num.toString().length + 1;
  return Array(+(zero > 0 && zero)).join("0") + num;
}

// anonymous function to set current date in pizzabox
window.onload = function()
{
	var now = new Date(); 
	var dateString = now.getFullYear() + '-' + zeroPad((now.getMonth()+1),2) + '-' + zeroPad(now.getDate(),2);

	document.getElementById('pizzaDate').value = dateString;
	document.getElementById('pizzaDate').min = dateString;
};
