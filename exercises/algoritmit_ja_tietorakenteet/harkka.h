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

const int PATEVYYS_MIN = 2;
const int PATEVYYS_MAX = 15;

class Asiakas 
{
	public:

		Asiakas() { sietokyky = 10+rand()%50; std::cout << "Uusi asiakas! Sietokyky: " << sietokyky << std::endl; }

		const int GetSietokyky() const { return sietokyky; }

		void LaskeSietokykya(unsigned);

	private:

		int sietokyky; 
};

class Palvelupiste 
{
	public:

		Palvelupiste(int num): ID(num) { patevyys = PATEVYYS_MIN+rand()%(PATEVYYS_MAX-PATEVYYS_MIN); std::cout << "Uusi myyjä! Pätevyys: " << patevyys << std::endl; }

		const int GetID() const { return ID; }

		const int GetPatevyys() { return patevyys; }

		void LisaaAsiakasJonoon() { asiakkaat.push_back(Asiakas()); std::cout << "Asiakas lisätty jonoon " << ID << std::endl; }
		void PoistaAsiakas();
		unsigned int AsiakkaitaJonossa() { return asiakkaat.size(); }

		void LaskeAsiakkaidenSietokyvyt();

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

		unsigned AsiakkaitaYhteensa();
		std::vector<unsigned> AsiakkaitaJonoissa();

		void UusiAsiakas();
		void TarkistaOstostapahtumat();

		void TarkistaSietokyvyt();
		void TallennaAsiakasLuvut();

		std::vector<unsigned> GetAsiakkaatKierroksella(unsigned index) { return asiakkaatKierroksella.at(index); }

	private:

		std::vector<Palvelupiste> palveluPisteet;
		std::vector< std::vector<unsigned> > asiakkaatKierroksella;
};

#endif /* end HARKKA_H */
