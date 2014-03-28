//Pascale Vacher - March 14
//OOP Assignment Semester 2

#include "CashPoint.h"

//---------------------------------------------------------------------------
//CashPoint: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

CashPoint::CashPoint()
	: p_theActiveAccount_( nullptr), p_theCashCard_( nullptr), p_theTransferAccount_( nullptr)
{ }

CashPoint::~CashPoint()
{
	assert( p_theActiveAccount_ == nullptr);
	assert( p_theCashCard_ == nullptr);
}

//____other public member functions

void CashPoint::activateCashPoint() {
	int command;
	theUI_.showWelcomeScreen();
    command = theUI_.readInCardIdentificationCommand();
	while ( command != QUIT_COMMAND)
    {
		performCardCommand( command);
	    theUI_.showByeScreen();
		command = theUI_.readInCardIdentificationCommand();
	}

}

//---------------------------------------------------------------------------
//private support member functions
//---------------------------------------------------------------------------

void CashPoint::performCardCommand( int option) {
    switch ( option)
	{
		case 1:
        {
            //read in card number and check that it is valid
            string cashCardNum;
			string cashCardFileName( theUI_.readInCardToBeProcessed( cashCardNum));	//read in card name & produce cashcard filename
            int validCardCode( validateCard( cashCardFileName));		//check valid card
            theUI_.showValidateCardOnScreen( validCardCode, cashCardNum);
            if ( validCardCode == VALID_CARD) //valid card
            {
				//dynamically create a cash card & store card data
        		activateCashCard( cashCardFileName);
				//display card data with available accounts
				string s_card( p_theCashCard_->toFormattedString());
				theUI_.showCardOnScreen( s_card);
				//process all request for current card (& bank accounts)
                processOneCustomerRequests();
				//free memory space used by cash card
				releaseCashCard();
            }
            break;
		}
		default:theUI_.showErrorInvalidCommand();
	}
}
int CashPoint::validateCard( const string& cashCardFileName) const {
//check that the card exists (valid)
    if ( ! canOpenFile( cashCardFileName))   //invalid card
        return UNKNOWN_CARD;
    else    //card empty (exist but no bank account listed on card)
		if ( ! linkedCard( cashCardFileName))  
			return EMPTY_CARD;
		else
			//card valid (exists and linked to at least one bank account)
			return VALID_CARD;
}

int CashPoint::validateAccount( const string& bankAccountFileName) const {
//check that the account is valid 
//MORE WORK NEEDED: in case of transfer
    int validBankCode;
    if ( ! canOpenFile( bankAccountFileName)) 
		//account does not exist
		validBankCode = UNKNOWN_ACCOUNT;
	else
	  	//unaccessible account (exist but not listed on card)
		if ( ! p_theCashCard_->onCard( bankAccountFileName))     
    		validBankCode = UNACCESSIBLE_ACCOUNT;
		else
			//account valid (exists and accessible)
       		validBankCode = VALID_ACCOUNT;
    return validBankCode;
}

void CashPoint::processOneCustomerRequests() {
//process from one account
    string anAccountNumber, anAccountSortCode;
    //select active account and check that it is valid
    string bankAccountFileName( theUI_.readInAccountToBeProcessed( anAccountNumber, anAccountSortCode));
    int validAccountCode( validateAccount( bankAccountFileName));  //check valid account
    theUI_.showValidateAccountOnScreen( validAccountCode, anAccountNumber, anAccountSortCode);
    if ( validAccountCode == VALID_ACCOUNT) //valid account: exists, accessible with card & not already open
    {
       	//dynamically create a bank account to store data from file
        p_theActiveAccount_ = activateBankAccount( bankAccountFileName);
		//process all request for current card (& bank accounts)
    	processOneAccountRequests();
		//store new state of bank account in file & free bank account memory space
        p_theActiveAccount_ = releaseBankAccount( p_theActiveAccount_, bankAccountFileName);
    }
}

