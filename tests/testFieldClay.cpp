/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 04.06.2021
 */

#include "../src/CFieldClay.h"
#include <cassert>
#include <iostream>
#include <memory>

using namespace std;

int main (){

    CFieldClay G (200);
    CItem item1 ("Pickaxe");
    item1.LevelUP().LevelUP().LevelUP().LevelUP().LevelUP().LevelUP();

    assert (!G.isDestroyed());
    assert (!G.canWalkThrough());
    assert (G.DrawChar() == 'X');

    G.receiveHit(item1).receiveHit(item1).receiveHit(item1);
    assert (G.isDestroyed());
    assert (G.DrawChar() == 'x');

    item1.LevelUP().LevelUP().LevelUP().LevelUP().LevelUP().LevelUP();
    G.receiveHit(item1);
    assert (G.isDestroyed());
    assert (G.DealsDamage() == 0);

    unique_ptr <CField> H = G.Clone();

    CFieldClay * test = dynamic_cast <CFieldClay*> (H.get());

    assert ( H->isDestroyed() );
    assert ( !H->canWalkThrough() );
    assert ( test != nullptr );

    cout << "CFieldClay test is ok." << endl;

    return 0;
}