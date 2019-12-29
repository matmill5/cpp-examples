// traversing genealogical tree using Composite and Visitors
// Mikhail Nesterenko
// 10/28/2015

// Author: Matthew E. Miller
// Date: 11/15/19

#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::endl; using std::cin;
using std::string;
using std::vector;

class Person { // component
public:
	Person(string firstName, Person *spouse, Person *father, Person *mother) :
		firstName_(firstName), spouse_(spouse), father_(father), mother_(mother) {}
	string getFirstName() { return firstName_; }
	Person *getSpouse() { return spouse_; }
	void setSpouse(Person *spouse) { spouse_ = spouse; }
	Person *getFather() { return father_; }
	Person *getMother() { return mother_; }

	virtual void accept(class PersonVisitor *) = 0;
	virtual ~Person() {}
private:
	string firstName_;
	Person *spouse_;
	Person *father_;
	Person *mother_;
};

// composites

// man has a last name 
class Man : public Person {
public:
	Man(string lastName, string firstName, Person *spouse,
		Person *father, Person *mother) :
		lastName_(lastName), Person(firstName, spouse, father, mother) {}
	string getLastName() { return lastName_; }
	void accept(class PersonVisitor *visitor) override;
private:
	string lastName_;
};

// woman has a list of children
class Woman : public Person {
public:
	Woman(vector<Person *> children,
		string firstName,
		Person *spouse,
		Person *father, Person *mother) :
		children_(children),
		Person(firstName, spouse, father, mother) {}
	const vector<Person *> & getChildren() { return children_; }
	void setChildren(const vector<Person *> &children) { children_ = children; }
	void accept(class PersonVisitor *visitor) override;
private:
	vector<Person *> children_;
};

// abstract visitor
class PersonVisitor {
public:
	virtual void visit(Man*) = 0;
	virtual void visit(Woman*) = 0;
	virtual ~PersonVisitor() {}
};

// composite methods that define traversal
void Man::accept(PersonVisitor *visitor) { visitor->visit(this); }

void Woman::accept(PersonVisitor *visitor) {
	// children traversal through mother only
	// father's children are not traversed so as not 
	// to traverse them twice: for mother and father

	visitor->visit(this);
	// traversing descendants
	for (auto child : children_) child->accept(visitor);
}

// concrete visitors
// the last name for a man is stored in object
// the last name a woman is determined by her 
// spouse if she is married
// or by her father if she is not
class NamePrinter : public PersonVisitor {
public:
	void visit(Man *m) override {
		cout << m->getFirstName() << " " << m->getLastName() << endl;
	}
	void visit(Woman *w) override {
		cout << w->getFirstName() << " ";
		if (w->getSpouse() != nullptr)
			cout << static_cast<Man *>
			(w->getSpouse())->getLastName();
		else if (w->getFather() != nullptr)
			cout << static_cast<Man *>
			(w->getFather())->getLastName();
		else
			cout << "Doe";
		cout << endl;
	}
};


class ChildrenPrinter : public PersonVisitor {
public:
	void visit(Man *m) override {
		cout << m->getFirstName() << ": ";
		Woman *spouse = static_cast<Woman *>(m->getSpouse());
		if (spouse != nullptr)
			printNames(spouse->getChildren());
		cout << endl;
	}
	void visit(Woman *w) override {
		cout << w->getFirstName() << ": ";
		printNames(w->getChildren());
		cout << endl;
	}
private:
	void printNames(const vector<Person *> &children) {
		for (const auto c : children)
			cout << c->getFirstName() << ", ";
	}
};

// Print maiden names
class MaidenPrinter : public PersonVisitor {
public:
	void visit(Man *m) override {
	}
	void visit(Woman *w) override {
		cout << w->getFirstName() << " ";
		if (w->getFather() != nullptr)
			cout << static_cast<Man *>
			(w->getFather())->getLastName();
		else
			cout << "Doe";
		cout << endl;
	}
};

