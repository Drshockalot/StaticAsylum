//Pascale Vacher - March 14
//OOP Assignment Semester 2

#include "UserInterface.h" 
#include "Date.h"
#include "Time.h"
//---------------------------------------------------------------------------
//UserInterface: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

//____other public member functions

//menu functions

void UserInterface::wait() const {
	char ch;
	cout << "\n\nPress RETURN to go back to menu\n";
	cin.get( ch);
	cin.get( ch);
//	flushall();
}
int UserInterface::readInCardIdentificationCommand() const {
    showCardIdentificationMenu();
    return ( readInCommand());
}
void UserInterface::showCardIdentificationMenu() const {
	cout << "\n\n\n      ________________________________________";
	cout << "\n      _______CARD IDENTIFICATION MENU________";
	cout << "\n      ________________________________________";
	cout << "\n       0           Quit CashPoint application";
	cout << "\n       1              Enter your card details";
	cout << "\n      ________________________________________";
}
int UserInterface::readInAccountProcessingCommand() const{
    showAccountProcessingMenu();
    return ( readInCommand());
}
void UserInterface::showAccountProcessingMenu() const {
	cout << "\n\n\n      ________________________________________";
	cout << "\n      ________ACCOUNT PROCESSING MENU________";
	cout << "\n      ________________________________________";
	cout << "\n       0 End account processing & remove card";
	cout << "\n       1                      Display balance";
	cout << "\n       2                Withdraw from account";
	cout << "\n       3                 Deposit into account";
	cout << "\n       4                       Show statement";
	cout << "\n       5                    Show all deposits";
	cout << "\n       6                  Show mini statement";
	cout << "\n       6                  Show mini statement";
	cout << "\n       7          Search account transactions";
	cout << "\n       8    Clear all transactions up to date";
	cout << "\n       9          Transfer to another account  //TO BE IMPLEMENTED FOR ASS 2";
	cout << "\n         ________________________________________";
}

const string UserInterface::readInCardToBeProcessed( string& aCardNumber) const {
	cout << "\n SELECT THE CARD ...\n";
	cout << "   CARD NUMBER:  ";         //ask for card number
    cin >> aCardNumber;
    cout << "\n=========================================";
    //create card file name
    return( FILEPATH + "card_" + aCardNumber + ".txt");
}

void UserInterface::showValidateCardOnScreen( int validCode, const string& cashCardNum) const {
    switch( validCode)
    {
    	case VALID_CARD:		//card valid: it exists, is accessible with that card (and not already open: TO BE IMPLEMENTED)
			cout << "\nTHE CARD (NUMBER: " << cashCardNum << ") EXIST!";
            break;
    	case UNKNOWN_CARD:		//card does not exist
			cout << "\nERROR: INVALID CARD\n"
                 << "\nTHE CARD (NUMBER: " << cashCardNum << ") DOES NOT EXIST!";
            break;
    	case EMPTY_CARD:		//account exists but is not accessible with that card
        	cout << "\nERROR: EMPTY CARD"
                  << "\nTHE CARD (NUMBER: " << cashCardNum << ") DOES NOT LINK TO ANY ACCOUNT!";
             break;
    }
}

void UserInterface::showCardOnScreen( const string& aCardDetails) const {
    cout << "\n=========================================";
    cout << "\n________ CARD DETAILS ___________________";
	cout << aCardDetails;
    cout << "\n________ END CARD DETAILS _______________";
    cout << "\n=========================================";
}

const string UserInterface::readInAccountToBeProcessed( string& anAccountNumber, string& aSortCode) const {
    cout << "\n SELECT THE ACCOUNT ...\n";
	cout << "   ACCOUNT NUMBER:  ";	//ask for account number
    cin >> anAccountNumber;
	cout << "   SORT CODE:       ";	//ask for sort code
    cin >> aSortCode;
    cout << "\n=========================================";
    //create account file name
    return( FILEPATH + "account_" + anAccountNumber + "_" + aSortCode + ".txt");
}

