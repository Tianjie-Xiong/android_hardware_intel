////////////////////////////////////////////////////////////////////////////
// channel_URC.cpp
//
// Copyright 2005-2011 Intrinsyc Software International, Inc.  All rights reserved.
// Patents pending in the United States of America and other jurisdictions.
//
//
// Description:
//    Provides implementations for helper functions used
//    to facilitate the use of multiple AT channels.
//    All URCs go on this channel.
//
/////////////////////////////////////////////////////////////////////////////

#include "types.h"
#include "rillog.h"
#include "channelbase.h"
#include "channel_URC.h"

extern char* g_szURCPort;
extern BOOL  g_bIsSocket;

// Init strings for this channel.
//  All URCs go on this channel.

// Add any init cmd strings for this channel during PowerOn or Ready boot phase
INITSTRING_DATA URCPowerOnInitString = { "" };
INITSTRING_DATA URCReadyInitString   = { "" };

CChannel_URC::CChannel_URC(UINT32 uiChannel)
: CChannel(uiChannel)
{
    RIL_LOG_VERBOSE("CChannel_URC::CChannel_URC() - Enter\r\n");
    RIL_LOG_VERBOSE("CChannel_URC::CChannel_URC() - Exit\r\n");
}

CChannel_URC::~CChannel_URC()
{
    RIL_LOG_VERBOSE("CChannel_URC::~CChannel_URC() - Enter\r\n");
    delete[] m_paInitCmdStrings;
    m_paInitCmdStrings = NULL;
    RIL_LOG_VERBOSE("CChannel_URC::~CChannel_URC() - Exit\r\n");
}

//  Override from base class
BOOL CChannel_URC::OpenPort()
{
    BOOL bRetVal = FALSE;

    RIL_LOG_INFO("CChannel_URC::OpenPort() - Opening COM Port: %s...\r\n", g_szURCPort);
    RIL_LOG_INFO("CChannel_URC::OpenPort() - g_bIsSocket=[%d]...\r\n", g_bIsSocket);

    bRetVal = m_Port.Open(g_szURCPort, g_bIsSocket);

    RIL_LOG_INFO("CChannel_URC::OpenPort() - Opening COM Port: %s\r\n",
            bRetVal ? "SUCCESS" : "FAILED!");

    return bRetVal;
}

BOOL CChannel_URC::FinishInit()
{
    RIL_LOG_VERBOSE("CChannel_URC::FinishInit() - Enter\r\n");
    BOOL bRet = FALSE;

    //  Init our channel AT init commands.
    m_paInitCmdStrings = new INITSTRING_DATA[COM_MAX_INDEX];
    if (!m_paInitCmdStrings)
    {
        RIL_LOG_CRITICAL("CChannel_URC::FinishInit() - chnl=[%d] Could not create new"
                " INITSTRING_DATA\r\n", m_uiRilChannel);
        goto Error;
    }

    // Set the init command strings for this channel
    m_paInitCmdStrings[COM_BASIC_INIT_INDEX].szCmd = m_szChannelBasicInitCmd;
    m_paInitCmdStrings[COM_UNLOCK_INIT_INDEX].szCmd = m_szChannelUnlockInitCmd;
    m_paInitCmdStrings[COM_POWER_ON_INIT_INDEX] = URCPowerOnInitString;
    m_paInitCmdStrings[COM_READY_INIT_INDEX] = URCReadyInitString;

    bRet = TRUE;
Error:
    RIL_LOG_VERBOSE("CChannel_URC::FinishInit() - Exit\r\n");
    return bRet;
}
