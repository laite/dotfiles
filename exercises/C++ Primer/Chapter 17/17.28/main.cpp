// Ex 17.28: multiple inheritance, panda

#include <iostream>
#include <string>

class ZooAnimal 
{
	public:

		ZooAnimal(std::string name): _name(name) { }
		virtual ~ZooAnimal() { }

		virtual void print() { std::cout << "ZooAnimal: " << _name << std::endl; }

	protected:

		std::string _name;
};

class Bear : public ZooAnimal
{
	public:

		Bear(std::string name): ZooAnimal(name) { }
		~Bear() { }

		void print() { std::cout << "Bear: " << _name << std::endl; }
		virtual void stand() { std::cout << "Bear stands up!" << std::endl; }
};

class Endangered
{
	public:

		Endangered(int status): _status(status) { }
		virtual ~Endangered() { }

		virtual void print() = 0;
		virtual void highlight() = 0;

		enum { low, severe, critical };

	protected:

		int _status;
};

class Panda : public Bear, public Endangered 
{
	public:

		Panda(std::string name, int danger_level): Bear(name), Endangered(danger_level) { }
		~Panda() { }

		void print() { std::cout << "Panda: " << _name << std::endl; }
		void highlight() { std::cout << "Danger_level level: " << _status << std::endl; }
		void stand() { std::cout << "Panda stands up!" << std::endl; }
		void cuddle() { std::cout << "Cuddle time!" << std::endl; }
};
int main()
{
	Panda p("Liu", Endangered::critical);
	Bear b("Brrr");
	Bear* bp = &p;

	std::cout << " === Bear b ===" << std::endl;
	b.print();
	b.stand();
	std::cout << " === Panda p ===" << std::endl;
	p.cuddle();
	p.print();
	p.highlight();

	std::cout << " === Bear* bp ===" << std::endl;
	bp->print();
	bp->stand();

	return 0;
}