Date UserInterface::readInValidDate(const Date& cd) const
{
	Date date;
	cout << "\nENTER DATE: ";
	cin >> date;
	while(!date.isValidDate(cd))
	{
		cout << "\nINVALID DATE!";
		cout << "\nENTER DATE: ";
		cin >> date;
	}
	return date;
}

void UserInterface::showValidateAccountOnScreen( int validCode, const string& accNum, const string& srtCode) const {
    switch( validCode)
    {
    	case VALID_ACCOUNT:		//account valid: it exists, is accessible with that card (and not already open: TO BE IMPLEMENTED)
        	cout << "\nTHE ACCOUNT (NUMBER: " << accNum
             	 << " CODE: " << srtCode << ") IS NOW OPEN!";
            break;
    	case UNKNOWN_ACCOUNT:		//account does not exist
        	cout << "\nERROR: INVALID ACCOUNT"
                 << "\nTHE ACCOUNT (NUMBER: " << accNum
                 << " CODE: " << srtCode << ") DOES NOT EXIST!";
            break;
    	case UNACCESSIBLE_ACCOUNT:		//account exists but is not accessible with that card
        	cout << "\nERROR: INVALID ACCOUNT"
             	 << "\nTHE ACCOUNT (NUMBER: " << accNum
             	 << " CODE: " << srtCode << ") IS NOT ACCESSIBLE WITH THIS CARD!";
            break;
    }
}

//input functions

double UserInterface::readInWithdrawalAmount() const {
    //ask for the amount to withdraw
    cout << "\nAMOUNT TO WITHDRAW: \234" ;
	return ( readInPositiveAmount());
}
double UserInterface::readInDepositAmount() const {
    //ask for the amount to deposit
    cout << "\nAMOUNT TO DEPOSIT: \234" ;
	return ( readInPositiveAmount());
}
int UserInterface::getNumberOfTransactions() const 
{
	cout << "\nNUMBER OF TRANSACTIONS : ";
	return ( readInPositiveAmount());
}
bool UserInterface::readInConfirmDeletion() const
{
	int choice;
	cout << "\nCONFIRM TO CLEAR SELECTED TRANSACTIONS\n";
	cout << "1 = yes\n";
	cout << "0 = no\n";
	cin >> choice;
	return(choice == 1);
}
//output functions

void UserInterface::showDeletionOfTransactionUpToDateOnScreen(const Date& date, const int& numOfTr, const bool& deletionConfirmed) const
{
	if(deletionConfirmed)
		cout << "\nTHE " << numOfTr << " TRANSACTIONS IN BANK ACCOUNT UP TO DATE " << date.toFormattedString() << " HAVE BEEN DELETED\n";
}

void UserInterface::showNoTransactionsUpToDateOnScreen(const Date& date) const
{
	cout << "\n THERE ARE NO TRANSACTIONS IN THIS ACCOUNT UP TO DATE " << date << "\n";
}

void UserInterface::showProduceBalanceOnScreen( double balance) const {
	cout << fixed << setprecision(2) << setfill(' ');
    cout << "\nTHE CURRENT BALANCE IS: \234" << setw(12) << balance;//display balance
}
void UserInterface::showWithdrawalOnScreen( bool trAuthorised, double amountWithdrawn) const {
    if ( trAuthorised)
    	cout << "\nTRANSACTION AUTHORISED!: \n\234"
             << setw(0) << amountWithdrawn
             << " WITHDRAWN FROM ACCOUNT";
    else //not enough money
		cout << "\nTRANSACTION IMPOSSIBLE!";
}
void UserInterface::showDepositOnScreen( bool trAuthorised, double amountDeposited) const {
    if ( trAuthorised)
    	cout << "\nTRANSACTION AUTHORISED!:\n\234"
             << setw(0) << amountDeposited
             << " DEPOSITED INTO ACCOUNT";
    else //too much to deposit
		cout << "\nTRANSACTION IMPOSSIBLE!";
}
void UserInterface::showStatementOnScreen( const string& statement) const {
    cout << "\nPREPARING STATEMENT...";
    cout << "\n________ ACCOUNT STATEMENT _____";
	cout << statement;
    cout << "\n________ END ACCOUNT STATEMENT _____";
}

