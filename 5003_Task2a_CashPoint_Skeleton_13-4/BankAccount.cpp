//Pascale Vacher - March 14
//OOP Assignment Semester 2

#include "BankAccount.h"

//---------------------------------------------------------------------------
//BankAccount: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

BankAccount::BankAccount()
    : accountNumber_( "null"),
      sortCode_( "null"),
	  balance_( 0.0)
{}
BankAccount::BankAccount( const string& typ, const string& acctNum, const string& sCode,
                          const Date& cD, double b,
                          const TransactionList& trList)
    : accountType_(typ),
	  accountNumber_( acctNum), sortCode_( sCode),
      creationDate_( cD),
      balance_( b),
      transactions_( trList)
{}
BankAccount::~BankAccount()
{}


//____other public member functions

const string BankAccount::getAccountType() const {
    return accountType_;
}
const string BankAccount::getAccountNumber() const {
    return accountNumber_;
}
const string BankAccount::getSortCode() const {
    return sortCode_;
}
const Date BankAccount::getCreationDate() const {
    return creationDate_;
}
double BankAccount::getBalance() const {
    return balance_;
}
const TransactionList BankAccount::getTransactions() const {
    return transactions_;
}

const void BankAccount::produceTransactionsUpToDate(const Date& date, string& str, int& numOfTr)
{
	TransactionList trl = transactions_.getTransactionsUpToDate(date);
	numOfTr = trl.size();
	str = trl.toFormattedString();
}

void BankAccount::clearTransactions(TransactionList tr)
{
	TransactionList deleteCopy(tr);
	while(deleteCopy.size() > 0)
	{
//		if(deleteCopy.newestTransaction() == transactions_.newestTransaction())
		transactions_.deleteGivenTransaction(deleteCopy.newestTransaction());
		deleteCopy.deleteFirstTransaction();
	}
}

bool BankAccount::isEmptyTransactionList() const {
	return transactions_.size() == 0;
}

void BankAccount::produceAllDepositTransactions(string& s, double& d)
{
	TransactionList trl(transactions_.getAllDepositTransactions());
	d = trl.getTotalTransactions();
	s = trl.toFormattedString();
}

void BankAccount::showAllDepositsOnScreen(bool& b, string& s, double& d) const
{

}

void BankAccount::recordDeposit( double amountToDeposit) {
    //create a deposit transaction
	Transaction aTransaction( "deposit_to_ATM", amountToDeposit);
    //update active bankaccount
    transactions_.addNewTransaction( aTransaction);		//update transactions_
    updateBalance( amountToDeposit);			//increase balance_
}

void BankAccount::addTransaction(Transaction tr)
{
	transactions_.addNewTransaction(tr);
}

void BankAccount::recordDeletionOfTransactionUpToDate(const Date& date) 
{
	transactions_.deleteTransactionsUpToDate(date);
}

double BankAccount::borrowable() const {
//return borrowable amount
    return balance_;
}
bool BankAccount::canWithdraw( double amountToWithdraw ) const {
//check if enough money in account
    return ( amountToWithdraw <= borrowable());
}

bool BankAccount::canTransferOut(double transferAmount) const
{
	return (transferAmount < getBalance());
}

bool BankAccount::canTransferIn(double transferAmount) const
{
	return true;
}

void BankAccount::recordTransferIn(const double& amount, const string& aAN, const string& aSC)
{
	Transaction transferTransaction( "transfer_from_ACC_" + aAN + "_" + aSC, amount);

	transactions_.addNewTransaction(transferTransaction);
	updateBalance(amount);
}

void BankAccount::recordTransferOut(const double& amount, const string& tAN, const string& tSC)
{
	Transaction transferTransaction( "transfer_to_ACC_" + tAN + "_" + tSC, -amount);

	transactions_.addNewTransaction(transferTransaction);
	updateBalance(-amount);
}

void BankAccount::recordWithdrawal( double amountToWithdraw) {
	//create a withdrawal transaction
    Transaction aTransaction( "withdrawal_from_ATM", -amountToWithdraw);
    //update active bankaccount
    transactions_.addNewTransaction( aTransaction);		//update transactions_
    updateBalance( -amountToWithdraw);			//decrease balance_
}

const string BankAccount::prepareFormattedStatement() const {
	ostringstream os;
	//account details
	os << prepareFormattedAccountDetails();
	//list of transactions (or message if empty)
	if ( ! transactions_.size() == 0)
		os << "\n\nLIST OF TRANSACTIONS \n"	<< transactions_.toFormattedString();	//one per line
	else
		os << "\n\nNO TRANSACTIONS IN BANK ACCOUNT!";
	return ( os.str());
}

