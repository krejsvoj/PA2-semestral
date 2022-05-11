/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 01.06.2021
 */

#include "CBuffer.h"

CBuffer::CBuffer(size_t height, size_t width)
        : m_MapHeight (height),
        m_MapWidth (width)
{
    m_Map.resize(m_MapHeight);
    for (size_t i = 0; i < m_MapHeight; ++i)
        m_Map[i].resize(m_MapWidth, ' ');
}

void CBuffer::DrawMapInBuffer(CMap &map) {

    for (size_t i = 0; i < m_MapHeight; ++i){
        for (size_t j = 0; j < m_MapWidth; ++j)
            m_Map[i][j] = map.GetField(CCoord (i, j)).DrawChar();
    }
}

CBuffer & CBuffer::PrintCharInMap (const CCoord & coord, char c){
    m_Map[coord.m_X][coord.m_Y] = c;
    return *this;
}
