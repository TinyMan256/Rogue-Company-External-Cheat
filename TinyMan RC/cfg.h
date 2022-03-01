#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include "other.h"
#include "imgui/imgui.h"

DWORD keys[] = { VK_LMENU, VK_MENU, VK_SHIFT, VK_RSHIFT, VK_CONTROL, VK_RCONTROL, VK_LBUTTON, VK_RBUTTON };
const char* keyItems[] = { "LAlt", "RAlt", "LShift", "RShift", "LControl", "RControl", "LMouse", "RMouse" };
DWORD keys2[] = { VK_HOME, VK_INSERT, VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10 };
const char* keyItems2[] = { "Home", "Insert", "UP", "DOWN", "RIGHT", "LEFT", "F1", "F2", "F3","F4","F5","F6","F7","F8","F9","F10" };
DWORD keys3[] = { VK_LMENU, VK_MENU, VK_SHIFT, VK_RSHIFT, VK_CONTROL, VK_RCONTROL, VK_LBUTTON, VK_RBUTTON , VK_HOME, VK_INSERT, VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10 };
const char* keyItems3[] = { "LAlt", "RAlt", "LShift", "RShift", "LControl", "RControl", "LMouse", "RMouse" , "Home", "Insert", "UP", "DOWN", "RIGHT", "LEFT", "F1", "F2", "F3","F4","F5","F6","F7","F8","F9","F10" };
DWORD keys4[] = {VK_END, VK_DELETE ,VK_LMENU, VK_MENU, VK_SHIFT, VK_RSHIFT, VK_CONTROL, VK_RCONTROL, VK_LBUTTON, VK_RBUTTON , VK_HOME, VK_INSERT, VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10 };
const char* keyItems4[] = {"End","Delete", "LAlt", "RAlt", "LShift", "RShift", "LControl", "RControl", "LMouse", "RMouse" , "Home", "Insert", "UP", "DOWN", "RIGHT", "LEFT", "F1", "F2", "F3","F4","F5","F6","F7","F8","F9","F10" };
DWORD keys5[] = { VK_END, VK_DELETE ,VK_LMENU, VK_MENU, VK_SHIFT, VK_RSHIFT, VK_CONTROL, VK_RCONTROL, VK_LBUTTON, VK_RBUTTON , VK_HOME, VK_INSERT, VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10 };
const char* keyItems5[] = { "End","Delete", "LAlt", "RAlt", "LShift", "RShift", "LControl", "RControl", "LMouse", "RMouse" , "Home", "Insert", "UP", "DOWN", "RIGHT", "LEFT", "F1", "F2", "F3","F4","F5","F6","F7","F8","F9","F10" };

