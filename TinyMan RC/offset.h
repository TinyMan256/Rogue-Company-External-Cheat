#pragma once
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <iostream>
#include <dwmapi.h>
#include  <d3d9.h>
#include  <d3dx9.h>
#include "other.h"
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dwmapi.lib")
          // ====================== goto https://rc.dumps.host/ to update offsets =======================
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
		DWORD offset_g_names = 0x689c100; // GNames
		DWORD offset_u_world = 0x6a0adf8; // GWorld
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
		DWORD offset_max_health = 0x2894; //AKSCharacter -> CachedMaxHealth
		DWORD offset_player_name = 0x300; // APlayerState -> PlayerNamePrivate
		DWORD BaseAccuracy = 0x68c; // UKSWeaponAsset -> BaseAccuracy
		DWORD bDowned = 0x28c1; // AKSCharacter -> bDowned
		DWORD offset_bKickbackEnabled = 0xaf8; // AKSPlayerController -> bKickbackEnabled
		DWORD bInRagdoll = 0x2e68; // AKSCharacter -> bInRagdoll
		DWORD bCanMoveWhileRevivingOther = 0x2a50; // AKSCharacter -> bCanMoveWhileRevivingOther
		DWORD ping = 0x228; // APlayerState -> Ping
		DWORD r_Team = 0x398; // AKSPlayerState -> r_Team
		DWORD r_TeamNum = 0x220; // AKSTeamState -> r_TeamNum
		DWORD EliminatedState = 0x448; // AKSPlayerState -> EliminatedState
		DWORD TimeDilation = 0x2e8; // AWorldSettings -> TimeDilation
		DWORD ActiveWeaponComponent = 0x22d0; // AKSCharacter -> ActiveWeaponComponent[0xb]
		DWORD WeaponAsset = 0x130; // UKSWeaponComponent -> WeaponAsset
		DWORD bUnlimitedAmmo = 0x3e0; // UKSWeaponAsset -> bUnlimitedAmmo
		DWORD MaxLungeDistance = 0x9b4; //UKSWeaponAsset_Melee -> MaxLungeDistance
		DWORD MeleeSphereRadius = 0x994; //UKSWeaponAsset_Melee -> MeleeSphereRadius
		DWORD bRevealed = 0x12dc; //AKSCharacterBase -> bRevealed
		DWORD bIsSpawnImmune = 0x14f8; //AKSCharacterBase -> bIsSpawnImmune
		DWORD bIgnoreCollisionWithTeammates = 0x4dd; //AKSCharacterFoundation -> bIgnoreCollisionWithTeammates
		DWORD CurrentOverheal = 0xd80; //AKSCharacterBase -> CurrentOverheal
		DWORD offset_last_submit_time = 0x2ac; // AServerStatReplicator -> NumRelevantDeletedActors
		DWORD offset_last_render_time = 0x2b4; // AServerStatReplicator -> NumReplicatedActors
		DWORD offset_actor_id = 0x18; // actor id
		DWORD offset_bone_array = 0x478; // bone array
		DWORD offset_component_to_world = 0x1c0; // component to world
		DWORD CurrentQuickMeleeWeapon = 0x2210; //AKSCharacter -> CurrentQuickMeleeWeapon
		DWORD MeleeWeaponAsset = 0x868; //AKSWeapon_Melee -> MeleeWeaponAsset
		DWORD BaseEyeHeight = 0x22c; //APawn -> BaseEyeHeight
		DWORD AmmoInClip = 0x4a4; //AKSWeapon -> AmmoInClip
		DWORD ClipSize = 0x4a8; //AKSWeapon -> ClipSize
		DWORD DefaultFOV = 0x238; //APlayerCameraManager -> DefaultFOV
		DWORD NoSpread = 0x68c; //UKSWeaponAsset -> BaseAccuracy
		DWORD firemodetype = 0x370; //UKSWeaponAsset -> FireModeType
		DWORD CurrentRevealColor = 0x12e0; //AKSCharacterBase -> CurrentRevealColor
		DWORD CharacterMovement = 0x288; //ACharacter -> CharacterMovement
		DWORD KSCharacterOwner = 0x858; //UKSCharacterMovementComponent -> KSCharacterOwner
		DWORD SpawnImmuneOutlineColorEnemy = 0x12f8; //AKSCharacterBase -> SpawnImmuneOutlineColorEnemy
		DWORD PreFireTime = 0x380; //UKSWeaponAsset -> PreFireTime
		DWORD RoundsPerBurst = 0x374; //UKSWeaponAsset -> RoundsPerBurst
		DWORD AimDownSightsFov = 0x5c8; //UKSWeaponAsset -> AimDownSightsFov
		DWORD PostReloadTime = 0x3c8; //UKSWeaponAsset -> PostReloadTime
		DWORD PreReloadTime = 0x3c4; //UKSWeaponAsset -> PreReloadTime
		DWORD trollnoreload = 0x3b8; //UKSWeaponAsset -> bCanEverReload
		DWORD trollnofire = 0x338; //UKSWeaponAsset -> bCanEverFire
		DWORD aimovershoulder = 0x5b4; //UKSWeaponAsset -> bCanEverAimOverShoulder
		DWORD aimdownsights = 0x5bc; //UKSWeaponAsset -> bCanEverAimDownSights
		DWORD ReloadType = 0x3c0; //UKSWeaponAsset -> ReloadType
		DWORD DamageCategory = 0x40; //UKSDamageTypeBase -> DamageCategory
		DWORD ReticleType = 0x3f1; //UKSWeaponAsset -> ReticleType
		DWORD WeaponEquipType = 0x288; //UKSWeaponAsset -> WeaponEquipType
		DWORD WalkSpeedModifier = 0x710; //UKSWeaponAsset -> WeaponEquipType
		DWORD ClipSize2 = 0x3bc; //UKSWeaponAsset -> ClipSize
		DWORD HeadDamageAmount = 0x53c; //UKSWeaponAsset -> HeadDamageAmount
		DWORD DamageAmount = 0x540; //UKSWeaponAsset -> DamageAmount
		DWORD LimbDamageAmount = 0x544; //UKSWeaponAsset -> LimbDamageAmount
		DWORD BurstShotIndex = 0x45c; //AKSWeapon -> BurstShotIndex
		DWORD PostFireTime = 0x38c; //UKSWeaponAsset -> PostFireTime
		DWORD AltPostFireTime = 0x390; //UKSWeaponAsset -> AltPostFireTime
		DWORD PostFireForgivenessTime = 0x394; //UKSWeaponAsset -> PostFireForgivenessTime
		DWORD InitialPostFireTime = 0x3a4; //UKSWeaponAsset -> InitialPostFireTime
		DWORD FinalPostFireTime = 0x3a8; //UKSWeaponAsset -> FinalPostFireTime
		DWORD PostFireChargeTime = 0x3ac; //UKSWeaponAsset -> PostFireChargeTime
		DWORD PostFireDecayTime = 0x3b0; //UKSWeaponAsset -> PostFireDecayTime
		DWORD PostFireDecayDelay = 0x3b4; //UKSWeaponAsset -> PostFireDecayDelay
	};
#define GameOffset RogueCompany::Offsets::Get()
}