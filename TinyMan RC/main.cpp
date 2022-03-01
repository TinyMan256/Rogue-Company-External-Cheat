#define _CRT_SECURE_NO_WARNINGS
#include "function.h"
#include "overlay.h"
#include <mmsystem.h>
#include <d3dx9.h>
#include <tchar.h>
#include <urlmon.h>
#include <filesystem>
#pragma comment(lib, "urlmon.lib")
#include "other.h";
#include "ImGui/imgui_internal.h"
#include <sstream>
#include <iostream>
#include <windows.h>

auto characterbase()
{
	auto m_Charatermovement = read<uint64_t>(GameVars.local_player_pawn + GameOffset.CharacterMovement);
	return read<uint64_t>(m_Charatermovement + GameOffset.KSCharacterOwner);
}
auto weaponasset()
{
	auto ActiveWeapon = read<uint64_t>(GameVars.local_player_pawn + GameOffset.ActiveWeaponComponent);
	return read<uint64_t>(ActiveWeapon + GameOffset.WeaponAsset);
}
auto MeleeWeaponAsset()
{
	uint64_t CurrentQuickMeleeWeapon = read<uint64_t>(GameVars.local_player_pawn + GameOffset.CurrentQuickMeleeWeapon);
	return read<uint64_t>(CurrentQuickMeleeWeapon + GameOffset.MeleeWeaponAsset);
}
auto randomname()
{
	return RandomString(15) + ".exe";
}
//enums
	enum class EKSWeaponEquipType : uint8_t
	{
		Normal = 0,
		Special = 1,
		GameMode = 2,
		Gambit = 3,
		EKSWeaponEquipType_MAX = 4,
	};
	enum class EWeaponStateNew : uint8_t
	{
		Idle = 0,
		Buildup = 1,
		PreFire = 2,
		PostFire = 3,
		Cooldown = 4,
		PreReload = 5,
		PostReload = 6,
		ReloadCooldown = 7,
		Retrieve = 8,
		Holster = 9,
		Inactive = 10,
		NotValid = 11,
		EWeaponStateNew_MAX = 12,
	};
	enum class EDamageCategory : uint8_t
	{
		Default = 0,
		NonDamage = 1,
		Firearm = 2,
		Impact = 3,
		Explosion = 4,
		Melee = 5,
		ThrownMelee = 6,
		InstantDeath = 7,
		Environmental = 8,
		Bleed = 9,
		Fire = 10,
		Poison = 11,
		EDamageCategory_MAX = 12,
	};
enum class EReticleType : uint8_t
{
	None = 0,
	Pistol = 1,
	Rifle = 2,
	Shotgun = 3,
	Circle = 4,
	Gatling = 5,
	ChaosLauncher = 6,
	Stealth = 7,
	EReticleType_MAX = 8,
};
enum class EReloadType : uint8_t
{
	Clip = 0,
	SingleShot = 1,
	EReloadType_MAX = 2,
};
enum class EFireModeType : uint8_t
{
	Single = 0,
	Burst = 1,
	SemiAuto = 2,
	EFireModeType_MAX = 3
};
//end enums
BOOL terminateprocess(DWORD dwProcessId, UINT uExitCode)
{
	DWORD dwDesiredAccess = PROCESS_TERMINATE;
	BOOL  bInheritHandle = FALSE;
	HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
	if (hProcess == NULL)
		return FALSE;
	BOOL result = TerminateProcess(hProcess, uExitCode);
	CloseHandle(hProcess);
	return result;
}
void overlaytext(int x, int y, const char* str)
{
	ImFont a;
	string utf_8_1 = string(str);
	string utf_8_2 = string_To_UTF8(utf_8_1);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImColor(255, 255, 255, 255), "", "");
}
void HotkeyButton(USHORT& dst, const char* const label, const char* new_button_id, bool& get_key)
{
#define XorCStr(x) x

	string button;

	if (get_key)
		button += "...";
	else
	{
		switch (dst)
		{
		case 0:
			button += XorCStr("NONE");
			break;
		case VK_ESCAPE:
			button += XorCStr("ESC");
			break;
		case VK_TAB:
			button += XorCStr("TAB");
			break;
		case VK_CAPITAL:
			button += XorCStr("CAPS");
			break;
		case VK_SHIFT:
			button += XorCStr("SHIFT");
			break;
		case VK_CONTROL:
			button += XorCStr("CTRL");
			break;
		case VK_MENU:
			button += XorCStr("ALT");
			break;
		case VK_XBUTTON1:
			button += XorCStr("MB 1");
			break;
		case VK_XBUTTON2:
			button += XorCStr("MB 2");
			break;
		case VK_F1:
			button += XorCStr("F1");
			break;
		case VK_F2:
			button += XorCStr("F2");
			break;
		case VK_F3:
			button += XorCStr("F3");
			break;
		case VK_F4:
			button += XorCStr("F4");
			break;
		case VK_F5:
			button += XorCStr("F5");
			break;
		case VK_F6:
			button += XorCStr("F6");
			break;
		case VK_F7:
			button += XorCStr("F7");
			break;
		case VK_F8:
			button += XorCStr("F8");
			break;
		case VK_F9:
			button += XorCStr("F9");
			break;
		case VK_F10:
			button += XorCStr("F10");
			break;
		case VK_F11:
			button += XorCStr("F11");
			break;
		case VK_F12:
			button += XorCStr("F12");
			break;
		case VK_F13:
			button += XorCStr("F13");
			break;
		case VK_F14:
			button += XorCStr("F14");
			break;
		case VK_F15:
			button += XorCStr("F15");
			break;
		case VK_F16:
			button += XorCStr("F16");
			break;
		case VK_F17:
			button += XorCStr("F17");
			break;
		case VK_F18:
			button += XorCStr("F18");
			break;
		case VK_F19:
			button += XorCStr("F19");
			break;
		case VK_F20:
			button += XorCStr("F20");
			break;
		case VK_F21:
			button += XorCStr("F21");
			break;
		case VK_F22:
			button += XorCStr("F22");
			break;
		case VK_F23:
			button += XorCStr("F23");
			break;
		case VK_F24:
			button += XorCStr("F24");
			break;
		case VK_HOME:
			button += XorCStr("HOME");
			break;
		case VK_DELETE:
			button += XorCStr("DELETE");
			break;
		case VK_INSERT:
			button += XorCStr("INSERT");
			break;
		case VK_END:
			button += XorCStr("END");
			break;
		case VK_SPACE:
			button += XorCStr("SPACE");
			break;
		case VK_SCROLL:
			button += XorCStr("SCROLL");
			break;
		case VK_LBUTTON:
			button += XorCStr("LCLICK");
			break;
		case VK_RBUTTON:
			button += XorCStr("RCLICK");
			break;
		case VK_RETURN:
			button += XorCStr("ENTER");
			break;
		default:
			button += dst;
		}
	}
	button += new_button_id;

	if (ImGui::Button(button.c_str(), ImVec2(70, 0)))
		get_key = true;
	if (ImGui::IsItemHovered())
	{
		if (dst != 0xADAF)
			ImGui::SetTooltip(XorCStr("Double Click to Reset"));
		if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			get_key = false;
			dst = 0;
		}
	}

	ImGui::SameLine();
	ImGui::Text(label);

	if (get_key)
	{
		for (int i = 0x1; i <= 0x100; i += 0x1)
		{
			if (GetAsyncKeyState(i) & 0x8000)
			{
				get_key = false;
				dst = i;
				break;
			}
		}
	}

#undef XorCStr
}
void DrawSeparator(const USHORT& extend)
{
	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImGui::GetForegroundDrawList()->AddLine(
		pos,																				// p1
		{ pos.x + extend, pos.y },															// p2
		(ImColor)ImGui::GetStyle().Colors[ImGuiCol_Separator],								// color
		1.f);																				// thickness
}
void toggle(const char* label, bool* v)
{
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	float height = ImGui::GetFrameHeight();
	float width = height * 1.55f;
	float radius = height * 0.50f;
	ImGui::InvisibleButton(label, ImVec2(width, height));
	if (ImGui::IsItemClicked())
		*v = !*v;
	float t = *v ? 1.0f : 0.0f;
	ImGuiContext& g = *GImGui;
	float ANIM_SPEED = 0.08f;
	if (g.LastActiveId == g.CurrentWindow->GetID(label))// && g.LastActiveIdTimer < ANIM_SPEED)
	{
		float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
		//t = *v ? (t_anim) : (1.0f - t_anim);
	}
	ImU32 col_bg;
	if (ImGui::IsItemHovered())
		col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.78f, 0.78f, 0.78f, 1.0f), ImVec4(0.64f, 0.83f, 0.34f, 1.0f), t));
	else
		col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 1.0f), ImVec4(0.56f, 0.83f, 0.26f, 1.0f), t));
	draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
	draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
}
namespace OverlayWindow
{
	WNDCLASSEX WindowClass;
	HWND Hwnd;
	LPCSTR Name;
}
char const* tempfolder = getenv("TMPDIR"); //get temp folder
string filelocation()// get file location
{
	char filelocation[_MAX_PATH]; // defining the path
	GetModuleFileNameA(NULL, filelocation, _MAX_PATH); // getting the path
	return string(filelocation); //returning the path
}
string RandomString(size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	string str(length, 0);
	generate_n(str.begin(), length, randchar);
	return str;
}
void removecheat()
{
	mhyprot::unload(); // unload driver
	//delete files
	char filename[] = MHYPROT_SYSFILE_NAME;
	int result = remove(filename);
	exit(0);
}
#define TopWindowGame 11
#define TopWindowMvoe 22
int isTopwin()
{
	HWND hWnd = GetForegroundWindow();
	if (hWnd == GameVars.gameHWND)
		return TopWindowGame;
	if (hWnd == GameVars.gameHWND)
		return TopWindowMvoe;
	return 0;
}
// PROCESS CHECKER
bool find(const char* name)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	auto snapshot = LI_FN(CreateToolhelp32Snapshot).safe()(TH32CS_SNAPPROCESS, NULL);

	if (LI_FN(Process32First).safe()(snapshot, &entry) == TRUE)
	{
		while (LI_FN(Process32Next).safe()(snapshot, &entry) == TRUE)
		{
			if (!strcmp(entry.szExeFile, name))
			{

				return true;
			}
		}
	}

	LI_FN(CloseHandle).safe()(snapshot);
	return false;
}
int processdetection()
{
	vector<const char*> processes = {
		("RogueCompany.exe"),
	};

	for (auto process : processes)
	{
		if (find(process)){}
		else {
			MessageBox(0, "Open Rogue company then run the cheat", "Information", MB_TOPMOST | MB_OK | MB_ICONINFORMATION);
			removecheat();
		}
	}

	return false;
}

void windowdetection()
{
	HWND window;
	window = FindWindow(0, (("Rogue Company")));
		if (window)
		{
			MessageBox(0, "Rogue company window not found", "Information", MB_TOPMOST | MB_OK | MB_ICONINFORMATION);
		}
		else
		{
			MessageBox(0, "Rogue company window found", "Information", MB_TOPMOST | MB_OK | MB_ICONINFORMATION);
		}
}
namespace DirectX9Interface
{
	IDirect3D9Ex* Direct3D9 = NULL;
	IDirect3DDevice9Ex* pDevice = NULL;
	D3DPRESENT_PARAMETERS pParams = { NULL };
	MARGINS Margin = { -1 };
	MSG Message = { NULL };
}
typedef struct _EntityList
{
	uintptr_t actor_pawn;
	uintptr_t actor_mesh;
	uintptr_t actor_state;
	int actor_id;

}EntityList;
vector<EntityList> entityList;

//menu color
float Colour_red = 1.0;
float Colour_green = 1.0;
float Colour_blue = 1.0;
float Colour_random = 30.0;
float Colour_speed = 30.0;
void ColourChange() {
	static float Colour[3];
	static DWORD Tickcount = 0;
	static DWORD Tickcheck = 0;
	ImGui::ColourConvertRGBtoHSV(Colour_red, Colour_green, Colour_blue, Colour[0], Colour[1], Colour[2]);
	if (GetTickCount64() - Tickcount >= 1) {
		if (Tickcheck != Tickcount) {
			Colour[0] += 0.001f * Colour_speed;
			Tickcheck = Tickcount;
		}
		Tickcount = GetTickCount64();
	}
	if (Colour[0] < 0.0f) Colour[0] += 1.0f;
	ImGui::ColourConvertHSVtoRGB(Colour[0], Colour[1], Colour[2], Colour_red, Colour_green, Colour_blue);
}
auto CallAimbot()->VOID
{
	while (true)
	{
		auto EntityList_Copy = entityList;
		if (cfg.autoaim == true)
		{
			cfg.aimbot = cfg.b_Aimbot;
		}
		else if (cfg.autoaim == false)
		{
			cfg.aimbot = cfg.b_Aimbot && GetAimKey();
		}
		if (cfg.aimbot == true)
		{
			float target_dist = FLT_MAX;
			EntityList target_entity = {};
			for (int index = 0; index < EntityList_Copy.size(); ++index)
			{
				auto Entity = EntityList_Copy[index];
				if (!Entity.actor_mesh || !isVisible(Entity.actor_mesh)) continue;
				if (cfg.Nodieaim)
				{
					if (!Entity.actor_state || !Entity.actor_pawn)
					{
						continue;
					}
				}
				/*auto Health = read<float>(Entity.actor_pawn + GameOffset.offset_health);
				auto MaxHealth = read<float>(Entity.actor_pawn + GameOffset.offset_max_health);
				auto Percentage = Health * 100 / MaxHealth;
				if (cfg.Nodieaim) {
					if (Percentage == 0)
					{
						continue;
					}
				}*/
				//team check
				auto Playerstate = read<uintptr_t>(Entity.actor_pawn + GameOffset.offset_player_state);
				uint64_t LAKSTeamState = read<uint64_t>(GameVars.local_player_state + GameOffset.r_Team);
				uint64_t LTeamNum = read<uint64_t>(LAKSTeamState + GameOffset.r_TeamNum);
				uint64_t AKSTeamState = read<uint64_t>(Playerstate + GameOffset.r_Team);
				uint64_t TeamNum = read<uint64_t>(AKSTeamState + GameOffset.r_TeamNum);
				if (LTeamNum != TeamNum)
				{
					//enemy
				}
				else {
					//team
					if (cfg.friendsaim == false)
					{
						continue;
					}
				}
				// end team check

				// no knocked aim
				if (cfg.nodownaim == true)
				{
					auto knocked = read<uintptr_t>(Entity.actor_pawn + GameOffset.bDowned);
					if (knocked == true)
					{
						continue;
					}
					else {
						NULL;
					}
				}
				// end no knocked aim
				auto head_pos = GetBoneWithRotation(Entity.actor_mesh, 110);
				auto targethead = ProjectWorldToScreen(Vector3(head_pos.x, head_pos.y, head_pos.z));

				float x = targethead.x - GameVars.ScreenWidth / 2.0f;
				float y = targethead.y - GameVars.ScreenHeight / 2.0f;
				float crosshair_dist = sqrtf((x * x) + (y * y));

				if (crosshair_dist <= FLT_MAX && crosshair_dist <= target_dist)
				{
					// FOV
					if (crosshair_dist > cfg.AimbotFOV)
					{
						continue;
					}
					target_dist = crosshair_dist;
					target_entity = Entity;

				}
			}
			
			if (target_entity.actor_mesh != 0 || target_entity.actor_pawn != 0 || target_entity.actor_id != 0)
			{
				    //Head = 110
					 //EyeBall Left = 126
					//EyeBall Right = 155
				    //Neck1 = 108
					//Neck2 = 109
					//Shoulder Right = 106
					 //Shoulder Left = 69
				    //Ring Right = 50
				    //Pelvis = 1
					//Knee Right = 9
					//Knee Left = 21
					//Hip Right = 3 // R_Thigh
					//Hip Left = 15 // L_Thigh
					 //Hand Right = 75
					//Hand Left = 39
					//Elbow Right = 100
					//Elbow Left = 62
					//Foot Right = 5
					//Foot Left = 17
					
				//auto targethead = ProjectWorldToScreen(Vector3(head_pos.x, head_pos.y, head_pos.z + 15));
				auto head_pos = GetBoneWithRotation(target_entity.actor_mesh, 110);
				auto targethead = ProjectWorldToScreen(Vector3(head_pos.x, head_pos.y, head_pos.z));
				move_to(targethead.x, targethead.y);
				/*if (cfg.aimlocbool == true)
				{
					
				}*/
				/*if (cfg.aimlocbool == false)
				{
					
				}*/
				
			}
			else {
				continue;
			}
			auto head_pos = GetBoneWithRotation(target_entity.actor_mesh, 110);
			auto targethead = ProjectWorldToScreen(Vector3(head_pos.x, head_pos.y, head_pos.z));
			if (cfg.triggerbot == true && head_pos.x)
			{
				mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
				mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
				Sleep(5);
			}
			if (cfg.autoscope == true)
			{
			}
		}
		Sleep(15);
	}
}
auto GameCache()->VOID
{
	while (true)
	{
		
		vector<EntityList> tmpList;
		GameVars.u_world = read<DWORD_PTR>(GameVars.dwProcess_Base + GameOffset.offset_u_world);
		GameVars.game_instance = read<DWORD_PTR>(GameVars.u_world + GameOffset.offset_game_instance); 
		GameVars.local_player_array = read<DWORD_PTR>(GameVars.game_instance + GameOffset.offset_local_players_array);  
		GameVars.local_player = read<DWORD_PTR>(GameVars.local_player_array);
		GameVars.local_player_controller = read<DWORD_PTR>(GameVars.local_player + GameOffset.offset_player_controller); 
		GameVars.local_player_pawn = read<DWORD_PTR>(GameVars.local_player_controller + GameOffset.offset_apawn); 
    	GameVars.local_player_root = read<DWORD_PTR>(GameVars.local_player_pawn + GameOffset.offset_root_component); 
		GameVars.local_player_state = read<DWORD_PTR>(GameVars.local_player_pawn + GameOffset.offset_player_state); 
		GameVars.persistent_level = read<DWORD_PTR>(GameVars.u_world + GameOffset.offset_persistent_level);
		GameVars.actors = read<DWORD_PTR>(GameVars.persistent_level + GameOffset.offset_actor_array); 
		GameVars.actor_count = read<int>(GameVars.persistent_level + GameOffset.offset_actor_count);
        
		for (int index = 0; index < GameVars.actor_count; ++index)
		{

			auto actor_pawn = read<DWORD_PTR>(GameVars.actors + index * 0x8);
			if (actor_pawn == 0x00)
				continue;

			auto actor_id = read<int>(actor_pawn + GameOffset.offset_actor_id);
			auto actor_state = read<DWORD_PTR>(actor_pawn + GameOffset.offset_player_state);
			auto actor_mesh = read<DWORD_PTR>(actor_pawn + GameOffset.offset_actor_mesh); 	

			auto name = GetNameFromFName(actor_id);

			EntityList Entity{ };
			Entity.actor_pawn = actor_pawn;
			Entity.actor_id = actor_id;
			if (cfg.enemiesesp == true)
			{
				if (name == "MainCharacter_C" || name == "MainCharacter_Royale_C")
				{
					if (actor_pawn != NULL || actor_id != NULL || actor_state != NULL || actor_mesh != NULL)
					{
						EntityList Entity{ };
						Entity.actor_pawn = actor_pawn;
						Entity.actor_id = actor_id;
						Entity.actor_state = actor_state;
						Entity.actor_mesh = actor_mesh;
						tmpList.push_back(Entity);
					}
				}
			}
			if (cfg.botsesp == true)
			{
				if (name == "DefaultPVPBotCharacter_C" || name == "DefaultBotCharacter_C")
				{
					if (actor_pawn != NULL || actor_id != NULL || actor_state != NULL || actor_mesh != NULL)
					{
						EntityList Entity{ };
						Entity.actor_pawn = actor_pawn;
						Entity.actor_id = actor_id;
						Entity.actor_state = actor_state;
						Entity.actor_mesh = actor_mesh;
						tmpList.push_back(Entity);
					}
				}
			}
		}
		entityList = tmpList;
		//Sleep(100);
	}
}