void CashPoint::processOneAccountRequests() {
    int option;
	//select option from account processing menu
	string accType = p_theActiveAccount_->getAccountType();
  	option = theUI_.readInAccountProcessingCommand(accType);
	while ( option != QUIT_COMMAND)
	{
		performAccountProcessingCommand( option);   //process command for selected option
		theUI_.wait();
		string accType = p_theActiveAccount_->getAccountType();
        option = theUI_.readInAccountProcessingCommand(accType);   //select another option
	}
}

void CashPoint::attemptTransfer(BankAccount* p_theTransferAccount_)
{
	double transferAmount = theUI_.readInTransferAmount();
	bool trOutOK = p_theActiveAccount_->canTransferOut(transferAmount);
	bool trInOK = p_theTransferAccount_->canTransferIn(transferAmount);
	if(trOutOK && trInOK)
		recordTransfer(transferAmount, p_theTransferAccount_);
	theUI_.showTransferOnScreen(trOutOK, trInOK, transferAmount);
}

void CashPoint::recordTransfer(const double& transferAmount, BankAccount* p_theTransferAccount_)
{
	string tAN = p_theTransferAccount_->getAccountNumber();
	string tSC = p_theTransferAccount_->getSortCode();
	p_theActiveAccount_->recordTransferOut(transferAmount, tAN, tSC);
	string aAN = p_theActiveAccount_->getAccountNumber();
	string aSC = p_theActiveAccount_->getSortCode();
	p_theTransferAccount_->recordTransferIn(transferAmount, aAN, aSC);
}

