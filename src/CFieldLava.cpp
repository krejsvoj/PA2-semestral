/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 27.05.2021
 */

#include "CFieldLava.h"

using namespace std;

CFieldLava::CFieldLava(int HP)
        : CField (true, false, HP)
{
}

CField &CFieldLava::receiveHit(const CItem &item) {
    (void) item;    // item is not used for CFieldLava, because it has no meaning (Lava cannot be destroyed)
    return *this;
}

int CFieldLava::DealsDamage() const {
    return LAVA_DMG;
}

char CFieldLava::DrawChar() const {
    return 'L';
}

std::unique_ptr<CField> CFieldLava::Clone() const {
    return std::make_unique <CFieldLava> (*this);
}
