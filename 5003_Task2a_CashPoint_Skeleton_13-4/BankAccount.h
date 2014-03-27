//Pascale Vacher - March 14
//OOP Assignment Semester 2

#ifndef BankAccountH
#define BankAccountH

//---------------------------------------------------------------------------
//BankAccount: class declaration
//---------------------------------------------------------------------------

//#include "Date.h"
//#include "Transaction.h"
#include "TransactionList.h"

#include <fstream>
using namespace std;


class BankAccount {
public:
    //constructors & destructor
	BankAccount();
    BankAccount( const string& typ, const string& acctNum, const string& sCode,
                          const Date& cD, double b,
                          const TransactionList& trList);
    virtual ~BankAccount();


	//getter (assessor) functions
	const string getAccountType() const;
    const string getAccountNumber() const;
    const string getSortCode() const;
    const Date getCreationDate() const;
	double getBalance() const;
    const TransactionList getTransactions() const;
	const void produceTransactionsUpToDate(const Date& date, string& str, int& numOfTr);
    bool	isEmptyTransactionList() const;
	void produceAllDepositTransactions(string&, double&);
	void showAllDepositsOnScreen(bool& b, string& s, double& d) const;
	//functions to put data into and get data from streams
	virtual ostream& putDataInStream( ostream& os) const;
	virtual istream& getDataFromStream( istream& is);
	virtual void setBADetails(const string& accT, const int& accN, const string& sC, const Date& cDate, const int& bal, const TransactionList& tr);

	//other operations
	virtual const string prepareFormattedStatement() const;
	virtual const string prepareFormattedMiniStatement(int numOfTr) const;

    virtual void recordDeposit( double amount);
	virtual void addTransaction(Transaction tr);
	void recordDeletionOfTransactionUpToDate(const Date& date);

	virtual double borrowable() const;
	virtual bool canWithdraw( double amount) const;
	virtual bool canTransferOut(double amount) const;
	virtual bool canTransferIn(double amount) const;
    virtual void recordWithdrawal( double amount);
	void recordTransferIn(const double& amount, const string& aAN, const string& aSC);
	void recordTransferOut(const double& amount, const string& tAN, const string& tSC);
	void clearTransactions(TransactionList tr);

	void readInBankAccountFromFile( const string& fileName);
	void storeBankAccountInFile( const string& fileName) const;

	virtual const TransactionList getRequestedNumberOfTransactions(int numOfTr) const;
	void updateBalance( double amount);
	template <typename T> string m7a_showTransactionsForAmount(T amount)
	{
		ostringstream os;
		TransactionList results(transactions_.getTransactionsForAmount(amount));
		if ( ! results.size() == 0)
			os << "\n\n"<< results.size() <<" TRANSACTIONS FOUND\n" << results.toFormattedString();	//one per line
		else
			os << "\n\nNO TRANSACTION IN BANK ACCOUNT MATCH THE SEARCH CRITERION GIVEN!";
		return ( os.str());
	}

private:
    //data items
    string accountType_;
    string accountNumber_;
    string sortCode_;
    Date   creationDate_;
	double balance_;
    TransactionList transactions_;
 
	//support functions
	
	virtual const string prepareFormattedAccountDetails() const;
	virtual const string prepareFormattedMiniAccountDetails(int numOfTr) const;
	
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream&, const BankAccount&);	//output operator
istream& operator>>( istream&, BankAccount&);	    //input operator

#endif