void CashPoint::performAccountProcessingCommand( int option) {
	string accType = p_theActiveAccount_->getAccountType();

	int menu = 0;

	if(accType == "BANK")
		menu = 0;
	else if(accType == "CURRENT")
		menu = 1;
	else if(accType == "SAVINGS")
		menu = 2;
	else if(accType == "CHILD")
		menu = 3;
	else if(accType == "ISA")
		menu = 4;
	switch(menu)
	{
		case 0:
			switch ( option)
			{
				case 1:	m1_produceBalance();
						break;
				case 2: m2_withdrawFromBankAccount();
 						break;
				case 3:	m3_depositToBankAccount();
						break;
				case 4:	m4_produceStatement();
						break;
				case 5: m5_showAllDepositTransactions();
						break;
				case 6: m6_showMiniStatement();
						break;
				case 7: m7_searchForTransactions();
						break;
				case 8: m8_clearTransactionsUpToDate();
						break;
				case 9: m9_transferCashToAnotherAccount();
						break;
				default:theUI_.showErrorInvalidCommand();
			}
			break;
		case 1:
			switch ( option)
			{
				case 1:	m1_produceBalance();
						break;
				case 2: m2_withdrawFromBankAccount();
 						break;
				case 3:	m3_depositToBankAccount();
						break;
				case 4:	m4_produceStatement();
						break;
				case 5: m5_showAllDepositTransactions();
						break;
				case 6: m6_showMiniStatement();
						break;
				case 7: m7_searchForTransactions();
						break;
				case 8: m8_clearTransactionsUpToDate();
						break;
				case 9: m9_transferCashToAnotherAccount();
						break;
				case 10: requestOverdraftLimit();
						break;
				default:theUI_.showErrorInvalidCommand();
			}
			break;
		case 2:
			switch ( option)
			{
				case 1:	m1_produceBalance();
						break;
				case 2: m2_withdrawFromBankAccount();
 						break;
				case 3:	m3_depositToBankAccount();
						break;
				case 4:	m4_produceStatement();
						break;
				case 5: m5_showAllDepositTransactions();
						break;
				case 6: m6_showMiniStatement();
						break;
				case 7: m7_searchForTransactions();
						break;
				case 8: m8_clearTransactionsUpToDate();
						break;
				case 9: m9_transferCashToAnotherAccount();
						break;
				case 10: requestMinimumBalance();
						break;
				default:theUI_.showErrorInvalidCommand();
			}
			break;
		case 3:
			switch ( option)
			{
				case 1:	m1_produceBalance();
						break;
				case 2: m2_withdrawFromBankAccount();
 						break;
				case 3:	m3_depositToBankAccount();
						break;
				case 4:	m4_produceStatement();
						break;
				case 5: m5_showAllDepositTransactions();
						break;
				case 6: m6_showMiniStatement();
						break;
				case 7: m7_searchForTransactions();
						break;
				case 8: m8_clearTransactionsUpToDate();
						break;
				case 9: m9_transferCashToAnotherAccount();
						break;
				case 10: requestMinimumBalance();
						break;
				case 11: requestDepositConstraints();
						break;
				default:theUI_.showErrorInvalidCommand();
			}
			break;
		case 4:
			switch ( option)
			{
				case 1:	m1_produceBalance();
						break;
				case 2: m2_withdrawFromBankAccount();
 						break;
				case 3:	m3_depositToBankAccount();
						break;
				case 4:	m4_produceStatement();
						break;
				case 5: m5_showAllDepositTransactions();
						break;
				case 6: m6_showMiniStatement();
						break;
				case 7: m7_searchForTransactions();
						break;
				case 8: m8_clearTransactionsUpToDate();
						break;
				case 9: m9_transferCashToAnotherAccount();
						break;
				case 10: requestMinimumBalance();
						break;
				case 11: requestIsaDetails();
						break;
				default:theUI_.showErrorInvalidCommand();
			}
			break;
	}
}
//------ menu options
//---option 1
void CashPoint::m1_produceBalance() const {
	double balance( p_theActiveAccount_->getBalance());
	theUI_.showProduceBalanceOnScreen( balance);
}
//---option 2
void CashPoint::m2_withdrawFromBankAccount() {
    double amountToWithdraw( theUI_.readInWithdrawalAmount());
    bool transactionAuthorised( p_theActiveAccount_->canWithdraw( amountToWithdraw));
    if ( transactionAuthorised)
    {   //transaction is accepted: money can be withdrawn from account
        p_theActiveAccount_->recordWithdrawal( amountToWithdraw);
    }   //else do nothing
    theUI_.showWithdrawalOnScreen( transactionAuthorised, amountToWithdraw);
}
//---option 3
void CashPoint::m3_depositToBankAccount() {
    double amountToDeposit( theUI_.readInDepositAmount());
	if(typeid(*p_theActiveAccount_) == typeid(ChildAccount))
	{
		p_ChildAccount_ = dynamic_cast<ChildAccount*>(p_theActiveAccount_);
		bool depAuth = p_ChildAccount_->canDeposit(amountToDeposit);
		if(depAuth)
			p_ChildAccount_->recordDeposit( amountToDeposit);
		theUI_.showDepositOnScreen( depAuth, amountToDeposit);
	}
	else if(typeid(*p_theActiveAccount_) == typeid(ISAAccount))
	{
		p_ISAAccount_ = dynamic_cast<ISAAccount*>(p_theActiveAccount_);
		bool depAuth = p_ISAAccount_->canDeposit(amountToDeposit);
		if(depAuth)
			p_ISAAccount_->recordDeposit(amountToDeposit);
		theUI_.showDepositOnScreen(depAuth, amountToDeposit);
	}
	else
	{
		p_theActiveAccount_->recordDeposit( amountToDeposit);
		theUI_.showDepositOnScreen( true, amountToDeposit);
	}
}
//---option 4
void CashPoint::m4_produceStatement() const {
	theUI_.showStatementOnScreen( p_theActiveAccount_->prepareFormattedStatement());
}

void CashPoint::m5_showAllDepositTransactions() const 
{
	bool noTransaction = p_theActiveAccount_->isEmptyTransactionList();
	string str = "";
	double total = 0.0;
	if(!noTransaction)
		p_theActiveAccount_->produceAllDepositTransactions(str, total);
	theUI_.showAllDepositsOnScreen(noTransaction, str, total);
}

void CashPoint::m6_showMiniStatement() const
{
	int	numOfTr = theUI_.getNumberOfTransactions();
	theUI_.showMiniStatementOnScreen(p_theActiveAccount_->prepareFormattedMiniStatement(numOfTr));
}

