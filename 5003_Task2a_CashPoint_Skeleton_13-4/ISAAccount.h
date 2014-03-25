#ifndef ISSAccountH
#define ISSAccountH

#include "SavingsAccount.h"

using namespace std;

class ISAAccount: public SavingsAccount
{
public:
	double getMaximumYearlyDeposit() const;
	double getCurrentYearlyDeposit() const;
	Date getEndDepositPeriod() const;
private:
	double maximumYearlyDeposit;
	double currentYearlyDeposit;
	Date endDepositPeriod;
	void updateCurrentYearlyDeposit(const double& a);
};

#endif