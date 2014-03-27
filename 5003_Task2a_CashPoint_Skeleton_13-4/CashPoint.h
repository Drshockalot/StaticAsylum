//Pascale Vacher - March 14
//OOP Assignment Semester 2

#ifndef CashPointH
#define CashPointH 

//---------------------------------------------------------------------------
//CashPoint: class declaration
//---------------------------------------------------------------------------

#include "CashCard.h"
#include "BankAccount.h"
#include "CurrentAccount.h"
#include "ChildAccount.h"
#include "ISAAccount.h"
#include "UserInterface.h"

#include <fstream>
#include <string>
using namespace std;

class CashPoint {
public:
	//constructors & destructor
	CashPoint();	//default constructor
	~CashPoint();	//destructor
    void activateCashPoint();
private:
	//data items
    BankAccount* p_theActiveAccount_;
	BankAccount* p_theTransferAccount_;
    CashCard* p_theCashCard_;
	CurrentAccount* p_CurrentAccount_;
	SavingsAccount* p_SavingsAccount_;
	ChildAccount* p_ChildAccount_;
    const UserInterface theUI_;

	//support functions
	void performCardCommand( int);
    void performAccountProcessingCommand( int);
    int  validateCard( const string&) const;
	int  validateAccount( const string&) const;
	void processOneCustomerRequests();
	void processOneAccountRequests();
	void attemptTransfer(BankAccount* p_theTransferAccount_);
	void recordTransfer(const double& transferAmount, BankAccount* p_theTransferAccount_);

    void performSubMenuCommand( int);
    //commands
    //option 1
    void m1_produceBalance() const;
    //option 2
    void m2_withdrawFromBankAccount();
    //option 3
    void m3_depositToBankAccount();
    //option 4
    void m4_produceStatement() const;
	//option 5
	void m5_showAllDepositTransactions() const;
	//option 6
	void m6_showMiniStatement() const;
	//option 7
	void m7_searchForTransactions() const;
	//option 8
	void m8_clearTransactionsUpToDate() const;
	//option 9
	void m9_transferCashToAnotherAccount();

	//current account functions
	void requestOverdraftLimit();

	//savings account functions
	void requestMinimumBalance();

	//child account functions
	void requestDepositConstraints();

    //support file handling functions & creation of dynamic objects

	void searchTransactions() const;
    bool canOpenFile( const string&) const;
	int checkAccountType( const string&) const;
	bool linkedCard( string cashCardFileName) const;

	BankAccount* activateBankAccount( const string&);
	BankAccount* releaseBankAccount( BankAccount*, string);

    void activateCashCard( const string&);
	void releaseCashCard();
};

#endif