auto RenderVisual()->VOID
{
	auto EntityList_Copy = entityList;

	for (int index = 0; index < EntityList_Copy.size(); ++index)
	{
		auto Entity = EntityList_Copy[index];


		if (cfg.selfesp == true)
		{
			Entity.actor_pawn == GameVars.local_player_pawn;
		}
		else if (cfg.selfesp == false)
		{
			if (Entity.actor_pawn == GameVars.local_player_pawn)
				continue;
		}
		if (cfg.Nodieesp) {
			if (!Entity.actor_mesh || !Entity.actor_state || !Entity.actor_pawn)
			{
				continue;
			}
		}
		/*auto Health = read<float>(Entity.actor_pawn + GameOffset.offset_health);
		auto MaxHealth = read<float>(Entity.actor_pawn + GameOffset.offset_max_health);
		auto Percentage = Health * 100 / MaxHealth;
		// no dead esp
		if (cfg.Nodieesp) {
			if (Percentage == 0)
			{
				continue;
			}
		}
		//end no dead esp*/
		// bunnyhop
		if (cfg.bunnyhop == true  && GetKeyState(VK_SPACE))
		{
			keybd_event(VK_SPACE, 0x39, NULL, NULL);
			Sleep(10);
			keybd_event(VK_SPACE, 0x39, KEYEVENTF_KEYUP, NULL);
		}
		//end bunnyhop

		// no knocked esp

		if (cfg.nodownesp == true)
		{
			auto knocked = read<uintptr_t>(Entity.actor_pawn + GameOffset.bDowned);
			if (knocked == true)
			{
				continue;
			}
			else {}
		}
		// end no knocked esp

			//team check
		auto Playerstate = read<uintptr_t>(Entity.actor_pawn + GameOffset.offset_player_state);
		uint64_t LAKSTeamState = read<uint64_t>(GameVars.local_player_state + GameOffset.r_Team);
		uint64_t LTeamNum = read<uint64_t>(LAKSTeamState + GameOffset.r_TeamNum);
		uint64_t AKSTeamState = read<uint64_t>(Playerstate + GameOffset.r_Team);
		uint64_t TeamNum = read<uint64_t>(AKSTeamState + GameOffset.r_TeamNum);
		if (LTeamNum != TeamNum)
		{
			//enemy
		}
		else {
			//team
			if (cfg.friendsesp == false)
			{
				continue;
			}
		}
		// end team check

		auto local_pos = read<Vector3>(GameVars.local_player_root + GameOffset.offset_relative_location);
		//right ring = 50
		//Pelvis = 1
		//FootRight = 5
		//KneeRight = 9
		//FootLeft = 17
		//KneeLeft = 21
		//HipRight = 3 // R_Thigh
		//HipLeft = 15 // L_Thigh
		//HandLeft = 39
		//ElbowLeft = 62
		//ShoulderLeft = 69
		//HandRight = 75
		//ElbowRight = 100
		//ShoulderRight = 106
		//Neck1 = 108
		//Neck2 = 109
		//Head = 110
		//EyeBallLeft = 126
		//EyeBallRight = 155
// positions
		auto head_pos = GetBoneWithRotation(Entity.actor_mesh, 110);
		auto rightring_pos = GetBoneWithRotation(Entity.actor_mesh, 50);
		auto Pelvis = GetBoneWithRotation(Entity.actor_mesh, 1);
		auto FootRight = GetBoneWithRotation(Entity.actor_mesh, 5);
		auto KneeRight = GetBoneWithRotation(Entity.actor_mesh, 9);
		auto FootLeft = GetBoneWithRotation(Entity.actor_mesh, 17);
		auto KneeLeft = GetBoneWithRotation(Entity.actor_mesh, 21);
		auto HipRight = GetBoneWithRotation(Entity.actor_mesh, 3);
		auto HipLeft = GetBoneWithRotation(Entity.actor_mesh, 15);
		auto HandLeft = GetBoneWithRotation(Entity.actor_mesh, 39);
		auto ElbowLeft = GetBoneWithRotation(Entity.actor_mesh, 62);
		auto ShoulderLeft = GetBoneWithRotation(Entity.actor_mesh, 69);
		auto HandRight = GetBoneWithRotation(Entity.actor_mesh, 75);
		auto ElbowRight = GetBoneWithRotation(Entity.actor_mesh, 100);
		auto ShoulderRight = GetBoneWithRotation(Entity.actor_mesh, 106);
		auto Neck1 = GetBoneWithRotation(Entity.actor_mesh, 108);
		auto Neck2 = GetBoneWithRotation(Entity.actor_mesh, 109);
		auto EyeBallLeft = GetBoneWithRotation(Entity.actor_mesh, 126);
		auto EyeBallRight = GetBoneWithRotation(Entity.actor_mesh, 155);
		auto bone_pos = GetBoneWithRotation(Entity.actor_mesh, 0);
		auto BottomBox = ProjectWorldToScreen(bone_pos);
		auto TopBox = ProjectWorldToScreen(Vector3(head_pos.x, head_pos.y, head_pos.z + 15));
		auto neckbox = ProjectWorldToScreen(Vector3(Neck1.x, Neck1.y, Neck1.z + 15));
		auto pelvisbox = ProjectWorldToScreen(Vector3(Pelvis.x, Pelvis.y, Pelvis.z + 15));
		auto entity_distance = local_pos.Distance(bone_pos);
		auto CornerHeight = abs(TopBox.y - BottomBox.y);
		auto CornerWidth = CornerHeight * 0.65;
		auto bVisible = isVisible(Entity.actor_mesh);
		auto ESP_Color = GetVisibleColor(bVisible);

		if (cfg.test == true)
		{

		}
		if (cfg.test2 == true)
		{
			
		}
		if (cfg.test3 == true)
		{
			
		}
		if (cfg.fastbulletsmelee == true)
		{
			write<float>(weaponasset() + GameOffset.PostFireTime, cfg.f_fastbulletsmelee);
			write<float>(weaponasset() + GameOffset.AltPostFireTime, cfg.f_fastbulletsmelee);
			write<float>(weaponasset() + GameOffset.PostFireForgivenessTime, cfg.f_fastbulletsmelee);
			write<float>(weaponasset() + GameOffset.InitialPostFireTime, cfg.f_fastbulletsmelee);
			write<float>(weaponasset() + GameOffset.FinalPostFireTime, cfg.f_fastbulletsmelee);
			write<float>(weaponasset() + GameOffset.PostFireChargeTime, cfg.f_fastbulletsmelee);
			write<float>(weaponasset() + GameOffset.PostFireDecayTime, cfg.f_fastbulletsmelee);
			write<float>(weaponasset() + GameOffset.PostFireDecayDelay, cfg.f_fastbulletsmelee);
		}
		if (cfg.clipsize == true)
		{
			write<int>(weaponasset() + GameOffset.ClipSize2, cfg.i_clipsize);
		}
		if (cfg.roundsperburst == true)
		{
			write<int>(weaponasset() + GameOffset.RoundsPerBurst, cfg.i_roundsperburst);
		}
		if (cfg.noreload == true)
		{
		}
		if (cfg.fastreload == true)
		{
			write<float>(weaponasset() + GameOffset.PreReloadTime, 0.1f);
		}
		if (cfg.halfreload == true)
		{
			write<float>(weaponasset() + GameOffset.PreReloadTime, 0.5f);
		}
		else if (cfg.fastreload == false && cfg.halfreload == false)
		{
			write<float>(weaponasset() + GameOffset.PreReloadTime, 1.0f);
		}
		if (cfg.shootingrangeinstatntkill == true)
		{
			write<float>(weaponasset() + GameOffset.HeadDamageAmount, cfg.f_shootingrangeinstatntkill);
			write<float>(weaponasset() + GameOffset.DamageAmount, cfg.f_shootingrangeinstatntkill);
			write<float>(weaponasset() + GameOffset.LimbDamageAmount, cfg.f_shootingrangeinstatntkill);
		}
		if (cfg.shootingrangewalkspeed == true)
		{
			write<float>(weaponasset() + GameOffset.WalkSpeedModifier, cfg.f_shootingrangewalkspeed);
		}
		if (cfg.trollnoreload == true)
		{
			write<bool>(weaponasset() + GameOffset.trollnoreload, false);
		}
		else if (cfg.trollnoreload == false)
		{
			write<bool>(weaponasset() + GameOffset.trollnoreload, true);
		}
		if (cfg.trollnofire == true)
		{
			write<bool>(weaponasset() + GameOffset.trollnofire, false);
		}
		else if (cfg.trollnofire == false)
		{
			write<bool>(weaponasset() + GameOffset.trollnofire, true);
		}
		if (cfg.aimdownsights == true)
		{
			write<bool>(weaponasset() + GameOffset.aimdownsights, true);
		}
		/*else if (cfg.aimdownsights == false)
		{
			write<bool>(weaponasset() + GameOffset.aimdownsights, false);
		}*/
		if (cfg.trollaimdownsights == true)
		{
			write<bool>(weaponasset() + GameOffset.aimdownsights, false);
		}
		/*else if (cfg.trollaimdownsights == false)
		{
			write<bool>(weaponasset() + GameOffset.aimdownsights, true);
		}*/
		if (cfg.trollaimovershoulder == true)
		{
			write<bool>(weaponasset() + GameOffset.aimovershoulder, false);
		}
		/*else if (cfg.trollaimovershoulder == false)
		{
			write<bool>(weaponasset() + GameOffset.aimovershoulder, true);
		}*/
		if (cfg.aimfov == true)
		{
			write<float>(weaponasset() + GameOffset.AimDownSightsFov, cfg.f_aimfov);
		}
		else if (cfg.aimfov == false)
		{
			write<float>(weaponasset() + GameOffset.AimDownSightsFov, 35.0f);
		}
		if (cfg.damagetype == true)
		{
			if (cfg.damagetypee == 0)
			{
				write<EDamageCategory>(weaponasset() + GameOffset.DamageCategory, EDamageCategory::Explosion);
			}
			if (cfg.damagetypee == 1)
			{
				write<EDamageCategory>(weaponasset() + GameOffset.DamageCategory, EDamageCategory::InstantDeath);
			}

		}
		if (cfg.weaponstate == true)
	{
		if (cfg.weaponstatee == 0)
		{
		write<EWeaponStateNew>(weaponasset() + GameOffset.DamageCategory, EWeaponStateNew::Buildup);
		}
	    if (cfg.weaponstatee == 1)
		{
		write<EWeaponStateNew>(weaponasset() + GameOffset.DamageCategory, EWeaponStateNew::PreFire);
		}
		if (cfg.weaponstatee == 2)
		{
			write<EWeaponStateNew>(weaponasset() + GameOffset.DamageCategory, EWeaponStateNew::PostFire);
		}
		if (cfg.weaponstatee == 3)
		{
			write<EWeaponStateNew>(weaponasset() + GameOffset.DamageCategory, EWeaponStateNew::Cooldown);
		}
		if (cfg.weaponstatee == 4)
		{
			write<EWeaponStateNew>(weaponasset() + GameOffset.DamageCategory, EWeaponStateNew::PreReload);
		}
		if (cfg.weaponstatee == 5)
		{
			write<EWeaponStateNew>(weaponasset() + GameOffset.DamageCategory, EWeaponStateNew::PostReload);
		}
		if (cfg.weaponstatee == 6)
		{
			write<EWeaponStateNew>(weaponasset() + GameOffset.DamageCategory, EWeaponStateNew::ReloadCooldown);
		}
		if (cfg.weaponstatee == 7)
		{
			write<EWeaponStateNew>(weaponasset() + GameOffset.DamageCategory, EWeaponStateNew::Retrieve);
		}
		if (cfg.weaponstatee == 8)
		{
			write<EWeaponStateNew>(weaponasset() + GameOffset.DamageCategory, EWeaponStateNew::Holster);
		}
		if (cfg.weaponstatee == 9)
		{
			write<EWeaponStateNew>(weaponasset() + GameOffset.DamageCategory, EWeaponStateNew::Inactive);
		}
	}
		if (cfg.reticletype == true)
		{
				/*if (cfg.reticletypee == 0)
			   {
					write<EReticleType>(weaponasset() + GameOffset.ReloadType, EReticleType::None); //Reload clip
			   }
			   if (cfg.reticletypee == 1)
			   {
				write<EReticleType>(weaponasset() + GameOffset.ReloadType, EReticleType::Pistol); //Reload single shot
			   }
			   if (cfg.reticletypee == 2)
			   {
				   write<EReticleType>(weaponasset() + GameOffset.ReloadType, EReticleType::Rifle); //Reload single shot
			   }
			   if (cfg.reticletypee == 3)
			   {
				   write<EReticleType>(weaponasset() + GameOffset.ReloadType, EReticleType::Shotgun); //Reload single shot
			   }
			   if (cfg.reticletypee == 4)
			   {
				   write<EReticleType>(weaponasset() + GameOffset.ReloadType, EReticleType::Circle); //Reload single shot
			   }
			   if (cfg.reticletypee == 5)
			   {
				   write<EReticleType>(weaponasset() + GameOffset.ReloadType, EReticleType::Gatling); //Reload single shot
			   }
			   if (cfg.reticletypee == 6)
			   {
				   write<EReticleType>(weaponasset() + GameOffset.ReloadType, EReticleType::ChaosLauncher); //Reload single shot
			   }
			   if (cfg.reticletypee == 7)
			   {
				   write<EReticleType>(weaponasset() + GameOffset.ReloadType, EReticleType::Stealth); //Reload single shot
			   }*/
		}
		if (cfg.EKSWeaponEquipTypebool == true)
		{
			if (cfg.EKSWeaponEquipType == 0)
			{
				write<EKSWeaponEquipType>(weaponasset() + GameOffset.WeaponEquipType, EKSWeaponEquipType::Normal);
			}
			if (cfg.EKSWeaponEquipType == 1)
			{
				write<EKSWeaponEquipType>(weaponasset() + GameOffset.WeaponEquipType, EKSWeaponEquipType::Special);
			}
			if (cfg.EKSWeaponEquipType == 2)
			{
				write<EKSWeaponEquipType>(weaponasset() + GameOffset.WeaponEquipType, EKSWeaponEquipType::GameMode);
			}
			if (cfg.EKSWeaponEquipType == 3)
			{
				write<EKSWeaponEquipType>(weaponasset() + GameOffset.WeaponEquipType, EKSWeaponEquipType::Gambit);
			}
		}
		if (cfg.reloadtypebool == true)
		{
			if (cfg.reloadtype == 0)
			{
				write<EReloadType>(weaponasset() + GameOffset.ReloadType, EReloadType::Clip); //Reload clip
			}
			if (cfg.reloadtype == 1)
			{
				write<EReloadType>(weaponasset() + GameOffset.ReloadType, EReloadType::SingleShot); //Reload single shot
			}
		}
		if (cfg.firetypebool == true)
		{
			if (cfg.FireType == 0)
			{
				write<EFireModeType>(weaponasset() + GameOffset.firemodetype, EFireModeType::Single); //Single bullet
			}
			if (cfg.FireType == 1)
			{
				write<EFireModeType>(weaponasset() + GameOffset.firemodetype, EFireModeType::Burst); //Burst bullets
			}
			if (cfg.FireType == 2)
			{
				write<EFireModeType>(weaponasset() + GameOffset.firemodetype, EFireModeType::SemiAuto); //Semi-auto bullets
			}
		}
		if (cfg.nospread == true)
		{
			write<float>(weaponasset() + GameOffset.NoSpread, 100.0f);
		}
		else if (cfg.nospread == false)
		{
			write<float>(weaponasset() + GameOffset.NoSpread, 0.9f);
		}
		if (cfg.ping == true)
		{
			auto ping = read<char>(Entity.actor_state + GameOffset.ping);
			CHAR buffer[64];
			sprintf(buffer, "%i", ping);
			DrawOutlinedText(Verdana, buffer, ImVec2(TopBox.x - 35, TopBox.y - 20), 14.0f, ImColor(255, 255, 255), true);
		}
		if (cfg.meleeteleport == true)
		{
			write<float>(MeleeWeaponAsset() + GameOffset.MaxLungeDistance, cfg.f_meleeteleport);
			if (cfg.meleeteleportlow == true)
			{
				write<float>(MeleeWeaponAsset() + GameOffset.MaxLungeDistance, 25000.0f);
			}
			if (cfg.meleeteleportmidium == true)
			{
				write<float>(MeleeWeaponAsset() + GameOffset.MaxLungeDistance, 50000.0f);
			}
			if (cfg.meleeteleporthigh == true)
			{
				write<float>(MeleeWeaponAsset() + GameOffset.MaxLungeDistance, 300000.0f);
			}
		}
		else if (cfg.meleeteleport == false)
		{
			write<float>(MeleeWeaponAsset() + GameOffset.MaxLungeDistance, 300.0f);
		}
		
		if (cfg.supermelee == true)
		{
		write<float>(MeleeWeaponAsset() + GameOffset.MeleeSphereRadius, cfg.f_supermelee);
		if (cfg.supermeleelow == true)
		{
		write<float>(MeleeWeaponAsset() + GameOffset.MeleeSphereRadius, 1700.f);
		}
		if (cfg.supermeleemedium == true)
		{
		write<float>(MeleeWeaponAsset() + GameOffset.MeleeSphereRadius, 2000.f);
		}
		if (cfg.supermeleehigh == true)
		{
		write<float>(MeleeWeaponAsset() + GameOffset.MeleeSphereRadius, 3000.f);
		}
		if (cfg.supermeleesuper == true)
		{
		write<float>(MeleeWeaponAsset() + GameOffset.MeleeSphereRadius, 6000.f);
		}
	}
		else if (cfg.supermelee == false)
		{
			write<float>(MeleeWeaponAsset() + GameOffset.MeleeSphereRadius, 0.f);
		}
			if (cfg.noragdoll == true)
		{
			//auto m_Charatermovement = read<uint64_t>(Entity.actor_pawn + GameOffset.CharacterMovement);
			//auto m_CharaterBase = read<uint64_t>(m_Charatermovement + GameOffset.KSCharacterOwner);
			write<bool>(characterbase() + GameOffset.bInRagdoll, true);
		}
		else if (cfg.noragdoll == false)
		{
			//auto m_Charatermovement = read<uint64_t>(Entity.actor_pawn + GameOffset.CharacterMovement);
			//auto m_CharaterBase = read<uint64_t>(m_Charatermovement + GameOffset.KSCharacterOwner);
			write<bool>(characterbase() + GameOffset.bInRagdoll, false);
		}
		if (cfg.enableknocked)
		{
			auto m_Charatermovement = read<uint64_t>(GameVars.local_player_pawn + GameOffset.CharacterMovement);
			auto m_CharaterBase = read<uint64_t>(m_Charatermovement + GameOffset.KSCharacterOwner);
			write<bool>(m_CharaterBase + GameOffset.bDowned, true);
		}
		if (cfg.disableknocked == true)
		{
			auto m_Charatermovement = read<uint64_t>(GameVars.local_player_pawn + GameOffset.CharacterMovement); //CharacterMovement
			auto m_CharaterBase = read<uint64_t>(m_Charatermovement + GameOffset.KSCharacterOwner);//KSCharacterOwner
			write<bool>(m_CharaterBase + GameOffset.bDowned, false);
		}
		
		if (cfg.botsgodmode == true)
		{
			auto m_Charatermovement = read<uint64_t>(Entity.actor_pawn + GameOffset.CharacterMovement); //CharacterMovement
			auto m_CharaterBase = read<uint64_t>(m_Charatermovement + GameOffset.KSCharacterOwner);//KSCharacterOwner
			write<float>(m_CharaterBase + GameOffset.offset_health, 999.0f);// AKSCharacterFoundation -> Health
		}
		if (cfg.unlimitedammo == true)
		{
			write<bool>(weaponasset() + GameOffset.bUnlimitedAmmo, true);
		}
		else if (cfg.unlimitedammo == false)
		{
			write<bool>(weaponasset() + GameOffset.bUnlimitedAmmo, false);
		}
		if (cfg.bdowned == true)
		{
			auto m_Charatermovement = read<uint64_t>(Entity.actor_pawn + GameOffset.CharacterMovement); //CharacterMovement
			auto m_CharaterBase = read<uint64_t>(m_Charatermovement + GameOffset.KSCharacterOwner);//KSCharacterOwner
			write<bool>(m_CharaterBase + GameOffset.bDowned, true);//bdowned
		}
		
		/*else if (cfg.bdowned == false)
		{
			auto m_Charatermovement = read<uint64_t>(Entity.actor_pawn + GameOffset.CharacterMovement); //CharacterMovement
			auto m_CharaterBase = read<uint64_t>(m_Charatermovement + GameOffset.KSCharacterOwner);//KSCharacterOwner
			write<bool>(m_CharaterBase + GameOffset.bDowned, false);//bdowned
		}*/
		if (cfg.norecoil == true)
		{
			write<bool>(GameVars.local_player_controller + GameOffset.offset_bKickbackEnabled, false);
		}
		else if (cfg.norecoil == false)
		{
			write<bool>(GameVars.local_player_controller + GameOffset.offset_bKickbackEnabled, true);
		}
		if (cfg.Immune == true)
		{
			cfg.glow = true;
			auto m_Charatermovement = read<uint64_t>(Entity.actor_pawn + GameOffset.CharacterMovement); //CharacterMovement
			auto m_CharaterBase = read<uint64_t>(m_Charatermovement + GameOffset.KSCharacterOwner);//KSCharacterOwner
			write<bool>(m_CharaterBase + GameOffset.bIsSpawnImmune, true);//bIsSpawnImmune
		}
		else if (cfg.Immune == false)
		{
			cfg.glow == false;
			auto m_Charatermovement = read<uint64_t>(Entity.actor_pawn + GameOffset.CharacterMovement); //CharacterMovement
			auto m_CharaterBase = read<uint64_t>(m_Charatermovement + GameOffset.KSCharacterOwner);//KSCharacterOwner
			write<bool>(m_CharaterBase + GameOffset.bIsSpawnImmune, false);//bIsSpawnImmune
		}
		if (cfg.teamcollision == true)
		{
			auto m_Charatermovement = read<uint64_t>(Entity.actor_pawn + GameOffset.CharacterMovement); //CharacterMovement
			auto m_CharaterBase = read<uint64_t>(m_Charatermovement + GameOffset.KSCharacterOwner);//KSCharacterOwner
			write<bool>(m_CharaterBase + GameOffset.bIgnoreCollisionWithTeammates, false);//bIgnoreCollisionWithTeammates
		}
		else if (cfg.teamcollision == false)
		{
			auto m_Charatermovement = read<uint64_t>(Entity.actor_pawn + GameOffset.CharacterMovement); //CharacterMovement
			auto m_CharaterBase = read<uint64_t>(m_Charatermovement + GameOffset.KSCharacterOwner);//KSCharacterOwner
			write<bool>(m_CharaterBase + GameOffset.bIgnoreCollisionWithTeammates, true);//bIgnoreCollisionWithTeammates
		}
		if (cfg.fakegodmode == true)
		{
			auto m_Charatermovement = read<uint64_t>(Entity.actor_pawn + GameOffset.CharacterMovement); //CharacterMovement
			auto m_CharaterBase = read<uint64_t>(m_Charatermovement + GameOffset.KSCharacterOwner);//KSCharacterOwner
			write<float>(m_CharaterBase + GameOffset.CurrentOverheal, 800.0f); //CurrentOverheal
		}
		else if (cfg.fakegodmode == false)
		{
			auto m_Charatermovement = read<uint64_t>(Entity.actor_pawn + GameOffset.CharacterMovement); //CharacterMovement
			auto m_CharaterBase = read<uint64_t>(m_Charatermovement + GameOffset.KSCharacterOwner);//KSCharacterOwner
			write<float>(m_CharaterBase + GameOffset.CurrentOverheal, 0.0f); //CurrentOverheal
		}
		if (cfg.b_Aimbot)
		{
			if (cfg.b_AimbotFOV)
			{
				DrawCircle(GameVars.ScreenWidth / 2, GameVars.ScreenHeight / 2, cfg.AimbotFOV, cfg.FovColor, 0);
			}
		}
		if (cfg.allvisuals)
		{
			if (entity_distance < cfg.max_distance)
			{
				if (cfg.b_EspBox)
				{
					if (cfg.BoxType == 0)
					{
						DrawBox(TopBox.x - (CornerWidth / 2), TopBox.y, CornerWidth, CornerHeight, ESP_Color, cfg.boxwidth);
					}
					else if (cfg.BoxType == 1)
					{
						DrawCorneredBox(TopBox.x - (CornerWidth / 2), TopBox.y, CornerWidth, CornerHeight, ESP_Color, cfg.boxwidth);
					}
				}
				if (cfg.glow == true)
				{
					auto m_Charatermovement = read<uint64_t>(Entity.actor_pawn + GameOffset.CharacterMovement);
					auto m_CharaterBase = read<uint64_t>(m_Charatermovement + GameOffset.KSCharacterOwner);
					write<bool>(m_CharaterBase + GameOffset.bRevealed, true);
				}
				else if (cfg.glow == false)
				{
					auto m_Charatermovement = read<uint64_t>(Entity.actor_pawn + GameOffset.CharacterMovement);
					auto m_CharaterBase = read<uint64_t>(m_Charatermovement + GameOffset.KSCharacterOwner);
					write<bool>(m_CharaterBase + GameOffset.bRevealed, false);
				}
				if (cfg.b_EspLine)
				{

					if (cfg.LineType == 0)
					{
						DrawLine(ImVec2(static_cast<float>(GameVars.ScreenWidth / 2), static_cast<float>(GameVars.ScreenHeight)), ImVec2(BottomBox.x, BottomBox.y), ESP_Color, 1.5f); //LINE FROM BOTTOM SCREEN
					}
					if (cfg.LineType == 1)
					{
						DrawLine(ImVec2(static_cast<float>(GameVars.ScreenWidth / 2), 0.f), ImVec2(TopBox.x, TopBox.y), ESP_Color, 1.5f); //LINE FROM TOP SCREEN
					}
					if (cfg.LineType == 2)
					{
						DrawLine(ImVec2(static_cast<float>(GameVars.ScreenWidth / 2), static_cast<float>(GameVars.ScreenHeight / 2)), ImVec2(BottomBox.x, BottomBox.y), ESP_Color, 1.5f); //LINE FROM CROSSHAIR
					}
					if (cfg.LineType == 3)
					{
						DrawLine(ImVec2(static_cast<float>(0.f), 0.f), ImVec2(TopBox.x, TopBox.y), ESP_Color, 1.5f); //LINE FROM TOP SCREEN
					}
					if (cfg.LineType == 4)
					{
						DrawLine(ImVec2(static_cast<float>(GameVars.ScreenWidth / 1), 0.f), ImVec2(TopBox.x, TopBox.y), ESP_Color, 1.5f); //LINE FROM TOP SCREEN
					}

				}
				if (cfg.b_EspDistance)
				{
					char dist[64];
					sprintf_s(dist, "D:%.fm", entity_distance);
					DrawOutlinedText(Verdana, dist, ImVec2(BottomBox.x, BottomBox.y), 14.0f, ImColor(255, 255, 255), true);
				}
				if (cfg.deadesp)
				{
					if (!Entity.actor_state || !Entity.actor_pawn)
					{
						char dead[64];
						sprintf_s(dead, "Dead");
						DrawOutlinedText(Verdana, dead, ImVec2(TopBox.x, BottomBox.y + 20), 14.0f, ImColor(255, 0, 0, 255), true);
					}
				}
				/*if (cfg.healthbar)
				{
					auto Health = read<float>(Entity.actor_pawn + GameOffset.offset_health);
					auto MaxHealth = read<float>(Entity.actor_pawn + GameOffset.offset_max_health);
					float Percentage = Health * 100 / MaxHealth;
					float width = CornerWidth / 10;
					if (width < 2.f) width = 2.;
					if (width > 3) width = 3.;
					HealthBar(TopBox.x - (CornerWidth / 2) - 8, TopBox.y, width, BottomBox.y - TopBox.y, Percentage);
				}
				if (cfg.healthpercenet)
				{
					float Health = read<float>(Entity.actor_pawn + GameOffset.offset_health);
					float MaxHealth = read<float>(Entity.actor_pawn + GameOffset.offset_max_health);
					float Percentage = Health * 100 / MaxHealth;
					if(Percentage <= 25)
					{
						char healthpercenet[64];
						sprintf(healthpercenet, "H:%.f%%", Percentage);
						DrawOutlinedText(Verdana, healthpercenet, ImVec2(TopBox.x, TopBox.y), 14.0f, ImColor(255, 38, 0), true);
					}
					if (Percentage <= 50 && Percentage >= 25)
					{
						char healthpercenet[64];
						sprintf(healthpercenet, "H:%.f%%", Percentage);
						DrawOutlinedText(Verdana, healthpercenet, ImVec2(TopBox.x, TopBox.y), 14.0f, ImColor(255, 77, 0), true);
					}
					if (Percentage <= 75 && Percentage >= 50)
					{
						char healthpercenet[64];
						sprintf(healthpercenet, "H:%.f%%", Percentage);
						DrawOutlinedText(Verdana, healthpercenet, ImVec2(TopBox.x, TopBox.y), 14.0f, ImColor(255, 200, 0), true);
					}
					if (Percentage <= 100 && Percentage >= 75)
					{
						char healthpercenet[64];
						sprintf(healthpercenet, "H:%.f%%", Percentage);
						DrawOutlinedText(Verdana, healthpercenet, ImVec2(TopBox.x, TopBox.y), 14.0f, ImColor(0, 255, 0, 255), true);
					}
				}*/
				if (cfg.crosshair)
				{
					
				}
				if (cfg.headcircle)
				{
					Vector3 vHeadOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 110));
					DrawCircle(ImVec2(vHeadOut.x, vHeadOut.y), cfg.headcirclesize, ESP_Color, cfg.headcirclewidth);
				}
				if (cfg.fullnameesp == true)
				{
					auto PlayerName = read<FString>(Entity.actor_state + GameOffset.offset_player_name);
					DrawOutlinedText(Verdana, PlayerName.ToString(), ImVec2(TopBox.x, TopBox.y - 20), 14.0f, cfg.fullPlayerName, true);
				}
				if (cfg.nameesp == true)
				{
					auto Playerstate = read<uintptr_t>(Entity.actor_pawn + GameOffset.offset_player_state);
					auto FPlayerName = read<FString>(read<uint64_t>(Playerstate + GameOffset.offset_player_name));
					CHAR buffer[64];
					sprintf_s(buffer, "%s", FPlayerName);
					DrawOutlinedText(Verdana, buffer, ImVec2(pelvisbox.x, pelvisbox.y), 15.0f, cfg.PlayerName, true);
				}
				if (cfg.thickskeleton)
				{
					Vector3 vHeadOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 110));
					Vector3 vNeckOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 108));
					Vector3 vSpine1Out = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 32));
					Vector3 vSpine2Out = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 33));
					Vector3 vSpine3Out = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 34));
					Vector3 vPelvisOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 1));
					Vector3 vRightThighOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 3));
					Vector3 vLeftThighOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 15));
					Vector3 vRightCalfOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 4));
					Vector3 vLeftCalfOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 16));
					Vector3 vRightFootOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 5));
					Vector3 vLeftFootOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 17));
					Vector3 vUpperArmRightOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 73));
					Vector3 vUpperArmLeftOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 37));
					Vector3 vLowerArmRightOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 74));
					Vector3 vLowerArmLeftOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 38));
					Vector3 vHandRightOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 75));
					Vector3 vHandLeftOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 39));
					Vector3 vFootOutOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 0));
					DrawLine(ImVec2(vHeadOut.x, vHeadOut.y), ImVec2(vNeckOut.x, vNeckOut.y), ESP_Color, 3.5f);
					DrawLine(ImVec2(vNeckOut.x, vNeckOut.y), ImVec2(vSpine1Out.x, vSpine1Out.y), ESP_Color, 3.5f);
					DrawLine(ImVec2(vSpine1Out.x, vSpine1Out.y), ImVec2(vSpine2Out.x, vSpine2Out.y), ESP_Color, 3.5f);
					DrawLine(ImVec2(vSpine2Out.x, vSpine2Out.y), ImVec2(vSpine3Out.x, vSpine3Out.y), ESP_Color, 3.5f);
					DrawLine(ImVec2(vSpine1Out.x, vSpine1Out.y), ImVec2(vUpperArmRightOut.x, vUpperArmRightOut.y), ESP_Color, 3.5f);
					DrawLine(ImVec2(vSpine1Out.x, vSpine1Out.y), ImVec2(vUpperArmLeftOut.x, vUpperArmLeftOut.y), ESP_Color, 3.5f);
					DrawLine(ImVec2(vSpine1Out.x, vSpine1Out.y), ImVec2(vPelvisOut.x, vPelvisOut.y), ESP_Color, 3.5f);
					DrawLine(ImVec2(vPelvisOut.x, vPelvisOut.y), ImVec2(vRightThighOut.x, vRightThighOut.y), ESP_Color, 3.5f);
					DrawLine(ImVec2(vPelvisOut.x, vPelvisOut.y), ImVec2(vLeftThighOut.x, vLeftThighOut.y), ESP_Color, 3.5f);
					DrawLine(ImVec2(vRightThighOut.x, vRightThighOut.y), ImVec2(vRightCalfOut.x, vRightCalfOut.y), ESP_Color, 3.5f);
					DrawLine(ImVec2(vLeftThighOut.x, vLeftThighOut.y), ImVec2(vLeftCalfOut.x, vLeftCalfOut.y), ESP_Color, 3.5f);
					DrawLine(ImVec2(vRightCalfOut.x, vRightCalfOut.y), ImVec2(vRightFootOut.x, vRightFootOut.y), ESP_Color, 3.5f);
					DrawLine(ImVec2(vLeftCalfOut.x, vLeftCalfOut.y), ImVec2(vLeftFootOut.x, vLeftFootOut.y), ESP_Color, 3.5f);
					DrawLine(ImVec2(vUpperArmRightOut.x, vUpperArmRightOut.y), ImVec2(vLowerArmRightOut.x, vLowerArmRightOut.y), ESP_Color, 3.5f);
					DrawLine(ImVec2(vUpperArmLeftOut.x, vUpperArmLeftOut.y), ImVec2(vLowerArmLeftOut.x, vLowerArmLeftOut.y), ESP_Color, 3.5f);
					DrawLine(ImVec2(vLowerArmLeftOut.x, vLowerArmLeftOut.y), ImVec2(vHandLeftOut.x, vHandLeftOut.y), ESP_Color, 3.5f);
					DrawLine(ImVec2(vLowerArmRightOut.x, vLowerArmRightOut.y), ImVec2(vHandRightOut.x, vHandRightOut.y), ESP_Color, 3.5f);
				}
				if (cfg.b_EspSkeleton)
				{
					Vector3 vHeadOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 110));
					Vector3 vNeckOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 108));
					Vector3 vSpine1Out = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 32));
					Vector3 vSpine2Out = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 33));
					Vector3 vSpine3Out = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 34));
					Vector3 vPelvisOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 1));
					Vector3 vRightThighOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 3));
					Vector3 vLeftThighOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 15));
					Vector3 vRightCalfOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 4));
					Vector3 vLeftCalfOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 16));
					Vector3 vRightFootOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 5));
					Vector3 vLeftFootOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 17));
					Vector3 vUpperArmRightOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 73));
					Vector3 vUpperArmLeftOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 37));
					Vector3 vLowerArmRightOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 74));
					Vector3 vLowerArmLeftOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 38));
					Vector3 vHandRightOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 75));
					Vector3 vHandLeftOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 39));
					Vector3 vFootOutOut = ProjectWorldToScreen(GetBoneWithRotation(Entity.actor_mesh, 0));
					DrawLine(ImVec2(vHeadOut.x, vHeadOut.y), ImVec2(vNeckOut.x, vNeckOut.y), ESP_Color, cfg.skeletonsize);
					DrawLine(ImVec2(vNeckOut.x, vNeckOut.y), ImVec2(vSpine1Out.x, vSpine1Out.y), ESP_Color, cfg.skeletonsize);
					DrawLine(ImVec2(vSpine1Out.x, vSpine1Out.y), ImVec2(vSpine2Out.x, vSpine2Out.y), ESP_Color, cfg.skeletonsize);
					DrawLine(ImVec2(vSpine2Out.x, vSpine2Out.y), ImVec2(vSpine3Out.x, vSpine3Out.y), ESP_Color, cfg.skeletonsize);
					DrawLine(ImVec2(vSpine1Out.x, vSpine1Out.y), ImVec2(vUpperArmRightOut.x, vUpperArmRightOut.y), ESP_Color, cfg.skeletonsize);
					DrawLine(ImVec2(vSpine1Out.x, vSpine1Out.y), ImVec2(vUpperArmLeftOut.x, vUpperArmLeftOut.y), ESP_Color, cfg.skeletonsize);
					DrawLine(ImVec2(vSpine1Out.x, vSpine1Out.y), ImVec2(vPelvisOut.x, vPelvisOut.y), ESP_Color, cfg.skeletonsize);
					DrawLine(ImVec2(vPelvisOut.x, vPelvisOut.y), ImVec2(vRightThighOut.x, vRightThighOut.y), ESP_Color, cfg.skeletonsize);
					DrawLine(ImVec2(vPelvisOut.x, vPelvisOut.y), ImVec2(vLeftThighOut.x, vLeftThighOut.y), ESP_Color, cfg.skeletonsize);
					DrawLine(ImVec2(vRightThighOut.x, vRightThighOut.y), ImVec2(vRightCalfOut.x, vRightCalfOut.y), ESP_Color, cfg.skeletonsize);
					DrawLine(ImVec2(vLeftThighOut.x, vLeftThighOut.y), ImVec2(vLeftCalfOut.x, vLeftCalfOut.y), ESP_Color, cfg.skeletonsize);
					DrawLine(ImVec2(vRightCalfOut.x, vRightCalfOut.y), ImVec2(vRightFootOut.x, vRightFootOut.y), ESP_Color, cfg.skeletonsize);
					DrawLine(ImVec2(vLeftCalfOut.x, vLeftCalfOut.y), ImVec2(vLeftFootOut.x, vLeftFootOut.y), ESP_Color, cfg.skeletonsize);
					DrawLine(ImVec2(vUpperArmRightOut.x, vUpperArmRightOut.y), ImVec2(vLowerArmRightOut.x, vLowerArmRightOut.y), ESP_Color, cfg.skeletonsize);
					DrawLine(ImVec2(vUpperArmLeftOut.x, vUpperArmLeftOut.y), ImVec2(vLowerArmLeftOut.x, vLowerArmLeftOut.y), ESP_Color, cfg.skeletonsize);
					DrawLine(ImVec2(vLowerArmLeftOut.x, vLowerArmLeftOut.y), ImVec2(vHandLeftOut.x, vHandLeftOut.y), ESP_Color, cfg.skeletonsize);
					DrawLine(ImVec2(vLowerArmRightOut.x, vLowerArmRightOut.y), ImVec2(vHandRightOut.x, vHandRightOut.y), ESP_Color, cfg.skeletonsize);
				}

			}
		}
	}
}
//get cheat folder location
string getCurrentDirectoryOnWindows2()
{
	const unsigned long maxDir = 260;
	char currentDir[maxDir];
	GetCurrentDirectory(maxDir, currentDir);
	return string(currentDir);
}
// end
void InputHandler() {
	for (int i = 0; i < 5; i++) ImGui::GetIO().MouseDown[i] = false;
	int button = -1;
	if (GetAsyncKeyState(VK_LBUTTON)) button = 0;
	if (button != -1) ImGui::GetIO().MouseDown[button] = true;
}

