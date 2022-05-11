/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 05.06.2021
 */

#include "../src/CMap.h"
#include <memory>
#include <cassert>
#include <iostream>

using namespace std;

int main (){

    CMap map1 (10, 10);

    try {
        map1.GetField(CCoord (1, 1));
    }
    catch ( runtime_error & err ){
        assert ( err.what() == "Map is not initialized"s );
    }

    assert ( map1.SetField ( CCoord (2, 2), '#', 1 ));
    assert ( map1.SetField ( CCoord (4, 4), 'A', 1 ));
    assert ( !map1.SetField ( CCoord (15, 15), 'A', 1));
    assert ( !map1.SetField ( CCoord (10, 10), 'A', 1));
    assert ( !map1.SetField ( CCoord (1, 1), 'B', 200 ));
    assert ( !map1.SetField ( CCoord (2, 2), 'Q', 500 ));
    assert ( map1.SetField ( CCoord (9, 9), 'X', 200));

    try {
        map1.GetField(CCoord (8, 8));
    }
    catch ( runtime_error & err ){
        assert ( err.what() == "Map is not initialized"s );
    }

    assert ( map1.SetField ( CCoord (3,3), 'A', 1 ));
    assert ( map1.GetField ( CCoord (3, 3) ).DrawChar() == 'A' );
    assert ( map1.GetField ( CCoord (9, 9) ).DrawChar() == 'X' );

    assert ( map1.SetField ( CCoord (7, 5), 'X', 50) );
    assert ( map1.GetField ( CCoord (7,5)).DrawChar() == 'x');

    CFieldClay * test = dynamic_cast <CFieldClay*> ( map1.GetField(CCoord (7,5)).Clone().get());

    assert ( test != nullptr );

    try {
        map1.GetField(CCoord (6, 8));
    }
    catch ( runtime_error & err ){
        assert ( err.what() == "Map is not initialized"s );
    }

    assert ( map1.SetField(CCoord (2,9), 'L', 1));
    assert ( map1.GetField(CCoord (2,9)).DrawChar() == 'L');

    CFieldLava * test2 = dynamic_cast <CFieldLava*> ( map1.GetField(CCoord (2,9)).Clone().get());

    assert ( test2 != nullptr );


    try {
        map1.GetField(CCoord (3, 8));
    }
    catch ( runtime_error & err ){
        assert ( err.what() == "Map is not initialized"s );
    }

    CMap map2 (map1);

    assert ( map2.GetField( CCoord (2,9)).DrawChar() == 'L' );
    assert ( !map2.isInside( CCoord (10, 10)) );

    assert ( map2.SetField( CCoord (5,5), 'C', 500));
    assert ( map2.GetField(CCoord (5,5)).DrawChar() == 'C');

    assert ( map2.SetField( CCoord (4,9), 'C', 50));
    assert ( map2.GetField( CCoord (4,9)).DrawChar() == 'c');

    CFieldRock * test3 = dynamic_cast <CFieldRock*> ( map2.GetField(CCoord (4,9)).Clone().get());

    assert (test3 != nullptr);

    CMap map3 = map2;

    assert ( map3.GetField(CCoord (5,5)).DrawChar() == 'C');
    assert ( map3.GetField( CCoord (4,9)).DrawChar() == 'c');

    try {
        map3.GetField(CCoord (0, 0));
    }
    catch ( runtime_error & err ){
        assert ( err.what() == "Map is not initialized"s );
    }

    assert ( !map3.isInside( CCoord ( -1, -1 )));
    assert ( !map3.isInside( CCoord (10, 10)));
    assert ( map3.isInside( CCoord (9,9)));
    assert ( map3.SetField( CCoord (0,0), 'A', 1));
    assert ( map3.GetField( CCoord (0,0)).DrawChar() == 'A');

    CFieldAir * test4 = dynamic_cast <CFieldAir*> ( map3.GetField(CCoord (0,0)).Clone().get());

    assert ( test4 != nullptr );

    CMap map4 = CMap (map3);

    assert ( map4.GetField(CCoord (0,0)).DrawChar() == 'A');
    assert ( !map4.isInside(CCoord (11, 11)));
    assert ( ! map4.SetField (CCoord (7,1), '.', 5));
    assert ( map4.SetField( CCoord (7,1), '#', 1));
    assert ( map4.GetField( CCoord (7,1)).DrawChar() == '#');

    CFieldBorder * test5 = dynamic_cast <CFieldBorder*> ( map4.GetField(CCoord (7,1)).Clone().get());

    assert ( test5 != nullptr );

    assert ( !map4.GetField( CCoord (7,1)).canWalkThrough());
    assert ( map3.GetField( CCoord (0,0)).canWalkThrough());

    cout << "Map test is ok" << endl;

    return 0;
}