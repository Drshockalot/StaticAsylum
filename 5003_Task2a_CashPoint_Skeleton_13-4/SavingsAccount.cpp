#include "SavingsAccount.h"

SavingsAccount::SavingsAccount()
	: minimumBalance(0.0)
{}

SavingsAccount::~SavingsAccount()
{}

double SavingsAccount::getMinimumBalance() const
{
	return minimumBalance;
}

void SavingsAccount::setMinimumBalance(const double& mB)
{
	minimumBalance = mB;
}