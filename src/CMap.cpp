/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 27.05.2021
 */

#include "CMap.h"

using namespace std;

CMap::CMap(size_t height, size_t width)
        : m_Height (height),
          m_Width (width)
{
    m_Map.resize(m_Height);
    for (size_t i = 0; i < m_Height; ++i)
        m_Map[i].resize(m_Width);
}

CMap &CMap::operator=(CMap map) {
    std::swap (m_Height, map.m_Height);
    std::swap (m_Width, map.m_Width);
    std::swap (m_Map, map.m_Map);
    return * this;
}

CMap::CMap(const CMap &map) {
    m_Height = map.m_Height;
    m_Width = map.m_Width;
    m_Map.resize(m_Height);
    for (size_t i = 0; i < m_Height; ++i)
        m_Map[i].resize(m_Width);
    for (size_t i = 0; i < map.m_Height; ++i){
        for (size_t j = 0; j < map.m_Width; ++j){
            if ( map.m_Map[i][j] != nullptr)
                m_Map[i][j] = map.m_Map[i][j]->Clone();
        }
    }
}

bool CMap::canWalkTrough(const CCoord &coord) const {
    if (!isInside(coord))
        throw runtime_error ("Out of map range.");
    return m_Map [coord.m_X][coord.m_Y]->canWalkThrough();
}

CField &CMap::GetField(const CCoord &coord) const{
    if (!isInside(coord))
        throw runtime_error ("Out of map range.");
    if ( m_Map[coord.m_X][coord.m_Y] == nullptr )
        throw runtime_error ("Map is not initialized");
    return *m_Map[coord.m_X][coord.m_Y];
}

CMap &CMap::SetAir(const CCoord &coord) {
    if (!isInside(coord))
        throw runtime_error ("Out of map range.");
    m_Map[coord.m_X][coord.m_Y] = std::make_unique<CFieldAir>(1);
    return *this;
}

bool CMap::isBorder(size_t x, size_t y) const {
    return (x == 0 || x == m_Height - 1 || y == 0 || y == m_Width - 1 );
}

bool CMap::isInside(const CCoord &coord) const {
    return coord.m_X < m_Height && coord.m_Y < m_Width;
}

bool CMap::SetField(const CCoord &coord, char c, int HP) {
    std::unique_ptr<CField> newField = nullptr;

    switch (c){
        case '#': newField = std::make_unique<CFieldBorder>(HP);   break;
        case 'A': newField = std::make_unique<CFieldAir>(HP);      break;
        case 'X': newField = std::make_unique<CFieldClay>(HP);     break;
        case 'L': newField = std::make_unique<CFieldLava>(HP);     break;
        case 'C': newField = std::make_unique<CFieldRock>(HP);      break;
        default : return false;
    }
    if (!isInside(coord))
        return false;

    m_Map[coord.m_X][coord.m_Y] = std::move (newField);

    return true;
}

void CMap::SaveMap( ofstream & mapFile ) const {
    mapFile << MAP_INFO << endl;
    mapFile << m_Width << " " << m_Height << endl << endl;
    for (size_t i = 0; i < m_Height; ++i){
        for (size_t j = 0; j < m_Width; ++j){
            m_Map[i][j]->SaveField(mapFile, i, j);
        }
        mapFile << endl;
    }
    mapFile << END_MAP_INFO << endl;
}
