#ifndef ChildAccountH
#define ChildAccountH

#include "SavingsAccount.h"

using namespace std;

class ChildAccount: public SavingsAccount
{
public:
	ChildAccount();
	virtual ~ChildAccount();
	double getMinimumPaidIn() const;
	double getMaximumPaidIn() const;
	virtual bool canDeposit(const double& amount) const;

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
	double minimumPaidIn;
	double maximumPaidIn;
};

ostream& operator<<( ostream&, const ChildAccount&);	//output operator
istream& operator>>( istream&, ChildAccount&);	    //input operator

#endif