////////////////////////////////////////////
//				GROUP UT1				  //
//	   <(''<) Chad Simpson (>'')>         //
//     Q(''O)  Luke Ward   Q(''O)         //
//	  <(._.<)  Shaun Webb  (>._.)>        //
////////////////////////////////////////////

#ifndef BankAccountH
#define BankAccountH

//---------------------------------------------------------------------------
//BankAccount: class declaration
//---------------------------------------------------------------------------

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
	//functions to put data into and get data from streams
	virtual ostream& putDataInStream( ostream& os) const = 0;
	virtual istream& getDataFromStream( istream& is) = 0;
	void setBADetails(const string& accT, const string& accN, const string& sC, const Date& cDate, const int& bal, const TransactionList& tr);

	//other operations
	virtual const string prepareFormattedAccountDetails() const = 0;
	virtual const string prepareFormattedStatement() const = 0;
	virtual const void produceNMostRecentTransactions(int numOfTr, string& str, double& total) const;

    virtual void recordDeposit( double amount);
	void addTransaction(Transaction tr);
	void recordDeletionOfTransactionUpToDate(const Date& date);

	virtual double borrowable() const = 0;
	virtual bool canWithdraw( double amount) const = 0;
	virtual bool canTransferOut(double amount, string& probStr) const = 0;
	virtual bool canTransferIn(double amount, string& probStr) const = 0;
    virtual void recordWithdrawal( double amount) = 0;
	virtual void recordTransferIn(const double& amount, const string& aAN, const string& aSC) = 0;
	virtual void recordTransferOut(const double& amount, const string& tAN, const string& tSC) = 0;

	void readInBankAccountFromFile( const string& fileName);
	void storeBankAccountInFile( const string& fileName) const;

	void updateBalance( double amount);
	void setFileName(const string& fName);
	string getFileName();

	//templates


private:
    //data items
    string accountType_;
    string accountNumber_;
    string sortCode_;
    Date   creationDate_;
	string fileName;
	double balance_;
    TransactionList transactions_;
};

//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream&, const BankAccount&);	//output operator
istream& operator>>( istream&, BankAccount&);	    //input operator

#endif
