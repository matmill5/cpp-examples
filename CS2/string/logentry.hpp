#ifndef CS_LOGENTRY_H_
#define CS_LOGENTRY_H_

////////////////////////////////////////////////////////////
//
// File:        logentry.hpp 
//       
// Version:     1.0
// Date:        
// Author:      
//
// Description: Class definition for a log entry.
//
//
//

////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>

#include "string.hpp" 

////////////////////////////////////////////////////////////
class Date {
public:
	Date() { day = ""; month = ""; year = 0; };
	Date(String c_day, String c_month, int c_year) { day = c_day; month = c_month; year = c_year; };
	String getDay() const { return day; };
	String getMonth() const { return month; };
	int getYear() const { return year; };
private:
	String  day, month;
	int     year;
};

////////////////////////////////////////////////////////////
class Time {
public:
	Time() { hour = 0; minute = 0; second = 0; };
	Time(int c_hour, int c_minute, int c_second) { hour = c_hour; minute = c_minute; second = c_second; };
	int getHour() const { return hour; };
	int getMinute() const { return minute; };
	int getSecond() const { return second; };
private:
	int     hour, minute, second;
};


////////////////////////////////////////////////////////////
class LogEntry {
public:
	LogEntry() { host = "EMPTY LOG"; request = ""; status = ""; number_of_bytes = 0; };
	LogEntry(String);
	friend  std::ostream& operator<<(std::ostream&, const LogEntry&);
	String getHost() const { return host; };
	Date getDate() const { return date; };
	Time getTime() const { return time; };
	String getRequest() const { return request; };
	String getStatus() const { return status; };
	int getNumBytes() const { return number_of_bytes; };
private:
	String  host;
	Date    date;
	Time    time;
	String  request;
	String  status;
	int     number_of_bytes;
};


////////////////////////////////////////////////////////////
//
// Free functions
//

std::vector<LogEntry>   parse(std::istream&);
void                    output_all(std::ostream&, const std::vector<LogEntry> &);
void                    by_host(std::ostream&, const std::vector<LogEntry> &);
int                     byte_count(const std::vector<LogEntry>&);

#endif
