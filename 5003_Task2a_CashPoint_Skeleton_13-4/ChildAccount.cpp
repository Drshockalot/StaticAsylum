#include "ChildAccount.h"

ChildAccount::ChildAccount()
	: minimumPaidIn(0.0),
	  maximumPaidIn(0.0)
{}

ChildAccount::~ChildAccount()
{}

double ChildAccount::getMinimumPaidIn() const
{
	return minimumPaidIn;
}

double ChildAccount::getMaximumPaidIn() const
{
	return maximumPaidIn;
}

bool ChildAccount::canDeposit(const double& amount) const
{
	return(amount >= minimumPaidIn && amount <= maximumPaidIn);
}

ostream& ChildAccount::putDataInStream( ostream& os) const
{
	os << getAccountType() << "\n";				//put account type
	os << getAccountNumber() << "\n";			//put account number
	os << getSortCode() << "\n";				//put sort code
    os << getCreationDate() << "\n";			//put creation date
	os << getBalance() << "\n";					//put balance
	os << getMinimumBalance() << "\n";
	os << getMinimumPaidIn() << "\n";
	os << getMaximumPaidIn() << "\n";
	if (  ! getTransactions().size() == 0)
		os << getTransactions();				//put all transactions, one per line
	return os;
}

istream& ChildAccount::getDataFromStream( istream& is)
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
	is >> minimumPaidIn;
	is >> maximumPaidIn;
	is >> tr;					//get all transactions (if any)
	setBADetails(accT, accN, sC, cDate, bal, tr);
	setMinimumBalance(mB);
	return is;
}

const string ChildAccount::prepareFormattedStatement() const
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
const string ChildAccount::prepareFormattedMiniStatement(int numOfTr) const
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
const string ChildAccount::prepareFormattedAccountDetails() const
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
	os << "\nMINIMUM PAID IN:  \234" << setw(10) << minimumPaidIn;
	os << "\nMAXIMUM PAID IN:  \234" << setw(10) << maximumPaidIn;
	return ( os.str());
}
const string ChildAccount::prepareFormattedMiniAccountDetails(int numOfTr) const
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
	os << "\nMINIMUM PAID IN:  \234" << setw(10) << minimumPaidIn;
	os << "\nMAXIMUM PAID IN:  \234" << setw(10) << maximumPaidIn;
	return ( os.str());
}

double ChildAccount::borrowable() const
{
	return (getBalance() - getMinimumBalance());
}

bool ChildAccount::canWithdraw( double amount) const
{
	return (amount <= borrowable());
}

void ChildAccount::recordDeposit( double amount)
{
	Transaction aTransaction( "deposit_to_ATM", amount);
    //update active bankaccount
    addTransaction( aTransaction);		//update transactions_
    updateBalance( amount);			//increase balance_
}

bool ChildAccount::canTransferOut(double amount) const
{
	return ((amount <= (getBalance() - getMinimumBalance())));
}

bool ChildAccount::canTransferIn(double amount) const
{
	return (amount >= minimumPaidIn && amount <= maximumPaidIn);
}

void ChildAccount::recordWithdrawal( double amount)
{
	Transaction aTransaction( "withdrawal_from_ATM", -amount);
    //update active bankaccount
	addTransaction( aTransaction);		//update transactions_
    updateBalance( -amount);			//decrease balance_
}

void ChildAccount::recordTransferIn(const double& amount, const string& aAN, const string& aSC)
{
	Transaction transferTransaction( "transfer_from_ACC_" + aAN + "_" + aSC, amount);

	addTransaction(transferTransaction);
	updateBalance(amount);
}

void ChildAccount::recordTransferOut(const double& amount, const string& tAN, const string& tSC)
{
	Transaction transferTransaction( "transfer_to_ACC_" + tAN + "_" + tSC, -amount);

	addTransaction(transferTransaction);
	updateBalance(-amount);
}