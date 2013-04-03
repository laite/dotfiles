/*										
 * harkka.cpp	
 * 
 * Jonosimulaatio
 * tietorakenteet ja algoritmit 2013
 * 
 */

#include "harkka.h"

#include <fstream>

// palvelupisteiden (jonojen) määrä kaupassa
const int PALVELUPISTEET = 1;

// todennäköisyydet per kierros (/100)
//const double OSTOS_SUORITETTU = 5;
const double UUSI_ASIAKAS = 50;

// kokonaisaika (kierrosta, ~10s reaaliaikaa)
const int KOKONAISAIKA = 200;

// tiedosto johon kierrostiedot dumpataan
const char *OUTPUT_FILE = "dump.txt";

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

void Kauppa::TallennaAsiakasLuvut()
{
	std::vector <unsigned> kierrosMaara;

	kierrosMaara.push_back(AsiakkaitaYhteensa());
	for (palvelupisteIter ppIter = palveluPisteet.begin(); ppIter != palveluPisteet.end(); ++ppIter)
		kierrosMaara.push_back((*ppIter).AsiakkaitaJonossa());

	asiakkaatKierroksella.push_back(kierrosMaara);
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
		if (rand()%100 < (*ppIter).GetPatevyys())
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

void dump_output(std::ostream &os, Kauppa &kauppa)
{
	int maxTotal = 0, maxJono = 0;

	for (int a = 0; a < KOKONAISAIKA; ++a)
	{
		std::vector<unsigned> asiakkaatKierroksella = kauppa.GetAsiakkaatKierroksella(a);

		if (asiakkaatKierroksella.at(0) > maxTotal)
			maxTotal = asiakkaatKierroksella.at(0);

		os << asiakkaatKierroksella.at(0) << "\t";
		for (int i = 0; i != PALVELUPISTEET; ++i)
		{
			if (asiakkaatKierroksella.at(i+1) > maxJono)
				maxJono = asiakkaatKierroksella.at(i+1);

			os << asiakkaatKierroksella.at(i+1) << "\t";
		}
		os << std::endl;
	}

	// just print these to console
	std::cout << "Kokonaisaika:        " << KOKONAISAIKA << std::endl;
	std::cout << "Suurin asiakasmäärä: " << maxTotal << std::endl;
	std::cout << "Pisin jono:          " << maxJono << std::endl;
}

int main(int argc, char **argv)
{
	srand(time(NULL));

	Kauppa r_kioski;
	std::vector<unsigned> asiakkaatKierroksella;

	int t = 0;
	while (++t <= KOKONAISAIKA)
	{
		r_kioski.TarkistaOstostapahtumat();

		r_kioski.TarkistaSietokyvyt();

		if (rand()%100 < UUSI_ASIAKAS)
			r_kioski.UusiAsiakas();

		r_kioski.TallennaAsiakasLuvut();
	}

	std::ofstream file(OUTPUT_FILE);
	dump_output(file, r_kioski);
	file.close();

	return 0;
}
