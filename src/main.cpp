#include <iostream>
#include <memory>

#include "CApplication.h"

using namespace std;

int main() {


    CApplication application (make_shared <CInterface> (cin, cout));

    try {
        application.Run();
    }
    catch (std::ios_base::failure & failure){
        if (cin.eof())
            return 0;
        else if (cin.fail() || cout.fail()){
            cerr << failure.what() << endl;
            return 1;
        }
        else if (cout.eof())
            cerr << failure.what() << endl;
    }
    catch (...) {
        cout << UNEXPECTED_ERROR << endl;
        return 32;
    }

    return 0;
}