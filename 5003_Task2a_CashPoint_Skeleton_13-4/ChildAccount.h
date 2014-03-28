#ifndef ChildAccountH
#define ChildAccountH

#include "SavingsAccount.h"

using namespace std;

class ChildAccount: public SavingsAccount
{
public:
	ChildAccount();
	~ChildAccount();
	double getMinimumPaidIn() const;
	double getMaximumPaidIn() const;
	bool canDeposit(const double& amount) const;

	ostream& putDataInStream( ostream& os) const;
	istream& getDataFromStream( istream& is);
	const string prepareFormattedStatement() const;
	const string prepareFormattedMiniStatement(int numOfTr) const;
	
	double borrowable() const;
	bool canWithdraw( double amount) const;
	void recordDeposit( double amount);
	bool canTransferOut(double amount) const;
	bool canTransferIn(double amount) const;
    void recordWithdrawal( double amount);
	void recordTransferIn(const double& amount, const string& aAN, const string& aSC);
	void recordTransferOut(const double& amount, const string& tAN, const string& tSC);
private:
	double minimumPaidIn;
	double maximumPaidIn;
	const string prepareFormattedAccountDetails() const;
	const string prepareFormattedMiniAccountDetails(int numOfTr) const;
};

#endif