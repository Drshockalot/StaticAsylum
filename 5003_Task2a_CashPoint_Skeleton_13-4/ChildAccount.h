#ifndef ChildAccountH
#define ChildAccountH

#include "SavingsAccount.h"

using namespace std;

class ChildAccount: public SavingsAccount
{
public:
	double getMinimumPaidIn() const;
	double getMaximumPaidIn() const;
private:
	double minimumPaidIn;
	double maximumPaidIn;
};

#endif