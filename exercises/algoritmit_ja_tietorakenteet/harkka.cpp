/*										
 * harkka.cpp	
 * 
 * Jonosimulaatio
 * tietorakenteet ja algoritmit 2013
 * 
 */

#include "harkka.h"

// palvelupisteiden (jonojen) määrä kaupassa
const int PALVELUPISTEET = 1;

// todennäköisyydet per kierros (/100)
const double OSTOS_SUORITETTU = 8;
const double UUSI_ASIAKAS = 20;

// kokonaisaika (kierrosta, ~10s reaaliaikaa)
const int KOKONAISAIKA = 100;

/*
 *
 *  Kauppa class
 *
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

	unsigned palvelupisteID;
	int asiakasmaara = -1;

	for (palvelupisteIter ppIter = palveluPisteet.begin(); ppIter != palveluPisteet.end(); ++ppIter)
	{
		if (((*ppIter).AsiakkaitaJonossa() < asiakasmaara) || (asiakasmaara == -1))
		{
			asiakasmaara = (*ppIter).AsiakkaitaJonossa();
			palvelupisteID = (*ppIter).GetID();
		}

	}
	return palvelupisteID;
}

unsigned Kauppa::AsiakkaitaYhteensa()
{
	unsigned asiakkaita = 0;
	for (palvelupisteIter ppIter = palveluPisteet.begin(); ppIter != palveluPisteet.end(); ++ppIter)
		asiakkaita += (*ppIter).AsiakkaitaJonossa();

	return asiakkaita;
}

void Kauppa::UusiAsiakas()
{
	// Uusi asiakas valitsee aina lyhimmän jonon
	unsigned jonoID = this->AnnaLyhinJono();

	palveluPisteet.at(jonoID).LisaaAsiakasJonoon();
}

void Kauppa::TarkistaSietokyvyt()
{
	for (palvelupisteIter ppIter = palveluPisteet.begin(); ppIter != palveluPisteet.end(); ++ppIter)
		(*ppIter).LaskeAsiakkaidenSietokyvyt();
}

void Kauppa::TarkistaOstostapahtumat()
{
	for (palvelupisteIter ppIter = palveluPisteet.begin(); ppIter != palveluPisteet.end(); ++ppIter)
	{
		if (rand()%100 < OSTOS_SUORITETTU)
			(*ppIter).PoistaAsiakas();
	}
}

/*
 *
 * Palvelupiste class
 *
 */

void Palvelupiste::PoistaAsiakas()
{
	if (asiakkaat.size() == 0)
		return;

	asiakkaat.erase(asiakkaat.begin());
	std::cout << "Asiakas jonossa " << ID << " suoritti ostoksensa." << std::endl;
}

void Palvelupiste::LaskeAsiakkaidenSietokyvyt()
{
	if (asiakkaat.size() == 0)
		return;

	std::vector<Asiakas> edelleenJonossa;

	for (std::vector<Asiakas>::iterator asiakasIter = asiakkaat.begin(); asiakasIter != asiakkaat.end(); ++asiakasIter)
	{
		// Asiakkaan sietokyky laskee sitä enemmän, mitä enemmän jonossa on ihmisiä
		(*asiakasIter).LaskeSietokykya(rand()%(this->AsiakkaitaJonossa()));
		if ((*asiakasIter).GetSietokyky() < 0)
			std::cout << "Asiakas jonossa " << ID << " kyllästyi odottamaan!" << std::endl;
		else
			edelleenJonossa.push_back(*asiakasIter);
	}

	asiakkaat = edelleenJonossa;
}

/*
 *
 * Asiakas Class
 *
 */

void Asiakas::LaskeSietokykya(unsigned lasku)
{
	sietokyky -= lasku;
}

/* 
 *
 * Main Function
 *
 */

int main(int argc, char **argv)
{
	srand(time(NULL));

	Kauppa r_kioski;

	int t = 0;
	while (++t != KOKONAISAIKA)
	{
		r_kioski.TarkistaOstostapahtumat();

		r_kioski.TarkistaSietokyvyt();

		if (rand()%100 < UUSI_ASIAKAS)
			r_kioski.UusiAsiakas();

		std::cout << "Kierros " << t << ": " << r_kioski.AsiakkaitaYhteensa() << " asiakasta." << std::endl;
	}

	return 0;
}
