// @author: Selan
//
#include <iostream>
#include <functional>
#include <tuple>
#include <cassert>

#include "../include/hashtbl.h"
#include "account.h"

using namespace ac;

//=== CLIENT CODE

int main() {
    Account acct("Alex Bastos", 1, 1668, 54321, 1500.f);
    Account myAccounts[] =
    {
        {"Alex Bastos", 1, 1668, 54321, 1500.f},
        {"Aline Souza", 1, 1668, 45794, 530.f},
        {"Cristiano Ronaldo", 13, 557, 87629, 150000.f},
        {"Jose Lima", 18, 331, 1231, 850.f},
        {"Saulo Cunha", 116, 666, 1, 5490.f},
        {"Lima Junior", 12, 123, 5671, 150.f},
        {"Carlito Pardo", 28, 506, 9816, 50.f},
        {"Januario Medeiros", 17, 324, 7777, 4850.f}
    };
    std::cout << ">>> Lista de Contas: " << std::endl;	

    for( auto & e : myAccounts )
        std::cout << e << std::endl;
    std::cout << std::endl;

    // Cria uma tabela de dispersao com capacidade p 23 elementos
    HashTbl< Account::AcctKey, Account, KeyHash, KeyEqual > contas( 4 );

    // Inserindo as contas na tabela hash.
    for( auto & e : myAccounts )
    {
        contas.insert( e.getKey(), e );
        std::cout << ">>> Inserindo \"" << e.m_name << "\"\n";
        std::cout << ">>> Tabela Hash de Contas depois da insercao: \n" << contas << std::endl;
        // Unit test for insertion
        Account conta_teste;
        contas.retrieve( e.getKey(), conta_teste );
        assert( conta_teste == e );
    }

    std::cout << "\n\n>>> ESTADO FINAL da Tabela Hash de Contas: \n" << contas << std::endl;


    // Em um segundo momento...
    {
        // Testando retrieve.
        Account conta1;

        std::cout << "\n>>> Recuperando dados de \"" << myAccounts[2].m_name << "\":\n";
        contas.retrieve( myAccounts[2].getKey(), conta1 );
        std::cout << conta1 << std::endl;
        assert( conta1 == myAccounts[2] );
    }
    {
        // Testando remove
        Account conta1;

        std::cout << "\n>>> Removendo \"" << myAccounts[2].m_name << "\":\n";
        contas.erase( myAccounts[2].getKey() );
        std::cout << "\n\n>>> Tabela Hash apos remover: \n" << contas << std::endl;
        assert( contas.retrieve( myAccounts[2].getKey(), conta1 ) == false );
    }
    {
        // Testando insert.
        std::cout << "\n>>> Inserindo \"" << myAccounts[2].m_name << "\":\n";
        contas.insert( myAccounts[2].getKey(), myAccounts[2] );
        std::cout << "\n\n>>> Tabela Hash apos insercao: \n" << contas << std::endl;
    }
    {
        // Testando capacidade de alteração do insert.
        myAccounts[2].m_balance = 40000000.f;
        std::cout << "\n>>> Alterando \"" << myAccounts[2].m_name << "\":\n";
        contas.insert( myAccounts[2].getKey(), myAccounts[2] );
        std::cout << "\n\n>>> Tabela Hash apos insercao: \n" << contas << std::endl;

        Account conta1;
        contas.retrieve( myAccounts[2].getKey(), conta1 );
        assert( conta1 == myAccounts[2] );
        assert( conta1.m_balance == 40000000.f );
    }
    {
        // Testando clear, empty.
        assert( contas.empty() == false );
        std::cout << "\n>>> Apagando a tabela: \n";
        contas.clear();
        std::cout << "\n\n>>> Tabela Hash apos limpar: \n" << contas << std::endl;
        assert( contas.empty() == true );
    }
    {
        // Testando rehash.
        // Cria uma tabela de dispersao com capacidade p 23 elementos
        HashTbl< Account::AcctKey, Account, KeyHash, KeyEqual > contas( 2 );

        // Inserindo as contas na tabela hash.
        for( auto & e : myAccounts )
        {
            std::cout << ">>> Size = " << contas.size() << std::endl;
            contas.insert( e.getKey(), e );
            std::cout << ">>> Inserindo \"" << e.m_name << "\"\n";
            std::cout << ">>> Tabela Hash de Contas depois da insercao: \n" << contas << std::endl;
            // Unit test for insertion
            Account conta_teste;
            contas.retrieve( e.getKey(), conta_teste );
            assert( conta_teste == e );
        }
    }

    return EXIT_SUCCESS;
}

