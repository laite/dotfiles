/* lastmod.js											*
 * writes the last modification - time/date on document */

function author() {
	return "Markus Klinga";
}

// read and return the modification date of a file
function lastModified() {
  // assign date to variable ModifyDate and cast it into a string showAs
  var ModifyDate = new Date(document.lastModified)
  var showAs = ModifyDate.getDate() + "." + (ModifyDate.getMonth() + 1) + "." + ModifyDate.getFullYear() + " " + ModifyDate.getHours() + ":" + ModifyDate.getMinutes()

  // return value of showAs
  return showAs
}

// write the result of lastModified function to HTML document
document.write ("Last modified by " + author() + " at " + lastModified());
