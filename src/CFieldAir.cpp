/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 27.05.2021
 */

#include "CFieldAir.h"

using namespace std;

CFieldAir::CFieldAir(int HP)
        : CField (true, false, HP)
{
}

CField &CFieldAir::receiveHit(const CItem &item) {
    (void) item;    // item is not used for CFieldAir, because it has no meaning (Air cannot be destroyed)
    return * this;
}

int CFieldAir::DealsDamage() const {
    return AIR_DMG;
}

char CFieldAir::DrawChar() const {
    return 'A';
}

std::unique_ptr<CField> CFieldAir::Clone() const {
    return std::make_unique <CFieldAir> (*this);
}
