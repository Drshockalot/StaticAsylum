#ifndef CurrentAccountH
#define CurrentAccountH

#include "BankAccount.h"

using namespace std;

class CurrentAccount: public BankAccount
{
public:
	double getOverdraftLimit() const;
private:
	double overdraftLimit;
};

#endif