void Render()
{
	if (cfg.alwaysmenucenter)
	{
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
	}

	if (cfg.lowendpc == true)
	{
		cfg.b_EspBox = false;
		cfg.b_EspDistance = false;
		cfg.healthbar = false;
		cfg.b_EspLine = false;
		cfg.b_EspSkeleton = false;
		cfg.deadesp = false;
		cfg.fullnameesp = false;
		cfg.lootesp = false;
		cfg.nameesp = false;
		cfg.glow = true;
		cfg.triggerbot = false;
		cfg.healthpercenet = false;
	}
	bool openmenu = GetOpenKey();
	bool aimbothotkey = GetAimBotKey();
	bool Unloadkey = GetUnloadKey();
	bool closegamekey = GetCloseGameKey();
	
	if (openmenu)
	{
		cfg.b_MenuShow = !cfg.b_MenuShow;
	}
	if (closegamekey)
	{
		terminateprocess(GameVars.dwProcessId, 0);
	}
	if (Unloadkey)
	{
		removecheat();
	}
	if (cfg.randomcheatnameloop == true)
	{
	}
	GameVars.dwProcessId = GetProcessId(GameVars.dwProcessName);
	if (!GameVars.dwProcessId)
	{
		MessageBox(0, "RC Cheat was completely unloaded", "Information", MB_OK | MB_TOPMOST | MB_ICONINFORMATION);
		removecheat();
	}
	if (aimbothotkey)
	{
		cfg.b_Aimbot = !cfg.b_Aimbot;
	}
	if (cfg.showcursor == true)
	{
		ImGui::GetIO().MouseDrawCursor = cfg.b_MenuShow;
	}
	
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	RenderVisual();
	
	if (cfg.b_MenuShow)
	{
		cfg.showcursor == true;
		InputHandler();
		ImGuiStyle* style = &ImGui::GetStyle();
		ImVec4* colors = style->Colors;
		style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
		ImGui::PushFont(DefaultFont);
		if (cfg.menufps == true)
		{
			ImGui::Text("%.1f fps", ImGui::GetIO().Framerate);
		}
		ImGui::SameLine();
		TabButton("Visual", &cfg.tab_index, 0, true);
		ImGui::SameLine();
		TabButton("Aimbot", &cfg.tab_index, 1, false);
		ImGui::SameLine();
		TabButton("Rage", &cfg.tab_index, 2, false);
		ImGui::SameLine();
		TabButton("Troll", &cfg.tab_index, 3, false);
		ImGui::SameLine();
		TabButton("Settings", &cfg.tab_index, 4, false);
		ImGui::SameLine();
		TabButton("Credits", &cfg.tab_index, 5, false);
		if (cfg.tab_index == 0)
		{
			/*toggle("", &cfg.test); ImGui::SameLine(); ImGui::Text("test 1");
			ImGui::SameLine();
			toggle("", &cfg.test2); ImGui::SameLine(); ImGui::Text("test 2");
			ImGui::SameLine();
			toggle("", &cfg.test3); ImGui::SameLine(); ImGui::Text("test 3");*/
			ImGui::Checkbox("Enable all visual options", &cfg.allvisuals);
			ImGui::Checkbox("low end pc mode", &cfg.lowendpc);
			ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			ImGui::Checkbox("ESP Line", &cfg.b_EspLine);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(180);
			ImGui::Combo("ESP Line Type", &cfg.LineType, cfg.LineTypes, 5);
				ImGui::Checkbox("ESP Box", &cfg.b_EspBox);
				ImGui::SameLine();
				ImGui::SetNextItemWidth(180);
				ImGui::Combo("ESP Box Type", &cfg.BoxType, cfg.BoxTypes, 2);
				ImGui::SameLine();
				ImGui::SetNextItemWidth(180);
				ImGui::SliderFloat("Box Width", &cfg.boxwidth, 0.5f, 20.0f);
				ImGui::Checkbox("GLOW", &cfg.glow);
			//	ImGui::Checkbox("Crosshair", &cfg.crosshair);
				ImGui::SameLine();
				ImGui::Checkbox("players ping", &cfg.ping);
				ImGui::Checkbox("Full Name ESP", &cfg.fullnameesp);
				ImGui::SameLine();
				ImGui::SetNextItemWidth(150);
				if (ImGui::ColorEdit3("Player Name Color", cfg.f_fullPlayerName, ImGuiColorEditFlags_NoDragDrop))
				{
					cfg.fullPlayerName = ImColor(cfg.f_fullPlayerName[0], cfg.f_fullPlayerName[1], cfg.f_fullPlayerName[2]);
				}
				ImGui::Checkbox("First Letter Name ESP", &cfg.nameesp);
				ImGui::SameLine();
				ImGui::SetNextItemWidth(150);
				if (ImGui::ColorEdit3("First letter Color", cfg.f_PlayerName, ImGuiColorEditFlags_NoDragDrop))
				{
					cfg.PlayerName = ImColor(cfg.f_PlayerName[0], cfg.f_PlayerName[1], cfg.f_PlayerName[2]);
				}
				ImGui::Checkbox("Head Circle", &cfg.headcircle);
				ImGui::SameLine();
				ImGui::SetNextItemWidth(180);
				ImGui::SliderFloat("Head Circle size", &cfg.headcirclesize, 0.5f, 100.0f);
				ImGui::SameLine();
				ImGui::SetNextItemWidth(180);
				ImGui::SliderFloat("Head Circle width", &cfg.headcirclewidth, 0.5f, 25.0f);
				ImGui::Checkbox("Dead ESP", &cfg.deadesp);
				ImGui::SameLine();
				ImGui::Checkbox("Self ESP", &cfg.selfesp);
				ImGui::SameLine();
				ImGui::Checkbox("Remove Dead Bodies ESP", &cfg.Nodieesp);
				ImGui::SameLine();
				ImGui::Checkbox("Remove Knocked enemies esp", &cfg.nodownesp);
				ImGui::Checkbox("Friends esp", &cfg.friendsesp);
				ImGui::SameLine();
				ImGui::Checkbox("Bots esp", &cfg.botsesp);
				ImGui::SameLine();
				ImGui::Checkbox("Enemies esp", &cfg.enemiesesp);
				//ImGui::Checkbox("Loot esp", &cfg.lootesp);
				//ImGui::Checkbox("GLOW Color", &cfg.glowcolor);
				/*if (ImGui::ColorEdit3("Glow Color", cfg.fl_glowcolor, ImGuiColorEditFlags_NoDragDrop))
				{
					cfg.glowcolor = ImColor(cfg.fl_glowcolor[0], cfg.fl_glowcolor[1], cfg.fl_glowcolor[2]);
				}*/
				
				ImGui::Checkbox("ESP Skeleton", &cfg.b_EspSkeleton);
				ImGui::SameLine();
				ImGui::Checkbox("Thick Skeleton", &cfg.thickskeleton);
				ImGui::SameLine();
				ImGui::SetNextItemWidth(250.f);
				ImGui::SliderFloat("Skeleton size", &cfg.skeletonsize, 0.5f, 20.0f);
				ImGui::Checkbox("ESP HealthBar", &cfg.healthbar);
				ImGui::SameLine();
				ImGui::Checkbox("Percentage Of Health", &cfg.healthpercenet);
				ImGui::SameLine();
				ImGui::Checkbox("ESP HealthBar outline", &cfg.healthbaroutline);
				ImGui::SameLine();
				ImGui::SetNextItemWidth(180);
				if (ImGui::ColorEdit3("Healthbar outline color", cfg.fl_hboutline, ImGuiColorEditFlags_NoDragDrop))
				{
					cfg.hboutline = ImColor(cfg.fl_hboutline[0], cfg.fl_hboutline[1], cfg.fl_hboutline[2]);
				}
				ImGui::SameLine(); ImGui::TextColored(ImVec4(255, 255, 0, 255), "[ COMING SOON ]");
				ImGui::Checkbox("ESP Distance", &cfg.b_EspDistance);
				ImGui::SameLine();
				ImGui::SetNextItemWidth(250.f);
				ImGui::SliderFloat("Max Distance", &cfg.max_distance, 1.0f, 10000.0f);
				if (ImGui::ColorEdit3("Visible Color", cfg.fl_VisibleColor, ImGuiColorEditFlags_NoDragDrop))
				{
					cfg.VisibleColor = ImColor(cfg.fl_VisibleColor[0], cfg.fl_VisibleColor[1], cfg.fl_VisibleColor[2]);
				}
				if (ImGui::ColorEdit3("Invisible Color", cfg.fl_InvisibleColor, ImGuiColorEditFlags_NoDragDrop))
				{
					cfg.InvisibleColor = ImColor(cfg.fl_InvisibleColor[0], cfg.fl_InvisibleColor[1], cfg.fl_InvisibleColor[2]);
				}
		}
		else if (cfg.tab_index == 1)
		{
			ImGui::Checkbox("Enable all aimbot options", &cfg.b_Aimbot);
			ImGui::Checkbox("Reticle type", &cfg.reticletype);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(180.f);
			ImGui::Combo("reticle style", &cfg.reticletypee, cfg.ReticleTypes, 8);
			ImGui::SameLine(); ImGui::TextColored(ImVec4(255, 255, 0, 255), "[ COMING SOON ]");
			ImGui::Checkbox("Reload type", &cfg.reloadtypebool);ImGui::SameLine();ImGui::SetNextItemWidth(180.f);ImGui::Combo("Clip / SingleShot", &cfg.reloadtype, cfg.ReloadTypes, 2);
			ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			ImGui::Checkbox("Weapon equip type", &cfg.EKSWeaponEquipTypebool); ImGui::SameLine(); ImGui::SetNextItemWidth(180.f); ImGui::Combo("Equip type", &cfg.EKSWeaponEquipType, cfg.weaponequiptypes, 4);
			ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			ImGui::Checkbox("Fire type", &cfg.firetypebool);
			ImGui::SameLine();ImGui::SetNextItemWidth(180.f);
			ImGui::Combo("Single / Burst / Semi-auto", &cfg.FireType, cfg.FireTypes, 3);
			ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			ImGui::Checkbox("Rounds per burst", &cfg.roundsperburst); if (ImGui::IsItemHovered())ImGui::SetTooltip("You must use burst weapon or choose burst from fire type");
			ImGui::SameLine(); ImGui::SetNextItemWidth(180.f);
			ImGui::SliderInt("[ Use burst weapon or use burst in fire type ]", &cfg.i_roundsperburst, 2, 90);
			ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			ImGui::Checkbox("Clip size", &cfg.clipsize); if (ImGui::IsItemHovered())ImGui::SetTooltip("Reload and your floor will be warzone");
			ImGui::SameLine(); ImGui::SetNextItemWidth(220.f);
			ImGui::SliderInt("Bullets in Clip", &cfg.i_clipsize, 2, 999);
			ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			ImGui::Checkbox("Aim FOV", &cfg.aimfov);
			ImGui::SameLine();
			ImGui::SetNextItemWidth(180.f);
			ImGui::SliderFloat("", &cfg.f_aimfov, 1.0f, 179.0f);
			ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			ImGui::Checkbox("Aim downsights", &cfg.aimdownsights);
			ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			//ImGui::Checkbox("Aimbot Location", &cfg.aimlocbool);

				ImGui::Checkbox("Show FOV", &cfg.b_AimbotFOV);
				//if (cfg.b_AimbotFOV)
				//{
				ImGui::SameLine();
				ImGui::SetNextItemWidth(180.f);
					ImGui::SliderFloat("FOV Size", &cfg.AimbotFOV, 1.0f, 1000.f);
					if (ImGui::ColorEdit3("FOV Color", cfg.fl_FovColor, ImGuiColorEditFlags_NoDragDrop))
					{
						cfg.FovColor = ImColor(cfg.fl_FovColor[0], cfg.fl_FovColor[1], cfg.fl_FovColor[2]);
					}
			//	}
				ImGui::Combo("Aimbot Key", &cfg.AimKey, keyItems, IM_ARRAYSIZE(keyItems),20);
				ImGui::Checkbox("Aimbot smooth", &cfg.b_AimbotSmooth);
				ImGui::SameLine();
				ImGui::SetNextItemWidth(180.f);
				ImGui::SliderFloat("Smoothing Value", &cfg.Smoothing, 0.200f, 10.0f);
				ImGui::Checkbox("Auto Aim", &cfg.autoaim);
				//ImGui::Checkbox("Auto Scope", &cfg.autoscope);
				ImGui::Checkbox("Friends aimbot", &cfg.friendsaim);
				ImGui::Checkbox("Remove Dead Bodies Aimbot", &cfg.Nodieaim);
				ImGui::Checkbox("Remove Knocked Aimbot", &cfg.nodownaim);

		}
		else if (cfg.tab_index == 2)
		{

		    //ImGui::Checkbox("Damage Type", &cfg.damagetype); if (ImGui::IsItemHovered())ImGui::SetTooltip("choose your damage type");
			//ImGui::SetNextItemWidth(180.f);
			//ImGui::Combo("Damage type", &cfg.damagetypee, cfg.DamageTypes, 2);
			//ImGui::Combo("Weapon State", &cfg.weaponstatee, cfg.weaponstates, 9);
			//ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			ImGui::Checkbox("Fast bullets / fast melee", &cfg.fastbulletsmelee); if (ImGui::IsItemHovered())ImGui::SetTooltip("No postfire time");
			ImGui::SameLine();ImGui::SetNextItemWidth(250.f);
			ImGui::SliderFloat("bullet & melee speed", &cfg.f_fastbulletsmelee, 0.0f, 10.0f);
			ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			ImGui::Checkbox("No Reload", &cfg.noreload); if (ImGui::IsItemHovered())ImGui::SetTooltip("remove reloading");
			ImGui::SameLine(); ImGui::TextColored(ImVec4(255, 255, 0, 255), "[ COMING SOON ]");
			ImGui::Checkbox("Fast Reload", &cfg.fastreload); if (ImGui::IsItemHovered())ImGui::SetTooltip("Super fast reload");
			ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			ImGui::Checkbox("Reduce reload time by 50%", &cfg.halfreload); if (ImGui::IsItemHovered())ImGui::SetTooltip("50% reload time reduced");
			ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			ImGui::Checkbox("No Spread", &cfg.nospread); if (ImGui::IsItemHovered())ImGui::SetTooltip("Best accuracy, No need to scope again");
			ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			ImGui::Checkbox("Unlimited ammo", &cfg.unlimitedammo); if (ImGui::IsItemHovered())ImGui::SetTooltip("Infinite ammo");
			ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			ImGui::Checkbox("Trigger Bot", &cfg.triggerbot); if (ImGui::IsItemHovered())ImGui::SetTooltip("Automatically shooting when aiming at enemies");
			ImGui::SameLine();
			ImGui::Checkbox("No Recoil", &cfg.norecoil); if (ImGui::IsItemHovered())ImGui::SetTooltip("weapon won't miss any bullet");
			ImGui::SameLine();
			ImGui::Checkbox("Bunny Hop", &cfg.bunnyhop); if (ImGui::IsItemHovered())ImGui::SetTooltip("press space once to be a bunny");
			//ImGui::Checkbox("Bunny Hop 2 [ Hold space ]", &cfg.bunnyhop2); if (ImGui::IsItemHovered())ImGui::SetTooltip("Hold space to be a bunny");
			ImGui::Checkbox("team collision", &cfg.teamcollision); if (ImGui::IsItemHovered())ImGui::SetTooltip("you can disable no clip in team");
			ImGui::SameLine(); ImGui::TextColored(ImVec4(128, 0, 128, 255), "[ Enable team collision before round starts to take effect ]");
			ImGui::Checkbox("Immune", &cfg.Immune);if (ImGui::IsItemHovered())ImGui::SetTooltip("Damage landing enemies");
			ImGui::SameLine();
			ImGui::Checkbox("Fake god mode", &cfg.fakegodmode);if (ImGui::IsItemHovered())ImGui::SetTooltip("Show fake heal stats");
			ImGui::SameLine();
			ImGui::Checkbox("all Downed [local]", &cfg.bdowned); if (ImGui::IsItemHovered())ImGui::SetTooltip("make all players downed [Knocked] locally");
			ImGui::Checkbox("Bots Godmode", &cfg.botsgodmode); if (ImGui::IsItemHovered())ImGui::SetTooltip("make all bots never die");
			ImGui::Checkbox("Enable Self knocked", &cfg.enableknocked); if (ImGui::IsItemHovered())ImGui::SetTooltip("make you always knocked");
			ImGui::SameLine();
			ImGui::Checkbox("Disable Self knocked", &cfg.disableknocked); if (ImGui::IsItemHovered())ImGui::SetTooltip("make you never get knocked");
			ImGui::Checkbox("No ragdoll", &cfg.noragdoll); if (ImGui::IsItemHovered())ImGui::SetTooltip("Ragdoll");
			ImGui::Checkbox("(Shooting range) walk speed", &cfg.shootingrangewalkspeed); if (ImGui::IsItemHovered())ImGui::SetTooltip("only works in shooting range");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(210.f);
			ImGui::SliderFloat("walk speed value", &cfg.f_shootingrangewalkspeed, 0.0f, 2000.0f);
			ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			ImGui::Checkbox("(Shooting range) Instant kill", &cfg.shootingrangeinstatntkill); if (ImGui::IsItemHovered())ImGui::SetTooltip("only works in shooting range");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(210.f);
			ImGui::SliderFloat("Damage value", &cfg.f_shootingrangeinstatntkill, 0.0f, 2000.0f);
			ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			//ImGui::Checkbox("Move while reviving other", &cfg.canmovewhilerevive); if (ImGui::IsItemHovered())ImGui::SetTooltip("you can move when you revive teammate");
		    ImGui::TextColored(ImVec4(128, 0, 128, 255), "[ Press V every respawn then left click to super melee ]");
			ImGui::Checkbox("Super Melee", &cfg.supermelee); if (ImGui::IsItemHovered())ImGui::SetTooltip("Enable/disable super melee completely");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(210.f);
			ImGui::SliderFloat("Super Melee value", &cfg.f_supermelee, 200.0f, 5000.0f);
			ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			ImGui::Checkbox("Super Melee Low Range", &cfg.supermeleelow); if (ImGui::IsItemHovered())ImGui::SetTooltip("kill all of them with only melee");
			ImGui::SameLine();
			ImGui::Checkbox("Super Melee Medium Range", &cfg.supermeleemedium); if (ImGui::IsItemHovered())ImGui::SetTooltip("kill all of them with only melee");
			ImGui::SameLine();
			ImGui::Checkbox("Super Melee High Range", &cfg.supermeleehigh); if (ImGui::IsItemHovered())ImGui::SetTooltip("kill all of them with only melee");
			ImGui::SameLine();
			ImGui::Checkbox("Super Melee Super Range", &cfg.supermeleesuper); if (ImGui::IsItemHovered())ImGui::SetTooltip("kill all of them with only melee");
			ImGui::Checkbox("Melee teleport", &cfg.meleeteleport); if (ImGui::IsItemHovered())ImGui::SetTooltip("Enable/disable melee teleport completely");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(210.f);
			ImGui::SliderFloat("Melee teleport value", &cfg.f_meleeteleport, 300.f, 500000.f);
			ImGui::SameLine(); ImGui::TextColored(ImVec4(0, 255, 0, 255), "[ New ]");
			ImGui::Checkbox("Melee Teleport Low Range", &cfg.meleeteleportlow); if (ImGui::IsItemHovered())ImGui::SetTooltip("Teleport to them with melee");
			ImGui::SameLine();
			ImGui::Checkbox("Melee Teleport Midium Range", &cfg.meleeteleportmidium); if (ImGui::IsItemHovered())ImGui::SetTooltip("Teleport to them with melee");
			ImGui::SameLine();
			ImGui::Checkbox("Melee Teleport High Range", &cfg.meleeteleporthigh); if (ImGui::IsItemHovered())ImGui::SetTooltip("Teleport to them with melee");
		}
		else if (cfg.tab_index == 3)
		{
		ImGui::Checkbox("No reload", &cfg.trollnoreload); if (ImGui::IsItemHovered())ImGui::SetTooltip("You will die with no ammo");
		ImGui::Checkbox("No Fire", &cfg.trollnofire); if (ImGui::IsItemHovered())ImGui::SetTooltip("You can't shoot anymore");
		ImGui::Checkbox("No AimDownSights", &cfg.trollaimdownsights); if (ImGui::IsItemHovered())ImGui::SetTooltip("You can't aim anymore");
		ImGui::Checkbox("No AimOverShoulder", &cfg.trollaimovershoulder); if (ImGui::IsItemHovered())ImGui::SetTooltip("You can't aim over shoulder anymore");
}
		else if (cfg.tab_index == 4)
		{
		    ImGui::SetNextItemWidth(250.f);
			ImGui::Combo("Show/hide menu key", &cfg.OpenKey, keyItems2, IM_ARRAYSIZE(keyItems2),30);
			ImGui::SetNextItemWidth(250.f);
			ImGui::Combo("Aimbot [enable / disable] Hotkey", &cfg.AimBotKey, keyItems3, IM_ARRAYSIZE(keyItems3), 30);
			ImGui::SetNextItemWidth(250.f);
			ImGui::Combo("Unload Cheat Hotkey", &cfg.UnloadKey, keyItems4, IM_ARRAYSIZE(keyItems4), 30);
			ImGui::SetNextItemWidth(250.f);
			ImGui::Combo("Close Game Hotkey", &cfg.CloseGameKey, keyItems5, IM_ARRAYSIZE(keyItems5), 30);
			ImGui::Checkbox("Startup sound", &cfg.startupsound);
			if (ImGui::Button("Save Settings"))
			{
				do {
					wchar_t buf[MAX_PATH];
					filesystem::path path = filesystem::path(getCurrentDirectoryOnWindows2() + "\\").remove_filename() / ".settings";
					auto file = CreateFileW(path.wstring().c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
					if (file == INVALID_HANDLE_VALUE) break;
					DWORD written;
					if (WriteFile(file, &cfg, sizeof(cfg), &written, 0))
					CloseHandle(file);
				} while (false);
			}
			ImGui::SameLine();
			if (ImGui::Button("Load Settings"))
			{
				do {
					wchar_t buf[MAX_PATH];
					filesystem::path path = filesystem::path(getCurrentDirectoryOnWindows2() + "\\").remove_filename() / ".settings";
					auto file = CreateFileW(path.wstring().c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					if (file == INVALID_HANDLE_VALUE) break;
					DWORD readed;
					if (ReadFile(file, &cfg, sizeof(cfg), &readed, 0))
					CloseHandle(file);
				} while (false);
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete Settings file"))
			{
				remove(".settings");
			}
			ImGui::Checkbox("Menu banner", &cfg.menubanner);
			ImGui::SameLine(); ImGui::TextColored(ImVec4(255, 255, 0, 255), "[ COMING SOON ]");
			ImGui::Checkbox("always center menu", &cfg.alwaysmenucenter);
			if (ImGui::Button("Center menu position"))
			{
				ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
			}
			if (ImGui::Button("Random cheat name"))
			{
				rename(filelocation().c_str(), randomname().c_str());
			}
			ImGui::SameLine();
			if (ImGui::Button("Reset menu size"))
			{
				ImGui::SetWindowSize(ImVec2(923, 736));
			}
			//ImGui::Checkbox("Random Cheat name loop", &cfg.randomcheatnameloop);
			ImGui::Checkbox("Hide console at startup", &cfg.hideconsole);
			if (ImGui::Button("HWID Spoofer"))
			{

			}
			ImGui::SameLine(); ImGui::TextColored(ImVec4(255, 255, 0, 255), "[ COMING SOON ]");
			ImGui::Checkbox("Menu Fps", &cfg.menufps);
			ImGui::Checkbox("Show Cursor", &cfg.showcursor);
			ImGui::Checkbox("Rainbow menu", &cfg.rainbowtheme);
			ImGui::SameLine(); ImGui::TextColored(ImVec4(255, 255, 0, 255), "[ COMING SOON ]");
			ImGui::Checkbox("Default", &cfg.defaulththeme);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 1", &cfg.theme1);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 2", &cfg.theme2);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 3", &cfg.theme3);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 4", &cfg.theme4);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 5", &cfg.theme5);
			ImGui::Separator();
			ImGui::Checkbox("Theme 6", &cfg.theme6);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 7", &cfg.theme7);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 8", &cfg.theme8);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 9", &cfg.theme9);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 10", &cfg.theme10);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 11", &cfg.theme11);
			ImGui::Separator();
			ImGui::Checkbox("Theme 12", &cfg.theme12);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 13", &cfg.theme13);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 14", &cfg.theme14);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 15", &cfg.theme15);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 16", &cfg.theme16);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 17", &cfg.theme17);
			ImGui::Separator();
			ImGui::Checkbox("Theme 18", &cfg.theme18);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 19", &cfg.theme19);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 20", &cfg.theme20);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 21", &cfg.theme21);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 22", &cfg.theme22);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 23", &cfg.theme23);
			ImGui::Separator();
			ImGui::Checkbox("Theme 24", &cfg.theme24);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 25", &cfg.theme25);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 26", &cfg.theme26);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 27", &cfg.theme27);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 28", &cfg.theme28);
			ImGui::SameLine();
			ImGui::Checkbox("Theme 29", &cfg.theme29);

			if (cfg.rainbowtheme == true)
			{
			}
			if (cfg.defaulththeme == true)
			{
				ImGuiStyle* style = &ImGui::GetStyle();
				style->WindowPadding = ImVec2(15, 15);
				style->WindowRounding = 5.0f;
				style->FramePadding = ImVec2(5, 5);
				style->FrameRounding = 4.0f;
				style->ItemSpacing = ImVec2(12, 8);
				style->ItemInnerSpacing = ImVec2(8, 6);
				style->IndentSpacing = 25.0f;
				style->ScrollbarSize = 15.0f;
				style->ScrollbarRounding = 9.0f;
				style->GrabMinSize = 5.0f;
				style->GrabRounding = 3.0f;
				style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
				style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
				style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
				style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
				style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
				style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
				style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
				style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
				style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
				style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
				style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
				style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
				style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
				style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
				style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
				style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
				style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
				style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
				style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
				style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
				style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
				style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
				style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
				style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
				style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
				style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
				style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
				style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
				style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
				style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
				style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
				style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
				style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
			}
			if (cfg.theme1 == true)
			{
				ImGuiStyle& style = ImGui::GetStyle();
						style.Colors[ImGuiCol_Text] = ImVec4(0.31f, 0.25f, 0.24f, 1.00f);
						style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
						style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.74f, 0.74f, 0.94f, 1.00f);
						style.Colors[ImGuiCol_Border] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
						style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
						style.Colors[ImGuiCol_FrameBg] = ImVec4(0.62f, 0.70f, 0.72f, 0.56f);
						style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.95f, 0.33f, 0.14f, 0.47f);
						style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.97f, 0.31f, 0.13f, 0.81f);
						style.Colors[ImGuiCol_TitleBg] = ImVec4(0.42f, 0.75f, 1.00f, 0.53f);
						style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.65f, 0.80f, 0.20f);
						style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.40f, 0.62f, 0.80f, 0.15f);
						style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.39f, 0.64f, 0.80f, 0.30f);
						style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.28f, 0.67f, 0.80f, 0.59f);
						style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 0.48f, 0.53f, 0.67f);
						style.Colors[ImGuiCol_CheckMark] = ImVec4(0.48f, 0.47f, 0.47f, 0.71f);
						style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.31f, 0.47f, 0.99f, 1.00f);
						style.Colors[ImGuiCol_Button] = ImVec4(1.00f, 0.79f, 0.18f, 0.78f);
						style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.42f, 0.82f, 1.00f, 0.81f);
						style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.72f, 1.00f, 1.00f, 0.86f);
						style.Colors[ImGuiCol_Header] = ImVec4(0.65f, 0.78f, 0.84f, 0.80f);
						style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.75f, 0.88f, 0.94f, 0.80f);
						style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.55f, 0.68f, 0.74f, 0.80f);//ImVec4(0.46f, 0.84f, 0.90f, 1.00f);
						style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.60f, 0.60f, 0.80f, 0.30f);
						style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
						style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
						style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.99f, 0.54f, 0.43f);
						style.Alpha = 1.0f;
						style.FrameRounding = 4;
						style.IndentSpacing = 12.0f;
			}
			if (cfg.theme2 == true)
			{
				ImVec4* colors = ImGui::GetStyle().Colors;
				colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
				colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
				colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
				colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
				colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
				colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
				colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
				colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
				colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
				colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
				colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
				colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
				colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
				colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
				colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
				colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
				colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
				colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
				colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
				colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
				colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
				colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
				colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
				colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
				colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
				colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
				colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
				colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
				colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
				colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
				colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
				colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
				colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
				colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
				colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
				colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
				colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
				colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
				colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
				colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
				colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
				colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
				colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
				colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
				colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
				colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
				colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
				colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
				colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
				colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);
				ImGuiStyle& style = ImGui::GetStyle();
				//style.WindowPadding = ImVec2(8.00f, 8.00f);
				//style.FramePadding = ImVec2(5.00f, 2.00f);
				//style.CellPadding = ImVec2(6.00f, 6.00f);
				//style.ItemSpacing = ImVec2(6.00f, 6.00f);
				//style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
				//style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
				style.IndentSpacing = 25;
				style.ScrollbarSize = 15;
				style.GrabMinSize = 10;
				style.WindowBorderSize = 1;
				style.ChildBorderSize = 1;
				style.PopupBorderSize = 1;
				//style.FrameBorderSize = 1;
				style.TabBorderSize = 1;
				style.WindowRounding = 7;
				style.ChildRounding = 4;
				style.FrameRounding = 3;
				style.PopupRounding = 4;
				style.ScrollbarRounding = 9;
				style.GrabRounding = 3;
				style.LogSliderDeadzone = 4;
				style.TabRounding = 4;
			}
			if (cfg.theme3 == true)
			{
				auto* style = &ImGui::GetStyle();
				style->FrameRounding = 2.0f;
				//style->WindowPadding = ImVec2(4.0f, 3.0f);
				//style->FramePadding = ImVec2(4.0f, 4.0f);
				//style->ItemSpacing = ImVec2(4.0f, 3.0f);
				style->IndentSpacing = 12;
				style->ScrollbarSize = 12;
				style->GrabMinSize = 9;
				style->WindowBorderSize = 0.0f;
				style->ChildBorderSize = 0.0f;
				style->PopupBorderSize = 0.0f;
				style->FrameBorderSize = 0.0f;
				style->TabBorderSize = 0.0f;
				style->WindowRounding = 0.0f;
				style->ChildRounding = 0.0f;
				style->FrameRounding = 0.0f;
				style->PopupRounding = 0.0f;
				style->GrabRounding = 2.0f;
				style->ScrollbarRounding = 12.0f;
				style->TabRounding = 0.0f;
				ImVec4* colors = ImGui::GetStyle().Colors;
				colors[ImGuiCol_Text] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
				colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
				colors[ImGuiCol_WindowBg] = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
				colors[ImGuiCol_ChildBg] = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
				colors[ImGuiCol_PopupBg] = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
				colors[ImGuiCol_Border] = ImVec4(0.89f, 0.89f, 0.89f, 1.00f);
				colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				colors[ImGuiCol_FrameBg] = ImVec4(0.93f, 0.93f, 0.93f, 1.00f);
				colors[ImGuiCol_FrameBgHovered] = ImVec4(1.00f, 0.69f, 0.07f, 0.69f);
				colors[ImGuiCol_FrameBgActive] = ImVec4(1.00f, 0.82f, 0.46f, 0.69f);
				colors[ImGuiCol_TitleBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				colors[ImGuiCol_TitleBgActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				colors[ImGuiCol_MenuBarBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				colors[ImGuiCol_ScrollbarBg] = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
				colors[ImGuiCol_ScrollbarGrab] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(1.00f, 0.69f, 0.07f, 0.69f);
				colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 0.82f, 0.46f, 0.69f);
				colors[ImGuiCol_CheckMark] = ImVec4(0.01f, 0.01f, 0.01f, 0.63f);
				colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.69f, 0.07f, 0.69f);
				colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.82f, 0.46f, 0.69f);
				colors[ImGuiCol_Button] = ImVec4(0.83f, 0.83f, 0.83f, 1.00f);
				colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 0.69f, 0.07f, 0.69f);
				colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.82f, 0.46f, 0.69f);
				colors[ImGuiCol_Header] = ImVec4(0.67f, 0.67f, 0.67f, 1.00f);
				colors[ImGuiCol_HeaderHovered] = ImVec4(1.00f, 0.69f, 0.07f, 1.00f);
				colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 0.82f, 0.46f, 0.69f);
				colors[ImGuiCol_Separator] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				colors[ImGuiCol_SeparatorHovered] = ImVec4(1.00f, 0.69f, 0.07f, 1.00f);
				colors[ImGuiCol_SeparatorActive] = ImVec4(1.00f, 0.82f, 0.46f, 0.69f);
				colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.18f);
				colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 0.69f, 0.07f, 1.00f);
				colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 0.82f, 0.46f, 0.69f);
				colors[ImGuiCol_Tab] = ImVec4(0.16f, 0.16f, 0.16f, 0.00f);
				colors[ImGuiCol_TabHovered] = ImVec4(1.00f, 0.69f, 0.07f, 1.00f);
				colors[ImGuiCol_TabActive] = ImVec4(1.00f, 0.69f, 0.07f, 1.00f);
				colors[ImGuiCol_TabUnfocused] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
				colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
				colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
				colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.69f, 0.07f, 1.00f);
				colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 0.69f, 0.07f, 1.00f);
				colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.69f, 0.07f, 1.00f);
				colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
				colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
				colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
			}
			if (cfg.theme4 == true)
			{
				auto* style = &ImGui::GetStyle();
				style->FrameRounding = 2.0f;
				//style->WindowPadding = ImVec2(4.0f, 3.0f);
				//style->FramePadding = ImVec2(4.0f, 4.0f);
				//style->ItemSpacing = ImVec2(4.0f, 3.0f);
				style->IndentSpacing = 12;
				style->ScrollbarSize = 12;
				style->GrabMinSize = 9;
				style->WindowBorderSize = 0.0f;
				style->ChildBorderSize = 0.0f;
				style->PopupBorderSize = 0.0f;
				style->FrameBorderSize = 0.0f;
				style->TabBorderSize = 0.0f;
				style->WindowRounding = 0.0f;
				style->ChildRounding = 0.0f;
				style->FrameRounding = 0.0f;
				style->PopupRounding = 0.0f;
				style->GrabRounding = 2.0f;
				style->ScrollbarRounding = 12.0f;
				style->TabRounding = 0.0f;
				ImVec4* colors = ImGui::GetStyle().Colors;
				colors[ImGuiCol_Text] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
				colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
				colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.16f, 1.00f);
				colors[ImGuiCol_ChildBg] = ImVec4(0.17f, 0.18f, 0.20f, 1.00f);
				colors[ImGuiCol_PopupBg] = ImVec4(0.22f, 0.24f, 0.25f, 1.00f);
				colors[ImGuiCol_Border] = ImVec4(0.16f, 0.17f, 0.18f, 1.00f);
				colors[ImGuiCol_BorderShadow] = ImVec4(0.16f, 0.17f, 0.18f, 1.00f);
				colors[ImGuiCol_FrameBg] = ImVec4(0.14f, 0.15f, 0.16f, 1.00f);
				colors[ImGuiCol_FrameBgHovered] = ImVec4(0.84f, 0.34f, 0.17f, 1.00f);
				colors[ImGuiCol_FrameBgActive] = ImVec4(0.59f, 0.24f, 0.12f, 1.00f);
				colors[ImGuiCol_TitleBg] = ImVec4(0.13f, 0.14f, 0.16f, 1.00f);
				colors[ImGuiCol_TitleBgActive] = ImVec4(0.13f, 0.14f, 0.16f, 1.00f);
				colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.13f, 0.14f, 0.16f, 1.00f);
				colors[ImGuiCol_MenuBarBg] = ImVec4(0.13f, 0.14f, 0.16f, 1.00f);
				colors[ImGuiCol_ScrollbarBg] = ImVec4(0.13f, 0.14f, 0.16f, 1.00f);
				colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.75f, 0.30f, 0.15f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
				colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
				colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
				colors[ImGuiCol_SliderGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
				colors[ImGuiCol_Button] = ImVec4(0.19f, 0.20f, 0.22f, 1.00f);
				colors[ImGuiCol_ButtonHovered] = ImVec4(0.84f, 0.34f, 0.17f, 1.00f);
				colors[ImGuiCol_ButtonActive] = ImVec4(0.59f, 0.24f, 0.12f, 1.00f);
				colors[ImGuiCol_Header] = ImVec4(0.22f, 0.23f, 0.25f, 1.00f);
				colors[ImGuiCol_HeaderHovered] = ImVec4(0.84f, 0.34f, 0.17f, 1.00f);
				colors[ImGuiCol_HeaderActive] = ImVec4(0.59f, 0.24f, 0.12f, 1.00f);
				colors[ImGuiCol_Separator] = ImVec4(0.17f, 0.18f, 0.20f, 1.00f);
				colors[ImGuiCol_SeparatorHovered] = ImVec4(0.75f, 0.30f, 0.15f, 1.00f);
				colors[ImGuiCol_SeparatorActive] = ImVec4(0.59f, 0.24f, 0.12f, 1.00f);
				colors[ImGuiCol_ResizeGrip] = ImVec4(0.84f, 0.34f, 0.17f, 0.14f);
				colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.84f, 0.34f, 0.17f, 1.00f);
				colors[ImGuiCol_ResizeGripActive] = ImVec4(0.59f, 0.24f, 0.12f, 1.00f);
				colors[ImGuiCol_Tab] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
				colors[ImGuiCol_TabHovered] = ImVec4(0.84f, 0.34f, 0.17f, 1.00f);
				colors[ImGuiCol_TabActive] = ImVec4(0.68f, 0.28f, 0.14f, 1.00f);
				colors[ImGuiCol_TabUnfocused] = ImVec4(0.13f, 0.14f, 0.16f, 1.00f);
				colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.17f, 0.18f, 0.20f, 1.00f);
				colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
				colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
				colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				colors[ImGuiCol_TextSelectedBg] = ImVec4(0.75f, 0.30f, 0.15f, 1.00f);
				colors[ImGuiCol_DragDropTarget] = ImVec4(0.75f, 0.30f, 0.15f, 1.00f);
				colors[ImGuiCol_NavHighlight] = ImVec4(0.75f, 0.30f, 0.15f, 1.00f);
				colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
				colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
				colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
			}
			if (cfg.theme5 == true)
			{
				ImGui::GetStyle().FrameRounding = 4.0f;
				ImGui::GetStyle().GrabRounding = 4.0f;
				ImVec4* colors = ImGui::GetStyle().Colors;
				colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
				colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
				colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
				colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
				colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
				colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
				colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
				colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
				colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
				colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
				colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
				colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
				colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
				colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
				colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
				colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
				colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
				colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
				colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
				colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
				colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
				colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
				colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
				colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
				colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
				colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
				colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
				colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
				colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
				colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
				colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
				colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
				colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
				colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
				colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
				colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
				colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
				colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
				colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
				colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
				colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
				colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
				colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
				colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
			}
			if (cfg.theme6 == true)
			{
				auto* style = &ImGui::GetStyle();
				//style->WindowMinSize = ImVec2(115, 20);
				//style->FramePadding = ImVec2(4, 2);
				//style->ItemSpacing = ImVec2(6, 2);
				//style->ItemInnerSpacing = ImVec2(6, 4);
				style->Alpha = 1.0f;
				style->WindowRounding = 4.0f;
				style->WindowPadding = ImVec2(9, 8);
				style->FrameRounding = 2.0f;
				style->IndentSpacing = 6.0f;
				style->ItemInnerSpacing = ImVec2(2, 4);
				style->ColumnsMinSpacing = 50.0f;
				style->GrabMinSize = 20.0f;
				style->GrabRounding = 20.0f;
				style->ScrollbarSize = 12.0f;
				style->ScrollbarRounding = 16.0f;
				style->Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
				style->Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
				style->Colors[ImGuiCol_PopupBg] = ImVec4(0.47f, 0.77f, 0.83f, 1.00f);
				style->Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 1.00f);
				style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
				style->Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.32f, 0.27f, 1.00f);
				style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.11f, 0.74f, 0.00f, 1.00f);
				style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.07f, 0.70f, 0.01f, 1.00f);
				style->Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.43f, 0.24f, 1.00f);
				style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
				style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.67f, 0.01f, 1.00f);
				style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
				style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
				style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.43f, 0.24f, 1.00f);
				style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.19f, 0.76f, 0.00f, 1.00f);
				style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.03f, 0.70f, 0.06f, 1.00f);
				style->Colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 0.71f, 0.39f, 1.00f);
				style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.02f, 0.59f, 0.38f, 1.00f);
				style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.00f, 0.49f, 0.51f, 1.00f);
				style->Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.43f, 0.24f, 1.00f);
				style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.08f, 0.77f, 0.03f, 1.00f);
				style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.08f, 0.72f, 0.00f, 1.00f);
				style->Colors[ImGuiCol_Header] = ImVec4(0.11f, 0.64f, 0.00f, 1.00f);
				style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.03f, 0.70f, 0.01f, 1.00f);
				style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.05f, 0.72f, 0.01f, 1.00f);
				style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 1.00f);
				style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 0.55f, 0.12f, 1.00f);
				style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00f, 0.71f, 0.01f, 1.00f);
				style->Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
				style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.05f, 0.64f, 0.01f, 1.00f);
				style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
				style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.04f, 0.70f, 0.02f, 1.00f);
				style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.02f, 0.57f, 0.00f, 1.00f);
			}
			if (cfg.theme7 == true)
			{
				ImGuiStyle& style = ImGui::GetStyle();
				style.WindowRounding = 5.3f;
				style.FrameRounding = 2.3f;
				style.ScrollbarRounding = 0;
				style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 0.90f);
				style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
				style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
				style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.85f);
				style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
				style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.01f, 1.00f);
				style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
				style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
				style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.83f);
				style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.80f, 0.20f);
				style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.87f);
				style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.01f, 0.01f, 0.02f, 0.80f);
				style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
				style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.55f, 0.53f, 0.55f, 0.51f);
				style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
				style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.91f);
				style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.83f);
				style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.70f, 0.62f);
				style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 0.84f);
				style.Colors[ImGuiCol_Button] = ImVec4(0.48f, 0.72f, 0.89f, 0.49f);
				style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.50f, 0.69f, 0.99f, 0.68f);
				style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
				style.Colors[ImGuiCol_Header] = ImVec4(0.30f, 0.69f, 1.00f, 0.53f);
				style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.44f, 0.61f, 0.86f, 1.00f);
				style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.38f, 0.62f, 0.83f, 1.00f);
				style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
				style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
				style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
				style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
				style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
				style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
			}
			if (cfg.theme8 == true)
			{
				ImVec4* colors = ImGui::GetStyle().Colors;
				colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				colors[ImGuiCol_TextDisabled] = ImVec4(0.00f, 1.00f, 0.00f, 0.57f);
				colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
				colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
				colors[ImGuiCol_PopupBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
				colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
				colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
				colors[ImGuiCol_FrameBgHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.39f);
				colors[ImGuiCol_FrameBgActive] = ImVec4(0.18f, 0.18f, 0.18f, 0.67f);
				colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
				colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 1.00f, 0.00f, 0.78f);
				colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
				colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
				colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
				colors[ImGuiCol_ScrollbarGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.57f);
				colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 1.00f, 0.00f, 0.57f);
				colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
				colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
				colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
				colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.57f);
				colors[ImGuiCol_Button] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
				colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.57f);
				colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
				colors[ImGuiCol_Header] = ImVec4(0.00f, 1.00f, 0.00f, 0.78f);
				colors[ImGuiCol_HeaderHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.39f);
				colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 1.00f, 0.00f, 0.57f);
				colors[ImGuiCol_Separator] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
				colors[ImGuiCol_SeparatorHovered] = ImVec4(0.72f, 0.72f, 0.72f, 0.78f);
				colors[ImGuiCol_SeparatorActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
				colors[ImGuiCol_ResizeGrip] = ImVec4(0.91f, 0.91f, 0.91f, 0.25f);
				colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.81f, 0.81f, 0.81f, 0.67f);
				colors[ImGuiCol_ResizeGripActive] = ImVec4(0.46f, 0.46f, 0.46f, 0.95f);
				colors[ImGuiCol_Tab] = ImVec4(0.24f, 0.79f, 0.69f, 1.00f);
				colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
			}
			if (cfg.theme9 == true)
			{
				ImGuiStyle* style = &ImGui::GetStyle();
				ImVec4* colors = style->Colors;
				colors[ImGuiCol_Text] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
				colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
				colors[ImGuiCol_WindowBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
				colors[ImGuiCol_ChildBg] = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
				colors[ImGuiCol_PopupBg] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
				colors[ImGuiCol_Border] = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
				colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
				colors[ImGuiCol_FrameBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
				colors[ImGuiCol_FrameBgHovered] = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
				colors[ImGuiCol_FrameBgActive] = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
				colors[ImGuiCol_TitleBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
				colors[ImGuiCol_TitleBgActive] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
				colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
				colors[ImGuiCol_MenuBarBg] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
				colors[ImGuiCol_ScrollbarBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
				colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
				colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
				colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
				colors[ImGuiCol_SliderGrab] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
				colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_Button] = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
				colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
				colors[ImGuiCol_ButtonActive] = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
				colors[ImGuiCol_Header] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
				colors[ImGuiCol_HeaderHovered] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
				colors[ImGuiCol_HeaderActive] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
				colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
				colors[ImGuiCol_SeparatorHovered] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
				colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
				colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
				colors[ImGuiCol_ResizeGripActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_Tab] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
				colors[ImGuiCol_TabHovered] = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
				colors[ImGuiCol_TabActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
				colors[ImGuiCol_TabUnfocused] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
				colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
				colors[ImGuiCol_PlotLines] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
				colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_PlotHistogram] = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
				colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
				colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_NavHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
				colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
				style->ChildRounding = 4.0f;
				//style->FrameBorderSize = 1.0f;
				style->FrameRounding = 2.0f;
				style->GrabMinSize = 7.0f;
				style->PopupRounding = 2.0f;
				style->ScrollbarRounding = 12.0f;
				style->ScrollbarSize = 13.0f;
				style->TabBorderSize = 1.0f;
				style->TabRounding = 0.0f;
				style->WindowRounding = 4.0f;
			}
			if (cfg.theme10 == true)
			{
				ImVec4* colors = ImGui::GetStyle().Colors;
				colors[ImGuiCol_Text] = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
				colors[ImGuiCol_TextDisabled] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
				colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.94f);
				colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
				colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
				colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
				colors[ImGuiCol_FrameBgHovered] = ImVec4(0.37f, 0.14f, 0.14f, 0.67f);
				colors[ImGuiCol_FrameBgActive] = ImVec4(0.39f, 0.20f, 0.20f, 0.67f);
				colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
				colors[ImGuiCol_TitleBgActive] = ImVec4(0.48f, 0.16f, 0.16f, 1.00f);
				colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.48f, 0.16f, 0.16f, 1.00f);
				colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
				colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
				colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
				colors[ImGuiCol_CheckMark] = ImVec4(0.56f, 0.10f, 0.10f, 1.00f);
				colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.19f, 0.19f, 0.40f);
				colors[ImGuiCol_SliderGrabActive] = ImVec4(0.89f, 0.00f, 0.19f, 1.00f);
				colors[ImGuiCol_Button] = ImVec4(1.00f, 0.19f, 0.19f, 0.40f);
				colors[ImGuiCol_ButtonHovered] = ImVec4(0.80f, 0.17f, 0.00f, 1.00f);
				colors[ImGuiCol_ButtonActive] = ImVec4(0.89f, 0.00f, 0.19f, 1.00f);
				colors[ImGuiCol_Header] = ImVec4(0.33f, 0.35f, 0.36f, 0.53f);
				colors[ImGuiCol_HeaderHovered] = ImVec4(0.76f, 0.28f, 0.44f, 0.67f);
				colors[ImGuiCol_HeaderActive] = ImVec4(0.47f, 0.47f, 0.47f, 0.67f);
				colors[ImGuiCol_Separator] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
				colors[ImGuiCol_SeparatorHovered] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
				colors[ImGuiCol_SeparatorActive] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
				colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
				colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
				colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
				colors[ImGuiCol_Tab] = ImVec4(0.07f, 0.07f, 0.07f, 0.51f);
				colors[ImGuiCol_TabHovered] = ImVec4(0.86f, 0.23f, 0.43f, 0.67f);
				colors[ImGuiCol_TabActive] = ImVec4(0.19f, 0.19f, 0.19f, 0.57f);
				colors[ImGuiCol_TabUnfocused] = ImVec4(0.05f, 0.05f, 0.05f, 0.90f);
				colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.13f, 0.13f, 0.74f);
				colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
				colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
				colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
				colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
				colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
				colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
				colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
				colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
				colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
				colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
				colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
				colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
				colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
			}
			if (cfg.theme11 == true)
			{
				ImVec4* colors = ImGui::GetStyle().Colors;
				colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
				colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
				colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
				colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
				colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				colors[ImGuiCol_FrameBg] = ImVec4(0.44f, 0.44f, 0.44f, 0.60f);
				colors[ImGuiCol_FrameBgHovered] = ImVec4(0.57f, 0.57f, 0.57f, 0.70f);
				colors[ImGuiCol_FrameBgActive] = ImVec4(0.76f, 0.76f, 0.76f, 0.80f);
				colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
				colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
				colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.60f);
				colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
				colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
				colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
				colors[ImGuiCol_CheckMark] = ImVec4(0.13f, 0.75f, 0.55f, 0.80f);
				colors[ImGuiCol_SliderGrab] = ImVec4(0.13f, 0.75f, 0.75f, 0.80f);
				colors[ImGuiCol_SliderGrabActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
				colors[ImGuiCol_Button] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
				colors[ImGuiCol_ButtonHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
				colors[ImGuiCol_ButtonActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
				colors[ImGuiCol_Header] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
				colors[ImGuiCol_HeaderHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
				colors[ImGuiCol_HeaderActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
				colors[ImGuiCol_Separator] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
				colors[ImGuiCol_SeparatorHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
				colors[ImGuiCol_SeparatorActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
				colors[ImGuiCol_ResizeGrip] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
				colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
				colors[ImGuiCol_ResizeGripActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
				colors[ImGuiCol_Tab] = ImVec4(0.13f, 0.75f, 0.55f, 0.80f);
				colors[ImGuiCol_TabHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.80f);
				colors[ImGuiCol_TabActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
				colors[ImGuiCol_TabUnfocused] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
				colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.36f, 0.36f, 0.36f, 0.54f);
				colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
				colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
				colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
				colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
				colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
				colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
				colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
				colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
				colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
				colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
				colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
				colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
				colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
			}
			if (cfg.theme12 == true)
			{
				ImGuiStyle& style = ImGui::GetStyle();
				style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
				style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
				style.Colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
				style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
				style.Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
				style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				style.Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
				style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
				style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
				style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
				style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
				style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
				style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
				style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
				style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
				style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
				style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
				style.Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
				style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
				style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
				style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
				style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
				style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
				style.Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
				style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
				style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
				style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
				style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
				style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
				style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
				style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
				style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
				style.Colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
				style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
				style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
				style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
				style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
				style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
				style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
				style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
				style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
				style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
				style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
				style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
				style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
				style.GrabRounding = style.FrameRounding = 2.3f;
			}
			constexpr auto ColorFromBytes = [](uint8_t r, uint8_t g, uint8_t b)
			{
				return ImVec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f);
			};
			if (cfg.theme13 == true)
			{
				auto& style = ImGui::GetStyle();
				ImVec4* colors = style.Colors;
				const ImVec4 lightBgColor = ColorFromBytes(82, 82, 85);
				const ImVec4 veryLightBgColor = ColorFromBytes(90, 90, 95);
				const ImVec4 panelColor = ColorFromBytes(51, 51, 55);
				const ImVec4 panelHoverColor = ColorFromBytes(29, 151, 236);
				const ImVec4 panelActiveColor = ColorFromBytes(0, 119, 200);
				const ImVec4 textColor = ColorFromBytes(255, 255, 255);
				const ImVec4 textDisabledColor = ColorFromBytes(151, 151, 151);
				const ImVec4 borderColor = ColorFromBytes(78, 78, 78);
				colors[ImGuiCol_Text] = textColor;
				colors[ImGuiCol_TextDisabled] = textDisabledColor;
				colors[ImGuiCol_TextSelectedBg] = panelActiveColor;
				colors[ImGuiCol_Border] = borderColor;
				colors[ImGuiCol_BorderShadow] = borderColor;
				colors[ImGuiCol_FrameBg] = panelColor;
				colors[ImGuiCol_FrameBgHovered] = panelHoverColor;
				colors[ImGuiCol_FrameBgActive] = panelActiveColor;
				colors[ImGuiCol_MenuBarBg] = panelColor;
				colors[ImGuiCol_ScrollbarBg] = panelColor;
				colors[ImGuiCol_ScrollbarGrab] = lightBgColor;
				colors[ImGuiCol_ScrollbarGrabHovered] = veryLightBgColor;
				colors[ImGuiCol_ScrollbarGrabActive] = veryLightBgColor;
				colors[ImGuiCol_CheckMark] = panelActiveColor;
				colors[ImGuiCol_SliderGrab] = panelHoverColor;
				colors[ImGuiCol_SliderGrabActive] = panelActiveColor;
				colors[ImGuiCol_Button] = panelColor;
				colors[ImGuiCol_ButtonHovered] = panelHoverColor;
				colors[ImGuiCol_ButtonActive] = panelHoverColor;
				colors[ImGuiCol_Header] = panelColor;
				colors[ImGuiCol_HeaderHovered] = panelHoverColor;
				colors[ImGuiCol_HeaderActive] = panelActiveColor;
				colors[ImGuiCol_Separator] = borderColor;
				colors[ImGuiCol_SeparatorHovered] = borderColor;
				colors[ImGuiCol_SeparatorActive] = borderColor;
				colors[ImGuiCol_ResizeGripHovered] = panelColor;
				colors[ImGuiCol_ResizeGripActive] = lightBgColor;
				colors[ImGuiCol_PlotLines] = panelActiveColor;
				colors[ImGuiCol_PlotLinesHovered] = panelHoverColor;
				colors[ImGuiCol_PlotHistogram] = panelActiveColor;
				colors[ImGuiCol_PlotHistogramHovered] = panelHoverColor;
				colors[ImGuiCol_TabActive] = panelActiveColor;
				colors[ImGuiCol_TabHovered] = panelHoverColor;
				style.WindowRounding = 0.0f;
				style.ChildRounding = 0.0f;
				style.FrameRounding = 0.0f;
				style.GrabRounding = 0.0f;
				style.PopupRounding = 0.0f;
				style.ScrollbarRounding = 0.0f;
				style.TabRounding = 0.0f;
			}
			if (cfg.theme14 == true)
			{
				auto& io = ImGui::GetIO();
				auto& style = ImGui::GetStyle();
				style.FrameRounding = 4.0f;
				style.WindowBorderSize = 0.0f;
				style.PopupBorderSize = 0.0f;
				style.GrabRounding = 4.0f;
				ImVec4* colors = ImGui::GetStyle().Colors;
				colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				colors[ImGuiCol_TextDisabled] = ImVec4(0.73f, 0.75f, 0.74f, 1.00f);
				colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.09f, 0.94f);
				colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
				colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);
				colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				colors[ImGuiCol_FrameBg] = ImVec4(0.71f, 0.39f, 0.39f, 0.54f);
				colors[ImGuiCol_FrameBgHovered] = ImVec4(0.84f, 0.66f, 0.66f, 0.40f);
				colors[ImGuiCol_FrameBgActive] = ImVec4(0.84f, 0.66f, 0.66f, 0.67f);
				colors[ImGuiCol_TitleBg] = ImVec4(0.47f, 0.22f, 0.22f, 0.67f);
				colors[ImGuiCol_TitleBgActive] = ImVec4(0.47f, 0.22f, 0.22f, 1.00f);
				colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.47f, 0.22f, 0.22f, 0.67f);
				colors[ImGuiCol_MenuBarBg] = ImVec4(0.34f, 0.16f, 0.16f, 1.00f);
				colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
				colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
				colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				colors[ImGuiCol_SliderGrab] = ImVec4(0.71f, 0.39f, 0.39f, 1.00f);
				colors[ImGuiCol_SliderGrabActive] = ImVec4(0.84f, 0.66f, 0.66f, 1.00f);
				colors[ImGuiCol_Button] = ImVec4(0.47f, 0.22f, 0.22f, 0.65f);
				colors[ImGuiCol_ButtonHovered] = ImVec4(0.71f, 0.39f, 0.39f, 0.65f);
				colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);
				colors[ImGuiCol_Header] = ImVec4(0.71f, 0.39f, 0.39f, 0.54f);
				colors[ImGuiCol_HeaderHovered] = ImVec4(0.84f, 0.66f, 0.66f, 0.65f);
				colors[ImGuiCol_HeaderActive] = ImVec4(0.84f, 0.66f, 0.66f, 0.00f);
				colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
				colors[ImGuiCol_SeparatorHovered] = ImVec4(0.71f, 0.39f, 0.39f, 0.54f);
				colors[ImGuiCol_SeparatorActive] = ImVec4(0.71f, 0.39f, 0.39f, 0.54f);
				colors[ImGuiCol_ResizeGrip] = ImVec4(0.71f, 0.39f, 0.39f, 0.54f);
				colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.84f, 0.66f, 0.66f, 0.66f);
				colors[ImGuiCol_ResizeGripActive] = ImVec4(0.84f, 0.66f, 0.66f, 0.66f);
				colors[ImGuiCol_Tab] = ImVec4(0.71f, 0.39f, 0.39f, 0.54f);
				colors[ImGuiCol_TabHovered] = ImVec4(0.84f, 0.66f, 0.66f, 0.66f);
				colors[ImGuiCol_TabActive] = ImVec4(0.84f, 0.66f, 0.66f, 0.66f);
				colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
				colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
				colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
				colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
				colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
				colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
				colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
				colors[ImGuiCol_NavHighlight] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
				colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
				colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
				colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
			}
			if (cfg.theme15 == true)
			{
				ImGuiStyle* style = &ImGui::GetStyle();
				ImVec4* colors = style->Colors;
				colors[ImGuiCol_Text] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
				colors[ImGuiCol_TextDisabled] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
				colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
				colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
				colors[ImGuiCol_Border] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
				colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				colors[ImGuiCol_FrameBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
				colors[ImGuiCol_FrameBgHovered] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
				colors[ImGuiCol_FrameBgActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
				colors[ImGuiCol_TitleBg] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
				colors[ImGuiCol_TitleBgActive] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
				colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
				colors[ImGuiCol_MenuBarBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
				colors[ImGuiCol_ScrollbarBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.53f);
				colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.81f, 0.83f, 0.81f, 1.00f);
				colors[ImGuiCol_CheckMark] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
				colors[ImGuiCol_SliderGrab] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
				colors[ImGuiCol_SliderGrabActive] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
				colors[ImGuiCol_Button] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
				colors[ImGuiCol_ButtonHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
				colors[ImGuiCol_ButtonActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
				colors[ImGuiCol_Header] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
				colors[ImGuiCol_HeaderHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
				colors[ImGuiCol_HeaderActive] = ImVec4(0.93f, 0.65f, 0.14f, 1.00f);
				colors[ImGuiCol_Separator] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
				colors[ImGuiCol_SeparatorHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
				colors[ImGuiCol_SeparatorActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
				colors[ImGuiCol_ResizeGrip] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
				colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
				colors[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
				colors[ImGuiCol_Tab] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
				colors[ImGuiCol_TabHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
				colors[ImGuiCol_TabActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
				colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
				colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
				colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
				colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
				colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
				colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
				colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
				colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
				colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
				colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
				colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
				//style->FramePadding = ImVec2(4, 2);
				//style->ItemSpacing = ImVec2(10, 2);
				style->IndentSpacing = 12;
				style->ScrollbarSize = 10;
				style->WindowRounding = 4;
				style->FrameRounding = 4;
				style->PopupRounding = 4;
				style->ScrollbarRounding = 6;
				style->GrabRounding = 4;
				style->TabRounding = 4;
				style->WindowMenuButtonPosition = ImGuiDir_Right;
				style->DisplaySafeAreaPadding = ImVec2(4, 4);
			}
			if (cfg.theme16 == true)
			{
				ImVec4* colors = ImGui::GetStyle().Colors;
				colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
				colors[ImGuiCol_WindowBg] = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
				colors[ImGuiCol_ChildBg] = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
				colors[ImGuiCol_PopupBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
				colors[ImGuiCol_Border] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
				colors[ImGuiCol_BorderShadow] = ImVec4(0.14f, 0.16f, 0.11f, 0.52f);
				colors[ImGuiCol_FrameBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
				colors[ImGuiCol_FrameBgHovered] = ImVec4(0.27f, 0.30f, 0.23f, 1.00f);
				colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.34f, 0.26f, 1.00f);
				colors[ImGuiCol_TitleBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
				colors[ImGuiCol_TitleBgActive] = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
				colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
				colors[ImGuiCol_MenuBarBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
				colors[ImGuiCol_ScrollbarBg] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
				colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.28f, 0.32f, 0.24f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.25f, 0.30f, 0.22f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.23f, 0.27f, 0.21f, 1.00f);
				colors[ImGuiCol_CheckMark] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
				colors[ImGuiCol_SliderGrab] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
				colors[ImGuiCol_SliderGrabActive] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
				colors[ImGuiCol_Button] = ImVec4(0.29f, 0.34f, 0.26f, 0.40f);
				colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
				colors[ImGuiCol_ButtonActive] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
				colors[ImGuiCol_Header] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
				colors[ImGuiCol_HeaderHovered] = ImVec4(0.35f, 0.42f, 0.31f, 0.6f);
				colors[ImGuiCol_HeaderActive] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
				colors[ImGuiCol_Separator] = ImVec4(0.14f, 0.16f, 0.11f, 1.00f);
				colors[ImGuiCol_SeparatorHovered] = ImVec4(0.54f, 0.57f, 0.51f, 1.00f);
				colors[ImGuiCol_SeparatorActive] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
				colors[ImGuiCol_ResizeGrip] = ImVec4(0.19f, 0.23f, 0.18f, 0.00f); // grip invis
				colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.54f, 0.57f, 0.51f, 1.00f);
				colors[ImGuiCol_ResizeGripActive] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
				colors[ImGuiCol_Tab] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
				colors[ImGuiCol_TabHovered] = ImVec4(0.54f, 0.57f, 0.51f, 0.78f);
				colors[ImGuiCol_TabActive] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
				colors[ImGuiCol_TabUnfocused] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
				colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
				colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
				colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
				colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.78f, 0.28f, 1.00f);
				colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				colors[ImGuiCol_TextSelectedBg] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
				colors[ImGuiCol_DragDropTarget] = ImVec4(0.73f, 0.67f, 0.24f, 1.00f);
				colors[ImGuiCol_NavHighlight] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
				colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
				colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
				colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
				ImGuiStyle& style = ImGui::GetStyle();
				//style.FrameBorderSize = 1.0f;
				style.WindowRounding = 0.0f;
				style.ChildRounding = 0.0f;
				style.FrameRounding = 0.0f;
				style.PopupRounding = 0.0f;
				style.ScrollbarRounding = 0.0f;
				style.GrabRounding = 0.0f;
				style.TabRounding = 0.0f;
			}
			if (cfg.theme17 == true)
			{
				ImGui::GetStyle().FrameRounding = 4.0f;
				ImGui::GetStyle().GrabRounding = 4.0f;
				ImVec4* colors = ImGui::GetStyle().Colors;
				colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
				colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
				colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
				colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
				colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
				colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
				colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
				colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
				colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
				colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
				colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
				colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
				colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
				colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
				colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
				colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
				colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
				colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
				colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
				colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
				colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
				colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
				colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
				colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
				colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
				colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
				colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
				colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
				colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
				colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
				colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
				colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
				colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
				colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
				colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
				colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
				colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
				colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
				colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
				colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
				colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
				colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
				colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
				colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
			}
			if (cfg.theme18 == true)
			{
				ImGuiStyle& style = ImGui::GetStyle();
				ImVec4* colors = style.Colors;
				/// 0 = FLAT APPEARENCE
				/// 1 = MORE "3D" LOOK
				int is3D = 1;
				colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
				colors[ImGuiCol_ChildBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
				colors[ImGuiCol_WindowBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
				colors[ImGuiCol_PopupBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
				colors[ImGuiCol_Border] = ImVec4(0.12f, 0.12f, 0.12f, 0.71f);
				colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
				colors[ImGuiCol_FrameBg] = ImVec4(0.42f, 0.42f, 0.42f, 0.54f);
				colors[ImGuiCol_FrameBgHovered] = ImVec4(0.42f, 0.42f, 0.42f, 0.40f);
				colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.67f);
				colors[ImGuiCol_TitleBg] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
				colors[ImGuiCol_TitleBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
				colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.17f, 0.17f, 0.17f, 0.90f);
				colors[ImGuiCol_MenuBarBg] = ImVec4(0.335f, 0.335f, 0.335f, 1.000f);
				colors[ImGuiCol_ScrollbarBg] = ImVec4(0.24f, 0.24f, 0.24f, 0.53f);
				colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
				colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
				colors[ImGuiCol_CheckMark] = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
				colors[ImGuiCol_SliderGrab] = ImVec4(0.52f, 0.52f, 0.52f, 1.00f);
				colors[ImGuiCol_SliderGrabActive] = ImVec4(0.64f, 0.64f, 0.64f, 1.00f);
				colors[ImGuiCol_Button] = ImVec4(0.54f, 0.54f, 0.54f, 0.35f);
				colors[ImGuiCol_ButtonHovered] = ImVec4(0.52f, 0.52f, 0.52f, 0.59f);
				colors[ImGuiCol_ButtonActive] = ImVec4(0.76f, 0.76f, 0.76f, 1.00f);
				colors[ImGuiCol_Header] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
				colors[ImGuiCol_HeaderHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
				colors[ImGuiCol_HeaderActive] = ImVec4(0.76f, 0.76f, 0.76f, 0.77f);
				colors[ImGuiCol_Separator] = ImVec4(0.000f, 0.000f, 0.000f, 0.137f);
				colors[ImGuiCol_SeparatorHovered] = ImVec4(0.700f, 0.671f, 0.600f, 0.290f);
				colors[ImGuiCol_SeparatorActive] = ImVec4(0.702f, 0.671f, 0.600f, 0.674f);
				colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
				colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
				colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
				colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
				colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
				colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
				colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				colors[ImGuiCol_TextSelectedBg] = ImVec4(0.73f, 0.73f, 0.73f, 0.35f);
				colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
				colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
				colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
				colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
				colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
				style.PopupRounding = 3;
				//style.WindowPadding = ImVec2(4, 4);
				//style.FramePadding = ImVec2(6, 4);
				//style.ItemSpacing = ImVec2(6, 2);
				style.ScrollbarSize = 18;
				style.WindowBorderSize = 1;
				style.ChildBorderSize = 1;
				style.PopupBorderSize = 1;
				//style.FrameBorderSize = is3D;
				style.WindowRounding = 3;
				style.ChildRounding = 3;
				style.FrameRounding = 3;
				style.ScrollbarRounding = 2;
				style.GrabRounding = 3;
				style.TabBorderSize = is3D;
				style.TabRounding = 3;
				colors[ImGuiCol_Tab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
				colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
				colors[ImGuiCol_TabActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
				colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
				colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
			}
			if (cfg.theme19 == true)
			{
				ImGuiStyle* style = &ImGui::GetStyle();
				ImVec4* colors = style->Colors;
				colors[ImGuiCol_Text] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
				colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
				colors[ImGuiCol_WindowBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
				colors[ImGuiCol_ChildBg] = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
				colors[ImGuiCol_PopupBg] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
				colors[ImGuiCol_Border] = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
				colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
				colors[ImGuiCol_FrameBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
				colors[ImGuiCol_FrameBgHovered] = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
				colors[ImGuiCol_FrameBgActive] = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
				colors[ImGuiCol_TitleBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
				colors[ImGuiCol_TitleBgActive] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
				colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
				colors[ImGuiCol_MenuBarBg] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
				colors[ImGuiCol_ScrollbarBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
				colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
				colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
				colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
				colors[ImGuiCol_SliderGrab] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
				colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_Button] = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
				colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
				colors[ImGuiCol_ButtonActive] = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
				colors[ImGuiCol_Header] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
				colors[ImGuiCol_HeaderHovered] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
				colors[ImGuiCol_HeaderActive] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
				colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
				colors[ImGuiCol_SeparatorHovered] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
				colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
				colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
				colors[ImGuiCol_ResizeGripActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_Tab] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
				colors[ImGuiCol_TabHovered] = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
				colors[ImGuiCol_TabActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
				colors[ImGuiCol_TabUnfocused] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
				colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
				colors[ImGuiCol_PlotLines] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
				colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_PlotHistogram] = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
				colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
				colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_NavHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
				colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
				colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
				style->ChildRounding = 4.0f;
				//style->FrameBorderSize = 1.0f;
				style->FrameRounding = 2.0f;
				style->GrabMinSize = 7.0f;
				style->PopupRounding = 2.0f;
				style->ScrollbarRounding = 12.0f;
				style->ScrollbarSize = 13.0f;
				style->TabBorderSize = 1.0f;
				style->TabRounding = 0.0f;
				style->WindowRounding = 4.0f;
			}
			if (cfg.theme20 == true)
			{
				ImGuiStyle* style = &ImGui::GetStyle();
				/*style->WindowPadding = { 10.f , 10.f };
				style->PopupRounding = 0.f;
				style->FramePadding = { 0.f, 0.f };
				style->ItemSpacing = { 10.f, 8.f };
				style->ItemInnerSpacing = { 6.f, 6.f };
				style->TouchExtraPadding = { 0.f, 0.f };
				style->IndentSpacing = 21.f;
				style->ScrollbarSize = 15.f;
				style->GrabMinSize = 8.f;
				style->WindowTitleAlign = ImVec2(0.5f, .0f);
				style->WindowBorderSize = 1.5f;
				style->ChildBorderSize = 1.5f;
				style->PopupBorderSize = 1.5f;
				style->FrameBorderSize = 0.f;
				style->WindowRounding = 1.5f;
				style->ChildRounding = 1.5f;
				style->FrameRounding = 1.5f;
				style->ScrollbarRounding = 1.f;
				style->GrabRounding = 1.f;
				style->ButtonTextAlign = { 0.5f, 0.5f };
				style->DisplaySafeAreaPadding = { 3.f, 3.f };*/
				style->AntiAliasedLines = true;
				style->AntiAliasedFill = true;
				style->CurveTessellationTol = 1.25f;
				style->Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				style->Colors[ImGuiCol_TextDisabled] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				style->Colors[ImGuiCol_WindowBg] = ImVec4(0.01f, 0.03f, 0.10f, 0.94f);
				style->Colors[ImGuiCol_ChildBg] = ImVec4(0.01f, 0.04f, 0.10f, 0.94f);
				style->Colors[ImGuiCol_PopupBg] = ImVec4(0.01f, 0.04f, 0.10f, 0.94f);
				style->Colors[ImGuiCol_Border] = ImVec4(0.02f, 0.08f, 0.23f, 0.94f);
				style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				style->Colors[ImGuiCol_FrameBg] = ImVec4(0.02f, 0.06f, 0.15f, 0.94f);
				style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.01f, 0.04f, 0.10f, 0.94f);
				style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.01f, 0.04f, 0.10f, 0.94f);
				style->Colors[ImGuiCol_TitleBg] = ImVec4(0.05f, 0.12f, 0.28f, 0.94f);
				style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.05f, 0.12f, 0.28f, 0.94f);
				style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05f, 0.12f, 0.28f, 0.94f);
				style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
				style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
				style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
				style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
				style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
				style->Colors[ImGuiCol_CheckMark] = ImVec4(0.01f, 0.01f, 0.1f, 0.1f);
				style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.01f, 0.04f, 0.10f, 0.94f);
				style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.01f, 0.04f, 0.10f, 0.94f);
				style->Colors[ImGuiCol_Button] = ImVec4(0.02f, 0.08f, 0.15f, 0.40f);
				style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
				style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
				style->Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
				style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
				style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
				style->Colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
				style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
				style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
				style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
				style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
				style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
				style->Colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.35f, 0.58f, 0.86f);
				style->Colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
				style->Colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.41f, 0.68f, 1.00f);
				style->Colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
				style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
				style->Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
				style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
				style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
				style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
				style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
				style->Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
				style->Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
				style->Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
				style->Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
				style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
			}
			if (cfg.theme21 == true)
			{
				ImGuiIO& io = ImGui::GetIO();
				ImGuiStyle* style = &ImGui::GetStyle();
				/*style->WindowPadding = ImVec2(15, 15);
				style->WindowRounding = 0.0f;
				style->FramePadding = ImVec2(2, 2);
				style->FrameRounding = 0.0f;*/
				style->ItemSpacing = ImVec2(8, 8);
				style->ItemInnerSpacing = ImVec2(8, 6);
				style->IndentSpacing = 25.0f;
				style->ScrollbarSize = 15.0f;
				style->ScrollbarRounding = 0.0f;
				style->GrabMinSize = 10.0f;
				style->GrabRounding = 0.0f;
				style->TabRounding = 0.f;
				style->ChildRounding = 0.f;
				style->Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
				style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
				style->Colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
				style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
				style->Colors[ImGuiCol_Border] = ImColor(40, 40, 40, 255);
				style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
				style->Colors[ImGuiCol_FrameBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
				style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
				style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
				style->Colors[ImGuiCol_TitleBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
				style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
				style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
				style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);
				style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
				style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
				style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
				style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
				style->Colors[ImGuiCol_CheckMark] = ImColor(150, 0, 0, 255);
				style->Colors[ImGuiCol_SliderGrab] = ImColor(40, 40, 40, 255);
				style->Colors[ImGuiCol_SliderGrabActive] = ImColor(60, 60, 60, 255);
				style->Colors[ImGuiCol_Button] = ImColor(40, 40, 40, 255);
				style->Colors[ImGuiCol_ButtonHovered] = ImColor(50, 50, 50, 255);
				style->Colors[ImGuiCol_ButtonActive] = ImColor(50, 50, 50, 255);
				style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
				style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
				style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
				style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
				style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
				style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
				style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
				style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
				style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
				style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
				style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
				style->WindowTitleAlign.x = 0.50f;
				style->FrameRounding = 2.0f;
			}
			if (cfg.theme22 == true)
			{
				ImGuiStyle& Style = ImGui::GetStyle();
				auto Color = Style.Colors;
				Style.WindowMinSize = ImVec2(700, 450);
				Style.WindowBorderSize = 0;
				Style.ChildRounding = 0;
				Style.FrameRounding = 0;
				Style.ScrollbarRounding = 0;
				Style.GrabRounding = 0;
				Style.PopupRounding = 0;
				Style.WindowRounding = 0;
				Color[ImGuiCol_WindowBg] = ImColor(18, 18, 18, 255);
				Color[ImGuiCol_FrameBg] = ImColor(31, 31, 31, 255);
				Color[ImGuiCol_FrameBgActive] = ImColor(41, 41, 41, 255);
				Color[ImGuiCol_FrameBgHovered] = ImColor(41, 41, 41, 255);
				Color[ImGuiCol_Button] = ImColor(29, 29, 29, 255);
				Color[ImGuiCol_ButtonActive] = ImColor(32, 32, 32, 255);
				Color[ImGuiCol_ButtonHovered] = ImColor(36, 36, 36, 255);
				Color[ImGuiCol_Border] = ImColor(0, 0, 0, 0);
				Color[ImGuiCol_Separator] = ImColor(36, 36, 36, 255);
				Color[ImGuiCol_ResizeGrip] = ImColor(30, 30, 30, 255);
				Color[ImGuiCol_ResizeGripActive] = ImColor(30, 30, 30, 255);
				Color[ImGuiCol_ResizeGripHovered] = ImColor(30, 30, 30, 255);
				Color[ImGuiCol_ChildBg] = ImColor(26, 26, 26, 255);
				Color[ImGuiCol_ScrollbarBg] = ImColor(24, 24, 24, 255);
				Color[ImGuiCol_ScrollbarGrab] = ImColor(24, 24, 24, 255);
				Color[ImGuiCol_ScrollbarGrabActive] = ImColor(24, 24, 24, 255);
				Color[ImGuiCol_ScrollbarGrabActive] = ImColor(24, 24, 24, 255);
				Color[ImGuiCol_Header] = ImColor(39, 39, 39, 255);
				Color[ImGuiCol_HeaderActive] = ImColor(39, 39, 39, 255);
				Color[ImGuiCol_HeaderHovered] = ImColor(39, 39, 39, 255);
				Color[ImGuiCol_CheckMark] = ImColor(255, 255, 255, 255);
			}
			if (cfg.theme23 == true)
			{
			#define AOC_PURPLE 0.549, 0.011, 0.988, 1.f
#define AOC_DARKPURPLE 0.219, 0.035, 0.286, 1.f
#define AOC_BLACK 0.078, 0.078, 0.078, 0.8f
#define AOC_WHITE 1, 1, 1, 1.f
	ImGui::GetStyle().ScaleAllSizes(1);
	ImGui::GetIO().FontGlobalScale = 1;
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowTitleAlign = ImVec2(0.45, 0.5);
	style->WindowPadding = ImVec2(15, 5);
	style->WindowRounding = 8.f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 8.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 20.f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 0.f;
	style->Colors[ImGuiCol_Text] = ImColor(255,255,255);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_Border] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(AOC_WHITE);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_Button] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_Header] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(AOC_BLACK);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(AOC_DARKPURPLE);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(AOC_PURPLE);
	style->Colors[ImGuiCol_TabUnfocused] = ImColor(AOC_BLACK);
	style->Colors[ImGuiCol_TabUnfocusedActive] = ImColor(AOC_BLACK);
			}
               if (cfg.theme24 == true)
			{
                colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 0.95f);
                colors[ImGuiCol_TextDisabled] = ImVec4(0.73f, 0.75f, 0.74f, 1.00f);
                colors[ImGuiCol_WindowBg] = ImVec4(0.39f, 0.00f, 0.63f, 0.11f);
                colors[ImGuiCol_ChildBg] = ImVec4(0.39f, 0.00f, 0.63f, 0.15f);
                colors[ImGuiCol_PopupBg] = ImVec4(0.94f, 0.02f, 1.28f, 0.30f);
                colors[ImGuiCol_Border] = ImVec4(2.45f, 0.00f, 1.01f, 0.30f);
                colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
                colors[ImGuiCol_FrameBg] = ImVec4(0.94f, 0.02f, 1.28f, 0.15f);
                colors[ImGuiCol_FrameBgHovered] = ImVec4(0.94f, 0.02f, 1.28f, 0.25f);
                colors[ImGuiCol_FrameBgActive] = ImVec4(0.94f, 0.02f, 1.28f, 0.07f);
                colors[ImGuiCol_TitleBg] = ImVec4(0.75f, 0.01f, 0.94f, 1.2f);
                colors[ImGuiCol_TitleBgActive] = ImVec4(0.39f, 0.00f, 0.63f, 0.15f);
                colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.39f, 0.00f, 0.63f, 0.15f);
                colors[ImGuiCol_MenuBarBg] = ImVec4(0.34f, 0.16f, 0.16f, 1.00f);
                colors[ImGuiCol_ScrollbarBg] = ImVec4(0.94f, 0.02f, 1.28f, 0.30f);
                colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.94f, 0.02f, 1.28f, 0.30f);
                colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.94f, 0.02f, 1.28f, 0.40f);
                colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.94f, 0.02f, 1.28f, 0.20f);
                colors[ImGuiCol_CheckMark] = ImVec4(2.45f, 0.00f, 0.50f, 0.25f);
                colors[ImGuiCol_SliderGrab] = ImVec4(2.45f, 0.00f, 0.50f, 0.25f);
                colors[ImGuiCol_SliderGrabActive] = ImVec4(2.45f, 0.00f, 0.50f, 0.15f);
                colors[ImGuiCol_Button] = ImVec4(0.39f, 0.00f, 0.63f, 0.0f);
                colors[ImGuiCol_ButtonHovered] = ImVec4(0.39f, 0.00f, 0.63f, 0.15f);
                colors[ImGuiCol_ButtonActive] = ImVec4(0.39f, 0.00f, 0.63f, 0.05f);
                colors[ImGuiCol_Header] = ImVec4(0.71f, 0.39f, 0.39f, 0.54f);
                colors[ImGuiCol_HeaderHovered] = ImVec4(0.84f, 0.66f, 0.66f, 0.65f);
                colors[ImGuiCol_HeaderActive] = ImVec4(0.84f, 0.66f, 0.66f, 0.00f);
                colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
                colors[ImGuiCol_SeparatorHovered] = ImVec4(0.71f, 0.39f, 0.39f, 0.54f);
                colors[ImGuiCol_SeparatorActive] = ImVec4(0.71f, 0.39f, 0.39f, 0.54f);
                colors[ImGuiCol_ResizeGrip] = ImVec4(0.71f, 0.39f, 0.39f, 0.54f);
                colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.84f, 0.66f, 0.66f, 0.66f);
                colors[ImGuiCol_ResizeGripActive] = ImVec4(0.84f, 0.66f, 0.66f, 0.66f);
                colors[ImGuiCol_Tab] = ImVec4(0.71f, 0.39f, 0.39f, 0.54f);
                colors[ImGuiCol_TabHovered] = ImVec4(0.84f, 0.66f, 0.66f, 0.66f);
                colors[ImGuiCol_TabActive] = ImVec4(0.84f, 0.66f, 0.66f, 0.66f);
                colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
                colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
                colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
                colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
                colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
                colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
                colors[ImGuiCol_TextSelectedBg] = ImVec4(2.45f, 0.00f, 1.01f, 0.30f);
                colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
                colors[ImGuiCol_NavHighlight] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
                colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
                colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
                colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
             }
if (cfg.theme25 == true)
			{
colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
                colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
                colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
                colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
                colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
                colors[ImGuiCol_Border] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
                colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
                colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
                colors[ImGuiCol_FrameBgHovered] = ImVec4(0.12f, 0.20f, 0.28f, 1.00f);
                colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.12f, 0.14f, 1.00f);
                colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.12f, 0.14f, 0.65f);
                colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.10f, 0.12f, 1.00f);
                colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
                colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
                colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f);
                colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
                colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.18f, 0.22f, 0.25f, 1.00f);
                colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.21f, 0.31f, 1.00f);
                colors[ImGuiCol_CheckMark] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
                colors[ImGuiCol_SliderGrab] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
                colors[ImGuiCol_SliderGrabActive] = ImVec4(0.37f, 0.61f, 1.00f, 1.00f);
                colors[ImGuiCol_Button] = ImVec4(0.20f, 0.25f, 0.29f, 0.00f);
                colors[ImGuiCol_ButtonHovered] = ImVec4(0.28f, 0.56f, 1.00f, 1.00f);
                colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
                colors[ImGuiCol_Header] = ImVec4(0.20f, 0.25f, 0.29f, 0.55f);
                colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
                colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
                colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
                colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
                colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
                colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
                colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
                colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
                colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
                colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
                colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
                colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
                colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
                colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
                colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
                colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
                colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
                colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
                colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
                colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
                colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
                colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
                colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
         }
