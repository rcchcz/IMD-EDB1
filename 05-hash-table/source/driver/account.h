/*!
 * @author: Selan
 * @date November, 28th 2018.
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <functional>
#include <tuple>

/// Represents a bank account.
struct Account {
	std::string m_name; //!< client name.
	int m_bank_code;    //!< Bank id.
	int m_branch_code;  //!< Branch id.
	int m_number;       //!< Account number.
	float m_balance;    //!< Account balance.

    // Nickname for the account key.
    using AcctKey = std::tuple< std::string, int, int, int >;

    /// Basic constructor.
    Account( std::string = "<empty>", int = 0, int = 0, int = 0, float = 0.f );
		     
	/// Returns the account key.
	AcctKey getKey(void) const;
	
	/// Stream extractor of the account information. 
	friend std::ostream &operator<< ( std::ostream & _os, const Account & _acct );
};

/// Compare two accounts
bool operator==( const Account & a, const Account & b );

/// Functor that generates a hash number for a given account.
struct KeyHash {
    std::size_t operator()( const Account::AcctKey & ) const;
};


// Functor that test two keys for equality.
struct KeyEqual {
	bool operator()( const Account::AcctKey & , const Account::AcctKey & ) const;
};

#endif
