// Author: Matthew E. Miller
// Date: 10/25/2019
// Assn: Lab08 SingletonLogger

#include <string>
#include <fstream>
#include <iostream>

using std::string;
using std::ofstream;

class SingletonLogger {
	public:
		static SingletonLogger* instance();
		void report(const string&);
		~SingletonLogger();
	private:
		SingletonLogger();
		SingletonLogger(const SingletonLogger&) = delete;
		SingletonLogger& operator=(const SingletonLogger&) = delete;
		ofstream fout;
};

SingletonLogger::SingletonLogger() {
	fout.open("log.txt", std::fstream::out | std::fstream::app);
}

SingletonLogger::~SingletonLogger() {
	report("destructor");
	fout.flush();
	fout.close();
}

SingletonLogger* SingletonLogger::instance() {
	static SingletonLogger aLog;
	return &aLog;
}

void SingletonLogger::report(const string& msg) {
	fout << msg << std::endl;
	fout.flush();
}

void nReports(int n) {
	for (int i = 0; i < n; ++i) {
		SingletonLogger::instance()->report("A Bunch of Nothing");
	}
}

void recordSomething(string aRecord) {
	SingletonLogger::instance()->report(aRecord);
}

int main() {
	SingletonLogger::instance()->report("Main");
	SingletonLogger::instance()->report("Calling nReports(int n)");
	SingletonLogger::instance()->report("Making ten reportings, right now:");
	nReports(10);
	SingletonLogger::instance()->report("Done with ten reporting entries.");
	SingletonLogger::instance()->report("Now, doing a custom reporting entry with recordSomething(string)");
	recordSomething("A Custom Entry");
	SingletonLogger::instance()->report("Done");
}