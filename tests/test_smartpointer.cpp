/**
 * @file
 *
 * @brief Runs the SmartPointer template class through various tests.
 *
 * @author Nate Lillich
 */

#include <cpps/cpps.h>

#include <iostream>

using namespace cpps;
using namespace std;

void spTest_one( void );

int main( void )
{
    spTest_one();
    return 0;
}

void spTest_one( void )
{
    SmartPointer<int> smint( 0 );

    cout << "Basic SmartPointer test: ";

    if( smint.getReferenceCount() != 1 )
        cout << "Error 1: Wrong reference count. Expected 1, found "
             << smint.getReferenceCount() << endl;
    else
    {
        SmartPointer<int> smint2 = smint;
        {
            SmartPointer<int> smint3 = smint2;
            if( smint.getReferenceCount() != 3 )
                cout << "Error 2: Wrong reference count. Expected 3, found "
                     << smint.getReferenceCount() << endl;

            ++(*smint3);
            ++(*smint2);
            if( *smint != *smint2 || *smint2 != *smint3 || *smint3 != 2 )
                cout << "Error 3: Wrong value. Expected 2, found "
                     << *smint << ", " << *smint2 << ", " << *smint3 << endl;
        }
        if( smint.getReferenceCount() != 2 )
            cout << "Error 4: Wrong reference count. Expected 2, found "
                 << smint.getReferenceCount() << endl;
        else
        {
            smint2 = SmartPointer<int>(5);
            if( *smint != 2 )
                cout << "Error 5: Wrong value. Expected 2, found "
                     << *smint << endl;
            else if( *smint2 != 5 )
                cout << "Error 6: Wrong value. Expected 5, found "
                     << *smint2 << endl;
            else if( smint.getReferenceCount() != 1 )
                cout << "Error 7: Wrong reference count. Expceted 1, found "
                     << smint.getReferenceCount() << endl;
            else if( smint2.getReferenceCount() != 1 )
                cout << "Error 8: Wrong reference count. Expected 1, found "
                     << smint2.getReferenceCount() << endl;
            else
            {
                cout << "Pass!" << endl;
            }
        }
    }
}

