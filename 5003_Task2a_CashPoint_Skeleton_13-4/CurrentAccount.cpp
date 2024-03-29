////////////////////////////////////////////
//				GROUP UT1				  //
//	   <(''<) Chad Simpson (>'')>         //
//     Q(''O)  Luke Ward   Q(''O)         //
//	  <(._.<)  Shaun Webb  (>._.)>        //
////////////////////////////////////////////

#include "CurrentAccount.h"

CurrentAccount::CurrentAccount()
	: overdraftLimit(0.0)
{}

CurrentAccount::~CurrentAccount()
{}

double CurrentAccount::getOverdraftLimit() const
{
	return overdraftLimit;
}

ostream& CurrentAccount::putDataInStream( ostream& os) const
{
	os << getAccountType() << "\n";				//put account type
	os << getAccountNumber() << "\n";			//put account number
	os << getSortCode() << "\n";				//put sort code
    os << getCreationDate() << "\n";			//put creation date
	os << getBalance() << "\n";					//put balance
	os << overdraftLimit << "\n";
	if (  ! getTransactions().size() == 0)
		os << getTransactions();				//put all transactions, one per line
	return os;
}

istream& CurrentAccount::getDataFromStream( istream& is)
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
	is >> overdraftLimit;
	is >> tr;					//get all transactions (if any)
	setBADetails(accT, accN, sC, cDate, bal, tr);
	return is;
}

const string CurrentAccount::prepareFormattedStatement() const
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

const string CurrentAccount::prepareFormattedAccountDetails() const
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
	os << "\nOVERDRAFTLIMIT:  \234" << setw(10) << overdraftLimit;
	return ( os.str());
}

double CurrentAccount::borrowable() const
{
	return (getBalance() + overdraftLimit);
}

bool CurrentAccount::canWithdraw( double amount) const
{
	return (amount <= borrowable());
}
void CurrentAccount::recordDeposit( double amount)
{
	Transaction aTransaction( "deposit_to_ATM", amount);
    //update active bankaccount
    addTransaction( aTransaction);		//update transactions_
    updateBalance( amount);			//increase balance_
}

bool CurrentAccount::canTransferOut(double amount, string& probStr) const
{
	if (amount <= borrowable())
		return true;
	else
		probStr = "ATTEMPTED WITHDRAWL EXCEEDS YOUR OVERDRAFT";
	return false;
}

bool CurrentAccount::canTransferIn(double amount, string& probStr) const
{
	return true;
}

void CurrentAccount::recordWithdrawal( double amount)
{
	Transaction aTransaction( "withdrawal_from_ATM", -amount);
    //update active bankaccount
	addTransaction( aTransaction);		//update transactions_
    updateBalance( -amount);			//decrease balance_
}

void CurrentAccount::recordTransferOut(const double& amount, const string& tAN, const string& tSC)
{
	Transaction transferTransaction( "transfer_to_ACC_" + tAN + "_" + tSC, -amount);

	addTransaction(transferTransaction);
	updateBalance(-amount);
}

void CurrentAccount::recordTransferIn(const double& amount, const string& aAN, const string& aSC)
{
	Transaction transferTransaction( "transfer_from_ACC_" + aAN + "_" + aSC, amount);

	addTransaction(transferTransaction);
	updateBalance(amount);
}