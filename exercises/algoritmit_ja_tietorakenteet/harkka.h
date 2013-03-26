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

		Asiakas() { sietokyky = 20+rand()%100; std::cout << "Uusi asiakas! Sietokyky: " << sietokyky << std::endl; }

	private:

		int sietokyky; 
};

class Palvelupiste 
{
	public:

		Palvelupiste(int num): ID(num) { }

		const int GetID() const { return ID; }

		void LisaaAsiakasJonoon() { asiakkaat.push_back(Asiakas()); std::cout << "Asiakas lisätty jonoon " << ID << std::endl; }
		void PoistaAsiakas() { asiakkaat.erase(asiakkaat.begin()); }
		unsigned int AsiakkaitaJonossa() { return asiakkaat.size(); }

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

		void UusiAsiakas();

	private:

		std::vector<Palvelupiste> palveluPisteet;
};

#endif /* end HARKKA_H */