void CashPoint::m7_searchForTransactions() const
{
	bool noTransaction = p_theActiveAccount_->isEmptyTransactionList();
	if(noTransaction)
		theUI_.showNoTransactionsOnScreen();	
	else
		searchTransactions();
}

void CashPoint::m8_clearTransactionsUpToDate() const
{
	bool noTransaction = p_theActiveAccount_->isEmptyTransactionList();
	bool deletionConfirmed;
	Date d, cd;
	int numOfTr = 0;
	string str = "";
	if(!noTransaction)
	{
		cd = p_theActiveAccount_->getCreationDate();
		d = theUI_.readInValidDate(cd);
		p_theActiveAccount_->produceTransactionsUpToDate(d, str, numOfTr);
	}
	if(numOfTr > 0)
		theUI_.showTransactionsUpToDateOnScreen(noTransaction, d, numOfTr, str);
	else
		theUI_.showNoTransactionsUpToDateOnScreen(d);
	if(!noTransaction && str != "")
		deletionConfirmed = theUI_.readInConfirmDeletion();
	if(!noTransaction && str != "" && deletionConfirmed)
		p_theActiveAccount_->recordDeletionOfTransactionUpToDate(d);
	if(!noTransaction && str != "")
		theUI_.showDeletionOfTransactionUpToDateOnScreen(d, numOfTr, deletionConfirmed);
}

void CashPoint::m9_transferCashToAnotherAccount()
{
	string accNo = "";
	string sortNo = "";
	theUI_.showCardOnScreen(p_theCashCard_->toFormattedString());
	string bankAccFileName = theUI_.readInAccountToBeProcessed(accNo, sortNo);
	int validAccountCode = validateAccount(bankAccFileName);
	theUI_.showValidateAccountOnScreen(validAccountCode, accNo, sortNo);
	if(validAccountCode == 0)
	{
		p_theTransferAccount_ = activateBankAccount(bankAccFileName);
		attemptTransfer(p_theTransferAccount_);
		releaseBankAccount(p_theTransferAccount_, bankAccFileName);
	}
}

void CashPoint::requestOverdraftLimit()
{
	p_CurrentAccount_ = dynamic_cast<CurrentAccount*>(p_theActiveAccount_);
	double oD = p_CurrentAccount_->getOverdraftLimit();
	theUI_.showOverdraftLimitOnScreen(oD);
}

void CashPoint::requestMinimumBalance()
{
	if(typeid(*p_theActiveAccount_) == typeid(ChildAccount))
	{
		p_ChildAccount_ = dynamic_cast<ChildAccount*>(p_theActiveAccount_);
		double mB = p_ChildAccount_->getMinimumBalance();
		theUI_.showMinimumBalanceOnScreen(mB);
	}
	else if(typeid(*p_theActiveAccount_) == typeid(ISAAccount))
	{
		p_ISAAccount_ = dynamic_cast<ISAAccount*>(p_theActiveAccount_);
		double mB = p_ISAAccount_->getMinimumBalance();
		theUI_.showMinimumBalanceOnScreen(mB);;
	}
}

void CashPoint::requestDepositConstraints()
{
	p_ChildAccount_ = dynamic_cast<ChildAccount*>(p_theActiveAccount_);
	double minPI = p_ChildAccount_->getMinimumPaidIn();
	double maxPI = p_ChildAccount_->getMaximumPaidIn();
	theUI_.showDepositConstraintsOnScreen(minPI, maxPI);
}

void CashPoint::requestIsaDetails()
{
	p_ISAAccount_ = dynamic_cast<ISAAccount*>(p_theActiveAccount_);
	double maxYD = p_ISAAccount_->getMaximumYearlyDeposit();
	double currYD = p_ISAAccount_->getCurrentYearlyDeposit();
	Date eDP = p_ISAAccount_->getEndDepositPeriod();
	theUI_.showIsaDetailsOnScreen(maxYD, currYD, eDP);
}

//------private file functions

