/*										
 * harkka.h	
 * 
 * Jonosimulaatio
 * tietorakenteet ja algoritmit 2013
 * 
 */

#ifndef HARKKA_H
#define HARKKA_H

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include <fstream>

// tiedosto johon kierrostiedot puretaan
const char *OUTPUT_FILE = "dump.txt";


/*
 *  Skenaarion muuttujat
 */


// palvelupisteiden (jonojen) määrä kaupassa
const int PALVELUPISTEET = 1;

// kokonaisaika (kierrosta, ~10s reaaliaikaa)
const int KOKONAISAIKA = 360;

// todennäköisyys että uusi asiakas tulee kauppaan (/100)
const double UUSI_ASIAKAS = 50;

// Myyjien todennäköisyys suoritetulle ostotapahtumalle
const int PATEVYYS_MIN = 25;
const int PATEVYYS_MAX = 50;

// Asiakkaiden sietokyky
// Mikäli sietokyky laskee alle nollan, asiakas poistuu paikalta
const int SIETOKYKY_MIN = 10;
const int SIETOKYKY_MAX = 100;


/*
 *  Luokat
 */


class Statistiikka 
{
	public:

		Statistiikka(): ostanutAsiakas(0), asiakkaitaYhteensa(0), poistunutAsiakas(0) { }

		// kaikki sisään tulleet asiakkaat
		unsigned asiakkaitaYhteensa;

		// asiakkaat, jotka suorittivat ostoksen
		unsigned ostanutAsiakas;

		// odottamaan kyllästyneiden asiakkaiden määrä
		unsigned poistunutAsiakas;

		// poistuneiden asiakkaiden odotusaika
		std::vector<unsigned> poistuneidenOdotusAjat;

		// asiakkaiden jonossa kuluttama aika, tallennetaan kun asiakas pääsee kassalta
		std::vector<unsigned> odotusAjat;

		std::vector< std::vector<unsigned> > asiakkaitaJonossa;

		// Myyjien pätevyydet
		std::vector<unsigned> myyjienPatevyydet;
};

class Asiakas 
{
	public:

		Asiakas(): odotusaika(0) { sietokyky = SIETOKYKY_MIN+rand()%(1+(SIETOKYKY_MAX-SIETOKYKY_MIN)); }

		const int GetSietokyky() const { return sietokyky; }
		const unsigned GetOdotusaika() const { return odotusaika; }

		void LaskeSietokykya(unsigned lasku) { sietokyky -= lasku; }
		void LisaaOdotusaikaa() { ++odotusaika; }

	private:

		int sietokyky; 
		unsigned odotusaika;
};

class Palvelupiste 
{
	public:

		Palvelupiste(int num);

		const int GetID() const { return ID; }

		const int GetPatevyys() { return patevyys; }

		void LisaaAsiakasJonoon() { asiakkaat.push_back(Asiakas()); }
		void PoistaAsiakas();
		unsigned int AsiakkaitaJonossa() { return asiakkaat.size(); }

		void KasitteleAsiakkaat();

	private:

		int ID;

		// todennakoisyys sille, että ostos tulee suoritettua (/100)
		int patevyys;

		std::vector<Asiakas> asiakkaat;
		
};

class Kauppa 
{
	public:

		typedef std::vector<Palvelupiste>::iterator palvelupisteIter;

		Kauppa();

		unsigned AnnaLyhinJono();

		std::vector<unsigned> AsiakkaitaJonoissa();

		void UusiAsiakas();
		void TarkistaOstostapahtumat();

		void TarkistaAsiakkaat();
		void TallennaAsiakasLuvut();

	private:

		std::vector<Palvelupiste> palveluPisteet;
};

#endif /* end HARKKA_H */
