#ifndef SavingsAccountH
#define SavingsAccountH

#include "BankAccount.h"

using namespace std;

class SavingsAccount: public BankAccount
{
public:
	double getMinimumBalance() const;
private:
	double minimumBalance;
};

#endif