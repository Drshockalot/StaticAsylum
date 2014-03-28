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

	ostream& putDataInStream( ostream& os) const;
	istream& getDataFromStream( istream& is);
	const string prepareFormattedStatement() const;
	const string prepareFormattedMiniStatement(int numOfTr) const;

	void recordTransferOut(const double& amount, const string& tAN, const string& tSC);
	void recordTransferIn(const double& amount, const string& aAN, const string& aSC);
	bool canDeposit(const double& amount) const;
	double borrowable() const;
	bool canWithdraw( double amount) const;
	void recordDeposit( double amount);
	bool canTransferOut(double amount) const;
	bool canTransferIn(double amount) const;
    void recordWithdrawal( double amount);
private:
	double maximumYearlyDeposit;
	double currentYearlyDeposit;
	Date endDepositPeriod;
	void updateCurrentYearlyDeposit(const double& a);
	const string prepareFormattedAccountDetails() const;
	const string prepareFormattedMiniAccountDetails(int numOfTr) const;
};

#endif