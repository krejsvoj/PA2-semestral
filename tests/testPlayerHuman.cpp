/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 05.06.2021
 */


#include "../src/CPlayerHuman.h"

#include <memory>
#include <cassert>
#include <iostream>

using namespace std;

int main (){

    shared_ptr <CInterface> interface = make_shared <CInterface> (cin, cout);
    CStats stats;
    stats.m_ItemName = "Pickaxe";
    stats.m_SecondItemName = "Sword";
    stats.m_HP = 100;
    CPlayerHuman human1 ( CCoord (1,1), stats, 0, interface, EDirection::NONE, EDirection::NONE);

    try {
        human1.ReceiveHit(1000);
    }
    catch ( YouDiedException & err ){
        cout << "Died test is ok" << endl;
    }

    assert ( !human1.isAlive() );
    assert ( human1.Print() == 'v');

    unique_ptr <CPlayer> human2 = human1.Clone();

    assert ( !human2->isAlive() );
    assert ( human2->Print() == 'v');

    CPlayerHuman * test = dynamic_cast <CPlayerHuman *> (human2.get());

    assert ( test != nullptr );

    assert ( human2->Attack() == 25 );
    assert ( human2->Attack() == 5 );

    CPlayerHuman human3 ( human1 );

    assert ( human3.Attack() == 25 );
    assert ( human3.Print() == 'v');

    CPlayerHuman human4 = human1;

    assert ( human4.Attack() == 25 );
    assert ( human4.Attack() == 5 );
    assert ( human4.Print() == 'v');

    assert ( human4.coordToMove() == human4.GetCoord() );
    assert ( human4.getLastDirection() == EDirection::NONE);

    CPlayerHuman human5 ( CCoord (5,5), stats, 5, interface, EDirection::LEFT, EDirection::LEFT);

    assert ( human5.GetTimeInAir() == 5 );
    human5.TimeInAir ( true );
    assert ( human5.GetTimeInAir() == 0 );
    CCoord human5coord = human5.GetCoord();
    assert ( human5.coordToMove() == human5coord.getLeft());
    assert ( human5.isAlive() );
    assert ( human5.getLastDirection() == EDirection::LEFT );
    human5.resetDirection();
    unique_ptr <CPlayer > human6 = human5.Clone ();
    human6->Move(human6->coordToMove());
    assert ( human6->getLastDirection() == EDirection::NONE);

    cout << "PlayerHuman test is ok" << endl;

    return 0;
}