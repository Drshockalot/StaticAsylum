//Pascale Vacher - March 14
//OOP Assignment Semester 2

#include "Date.h"

//---------------------------------------------------------------------------
//Date: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors
Date::Date() 						//default constructor
: day_( 0), month_( 0), year_( 0)
{}
Date::Date( int d, int m, int y) 	//constructor
: day_( d), month_( m), year_( y)
{}

//____other public member functions
int Date::getDay() const {
	return day_;
}
int Date::getMonth() const {
	return month_;
}
int Date::getYear() const {
	return year_;
}
const Date Date::currentDate() {	//returns the current date
	time_t now( time(0));
	struct tm& t( *localtime(&now));
    return Date( t.tm_mday, t.tm_mon + 1,  t.tm_year + 1900);
}
void Date::setDate( int d, int m, int y) {
	day_ = d;
	month_ = m;
	year_ = y;
}
string Date::toFormattedString() const {
//return date formatted output ("DD/MM/YYYY")
	ostringstream os_date;
	os_date << setfill('0');
	os_date << setw(2) << day_ << "/";
	os_date << setw(2) << month_ << "/";
	os_date << setw(2) << year_;
	os_date << setfill(' ');
	return ( os_date.str());
}

bool Date::isValidDate(const Date& creationDate) const
{
	if((*this <= currentDate()) && (*this >= creationDate))
		if(day_ > 0)
			if(day_ < 28 && month_ == 2)
				return true;
			else if(day_ < 30 && (month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11))
				return true;
			else if(day_ < 31 && (month_ == 1 || month_ == 3 || month_ == 5 || month_ == 7 || month_ == 10 || month_ == 12))
				return true;
	return false;
}

ostream& Date::putDataInStream( ostream& os) const {
//put (unformatted) date (D/M/Y) into an output stream
	os << setw(2) << day_ << "/";
	os << setw(2) << month_ << "/";
	os << setw(4) << year_;
	return os;
}
istream& Date::getDataFromStream( istream& is) {
//read in date from (unformatted) input stream ("DD/MM/YY")
	char ch;			//(any) colon field delimiter
	is >> day_ >> ch >> month_ >> ch >> year_;
	return is;
}

//---------------------------------------------------------------------------
//overloaded operator functions
//---------------------------------------------------------------------------

bool Date::operator==( const Date& d) const { //comparison operator
	return
		(( day_ == d.day_) &&
		 ( month_ == d.month_) &&
		 ( year_ == d.year_));
}
bool Date::operator!=( const Date& d) const {
	return ( !( *this == d));
}
bool Date::operator<( const Date& d) const { //NEW
//true if (strictly) earlier than d (i.e., *this < d)
	return ( ( year_ < d.year_)
	     || (( year_ == d.year_) && (month_ < d.month_) )
	     || (( year_ == d.year_) && (month_ == d.month_) && (day_ < d.day_)));
}
bool Date::operator<=( const Date& d) const
{
	return ((( year_ < d.year_)
	     || (( year_ == d.year_) && (month_ < d.month_) )
	     || (( year_ == d.year_) && (month_ == d.month_) && (day_ < d.day_))) ||
		 (( day_ == d.day_) &&
		 ( month_ == d.month_) &&
		 ( year_ == d.year_)));
}
bool Date::operator>=( const Date& d) const
{
	return ((( year_ > d.year_)
	     || (( year_ == d.year_) && (month_ > d.month_) )
	     || (( year_ == d.year_) && (month_ == d.month_) && (day_ > d.day_))) ||
		 (( day_ == d.day_) &&
		 ( month_ == d.month_) &&
		 ( year_ == d.year_)));
}
//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream& os, const Date& aDate) {
    return ( aDate.putDataInStream( os));
}
istream& operator>>( istream& is, Date& aDate) {
	return ( aDate.getDataFromStream( is));
}
