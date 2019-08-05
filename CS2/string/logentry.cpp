//
//
// File:        logentry.cpp  
//       
// Version:     1.0
// Date:        
// Author:      
//
// Description: Class implementation for a log entry.
//
//

////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <iterator>

#include "string.hpp" 
#include "logentry.hpp"

////////////////////////////////////////////////////////// 
// REQUIRES:  
// ENSURES: 
//
LogEntry::LogEntry(String s) : LogEntry() {
	std::vector<String> vec = s.split(' ');
	if (vec.size() == 10) {
		host = vec[0];
		String day = vec[3].substr(1, 2);
		String month = vec[3].substr(4, 6);
		String aYear = vec[3].substr(8, 11);
		int year = aYear.stoi();
		Date* aDate = new Date(day, month, year);
		date = *aDate;
		Time* aTime = new Time(vec[3].substr(13, 14).stoi(), vec[3].substr(16, 17).stoi(), vec[3].substr(19, 20).stoi());
		time = *aTime;
		String b = vec[5];
		String d = vec[6];
		String f = vec[7];
		request = b+d+f;
		status = vec[8];
		number_of_bytes = vec[9].stoi();
	}
}

////////////////////////////////////////////////////////// 
// REQUIRES:  
// ENSURES: 
//
std::vector<LogEntry> parse(std::istream& in) {
	std::vector<LogEntry> result;
	do {
		String input_line = getline(in);
		LogEntry log(input_line);
		result.push_back(log);
	} while (!in.eof());
	return result;
}

////////////////////////////////////////////////////////// 
// REQUIRES:  
// ENSURES: 
//
void output_all(std::ostream& out, const std::vector<LogEntry> &vec) {
	for (unsigned long i = 0; i < vec.size() - 1; i++) {
		out << vec[i];
	} out << '\n';
}

////////////////////////////////////////////////////////// 
// REQUIRES:  
// ENSURES: 
//
void by_host(std::ostream& out, const std::vector<LogEntry>&vec) {
	std::cout << "By Host" << '\n';

	for (unsigned long i = 0; i < vec.size() - 1; i++) {
		out << vec[i].getHost() << '\n';
	}
}

////////////////////////////////////////////////////////// 
// REQUIRES:  
// ENSURES: 
//
int byte_count(const std::vector<LogEntry> &vec) {
	int total = 0;
	for (unsigned long i = 0; i < vec.size() - 1; i++) {
		total = total + vec[i].getNumBytes();
	}
	return total;
}

std::ostream& operator<<(std::ostream&out, const LogEntry&aLog) {
	//std::cout << "Output operator" << '\n';
	out << aLog.host << " "; //Host
	{//Date
		Date aDate = aLog.getDate();
		out << aDate.getDay() << " ";
		out << aDate.getMonth() << " ";
		out << aDate.getYear() << " ";
	}
	{//Time
		Time aTime = aLog.getTime();
		out << aTime.getHour() << " ";
		out << aTime.getMinute() << " ";
		out << aTime.getSecond() << " ";
	}
	{//Request+Status+NumberOfBytes
		out << aLog.getRequest() << " ";
		out << aLog.getStatus() << " ";
		out << aLog.getNumBytes() << '\n';
	}
	return out;
}
