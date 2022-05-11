/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 04.06.2021
 */

#include "../src/CCoord.h"
#include <cassert>
#include <iostream>

using namespace std;

int main (){

    CCoord A (1, 1);

    assert (A.m_X == 1 && A.m_Y == 1);
    A.getUp();
    assert (A.m_X == 0 && A.m_Y == 1);
    A.getDown().getDown();
    assert (A.m_X == 2 && A.m_Y == 1);
    A.getLeft().getLeft();
    assert (A.m_X == 2 && A.m_Y == size_t (-1));

    CCoord B (25, 25);
    B.getRight().getDown();
    assert (B.m_X == 26 && B.m_Y == 26);
    B.getDown().getDown();
    assert (B.m_X == 28 && B.m_Y == 26);

    CCoord C (30, 30) ;
    CCoord D (30, 30) ;

    assert (C == D);
    C.getDown().getLeft().getRight().getUp();
    D.getDown().getLeft().getRight().getUp();
    assert (C == D);

    CCoord E (20, 20);
    E.getUp().getUp();
    assert (E.m_X == 18 && E.m_Y == 20);
    E = D;
    assert (E == D);
    E.getDown();
    assert ( ! (E == D));
    E.getUp();
    assert (E == D);
    E.getLeft();
    assert (! (E == D));

    cout << "Coord test is ok" << endl;

    return 0;
}