// Check for eligible marriage
class MarriageVisitor : public PersonVisitor {
public:
	MarriageVisitor(Person* one, Person* two) : one_(one), two_(two), oneMarryTwo_(false), twoMarryOne_(false) {}
	void visit(Man *m) override {
		if (m == one_) {
			oneMarryTwo_ = setStatus(two_, one_);
		}
		else if (m == two_) {
			twoMarryOne_ = setStatus(one_, two_);
		}
	}
	void visit(Woman *w) override {
		if (w == one_) {
			oneMarryTwo_ = setStatus(one_, two_);
		}
		if (w == two_) {
			twoMarryOne_ = setStatus(two_, one_);
		}
	}
	bool eligibleMarriage() {
		return oneMarryTwo_ && twoMarryOne_;
	}
	bool isRelated(Person *one, Person *two);
private:
	bool setStatus(Person *one, Person *two) {return !isRelated(one, two) && !(one->getSpouse()) && !(two->getSpouse());}
	Person *one_;
	Person *two_;
	bool oneMarryTwo_;
	bool twoMarryOne_;
};

bool MarriageVisitor::isRelated(Person *one, Person *two) {
	// Check for null-member marriage
	if (one == nullptr) return true;
	if (two == nullptr) return true;
	// Check for self-marriage
	if (one == two) return true;
	// Check for sibling-marriage
	if (one->getFather() == two->getFather() && one->getFather() != nullptr)
		return true;
	if (one->getMother() == two->getMother() && one->getMother() != nullptr)
		return true;
	// Check for Aunt/Uncle-marriage
	Woman *aMom = static_cast<Woman*>(one->getMother());
	if (aMom != nullptr) {
		if (aMom->getMother() != nullptr) {
			Woman *aGMom = static_cast<Woman*>(aMom->getMother());
			vector<Person*> auntsUncles = aGMom->getChildren();
			for (Person *tmp : auntsUncles) {
				if (two == tmp)
					return true;
			}
		}
	}
	// Check for Aunt/Uncle-marriage
	Woman *aMomTwo = static_cast<Woman*>(two->getMother());
	if (aMomTwo != nullptr) {
		if (aMomTwo->getMother() != nullptr) {
			Woman *aGMomTwo = static_cast<Woman*>(aMomTwo->getMother());
			vector<Person*> auntsUnclesTwo = aGMomTwo->getChildren();
			for (Person *tmpTwo : auntsUnclesTwo) {
				if (one == tmpTwo)
					return true;
			}
		}
	}
	return false; // Else, not related
}

// Using this to locate the person who corresponds to our user's input
class FindPersonVisitor : public PersonVisitor {
public:
	FindPersonVisitor(string firstName, string lastName) : firstName_(firstName), lastName_(lastName), aPerson_(nullptr) {}

	void visit(Man *m) override {
		// must test if element you are visiting is the input
		if (m->getFirstName() == firstName_ && m->getLastName() == lastName_)
			aPerson_ = m;
	}
	void visit(Woman *w) override {
		string checkLastName = "";
		if (w->getFirstName() == firstName_) {
			if (w->getSpouse() != nullptr)
				checkLastName = static_cast<Man*>(w->getSpouse())->getLastName();
			else if (w->getFather() != nullptr)
				checkLastName = static_cast<Man*>(w->getFather())->getLastName();
			else
				checkLastName = "Doe";
		}
		if (checkLastName == lastName_) {
			aPerson_ = w;
		}
	}

	Person *getPerson() { return aPerson_; }
private:
	const string firstName_;
	const string lastName_;
	Person *aPerson_;
};


