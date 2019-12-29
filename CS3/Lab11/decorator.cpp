// decorator pattern illustration using HTML 
// Mikhail Nesterenko
// 10/31/2019

#include <string>
#include <iostream>

using std::cout; using std::endl;
using std::string;

enum class DrinkType { small, medium, large };

class Drink {
public:
	Drink(DrinkType type = small, price = 0) :
		type_(type), price_(price) {}
	virtual int getPrice() const;
	virtual std::string getName() const;
	std::string getCustomer() const { return customer };
	void setCustomer(string name) { customer_ = name; }
private:
	int price_;
	DrinkType type_;
	std::string customer_;
};

int Drink::getPrice() const {
	if (type_ == DrinkType::small)
		return 1;
	else if (type_ == DrinkType::medium)
		return 2;
	else
		return 3;
}

std::string Drink::getName() const {
	return "";
}


// Sprinkles decorator
class Sprinkles : public Drink {
public:
	Sprinkles (const Drink* wrapped) :
		wrapped_(wrapped) {}
	double getPrice() const override { return 0.50 + wrapped_->getPrice(); }
	string getName() const override { return "Sprinkles " + wrapped_->getName(); }
private:
	const Drink *wrapped_;
};


// Caramel decorator
class Caramel : public Drink {
public:
	Caramel(const Drink* wrapped) :
		wrapped_(wrapped) {}
	double getPrice() const override { return 0.20 + wrapped_->getPrice(); }
	string getName() const override { return "Caramel " + wrapped_->getName(); }
private:
	const Drink *wrapped_;
};

// Foam decorator
class Foam : public Drink {
public:
	Foam(const Drink* wrapped) :
		wrapped_(wrapped) {}
	double getPrice() const override { return 0.40 + wrapped_->getPrice(); }
	string getName() const override { return "Foam " + wrapped_->getName(); }
private:
	const Drink *wrapped_;
};

// Ice decorator
class Ice : public Drink {
public:
	Ice(const Drink* wrapped) :
		wrapped_(wrapped) {}
	double getPrice() const override { return 0.10 + wrapped_->getPrice(); }
	string getName() const override { return "Ice " + wrapped_->getName(); }
private:
	const Drink *wrapped_;
};

int main() {
	std::string userSelection;
	Drink* aDrink;
	cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee?" << endl;
	cin >> userSelection;

	switch (userSelection) {
		case "s":
			aDrink = Drink(small);
			break;
		case "m":
			aDrink = Drink(medium);
			break;
		case "l":
			aDrink = Drink(large);
			break;
		default:
			aDrink = Drink();
	}

	while (userSelection != "n") {
		cout << "Would you like to add [s]prinkles, [c]aramel, mill [f]oam, [i]ce or [n]ot?";
		std::cin >> userSelection;
		cout << endl;
		switch (userSelection) {
		case "s":
			aDrink = new Sprinkles(aDrink);
			break;
		case "c":
			aDrink = new Caramel(aDrink);
			break;
		case "f":
			aDrink = new Foam(aDrink);
			break;
		case "i":
			aDrink = new Ice(aDrink);
			break;
		case "n":
			break;
		default:
			cout << "Invalid.  Options are [s], [c], [f], [i], [n]" << endl;
		}
	}

	cout << "Can I get your name?";
	std::cin >> userSelection;
	cout << endl;
	aDrink->setCustomer(userSelection);

	cout << aDrink->getCustomer() + ", your" + aDrink->getName() + "is ready." + "It will be " + aDrink->getPrice() + ", please.";

	/*
	Text p("Hello, World!");
	Text q("Good bye, World!");

	cout << p.getHTML() << endl;
	cout << q.getHTML() << endl;

	// illustrates per-object application of decoration
	BoldParagraph bp(&p);
	ItalicParagraph iq(&q);
	cout << bp.getHTML() << endl;
	cout << iq.getHTML() << endl;

	ItalicParagraph iiq(&iq);
	cout << iiq.getHTML() << endl;

	// complex decorators
	BoldParagraph bip(&iq);
	cout << bip.getHTML() << endl;

	ItalicParagraph ibp(&bp);
	cout << ibp.getHTML() << endl;

	// dynamic decorator
	cout << BoldParagraph(&p).getHTML() << endl;


	// dynamic complex decorator
	cout << BoldParagraph(new ItalicParagraph(&bp)).getHTML() << endl;
	cout << ItalicParagraph(&bp).getHTML() << endl;
	*/
}