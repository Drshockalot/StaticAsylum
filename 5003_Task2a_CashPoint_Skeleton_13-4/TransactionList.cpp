//Pascale Vacher - March 14
//OOP Assignment Semester 2

#include "TransactionList.h"

//---------------------------------------------------------------------------
//TransactionList: class implementation
//---------------------------------------------------------------------------

//____public member functions

//____constructors & destructors

//____other public member functions

void TransactionList::addNewTransaction( const Transaction& tr) {
    listOfTransactions_.addInFront( tr);
}
const Transaction TransactionList::newestTransaction() const {
    return (listOfTransactions_.first());
}
const TransactionList TransactionList::olderTransactions() const{
	TransactionList trlist( *this);
    trlist.deleteFirstTransaction();
    return trlist;
}
void TransactionList::deleteFirstTransaction() {
    listOfTransactions_.deleteFirst();
}
void TransactionList::deleteGivenTransaction( const Transaction& tr) {
    assert(size() != 0);
	if (newestTransaction() == tr)
		*this = olderTransactions();
	else
	{
		Transaction firstTr(newestTransaction());
			TransactionList trlist( *this);
			trlist.deleteFirstTransaction();
		trlist.deleteGivenTransaction(tr);
		this->addNewTransaction(firstTr);
	}

}
int TransactionList::size() const {
    return (listOfTransactions_.length());
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
		listOfTransactions_.addAtEnd( aTransaction);   //add transaction to list of transactions
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
		if(copy.newestTransaction().getAmount() > 0)
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
		total += copy.newestTransaction().getAmount();
		copy.deleteFirstTransaction();
	}

	return total;
}
void TransactionList::addTransaction(const Transaction tr)
{
	listOfTransactions_.addAtEnd(tr);
}
TransactionList TransactionList::getTransactionsForAmount(const double amount)
{
	TransactionList copy(*this);
	TransactionList temp;
	for(int i = 0 ; i < (*this).size() ; ++i)
	{
		if(copy.size() > 0)
		{
			if(copy.newestTransaction().getAmount() == amount)
			{
				temp.addTransaction(copy.newestTransaction());
			}
			copy.deleteFirstTransaction();
		}
	}
	return temp;
}
TransactionList TransactionList::getTransactionsForTitle(const string title)
{
	TransactionList copy(*this);
	TransactionList temp;
	for(int i = 0 ; i < (*this).size() ; ++i)
	{
		if(copy.size() > 0)
		{
			if(copy.newestTransaction().getTitle() == title)
			{
				temp.addTransaction(copy.newestTransaction());
			}
			copy.deleteFirstTransaction();
		}
	}
	return temp;
}
TransactionList TransactionList::getTransactionsForDate(Date date)
{
	TransactionList copy(*this);
	TransactionList temp;
	for(int i = 0 ; i < (*this).size() ; ++i)
	{
		if(copy.size() > 0)
		{
			if(copy.newestTransaction().getDate() == date)
			{
				temp.addTransaction(copy.newestTransaction());
			}
			copy.deleteFirstTransaction();
		}
	}
	return temp;
}
//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream& os, const TransactionList& aTransactionList) {
    return ( aTransactionList.putDataInStream( os));
}
istream& operator>>( istream& is, TransactionList& aTransactionList) {
	return ( aTransactionList.getDataFromStream( is));
}
