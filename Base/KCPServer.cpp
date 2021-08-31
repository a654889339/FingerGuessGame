#include "stdafx.h"
#include "KCPServer.h"

KCPServer::KCPServer()
{
    memset(m_nConnecFlag, -1, sizeof(m_nConnecFlag));
}

KCPServer::~KCPServer()
{

}