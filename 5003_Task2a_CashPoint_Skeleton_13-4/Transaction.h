////////////////////////////////////////////
//				GROUP UT1				  //
//	   <(''<) Chad Simpson (>'')>         //
//     Q(''O)  Luke Ward   Q(''O)         //
//	  <(._.<)  Shaun Webb  (>._.)>        //
////////////////////////////////////////////

#ifndef TransactionH
#define TransactionH

//---------------------------------------------------------------------------
//Transaction: class declaration
//---------------------------------------------------------------------------

#include "Date.h"
#include "Time.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Transaction {
public:
	Transaction();	//default constructor
	Transaction( const Date&, const Time&, const string&, double);	//constructor
    Transaction( const string&, double);   //constructor

	template <typename T> const T getValue() const
	{
		return date_;
	}
	template <> const Time getValue<Time>() const
	{
		return time_;
	}
	template <> const string getValue<string>() const
	{
		return title_;
	}
	template <> const double getValue<double>() const
	{
		return amount_;
	}

	const string toFormattedString() const ;				//return transaction as a formatted string
	ostream& putDataInStream( ostream& os) const;	//send Transaction info into an output stream
	istream& getDataFromStream( istream& is);		//receive Transaction info from an input stream

	bool operator==( const Transaction&) const; 	//"equal" operator
	bool operator!=( const Transaction&) const; 	//"not-equal" operator

private:
    Date date_;			//transaction date
	Time time_;			//transaction time
	string title_;		//transaction title
	double amount_;		//transaction amount
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream&, const Transaction&);	//output operator
istream& operator>>( istream&, Transaction&);	//input operator

#endif