if (cfg.theme26 == true)
			{
colors[ImGuiCol_Text] = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
            colors[ImGuiCol_TextDisabled] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
            colors[ImGuiCol_WindowBg] = ImVec4(0.03f, 0.03f, 0.03f, 1.00f);
            colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 0.19f, 0.19f, 0.10f);
            colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
            colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
            colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
            colors[ImGuiCol_FrameBgHovered] = ImVec4(0.37f, 0.14f, 0.14f, 0.67f);
            colors[ImGuiCol_FrameBgActive] = ImVec4(0.39f, 0.20f, 0.20f, 0.67f);
            colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
            colors[ImGuiCol_TitleBgActive] = ImVec4(0.48f, 0.16f, 0.16f, 1.00f);
            colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.48f, 0.16f, 0.16f, 1.00f);
            colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
            colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
            colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
            colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
            colors[ImGuiCol_CheckMark] = ImVec4(0.56f, 0.10f, 0.10f, 1.00f);
            colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.19f, 0.19f, 0.40f);
            colors[ImGuiCol_SliderGrabActive] = ImVec4(0.89f, 0.00f, 0.19f, 1.00f);
            colors[ImGuiCol_Button] = ImVec4(1.00f, 0.19f, 0.19f, 0.00f);
            colors[ImGuiCol_ButtonHovered] = ImVec4(0.80f, 0.17f, 0.00f, 1.00f);
            colors[ImGuiCol_ButtonActive] = ImVec4(0.89f, 0.00f, 0.19f, 1.00f);
            colors[ImGuiCol_Header] = ImVec4(0.33f, 0.35f, 0.36f, 0.53f);
            colors[ImGuiCol_HeaderHovered] = ImVec4(0.76f, 0.28f, 0.44f, 0.67f);
            colors[ImGuiCol_HeaderActive] = ImVec4(0.47f, 0.47f, 0.47f, 0.67f);
            colors[ImGuiCol_Separator] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
            colors[ImGuiCol_SeparatorHovered] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
            colors[ImGuiCol_SeparatorActive] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
            colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.85f);
            colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
            colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
            colors[ImGuiCol_Tab] = ImVec4(0.07f, 0.07f, 0.07f, 0.51f);
            colors[ImGuiCol_TabHovered] = ImVec4(0.86f, 0.23f, 0.43f, 0.67f);
            colors[ImGuiCol_TabActive] = ImVec4(0.19f, 0.19f, 0.19f, 0.57f);
            colors[ImGuiCol_TabUnfocused] = ImVec4(0.05f, 0.05f, 0.05f, 0.90f);
            colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.13f, 0.13f, 0.74f);
            colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
            colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
            colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
            colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
            colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
            colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
            colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
            colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
            colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		}
		if (cfg.theme27 == true)
		{
			colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
			colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
			colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.75f, 0.55f, 0.10f);
			colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
			colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_FrameBg] = ImVec4(0.44f, 0.44f, 0.44f, 0.60f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.57f, 0.57f, 0.57f, 0.70f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(0.76f, 0.76f, 0.76f, 0.80f);
			colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.60f);
			colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
			colors[ImGuiCol_CheckMark] = ImVec4(0.13f, 0.75f, 0.55f, 0.80f);
			colors[ImGuiCol_SliderGrab] = ImVec4(0.13f, 0.75f, 0.75f, 0.80f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
			colors[ImGuiCol_Button] = ImVec4(0.13f, 0.75f, 0.55f, 0.00f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
			colors[ImGuiCol_ButtonActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
			colors[ImGuiCol_Header] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
			colors[ImGuiCol_HeaderActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
			colors[ImGuiCol_Separator] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
			colors[ImGuiCol_SeparatorHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
			colors[ImGuiCol_Tab] = ImVec4(0.13f, 0.75f, 0.55f, 0.80f);
			colors[ImGuiCol_TabHovered] = ImVec4(0.13f, 0.75f, 0.75f, 0.80f);
			colors[ImGuiCol_TabActive] = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
			colors[ImGuiCol_TabUnfocused] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
			colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.36f, 0.36f, 0.36f, 0.54f);
			colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
			colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
			colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
			colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
			colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
			colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
			colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
			colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
			colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
		}
if (cfg.theme28 == true)
{
	colors[ImGuiCol_Text] = ImVec4(0.03f, 0.03f, 0.03f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.93f, 0.93f, 0.93f, 0.98f);
	colors[ImGuiCol_Border] = ImVec4(0.71f, 0.71f, 0.71f, 0.08f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.04f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.71f, 0.71f, 0.71f, 0.55f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.94f, 0.94f, 0.94f, 0.55f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.71f, 0.78f, 0.69f, 0.98f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.82f, 0.78f, 0.78f, 0.51f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.61f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.90f, 0.90f, 0.90f, 0.30f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.92f, 0.92f, 0.92f, 0.78f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.184f, 0.407f, 0.193f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.71f, 0.78f, 0.69f, 0.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.725f, 0.805f, 0.702f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.793f, 0.900f, 0.836f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.71f, 0.78f, 0.69f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.71f, 0.78f, 0.69f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.71f, 0.78f, 0.69f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.45f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_NavHighlight] = colors[ImGuiCol_HeaderHovered];
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
}             
if (cfg.theme29 == true)
{
	ImGui::GetStyle().WindowBorderSize = 0.0f;
	ImGui::GetStyle().FrameBorderSize = 0.0f;
	ImGui::GetStyle().PopupBorderSize = 0.0f;
	ImGui::GetStyle().WindowRounding = 0.0f;
	ImGui::GetStyle().ChildRounding = 0.0f;
	ImGui::GetStyle().FrameRounding = 0.0f;
	ImGui::GetStyle().PopupRounding = 0.0f;
	ImGui::GetStyle().ScrollbarRounding = 0.0f;
	ImGui::GetStyle().GrabRounding = 0.0f;
	ImGui::GetStyle().LogSliderDeadzone = 0.0f;
	ImGui::GetStyle().TabRounding = 0.0f;
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.91f, 0.33f, 0.13f, 1.00f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.05f, 0.52f, 0.13f, 1.00f);
}
		}
		else if (cfg.tab_index == 5)
		{
			ImGui::Text("Developed by Tiny Man");
			ImGui::Text("Discord: Tiny Man#0200");
			ImGui::SameLine();if (ImGui::Button("Copy discord to clipboard")){ImGui::SetClipboardText("Tiny Man#0200");}
			ImGui::Text("Discord: Tiny Man#9899");
			ImGui::SameLine(); if (ImGui::Button("Copy alt discord to clipboard")) { ImGui::SetClipboardText("Tiny Man#9899"); }
			ImGui::Text("Unknown Cheaters discord server: https://discord.gg/4NdrctMGtu");
			ImGui::SameLine(); if (ImGui::Button("Copy UC link to clipboard")) { ImGui::SetClipboardText("https://discord.gg/4NdrctMGtu"); }
			ImGui::Text("Unknown Gamers server: https://discord.gg/dE58HDgQcY");
			ImGui::SameLine(); if (ImGui::Button("Copy UG link to clipboard")) { ImGui::SetClipboardText("https://discord.gg/dE58HDgQcY"); }
			if (ImGui::Button("open discord links"))
			{
				system("start https://discord.gg/4NdrctMGtu");
				system("start https://discord.gg/dE58HDgQcY");
			}
		}
		ImGui::PopFont();
		ImGui::End();
	}
	ImGui::EndFrame();
	DirectX9Interface::pDevice->SetRenderState(D3DRS_ZENABLE, false);
	DirectX9Interface::pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	DirectX9Interface::pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	DirectX9Interface::pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	if (DirectX9Interface::pDevice->BeginScene() >= 0) {
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		DirectX9Interface::pDevice->EndScene();
	}
	HRESULT result = DirectX9Interface::pDevice->Present(NULL, NULL, NULL, NULL);
	if (result == D3DERR_DEVICELOST && DirectX9Interface::pDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
		ImGui_ImplDX9_InvalidateDeviceObjects();
		DirectX9Interface::pDevice->Reset(&DirectX9Interface::pParams);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}
