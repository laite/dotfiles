
/*      
 * The game is called Twentyone.
 * 
 * 1. Player takes two cards
 * 2. Dealer asks if player takes more cards.
 * 3. If player says yes, dealer gives one card, if player says no, dealer
 * shows the cards of player.
 * 4. if player has under 21 points, dealer tries to take so many cards that
 * sum of the cards is bigger than players points but not more than 21
 * 
 * - If player has 21 points, player wins - if player has over 21 points
 * he loses - if dealer has over 21 points, player wins - if player
 * points > dealer points, player wins. if dealer points > player points, 
 * dealer wins.
 */

/*
 * Try this little text based Java game in NetBeans. Then Rewrite the game in Javascript. 
 * The JS game must work in browser. You can reuse this Java code, because Java and JS 
 * resemble each other quite much. Comment all things that are different
 * in Javascript compared to Java. Tip: You can use prompt() to text input
 * in Javascript.
 *
 */


// Huom! Javascriptin kanssa on *ehdottoman* suositeltavaa käyttää K&A - tyyliä aaltosulkujen suhteen!

// ei tarvita
// import java.util.Scanner;

// ei tarvitse olla 'pääluokkaa'
// public class TwentyOne {

// ei tarvita lukijaa
// private static Scanner reader = new Scanner(System.in);

// muutetaan luokkamäärite funktioksi 
// functio palauttaa 
// * tosi, jos pelaaja voittaa
// * epätosi, jos jakaja voittaa
function TwentyOne() {
	// int => var
	var firstCard = drawNumber(1, 13);
	// tulostetaan näytölle apufunktiolla kirjoita()
	kirjoita("You got the card number " + firstCard + "<br />");

	var secondCard = drawNumber(1, 13);
	kirjoita("You got the card number " + secondCard + "<br />");

	var sum = firstCard + secondCard;

	while (sum < 21) {
		var message = "Sum is " + sum + "\nDo you want to take more cards?";
		// käytämme js:n omaa vahvistus-dialogia käyttäjän pelaamiseen
		var answer = confirm(message);

		if (answer == false) 
			break;

		var newCard = drawNumber(1, 13);
		kirjoita("You got the card number " + newCard + "<br />");
		sum += newCard;
	}
	kirjoita("The sum of your cards is " + sum + "<br />");

	if (sum == 21)
		return true;
	else if (sum > 21)
		return false;

	// käsitellään jakajan tulos seuraavaksi
	var dealer = 0;
	while (sum > dealer) {
		var newCard = drawNumber(1, 13);
		kirjoita("Dealer got the card number " + newCard + "<br />");
		dealer += newCard;
	}
	kirjoita("Dealer got " + dealer + " points.<br />");

	// jos jakaja sai yli 21, pelaaja voittaa
	return (dealer > 21);
}

function drawNumber(smallest, biggest) {
	// lasketaan pyöristetty integer suoraan muuttujaan
	// ja palautetaan se
	var drawedNumber = Math.floor((Math.random()*biggest)+smallest);
	return drawedNumber;
}

function logo(num) {
	// nollataan html-sivu joka kierroksella
	document.getElementById("text_alue").innerHTML = "";
	kirjoita("<h3>Kierros " + num + "</h3>");
}

// apufunktio, selvitään hieman vähemmällä kirjoittamisella
function kirjoita(text) {
	document.getElementById("text_alue").innerHTML += text;
}

function main() {
	var points = 0;
	var games = 0;
	var stillPlaying = true;

	while (stillPlaying) {
		logo(games+1);
		games++;
		var result = TwentyOne();
		if (result == true) {
			kirjoita("<strong>You won!</strong>");
			points++;
		} else {
			kirjoita("<strong>You lost!</strong>");
		}

		stillPlaying = confirm("Do you want to play another game?");
	}

	alert("You won " + points + " out of " + games + " games.");
}
