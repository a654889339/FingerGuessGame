#include "stdafx.h"
#include "ClientControl.h"
#include "ClientWorld.h"

#define REGISTER_EXTERNAL_FUNC(ProtocolID, FuncName)  \
{m_ProcessProtocolFuns[ProtocolID] = FuncName;}

ClientControl::ClientControl()
{
    m_bCheckInput = false;

    memset(m_szInstruct, 0, sizeof(m_szInstruct));
    memset(m_ProcessProtocolFuns, 0, sizeof(m_ProcessProtocolFuns));


    REGISTER_EXTERNAL_FUNC(cipc_show, &ClientControl::OnShow);
    REGISTER_EXTERNAL_FUNC(cipc_create, &ClientControl::OnCreate);
    REGISTER_EXTERNAL_FUNC(cipc_join, &ClientControl::OnJoin);
    REGISTER_EXTERNAL_FUNC(cipc_quit, &ClientControl::OnQuit);
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
    Input();
    ProcessInput();
}

//////////////////////////////////////////////////////////////////////////


void ClientControl::OnShow()
{
    g_pClient->m_Connection.DoC2SApplyAllPlayerRequest();
}

void ClientControl::OnCreate()
{
    g_pClient->m_Connection.DoCreateGameRequest();
}

void ClientControl::OnJoin()
{

}

void ClientControl::OnQuit()
{
    g_pClient->Quit();
}

//////////////////////////////////////////////////////////////////////////
void ClientControl::Input()
{
    bool bResult = false;
    bool bRetCode = false;
    char cInput = 0;

    while (_kbhit())
    {
        JY_PROCESS_SUCCESS(m_Input.res_size() == 0);

        cInput = _getche();

        if (cInput == '\r')
            cInput = '\n';

        bRetCode = m_Input.push(&cInput, 1);
        JYLOG_PROCESS_ERROR(bRetCode);

        m_bCheckInput = true;
    }

Exit1:
    bResult = true;
Exit0:
    if (!bResult)
    {
        printf("[ClientControl] Input Error.\n");
        g_pClient->Quit();
    }
    return ;
}

void ClientControl::ProcessInput()
{
    bool bRetCode = false;
    int nInputSize = -1;
    CLIENT_INPUT_PROTOCOL_CODE eInputCode = cipc_invalid;
    PROCESS_PROTOCOL_FUNC Func = NULL;

    JY_PROCESS_ERROR(m_Input.size() && m_bCheckInput);

    m_bCheckInput = false;

    nInputSize = m_Input.find('\n');
    JY_PROCESS_ERROR(nInputSize != -1);

    bRetCode = m_Input.pop(nInputSize + 1, m_szInstruct);
    JYLOG_PROCESS_ERROR(bRetCode);

    m_bCheckInput = true;
    m_szInstruct[nInputSize] = '\0';

    for (int i = cipc_invalid + 1; i < cipc_total; i++)
    {
        if (strcmp(m_szInstruct, _szInputProtocolName[i]) == 0)
        {
            eInputCode = (CLIENT_INPUT_PROTOCOL_CODE)i;
            break;
        }
    }
    if (eInputCode == cipc_invalid)
    {
        printf("[ClientControl] Undefined instruction: %s.\n", m_szInstruct);
        goto Exit0;
    }

    Func = m_ProcessProtocolFuns[eInputCode];
    JYLOG_PROCESS_ERROR(Func);

    (this->*Func)();

    JY_STD_VOID_END
}
