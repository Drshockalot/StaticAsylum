////////////////////////////////////////////
//				GROUP UT1				  //
//	   <(''<) Chad Simpson (>'')>         //
//     Q(''O)  Luke Ward   Q(''O)         //
//	  <(._.<)  Shaun Webb  (>._.)>        //
////////////////////////////////////////////

#include "TransactionList.h"

//---------------------------------------------------------------------------
//TransactionList: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors

//____other public member functions

void TransactionList::addNewTransaction( const Transaction& tr) {
	listOfTransactions_.push_front( tr);
}
const Transaction TransactionList::newestTransaction() const {
	return (listOfTransactions_.front());
}
const TransactionList TransactionList::olderTransactions() const{
	TransactionList trlist( *this);
    trlist.deleteFirstTransaction();
    return trlist;
}
void TransactionList::deleteFirstTransaction() {
    listOfTransactions_.pop_front();
}
void TransactionList::deleteGivenTransaction( const Transaction& tr) {
    assert(size() != 0);
	if (newestTransaction() == tr)
		*this = olderTransactions();
	else
	{
		Transaction firstTr(newestTransaction());
			//TransactionList trlist( *this);
			this->deleteFirstTransaction();
		this->deleteGivenTransaction(tr);
		this->addNewTransaction(firstTr);
	}
}

void TransactionList::deleteTransactionsUpToDate(const Date& date)
{
	if(size() <= 0)
	{
		return;
	}
	else
	{
		if (newestTransaction().getValue<Date>() <= date)
		{
			*this = olderTransactions();
			this->deleteTransactionsUpToDate(date);
		}
		else
		{
			Transaction firstTr(newestTransaction());
			this->deleteFirstTransaction();
			this->deleteTransactionsUpToDate(date);
			this->addNewTransaction(firstTr);
		}
	}
}

int TransactionList::size() const {
    return (listOfTransactions_.size());
}

const string TransactionList::toFormattedString() const {
//return transaction list as a (formatted) string
	ostringstream os_transactionlist;
    TransactionList tempTrList( *this);
	while ( ! ( tempTrList.size() == 0))
    {
		os_transactionlist << tempTrList.newestTransaction().toFormattedString() << endl;
        tempTrList.deleteFirstTransaction();
    }
	return ( os_transactionlist.str());
}

ostream& TransactionList::putDataInStream( ostream& os) const {
//put (unformatted) transaction list into an output stream
    TransactionList tempTrList( *this);
	while ( ! ( tempTrList.size() == 0))
    {
		os << tempTrList.newestTransaction() << endl;
        tempTrList.deleteFirstTransaction();
    }
	return os;
}
istream& TransactionList::getDataFromStream( istream& is) {
//read in (unformatted) transaction list from input stream
	Transaction aTransaction;
	is >> aTransaction;	//read first transaction
	while ( is != 0) 	//while not end of file
	{
		listOfTransactions_.push_back( aTransaction);   //add transaction to list of transactions
		is >> aTransaction;	//read in next transaction
	}
	return is;
}

TransactionList TransactionList::getAllDepositTransactions()
{
	TransactionList copy(*this);
	TransactionList temp;
	while (copy.size() > 0)
	{
		if(copy.newestTransaction().getValue<double>() > 0)
			temp.addTransaction(copy.newestTransaction());
		copy.deleteFirstTransaction();
	}
	return temp;
}

double TransactionList::getTotalTransactions() const
{
	double total = 0.0;
	TransactionList copy(*this);
	for(int i = 0 ; i < size() ; ++i)
	{
		total += copy.newestTransaction().getValue<double>();
		copy.deleteFirstTransaction();
	}

	return total;
}

TransactionList TransactionList::getTransactionsUpToDate(const Date& date, TransactionList temp)
{
	if(temp.size() <= 0)
	{
		TransactionList dummyTrl;
		return dummyTrl;
	}
	else
		if(temp.newestTransaction().getValue<Date>() <= date)
			return temp;
		else
		{
			temp.deleteFirstTransaction();
			TransactionList test(getTransactionsUpToDate(date, temp));
			return test;
		}
}

TransactionList TransactionList::getMostRecentTransactions(int numOfTr)
{
	list<Transaction> copy(listOfTransactions_);
	TransactionList temp;
	for (int i = 0; i < numOfTr; ++i)
	{
		if (copy.size() > 0)
		{
			temp.addTransaction(copy.front());
			copy.pop_front();
		}
	}
	return temp;
}

void TransactionList::addTransaction(const Transaction tr)
{
	listOfTransactions_.push_back(tr);
}

ostream& operator<<( ostream& os, const TransactionList& aTransactionList) {
    return ( aTransactionList.putDataInStream( os));
}
istream& operator>>( istream& is, TransactionList& aTransactionList) {
	return ( aTransactionList.getDataFromStream( is));
}
