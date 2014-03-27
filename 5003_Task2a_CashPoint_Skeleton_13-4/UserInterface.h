//Pascale Vacher - March 14
//OOP Assignment Semester 2

#ifndef UserInterfaceH 
#define UserInterfaceH

//---------------------------------------------------------------------------
//UserInterface: class declaration
//---------------------------------------------------------------------------

#include "constants.h"
#include "Date.h"

#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

class UserInterface {
public:
	//constructors & destructor
    void	showWelcomeScreen() const;
    void	showByeScreen() const;

	int		readInCardIdentificationCommand() const;
	int		readInAccountProcessingCommand() const;

	void	showErrorInvalidCommand() const;
    void	wait() const;
	const string	readInCardToBeProcessed( string& cardNum) const;
    void	showValidateCardOnScreen( int validCode, const string& cardNum) const;
	void	showCardOnScreen( const string& cardSt) const;
	const string  readInAccountToBeProcessed( string& aNum, string& sCod) const;
	void	showValidateAccountOnScreen( int valid, const string& aNum, const string& sCod) const;

    double	readInWithdrawalAmount() const;
    double	readInDepositAmount() const;
	int		getNumberOfTransactions() const;
	bool	readInConfirmDeletion() const;
	double	readInTransferAmount() const;

    void	showProduceBalanceOnScreen( double bal) const;
    void	showDepositOnScreen( bool auth, double deposit) const;
    void	showWithdrawalOnScreen( bool auth, double withdrawal) const;
    void	showStatementOnScreen( const string&) const;
	void	showMiniStatementOnScreen(const string&) const;
	void	showAllDepositsOnScreen(bool noTransaction, string str, double total) const;
	void	showDeletionOfTransactionUpToDateOnScreen(const Date& date, const int& numOfTr, const bool& deletionConfirmed) const;
	void	showNoTransactionsUpToDateOnScreen(const Date& date) const;
	void	showTransactionsUpToDateOnScreen(const bool& noTransactions, const Date& d, const int& numOfTr, const string& str) const;
	void	showTransferOnScreen(const bool& trOutOK, const bool& trInOK, const double& transferAmount) const;
	void	showOverdraftLimitOnScreen(const double& oD) const;
	Date	readInValidDate(const Date& date) const;

	void	showNoTransactionsOnScreen() const;
	void	showSearchMenu() const;
	int		readInSearchCommand() const;
	template <typename T> T readInSearchAmount() const
	{
		T amount;
		cout << "\n ENTER SEARCH AMOUNT:  ";
		cin >> amount;
		return amount;
		//return searchAmount;
	}
	template <> Date readInSearchAmount<Date>() const
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

	void	showMatchingTransactionsOnScreen( const string& results) const;
private:
    //support functions 
	void	showCardIdentificationMenu() const;
	void	showAccountProcessingMenu() const;
    int		readInCommand() const;
    double	readInPositiveAmount() const;
};

#endif