const string BankAccount::prepareFormattedMiniStatement(int numOfTr) const
{
	ostringstream os;

	os << prepareFormattedMiniAccountDetails(numOfTr);
	TransactionList tr = getRequestedNumberOfTransactions(numOfTr);
	if ( ! transactions_.size() == 0)
		os << "\n\nLIST OF TRANSACTIONS\n" << tr.toFormattedString();	//one per line
	else
		os << "\n\nNO TRANSACTIONS IN BANK ACCOUNT!";
	return ( os.str());
}

const TransactionList BankAccount::getRequestedNumberOfTransactions(int numOfTr) const
{
	TransactionList copy(getTransactions());
	TransactionList temp;
	for(int i = 0 ; i < numOfTr ; ++i)
	{
		if(copy.size() > 0)
		{
			temp.addTransaction(copy.newestTransaction());
			copy.deleteFirstTransaction();
		}

	}
	return temp;
}

void BankAccount::readInBankAccountFromFile( const string& fileName) {
	ifstream fromFile;
	fromFile.open( fileName.c_str(), ios::in); 	//open file in read mode
	if ( fromFile.fail())
		cout << "\nAN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
        fromFile >> (*this);  	//read  all info from bank account file
    fromFile.close();			//close file: optional here
}

void BankAccount::storeBankAccountInFile( const string& fileName) const {
	ofstream toFile;
	toFile.open( fileName.c_str(), ios::out);	//open copy file in write mode
	if ( toFile.fail())
		cout << "\nAN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
        toFile << (*this);	//store all info to bank account file
	toFile.close();			//close file: optional here
}

ostream& BankAccount::putDataInStream( ostream& os) const {
//put (unformatted) BankAccount details in stream
    os << accountType_ << "\n";				//put account type
    os << accountNumber_ << "\n";			//put account number
	os << sortCode_ << "\n";				//put sort code
    os << creationDate_ << "\n";			//put creation date
	os << balance_ << "\n";					//put balance
	if (  ! transactions_.size() == 0)
		os << transactions_;				//put all transactions, one per line
	return os;
}
istream& BankAccount::getDataFromStream( istream& is) {
//get BankAccount details from stream
    is >> accountType_;						//get account type
    is >> accountNumber_;					//get account number
	is >> sortCode_;						//get sort code
 	is >> creationDate_;					//get creation date
	is >> balance_;							//get balance_
	is >> transactions_;					//get all transactions (if any)
	return is;
}

void BankAccount::setBADetails(const string& accT, const int& accN, const string& sC, const Date& cDate, const int& bal, const TransactionList& tr)
{
	accountType_ = accT;
	accountNumber_ = accN;
	sortCode_ = sC;
	creationDate_ = cDate;
	balance_ = bal;
	transactions_ = tr;
}

//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------

void BankAccount::updateBalance( double amount) {
    balance_ += amount;   //add/take amount to/from balance_
}
const string BankAccount::prepareFormattedAccountDetails() const {
	//collect account details in string
	ostringstream os;
	//account details
	os << "\nACCOUNT TYPE:    " << accountType_ << " ACCOUNT";						//display account type
	os << "\nACCOUNT NUMBER:  " << accountNumber_;									//display account number
	os << "\nSORT CODE:       " << sortCode_;										//display sort code
	os << "\nCREATION DATE:   " << creationDate_.toFormattedString();				//display creation date
	os << fixed << setprecision(2) << setfill(' ');
	os << "\nBALANCE:         \234" << setw(10) << balance_;	//display balance
	return ( os.str());
}

const string BankAccount::prepareFormattedMiniAccountDetails(int numOfTr) const
{
	ostringstream os;
	os << "\nACCOUNT TYPE:    " << accountType_ << " ACCOUNT";						//display account type
	os << "\nACCOUNT NUMBER:  " << accountNumber_;									//display account number
	os << "\nSORT CODE:       " << sortCode_;										//display sort code
	os << "\nCREATION DATE:   " << creationDate_.toFormattedString();				//display creation date
	os << fixed << setprecision(2) << setfill(' ');
	os << "\nBALANCE:         \234" << setw(10) << balance_;	//display balance
	return os.str();
}
//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream& os, const BankAccount& aBankAccount) {
//put (unformatted) BankAccount details in stream
    return ( aBankAccount.putDataInStream( os));
}
istream& operator>>( istream& is, BankAccount& aBankAccount) {
//get BankAccount details from stream
	return ( aBankAccount.getDataFromStream( is));
}
