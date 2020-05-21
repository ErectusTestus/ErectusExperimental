#include "ErectusInclude.h"

bool ThreadCreationState = false;
bool ThreadDestructionQueued = false;
bool ThreadDestructionState = false;
int ThreadDestructionCounter = 0;

bool BufferEntityListThreadActive = false;
bool BufferNPCListThreadActive = false;
bool BufferPlayerListThreadActive = false;
bool WeaponEditorThreadActive = false;
bool LockingThreadActive = false;
bool MultihackThreadActive = false;
bool HarvesterThreadActive = false;
bool KnownRecipeThreadActive = false;

bool PositionSpoofingToggle = false;
bool NoclipToggle = false;

DWORD WINAPI BufferEntityListThread(LPVOID lpParameter)
{
	UNREFERENCED_PARAMETER(lpParameter);

	while (!ThreadDestructionState)
	{
		BufferEntityListCounter++;
		if (BufferEntityListCounter > 60)
		{
			BufferEntityListCounter = 0;
			if (!BufferEntityListUpdated)
			{
				BufferEntityListUpdated = UpdateBufferEntityList();
				if (!BufferEntityListUpdated)
				{
					CustomEntityListDestructionQueued = true;
				}
			}
		}

		if (BufferEntityListDestructionQueued)
		{
			BufferEntityListDestructionQueued = false;
			DeleteBufferEntityList();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	DeleteBufferEntityList();

	BufferEntityListThreadActive = false;

	return 0xBEEF;
}

DWORD WINAPI BufferNPCListThread(LPVOID lpParameter)
{
	UNREFERENCED_PARAMETER(lpParameter);

	while (!ThreadDestructionState)
	{
		BufferNPCListCounter++;
		if (BufferNPCListCounter > 60)
		{
			BufferNPCListCounter = 0;
			if (!BufferNPCListUpdated)
			{
				BufferNPCListUpdated = UpdateBufferNPCList();
				if (!BufferNPCListUpdated)
				{
					CustomNPCListDestructionQueued = true;
				}
			}
		}

		if (BufferNPCListDestructionQueued)
		{
			BufferNPCListDestructionQueued = false;
			DeleteBufferNPCList();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	DeleteBufferNPCList();

	BufferNPCListThreadActive = false;

	return 0xFADE;
}

DWORD WINAPI BufferPlayerListThread(LPVOID lpParameter)
{
	UNREFERENCED_PARAMETER(lpParameter);

	while (!ThreadDestructionState)
	{
		BufferPlayerListCounter++;
		if (BufferPlayerListCounter > 60)
		{
			BufferPlayerListCounter = 0;
			if (!BufferPlayerListUpdated)
			{
				BufferPlayerListUpdated = UpdateBufferPlayerList();
				if (!BufferPlayerListUpdated)
				{
					CustomPlayerListDestructionQueued = true;
				}
			}
		}

		if (BufferPlayerListDestructionQueued)
		{
			BufferPlayerListDestructionQueued = false;
			DeleteBufferPlayerList();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	DeleteBufferPlayerList();

	BufferPlayerListThreadActive = false;

	return 0xFEED;
}

DWORD WINAPI WeaponEditorThread(LPVOID lpParameter)
{
	UNREFERENCED_PARAMETER(lpParameter);

	while (!ThreadDestructionState)
	{
		OldWeaponListCounter++;
		if (OldWeaponListCounter > 60)
		{
			OldWeaponListCounter = 0;
			if (!OldWeaponListUpdated)
			{
				OldWeaponListUpdated = UpdateOldWeaponData();
			}

			if (OldWeaponListUpdated)
			{
				bool RevertWeapons = true;
				if (WeaponEditingEnabled())
				{
					RevertWeapons = false;
				}

				for (int i = 0; i < OldWeaponListSize; i++)
				{
					if (ThreadDestructionState) break;
					else EditWeapon(i, RevertWeapons);
				}
			}

			InfiniteAmmo(CustomWeaponSettings.InfiniteAmmo);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	if (OldWeaponListUpdated)
	{
		for (int i = 0; i < OldWeaponListSize; i++)
		{
			EditWeapon(i, true);
		}
	}

	InfiniteAmmo(false);

	DeleteOldWeaponList();

	WeaponEditorThreadActive = false;

	return 0xDEAD;
}

DWORD WINAPI LockingThread(LPVOID lpParameter)
{
	UNREFERENCED_PARAMETER(lpParameter);

	srand(unsigned int(time(NULL)));

	int FavoritedWeaponCounter = 0;

	DWORD WeaponId = 0;
	BYTE ShotsHit = 1;
	BYTE ShotsFired = 0;

	DWORD64 TargetingPage = 0;
	bool TargetingPageValid = false;

	int SendDamageCounter = 0;
	int SendDamageThreshold = 0;

	int MeleeCounter = 0;
	int MeleeThreshold = 0;

	while (!ThreadDestructionState)
	{
		FavoritedWeaponCounter++;
		if (FavoritedWeaponCounter > 60)
		{
			FavoritedWeaponCounter = 0;
			if (CustomTargetSettings.FavoriteIndex < 12)
			{
				WeaponId = GetFavoritedWeaponId(BYTE(CustomTargetSettings.FavoriteIndex));
			}
			else
			{
				WeaponId = 0;
			}
		}

		if (OverlayForeground && GetAsyncKeyState('T'))
		{
			if (!TargetLockingKeyPressed)
			{
				TargetLockingKeyPressed = true;
			}

			if (TargetLockingCooldown > 0)
			{
				TargetLockingCooldown--;
			}
		}
		else
		{
			if (TargetLockingKeyPressed)
			{
				TargetLockingKeyPressed = false;
			}

			if (TargetLockingCooldown)
			{
				TargetLockingCooldown = 0;
			}

			if (TargetLockingPtr)
			{
				TargetLockingPtr = 0;
			}
		}

		if (TargetLockingPtr)
		{
			DamageRedirection(&TargetingPage, &TargetingPageValid, false, true);

			SendDamageCounter++;
			if (SendDamageCounter > SendDamageThreshold)
			{
				SendDamageCounter = 0;
				SendDamageThreshold = GetRangedInt(CustomTargetSettings.SendDamageMin, CustomTargetSettings.SendDamageMax);
				SendDamage(WeaponId, &ShotsHit, &ShotsFired, 1);
			}
		}
		else
		{
			DamageRedirection(&TargetingPage, &TargetingPageValid, false, false);
			SendDamageThreshold = 0;
		}

		if (CustomMeleeSettings.MeleeEnabled)
		{
			if (OverlayForeground && GetAsyncKeyState('U'))
			{
				MeleeCounter++;
				if (MeleeCounter > MeleeThreshold)
				{
					MeleeCounter = 0;
					MeleeThreshold = GetRangedInt(CustomMeleeSettings.MeleeSpeedMin, CustomMeleeSettings.MeleeSpeedMax);
					MeleeAttack();
				}
			}
			else
			{
				MeleeThreshold = 0;
			}
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	DamageRedirection(&TargetingPage, &TargetingPageValid, true, false);

	if (TargetingPage)
	{
		FreeEx(TargetingPage);
	}

	LockingThreadActive = false;

	return 0xCAFE;
}

DWORD WINAPI MultihackThread(LPVOID lpParameter)
{
	UNREFERENCED_PARAMETER(lpParameter);

	bool PositionSpoofingPress = false;
	bool NoclipPress = false;

	int ClientStateCounter = 0;

	DWORD64 ActorValuePage = 0;
	bool ActorValuePageValid = false;

	int ActorValueDefaultCounter = 0;

	bool OpkPlayersPress = false;
	bool OpkPlayersToggle = false;

	bool OpkNpcsPress = false;
	bool OpkNpcsToggle = false;

	DWORD64 OpkPage = 0;
	bool OpkPageValid = false;

	DWORD64 FreezeApPage = 0;
	bool FreezeApPageValid = false;

	bool LootScrapKeyPress = false;
	bool LootItemsKeyPress = false;

	int LootScrapCounter = 0;
	int LootScrapThreshold = 0;

	int LootItemsCounter = 0;
	int LootItemsThreshold = 0;

	int NukeCodeCounter = 0;
	
	int ChargenCounter = 0;

	while (!ThreadDestructionState)
	{
		if (DoubleKeyPress(VK_CONTROL, 'L', &PositionSpoofingPress))
		{
			if (PositionSpoofingToggle)
			{
				PositionSpoofingToggle = false;
			}
			else
			{
				PositionSpoofingToggle = true;
				if (CustomLocalPlayerSettings.PositionSpoofingEnabled)
				{
					if (CustomLocalPlayerSettings.ClientState)
					{
						SetClientState(2);
					}
				}
			}
		}

		if (!CustomLocalPlayerSettings.PositionSpoofingEnabled)
		{
			PositionSpoofingToggle = false;
		}

		if (DoubleKeyPress(VK_CONTROL, 'Y', &NoclipPress))
		{
			if (NoclipToggle)
			{
				NoclipToggle = false;
			}
			else
			{
				NoclipToggle = true;
				if (CustomLocalPlayerSettings.NoclipEnabled)
				{
					if (CustomLocalPlayerSettings.ClientState)
					{
						SetClientState(2);
					}
				}
			}
		}

		if (!CustomLocalPlayerSettings.NoclipEnabled)
		{
			NoclipToggle = false;
		}

		if (DoubleKeyPress(VK_CONTROL, 'B', &OpkPlayersPress))
		{
			if (OpkPlayersToggle)
			{
				OpkPlayersToggle = false;
			}
			else
			{
				OpkPlayersToggle = true;
			}
		}

		if (DoubleKeyPress(VK_CONTROL, 'N', &OpkNpcsPress))
		{
			if (OpkNpcsToggle)
			{
				OpkNpcsToggle = false;
			}
			else
			{
				OpkNpcsToggle = true;
			}
		}

		if (DoubleKeyPress(VK_CONTROL, 'E', &LootScrapKeyPress))
		{
			if (CustomScrapLooterSettings.ScrapKeybindEnabled)
			{
				if (CheckScrapList())
				{
					LootScrap();
				}
			}
		}

		if (DoubleKeyPress(VK_CONTROL, 'R', &LootItemsKeyPress))
		{
			if (CustomItemLooterSettings.ItemKeybindEnabled)
			{
				if (CheckItemLooterSettings())
				{
					LootItems();
				}
			}
		}

		if (PositionSpoofingToggle || NoclipToggle)
		{
			if (CustomLocalPlayerSettings.AutomaticClientState)
			{
				ClientStateCounter++;
				if (ClientStateCounter > 60)
				{
					ClientStateCounter = 0;
					SetClientState(2);
				}
			}
		}

		PositionSpoofing(PositionSpoofingToggle);

		Noclip(NoclipToggle);

		ActorValue(&ActorValuePage, &ActorValuePageValid, true);

		ActorValueDefaultCounter++;
		if (ActorValueDefaultCounter > 60)
		{
			ActorValueDefaultCounter = 0;
			SetActorValueMaximum(0x000002C2, 100.0f, float(CustomLocalPlayerSettings.Strength), CustomLocalPlayerSettings.StrengthEnabled);
			SetActorValueMaximum(0x000002C3, 100.0f, float(CustomLocalPlayerSettings.Perception), CustomLocalPlayerSettings.PerceptionEnabled);
			SetActorValueMaximum(0x000002C4, 100.0f, float(CustomLocalPlayerSettings.Endurance), CustomLocalPlayerSettings.EnduranceEnabled);
			SetActorValueMaximum(0x000002C5, 100.0f, float(CustomLocalPlayerSettings.Charisma), CustomLocalPlayerSettings.CharismaEnabled);
			SetActorValueMaximum(0x000002C6, 100.0f, float(CustomLocalPlayerSettings.Agility), CustomLocalPlayerSettings.AgilityEnabled);
			SetActorValueMaximum(0x000002C7, 100.0f, float(CustomLocalPlayerSettings.Intelligence), CustomLocalPlayerSettings.IntelligenceEnabled);
			SetActorValueMaximum(0x000002C8, 100.0f, float(CustomLocalPlayerSettings.Luck), CustomLocalPlayerSettings.LuckEnabled);
		}
		
		FreezeActionPoints(&FreezeApPage, &FreezeApPageValid, true);
		
		OnePositionKill(&OpkPage, &OpkPageValid, true);

		if (OpkPageValid)
		{
			if (OpkPlayersToggle)
			{
				if (!CustomOpkSettings.PlayersEnabled)
				{
					OpkPlayersToggle = false;
				}
				else
				{
					SetOpkData(OpkPage, true, true);
				}
			}
			else
			{
				SetOpkData(OpkPage, true, false);
			}

			if (OpkNpcsToggle)
			{
				if (!CustomOpkSettings.NpcsEnabled)
				{
					OpkNpcsToggle = false;
				}
				else
				{
					SetOpkData(OpkPage, false, true);
				}
			}
			else
			{
				SetOpkData(OpkPage, false, false);
			}
		}

		if (CustomNukeCodeSettings.AutomaticNukeCodes)
		{
			NukeCodeCounter++;
			if (NukeCodeCounter > 300)
			{
				NukeCodeCounter = 0;
				GetNukeCode(0x000921AE, AlphaCode);
				GetNukeCode(0x00092213, BravoCode);
				GetNukeCode(0x00092214, CharlieCode);
			}
		}

		if (CustomScrapLooterSettings.ScrapAutomaticLootingEnabled)
		{
			LootScrapCounter++;
			if (LootScrapCounter > LootScrapThreshold)
			{
				LootScrapCounter = 0;
				LootScrapThreshold = GetRangedInt(CustomScrapLooterSettings.ScrapAutomaticSpeedMin, CustomScrapLooterSettings.ScrapAutomaticSpeedMax);
				if (CheckScrapList())
				{
					LootScrap();
				}
			}
		}
		else
		{
			LootScrapThreshold = 0;
		}

		if (CustomItemLooterSettings.ItemAutomaticLootingEnabled)
		{
			LootItemsCounter++;
			if (LootItemsCounter > LootItemsThreshold)
			{
				LootItemsCounter = 0;
				LootItemsThreshold = GetRangedInt(CustomItemLooterSettings.ItemAutomaticSpeedMin, CustomItemLooterSettings.ItemAutomaticSpeedMax);
				if (CheckItemLooterSettings())
				{
					LootItems();
				}
			}
		}
		else
		{
			LootItemsThreshold = 0;
		}
		
		if (CustomChargenSettings.ChargenEditingEnabled)
		{
			ChargenCounter++;
			if (ChargenCounter > 10)
			{
				ChargenCounter = 0;
				ChargenEditing();
			}
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	PositionSpoofing(false);

	Noclip(false);

	ActorValue(&ActorValuePage, &ActorValuePageValid, false);

	if (ActorValuePage)
	{
		FreeEx(ActorValuePage);
	}

	SetActorValueMaximum(0x000002C2, 100.0f, float(CustomLocalPlayerSettings.Strength), false);
	SetActorValueMaximum(0x000002C3, 100.0f, float(CustomLocalPlayerSettings.Perception), false);
	SetActorValueMaximum(0x000002C4, 100.0f, float(CustomLocalPlayerSettings.Endurance), false);
	SetActorValueMaximum(0x000002C5, 100.0f, float(CustomLocalPlayerSettings.Charisma), false);
	SetActorValueMaximum(0x000002C6, 100.0f, float(CustomLocalPlayerSettings.Agility), false);
	SetActorValueMaximum(0x000002C7, 100.0f, float(CustomLocalPlayerSettings.Intelligence), false);
	SetActorValueMaximum(0x000002C8, 100.0f, float(CustomLocalPlayerSettings.Luck), false);

	OnePositionKill(&OpkPage, &OpkPageValid, false);

	if (OpkPage)
	{
		FreeEx(OpkPage);
	}

	FreezeActionPoints(&FreezeApPage, &FreezeApPageValid, false);

	if (FreezeApPage)
	{
		FreeEx(FreezeApPage);
	}

	MultihackThreadActive = false;

	return 0xBEAD;
}

DWORD WINAPI HarvesterThread(LPVOID lpParameter)
{
	UNREFERENCED_PARAMETER(lpParameter);

	bool NPCKeyPress = false;
	bool ContainerKeyPress = false;
	bool FloraKeyPress = false;

	int HarvesterCounter = 0;
	int HarvesterThreshold = 0;

	while (!ThreadDestructionState)
	{
		if (DoubleKeyPress(VK_CONTROL, VK_OEM_COMMA, &NPCKeyPress))
		{
			if (NPCLooterSettings.EntityLooterEnabled)
			{
				NPCLooterSettings.EntityLooterEnabled = false;
			}
			else
			{
				NPCLooterSettings.EntityLooterEnabled = true;
			}
		}

		if (DoubleKeyPress(VK_CONTROL, VK_OEM_PERIOD, &ContainerKeyPress))
		{
			if (ContainerLooterSettings.EntityLooterEnabled)
			{
				ContainerLooterSettings.EntityLooterEnabled = false;
			}
			else
			{
				ContainerLooterSettings.EntityLooterEnabled = true;
			}
		}

		if (DoubleKeyPress(VK_CONTROL, 'P', &FloraKeyPress))
		{
			if (CustomHarvesterSettings.HarvesterEnabled)
			{
				CustomHarvesterSettings.HarvesterEnabled = false;
			}
			else
			{
				CustomHarvesterSettings.HarvesterEnabled = true;
			}
		}

		HarvesterCounter++;
		if (HarvesterCounter > HarvesterThreshold)
		{
			HarvesterCounter = 0;
			HarvesterThreshold = GetRangedInt(12, 36);
			Harvester();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	HarvesterThreadActive = false;

	return 0xDEAF;
}

DWORD WINAPI KnownRecipeThread(LPVOID lpParameter)
{
	UNREFERENCED_PARAMETER(lpParameter);

	int KnownRecipeCounter = 0;
	bool KnownRecipeListUpdated = false;

	while (!ThreadDestructionState)
	{
		if (KnownRecipeListUpdated)
		{
			KnownRecipeCounter++;
			if (KnownRecipeCounter > 300)
			{
				KnownRecipeCounter = 0;
				KnownRecipeListUpdated = UpdateKnownRecipes();
			}
		}
		else
		{
			KnownRecipeCounter++;
			if (KnownRecipeCounter > 60)
			{
				KnownRecipeCounter = 0;
				KnownRecipeListUpdated = UpdateKnownRecipes();
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	KnownRecipeThreadActive = false;

	return 0xCADE;
}

bool CreateProcessThreads()
{
	if (ThreadDestructionQueued)
	{
		return false;
	}

	if (ThreadDestructionState)
	{
		return false;
	}

	if (ThreadDestructionCounter)
	{
		return false;
	}

	if (!BufferEntityListThreadActive)
	{
		BufferEntityListThreadActive = CloseHandle(CreateThread(NULL, 0, BufferEntityListThread, NULL, 0, NULL));
		if (!BufferEntityListThreadActive)
		{
			ThreadDestructionQueued = true;
			return false;
		}
	}

	if (!BufferNPCListThreadActive)
	{
		BufferNPCListThreadActive = CloseHandle(CreateThread(NULL, 0, BufferNPCListThread, NULL, 0, NULL));
		if (!BufferNPCListThreadActive)
		{
			ThreadDestructionQueued = true;
			return false;
		}
	}

	if (!BufferPlayerListThreadActive)
	{
		BufferPlayerListThreadActive = CloseHandle(CreateThread(NULL, 0, BufferPlayerListThread, NULL, 0, NULL));
		if (!BufferPlayerListThreadActive)
		{
			ThreadDestructionQueued = true;
			return false;
		}
	}

	if (!WeaponEditorThreadActive)
	{
		WeaponEditorThreadActive = CloseHandle(CreateThread(NULL, 0, WeaponEditorThread, NULL, 0, NULL));
		if (!WeaponEditorThreadActive)
		{
			ThreadDestructionQueued = true;
			return false;
		}
	}

	if (!LockingThreadActive)
	{
		LockingThreadActive = CloseHandle(CreateThread(NULL, 0, LockingThread, NULL, 0, NULL));
		if (!LockingThreadActive)
		{
			ThreadDestructionQueued = true;
			return false;
		}
	}

	if (!MultihackThreadActive)
	{
		MultihackThreadActive = CloseHandle(CreateThread(NULL, 0, MultihackThread, NULL, 0, NULL));
		if (!MultihackThreadActive)
		{
			ThreadDestructionQueued = true;
			return false;
		}
	}

	if (!HarvesterThreadActive)
	{
		HarvesterThreadActive = CloseHandle(CreateThread(NULL, 0, HarvesterThread, NULL, 0, NULL));
		if (!HarvesterThreadActive)
		{
			ThreadDestructionQueued = true;
			return false;
		}
	}

	if (!KnownRecipeThreadActive)
	{
		KnownRecipeThreadActive = CloseHandle(CreateThread(NULL, 0, KnownRecipeThread, NULL, 0, NULL));
		if (!KnownRecipeThreadActive)
		{
			ThreadDestructionQueued = true;
			return false;
		}
	}

	return true;
}

bool ThreadDestruction()
{
	ThreadDestructionState = true;

	if (BufferEntityListThreadActive)
	{
		return false;
	}

	if (BufferNPCListThreadActive)
	{
		return false;
	}

	if (BufferPlayerListThreadActive)
	{
		return false;
	}

	if (WeaponEditorThreadActive)
	{
		return false;
	}

	if (LockingThreadActive)
	{
		return false;
	}

	if (MultihackThreadActive)
	{
		return false;
	}

	if (HarvesterThreadActive)
	{
		return false;
	}

	if (KnownRecipeThreadActive)
	{
		return false;
	}

	ThreadCreationState = false;
	ThreadDestructionQueued = false;
	ThreadDestructionState = false;
	ThreadDestructionCounter = 0;

	return true;
}
