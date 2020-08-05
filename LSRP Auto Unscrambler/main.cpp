
#include "main.h"

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")

DWORD				g_SAMP;
HANDLE				g_DllHandle;

CSimpleIniA			config;
stSettings			settings;

bool _UnsWork = false;
bool _conLastStatus = false;
ULONGLONG _UnsNewTick = -1;
std::string _UnsSolved;
std::string _UnsLastWord = "NaN";
bool LicenseVerified = false;
std::vector<std::string> wordList;


std::string workingDir()
{
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}

void SaveConfig()
{
	config.SetBoolValue("main", "useConsole", settings.useConsole);
	config.SetBoolValue("main", "useGameTexts", settings.useGameTexts);
	config.SetLongValue("main", "initWaitTime", settings.initWaitTime);
	config.SetLongValue("main", "mainLoopDelay", settings.mainLoopDelay);

	config.SetLongValue("unscrambler", "unscrambleDelay", settings.unscrambleDelay);
	config.SetValue("unscrambler", "cmdExec", settings.cmdExec);
	config.SetValue("unscrambler", "stringSearch", settings.stringSearch);
	config.SetValue("unscrambler", "stringSeparateLeft", settings.stringSeparateLeft);
	config.SetValue("unscrambler", "stringSeparateRight", settings.stringSeparateRight);

	config.SaveFile(string(workingDir() + "\\AutoUnscrambler.ini").c_str());
}

void CreateConfig()
{
	FILE* szFile;
	szFile = fopen(string(workingDir() + "\\AutoUnscrambler.ini").c_str(), "w");
	if (szFile != NULL)
	{
		fclose(szFile);
	}

	config.LoadFile(string(workingDir() + "\\AutoUnscrambler.ini").c_str());

	SaveConfig();
}

void LoadConfig()
{
	config.LoadFile(string(workingDir() + "\\AutoUnscrambler.ini").c_str());

	settings.useConsole = config.GetBoolValue("main", "useConsole", false);
	settings.useGameTexts = config.GetBoolValue("main", "useGameTexts", true);
	settings.initWaitTime = config.GetLongValue("main", "initWaitTime", 332996);
	settings.mainLoopDelay = config.GetLongValue("main", "mainLoopDelay", 100);

	settings.unscrambleDelay = config.GetLongValue("unscrambler", "unscrambleDelay", 750);

	settings.cmdExec = config.GetValue("unscrambler", "cmdExec", "/uns");

	settings.stringSearch = config.GetValue("unscrambler", "stringSearch", " to unscramble the word.~n~\"~w~");
	settings.stringSeparateLeft = config.GetValue("unscrambler", "stringSeparateLeft", "\"~w~");
	settings.stringSeparateRight = config.GetValue("unscrambler", "stringSeparateRight", "~r~\"");

	if (settings.useConsole && _conLastStatus == false)
	{
		_conLastStatus = true;
		AllocConsole();
		AttachConsole(GetCurrentProcessId());

		void *frepo = freopen("CON", "w", stdout);

		SetConsoleTitle("Auto Unscrambler");
		system("cls");
	}
	else if (!settings.useConsole && _conLastStatus == true)
	{
		FreeConsole();
		_conLastStatus = false;
	}
	return;
}

void LoadWordlist()
{
	wordList.clear();
	std::ifstream dictionary(workingDir() + "\\wordlist.txt");
	if (!dictionary.is_open())
	{
		std::ofstream dictFileEx(workingDir() + "\\wordlist.txt");
		if (dictFileEx.is_open())
		{
			dictFileEx << "[dont_remove_this]";
		}
		dictFileEx.close();
	}
	else
	{
		std::string temp;
		while (!dictionary.eof())
		{
			dictionary >> temp;
			wordList.push_back(temp);
		}
	}
	dictionary.close();
	return;
}