void MainLoop() {
	isTopwin();
	static RECT OldRect;
	ZeroMemory(&DirectX9Interface::Message, sizeof(MSG));

	while (DirectX9Interface::Message.message != WM_QUIT) {
		if (PeekMessage(&DirectX9Interface::Message, OverlayWindow::Hwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&DirectX9Interface::Message);
			DispatchMessage(&DirectX9Interface::Message);
		}
		HWND ForegroundWindow = GetForegroundWindow();
		if (ForegroundWindow == GameVars.gameHWND) {
			HWND TempProcessHwnd = GetWindow(ForegroundWindow, GW_HWNDPREV);
			SetWindowPos(OverlayWindow::Hwnd, TempProcessHwnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		RECT TempRect;
		POINT TempPoint;
		ZeroMemory(&TempRect, sizeof(RECT));
		ZeroMemory(&TempPoint, sizeof(POINT));

		GetClientRect(GameVars.gameHWND, &TempRect);
		ClientToScreen(GameVars.gameHWND, &TempPoint);

		TempRect.left = TempPoint.x;
		TempRect.top = TempPoint.y;
		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = GameVars.gameHWND;

		POINT TempPoint2;
		GetCursorPos(&TempPoint2);
		io.MousePos.x = TempPoint2.x - TempPoint.x;
		io.MousePos.y = TempPoint2.y - TempPoint.y;

		if (GetAsyncKeyState(0x1)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else {
			io.MouseDown[0] = false;
		}

		if (TempRect.left != OldRect.left || TempRect.right != OldRect.right || TempRect.top != OldRect.top || TempRect.bottom != OldRect.bottom) {
			OldRect = TempRect;
			GameVars.ScreenWidth = TempRect.right;
			GameVars.ScreenHeight = TempRect.bottom;
			DirectX9Interface::pParams.BackBufferWidth = GameVars.ScreenWidth;
			DirectX9Interface::pParams.BackBufferHeight = GameVars.ScreenHeight;
			SetWindowPos(OverlayWindow::Hwnd, (HWND)0, TempPoint.x, TempPoint.y, GameVars.ScreenWidth, GameVars.ScreenHeight, SWP_NOREDRAW);
			DirectX9Interface::pDevice->Reset(&DirectX9Interface::pParams);
		}
		Render();
	}
	//ImGui_ImplDX9_Shutdown();
	//ImGui_ImplWin32_Shutdown();
//	ImGui::DestroyContext();
	if (DirectX9Interface::pDevice != NULL) {
		DirectX9Interface::pDevice->EndScene();
		DirectX9Interface::pDevice->Release();
	}
	if (DirectX9Interface::Direct3D9 != NULL) {
		DirectX9Interface::Direct3D9->Release();
	}
	/*DestroyWindow(OverlayWindow::Hwnd);
	UnregisterClass(OverlayWindow::WindowClass.lpszClassName, OverlayWindow::WindowClass.hInstance);*/
}

bool DirectXInit() {
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &DirectX9Interface::Direct3D9))) {
		return false;
	}

	D3DPRESENT_PARAMETERS Params = { 0 };
	Params.Windowed = TRUE;
	Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Params.hDeviceWindow = OverlayWindow::Hwnd;
	Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	Params.BackBufferWidth = GameVars.ScreenWidth;
	Params.BackBufferHeight = GameVars.ScreenHeight;
	Params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	Params.EnableAutoDepthStencil = TRUE;
	Params.AutoDepthStencilFormat = D3DFMT_D16;
	Params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	Params.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	if (FAILED(DirectX9Interface::Direct3D9->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, OverlayWindow::Hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &Params, 0, &DirectX9Interface::pDevice))) {
		DirectX9Interface::Direct3D9->Release();
		return false;
	}

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantTextInput || ImGui::GetIO().WantCaptureKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui_ImplWin32_Init(OverlayWindow::Hwnd);
	ImGui_ImplDX9_Init(DirectX9Interface::pDevice);
	DirectX9Interface::Direct3D9->Release();
	return true;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message) {
	case WM_DESTROY:
		if (DirectX9Interface::pDevice != NULL) {
			DirectX9Interface::pDevice->EndScene();
			DirectX9Interface::pDevice->Release();
		}
		if (DirectX9Interface::Direct3D9 != NULL) {
			DirectX9Interface::Direct3D9->Release();
		}
		PostQuitMessage(0);
		exit(4);
		break;
	case WM_SIZE:
		if (DirectX9Interface::pDevice != NULL && wParam != SIZE_MINIMIZED) {
			ImGui_ImplDX9_InvalidateDeviceObjects();
			DirectX9Interface::pParams.BackBufferWidth = LOWORD(lParam);
			DirectX9Interface::pParams.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = DirectX9Interface::pDevice->Reset(&DirectX9Interface::pParams);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}

void SetupWindow() {
	OverlayWindow::WindowClass = {
		sizeof(WNDCLASSEX), 0, WinProc, 0, 0, nullptr, LoadIcon(nullptr, IDI_APPLICATION), LoadCursor(nullptr, IDC_ARROW), nullptr, nullptr, OverlayWindow::Name, LoadIcon(nullptr, IDI_APPLICATION)
	};

	RegisterClassEx(&OverlayWindow::WindowClass);
	if (GameVars.gameHWND) {
		static RECT TempRect = { NULL };
		static POINT TempPoint;
		GetClientRect(GameVars.gameHWND, &TempRect);
		ClientToScreen(GameVars.gameHWND, &TempPoint);
		TempRect.left = TempPoint.x;
		TempRect.top = TempPoint.y;
		GameVars.ScreenWidth = TempRect.right;
		GameVars.ScreenHeight = TempRect.bottom;
	}
	OverlayWindow::Hwnd = CreateWindowEx(NULL, OverlayWindow::Name, OverlayWindow::Name, WS_POPUP | WS_VISIBLE, GameVars.ScreenLeft, GameVars.ScreenTop, GameVars.ScreenWidth, GameVars.ScreenHeight, NULL, NULL, 0, NULL);
	DwmExtendFrameIntoClientArea(OverlayWindow::Hwnd, &DirectX9Interface::Margin);
	SetWindowLong(OverlayWindow::Hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	//ShowWindow(OverlayWindow::Hwnd, SW_SHOW);
	UpdateWindow(OverlayWindow::Hwnd);
}

bool CreateConsole = false;
void cleanotherservices()
{
	//reload / stop / delete services
	system("sc stop tinyman0200");
	system("sc delete tinymanrc");
	system("sc delete mhyprot2");
	system("sc delete tinymanrr");
}
void loadcurrentconfig()
{
}
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	/*//rename file
	char old_name[] = "oldname";
	char new_name[] = "newname";
	int value;
	value = rename(old_name, new_name);
	*/
	mhyprot::init(); //load driver
	loadcurrentconfig();
	if (cfg.loadconfigonstartup)
	{
	}
	if (cfg.hideconsole == true)
	{
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}
	else if (cfg.hideconsole == false)
	{
		ShowWindow(GetConsoleWindow(), SW_SHOW);
	}
	//cleanotherservices();
	processdetection(); //check for process
	//windowdetection(); //check for rc window
	if(cfg.startupsound == true)
		{
	//PlaySoundA(startup, NULL, SND_ASYNC | SND_MEMORY); // startup sound
		}
	HANDLE handle = CreateMutex(NULL, TRUE, "TinyMan RC v1.4 Rage update"); // check if cheat is running by finding exe name so change TinyMan RC v1.4 Rage update to your exe name
	if (GetLastError() != ERROR_SUCCESS)
	{
		MessageBox(0, "Cheat is already running! press END to close it", "Information", MB_OK | MB_TOPMOST | MB_ICONINFORMATION);
	}
	//system("CLS"); // CLEAR
	GameVars.dwProcessId = GetProcessId(GameVars.dwProcessName);
	/*	if (!GameVars.dwProcessId)
		{
		}*/
	/*if (!mhyprot::init())
	{
		//printf("[!] failed to initialize vulnerable driver\n");
		return -1;
	}*/
	if (!mhyprot::driver_impl::driver_init(false, false))
	{
		//printf("[!] failed to initialize driver properly\n");
		//mhyprot::unload();
		//return -1;
	}
	GameVars.dwProcess_Base = GetProcessBase(GameVars.dwProcessId);
	/*if (!GameVars.dwProcess_Base)
	{
		//printf("[!] failed to get baseadress\n");
	}*/
	//printf("[+] ProcessName: %s ID: (%d) base: %llx\n", GameVars.dwProcessName, GameVars.dwProcessId, GameVars.dwProcess_Base);
	CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(GameCache), nullptr, NULL, nullptr);
	CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(CallAimbot), nullptr, NULL, nullptr);
	/*if (CreateConsole == false)
	{
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}*/
	bool WindowFocus = false;
	while (WindowFocus == false)
	{
		DWORD ForegroundWindowProcessID;
		GetWindowThreadProcessId(GetForegroundWindow(), &ForegroundWindowProcessID);
		if (GetProcessId(GameVars.dwProcessName) == ForegroundWindowProcessID)
		{
			GameVars.gameHWND = GetForegroundWindow();
			RECT TempRect;
			GetWindowRect(GameVars.gameHWND, &TempRect);
			GameVars.ScreenWidth = TempRect.right - TempRect.left;
			GameVars.ScreenHeight = TempRect.bottom - TempRect.top;
			GameVars.ScreenLeft = TempRect.left;
			GameVars.ScreenRight = TempRect.right;
			GameVars.ScreenTop = TempRect.top;
			GameVars.ScreenBottom = TempRect.bottom;
			WindowFocus = true;
		}
	}
	OverlayWindow::Name = RandomString(10).c_str();
	SetupWindow();
	DirectXInit();
	ImGuiIO& io = ImGui::GetIO();
	DefaultFont = io.Fonts->AddFontDefault();
	Verdana = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 16.0f);
	io.Fonts->Build();
	while (TRUE)
	{
		MainLoop();
	}
}
