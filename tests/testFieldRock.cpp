/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 04.06.2021
 */

#include "../src/CFieldRock.h"
#include <memory>
#include <iostream>
#include <cassert>

using namespace std;

int main (){

    CFieldRock A (500);
    CItem item1 ("Pickaxe");
    item1.LevelUP().LevelUP().LevelUP().LevelUP().LevelUP().LevelUP();

    assert (!A.isDestroyed());
    assert (!A.canWalkThrough());
    assert (A.DrawChar() == 'C');
    A.receiveHit(item1);
    assert (!A.isDestroyed());
    assert (A.DrawChar() == 'c');

    item1.LevelUP().LevelUP().LevelUP().LevelUP().LevelUP().LevelUP();
    A.receiveHit(item1);
    assert (A.isDestroyed());
    assert (A.DealsDamage() == 0);

    unique_ptr <CField> B = A.Clone();

    CFieldRock * test = dynamic_cast <CFieldRock*> (B.get());

    assert ( B->isDestroyed() );
    assert ( !B->canWalkThrough() );
    assert ( B->DrawChar() == 'c');
    assert ( test != nullptr );

    cout << "CFieldRock test is ok." << endl;

    return 0;
}