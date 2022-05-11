/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 05.06.2021
 */

#include "../src/CItem.h"
#include <memory>
#include <iostream>
#include <cassert>

using namespace std;

int main (){

    CItem pickaxe ("Pickaxe");
    CItem sword ( "Sword");

    assert (pickaxe.Type() == "Pickaxe");
    assert (sword.Type() == "Sword");
    assert (pickaxe.Damage() == 5);
    assert (sword.Damage() == 5);
    pickaxe.LevelUP().LevelUP();
    sword.LevelUP();
    assert ( pickaxe.Damage() == 15);
    assert ( sword.Damage() == 10);

    CItem newItem = pickaxe;

    assert ( newItem.Type() == "Pickaxe");
    assert ( newItem.Damage() == 15);

    CItem newItem2 (sword);

    assert ( newItem2.Type() == "Sword");
    assert ( newItem2.Damage() == 10);

    cout << "Item test is ok" << endl;

    return 0;
}