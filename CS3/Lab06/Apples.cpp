// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 10/03/2018


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

// A Functor 
class jam
{
public:
	double maxWeight;
	double& jamWeight;

	jam(double &jW) : jamWeight(jW) {  }

	// This operator overloading enables calling 
	// operator function () on objects of increment 
	void operator () (double jW, double mW) const {
		jamWeight += jW;
	}
};

struct Apples {
	double weight; // oz
	string color;  // red or green
	void print() const { cout << color << ", " << weight << endl; }
	Apples() {
		weight = 0;
		color = "blue";
	}
	Apples(int minWeight, int maxWeight) {
		weight = minWeight + static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
		color = rand() % 2 == 1 ? "green" : "red";
	}
};

int main() {
	srand(time(nullptr));
	const double minWeight = 8.;
	const double maxWeight = 3.;

	cout << "Input crate size: ";
	int size;
	cin >> size;

	vector <Apples> crate(size);

	// assign random weight and color to apples in the crate
	// replace with generate()
	generate(crate.begin(), crate.end(), [minWeight, maxWeight] {
		Apples aApple(minWeight, maxWeight);
		return aApple;
	});

	cout << "Enter weight to find: ";
	double toFind;
	cin >> toFind;

	// count_if()
	int cnt = 0;
	cnt = count_if(crate.cbegin(), crate.cend(), [toFind](Apples a) { return a.weight > toFind; });
	cout << "There are " << cnt << " apples heavier than "
		<< toFind << " oz" << endl;

	// find_if()
	cout << "at positions ";
	vector<Apples>::iterator ptr = crate.begin();
	for (int i = 0; i < size; ++i) {
		ptr = find_if(ptr, crate.end(), [toFind](Apples a) {return a.weight > toFind; });
		if(ptr != crate.end()){
			cout << std::distance(crate.begin(), ptr) << ", ";
			++ptr;
		}
	}
	cout << endl;


	// max_element()
	auto heaviest = max_element(crate.begin(), crate.end(), [](Apples a, Apples b) { return (a.weight < b.weight); });
	cout << "Heaviest apple weighs: " << heaviest->weight << " oz" << endl;


	// for_each() or accumulate()
	double sum = 0;
	for_each(crate.begin(), crate.end(), [&sum](Apples a) { return sum += a.weight; });
	cout << "Total apple weight is: " << sum << " oz" << endl;


	// transform();
	cout << "How much should they grow: ";
	double toGrow;
	cin >> toGrow;
	transform(crate.begin(), crate.end(), crate.begin(), [toGrow](Apples a) { a.weight += toGrow; return a; });

	// remove_if()
	cout << "Input minimum acceptable weight: ";
	double minAccept;
	cin >> minAccept;
	auto rmIt = remove_if(crate.begin(), crate.end(), [minAccept](Apples a) { return a.weight < minAccept; });
	if (rmIt != crate.end()) {
		crate.erase(rmIt, crate.end());
	}
	cout << "removed " << size - crate.size() << " elements" << endl;


	// bubble sort, replace with sort()
	sort(crate.begin(), crate.end(), [](Apples a, Apples b) {return a.weight > b.weight; });


	// moving all red apples from crate to peck
	// remove_copy_if() with back_inserter()/front_inserter() or equivalents
	deque<Apples> peck;
	remove_copy_if(crate.begin(), crate.end(), inserter(peck, peck.begin()), [](Apples a) {return a.color != "red"; });
	crate.erase(remove_if(crate.begin(), crate.end(), [](Apples a) { return a.color == "red"; }), crate.end());

	// for_each() possibly
	cout << "apples in the create" << endl;
	for_each(crate.begin(), crate.end(), [](Apples a) { a.print(); });
	cout << endl;

	// for_each() possibly
	cout << "apples in the peck" << endl;
	for_each(peck.begin(), peck.end(), [](Apples a) { a.print(); });


	// prints every "space" apple in the peck
	// 
	const int space = 3;
	cout << "\nevery " << space << "\'d apple in the peck" << endl;

	// replace with advance()/next()/distance()
	// no iterator arithmetic
	auto it = peck.begin(); int i = 0;
	while (it != peck.cend()) {
		if (i == space) {
			it->print();
			i = 0;
		}
		++i;
		advance(it, 1);
	}


	//NOTE, this part doesn't work correctly.  
	//Tried to implement it best I could, but out-of-time.
	// putting all small green apples in a jam
	// use a binder to create a functor with configurable max weight
	// count_if() then remove_if()
	const double weightToJam = 10.0;
	double jamWeight = 0;
	auto jamFn = bind(jam(jamWeight), std::placeholders::_1, weightToJam);
	for (auto it = crate.begin(); it != crate.end();)
		if (it->weight < weightToJam) {
			jam(it->weight);
		}
		else
			++it;

	cout << count_if(crate.begin(), crate.end(), [weightToJam](Apples a) { return a.weight < weightToJam; });
	crate.erase(remove_if(crate.begin(), crate.end(), [weightToJam](Apples a) { return a.weight < 10; }), crate.end());
	cout << "Weight of jam is: " << jamWeight << endl;




}