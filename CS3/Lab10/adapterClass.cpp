// figures: class adapter pattern
// Mikhail Nesterenko
// 2/16/2014

// Editor:  Matthew E. Miller
// Date: 11/1/2019

#include <iostream>

using std::cout; using std::endl;

// base interface
class Figure {
public:
	virtual void draw() = 0;
	virtual ~Figure() {}
};

// adaptee/implementer
class LegacyRectangle {
public:
	LegacyRectangle(int topLeftX,
		int topLeftY,
		int bottomRightX,
		int bottomRightY) :
		topLeftX_(topLeftX),
		topLeftY_(topLeftY),
		bottomRightX_(bottomRightX),
		bottomRightY_(bottomRightY) {}

	void move(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
		topLeftX_ = topLeftX;
		topLeftY_ = topLeftY;
		bottomRightX_ = bottomRightX;
		bottomRightY_ = bottomRightY;
	};

	int getTopLeftX() { return topLeftX_; };
	int getTopLeftY() { return topLeftY_; };
	int getBottomRightX() { return bottomRightX_; };
	int getBottomRightY() { return bottomRightY_; };

	void oldDraw() {
		for (int i = 0; i < bottomRightY_; ++i) {
			for (int j = 0; j < bottomRightX_; ++j)
				if (i >= topLeftY_ && j >= topLeftX_)
					cout << '*';
				else
					cout << ' ';
			cout << endl;
		}
	}
private: // defining top/left and bottom/right coordinates 
	int topLeftX_;
	int topLeftY_;
	int bottomRightX_;
	int bottomRightY_;
};

// adapter uses multiple inheritance to inherit
// interface and implementation
class SquareAdapter : public Figure,
	private LegacyRectangle {
public:
	SquareAdapter(int size) :
		LegacyRectangle(0, 0, size, size) {};
	int size() { return getBottomRightX(); };
	void resize(int newSize) {
		this->move(0, 0, newSize, newSize);
	};
	void draw() override {
		oldDraw();
	}
};


int main() {
	Figure *square = new SquareAdapter(10);
	square->draw();
	
	int inSize = 0;

	std::cout << "Please enter the size of a square: " << std::endl;
	std::cin >> inSize;

	SquareAdapter *user_Square = new SquareAdapter(inSize);
	user_Square->draw();
	std::cout << "Please enter a new size for the square: " << std::endl;
	std::cin >> inSize;
	user_Square->resize(inSize);
	user_Square->draw();
	std::cout << "Thanks" << endl;

}