/*!
 * @file: account.cpp
 */
#include "account.h"

/// Basic constructor.
Account::Account( std::string n, int bnc, int brc, int nmr, float bal )
    : m_name( n )
    , m_bank_code( bnc )
    , m_branch_code( brc )
    , m_number( nmr )
      , m_balance( bal )
{ /* Empty */ }

/// Returns the account key.
Account::AcctKey Account::getKey(void) const {
    return std::make_tuple( m_name, m_bank_code, m_branch_code, m_number );
}

std::ostream& operator<< ( std::ostream & os_, const Account::AcctKey & ak_ ) {
    return os_ << "K{"
               << std::get<0>( ak_ ) << ","
               << std::get<1>( ak_ ) << ","
               << std::get<2>( ak_ ) << ","
               << std::get<3>( ak_ ) << "}";
}

/// Stream extractor of the account information. 
std::ostream& operator<< ( std::ostream & os_, const Account & acct_ ) {
    return os_ << "[ Client: <" << acct_.m_name <<
        "> Bank: <"   << acct_.m_bank_code <<
        "> Branch: <" << acct_.m_branch_code <<
        "> Number: <" << acct_.m_number <<
        "> Balance: <" << acct_.m_balance << "> ]";
}

/// Compare two accounts
bool operator==( const Account & a, const Account & b ) {
    return ( a.m_name == b.m_name and
            a.m_bank_code   == b.m_bank_code and
            a.m_branch_code == b.m_branch_code and
            a.m_number     == b.m_number and
            a.m_balance    == b.m_balance ) ;
}

std::size_t KeyHash::operator()( const Account::AcctKey & _k ) const {
    return std::hash< std::string >()(std::get<0>( _k )) xor
        std::hash< int >()(std::get<1>( _k )) xor
        std::hash< int >()(std::get<2>( _k )) xor
        std::hash< int >()(std::get<3>( _k ));
}


// Functor that test two keys for equality.
bool KeyEqual::operator()( const Account::AcctKey & _lhs, const Account::AcctKey & _rhs ) const {
    return std::get<0>(_lhs) == std::get<0>(_rhs) and
        std::get<1>(_lhs) == std::get<1>(_rhs) and
        std::get<2>(_lhs) == std::get<2>(_rhs) and
        std::get<3>(_lhs) == std::get<3>(_rhs);
}
