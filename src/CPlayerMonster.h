/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 05.05.2021
 */

#pragma once

#include "CPlayer.h"
#include "CCoord.h"
#include "CMap.h"

/**
 * @brief
 * Class that represents special type of a player: MONSTER
 *
 */

class CPlayerMonster : public CPlayer {
public:

    /**
     * Constructor that initializes CPlayerMonster.
     *
     * @param coord          (player's coordinates)
     * @param HP             (player's HP)
     * @param airTime        (player's airTime)
     * @param direction      (player's direction)
     * @param lastDirection  (player's last direction)
     * @param damage         (player's damage)
     * @param count          (counter for AI)
     */
    CPlayerMonster ( const CCoord & coord, int HP, size_t airTime, EDirection direction,
                    EDirection lastDirection, size_t damage, size_t count );

    /**
     * Copy constructor that makes a deep copy of CPlayerMonster.
     *
     * @param other     (monster to be copied)
     */
    CPlayerMonster ( const CPlayerMonster & other );

    /**
     * Operator =. Copy & swap method is used.
     *
     * @param other (monster to be copied)
     * @return
     */
    CPlayerMonster & operator = ( CPlayerMonster other );

    /**
     * Method that saves a monster into a file in a specific format.
     *
     * @param filename     (file name)
     */
    void SavePlayer ( std::ofstream & filename ) const override;

    /**
     * Method that represents a monster attack.
     *
     * @return     (amount of damage)
     */
    size_t Attack () override;

    /**
     * Method that represents monster being hit.
     *
     * @param damage     (damage to be hit for)
     * @return           (itself)
     */
    CPlayer & ReceiveHit ( size_t damage ) override;

    /**
     * Method that returns a character based on player's direction.
     *
     * @return      (character)
     */
    char Print () const override;

    /**
     * Method that represents CPlayerMonster turn.
     *
     * @param map     (map according to which the monster can take decision)
     * @return        (always return true)
     */
    bool TakeTurn ( CMap & map ) override;

    /**
     * Method that prints the CPlayerMonster into the buffer.
     *
     * @param buffer    (buffer to be printed in)
     */
    void DrawIntoBuffer ( CBuffer & buffer ) override;

    /**
     * Method that makes copy of itself and returns it as an unique_ptr.
     *
     * @return      (pointer to the copied object)
     */
    std::unique_ptr<CPlayer> Clone() const override;

private:

    /**
     * Method that represents monster's AI. The monster uses the map to decide where to move.
     * The monster is careful not to fall from a height or step on the lava and
     * changes its movements regularly.
     * Method is not made const because it changes multiple CPlayerMonster's variables.
     *
     * @param map      (map according to which the monster makes decision)
     * @return         (itself)
     */
    CPlayer & setMove ( CMap & map );

    size_t m_Count;
    size_t m_Damage;
    static constexpr int MONSTER_MAX_HP = 500;
    static constexpr size_t MONSTER_MAX_DMG = 50;
};



