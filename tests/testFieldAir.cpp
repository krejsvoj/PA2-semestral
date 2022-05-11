/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 04.06.2021
 */

#include "../src/CFieldAir.h"
#include <memory>
#include <cassert>
#include <iostream>

using namespace std;

int main (){

    CFieldAir C (1);
    CItem item1 ("Pickaxe");
    item1.LevelUP().LevelUP().LevelUP().LevelUP().LevelUP().LevelUP();

    C.receiveHit(item1);
    assert (!C.isDestroyed());
    assert (C.canWalkThrough());
    item1.LevelUP().LevelUP().LevelUP().LevelUP().LevelUP().LevelUP();
    C.receiveHit(item1);
    assert (!C.isDestroyed());
    assert (C.DrawChar() == 'A');
    assert (C.DealsDamage() == 0);

    unique_ptr <CField> D = C.Clone();

    assert ( !D->isDestroyed());
    assert ( D->DrawChar() == 'A');
    assert ( D->canWalkThrough() );
    assert ( D->DealsDamage() == 0);
    CFieldAir * test = dynamic_cast <CFieldAir *> (D.get());

    assert (test != nullptr);

    cout << "CFieldAir test is ok" << endl;

    return 0;
}