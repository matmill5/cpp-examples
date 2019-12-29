// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Mikhail Nesterenko
// 2/12/2014

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill {
public:
	//Fill(char fillChar) :fillChar_(fillChar) {}
	Fill(char fillChar, char borderChar) : fillChar_(fillChar), borderChar_(borderChar) {}
	virtual char getBorder() = 0;
	virtual char getInternal() = 0;
	virtual ~Fill() {}
protected:
	char fillChar_;
	char borderChar_;
};

// concrete body
class Hollow : public Fill {
public:
	Hollow(char borderChar) :Fill(' ', borderChar) {}
	char getBorder() override { return borderChar_; }
	char getInternal() override { return fillChar_; }
	~Hollow() {}
};



// another concrete body
class Filled : public Fill {
public:
	Filled(char fillChar) : Fill(fillChar, fillChar) {}
	char getBorder() override { return borderChar_; }
	char getInternal() override { return fillChar_; }
	~Filled() {}
};

// Two Character Paint
class EnhancedFill : public Fill {
public:
	EnhancedFill(char fillChar, char borderChar) : Fill(fillChar, borderChar) {}
	char getBorder() override { return borderChar_; };
	char getInternal() override { return fillChar_; };
	~EnhancedFill() {}
};

// abstract handle
class Figure {
public:
	Figure(int size, Fill* fill) : size_(size),
		fill_(fill) {}
	virtual void draw() = 0;
	void changeFill(const Fill* aFill) { fill_ = const_cast<Fill*>(aFill); };
	virtual ~Figure() {}
protected:
	int size_;
	Fill *fill_;
};

// concrete handle
class Square : public Figure {
public:
	Square(int size, Fill* fill) : Figure(size, fill) {}
	void draw() override;

};


void Square::draw() {
	for (int i = 0; i < size_; ++i) {
		for (int j = 0; j < size_; ++j)
			if (i == 0 || j == 0 || i == size_ - 1 || j == size_ - 1)
				cout << fill_->getBorder();
			else
				cout << fill_->getInternal();
		cout << endl;
	}
}


int main() {
	Fill* hollowPaintY = new Hollow('Y');
	Fill* filledPaintStar = new Filled('*');


	Figure *smallBox = new Square(4, filledPaintStar);
	Figure *bigBox = new Square(10, hollowPaintY);

	smallBox->draw();
	cout << endl;
	bigBox -> draw();

	// ask user for figure parameters
	cout << "Enter fill character: ";
	char fchar; cin >> fchar;
	cout << "Filled or hollow? [f/h] ";
	char ifFilled; cin >> ifFilled;
	cout << "Enter size: "; int size; cin >> size;

	Figure *userBox = new Square(size, ifFilled == 'f' ?
		static_cast<Fill *>(new Filled(fchar)) :
		static_cast<Fill *>(new Hollow(fchar))
	);

	/*
	Figure *userBox = ifFilled == 'f'?
	   new Square(size, new Filled(fchar)):
	   new Square(size, new Hollow(fchar));
	*/

	userBox->draw();
	cout << endl;

	// ask user for figure parameters
	cout << "Enhanced box drawing." << endl;
	cout << "Enter fill character: ";
	cin >> fchar;
	cout << "Enter border character:";
	char bchar; cin >> bchar;
	cout << "Enter size: "; cin >> size;

	Figure *enhancedBox = new Square(size, static_cast<Fill *>(new EnhancedFill(fchar, bchar)));

	cout << "\nEnhanced Box: " << endl;
	enhancedBox->draw();
}