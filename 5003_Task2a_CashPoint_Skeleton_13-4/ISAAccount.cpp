////////////////////////////////////////////
//				GROUP UT1				  //
//	   <(''<) Chad Simpson (>'')>         //
//     Q(''O)  Luke Ward   Q(''O)         //
//	  <(._.<)  Shaun Webb  (>._.)>        //
////////////////////////////////////////////

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
	return (((amount + currentYearlyDeposit) < maximumYearlyDeposit) && (Date::currentDate() <= endDepositPeriod));
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
	updateCurrentYearlyDeposit(amount);
    updateBalance( amount);			//increase balance_
}

bool ISAAccount::canTransferOut(double amount, string& probStr) const
{
	if (amount <= (getBalance() - getMinimumBalance()))
		return true;
	else
		probStr = "THE REQUESTED AMOUNT EXCEEDS YOUR MINIMUM BALANCE";
}

bool ISAAccount::canTransferIn(double amount, string& probStr) const
{
	if ((amount + currentYearlyDeposit) < maximumYearlyDeposit && Date::currentDate() <= endDepositPeriod)
		return true;
	else if ((amount + currentYearlyDeposit) > maximumYearlyDeposit)
		probStr = "THE REQUESTED DEPOSIT AMOUNT WOULD EXCEED YOUR MAXIMUM YEARLY DEPOSIT";
	else if (Date::currentDate() > endDepositPeriod)
		probStr = "THE END DEPOSIT PERIOD FOR THIS ACCOUNT HAS PASSED";
	return false;
}

void ISAAccount::recordWithdrawal( double amount)
{
	Transaction aTransaction( "withdrawal_from_ATM", -amount);
    //update active bankaccount
	addTransaction( aTransaction);		//update transactions_
    updateBalance( -amount);			//decrease balance_
}

void ISAAccount::recordTransferIn(const double& amount, const string& aAN, const string& aSC)
{
	Transaction transferTransaction( "transfer_from_ACC_" + aAN + "_" + aSC, amount);

	addTransaction(transferTransaction);
	updateCurrentYearlyDeposit(amount);
	updateBalance(amount);
}

void ISAAccount::recordTransferOut(const double& amount, const string& tAN, const string& tSC)
{
	Transaction transferTransaction( "transfer_to_ACC_" + tAN + "_" + tSC, -amount);

	addTransaction(transferTransaction);
	updateBalance(-amount);
}