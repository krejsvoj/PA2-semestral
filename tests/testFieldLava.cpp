/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 04.06.2021
 */

#include "../src/CFieldLava.h"
#include <memory>
#include <cassert>
#include <iostream>


using namespace std;

int main(){

    CFieldLava E (1);
    CItem item1 ("Pickaxe");
    item1.LevelUP().LevelUP().LevelUP().LevelUP().LevelUP().LevelUP();

    E.receiveHit(item1);
    assert (!E.isDestroyed());
    assert (E.canWalkThrough());
    item1.LevelUP().LevelUP().LevelUP().LevelUP().LevelUP().LevelUP();
    E.receiveHit(item1);
    assert (!E.isDestroyed());
    assert (E.DrawChar() == 'L');
    assert (E.DealsDamage() == 1000);

    unique_ptr <CField> F = E.Clone();

    assert ( F->DealsDamage() == 1000 );
    assert ( F->DrawChar() == 'L');
    assert ( F->canWalkThrough() );
    assert ( ! F->isDestroyed() );
    CFieldLava * test = dynamic_cast <CFieldLava *> (F.get());

    assert (test != nullptr);

    cout << "CFieldLava test is ok" << endl;

    return 0;
}