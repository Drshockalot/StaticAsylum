#include "ISAAccount.h"

ISAAccount::ISAAccount()
	: maximumYearlyDeposit(0.0),
	  currentYearlyDeposit(0.0),
	  endDepositPeriod(Date())
{}

ISAAccount::~ISAAccount()
{}

double ISAAccount::getMaximumYearlyDeposit() const
{
	return maximumYearlyDeposit;
}

double ISAAccount::getCurrentYearlyDeposit() const
{
	return currentYearlyDeposit;
}

Date ISAAccount::getEndDepositPeriod() const
{
	return endDepositPeriod;
}

void ISAAccount::updateCurrentYearlyDeposit(const double& a)
{
	currentYearlyDeposit += a;
}

bool ISAAccount::canDeposit(const double& amount) const
{
	return (((amount + currentYearlyDeposit) < maximumYearlyDeposit) && (Date::currentDate() < endDepositPeriod));
}

ostream& ISAAccount::putDataInStream( ostream& os) const
{
	os << getAccountType() << "\n";				//put account type
	os << getAccountNumber() << "\n";			//put account number
	os << getSortCode() << "\n";				//put sort code
    os << getCreationDate() << "\n";			//put creation date
	os << getBalance() << "\n";					//put balance
	os << getMinimumBalance() << "\n";
	os << maximumYearlyDeposit << "\n";
	os << currentYearlyDeposit << "\n";
	os << endDepositPeriod << "\n";
	if (  ! getTransactions().size() == 0)
		os << getTransactions();				//put all transactions, one per line
	return os;
}

istream& ISAAccount::getDataFromStream( istream& is)
{
	string accT, sC, accN;
	int bal;
	double mB;
	Date cDate;
	TransactionList tr;
	is >> accT;						//get account type
    is >> accN;					//get account number
	is >> sC;						//get sort code
 	is >> cDate;					//get creation date
	is >> bal;							//get balance_
	is >> mB;
	is >> maximumYearlyDeposit;
	is >> currentYearlyDeposit;
	is >> endDepositPeriod;
	is >> tr;					//get all transactions (if any)
	setBADetails(accT, accN, sC, cDate, bal, tr);
	setMinimumBalance(mB);
	return is;
}

const string ISAAccount::prepareFormattedStatement() const
{
	ostringstream os;
	//account details
	os << prepareFormattedAccountDetails();
	//list of transactions (or message if empty)
	if ( ! getTransactions().size() == 0)
		os << "\n\nLIST OF TRANSACTIONS \n"	<< getTransactions().toFormattedString();	//one per line
	else
		os << "\n\nNO TRANSACTIONS IN BANK ACCOUNT!";
	return ( os.str());
}
const string ISAAccount::prepareFormattedMiniStatement(int numOfTr) const
{
	ostringstream os;

	os << prepareFormattedMiniAccountDetails(numOfTr);
	TransactionList tr = getRequestedNumberOfTransactions(numOfTr);
	if ( ! getTransactions().size() == 0)
		os << "\n\nLIST OF TRANSACTIONS\n" << tr.toFormattedString();	//one per line
	else
		os << "\n\nNO TRANSACTIONS IN BANK ACCOUNT!";
	return ( os.str());
}
const string ISAAccount::prepareFormattedAccountDetails() const
{
	//collect account details in string
	ostringstream os;
	//account details
	os << "\nACCOUNT TYPE:    " << getAccountType() << " ACCOUNT";						//display account type
	os << "\nACCOUNT NUMBER:  " << getAccountNumber();									//display account number
	os << "\nSORT CODE:       " << getSortCode();										//display sort code
	os << "\nCREATION DATE:   " << getCreationDate().toFormattedString();				//display creation date
	os << fixed << setprecision(2) << setfill(' ');
	os << "\nBALANCE:         \234" << setw(10) << getBalance();	//display balance
	os << "\nMINIMUM BALANCE:  \234" << setw(10) << getMinimumBalance();
	os << "\nMAXIMUM YEARLY DEPOSIT: \234" << setw(10) << maximumYearlyDeposit;
	os << "\nCURRENT YEARLY DEPOSIT: \234" << setw(10) << currentYearlyDeposit;
	os << "\nEND DEPOSIT PERIOD: " << endDepositPeriod;
	return ( os.str());
}
const string ISAAccount::prepareFormattedMiniAccountDetails(int numOfTr) const
{
	ostringstream os;
	//account details
	os << "\nACCOUNT TYPE:    " << getAccountType() << " ACCOUNT";						//display account type
	os << "\nACCOUNT NUMBER:  " << getAccountNumber();									//display account number
	os << "\nSORT CODE:       " << getSortCode();										//display sort code
	os << "\nCREATION DATE:   " << getCreationDate().toFormattedString();				//display creation date
	os << fixed << setprecision(2) << setfill(' ');
	os << "\nBALANCE:         \234" << setw(10) << getBalance();	//display balance
	os << "\nMINIMUM BALANCE:  \234" << setw(10) << getMinimumBalance();
	os << "\nMAXIMUM YEARLY DEPOSIT: \234" << setw(10) << maximumYearlyDeposit;
	os << "\nCURRENT YEARLY DEPOSIT: \234" << setw(10) << currentYearlyDeposit;
	os << "\nEND DEPOSIT PERIOD: " << endDepositPeriod;
	return ( os.str());
}

double ISAAccount::borrowable() const
{
	return (getBalance() - getMinimumBalance());
}

bool ISAAccount::canWithdraw( double amount) const
{
	return (amount <= borrowable());
}
void ISAAccount::recordDeposit( double amount)
{
	Transaction aTransaction( "deposit_to_ATM", amount);
    //update active bankaccount
    addTransaction( aTransaction);		//update transactions_
    updateBalance( amount);			//increase balance_
}

bool ISAAccount::canTransferOut(double amount) const
{
	return (amount <= (getBalance() - getMinimumBalance()));
}

bool ISAAccount::canTransferIn(double amount) const
{
	return (currentYearlyDeposit < maximumYearlyDeposit && Date::currentDate() <= endDepositPeriod);
}

void ISAAccount::recordWithdrawal( double amount)
{
	Transaction aTransaction( "withdrawal_from_ATM", -amount);
    //update active bankaccount
	addTransaction( aTransaction);		//update transactions_
    updateBalance( -amount);			//decrease balance_
}