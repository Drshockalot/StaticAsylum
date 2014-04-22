////////////////////////////////////////////
//				GROUP UT1				  //
//	   <(''<) Chad Simpson (>'')>         //
//     Q(''O)  Luke Ward   Q(''O)         //
//	  <(._.<)  Shaun Webb  (>._.)>        //
////////////////////////////////////////////

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
	static UserInterface* getInstance(){
		static UserInterface instance;
		return &instance;
	}

    void	showWelcomeScreen() const;
    void	showByeScreen() const;

	int		readInCardIdentificationCommand() const;
	int		readInAccountProcessingCommand(const string& accType) const;

	void	showErrorInvalidCommand() const;
    void	wait() const;
	const string	readInCardToBeProcessed( string& cardNum) const;
    void	showValidateCardOnScreen( int validCode, const string& cardNum) const;
	void	showCardOnScreen( const string& cardSt) const;
	const string  readInAccountToBeProcessed( string& aNum, string& sCod) const;
	void	showValidateAccountOnScreen( int valid, const string& aNum, const string& sCod) const;

    double	readInWithdrawalAmount() const;
    double	readInDepositAmount() const;
	int		readInNumberOfTransactions() const;
	bool	readInConfirmDeletion() const;
	double	readInTransferAmount() const;

    void	showProduceBalanceOnScreen( double bal) const;
    void	showDepositOnScreen( bool auth, double deposit) const;
    void	showWithdrawalOnScreen( bool auth, double withdrawal) const;
    void	showStatementOnScreen( const string&) const;
	void	showMiniStatementOnScreen(const int&, const string&, const double&) const;
	void	showAllDepositsOnScreen(bool noTransaction, string str, double total) const;
	void	showDeletionOfTransactionUpToDateOnScreen(const Date& date, const int& numOfTr, const bool& deletionConfirmed) const;
	void	showNoTransactionsUpToDateOnScreen(const Date& date) const;
	void	showTransactionsUpToDateOnScreen(const bool& noTransactions, const Date& d, const int& numOfTr, const string& str) const;
	void	showTransferOnScreen(const bool& trOutOK, const bool& trInOK, const double& transferAmount) const;
	void	showOverdraftLimitOnScreen(const double& oD) const;
	void	showMinimumBalanceOnScreen(const double& mB) const;
	void	showDepositConstraintsOnScreen(const double& minPI, const double& maxPI) const;
	void	showIsaDetailsOnScreen(const double& maxYD, const double& currYD, const Date& eOD) const;
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
	template <typename T> Date readInSearchAmount(T cr) const
	{
		int day,month,year;
		Date searchDate;
		do{
			cout << "\n ENTER VALID DATE: "
			cout << "\n ENTER SEARCH DAY:  ";
			cin >> day;
			cout << "\n ENTER SEARCH MONTH:  ";
			cin >> month;
			cout << "\n ENTER SEARCH YEAR:  ";
			cin >> year;
			searchDate = Date(day, month, year);
		} while (!searchDate.isValidDate(cr));
		return searchDate;
	}

	void	showMatchingTransactionsOnScreen( const string& results) const;
private:
    //support functions 
	UserInterface(){}
	UserInterface(const UserInterface &){}
	UserInterface& operator=(const UserInterface &){}

	void	showCardIdentificationMenu() const;
	void	showAccountProcessingMenu(const string& accType) const;
    int		readInCommand() const;
    double	readInPositiveAmount() const;
};

#endif
