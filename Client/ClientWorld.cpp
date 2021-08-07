#include "stdafx.h"
#include "ClientWorld.h"

ClientWorld::ClientWorld()
{
    m_nPort = 0;
    memset(m_szIP, 0, sizeof(m_szIP));
}

ClientWorld::~ClientWorld()
{

}

bool ClientWorld::Init()
{
    bool bResult = false;
    bool bRetCode = false;

    bRetCode = LoadConfig();
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void ClientWorld::UnInit()
{

}


bool ClientWorld::LoadConfig()
{
    bool bResult = false;

    strcpy(m_szIP, "127.0.0.1");
    m_nPort = 5566;

    JY_STD_BOOL_END
}