#include "stdafx.h"
#include "Player.h"

Player::Player()
{
    m_nConnIndex = 0;
    memset(m_szName, 0, sizeof(m_szName));
}

Player::~Player()
{

}

bool Player::Init(int nConnIndex, const char szName[])
{
    bool bResult = false;

    m_nConnIndex = nConnIndex;

    strncpy(m_szName, szName, sizeof(m_szName));
    m_szName[sizeof(m_szName) - 1] = '\0';

    JY_STD_BOOL_END
}
void Player::UnInit()
{

}