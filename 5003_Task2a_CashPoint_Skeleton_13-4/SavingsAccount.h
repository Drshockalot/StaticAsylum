#ifndef SavingsAccountH
#define SavingsAccountH

#include "BankAccount.h"

using namespace std;

class SavingsAccount: public BankAccount
{
public:
	SavingsAccount();
	virtual ~SavingsAccount();
	double getMinimumBalance() const;
	void setMinimumBalance(const double& mB);

	virtual ostream& putDataInStream( ostream& os) const;
	virtual istream& getDataFromStream( istream& is);
	virtual const string prepareFormattedStatement() const;
	virtual const string prepareFormattedMiniStatement(int numOfTr) const;
	virtual const string prepareFormattedAccountDetails() const;
	virtual const string prepareFormattedMiniAccountDetails(int numOfTr) const;

	virtual double borrowable() const;
	virtual bool canWithdraw( double amount) const;
	virtual void recordDeposit( double amount);
	virtual bool canTransferOut(double amount) const;
	virtual bool canTransferIn(double amount) const;
    virtual void recordWithdrawal( double amount);
private:
	double minimumBalance;
};

ostream& operator<<( ostream&, const SavingsAccount&);	//output operator
istream& operator>>( istream&, SavingsAccount&);	    //input operator

#endif