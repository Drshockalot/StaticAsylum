#include "SavingsAccount.h"

SavingsAccount::SavingsAccount()
	: minimumBalance(0.0)
{}

SavingsAccount::~SavingsAccount()
{}

double SavingsAccount::getMinimumBalance() const
{
	return minimumBalance;
}

void SavingsAccount::setMinimumBalance(const double& mB)
{
	minimumBalance = mB;
}

ostream& SavingsAccount::putDataInStream( ostream& os) const
{
	os << getAccountType() << "\n";				//put account type
	os << getAccountNumber() << "\n";			//put account number
	os << getSortCode() << "\n";				//put sort code
    os << getCreationDate() << "\n";			//put creation date
	os << getBalance() << "\n";					//put balance
	os << minimumBalance << "\n";
	if (  ! getTransactions().size() == 0)
		os << getTransactions();				//put all transactions, one per line
	return os;
}

istream& SavingsAccount::getDataFromStream( istream& is)
{
	string accT, sC, accN;
	int bal;
	Date cDate;
	TransactionList tr;
	is >> accT;						//get account type
    is >> accN;					//get account number
	is >> sC;						//get sort code
 	is >> cDate;					//get creation date
	is >> bal;							//get balance_
	is >> minimumBalance;
	is >> tr;					//get all transactions (if any)
	setBADetails(accT, accN, sC, cDate, bal, tr);
	return is;
}

const string SavingsAccount::prepareFormattedStatement() const
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
const string SavingsAccount::prepareFormattedMiniStatement(int numOfTr) const
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
const string SavingsAccount::prepareFormattedAccountDetails() const
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
	os << "\nMINIMUM BALANCE:  \234" << setw(10) << minimumBalance;
	return ( os.str());
}
const string SavingsAccount::prepareFormattedMiniAccountDetails(int numOfTr) const
{
	ostringstream os;
	//account details
	os << "\nACCOUNT TYPE:    " << getAccountType() << " ACCOUNT";						//display account type
	os << "\nACCOUNT NUMBER:  " << getAccountNumber();									//display account number
	os << "\nSORT CODE:       " << getSortCode();										//display sort code
	os << "\nCREATION DATE:   " << getCreationDate().toFormattedString();				//display creation date
	os << fixed << setprecision(2) << setfill(' ');
	os << "\nBALANCE:         \234" << setw(10) << getBalance();	//display balance
	os << "\nMINIMUM BALANCE:  \234" << setw(10) << minimumBalance;
	return ( os.str());
}

double SavingsAccount::borrowable() const
{
	return (getBalance() - minimumBalance);
}

bool SavingsAccount::canWithdraw( double amount) const
{
	return (amount <= borrowable());
}
void SavingsAccount::recordDeposit( double amount)
{
	Transaction aTransaction( "deposit_to_ATM", amount);
    //update active bankaccount
    addTransaction( aTransaction);		//update transactions_
    updateBalance( amount);			//increase balance_
}

bool SavingsAccount::canTransferOut(double amount) const
{
	return (amount <= (getBalance() - minimumBalance));
}

bool SavingsAccount::canTransferIn(double amount) const
{
	return true;
}

void SavingsAccount::recordWithdrawal( double amount)
{
	Transaction aTransaction( "withdrawal_from_ATM", -amount);
    //update active bankaccount
	addTransaction( aTransaction);		//update transactions_
    updateBalance( -amount);			//decrease balance_
}