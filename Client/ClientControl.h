#ifndef _CLIENT_CONTROL_H_
#define _CLIENT_CONTROL_H_

#include "ClientInputDef.h"
#include "ClientBase.h"

class ClientControl
{
public:
    ClientControl();
    virtual ~ClientControl();

    bool Init();
    void UnInit();

    void Active();

private:
    bool CheckState(GameState eGameState);

    void OnShow();
    void OnCreate();
    void OnJoin();
    void OnJoinInputName();
    void OnRock();
    void OnScissors();
    void OnPaper();
    void OnQuit();

    void Input();
    void ProcessInput();

private:
    typedef void (ClientControl::*PROCESS_PROTOCOL_FUNC)();
    PROCESS_PROTOCOL_FUNC   m_ProcessProtocolFuns[cipc_total];

    typedef CycleQueue<char> CLIENT_CONTROL_BUFFER;
    CLIENT_CONTROL_BUFFER m_Input;

    bool m_bCheckInput;
    bool m_bJoinInputName;
    char m_szInstruct[MAX_INPUT_BUFFER_SIZE];
};

#endif