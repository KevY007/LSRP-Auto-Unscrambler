#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <cstdio>
#include <stdio.h>
#include <cassert>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <intrin.h>
#include "ConvertUTF.h"
#include "SimpleIni.h"
#include "functions.h"

using namespace std;

extern DWORD g_SAMP;
extern HANDLE g_DllHandle;

struct stSettings
{
	bool useConsole = false;
	bool useGameTexts = true;
	long initWaitTime = 30000;
	long mainLoopDelay = 100;

	long unscrambleDelay = 750;

	const char* cmdExec = "/uns";

	const char* stringSearch = " to unscramble the word.~n~\"~w~";
	const char* stringSeparateLeft = "\"~w~";
	const char* stringSeparateRight = "~r~\"";
};



enum ChatMessageType
{
	CHAT_TYPE_NONE = 0,
	CHAT_TYPE_CHAT = 2,
	CHAT_TYPE_INFO = 4,
	CHAT_TYPE_DEBUG = 8
};


#define SAMP_CHAT_INFO_OFFSET						0x2ACA10
#define SAMP_CHAT_INPUT_INFO_OFFSET					0x2ACA14
#define SAMP_INFO_OFFSET							0x2ACA24
#define SAMP_MISC_INFO								0x2ACA3C
#define SAMP_DRAWING_DISTANCE						0x11812C


#define SAMP_FUNC_ADDTOCHATWND						0x67650
#define SAMP_FUNC_SAY								0x5860
#define SAMP_FUNC_SENDCMD							0x69340




