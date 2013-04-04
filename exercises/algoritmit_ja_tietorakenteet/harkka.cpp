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
	// Luodaan palvelupisteet
	// Jonoja luodaan joko 1 tai yhtä monta kuin palvelupisteitä on
	// muuttuja: VAIN_YKSI_JONO 
	for (int i = 0; i < PALVELUPISTEET; ++i)
	{
		if ((i==0) || (!VAIN_YKSI_JONO))
			jonot.push_back(new Jono());

		palveluPisteet.push_back(Palvelupiste(i, jonot.at(jonot.size()-1)));
	}
}

Kauppa::~Kauppa()
{
	// delete allocated jono pointers
	for (std::vector<Jono*>::iterator iter = jonot.begin(); iter != jonot.end(); ++iter)
		delete *iter;
}

unsigned Kauppa::AnnaLyhinJono()
{
	if (palveluPisteet.size() < 1)
		throw std::runtime_error("Ei ainuttakaan palvelupistettä!");

	unsigned palvelupisteID;
	int asiakasmaara = -1;

	// jos vain yksi jono, palautetaan se välittömästi
	if (jonot.size() == 1)
		return (*palveluPisteet.begin()).GetID();

	// muussa tapauksessa etsitään lyhin
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

		if (VAIN_YKSI_JONO)
			break;
	}

	// tallennetaan tilastoihin vektori, jossa on kunkin jonon asiakasmäärät
	tilastot.asiakkaitaJonossa.push_back(kierrosMaara);
}

void Kauppa::UusiAsiakas()
{
	// Uusi asiakas valitsee aina lyhimmän jonon
	unsigned jonoID = this->AnnaLyhinJono();

	// LisaaAsiakasJonoon luo uuden Asiakas-luokan kappaleen
	palveluPisteet.at(jonoID).LisaaAsiakasJonoon();

	++tilastot.asiakkaitaYhteensa;
}

void Kauppa::TarkistaAsiakkaat()
{
	// jos on vain yksi jono, käsitellään asiakkaat vain ensimmäisen palvelupisteen kautta
	if (VAIN_YKSI_JONO)
	{
		(*palveluPisteet.begin()).KasitteleAsiakkaat();
		return;
	}

	// muussa tapauksessa käydään jokainen jono yksitellen läpi
	for (palvelupisteIter ppIter = palveluPisteet.begin(); ppIter != palveluPisteet.end(); ++ppIter)
		(*ppIter).KasitteleAsiakkaat();
}

void Kauppa::TarkistaOstostapahtumat()
{
	for (palvelupisteIter ppIter = palveluPisteet.begin(); ppIter != palveluPisteet.end(); ++ppIter)
	{
		// käydään kaikki palvelupisteet lävitse ja katsotaan tuliko tapahtuma suoritettua
		if (((*ppIter).AsiakkaitaJonossa() > 0) && (rand()%100 < (*ppIter).GetPatevyys()))
		{
			// mikäli tuli, poistetaan asiakas jonosta ja tilastoidaan
			(*ppIter).PoistaAsiakas();
			++tilastot.ostanutAsiakas;
		}
	}
}


/*
 *
 * Palvelupiste class
 *
 */


Palvelupiste::Palvelupiste(int num, Jono *j)
	: ID(num) 
	, jono(j)
{ 
	patevyys = PATEVYYS_MIN+rand()%(1+(PATEVYYS_MAX-PATEVYYS_MIN));
	tilastot.myyjienPatevyydet.push_back(patevyys);
}


/*
 *  Jono class
 */


void Jono::PoistaAsiakas()
{
	if (asiakkaat.size() == 0)
		return;

	tilastot.odotusAjat.push_back(asiakkaat.at(0).GetOdotusaika());

	// poistetaan asiakas vektorin alusta, uudet asiakkaat tulevat aina vektorin perään
	asiakkaat.erase(asiakkaat.begin());
}

void Jono::KasitteleAsiakkaat()
{
	if (asiakkaat.size() == 0)
		return;

	std::vector<Asiakas> edelleenJonossa;

	unsigned ihmisiaEdella = 0;
	
	// luuppi käy jonon asiakkaat läpi alusta loppuun päin, jolloin jokaisen kohdalla edellä
	// olevien asiakkaiden määrä nousee yhdellä
	for (std::vector<Asiakas>::iterator asiakasIter = asiakkaat.begin(); asiakasIter != asiakkaat.end(); ++asiakasIter)
	{
		(*asiakasIter).LisaaOdotusaikaa();

		// Asiakkaan sietokyky laskee sitä enemmän, mitä enemmän hänen edessään on ihmisiä
		(*asiakasIter).LaskeSietokykya(rand()%(ihmisiaEdella+1));
		if ((*asiakasIter).GetSietokyky() < 0)
		{
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

			if (VAIN_YKSI_JONO)
				break;
		}

		if (yhteensa > maxTotal)
			maxTotal = yhteensa;

		os << std::endl;
	}

	unsigned asiakkaita = tilastot.odotusAjat.size();
	unsigned poistuneitaAsiakkaita = tilastot.poistuneidenOdotusAjat.size();
	double keskiOdotus = 0, poistuneidenKeskiOdotus = 0;

	for (std::vector<unsigned>::const_iterator iter = tilastot.poistuneidenOdotusAjat.begin();
			iter != tilastot.poistuneidenOdotusAjat.end(); ++iter) {
		poistuneidenKeskiOdotus += *iter;
	}

	for (std::vector<unsigned>::const_iterator iter = tilastot.odotusAjat.begin();
			iter != tilastot.odotusAjat.end(); ++iter) {
		keskiOdotus += *iter;
	}

	if (asiakkaita > 0)
		keskiOdotus /= asiakkaita;
	if (poistuneitaAsiakkaita > 0)
		poistuneidenKeskiOdotus /= poistuneitaAsiakkaita;

	os << "Kokonaisaika:\t" << KOKONAISAIKA << std::endl;
	os << "Palvelupisteitä:\t" << PALVELUPISTEET << std::endl;
	os << "Jonoja:\t" << ((VAIN_YKSI_JONO)? 1 : PALVELUPISTEET) << std::endl;

	os << "Myyjien pätevyydet:\t";

	for (std::vector<unsigned>::const_iterator myyjaIter = tilastot.myyjienPatevyydet.begin();
			myyjaIter != tilastot.myyjienPatevyydet.end(); ++myyjaIter)
	{
		os << *myyjaIter << " ";
	}
	os << std::endl;

	os << "Suurin asiakasmäärä:\t" << maxTotal << std::endl;
	os << "Pisin jono:\t" << maxJono << std::endl;
	os << "Asiakkaita yhteensä:\t" << tilastot.asiakkaitaYhteensa << " (kaupassa vielä: " << (tilastot.asiakkaitaYhteensa-(tilastot.ostanutAsiakas+tilastot.poistunutAsiakas)) << ")" << std::endl;
	os << "Ostoksia yhteensä:\t" << tilastot.ostanutAsiakas << std::endl;
	os << "Keskimääräinen odotus:\t" << keskiOdotus << std::endl;
	os << "Kyllästyneitä:\t" << tilastot.poistunutAsiakas << " (keskimääräinen odotus: " << poistuneidenKeskiOdotus << ")"<< std::endl;
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
