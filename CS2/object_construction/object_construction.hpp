#ifndef OBJ_CONST_HPP
#define OBJ_CONST_HPP

class myClass{
public:
	myClass();
	myClass(const myClass&);
	~myClass();
	void operator = (myClass);
private:
	int*x;
};

#endif
