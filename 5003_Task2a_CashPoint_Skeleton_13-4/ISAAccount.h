#ifndef ISSAccountH
#define ISSAccountH

#include "SavingsAccount.h"

using namespace std;

class ISAAccount: public SavingsAccount
{
public:
	ISAAccount();
	~ISAAccount();
	double getMaximumYearlyDeposit() const;
	double getCurrentYearlyDeposit() const;
	Date getEndDepositPeriod() const;

	virtual ostream& putDataInStream( ostream& os) const;
	virtual istream& getDataFromStream( istream& is);
	virtual const string prepareFormattedStatement() const;
	virtual const string prepareFormattedMiniStatement(int numOfTr) const;
	virtual const string prepareFormattedAccountDetails() const;
	virtual const string prepareFormattedMiniAccountDetails(int numOfTr) const;

	virtual bool canDeposit(const double& amount) const;
	virtual double borrowable() const;
	virtual bool canWithdraw( double amount) const;
	virtual void recordDeposit( double amount);
	virtual bool canTransferOut(double amount) const;
	virtual bool canTransferIn(double amount) const;
    virtual void recordWithdrawal( double amount);
private:
	double maximumYearlyDeposit;
	double currentYearlyDeposit;
	Date endDepositPeriod;
	void updateCurrentYearlyDeposit(const double& a);
};

#endif