#include "main.h"

struct stSAMP* g_stSAMP;

bool FileExists(const std::string& filename)
{
	WIN32_FIND_DATAA fd = { 0 };
	HANDLE hFound = FindFirstFileA(filename.c_str(), &fd);
	bool retval = hFound != INVALID_HANDLE_VALUE;
	FindClose(hFound);

	return retval;
}

void sayfunc(char* szText)
{
	if (g_SAMP == NULL) return;

	if (szText[0] == '/')
	{
		((void(__thiscall*) (void* _this, char* message)) (g_SAMP + SAMP_FUNC_SENDCMD))(0, szText);
	}
	else
	{
		((void(__thiscall*) (void* _this, char* message)) (g_SAMP + SAMP_FUNC_SAY)) (0, szText);
	}

	return;
}

void say(const char* szText)
{
	char converted[128] = { 0 };
	sprintf(converted, "%s", szText);
	sayfunc(converted);
	return;
}

void showGameText(const char* text, int time, int style)
{
	((void(__cdecl*) (uint32_t something)) (0x0069DCD0)) (0);
	((void(__cdecl*) (const char* text, int time, int style)) (0x0069F2B0)) (text, time, style);
}

std::string extractfromstr(const std::string& s,
	const std::string& start_delim,
	const std::string& stop_delim)
{
	unsigned first_delim_pos = s.find(start_delim);
	unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
	unsigned last_delim_pos = s.find(stop_delim);

	return s.substr(end_pos_of_first_delim,
		last_delim_pos - end_pos_of_first_delim);
}

std::string extractfromstr(const char* scc,
	const char* start_delim,
	const char* stop_delim)
{
	std::string s = scc;

	unsigned first_delim_pos = s.find(start_delim);
	unsigned end_pos_of_first_delim = first_delim_pos + strlen(start_delim);
	unsigned last_delim_pos = s.find(stop_delim);

	return s.substr(end_pos_of_first_delim,
		last_delim_pos - end_pos_of_first_delim);
}

template<typename T>
T GetSAMPPtrInfo(uint32_t offset)
{

	return *(T*)(g_SAMP + offset);
}

struct stSAMP* stGetSampInfo(void)
{
	return GetSAMPPtrInfo<stSAMP*>(SAMP_INFO_OFFSET);
}

std::string GetCPUID() {

	int CPUInfo[4] = { -1 };
	__cpuid(CPUInfo, 0);
	if (CPUInfo[0] < 4)
		return ""; //Error on retrieving

	stringstream srt;
	for (int i = 0; i <= 3; i++) {
		srt << CPUInfo[i];
	}

	return srt.str();

}

std::string GetMoboModel()
{
	std::string key = "HARDWARE\\DESCRIPTION\\System\\BIOS";
	std::string name = "BaseBoardProduct";

	HKEY hKey;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, key.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, &hKey) != ERROR_SUCCESS) return "NaN";

	DWORD type;
	DWORD cbData;

	if (RegQueryValueEx(hKey, name.c_str(), NULL, &type, NULL, &cbData) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return "NaN";
	}

	if (type != REG_SZ)
	{
		RegCloseKey(hKey);
		return "NaN";
	}

	std::string value(cbData / sizeof(char), '\0');
	if (RegQueryValueEx(hKey, name.c_str(), NULL, NULL, reinterpret_cast<LPBYTE>(&value[0]), &cbData) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return "NaN";
	}

	RegCloseKey(hKey);
	return value;
}


std::string GetMachineGuid()
{
	std::string key = "SOFTWARE\\Microsoft\\Cryptography";
	std::string name = "MachineGuid";

	HKEY hKey;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, key.c_str(), 0, KEY_READ | KEY_WOW64_64KEY, &hKey) != ERROR_SUCCESS) return "NaN";

	DWORD type;
	DWORD cbData;

	if (RegQueryValueEx(hKey, name.c_str(), NULL, &type, NULL, &cbData) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return "NaN";
	}

	if (type != REG_SZ)
	{
		RegCloseKey(hKey);
		return "NaN";
	}

	std::string value(cbData / sizeof(char), '\0');
	if (RegQueryValueEx(hKey, name.c_str(), NULL, NULL, reinterpret_cast<LPBYTE>(&value[0]), &cbData) != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return "NaN";
	}

	RegCloseKey(hKey);
	return value;
}