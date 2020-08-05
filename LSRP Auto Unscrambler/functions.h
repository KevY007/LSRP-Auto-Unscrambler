#pragma once

#include "main.h"

void showGameText(const char* text, int time, int style);
void say(const char* szText);
void sayfunc(char* szText);
bool FileExists(const std::string& filename);

struct stSAMP* stGetSampInfo(void);
extern struct stSAMP* g_stSAMP;

std::string extractfromstr(const char* scc, const char* start_delim, const char* stop_delim);
std::string extractfromstr(const std::string& s, const std::string& start_delim, const std::string& stop_delim);
std::string GetMachineGuid();
std::string GetMoboModel();
std::string GetCPUID();

#pragma pack(push, 1)

enum Limits
{
	SAMP_MAX_ACTORS = 1000,
	SAMP_MAX_PLAYERS = 1004,
	SAMP_MAX_VEHICLES = 2000,
	SAMP_MAX_PICKUPS = 4096,
	SAMP_MAX_OBJECTS = 2100,
	SAMP_MAX_GANGZONES = 1024,
	SAMP_MAX_3DTEXTS = 2048,
	SAMP_MAX_TEXTDRAWS = 2048,
	SAMP_MAX_PLAYERTEXTDRAWS = 256,
	SAMP_MAX_CLIENTCMDS = 144,
	SAMP_MAX_MENUS = 128,
	SAMP_MAX_PLAYER_NAME = 24,
	SAMP_ALLOWED_PLAYER_NAME_LENGTH = 20,
	SAMP_MAX_MAPICONS = 100,
};

enum Gamestate
{
	GAMESTATE_WAIT_CONNECT = 9,
	GAMESTATE_CONNECTING = 13,
	GAMESTATE_AWAIT_JOIN = 15,
	GAMESTATE_CONNECTED = 14,
	GAMESTATE_RESTARTING = 18
};

struct stSAMPPools
{
	void* pMenu;
	struct stActorPool* pActor;
	struct stPlayerPool* pPlayer;
	struct stVehiclePool* pVehicle;
	struct stPickupPool* pPickup;
	struct stObjectPool* pObject;
	struct stGangzonePool* pGangzone;
	struct stTextLabelPool* pText3D;
	struct stTextdrawPool* pTextdraw;
};

struct stSAMP
{
	uint8_t                  	_pad0[20];
	void* pUnk0;
	struct stServerInfo* pServerInfo;
	uint8_t				_pad1[16];
	void* pRakClientInterface;
	char				szIP[256 + 1];
	char				szHostname[256 + 1];
	uint8_t                 	_pad2;
	bool                    	m_bUpdateCameraTarget;
	bool				m_bNoNameTagStatus;
	uint32_t			ulPort;
	BOOL				m_bLanMode;
	uint32_t			ulMapIcons[SAMP_MAX_MAPICONS];
	Gamestate			iGameState;
	uint32_t			ulConnectTick;
	struct stServerPresets* pSettings;
	uint8_t                 	_pad3[5];
	struct stSAMPPools* pPools;
};

struct stTextdraw
{
	char		szText[800 + 1];
	char		szString[1600 + 2];
	float		fLetterWidth;
	float		fLetterHeight;
	DWORD		dwLetterColor;
	uint8_t		byte_unk;	// always = 01 (?)
	BYTE		byteCenter;
	BYTE		byteBox;
	float		fBoxSizeX;
	float		fBoxSizeY;
	DWORD		dwBoxColor;
	BYTE		byteProportional;
	DWORD		dwShadowColor;
	BYTE		byteShadowSize;
	BYTE		byteOutline;
	BYTE		byteLeft;
	BYTE		byteRight;
	int			iStyle;		// font style/texture/model
	float		fX;
	float		fY;
	byte		unk[8];
	DWORD		dword99B;	// -1 by default
	DWORD		dword99F;	// -1 by default
	DWORD		index;		// -1 if bad
	BYTE		byte9A7;	// = 1; 0 by default
	uint16_t	sModel;
	float		fRot[3];
	float		fZoom;
	WORD		sColor[2];
	BYTE		f9BE;
	BYTE		byte9BF;
	BYTE		byte9C0;
	DWORD		dword9C1;
	DWORD		dword9C5;
	DWORD		dword9C9;
	DWORD		dword9CD;
	BYTE		byte9D1;
	DWORD		dword9D2;
};

struct stTextdrawPool
{
	int					iIsListed[SAMP_MAX_TEXTDRAWS];
	int					iPlayerTextDraw[SAMP_MAX_PLAYERTEXTDRAWS];
	struct stTextdraw* textdraw[SAMP_MAX_TEXTDRAWS];
	struct stTextdraw* playerTextdraw[SAMP_MAX_PLAYERTEXTDRAWS];
};

struct stServerInfo {
	uint32_t 			uiIP;
	uint16_t 			usPort;

	// ...

};

struct stServerPresets
{
	uint8_t byteCJWalk;
	int m_iDeathDropMoney;
	float	fWorldBoundaries[4];
	bool m_bAllowWeapons;
	float	fGravity;
	uint8_t byteDisableInteriorEnterExits;
	uint32_t ulVehicleFriendlyFire;
	bool m_byteHoldTime;
	bool m_bInstagib;
	bool m_bZoneNames;
	bool m_byteFriendlyFire;
	int		iClassesAvailable;
	float	fNameTagsDistance;
	bool m_bManualVehicleEngineAndLight;
	uint8_t byteWorldTime_Hour;
	uint8_t byteWorldTime_Minute;
	uint8_t byteWeather;
	uint8_t byteNoNametagsBehindWalls;
	int iPlayerMarkersMode;
	float	fGlobalChatRadiusLimit;
	uint8_t byteShowNameTags;
	bool m_bLimitGlobalChatRadius;
};