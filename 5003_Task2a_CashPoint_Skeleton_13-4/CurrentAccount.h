////////////////////////////////////////////
//				GROUP UT1				  //
//	   <(''<) Chad Simpson (>'')>         //
//     Q(''O)  Luke Ward   Q(''O)         //
//	  <(._.<)  Shaun Webb  (>._.)>        //
////////////////////////////////////////////

#ifndef CurrentAccountH
#define CurrentAccountH

#include "BankAccount.h"

using namespace std;

class CurrentAccount: public BankAccount
{
public:
	CurrentAccount();
	virtual ~CurrentAccount();
	double getOverdraftLimit() const;

	virtual ostream& putDataInStream( ostream& os) const;
	virtual istream& getDataFromStream( istream& is);
	virtual const string prepareFormattedStatement() const;
	virtual const string prepareFormattedMiniStatement(int numOfTr) const;

	virtual double borrowable() const;
	virtual bool canWithdraw( double amount) const;
	virtual void recordDeposit( double amount);
	virtual bool canTransferOut(double amount) const;
	virtual bool canTransferIn(double amount) const;
    virtual void recordWithdrawal( double amount);
	void recordTransferOut(const double& amount, const string& tAN, const string& tSC);
	void recordTransferIn(const double& amount, const string& aAN, const string& aSC);
private:
	double overdraftLimit;
	virtual const string prepareFormattedAccountDetails() const;
	virtual const string prepareFormattedMiniAccountDetails(int numOfTr) const;
};

#endif