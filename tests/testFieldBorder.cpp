/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 04.06.2021
 */

#include "../src/CFieldBorder.h"
#include <cassert>
#include <iostream>
#include <memory>

using namespace std;

int main (){

    CFieldBorder A (1);

    unique_ptr<CField> B = A.Clone();

    assert (A.DealsDamage() == 0);
    assert (! (A.DealsDamage() != 0));

    CItem item1 ("Pickaxe");
    item1.LevelUP().LevelUP().LevelUP().LevelUP().LevelUP().LevelUP();
    assert ( ! A.isDestroyed() );
    A.receiveHit(item1);
    item1.LevelUP().LevelUP().LevelUP().LevelUP().LevelUP().LevelUP();
    A.receiveHit(item1);

    assert ( ! A.isDestroyed() );
    assert ( A.DrawChar() == '#' );

    B->receiveHit(item1);

    assert (! B->isDestroyed());
    assert ( B->DrawChar() == '#');
    assert ( B->DealsDamage() == 0);

    assert ( !A.canWalkThrough());
    assert ( !B->canWalkThrough());

    CFieldBorder * test = dynamic_cast <CFieldBorder *> (B.get());

    assert ( test != nullptr );

    cout << "CFieldBorder test is ok." << endl;

    return 0;
}