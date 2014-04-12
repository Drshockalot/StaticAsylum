////////////////////////////////////////////
//				GROUP UT1				  //
//	   <(''<) Chad Simpson (>'')>         //
//     Q(''O)  Luke Ward   Q(''O)         //
//	  <(._.<)  Shaun Webb  (>._.)>        //
////////////////////////////////////////////

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