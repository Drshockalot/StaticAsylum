//Pascale Vacher - March 14
//OOP Assignment Semester 2

#include "CashCard.h"

//---------------------------------------------------------------------------
//CashCard: class implementation
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//public member functions
//---------------------------------------------------------------------------

//____constructors & destructors

CashCard::CashCard()
    : cardNumber_( "null")
{}
CashCard::CashCard( const string& cardNum, const List<string>& accList)
    : cardNumber_( cardNum),
      accountsList_( accList)
{}

//____other public member functions

const string CashCard::getCardNumber() const {
    return cardNumber_;
}
const List<string> CashCard::getAccountsList() const {
    return accountsList_;
}
bool CashCard::onCard( const string& accFileName) const {
    //e.g., data\account_001_00-44.txt
	string accName = accFileName.substr( 13, 9);	//account identifier
	return ( accountsList_.member( accName)); //check if member of the card account list
}
void CashCard::readInCardFromFile( const string& accFileName) {
	ifstream fromFile;
	fromFile.open( accFileName.c_str(), ios::in); 	//open file in read mode
	if ( fromFile.fail())
		cout << "\nAN ERROR HAS OCCURED WHEN OPENING THE FILE.";
	else
        fromFile >> (*this);   //read all info from card file
//  fromFile.close();			//close file: optional here
}

const string CashCard::toFormattedString() const {
//return cash card as a (formatted) string
	ostringstream os_card;
	os_card << "\nCARD NUMBER:    " << cardNumber_ << endl;	//display card no
	os_card << "\nLIST OF ACCOUNTS ";						//display transactions
	if ( accountsList_.isEmpty())
		os_card << "IS EMPTY!!!";
	else
	{
	   	List<string> tempAccList( accountsList_); //make a copy of the list of accounts on card
		while ( ! ( tempAccList.isEmpty()))
   		{
      		os_card << "\n";
			string s = tempAccList.first();     //account details (e.g., "001_00-44")
			string s_accNum = s.substr( 0, 3);	//account number (e.g., "001")
			string s_srtCod = s.substr( 4, 5);	//sort code (e.g., "00-44")
			os_card << "  ACCOUNT NUMBER: " << s_accNum;
			os_card << "  SORT CODE: " << s_srtCod;
       		tempAccList.deleteFirst();
		}
    }
	return ( os_card.str());
}

ostream& CashCard::putDataInStream( ostream& os) const {
//put (formatted) CashCard details in stream
    os << cardNumber_ << "\n";	//store card number
    List<string> tempAccounts( accountsList_);
    while ( ! ( tempAccounts.isEmpty())) 	//while not empty
	{
		os << tempAccounts.first() << endl; 	//copy each account name & <Return> in file
	    tempAccounts.deleteFirst();	//delete account reference from history of transactions
	}
	return os;
}
istream& CashCard::getDataFromStream( istream& is) {
//get CashCard details from stream
    List<string> anAccountsList;
	is >> cardNumber_;	//read card number
	string anAccountName;
	is >> anAccountName;	//read first account name
    while ( is != 0) 	//while not end of file
    {
        accountsList_.addAtEnd( anAccountName);   //add account
		is >> anAccountName;	//read next account name
	}
	return is;
}
//---------------------------------------------------------------------------
//non-member operator functions
//---------------------------------------------------------------------------

ostream& operator<<( ostream& os, const CashCard& aCashCard) {
						//Card formatted output
    return ( aCashCard.putDataInStream( os));
}
istream& operator>>( istream& is, CashCard& aCashCard) {
						//read in CashCard details
	return ( aCashCard.getDataFromStream( is));
}
