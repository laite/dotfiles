/*										
 * harkka.cpp	
 * 
 * Jonosimulaatio
 * tietorakenteet ja algoritmit 2013
 * 
 */

#include "harkka.h"

Statistiikka tilastot;

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

void Kauppa::TallennaAsiakasLuvut()
{
	std::vector <unsigned> kierrosMaara;

	for (palvelupisteIter ppIter = palveluPisteet.begin(); ppIter != palveluPisteet.end(); ++ppIter)
	{
		unsigned asiakkaitaJonossa = (*ppIter).AsiakkaitaJonossa();
		kierrosMaara.push_back(asiakkaitaJonossa);
	}

	tilastot.asiakkaitaJonossa.push_back(kierrosMaara);
}

void Kauppa::UusiAsiakas()
{
	// Uusi asiakas valitsee aina lyhimmän jonon
	unsigned jonoID = this->AnnaLyhinJono();

	// LisaaAsiakasJonoon luo uuden Asiakas-luokan kappaleen
	palveluPisteet.at(jonoID).LisaaAsiakasJonoon();
}

void Kauppa::TarkistaAsiakkaat()
{
	for (palvelupisteIter ppIter = palveluPisteet.begin(); ppIter != palveluPisteet.end(); ++ppIter)
		(*ppIter).KasitteleAsiakkaat();
}

void Kauppa::TarkistaOstostapahtumat()
{
	for (palvelupisteIter ppIter = palveluPisteet.begin(); ppIter != palveluPisteet.end(); ++ppIter)
	{
		if (rand()%100 < (*ppIter).GetPatevyys())
		{
			(*ppIter).PoistaAsiakas();
			++tilastot.asiakkaitaYhteensa;
		}
	}
}

/*
 *
 * Palvelupiste class
 *
 */

Palvelupiste::Palvelupiste(int num)
	: ID(num) 
{ 
	patevyys = PATEVYYS_MIN+rand()%(1+(PATEVYYS_MAX-PATEVYYS_MIN));
	tilastot.myyjienPatevyydet.push_back(patevyys);
}

void Palvelupiste::PoistaAsiakas()
{
	if (asiakkaat.size() == 0)
		return;

	tilastot.odotusAjat.push_back(asiakkaat.at(0).GetOdotusaika());

	asiakkaat.erase(asiakkaat.begin());
	//std::cout << "Asiakas jonossa " << ID << " suoritti ostoksensa." << std::endl;
}

void Palvelupiste::KasitteleAsiakkaat()
{
	if (asiakkaat.size() == 0)
		return;

	std::vector<Asiakas> edelleenJonossa;

	unsigned ihmisiaEdella = 0;
	for (std::vector<Asiakas>::iterator asiakasIter = asiakkaat.begin(); asiakasIter != asiakkaat.end(); ++asiakasIter)
	{
		(*asiakasIter).LisaaOdotusaikaa();

		// Asiakkaan sietokyky laskee sitä enemmän, mitä enemmän hänen edessään on ihmisiä
		(*asiakasIter).LaskeSietokykya(rand()%(ihmisiaEdella+1));
		if ((*asiakasIter).GetSietokyky() < 0)
		{
			//std::cout << "Asiakas jonossa " << ID << " kyllästyi odottamaan (odotti " << (*asiakasIter).GetOdotusaika() << " sykliä)!" << std::endl;
			++tilastot.poistunutAsiakas;
			tilastot.poistuneidenOdotusAjat.push_back((*asiakasIter).GetOdotusaika());
		}
		else
			edelleenJonossa.push_back(*asiakasIter);

		++ihmisiaEdella;
	}

	asiakkaat = edelleenJonossa;
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
		std::vector<unsigned> asiakkaatKierroksella = tilastot.asiakkaitaJonossa.at(a);
		int yhteensa = 0;

		for (int i = 0; i != PALVELUPISTEET; ++i)
		{
			yhteensa += asiakkaatKierroksella.at(i);
			if (asiakkaatKierroksella.at(i) > maxJono)
				maxJono = asiakkaatKierroksella.at(i);

			os << asiakkaatKierroksella.at(i) << "\t";
		}

		if (yhteensa > maxTotal)
			maxTotal = yhteensa;

		os << std::endl;
	}

	unsigned asiakkaita = 0;
	double keskiOdotus = 0, poistuneidenKeskiOdotus = 0;

	for (std::vector<unsigned>::const_iterator iter = tilastot.poistuneidenOdotusAjat.begin();
			iter != tilastot.poistuneidenOdotusAjat.end(); ++iter)
	{
		poistuneidenKeskiOdotus += *iter;
	}

	for (std::vector<unsigned>::const_iterator iter = tilastot.odotusAjat.begin();
			iter != tilastot.odotusAjat.end(); ++iter)
	{
		keskiOdotus += *iter;
		++asiakkaita;
	}

	keskiOdotus /= asiakkaita;
	poistuneidenKeskiOdotus /= asiakkaita;

	// just print these to console
	std::cout << "Kokonaisaika:           " << KOKONAISAIKA << std::endl;
	std::cout << "Palvelupisteitä:        " << PALVELUPISTEET << std::endl;

	std::cout << "Myyjien pätevyydet:     ";

	for (std::vector<unsigned>::const_iterator myyjaIter = tilastot.myyjienPatevyydet.begin();
			myyjaIter != tilastot.myyjienPatevyydet.end(); ++myyjaIter)
	{
		std::cout << *myyjaIter << " ";
	}
	std::cout << std::endl;

	std::cout << "Suurin asiakasmäärä:    " << maxTotal << std::endl;
	std::cout << "Pisin jono:             " << maxJono << std::endl;
	std::cout << "Ostoksia yhteensä:      " << tilastot.asiakkaitaYhteensa << std::endl;
	std::cout << "Keskimääräinen odotus:  " << keskiOdotus << std::endl;
	std::cout << "Poistuneita asiakkaita: " << tilastot.poistunutAsiakas << " (keskimääräinen odotus: " << poistuneidenKeskiOdotus << ")"<< std::endl;
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

		r_kioski.TarkistaAsiakkaat();

		if (rand()%100 < UUSI_ASIAKAS)
			r_kioski.UusiAsiakas();

		r_kioski.TallennaAsiakasLuvut();
	}

	std::ofstream file(OUTPUT_FILE);
	dump_output(file, r_kioski);
	file.close();

	return 0;
}
