////////////////////////////////////////////
//				GROUP UT1				  //
//	   <(''<) Chad Simpson (>'')>         //
//     Q(''O)  Luke Ward   Q(''O)         //
//	  <(._.<)  Shaun Webb  (>._.)>        //
////////////////////////////////////////////

#ifndef CurrentAccountH
#define CurrentAccountH

#include "BankAccount.h"

using namespace std;

class CurrentAccount: public BankAccount
{
public:
	CurrentAccount();
	~CurrentAccount();
	double getOverdraftLimit() const;

	ostream& putDataInStream( ostream& os) const;
	istream& getDataFromStream( istream& is);
	const string prepareFormattedStatement() const;
	const string prepareFormattedAccountDetails() const;

	double borrowable() const;
	bool canWithdraw( double amount) const;
	void recordDeposit( double amount);
	bool canTransferOut(double amount, string& probStr) const;
	bool canTransferIn(double amount, string& probStr) const;
    void recordWithdrawal( double amount);
	void recordTransferOut(const double& amount, const string& tAN, const string& tSC);
	void recordTransferIn(const double& amount, const string& aAN, const string& aSC);
private:
	double overdraftLimit;
};

#endif