////////////////////////////////////////////
//				GROUP UT1				  //
//	   <(''<) Chad Simpson (>'')>         //
//     Q(''O)  Luke Ward   Q(''O)         //
//	  <(._.<)  Shaun Webb  (>._.)>        //
////////////////////////////////////////////

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
	TransactionList temp(transactions_);
	TransactionList trl = transactions_.getTransactionsUpToDate(date, temp);
	numOfTr = trl.size();
	str = trl.toFormattedString();
}

bool BankAccount::isEmptyTransactionList() const {
	return transactions_.size() == 0;
}

void BankAccount::produceAllDepositTransactions(string& str, double& total)
{
	TransactionList trl(transactions_.getAllDepositTransactions());
	total = trl.getTotalTransactions();
	str = trl.toFormattedString();
}

void BankAccount::recordDeposit( double amountToDeposit) {
    //create a deposit transaction
	Transaction aTransaction( "deposit_to_ATM", amountToDeposit);
    //update active bankaccount
    transactions_.addNewTransaction( aTransaction);		//update transactions_
    updateBalance( amountToDeposit);			//increase balance_
}

void const BankAccount::produceNMostRecentTransactions(int numOfTr, string& str, double& total) const
{
	TransactionList trl = transactions_.getMostRecentTransactions(numOfTr);
	total = trl.getTotalTransactions();
	str = trl.toFormattedString();
}

void BankAccount::updateBalance(double amount)
{
	balance_ += amount;
}

void BankAccount::addTransaction(Transaction tr)
{
	transactions_.addNewTransaction(tr);
}

void BankAccount::recordDeletionOfTransactionUpToDate(const Date& date) 
{
	transactions_.deleteTransactionsUpToDate(date);
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

void BankAccount::setBADetails(const string& accT, const string& accN, const string& sC, const Date& cDate, const int& bal, const TransactionList& tr)
{
	accountType_ = accT;
	accountNumber_ = accN;
	sortCode_ = sC;
	creationDate_ = cDate;
	balance_ = bal;
	transactions_ = tr;
}

void BankAccount::setFileName(const string& fName)
{
	fileName = fName;
}

string BankAccount::getFileName()
{
	return fileName;
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
