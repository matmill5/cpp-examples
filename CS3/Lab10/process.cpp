// demonstrates state design pattern
// Mikhail Nesterenko
// 2/23/2014

// Author: Matthew E. Miller
// Date: 11/1/19
// Lab 10 - Part 2

#include <iostream>
#include <string>
using std::cin; using std::cout; using std::endl; using std::string;

class State;

// context
class Process {
public:
	Process();

	// behaviors
	//void skipLunch();
	//void eat();
	string report();
	string getName() { return name_; }

	void admitted();
	void interrupt();
	void schedulerDispath();
	void exit();
	void io();
	void eventCompletion();
	void eventWait();

	// part of implementation of state pattern
	void changeState(State* s) { state_ = s; }
private:
	State* state_;
	static int uid_;
	const string name_;
};

// absract state
class State {
public:
	// provides default implementation
	//virtual void skipLunch(Character*) {}
	// provides default implementation
	//virtual void eat(Character*) {}
	virtual string report() = 0;

	//Lab10
	virtual void admitted(Process*) {}
	virtual void interrupt(Process*) {}
	virtual void schedulerDispatch(Process*) {}
	virtual void exit(Process*) {}
	virtual void io(Process*) {}
	virtual void eventCompletion(Process*) {}
	virtual void eventWait(Process*) {}

	void changeState(Process* p, State* s) {
		p->changeState(s);
	}
};

class New : public State {
public:
	static State* instance() {
		static State* onlyInstance = new New;
		return onlyInstance;
	}
	//virtual void eat(Character*) override;
	//void skipLunch(Character*) override;
	string report() override { return "New"; }
	void admitted(Process*) override;
private:
	// here and elsewhere should be stated private constructor/assignment
	// to correctly implement singleton, skipped to simplify code
};


class Ready : public State {
public:
	static State* instance() {
		static State* onlyInstance = new Ready;
		return onlyInstance;
	}
	//void skipLunch(Character*) override;
	//void eat(Character*) override;
	string report() override { return "Ready"; }
	void schedulerDispatch(Process*) override;
};


class Waiting : public State {
public:
	static State* instance() {
		static State* onlyInstance = new Waiting;
		return onlyInstance;
	}
	string report() override { return "Waiting"; }
	virtual void io(Process*) override;
	void eventCompletion(Process*) override;
};

class Running : public State {
public:
	static State* instance() {
		static State* onlyInstance = new Running;
		return onlyInstance;
	}
	string report() override { return "Running"; }
	void interrupt(Process*) override;
	void eventWait(Process*) override;
	void io(Process*) override;
	void exit(Process*) override;
};

class Terminated : public State {
public:
	static State* instance() {
		static State* onlyInstance = new Terminated;
		return onlyInstance;
	}
	string report() override { return "Terminated"; }
};

// state transitions member functions
// New
void New::admitted(Process *p) { changeState(p, Ready::instance()); }

//Ready
void Ready::schedulerDispatch(Process *p) { changeState(p, Running::instance()); }

//Waiting
void Waiting::io(Process *p) { changeState(p, Ready::instance()); }
void Waiting::eventCompletion(Process *p) { changeState(p, Ready::instance()); }

//Running
void Running::interrupt(Process *p) { changeState(p, Ready::instance()); }
void Running::eventWait(Process *p) { changeState(p, Waiting::instance()); }
void Running::io(Process *p) { changeState(p, Waiting::instance()); }
void Running::exit(Process *p) { changeState(p, Terminated::instance()); }

//Terminated
//No transitions

// Process member functions
int Process::uid_ = 0;
Process::Process() : name_("Process " + std::to_string(uid_++)) { state_ = New::instance(); }

// handles/behaviors
void Process::admitted() { state_->admitted(this); }
void Process::interrupt() { state_->interrupt(this); }
void Process::io() { state_->io(this); }
void Process::eventCompletion() { state_->eventCompletion(this); }
void Process::schedulerDispath() { state_->schedulerDispatch(this); }
void Process::eventWait() { state_->eventWait(this); }
void Process::exit() { state_->exit(this); }
string Process::report() { return state_->report(); }

int main() {
	Process aProcess;
	cout << aProcess.getName() << " is " << aProcess.report() << endl;

	while (aProcess.report() != "Terminated") {
		cout << "What should happen to the process? [a/i/o/c/d/w/e] ";
		char action; cin >> action;
		switch (action) {
			case 'a':
				aProcess.admitted();
				break;
			case 'i':
				aProcess.interrupt();
				break;
			case 'o':
				aProcess.io();
				break;
			case 'c':
				aProcess.eventCompletion();
				break;
			case 'd':
				aProcess.schedulerDispath();
				break;
			case 'w':
				aProcess.eventWait();
				break;
			case 'e':
				aProcess.exit();
				break;
			default:
				cout << "Non option";
				break;
		}
		cout << aProcess.getName() << " is " << aProcess.report() << endl;
	}

	// demonstrates that two Characters may be in two different states
	Process anotherProcess;
	cout << aProcess.getName() << " is " << aProcess.report() << " while "
		<< anotherProcess.getName() << " is " << anotherProcess.report() << endl;
}