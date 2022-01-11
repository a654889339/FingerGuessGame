#include "stdafx.h"
#include "ClientControl.h"
#include "ClientLogic.h"

ClientControl::ClientControl()
{
    m_bCheckInput = false;

    memset(m_szInstruct, 0, sizeof(m_szInstruct));
    memset(m_ProcessProtocolFuns, 0, sizeof(m_ProcessProtocolFuns));


    //REGISTER_EXTERNAL_FUNC(cipc_show, &ClientControl::OnShow);
    //REGISTER_EXTERNAL_FUNC(cipc_create, &ClientControl::OnCreate);
    //REGISTER_EXTERNAL_FUNC(cipc_join, &ClientControl::OnJoin);
    //REGISTER_EXTERNAL_FUNC(cipc_join_input_name, &ClientControl::OnJoinInputName);
    //REGISTER_EXTERNAL_FUNC(cipc_game_rock, &ClientControl::OnRock);
    //REGISTER_EXTERNAL_FUNC(cipc_game_scissors, &ClientControl::OnScissors);
    //REGISTER_EXTERNAL_FUNC(cipc_game_paper, &ClientControl::OnPaper);
    //REGISTER_EXTERNAL_FUNC(cipc_quit, &ClientControl::OnQuit);
}

ClientControl::~ClientControl()
{

}

bool ClientControl::Init()
{
    bool bResult = false;
    bool bRetCode = false;

    bRetCode = m_Input.init(MAX_INPUT_BUFFER_SIZE);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void ClientControl::UnInit()
{

}

void ClientControl::Active()
{
}

//////////////////////////////////////////////////////////////////////////
void ClientControl::OnQuit()
{
    g_pClient->Quit();
}

//////////////////////////////////////////////////////////////////////////
