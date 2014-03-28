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
	virtual bool canDeposit(const double& amount) const = 0;
private:
	double minimumBalance;
};

#endif