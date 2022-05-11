/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 05.06.2021
 */

#include "../src/CPlayerMonster.h"

#include <memory>
#include <cassert>
#include <iostream>

using namespace std;

int main (){

    CPlayerMonster monster1 (CCoord (1,1), 500, 0, EDirection::NONE,
                             EDirection::NONE, 20, 0);

    assert ( monster1.Attack() >= 20 && monster1.Attack() < 25);
    assert ( monster1.Print() == '{');
    assert ( monster1.isAlive() );

    monster1.ReceiveHit(1000);
    assert ( ! monster1.isAlive() );

    CPlayerMonster monster2 (CCoord (1,1), 500, 0, EDirection::LEFT,
                             EDirection::LEFT, 20, 10);

    assert ( monster2.GetCoord() == CCoord (1, 1));

    CCoord toMove = monster2.coordToMove();
    assert ( toMove == CCoord (1,1).getLeft() );
    assert ( monster2.Print() == '}');

    CPlayerMonster * test = dynamic_cast <CPlayerMonster *> (monster2.Clone().get());

    assert ( test != nullptr );

    CPlayerMonster monster3 (monster1);

    assert (!monster3.isAlive());

    CPlayerMonster monster4 (CCoord (1,1), 500, 0, EDirection::LEFT,
                             EDirection::LEFT, 20, 10);

    monster4.ReceiveHit(499);
    assert (monster4.isAlive());

    cout << "PlayerMonster test is ok" << endl;

    return 0;
}