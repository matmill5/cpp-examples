// implements command history 
// (multiple undos)
// demonstrates command pattern
// Mikhail Nesterenko
// 11/22/2014

#include <iostream>
#include <vector>
#include <string>
#include <stack>

using std::vector; using std::string;
using std::cout; using std::cin; using std::endl;

// receiver
class Document {
public:

	Document(const vector <string> & lines = {}) : lines_(lines) {}

	// actions
	void insert(int line, const string &str) {
		const int index = line - 1;
		if (index <= lines_.size())
			lines_.insert(lines_.begin() + index, str);
		else
			cout << "line out of range" << endl;
	}

	string remove(int line) {
		const int index = line - 1;
		string deletedLine = "";
		if (index < lines_.size()) {
			deletedLine = lines_[index];
			lines_.erase(lines_.begin() + index);
		}
		else
			cout << "line out of range" << endl;
		return deletedLine;
	}

	void show() {
		for (int i = 0; i < lines_.size(); ++i)
			cout << i + 1 << ". " << lines_[i] << endl;
	}

	class Memento *createMemento() const;
	void rollBack(class Memento *);

private:
	vector<string>lines_;
};

// abstract command
class Command {
public:
	Command(Document *doc) : doc_(doc) {}
	virtual void execute() = 0;
	virtual void unexecute() = 0;
	virtual ~Command() {}
	virtual void printCommand() {}
protected:
	Document *doc_;
};

// two concrete commands
class InsertCommand : public Command {
public:
	InsertCommand(Document *doc, int line, const string &str) :
		Command(doc), line_(line), str_(str) {}
	void execute() { doc_->insert(line_, str_); }
	void unexecute() { doc_->remove(line_); }
	void printCommand() { cout << "insert " << '"' << str_ << '"' << " at line " << line_ << endl; }
private:
	int line_;
	string str_;
};


class EraseCommand : public Command {
public:
	EraseCommand(Document *doc, int line) :
		Command(doc), line_(line), str_("") {}
	void execute() { str_ = doc_->remove(line_); }
	void unexecute() { doc_->insert(line_, str_); }
	void printCommand() { cout << "erase " << "line " << line_ << endl; }
private:
	int line_;
	string str_;
};

// client
class DocumentWithHistory {
public:
	DocumentWithHistory(const vector<string> & text = {}) : doc_(text) {}

	void insert(int line, string str) {
		Command *com = new InsertCommand(&doc_, line, str);
		com->execute();
		doneCommands_.push(com);
	}

	void erase(int line) {
		Command *com = new EraseCommand(&doc_, line);
		com->execute();
		doneCommands_.push(com);
	}

	void undo() {
		if (doneCommands_.size() != 0) {
			Command *com = doneCommands_.top();
			doneCommands_.pop();
			com->unexecute();
			delete com; // don't forget to delete command
		}
		else
			cout << "no commands to undo" << endl;
	}

	Document* getDoc() { return &doc_; }
	std::stack<Command*> *getCommands() { return &doneCommands_; }

	void show() { doc_.show(); }

private:
	std::stack<Command*> doneCommands_;
	Document doc_;
};

//Memento
class Memento {
public:
	Memento(const Document& doc) : doc_(doc) {}
	const Document& getState() const { return doc_; }
private:
	const Document doc_;
};

Memento *Document::createMemento() const {
	cout << "createMemnto" << endl;
	return new Memento(*this);    // copying the Document itself
}

void Document::rollBack(Memento *mem) {
	cout << "rollback" << endl;
	*this = mem->getState();  // copying back
}

// invoker
int main() {

	DocumentWithHistory doc({
	  "Lorem Ipsum is simply dummy text of the printing and typesetting",
	  "industry. Lorem Ipsum has been the industry's standard dummy text",
	  "ever since the 1500s, when an unknown printer took a galley of",
	  "type and scrambled it to make a type specimen book. It has",
	  "survived five centuries." });
	
	Memento *checkpoint = nullptr;
	char option;
	std::stack<Command*> tmpCommands_;
	string uin;
	Command *tmpCommand;

	do {
		doc.show();
		cout << endl;

		cout << "Enter option (i)nsert line, (e)rase line, (u)ndo last command, (c)heckpoint, roll(b)ack, (h)istory, (r)edo: ";
		cin >> option;

		int line; string str;
		switch (option) {
		case 'i':
			cout << "line number to insert: ";
			cin >> line;
			cout << "line to insert: ";
			cin.get();
			getline(cin, str);
			doc.insert(line, str);
			break;

		case 'e':
			cout << "line number to remove: ";
			cin >> line;
			doc.erase(line);
			break;

		case 'u':
			doc.undo();
			break;

		case 'c':
			checkpoint = doc.getDoc()->createMemento();
			// When new checkpoint, clear the stack
			while (doc.getCommands()->size() > 0) {
				doc.getCommands()->pop();
			}
			break;

		case 'b':
			if (checkpoint != nullptr) {
				doc.getDoc()->rollBack(checkpoint);
				delete checkpoint;
			}
			break;
		case 'h':
			while (doc.getCommands()->size() > 0) {
				doc.getCommands()->top()->printCommand();
				tmpCommands_.push(doc.getCommands()->top());
				doc.getCommands()->pop();
			}
			while (tmpCommands_.size() > 0) {
				doc.getCommands()->push(tmpCommands_.top());
				tmpCommands_.pop();
			}
			cout << endl;
			break;
		case 'r': {
			cout << "Which command would you like to redo?" << endl;
			cin >> uin;
			if (std::stoi(uin) > doc.getCommands()->size()) {
				cout << "That command is outside the scope of history" << endl;
				cout << "There is only " << doc.getCommands()->size() << "to pick from." << endl;
			}
			else {
				while (doc.getCommands()->size() != std::stoi(uin)) {
					tmpCommands_.push(doc.getCommands()->top());
					doc.getCommands()->pop();
				}
				// Alert use of the executed command
				tmpCommand = doc.getCommands()->top();
				tmpCommand->execute();
				cout << "Command Done: ";
				doc.getCommands()->top()->printCommand();
				cout << endl;
				while (tmpCommands_.size() > 0) {
					doc.getCommands()->push(tmpCommands_.top());
					tmpCommands_.pop();
				}
				doc.getCommands()->push(tmpCommand);
			}
			break;
		}
		}
	} while (option == 'i' || option == 'e' || option == 'u' || option == 'c' || option == 'r' || option == 'h' || option == 'b');
}