// demonstrating the operation
int main() {

	// setting up the genealogical tree      
	// the tree is as follows
	//    
	//
	//       James Smith  <--spouse-->   Mary 
	//	                                  |
	//	                                 children -------------------------
	//	                                  |              |                |
	//	                                  |              |                |
	//	   William Johnson <--spouse-> Patricia      Robert Smith       Linda
	//	                                  |
	//	                                 children------------
	//	                                  |                 |
	//                                     |                 |
	//	   Jennifer  <--spouse-->  Michael Johnson      Barbara
	//	       |
	//	     children
	//	       |
	//          |
	//	     Susan


	// first generation
	Man *js = new Man("Smith", "James",
		nullptr, nullptr, nullptr);
	Woman *ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
	ms->setSpouse(js);
	js->setSpouse(ms);

	// second generation
	Woman *ps = new Woman({}, "Patricia",
		nullptr, js, ms);
	Man *wj = new Man("Johnson", "William",
		nullptr, nullptr, nullptr);
	ps->setSpouse(wj); wj->setSpouse(ps);

	vector<Person *> marysKids = { ps,
					   new Man("Smith", "Robert", nullptr, js, ms),
					   new Woman({}, "Linda", nullptr, js, ms) };
	ms->setChildren(marysKids);

	// third generation
	Man *mj = new Man("Johnson", "Michael", nullptr, wj, ps);
	vector<Person *> patsKids = { mj,
								   new Woman({}, "Barbara", nullptr, wj, ps) };
	ps->setChildren(patsKids);

	Woman *jj = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);
	vector<Person *> jensKids = { new Woman({}, "Susan", nullptr, mj ,jj) };

	jj->setSpouse(mj); mj->setSpouse(jj);
	jj->setChildren(jensKids);

	// Two seemingly marriage-eligible people
	Man *am = new Man("Mikerson", "Mike", nullptr, nullptr, nullptr);
	Woman *aw = new Woman({}, "Sarah", nullptr, nullptr, nullptr);

	// defining visitors
	ChildrenPrinter *cp = new ChildrenPrinter;
	NamePrinter *np = new NamePrinter;
	MaidenPrinter *mp = new MaidenPrinter;

	cout << "\nNAME LIST\n";
	ms->accept(np);

	cout << endl << endl;

	// executing the traversal with the composite
	// and the specific visitor
	cout << "CHILDREN LIST\n";
	ms->accept(cp);

	cout << endl << endl;

	// executing the traversal with the composite
	// and the specific visitor
	cout << "MAIDEN LIST\n";
	ms->accept(mp);

	bool cont = true;
	cout << "\nMARRIAGE TEST\n";
	while (cont) {
		cout << "Enter two Person's first and last names to test for eligible marriage." << endl;
		string oneFirstName, oneLastName, twoLastName, twoFirstName;

		//Bring in first person
		cout << "Enter Person one's first name:";
		cin >> oneFirstName;
		cout << "Enter Person one's last name:";
		cin >> oneLastName;

		//Bring in second person
		cout << "Enter Person two's first name:";
		cin >> twoFirstName;
		cout << "Enter Person two's last name:";
		cin >> twoLastName;

		//Find our people
		FindPersonVisitor *findOne = new FindPersonVisitor(oneFirstName, oneLastName);
		FindPersonVisitor *findTwo = new FindPersonVisitor(twoFirstName, twoLastName);

		ms->accept(findOne);
		Person *one = findOne->getPerson();
		ms->accept(findTwo);
		Person *two = findTwo->getPerson();

		if (one == nullptr || two == nullptr) {
			cout << "Marriage parties not found" << endl;
			cout << endl;
			continue;
		}

		MarriageVisitor* eMarriage = new MarriageVisitor(one, two);

		ms->accept(eMarriage);

		if (eMarriage->eligibleMarriage())
			cout << one->getFirstName() << " can marry " << two->getFirstName() << endl;
		else
			cout << one->getFirstName() << " can NOT marry " << two->getFirstName() << endl;

		cout << endl;

		string  uin;
		cout << "Continue checking marriages? (y/n)" << endl;
		cin >> uin;
		if (uin == "y") {
			cont = true;
		}
		else if (uin == "n") {
			cont = false;
		}
	}
}