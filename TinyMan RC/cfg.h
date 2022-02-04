#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include "singleton.h"
#include "imgui/imgui.h"

DWORD keys[] = { VK_LMENU, VK_MENU, VK_SHIFT, VK_RSHIFT, VK_CONTROL, VK_RCONTROL, VK_LBUTTON, VK_RBUTTON };
const char* keyItems[] = { "LAlt", "RAlt", "LShift", "RShift", "LControl", "RControl", "LMouse", "RMouse" };
DWORD keys2[] = { VK_HOME, VK_INSERT, VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10 };
const char* keyItems2[] = { "Home", "Insert", "UP", "DOWN", "RIGHT", "LEFT", "F1", "F2", "F3","F4","F5","F6","F7","F8","F9","F10" };

inline namespace Configuration
{
	class Settings : public Singleton<Settings>
	{
	public:

		const char* BoxTypes[2] = { "Full Box","Cornered Box" };
		const char* LineTypes[5] = { "Bottom To Enemy","Top To Enemy","Crosshair To Enemy", "Top left", "Top Right" };
		bool checkbox = false;
		bool togglebutton = true;
		bool fullnameesp = true;
		bool collision = false;
		bool ping = false;
		bool teamcollision = false;
		bool nameesp = false;
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
		bool healthpercenet = true;
		bool Immune = false;
		bool Nodieesp = true;
		bool noreloadaim = true;
		bool Nodieaim = true;
		bool noragdoll = false;
		bool deadesp = false;
		bool botsgodmode = false;
		bool b_MenuShow = true;
		bool thickskeleton = false;
		bool headcircle = false;
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
		bool healthoutline = false;
		bool menufps = true;
		//bool hideconsole = true;
		bool b_Visual = true;
		bool fakegodmode = false;
		bool burstrounds = false;
		bool fastland = false;
		bool b_EspBox = true;
		bool b_EspSkeleton = false;
		bool b_EspLine = true;
		bool nodownesp = true;
		bool nodownaim = true;
		bool unlimitedammo = false;
		bool b_EspDistance = true;
		bool b_EspHealth = false;
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
		//ImColor glowcolor = ImColor(255.f / 255, 0.f, 0.f);
		//float fl_glowcolor[3] = { 0.f,255.f / 255,0.f };  //

		ImColor VisibleColor = ImColor(255.f / 255, 0.f, 0.f);
		float fl_VisibleColor[3] = { 0.f,255.f / 255,0.f };  //

		ImColor InvisibleColor = ImColor(0.f, 255.f / 255, 0.f);
		float fl_InvisibleColor[3] = { 255.f / 255,0.f,0.f };  //

		ImColor FovColor = ImColor(255.f / 255, 0.f, 0.f);
		float fl_FovColor[3] = { 255.f / 255,0.f,0.f };  //

		float headcirclewidth = 1.5f;
		float headcirclesize = 15.0f;
		int BoxType = 1;
		int LineType = 1;
		int tab_index = 0;
		float boxwidth = 1.5f;
		int AimKey = 7;
		bool aimlocbool = false;
		bool triggerbot = true;
		float skeletonsize = 1.5f;
		int aimlocationn = 0;
		int OpenKey = 0;
		float fakehealth = 900.0f;
		float Smoothing = 0.500f;
		float AimbotFOV = 300.0f;
		float max_distance = 10000.0f;
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
