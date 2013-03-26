/*										
 * harkka.cpp	
 * 
 * Jonosimulaatio
 * tietorakenteet ja algoritmit 2013
 * 
 */

#include "harkka.h"

const int PALVELUPISTEET = 3;

// todennäköisyydet per kierros
const double OSTOS_SUORITETTU = 0.2; 
const double UUSI_ASIAKAS = 0.2;

/*
 *  Kauppa class
 */

Kauppa::Kauppa()
{
	for (int i = 0; i < PALVELUPISTEET; ++i)
		palveluPisteet.push_back(Palvelupiste(i));
}

unsigned Kauppa::AnnaLyhinJono()
{
	if (palveluPisteet.size() < 1)
		throw std::runtime_error("Ei ainuttakaan palvelupistettä!");

	unsigned palvelupisteID = (*palveluPisteet.begin()).GetID();
	unsigned asiakasmaara = (*palveluPisteet.begin()).AsiakkaitaJonossa();

	for (palvelupisteIter ppIter = palveluPisteet.begin() + 1; ppIter != palveluPisteet.end(); ++ppIter)
	{
		if ((*ppIter).AsiakkaitaJonossa() < asiakasmaara)
		{
			asiakasmaara = (*ppIter).AsiakkaitaJonossa();
			palvelupisteID = (*ppIter).GetID();
		}

	}
	return palvelupisteID;
}

void Kauppa::UusiAsiakas()
{
	// Uusi asiakas valitsee aina lyhimmän jonon
	unsigned jonoID = this->AnnaLyhinJono();

	palveluPisteet.at(jonoID).LisaaAsiakasJonoon();

}

/*
 *  Palvelupiste class
 */



int main(int argc, char **argv)
{
	srand(time(NULL));

	Kauppa r_kioski;

	r_kioski.UusiAsiakas();
	r_kioski.UusiAsiakas();

	std::cout << r_kioski.AnnaLyhinJono() << std::endl;
	r_kioski.UusiAsiakas();
	r_kioski.UusiAsiakas();

	std::cout << r_kioski.AnnaLyhinJono() << std::endl;

	return 0;
}