void UserInterface::showMiniStatementOnScreen(const string& miniStatement) const
{
	cout << "\nPREPARING MINI STATEMENT...";
	cout << "\n________ ACCOUNT MINI STATEMENT _____";
	cout << miniStatement;
	cout << "\n________ END ACCOUNT MINI STATEMENT _____";
}

void UserInterface::showTransactionsUpToDateOnScreen(const bool& noTransaction, const Date& d, const int& numOfTr, const string& str) const
{
	if(!noTransaction)
	{
	cout << "\nLIST OF TRANSACTIONS PENDING FOR DELETION: ";
	cout << "\n" << str;
	}
	else
		cout << "NO TRANSACTIONS IN BANK ACCOUNT";
}

//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------

void UserInterface::showWelcomeScreen() const {
	cout << "\n\n\n             _____WELCOME TO THE ATM_____";
}
void UserInterface::showByeScreen() const {
    cout << "\n\n\n________________NEXT CUSTOMER...\n\n";
}
int UserInterface::readInCommand() const{
	int com;
	cout << "\n          ENTER YOUR COMMAND: ";
	cin >> com;
	return com;
}
void UserInterface::showErrorInvalidCommand() const {
	cout << "\nINVALID COMMAND CHOICE, TRY AGAIN";
}
double UserInterface::readInPositiveAmount() const {
    double amount;
	cin >> amount;
	while ( amount <= 0.0)
    {
	    cout << "\nAMOUNT SHOULD BE A POSITIVE AMOUNT, TRY AGAIN: ";
		cin >> amount;
	}
    return amount;
}
void UserInterface::showAllDepositsOnScreen(bool noTransaction, string str, double total) const
{
	if(!noTransaction)
	{
	cout << "\nALL DEPOSIT TRANSACTIONS REQUESTED AT " << Time::currentTime() << "ON" << Date::currentDate();
	cout << "\n" << str;
	cout << "\n" << "Total amount of deposits: " << "\234" << total;
	}
	else
	{
		cout << "NO TRANSACTIONS IN BANK ACCOUNT";
	}
}
void UserInterface::showNoTransactionsOnScreen() const
{
	cout << "\nNO TRANSACTIONS AVAILABLE AT THIS TIME";
}

void UserInterface::showSearchMenu() const
{
	cout << "\n___________Search Transactions_____________ ";
	cout << "\n       1	By amount";
	cout << "\n       2 By title";
	cout << "\n       3	By date";
	cout << "\n       4 Exit search";
}
int UserInterface::readInSearchCommand() const
{
	cout << "\n ENTER YOUR COMMAND:  ";
	int option;
	cin >> option;
	return option;
}
double UserInterface::readInSearchAmount() const
{
	double amount;
	cout << "\n ENTER SEARCH AMOUNT:  ";
	cin >> amount;
	return amount;
	//return searchAmount;
}
string UserInterface::readInSearchString() const
{
	string amount;
	cout << "\n ENTER SEARCH AMOUNT:  ";
	cin >> amount;
	cout << amount;
	return amount;
}
Date UserInterface::readInSearchDate() const
{
	int day,month,year;
	cout << "\n ENTER SEARCH DAY:  ";
	cin >> day;
	cout << "\n ENTER SEARCH MONTH:  ";
	cin >> month;
	cout << "\n ENTER SEARCH YEAR:  ";
	cin >> year;
	Date searchDate(day,month,year);
	return searchDate;
}
void UserInterface::showMatchingTransactionsOnScreen( const string& results) const {
    cout << "\n________ SEARCH RESULTS _____";
	cout << results;
}