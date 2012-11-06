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
	var dateString = now.toJSON().substring(0,10); //toJSON() returns full date+time, we only need date

	document.getElementById('pizzaDate').min = document.getElementById('pizzaDate').value = dateString;
};