void Main()
{
	Sleep(2000);
	if (!FileExists(string(workingDir() + "\\AutoUnscrambler.ini").c_str()))
	{
		CreateConfig();
	}
	else
	{
		LoadConfig();
	}

	LoadWordlist();

	if (settings.initWaitTime == 8346996)
	{
		settings.initWaitTime = 30000;
		Main();
		return;
	}

	Sleep(settings.initWaitTime);

	g_SAMP = (DWORD)GetModuleHandle("samp.dll");


	if (settings.useConsole)
	{
		SetConsoleTitle("Auto Unscrambler");
		system("cls");
	}

	if (settings.useGameTexts) showGameText("~y~Auto Unscrambler Loaded ~n~ ~b~By 0x32789", 650, 5);


	printf("[INIT] Loading SAMP, base at -> %#X\n", g_SAMP);

	g_stSAMP = stGetSampInfo();
	
	ULONGLONG lastUpdateTick = GetTickCount64();

	while (true)
	{
		#ifdef ENABLE_VERIFICATION
		if (!LicenseVerified)
		{
			FreeConsole();
			break;
		}
		#endif

		if (_UnsWork && (_UnsNewTick == -1 || GetTickCount64() > _UnsNewTick))
		{
			char cmdEx[92] = { 0 };
			sprintf(cmdEx, "%s %s", settings.cmdExec, _UnsSolved.c_str());

			printf("[UNSCRAMBLER] Sending command (uns): %s\n", cmdEx);
			say(cmdEx);

			_UnsWork = false;
			_UnsNewTick = -1;
			_UnsSolved = "";
		}

		if(GetAsyncKeyState(0x74)) // F5
		{
			printf("[UNSCRAMBLER] Reloading config...\n");

			LoadConfig();

			_UnsWork = false;
			_UnsSolved = "";
			_UnsNewTick = -1;

			LoadWordlist();
			
			if (settings.useGameTexts) showGameText("~b~Reloading", 1250, 5);
			Sleep(1000);
		}

		if(settings.useConsole)
		{
			if (GetAsyncKeyState(0x71)) // F2
			{
				ShowWindow(GetConsoleWindow(), SW_HIDE);

				printf("[CONSOLE] Console hidden.\n");
				SetConsoleTitle("Auto Unscrambler - Hidden");
				if(settings.useGameTexts) showGameText("~g~Console Hidden!", 1000, 5);
				Sleep(750);
			}
			else if (GetAsyncKeyState(0x72)) // F3
			{
				ShowWindow(GetConsoleWindow(), SW_SHOW);

				printf("[CONSOLE] Console unhidden.\n");
				SetConsoleTitle("Auto Unscrambler");
				if(settings.useGameTexts) showGameText("~r~Console Unhidden!", 1000, 5);
				Sleep(750);
			}
		}

		/*if (GetTickCount64() - lastUpdateTick > (DWORD)settings.textUpdateDelay)
		{
			g_stSAMP = stGetSampInfo();
			lastUpdateTick = GetTickCount64();
		}*/

        if (_UnsWork == false)
        {
            for (int i = 0; i < 255; i++)
            {
                if (g_stSAMP->pPools->pTextdraw->playerTextdraw[i]->szText == nullptr) continue;

                char* findPos = strstr(g_stSAMP->pPools->pTextdraw->playerTextdraw[i]->szText, settings.stringSearch);
                if (findPos != NULL)
                {
                    std::string extracted = extractfromstr(g_stSAMP->pPools->pTextdraw->playerTextdraw[i]->szText, settings.stringSeparateLeft, settings.stringSeparateRight);

                    if (extracted.length() > 2 && _UnsLastWord.compare(extracted) != 0)
                    {
                        std::string word = extracted;
                        _UnsLastWord = word;
                        bool foundIt = false;
                        int countInz = 0;
                        for (unsigned int i = 0; i < wordList.size(); i++)
                        {
                            if (foundIt == true) break;
                            countInz = 0;
                            std::sort(word.begin(), word.end());
                            do
                            {
                                if (word.compare(extracted) == 0)
                                {
                                    countInz++;
                                    if (wordList[i].compare(word) == 0)
                                    {
                                        foundIt = true;
                                        break;
                                    }
                                    if (countInz > 5) break;
                                }
                                if (wordList[i].compare(word) == 0)
                                {
                                    foundIt = true;
                                    break;
                                }
                            } while (next_permutation(word.begin(), word.end()));
                        }
                        if (foundIt == true)
                        {
							printf("[UNSCRAMBLER] Calculated Word: %s\n", word.c_str());
                            _UnsSolved = word;
                            _UnsNewTick = GetTickCount64() + settings.unscrambleDelay;
                            _UnsWork = true;
                        }
                    }
                }
			}
		}
		Sleep(settings.mainLoopDelay);
	}
}


BOOL WINAPI DllMain(
	HINSTANCE hinstDLL, 
	DWORD fdwReason,    
	LPVOID lpReserved) 
{

	g_DllHandle = hinstDLL;

	DisableThreadLibraryCalls((HMODULE)hinstDLL);

	if (fdwReason != DLL_PROCESS_ATTACH)
		return FALSE;

	if (GetModuleHandle("samp.dll"))
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Main, NULL, 0, NULL);

	return TRUE;  
}