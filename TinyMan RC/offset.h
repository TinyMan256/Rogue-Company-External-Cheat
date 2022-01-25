#pragma once
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <iostream>
#include <dwmapi.h>
#include  <d3d9.h>
#include  <d3dx9.h>
#include "singleton.h"
#include "vector.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dwmapi.lib")
inline namespace RogueCompany
{
	class Variables : public Singleton<Variables>
	{
	public:
		const char* dwProcessName = "RogueCompany.exe";
		DWORD dwProcessId = NULL;
		uint64_t dwProcess_Base = NULL;
		HWND gameHWND = NULL;
		int actor_count = NULL;
		int ScreenHeight = NULL;
		int ScreenWidth = NULL;
		int ScreenLeft = NULL;
		int ScreenRight = NULL;
		int ScreenTop = NULL;
		int ScreenBottom = NULL;
		float ScreenCenterX = ScreenWidth / 2;
		float ScreenCenterY = ScreenHeight / 2;
		DWORD_PTR game_instance = NULL;
		DWORD_PTR u_world = NULL;
		DWORD_PTR local_player_pawn = NULL;
		DWORD_PTR local_player_array = NULL;
		DWORD_PTR local_player = NULL;
		DWORD_PTR local_player_root = NULL;
		DWORD_PTR local_player_controller = NULL;
		DWORD_PTR local_player_state = NULL;
		DWORD_PTR persistent_level = NULL;
		DWORD_PTR actors = NULL;
	};
#define GameVars RogueCompany::Variables::Get()
	class Offsets : public Singleton<Offsets>
	{
	public:
		DWORD offset_g_names = 0x672d200;
		DWORD offset_u_world = 0x689be48;
		DWORD offset_camera_manager = 0x2b8; // APlayerController -> PlayerCameraManager
		DWORD offset_camera_cache = 0x1aa0; //APlayerCameraManager -> CameraCachePrivate
		DWORD offset_persistent_level = 0x30; //UWorld -> PersistentLevel
		DWORD offset_game_instance = 0x188; //UWorld -> OwningGameInstance
		DWORD offset_local_players_array = 0x38; //UGameInstance -> LocalPlayers
		DWORD offset_player_controller = 0x30; //UPlayer -> PlayerController
		DWORD offset_apawn = 0x2a0;  //APlayerController -> AcknowledgedPawn
		DWORD offset_root_component = 0x130; //AActor -> RootComponent
		DWORD offset_actor_array = 0x98; //UNetConnection -> OwningActor
		DWORD offset_actor_count = 0xa0; //UNetConnection -> MaxPacket
		DWORD offset_player_state = 0x240; //APawn -> PlayerState
		DWORD offset_actor_mesh = 0x280; //ACharacter -> Mesh
		DWORD offset_relative_location = 0x11c; //USceneComponent -> RelativeLocation
		DWORD offset_health = 0x528; //AKSCharacterFoundation -> Health
		DWORD offset_max_health = 0x287c; //AKSCharacter -> CachedMaxHealth
		DWORD offset_player_name = 0x300; // APlayerState -> PlayerNamePrivate
		DWORD BaseAccuracy = 0x68c; // UKSWeaponAsset -> BaseAccuracy
		DWORD bDowned = 0x28b9; // AKSCharacter -> bDowned
		DWORD offset_bKickbackEnabled = 0xaf8; // AKSPlayerController -> bKickbackEnabled
		DWORD bInRagdoll = 0x2e60; // AKSCharacter -> bInRagdoll
		DWORD bCanMoveWhileRevivingOther = 0x2a48; // AKSCharacter -> bCanMoveWhileRevivingOther
		DWORD ping = 0x228; // APlayerState -> Ping
		DWORD r_Team = 0x398; // AKSPlayerState -> r_Team
		DWORD r_TeamNum = 0x220; // AKSTeamState -> r_TeamNum
		DWORD EliminatedState = 0x448; // AKSPlayerState -> EliminatedState
		DWORD TimeDilation = 0x2e8; // AWorldSettings -> TimeDilation
		DWORD ActiveWeaponComponent = 0x22b8; // AKSCharacter -> ActiveWeaponComponent[0xb]
		DWORD WeaponAsset = 0x130; // UKSWeaponComponent -> WeaponAsset
		DWORD bUnlimitedAmmo = 0x3e0; // UKSWeaponAsset -> bUnlimitedAmmo
		DWORD MaxLungeDistance = 0x9b4; //UKSWeaponAsset_Melee -> MaxLungeDistance
		DWORD MeleeSphereRadius = 0x994; //UKSWeaponAsset_Melee -> MeleeSphereRadius
		DWORD Health = 0x528; //AKSCharacterFoundation -> Health
		DWORD bRevealed = 0x12d4; //AKSCharacterBase -> bRevealed
		DWORD bIsSpawnImmune = 0x14f0; //AKSCharacterBase -> bIsSpawnImmune
		DWORD bIgnoreCollisionWithTeammates = 0x4dd; //AKSCharacterFoundation -> bIgnoreCollisionWithTeammates
		DWORD CurrentOverheal = 0xd80; //AKSCharacterBase -> CurrentOverheal
		DWORD offset_last_submit_time = 0x2aC; // AServerStatReplicator -> NumRelevantDeletedActors
		DWORD offset_last_render_time = 0x2b4; // AServerStatReplicator -> NumReplicatedActors
		DWORD offset_actor_id = 0x18;
		DWORD offset_bone_array = 0x478;
		DWORD offset_component_to_world = 0x1c0;
	};
#define GameOffset RogueCompany::Offsets::Get()
}