inline namespace Configuration
{
	class Settings : public Singleton<Settings>
	{
	public:
		const char* BoxTypes[2] = { "Full Box","Cornered Box" };
		const char* LineTypes[5] = { "Bottom To Enemy","Top To Enemy","Crosshair To Enemy", "Top left", "Top Right" };
		const char* FireTypes[3] = { "Single","Burst","Semi-auto" };
		const char* DamageTypes[2] = { "Explosion","instant kill" };
		const char* ReloadTypes[2] = { "Clip","SingleShot" };
		const char* weaponstates[10] = { "Buildup","PreFire","PostFire","Cooldown","PreReload","PostReload","ReloadCooldown","Retrieve","Holster","Inactive" };
		const char* ReticleTypes[8] = { "None","Pistol","Rifle","Shotgun","Circle","Gatling","ChaosLauncher","Stealth" };
		const char* weaponequiptypes[4] = { "Normal","Special","GameMode","Gambit" };
		bool reticletype = false;
		int reticletypee = 4;
		bool checkbox = false;
		bool shootingrangeinstatntkill = false;
		float f_shootingrangeinstatntkill = 500.f;
		bool fastbulletsmelee = false;
		bool NoAimsDuringReload = true;
		bool openscopespeed = true;
		float f_openscopespeed = 0.0f;
		float f_fastbulletsmelee = 0.f;
		bool shootingrangewalkspeed = false;
		float f_shootingrangewalkspeed = 100.f;
		bool roundsperburst = false;
		int i_roundsperburst = 5;
		bool clipsize = false;
		int i_clipsize = 100;
		bool damagetype = false;
		bool weaponstate = false;
		bool startupsound = true;
		int weaponstatee = 0;
		int damagetypee = 0;
		bool fastreload = true;
		bool autosaveloadsettings = true;
		bool halfreload = false;
		bool lowendpc = false;
		bool aimdownsights = false;
		bool aimfov = false;
		float f_aimfov = 15.0f;
		bool firetypebool = true;
		bool reloadtypebool = true;
		bool nospread = true;
		bool togglebutton = true;
		bool fullnameesp = true;
		bool collision = false;
		bool ping = false;
		bool teamcollision = false;
		bool nameesp = false;
		bool noreload = true;
		bool trollnoreload = false;
		bool trollnofire = false;
		bool trollaimdownsights = false;
		bool trollaimovershoulder = false;
		int EKSWeaponEquipType = 0;
		bool EKSWeaponEquipTypebool = false;
		bool test = false;
		bool test2 = false;
		bool test3 = false;
		bool bunnyhop = false;
		bool bunnyhop2 = false;
		bool meleeteleportlow = false;
		bool meleeteleportmidium = false;
		bool meleeteleporthigh = false;
		bool enableknocked = false;
		bool disableknocked = false;
		bool crosshair = false;
		bool selfesp = false;
		bool canmovewhilerevive = false;
		bool friendsesp = false;
		bool friendsaim = false;
		bool Immune = false;
		bool Nodieesp = true;
		bool noreloadaim = true;
		bool Nodieaim = true;
		bool noragdoll = false;
		bool deadesp = false;
		bool botsgodmode = false;
		bool b_MenuShow = true;
		bool thickskeleton = false;
		bool randomcheatnameloop = false;
		bool headcircle = false;
		bool freecam = true;
		bool enemiesesp = true;
		bool botsesp = true;
		bool autoaim = false;
		bool lootesp = false;
		bool norecoil = true;
		bool supermeleelow = false;
		bool supermeleemedium = false;
		bool supermeleehigh = false;
		bool supermeleesuper = false;
		bool enemygodmode = false;
		bool menufps = true;
		bool hideconsole = true;
		bool allvisuals = true;
		bool fakegodmode = false;
		bool burstrounds = false;
		bool fastland = false;
		bool b_EspBox = true;
		bool b_EspSkeleton = false;
		bool b_EspLine = true;
		bool nodownesp = true;
		bool nodownaim = true;
		bool unlimitedammo = true;
		bool b_EspDistance = true;
		bool healthbar = false;
		bool healthbaroutline = false;
		bool healthpercenet = false;
		bool healthregeneration = false;
		bool healthregenerationslow = false;
		bool glow = false;
		bool glowcolor = false;
		bool aimbot = true;
		bool autoscope = false;
		bool b_Aimbot = true;
		bool b_AimbotFOV = false;
		bool b_AimbotSmooth = true;
		bool invisible_color = false;
		bool visible_color = false;
		bool bdowned = false;
		bool eliminated = false;
		bool showcursor = true;
		bool menubanner = true;
		bool rainbowtheme = false;
		bool defaulththeme = true;
		bool theme1 = false;
		bool theme2 = false;
		bool theme3 = false;
		bool theme4 = false;
		bool theme5 = false;
		bool theme6 = false;
		bool theme7 = false;
		bool theme8 = false;
		bool theme9 = false;
		bool theme10 = false;
		bool theme11 = false;
		bool theme12 = false;
		bool theme13 = false;
		bool theme14 = false;
		bool theme15 = false;
		bool theme16 = false;
		bool theme17 = false;
		bool theme18 = false;
		bool theme19 = false;
		bool theme20 = false;
		bool theme21 = false;
		bool theme22 = false;
		bool theme23 = false;
		bool theme24 = false;
		bool theme25 = false;
		bool theme26 = false;
		bool theme27 = false;
		bool theme28 = false;
		bool theme29 = false;
		//ImColor glowcolor = ImColor(255.f / 255, 0.f, 0.f);
		//float fl_glowcolor[3] = { 0.f,255.f / 255,0.f };
		ImColor VisibleColor = ImColor(255.f / 255, 0.f, 0.f);
		float fl_VisibleColor[3] = { 0.f,255.f / 255,0.f };
		ImColor InvisibleColor = ImColor(0.f, 255.f / 255, 0.f);
		float fl_InvisibleColor[3] = { 255.f / 255,0.f,0.f };
		ImColor FovColor = ImColor(255.0f / 255, 0.f, 0.0f);
		float fl_FovColor[3] = { 255.0f / 255, 0.f, 0.0f };
		ImColor hboutline = ImColor(255.0f / 255, 255.0f, 255.0f);
		float fl_hboutline[3] = { 255.0f / 255, 255.0f, 255.0f };
		ImColor fullPlayerName = ImColor( 255.f / 255.f , 0.f , 0.f );
		float f_fullPlayerName[3] = {255.f / 255.f, 0.f , 0.f };
		ImColor PlayerName = ImColor(255.f / 255.f, 0.f, 0.f);
		float f_PlayerName[3] = { 255.f / 255.f, 0.f , 0.f };
		float freecamm = 100.0f;
		float headcirclewidth = 1.5f;
		float headcirclesize = 15.0f;
		int BoxType = 1;
		int LineType = 1;
		int FireType = 2;
		int reloadtype = 0;
		int tab_index = 0;
		float boxwidth = 1.5f;
		int AimKey = 7;
		bool alwaysmenucenter = true;
		bool loadconfigonstartup = true;
		bool supermelee = false;
		bool meleeteleport = false;
		float f_supermelee = 1700.f;
		float f_meleeteleport = 25000.f;
		bool aimlocbool = false;
		bool triggerbot = true;
		float skeletonsize = 1.5f;
		int aimlocationn = 0;
		int OpenKey = 0;
		int AimBotKey = 14;
		int UnloadKey = 0;
		int CloseGameKey = 25;
		float fakehealth = 900.0f;
		float Smoothing = 0.500f;
		float AimbotFOV = 300.0f;
		float max_distance = 10000.0f;
		int ScreenWidth = GetSystemMetrics(SM_CXSCREEN) / 2;
		int ScreenHeight = GetSystemMetrics(SM_CYSCREEN) / 2;
	};
#define cfg Configuration::Settings::Get()
}
bool GetAimKey()
{
	return GetAsyncKeyState(keys[cfg.AimKey]);
}
bool GetOpenKey()
{
	return GetAsyncKeyState(keys2[cfg.OpenKey]) & 1;
}
bool GetAimBotKey()
{
	return GetAsyncKeyState(keys3[cfg.AimBotKey]) & 1;
}
bool GetUnloadKey()
{
	return GetAsyncKeyState(keys4[cfg.UnloadKey]);
}
bool GetCloseGameKey()
{
	return GetAsyncKeyState(keys5[cfg.CloseGameKey]);
}