bool CashPoint::canOpenFile( const string& st) const {
//check if a file already exist
	ifstream inFile;
	inFile.open( st.c_str(), ios::in); 	//open file
	//if does not exist fail, otherwise open file but do nothing to it
	bool exist;
    if ( inFile.fail())
        exist = false;
    else
        exist = true;
    inFile.close();			//close file: optional here
    return exist;
}
bool CashPoint::linkedCard( string cashCardFileName) const {
//check that card is linked with account data
	ifstream inFile;
	inFile.open( cashCardFileName.c_str(), ios::in); 	//open file
 	bool linked(false);
	if ( ! inFile.fail()) //file should exist at this point 
	{	//check that it contain some info in addition to card number
		string temp;
		inFile >> temp; //read card number
		inFile >> temp;	//ready first account data or eof
		if (inFile.eof())
			linked = false;
		else
			linked = true;
		inFile.close();			//close file: optional here
	}
	return linked;
}

void CashPoint::activateCashCard( const string& aCCFileName) {
//dynamically create a cash card to store data from file
    //effectively create the cash card instance with the data
	p_theCashCard_ = new CashCard;
    p_theCashCard_->readInCardFromFile( aCCFileName);
}

void CashPoint::releaseCashCard() {
//release the memory allocated to the dynamic instance of a CashCard
	delete p_theCashCard_;
	p_theCashCard_ = nullptr;
}

int CashPoint::checkAccountType( const string& aBAFileName) const {
    //(simply) identify type/class of account from the account number
    //start with 0 for bank account, 1 for current account, 2 for saving account, etc.
	return( atoi( aBAFileName.substr( 13, 1).c_str()));
}

BankAccount* CashPoint::activateBankAccount(  const string& aBAFileName) {
	//check the type of the account (already checked for validity)
	int accType( checkAccountType( aBAFileName));
    //effectively create the active bank account instance of the appropriate class
	//& store the appropriate data read from the file
	CurrentAccount* p_CA( nullptr);
	ChildAccount* p_ChA( nullptr);
	ISAAccount* p_IA( nullptr);

	switch( accType)
    {
		case CURRENTACCOUNT_TYPE:
			cout << "\n-------CURRENT-------\n";
			p_CA = new CurrentAccount;
			p_CA->readInBankAccountFromFile( aBAFileName);
			return p_CA;
			break;
		case CHILDACCOUNT_TYPE:
			cout << "\n-------CHILD-------\n";
			p_ChA = new ChildAccount;
			p_ChA->readInBankAccountFromFile( aBAFileName);
			return p_ChA;
			break;
		case ISAACCOUNT_TYPE:
			cout << "\n-------ISA-------\n";
			p_IA = new ISAAccount;
			p_IA->readInBankAccountFromFile( aBAFileName);
			return p_IA;
			break;
    }
	//use dynamic memory allocation: the bank account created will have to be released in releaseBankAccount
}

BankAccount* CashPoint::releaseBankAccount( BankAccount* p_BA, string aBAFileName) {
//store (possibly updated) data back in file
    p_BA->storeBankAccountInFile( aBAFileName);
	//effectively destroy the bank account instance
	delete p_BA;
	return nullptr;
}

void CashPoint::searchTransactions() const
{
	double amount;
	string title;
	string date;
	theUI_.showSearchMenu();
	int opt = theUI_.readInSearchCommand();
	switch(opt)
	{
	case 1:
		amount = theUI_.readInSearchAmount<double>();
		theUI_.showMatchingTransactionsOnScreen(p_theActiveAccount_->m7a_showTransactionsForAmount(amount));
		break;
	case 2: 
		title = theUI_.readInSearchAmount<string>();
		theUI_.showMatchingTransactionsOnScreen(p_theActiveAccount_->m7a_showTransactionsForAmount(title));
		break;
	case 3: 
		Date date = theUI_.readInSearchAmount<Date>();
		theUI_.showMatchingTransactionsOnScreen(p_theActiveAccount_->m7a_showTransactionsForAmount(date));
		break;
	}
}
