////////////////////////////////////////////
//				GROUP UT1				  //
//	   <(''<) Chad Simpson (>'')>         //
//     Q(''O)  Luke Ward   Q(''O)         //
//	  <(._.<)  Shaun Webb  (>._.)>        //
////////////////////////////////////////////

#include "Transaction.h"

//---------------------------------------------------------------------------
//Transaction: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors
Transaction::Transaction() { 
}

Transaction::Transaction( const Date& d, const Time& t, const string& s, double a)
: date_( d), time_( t), title_( s), amount_( a)
{ }
Transaction::Transaction( const string& s, double a)
: title_( s), amount_( a), date_( Date::currentDate()), time_( Time::currentTime()) //get date and time from system
{}
const string Transaction::toFormattedString() const {
//return (formatted) transaction as a string ("HH:MM:SS")
	ostringstream os_transaction;
	os_transaction << setfill('0');
	os_transaction << date_ << " ";
	os_transaction << time_ << " ";
	os_transaction << setfill('-');
	os_transaction << setw(30) << title_ << " ";
	os_transaction << setfill(' ') << fixed << setprecision(2);
    os_transaction << "\234" << setw(8) << amount_;
	return ( os_transaction.str());
}

ostream& Transaction::putDataInStream( ostream& os) const {
//put (unformatted) transaction into an output stream
	os << date_ << " ";
	os << time_ << " ";
	os << title_ << " ";
    os << amount_;
	return os;
}
istream& Transaction::getDataFromStream( istream& is) {
//read in (unformatted) transaction from input stream
	is >> date_ >> time_ >> title_ >> amount_;
	return is;
}

//---------------------------------------------------------------------------
//overloaded operator functions
//---------------------------------------------------------------------------

bool Transaction::operator==( const Transaction& tr) const {
	return
		(( date_   == tr.date_)   &&
		 ( time_   == tr.time_)   &&
		 ( title_  == tr.title_)  &&
		 ( amount_ == tr.amount_));
}
bool Transaction::operator!=( const Transaction& tr) const {
	return (! (*this == tr));
}

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream& os, const Transaction& aTransaction) {
    return ( aTransaction.putDataInStream( os));
}
istream& operator>>( istream& is, Transaction& aTransaction) {
	return ( aTransaction.getDataFromStream( is));
}
