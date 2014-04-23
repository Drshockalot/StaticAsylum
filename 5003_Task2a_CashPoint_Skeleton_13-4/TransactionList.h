////////////////////////////////////////////
//				GROUP UT1				  //
//	   <(''<) Chad Simpson (>'')>         //
//     Q(''O)  Luke Ward   Q(''O)         //
//	  <(._.<)  Shaun Webb  (>._.)>        //
////////////////////////////////////////////

#ifndef TransactionListH
#define TransactionListH

//---------------------------------------------------------------------------
//TransactionList: class declaration
//---------------------------------------------------------------------------

//#include "ListT.h"
#include "Transaction.h"

#include <cassert> 	// for assert()
#include <sstream>
#include <list>

class TransactionList {
public:

	void   addNewTransaction( const Transaction&);
    const Transaction newestTransaction() const;
    const TransactionList olderTransactions() const;
    void   deleteFirstTransaction();
    void   deleteGivenTransaction( const Transaction&);
	int    size() const;
	TransactionList getAllDepositTransactions();
	double getTotalTransactions() const;
	TransactionList getMostRecentTransactions(int numOfTr);
	TransactionList getTransactionsUpToDate(const Date& date, TransactionList temp);
	void deleteTransactionsUpToDate(const Date& date);
	void addTransaction(const Transaction tr);
	template <typename T> TransactionList getTransactionsForAmount(const T amount) const
	{
		TransactionList copy(*this);
		TransactionList temp;
		for(int i = 0 ; i < (*this).size() ; ++i)
		{
			if(copy.size() > 0)
			{
				if(copy.newestTransaction().getValue<T>() == amount)
				{
					temp.addTransaction(copy.newestTransaction());
				}
				copy.deleteFirstTransaction();
			}
		}
		return temp;
	}
	const string toFormattedString() const;		//return transactionlist as a (formatted) string
	ostream& putDataInStream( ostream& os) const;	//send TransactionList info into an output stream
	istream& getDataFromStream( istream& is);	//receive TransactionList info from an input stream


private:
    list<Transaction> listOfTransactions_;	//list of transactions
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream&, const TransactionList&);	//insertion operator
istream& operator>>( istream& is, TransactionList& trl); //extraction operator

#endif

