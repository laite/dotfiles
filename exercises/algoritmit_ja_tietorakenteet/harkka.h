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

		Palvelupiste(int num): ID(num) { }

		const int GetID() const { return ID; }

		void LisaaAsiakasJonoon() { asiakkaat.push_back(Asiakas()); std::cout << "Asiakas lisätty jonoon " << ID << std::endl; }
		void PoistaAsiakas();
		unsigned int AsiakkaitaJonossa() { return asiakkaat.size(); }

		void LaskeAsiakkaidenSietokyvyt();

	private:

		int ID;

		std::vector<Asiakas> asiakkaat;
		
};

class Kauppa 
{
	public:

		typedef std::vector<Palvelupiste>::iterator palvelupisteIter;

		Kauppa();

		unsigned AnnaLyhinJono();

		unsigned AsiakkaitaYhteensa();

		void UusiAsiakas();
		void TarkistaOstostapahtumat();

		void TarkistaSietokyvyt();

	private:

		std::vector<Palvelupiste> palveluPisteet;
};

#endif /* end HARKKA_H */
