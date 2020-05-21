#include "ErectusInclude.h"

bool ImGuiContextCreated = false;
bool ImGuiD3D9Initialized = false;
bool ImGuiWin32Initialized = false;
bool ImGuiInitialized = false;

POINT PointerPosition = { 0, 0 };
ImVec2 PointerOrigin = { 0.0f, 0.0f };
bool PointerDrag = false;

DWORD64 GetPtrResult = 0;
DWORD64 GetAddressResult = 0;

bool SwapperSourceToggle = false;
bool SwapperDestinationToggle = false;

bool TransferSourceToggle = false;
bool TransferDestinationToggle = false;

int AlphaCode[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int BravoCode[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int CharlieCode[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

char **FavoritedWeaponsArray = nullptr;

bool DragMenu()
{
	if (!GetCursorPos(&PointerPosition)) return false;

	WindowPosition[0] = PointerPosition.x - int(PointerOrigin.x);
	WindowPosition[1] = PointerPosition.y - int(PointerOrigin.y);

	int ScreenX = GetSystemMetrics(SM_CXSCREEN);
	int ScreenY = GetSystemMetrics(SM_CYSCREEN);

	if (WindowPosition[0] < 0)
	{
		WindowPosition[0] = 0;
	}

	if (WindowPosition[1] < 0)
	{
		WindowPosition[1] = 0;
	}

	if (WindowPosition[0] > (ScreenX - WindowSize[0]))
	{
		WindowPosition[0] = (ScreenX - WindowSize[0]);
	}

	if (WindowPosition[1] > (ScreenY - WindowSize[1]))
	{
		WindowPosition[1] = (ScreenY - WindowSize[1]);
	}

	return MoveWindow(WindowHwnd, WindowPosition[0], WindowPosition[1], WindowSize[0], WindowSize[1], FALSE);
}

void ProcessMenu()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2(float(WindowSize[0]), float(WindowSize[1])));
	ImGui::SetNextWindowCollapsed(false);

	bool AllowDrag = true;
	if (ImGui::Begin("Erectus - Process Menu", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::MenuItem("Exit"))
			{
				Close();
			}

			if (ProcessSelected)
			{
				if (ImGui::MenuItem("Overlay Menu"))
				{
					SetOverlayMenu();
				}

				if (ImGui::MenuItem("Overlay"))
				{
					SetOverlayPosition(false, true);
				}
			}
			else
			{
				ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
				ImGui::MenuItem("Overlay Menu");
				ImGui::MenuItem("Overlay");
				ImGui::PopStyleVar();
				ImGui::PopItemFlag();
			}

			ImGui::EndMenuBar();
		}

		ImGui::SetNextItemWidth(float(WindowSize[0]) - 16.0f);
		if (ImGui::BeginCombo("###ProcessList", ProcessList[ProcessIndex]))
		{
			if (!ProcessListUpdated)
			{
				ProcessListUpdated = true;
				if (!UpdateProcessList())
				{
					ResetProcessData(true, 1);
				}
			}

			for (int i = 0; i < ProcessListSize; i++)
			{
				if (ImGui::Selectable(ProcessList[i]))
				{
					ProcessIndex = i;
					if (ProcessIndex)
					{
						ProcessSelected = ProcessValid(ProcessIdList[ProcessIndex]);
						if (!ProcessSelected)
						{
							ResetProcessData(false, 1);
						}
					}
				}
			}

			ImGui::EndCombo();
			AllowDrag = false;
		}
		else
		{
			if (ProcessListUpdated)
			{
				ProcessListUpdated = false;
			}
		}

		ImGui::Separator();
		switch (ProcessErrorId)
		{
		case 0:
			ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), ProcessError);
			break;
		case 1:
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), ProcessError);
			break;
		case 2:
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), ProcessError);
			break;
		default:
			ImGui::Text(ProcessError);
			break;
		}

		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::Columns(2);
		ImGui::Separator();
		ImGui::Text("Overlay Menu Keybind");
		ImGui::NextColumn();
		ImGui::Text("CTRL+ENTER");
		ImGui::NextColumn();
		ImGui::Separator();
		ImGui::Text("ImGui (D3D9) FPS");
		ImGui::NextColumn();
		ImGui::Text("%.1f", ImGui::GetIO().Framerate);
		ImGui::NextColumn();
		ImGui::Separator();
		ImGui::Text("PID (Process Id)");
		ImGui::NextColumn();
		ImGui::Text("%lu", Pid);
		ImGui::NextColumn();
		ImGui::Separator();
		ImGui::Text("HWND (Window)");
		ImGui::NextColumn();
		ImGui::Text("%p", Hwnd);
		ImGui::NextColumn();
		ImGui::Separator();
		ImGui::Text("Base Address");
		ImGui::NextColumn();
		ImGui::Text("%016llX", Exe);
		ImGui::NextColumn();
		ImGui::Separator();
		ImGui::Text("HANDLE");
		ImGui::NextColumn();
		ImGui::Text("%p", Handle);
		ImGui::Columns(1);
		ImGui::Separator();
		ImGui::PopItemFlag();

		if (ImGui::IsMouseDragging(0) && AllowDrag)
		{
			if (!PointerDrag)
			{
				PointerOrigin = ImGui::GetMousePos();
				PointerDrag = true;
			}
		}
		else
		{
			if (PointerDrag)
			{
				PointerOrigin = { 0.0f, 0.0f };
				PointerDrag = false;
			}
		}

		if (PointerDrag)
		{
			DragMenu();
		}
	}

	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

void ButtonToggle(const char *Label, bool *State)
{
	if (*State)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 0.3f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.0f, 0.4f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 1.0f, 0.0f, 0.5f));
		if (ImGui::Button(Label, ImVec2(224.0f, 0.0f))) *State = false;
		ImGui::PopStyleColor(3);
	}
	else
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.3f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.4f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
		if (ImGui::Button(Label, ImVec2(224.0f, 0.0f))) *State = true;
		ImGui::PopStyleColor(3);
	}
}

void LargeButtonToggle(const char *Label, bool *State)
{
	if (*State)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 0.3f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.0f, 0.4f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 1.0f, 0.0f, 0.5f));
		if (ImGui::Button(Label, ImVec2(451.0f, 0.0f))) *State = false;
		ImGui::PopStyleColor(3);
	}
	else
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.3f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.4f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
		if (ImGui::Button(Label, ImVec2(451.0f, 0.0f))) *State = true;
		ImGui::PopStyleColor(3);
	}
}

void SmallButtonToggle(const char *Label, bool *State)
{
	if (*State)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 0.3f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.0f, 0.4f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 1.0f, 0.0f, 0.5f));
		if (ImGui::Button(Label, ImVec2(110.0f, 0.0f))) *State = false;
		ImGui::PopStyleColor(3);
	}
	else
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.3f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.4f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
		if (ImGui::Button(Label, ImVec2(110.0f, 0.0f))) *State = true;
		ImGui::PopStyleColor(3);
	}
}

void OverlayMenu()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2(float(WindowSize[0]), float(WindowSize[1])));
	ImGui::SetNextWindowCollapsed(false);

	bool AllowDrag = true;
	if (ImGui::Begin("Erectus - Overlay Menu", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysVerticalScrollbar))
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::MenuItem("Exit"))
			{
				Close();
			}

			if (ImGui::MenuItem("Process Menu"))
			{
				SetProcessMenu();
			}

			if (ImGui::MenuItem("Overlay"))
			{
				if (!SetOverlayPosition(false, true))
				{
					SetProcessMenu();
				}
			}

			ImGui::EndMenuBar();
		}

		if (ImGui::BeginTabBar("###OverlayMenuTabBar", ImGuiTabBarFlags_None))
		{
			if (ImGui::BeginTabItem("ESP###ESPTab"))
			{
				if (ImGui::CollapsingHeader("Player ESP Settings"))
				{
					ButtonToggle("Player ESP Enabled", &PlayerSettings.Enabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###PlayerSettingsEnabledDistance", &PlayerSettings.EnabledDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&PlayerSettings.EnabledDistance, 0, 3000);

					ButtonToggle("Draw Living Players", &PlayerSettings.DrawAlive);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::ColorEdit3("###PlayerSettingsAliveColor", PlayerSettings.AliveColor);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(PlayerSettings.AliveColor);

					ButtonToggle("Draw Downed Players", &PlayerSettings.DrawDowned);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::ColorEdit3("###PlayerSettingsDownedColor", PlayerSettings.DownedColor);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(PlayerSettings.DownedColor);

					ButtonToggle("Draw Dead Players", &PlayerSettings.DrawDead);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::ColorEdit3("###PlayerSettingsDeadColor", PlayerSettings.DeadColor);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(PlayerSettings.DeadColor);

					ButtonToggle("Draw Unknown Players", &PlayerSettings.DrawUnknown);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::ColorEdit3("###PlayerSettingsUnknownColor", PlayerSettings.UnknownColor);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(PlayerSettings.UnknownColor);

					ButtonToggle("Draw Enabled Players", &PlayerSettings.DrawEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###PlayerSettingsEnabledAlpha", &PlayerSettings.EnabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&PlayerSettings.EnabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Disabled Players", &PlayerSettings.DrawDisabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###PlayerSettingsDisabledAlpha", &PlayerSettings.DisabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&PlayerSettings.DisabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Named Players", &PlayerSettings.DrawNamed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Draw Unnamed Players", &PlayerSettings.DrawUnnamed);

					ButtonToggle("Show Player Name", &PlayerSettings.ShowName);
					ImGui::SameLine(235.0f);
					ButtonToggle("Show Player Distance", &PlayerSettings.ShowDistance);

					ButtonToggle("Show Player Health", &PlayerSettings.ShowHealth);
					ImGui::SameLine(235.0f);
					ButtonToggle("Show Dead Player Health", &PlayerSettings.ShowDeadHealth);

					ButtonToggle("Player Text Shadowed", &PlayerSettings.TextShadowed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Player Text Centered", &PlayerSettings.TextCentered);
				}

				if (ImGui::CollapsingHeader("NPC ESP Settings"))
				{
					ButtonToggle("NPC ESP Enabled", &NpcSettings.Enabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###NpcSettingsEnabledDistance", &NpcSettings.EnabledDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&NpcSettings.EnabledDistance, 0, 3000);

					ButtonToggle("Draw Living NPCs", &NpcSettings.DrawAlive);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::ColorEdit3("###NpcSettingsAliveColor", NpcSettings.AliveColor);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(NpcSettings.AliveColor);

					ButtonToggle("Draw Downed NPCs", &NpcSettings.DrawDowned);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::ColorEdit3("###NpcSettingsDownedColor", NpcSettings.DownedColor);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(NpcSettings.DownedColor);

					ButtonToggle("Draw Dead NPCs", &NpcSettings.DrawDead);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::ColorEdit3("###NpcSettingsDeadColor", NpcSettings.DeadColor);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(NpcSettings.DeadColor);

					ButtonToggle("Draw Unknown NPCs", &NpcSettings.DrawUnknown);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::ColorEdit3("###NpcSettingsUnknownColor", NpcSettings.UnknownColor);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(NpcSettings.UnknownColor);

					ButtonToggle("Draw Enabled NPCs", &NpcSettings.DrawEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###NpcSettingsEnabledAlpha", &NpcSettings.EnabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&NpcSettings.EnabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Disabled NPCs", &NpcSettings.DrawDisabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###NpcSettingsDisabledAlpha", &NpcSettings.DisabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&NpcSettings.DisabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Named NPCs", &NpcSettings.DrawNamed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Draw Unnamed NPCs", &NpcSettings.DrawUnnamed);

					ButtonToggle("Show NPC Name", &NpcSettings.ShowName);
					ImGui::SameLine(235.0f);
					ButtonToggle("Show NPC Distance", &NpcSettings.ShowDistance);

					ButtonToggle("Show NPC Health", &NpcSettings.ShowHealth);
					ImGui::SameLine(235.0f);
					ButtonToggle("Show Dead NPC Health", &NpcSettings.ShowDeadHealth);

					ButtonToggle("NPC Text Shadowed", &NpcSettings.TextShadowed);
					ImGui::SameLine(235.0f);
					ButtonToggle("NPC Text Centered", &NpcSettings.TextCentered);

					ButtonToggle("Always Draw Living 1* NPCs", &CustomLegendarySettings.OverrideLivingOneStar);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::ColorEdit3("###LivingOneStarColor", CustomLegendarySettings.LivingOneStarColor);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(CustomLegendarySettings.LivingOneStarColor);

					ButtonToggle("Always Draw Dead 1* NPCs", &CustomLegendarySettings.OverrideDeadOneStar);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::ColorEdit3("###DeadOneStarColor", CustomLegendarySettings.DeadOneStarColor);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(CustomLegendarySettings.DeadOneStarColor);

					ButtonToggle("Always Draw Living 2* NPCs", &CustomLegendarySettings.OverrideLivingTwoStar);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::ColorEdit3("###LivingTwoStarColor", CustomLegendarySettings.LivingTwoStarColor);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(CustomLegendarySettings.LivingTwoStarColor);

					ButtonToggle("Always Draw Dead 2* NPCs", &CustomLegendarySettings.OverrideDeadTwoStar);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::ColorEdit3("###DeadTwoStarColor", CustomLegendarySettings.DeadTwoStarColor);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(CustomLegendarySettings.DeadTwoStarColor);

					ButtonToggle("Always Draw Living 3* NPCs", &CustomLegendarySettings.OverrideLivingThreeStar);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::ColorEdit3("###LivingThreeStarColor", CustomLegendarySettings.LivingThreeStarColor);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(CustomLegendarySettings.LivingThreeStarColor);

					ButtonToggle("Always Draw Dead 3* NPCs", &CustomLegendarySettings.OverrideDeadThreeStar);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::ColorEdit3("###DeadThreeStarColor", CustomLegendarySettings.DeadThreeStarColor);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(CustomLegendarySettings.DeadThreeStarColor);
					
					LargeButtonToggle("Hide NPCs in the Settler Faction", &CustomExtraNPCSettings.HideSettlerFaction);
					LargeButtonToggle("Hide NPCs in the Crater Raider Faction", &CustomExtraNPCSettings.HideCraterRaiderFaction);
					LargeButtonToggle("Hide NPCs in the Diehards Faction", &CustomExtraNPCSettings.HideDieHardFaction);
					LargeButtonToggle("Hide NPCs in the Secret Service Faction", &CustomExtraNPCSettings.HideSecretServiceFaction);

					LargeButtonToggle("NPC Blacklist Enabled", &CustomExtraNPCSettings.UseNPCBlacklist);
					if (ImGui::CollapsingHeader("NPC Blacklist"))
					{
						for (int i = 0; i < 64; i++)
						{
							char NPCBlacklistEnabledText[sizeof("NPC Blacklist: 63")];
							char NPCBlacklistLabelText[sizeof("###NPCBlacklist63")];
							sprintf_s(NPCBlacklistEnabledText, "NPC Blacklist: %d", i);
							sprintf_s(NPCBlacklistLabelText, "###NPCBlacklist%d", i);
							ButtonToggle(NPCBlacklistEnabledText, &CustomExtraNPCSettings.NPCBlacklistEnabled[i]);
							ImGui::SameLine(235.0f);
							char FormidText[sizeof("00000000")];
							sprintf_s(FormidText, "%08lX", CustomExtraNPCSettings.NPCBlacklist[i]);
							ImGui::SetNextItemWidth(224.0f);
							ImGui::InputText(NPCBlacklistLabelText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
							if (ImGui::IsItemActive()) AllowDrag = false;
							sscanf_s(FormidText, "%08lX", &CustomExtraNPCSettings.NPCBlacklist[i]);
						}
					}
				}

				if (ImGui::CollapsingHeader("Container ESP Settings"))
				{
					ButtonToggle("Container ESP Enabled", &ContainerSettings.Enabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###ContainerSettingsEnabledDistance", &ContainerSettings.EnabledDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&ContainerSettings.EnabledDistance, 0, 3000);

					ImGui::SetNextItemWidth(451.0f);
					ImGui::ColorEdit3("###ContainerSettingsColor", ContainerSettings.Color);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(ContainerSettings.Color);

					ButtonToggle("Draw Enabled Containers", &ContainerSettings.DrawEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###ContainerSettingsEnabledAlpha", &ContainerSettings.EnabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&ContainerSettings.EnabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Disabled Containers", &ContainerSettings.DrawDisabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###ContainerSettingsDisabledAlpha", &ContainerSettings.DisabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&ContainerSettings.DisabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Named Containers", &ContainerSettings.DrawNamed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Draw Unnamed Containers", &ContainerSettings.DrawUnnamed);

					ButtonToggle("Show Container Name", &ContainerSettings.ShowName);
					ImGui::SameLine(235.0f);
					ButtonToggle("Show Container Distance", &ContainerSettings.ShowDistance);

					ButtonToggle("Container Text Shadowed", &ContainerSettings.TextShadowed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Container Text Centered", &ContainerSettings.TextCentered);

					if (ImGui::CollapsingHeader("Container Whitelist Settings"))
					{
						for (int i = 0; i < 32; i++)
						{
							char WhitelistedText[sizeof("Container Whitelist Slot: 31")];
							char WhitelistText[sizeof("###ContainerWhitelist31")];
							sprintf_s(WhitelistedText, "Container Whitelist Slot: %d", i);
							sprintf_s(WhitelistText, "###ContainerWhitelist%d", i);
							ButtonToggle(WhitelistedText, &ContainerSettings.Whitelisted[i]);
							ImGui::SameLine(235.0f);
							char FormidText[sizeof("00000000")];
							sprintf_s(FormidText, "%08lX", ContainerSettings.Whitelist[i]);
							ImGui::SetNextItemWidth(224.0f);
							ImGui::InputText(WhitelistText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
							if (ImGui::IsItemActive()) AllowDrag = false;
							sscanf_s(FormidText, "%08lX", &ContainerSettings.Whitelist[i]);
						}
					}
				}

				if (ImGui::CollapsingHeader("Junk ESP Settings"))
				{
					ButtonToggle("Junk ESP Enabled", &JunkSettings.Enabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###JunkSettingsEnabledDistance", &JunkSettings.EnabledDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&JunkSettings.EnabledDistance, 0, 3000);

					ImGui::SetNextItemWidth(451.0f);
					ImGui::ColorEdit3("###JunkSettingsColor", JunkSettings.Color);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(JunkSettings.Color);

					ButtonToggle("Draw Enabled Junk", &JunkSettings.DrawEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###JunkSettingsEnabledAlpha", &JunkSettings.EnabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&JunkSettings.EnabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Disabled Junk", &JunkSettings.DrawDisabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###JunkSettingsDisabledAlpha", &JunkSettings.DisabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&JunkSettings.DisabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Named Junk", &JunkSettings.DrawNamed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Draw Unnamed Junk", &JunkSettings.DrawUnnamed);

					ButtonToggle("Show Junk Name", &JunkSettings.ShowName);
					ImGui::SameLine(235.0f);
					ButtonToggle("Show Junk Distance", &JunkSettings.ShowDistance);

					ButtonToggle("Junk Text Shadowed", &JunkSettings.TextShadowed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Junk Text Centered", &JunkSettings.TextCentered);

					if (ImGui::CollapsingHeader("Junk Whitelist Settings"))
					{
						for (int i = 0; i < 32; i++)
						{
							char WhitelistedText[sizeof("Junk Whitelist Slot: 31")];
							char WhitelistText[sizeof("###JunkWhitelist31")];
							sprintf_s(WhitelistedText, "Junk Whitelist Slot: %d", i);
							sprintf_s(WhitelistText, "###JunkWhitelist%d", i);
							ButtonToggle(WhitelistedText, &JunkSettings.Whitelisted[i]);
							ImGui::SameLine(235.0f);
							char FormidText[sizeof("00000000")];
							sprintf_s(FormidText, "%08lX", JunkSettings.Whitelist[i]);
							ImGui::SetNextItemWidth(224.0f);
							ImGui::InputText(WhitelistText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
							if (ImGui::IsItemActive()) AllowDrag = false;
							sscanf_s(FormidText, "%08lX", &JunkSettings.Whitelist[i]);
						}
					}
				}

				if (ImGui::CollapsingHeader("Plan ESP Settings"))
				{
					ButtonToggle("Plan ESP Enabled", &PlanSettings.Enabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###PlanSettingsEnabledDistance", &PlanSettings.EnabledDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&PlanSettings.EnabledDistance, 0, 3000);

					ImGui::SetNextItemWidth(451.0f);
					ImGui::ColorEdit3("###PlanSettingsColor", PlanSettings.Color);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(PlanSettings.Color);

					ButtonToggle("Draw Enabled Plans", &PlanSettings.DrawEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###PlanSettingsEnabledAlpha", &PlanSettings.EnabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&PlanSettings.EnabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Disabled Plans", &PlanSettings.DrawDisabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###PlanSettingsDisabledAlpha", &PlanSettings.DisabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&PlanSettings.DisabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Known Plans", &CustomKnownRecipeSettings.KnownRecipesEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("Draw Unknown Plans", &CustomKnownRecipeSettings.UnknownRecipesEnabled);

					ButtonToggle("Draw Named Plans", &PlanSettings.DrawNamed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Draw Unnamed Plans", &PlanSettings.DrawUnnamed);

					ButtonToggle("Show Plan Name", &PlanSettings.ShowName);
					ImGui::SameLine(235.0f);
					ButtonToggle("Show Plan Distance", &PlanSettings.ShowDistance);

					ButtonToggle("Plan Text Shadowed", &PlanSettings.TextShadowed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Plan Text Centered", &PlanSettings.TextCentered);

					if (ImGui::CollapsingHeader("Plan Whitelist Settings"))
					{
						for (int i = 0; i < 32; i++)
						{
							char WhitelistedText[sizeof("Plan Whitelist Slot: 31")];
							char WhitelistText[sizeof("###PlanWhitelist31")];
							sprintf_s(WhitelistedText, "Plan Whitelist Slot: %d", i);
							sprintf_s(WhitelistText, "###PlanWhitelist%d", i);
							ButtonToggle(WhitelistedText, &PlanSettings.Whitelisted[i]);
							ImGui::SameLine(235.0f);
							char FormidText[sizeof("00000000")];
							sprintf_s(FormidText, "%08lX", PlanSettings.Whitelist[i]);
							ImGui::SetNextItemWidth(224.0f);
							ImGui::InputText(WhitelistText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
							if (ImGui::IsItemActive()) AllowDrag = false;
							sscanf_s(FormidText, "%08lX", &PlanSettings.Whitelist[i]);
						}
					}
				}

				if (ImGui::CollapsingHeader("Magazine ESP Settings"))
				{
					ButtonToggle("Magazine ESP Enabled", &MagazineSettings.Enabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###MagazineSettingsEnabledDistance", &MagazineSettings.EnabledDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&MagazineSettings.EnabledDistance, 0, 3000);

					ImGui::SetNextItemWidth(451.0f);
					ImGui::ColorEdit3("###MagazineSettingsColor", MagazineSettings.Color);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(MagazineSettings.Color);

					ButtonToggle("Draw Enabled Magazines", &MagazineSettings.DrawEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###MagazineSettingsEnabledAlpha", &MagazineSettings.EnabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&MagazineSettings.EnabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Disabled Magazines", &MagazineSettings.DrawDisabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###MagazineSettingsDisabledAlpha", &MagazineSettings.DisabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&MagazineSettings.DisabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Named Magazines", &MagazineSettings.DrawNamed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Draw Unnamed Magazines", &MagazineSettings.DrawUnnamed);

					ButtonToggle("Show Magazine Name", &MagazineSettings.ShowName);
					ImGui::SameLine(235.0f);
					ButtonToggle("Show Magazine Distance", &MagazineSettings.ShowDistance);

					ButtonToggle("Magazine Text Shadowed", &MagazineSettings.TextShadowed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Magazine Text Centered", &MagazineSettings.TextCentered);

					if (ImGui::CollapsingHeader("Magazine Whitelist Settings"))
					{
						for (int i = 0; i < 32; i++)
						{
							char WhitelistedText[sizeof("Magazine Whitelist Slot: 31")];
							char WhitelistText[sizeof("###MagazineWhitelist31")];
							sprintf_s(WhitelistedText, "Magazine Whitelist Slot: %d", i);
							sprintf_s(WhitelistText, "###MagazineWhitelist%d", i);
							ButtonToggle(WhitelistedText, &MagazineSettings.Whitelisted[i]);
							ImGui::SameLine(235.0f);
							char FormidText[sizeof("00000000")];
							sprintf_s(FormidText, "%08lX", MagazineSettings.Whitelist[i]);
							ImGui::SetNextItemWidth(224.0f);
							ImGui::InputText(WhitelistText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
							if (ImGui::IsItemActive()) AllowDrag = false;
							sscanf_s(FormidText, "%08lX", &MagazineSettings.Whitelist[i]);
						}
					}
				}

				if (ImGui::CollapsingHeader("Bobblehead ESP Settings"))
				{
					ButtonToggle("Bobblehead ESP Enabled", &BobbleheadSettings.Enabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###BobbleheadSettingsEnabledDistance", &BobbleheadSettings.EnabledDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&BobbleheadSettings.EnabledDistance, 0, 3000);

					ImGui::SetNextItemWidth(451.0f);
					ImGui::ColorEdit3("###BobbleheadSettingsColor", BobbleheadSettings.Color);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(BobbleheadSettings.Color);

					ButtonToggle("Draw Enabled Bobbleheads", &BobbleheadSettings.DrawEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###BobbleheadSettingsEnabledAlpha", &BobbleheadSettings.EnabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&BobbleheadSettings.EnabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Disabled Bobbleheads", &BobbleheadSettings.DrawDisabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###BobbleheadSettingsDisabledAlpha", &BobbleheadSettings.DisabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&BobbleheadSettings.DisabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Named Bobbleheads", &BobbleheadSettings.DrawNamed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Draw Unnamed Bobbleheads", &BobbleheadSettings.DrawUnnamed);

					ButtonToggle("Show Bobblehead Name", &BobbleheadSettings.ShowName);
					ImGui::SameLine(235.0f);
					ButtonToggle("Show Bobblehead Distance", &BobbleheadSettings.ShowDistance);

					ButtonToggle("Bobblehead Text Shadowed", &BobbleheadSettings.TextShadowed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Bobblehead Text Centered", &BobbleheadSettings.TextCentered);

					if (ImGui::CollapsingHeader("Bobblehead Whitelist Settings"))
					{
						for (int i = 0; i < 32; i++)
						{
							char WhitelistedText[sizeof("Bobblehead Whitelist Slot: 31")];
							char WhitelistText[sizeof("###BobbleheadWhitelist31")];
							sprintf_s(WhitelistedText, "Bobblehead Whitelist Slot: %d", i);
							sprintf_s(WhitelistText, "###BobbleheadWhitelist%d", i);
							ButtonToggle(WhitelistedText, &BobbleheadSettings.Whitelisted[i]);
							ImGui::SameLine(235.0f);
							char FormidText[sizeof("00000000")];
							sprintf_s(FormidText, "%08lX", BobbleheadSettings.Whitelist[i]);
							ImGui::SetNextItemWidth(224.0f);
							ImGui::InputText(WhitelistText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
							if (ImGui::IsItemActive()) AllowDrag = false;
							sscanf_s(FormidText, "%08lX", &BobbleheadSettings.Whitelist[i]);
						}
					}
				}

				if (ImGui::CollapsingHeader("Item ESP Settings"))
				{
					ButtonToggle("Item ESP Enabled", &ItemSettings.Enabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###ItemSettingsEnabledDistance", &ItemSettings.EnabledDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&ItemSettings.EnabledDistance, 0, 3000);

					ImGui::SetNextItemWidth(451.0f);
					ImGui::ColorEdit3("###ItemSettingsColor", ItemSettings.Color);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(ItemSettings.Color);

					ButtonToggle("Draw Enabled Items", &ItemSettings.DrawEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###ItemSettingsEnabledAlpha", &ItemSettings.EnabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&ItemSettings.EnabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Disabled Items", &ItemSettings.DrawDisabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###ItemSettingsDisabledAlpha", &ItemSettings.DisabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&ItemSettings.DisabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Named Items", &ItemSettings.DrawNamed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Draw Unnamed Items", &ItemSettings.DrawUnnamed);

					ButtonToggle("Show Item Name", &ItemSettings.ShowName);
					ImGui::SameLine(235.0f);
					ButtonToggle("Show Item Distance", &ItemSettings.ShowDistance);

					ButtonToggle("Item Text Shadowed", &ItemSettings.TextShadowed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Item Text Centered", &ItemSettings.TextCentered);

					if (ImGui::CollapsingHeader("Item Whitelist Settings"))
					{
						for (int i = 0; i < 32; i++)
						{
							char WhitelistedText[sizeof("Item Whitelist Slot: 31")];
							char WhitelistText[sizeof("###ItemWhitelist31")];
							sprintf_s(WhitelistedText, "Item Whitelist Slot: %d", i);
							sprintf_s(WhitelistText, "###ItemWhitelist%d", i);
							ButtonToggle(WhitelistedText, &ItemSettings.Whitelisted[i]);
							ImGui::SameLine(235.0f);
							char FormidText[sizeof("00000000")];
							sprintf_s(FormidText, "%08lX", ItemSettings.Whitelist[i]);
							ImGui::SetNextItemWidth(224.0f);
							ImGui::InputText(WhitelistText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
							if (ImGui::IsItemActive()) AllowDrag = false;
							sscanf_s(FormidText, "%08lX", &ItemSettings.Whitelist[i]);
						}
					}
				}

				if (ImGui::CollapsingHeader("Flora ESP Settings"))
				{
					ButtonToggle("Flora ESP Enabled", &FloraSettings.Enabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###FloraSettingsEnabledDistance", &FloraSettings.EnabledDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&FloraSettings.EnabledDistance, 0, 3000);

					ImGui::SetNextItemWidth(451.0f);
					ImGui::ColorEdit3("###FloraSettingsColor", FloraSettings.Color);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(FloraSettings.Color);

					ButtonToggle("Draw Enabled Flora", &FloraSettings.DrawEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###FloraSettingsEnabledAlpha", &FloraSettings.EnabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&FloraSettings.EnabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Disabled Flora", &FloraSettings.DrawDisabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###FloraSettingsDisabledAlpha", &FloraSettings.DisabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&FloraSettings.DisabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Named Flora", &FloraSettings.DrawNamed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Draw Unnamed Flora", &FloraSettings.DrawUnnamed);

					LargeButtonToggle("Draw Raw Crimson Flux Yielding Flora", &CustomFluxSettings.CrimsonFluxEnabled);
					LargeButtonToggle("Draw Raw Cobalt Flux Yielding Flora", &CustomFluxSettings.CobaltFluxEnabled);
					LargeButtonToggle("Draw Raw Yellowcake Flux Yielding Flora", &CustomFluxSettings.YellowcakeFluxEnabled);
					LargeButtonToggle("Draw Raw Fluorescent Flux Yielding Flora", &CustomFluxSettings.FluorescentFluxEnabled);
					LargeButtonToggle("Draw Raw Violet Flux Yielding Flora", &CustomFluxSettings.VioletFluxEnabled);

					ButtonToggle("Show Flora Name", &FloraSettings.ShowName);
					ImGui::SameLine(235.0f);
					ButtonToggle("Show Flora Distance", &FloraSettings.ShowDistance);

					ButtonToggle("Flora Text Shadowed", &FloraSettings.TextShadowed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Flora Text Centered", &FloraSettings.TextCentered);

					if (ImGui::CollapsingHeader("Flora Whitelist Settings"))
					{
						for (int i = 0; i < 32; i++)
						{
							char WhitelistedText[sizeof("Flora Whitelist Slot: 31")];
							char WhitelistText[sizeof("###FloraWhitelist31")];
							sprintf_s(WhitelistedText, "Flora Whitelist Slot: %d", i);
							sprintf_s(WhitelistText, "###FloraWhitelist%d", i);
							ButtonToggle(WhitelistedText, &FloraSettings.Whitelisted[i]);
							ImGui::SameLine(235.0f);
							char FormidText[sizeof("00000000")];
							sprintf_s(FormidText, "%08lX", FloraSettings.Whitelist[i]);
							ImGui::SetNextItemWidth(224.0f);
							ImGui::InputText(WhitelistText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
							if (ImGui::IsItemActive()) AllowDrag = false;
							sscanf_s(FormidText, "%08lX", &FloraSettings.Whitelist[i]);
						}
					}
				}

				if (ImGui::CollapsingHeader("Entity ESP Settings"))
				{
					ButtonToggle("Entity ESP Enabled", &EntitySettings.Enabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###EntitySettingsEnabledDistance", &EntitySettings.EnabledDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&EntitySettings.EnabledDistance, 0, 3000);

					ImGui::SetNextItemWidth(451.0f);
					ImGui::ColorEdit3("###EntitySettingsColor", EntitySettings.Color);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(EntitySettings.Color);

					ButtonToggle("Draw Enabled Entities", &EntitySettings.DrawEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###EntitySettingsEnabledAlpha", &EntitySettings.EnabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&EntitySettings.EnabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Disabled Entities", &EntitySettings.DrawDisabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###EntitySettingsDisabledAlpha", &EntitySettings.DisabledAlpha, 0.0f, 1.0f, "Alpha: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&EntitySettings.DisabledAlpha, 0.0f, 1.0f);

					ButtonToggle("Draw Named Entities", &EntitySettings.DrawNamed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Draw Unnamed Entities", &EntitySettings.DrawUnnamed);

					ButtonToggle("Show Entity Name", &EntitySettings.ShowName);
					ImGui::SameLine(235.0f);
					ButtonToggle("Show Entity Distance", &EntitySettings.ShowDistance);

					ButtonToggle("Entity Text Shadowed", &EntitySettings.TextShadowed);
					ImGui::SameLine(235.0f);
					ButtonToggle("Entity Text Centered", &EntitySettings.TextCentered);

					if (ImGui::CollapsingHeader("Entity Whitelist Settings"))
					{
						for (int i = 0; i < 32; i++)
						{
							char WhitelistedText[sizeof("Entity Whitelist Slot: 31")];
							char WhitelistText[sizeof("###EntityWhitelist31")];
							sprintf_s(WhitelistedText, "Entity Whitelist Slot: %d", i);
							sprintf_s(WhitelistText, "###EntityWhitelist%d", i);
							ButtonToggle(WhitelistedText, &EntitySettings.Whitelisted[i]);
							ImGui::SameLine(235.0f);
							char FormidText[sizeof("00000000")];
							sprintf_s(FormidText, "%08lX", EntitySettings.Whitelist[i]);
							ImGui::SetNextItemWidth(224.0f);
							ImGui::InputText(WhitelistText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
							if (ImGui::IsItemActive()) AllowDrag = false;
							sscanf_s(FormidText, "%08lX", &EntitySettings.Whitelist[i]);
						}
					}
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Loot###LootTab"))
			{
				if (ImGui::CollapsingHeader("Scrap Looter"))
				{
					if (CheckScrapList())
					{
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 0.3f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.0f, 0.4f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 1.0f, 0.0f, 0.5f));
						if (ImGui::Button("Loot Scrap (Keybind: CTRL+E)###LootSelectedScrapEnabled", ImVec2(224.0f, 0.0f)))
						{
							LootScrap();
						}
						ImGui::PopStyleColor(3);
					}
					else
					{
						ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.3f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.4f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
						ImGui::Button("Loot Scrap (Keybind: CTRL+E)###LootSelectedScrapDisabled", ImVec2(224.0f, 0.0f));
						ImGui::PopStyleColor(3);
						ImGui::PopItemFlag();
					}

					ImGui::SameLine(235.0f);
					ButtonToggle("Scrap Looter Keybind Enabled", &CustomScrapLooterSettings.ScrapKeybindEnabled);

					LargeButtonToggle("Scrap Looter ESP Override (Uses Junk ESP Settings)", &CustomScrapLooterSettings.ScrapOverrideEnabled);

					ButtonToggle("Automatic Looting Enabled###ScrapAutomaticLootingEnabled", &CustomScrapLooterSettings.ScrapAutomaticLootingEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("Draw Automatic Looting Status###ScrapAutomaticStatus", &CustomScrapLooterSettings.ScrapAutomaticStatus);

					ImGui::SetNextItemWidth(224.0f);
					char ScrapAutomaticSpeedMinText[sizeof("Speed (Min): 60 (960 ms)")];
					sprintf_s(ScrapAutomaticSpeedMinText, "Speed (Min): %d (%d ms)", CustomScrapLooterSettings.ScrapAutomaticSpeedMin, CustomScrapLooterSettings.ScrapAutomaticSpeedMin * 16);
					ImGui::SliderInt("###ScrapAutomaticSpeedMin", &CustomScrapLooterSettings.ScrapAutomaticSpeedMin, 10, 60, ScrapAutomaticSpeedMinText);
					if (ImGui::IsItemActive())
					{
						AllowDrag = false;
						if (CustomScrapLooterSettings.ScrapAutomaticSpeedMax < CustomScrapLooterSettings.ScrapAutomaticSpeedMin)
						{
							CustomScrapLooterSettings.ScrapAutomaticSpeedMax = CustomScrapLooterSettings.ScrapAutomaticSpeedMin;
						}
					}
					ValidateInt(&CustomScrapLooterSettings.ScrapAutomaticSpeedMin, 10, 60);
					ValidateInt(&CustomScrapLooterSettings.ScrapAutomaticSpeedMax, 10, 60);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					char ScrapAutomaticSpeedMaxText[sizeof("Speed (Max): 60 (960 ms)")];
					sprintf_s(ScrapAutomaticSpeedMaxText, "Speed (Max): %d (%d ms)", CustomScrapLooterSettings.ScrapAutomaticSpeedMax, CustomScrapLooterSettings.ScrapAutomaticSpeedMax * 16);
					ImGui::SliderInt("###ScrapAutomaticSpeedMax", &CustomScrapLooterSettings.ScrapAutomaticSpeedMax, 10, 60, ScrapAutomaticSpeedMaxText);
					if (ImGui::IsItemActive())
					{
						AllowDrag = false;
						if (CustomScrapLooterSettings.ScrapAutomaticSpeedMax < CustomScrapLooterSettings.ScrapAutomaticSpeedMin)
						{
							CustomScrapLooterSettings.ScrapAutomaticSpeedMin = CustomScrapLooterSettings.ScrapAutomaticSpeedMax;
						}
					}
					ValidateInt(&CustomScrapLooterSettings.ScrapAutomaticSpeedMin, 10, 60);
					ValidateInt(&CustomScrapLooterSettings.ScrapAutomaticSpeedMax, 10, 60);
					if (CustomScrapLooterSettings.ScrapAutomaticSpeedMax < CustomScrapLooterSettings.ScrapAutomaticSpeedMin)
					{
						CustomScrapLooterSettings.ScrapAutomaticSpeedMax = CustomScrapLooterSettings.ScrapAutomaticSpeedMin;
					}

					ImGui::SetNextItemWidth(451.0f);
					ImGui::SliderInt("###ScrapLooterDistance", &CustomScrapLooterSettings.ScrapLooterDistance, 0, 3000, "Scrap Looter Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomScrapLooterSettings.ScrapLooterDistance, 0, 3000);

					for (int i = 0; i < 40; i++)
					{
						ButtonToggle(CustomScrapLooterSettings.ScrapNameList[i], &CustomScrapLooterSettings.ScrapEnabledList[i]);
						ImGui::SameLine(235.0f);
						char LabelText[sizeof("###ScrapReadOnly39")];
						sprintf_s(LabelText, "###ScrapReadOnly%d", i);
						char FormidText[sizeof("00000000")];
						sprintf_s(FormidText, "%08lX", CustomScrapLooterSettings.ScrapFormidList[i]);
						ImGui::SetNextItemWidth(224.0f);
						ImGui::InputText(LabelText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_ReadOnly);
						if (ImGui::IsItemActive()) AllowDrag = false;
					}
				}

				if (ImGui::CollapsingHeader("Item Looter"))
				{
					if (CheckItemLooterSettings())
					{
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 0.3f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.0f, 0.4f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 1.0f, 0.0f, 0.5f));
						if (ImGui::Button("Loot Items (Keybind: CTRL+R)###LootSelectedItemsEnabled", ImVec2(224.0f, 0.0f)))
						{
							LootItems();
						}
						ImGui::PopStyleColor(3);
					}
					else
					{
						ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.3f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.4f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
						ImGui::Button("Loot Items (Keybind: CTRL+R)###LootSelectedItemsDisabled", ImVec2(224.0f, 0.0f));
						ImGui::PopStyleColor(3);
						ImGui::PopItemFlag();
					}

					ImGui::SameLine(235.0f);
					ButtonToggle("Item Looter Keybind Enabled", &CustomItemLooterSettings.ItemKeybindEnabled);

					ButtonToggle("Automatic Looting Enabled###ItemAutomaticLootingEnabled", &CustomItemLooterSettings.ItemAutomaticLootingEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("Draw Automatic Looting Status###ItemAutomaticStatus", &CustomItemLooterSettings.ItemAutomaticStatus);

					ImGui::SetNextItemWidth(224.0f);
					char ItemAutomaticSpeedMinText[sizeof("Speed (Min): 60 (960 ms)")];
					sprintf_s(ItemAutomaticSpeedMinText, "Speed (Min): %d (%d ms)", CustomItemLooterSettings.ItemAutomaticSpeedMin, CustomItemLooterSettings.ItemAutomaticSpeedMin * 16);
					ImGui::SliderInt("###ItemAutomaticSpeedMin", &CustomItemLooterSettings.ItemAutomaticSpeedMin, 10, 60, ItemAutomaticSpeedMinText);
					if (ImGui::IsItemActive())
					{
						AllowDrag = false;
						if (CustomItemLooterSettings.ItemAutomaticSpeedMax < CustomItemLooterSettings.ItemAutomaticSpeedMin)
						{
							CustomItemLooterSettings.ItemAutomaticSpeedMax = CustomItemLooterSettings.ItemAutomaticSpeedMin;
						}
					}
					ValidateInt(&CustomItemLooterSettings.ItemAutomaticSpeedMin, 10, 60);
					ValidateInt(&CustomItemLooterSettings.ItemAutomaticSpeedMax, 10, 60);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					char ItemAutomaticSpeedMaxText[sizeof("Speed (Max): 60 (960 ms)")];
					sprintf_s(ItemAutomaticSpeedMaxText, "Speed (Max): %d (%d ms)", CustomItemLooterSettings.ItemAutomaticSpeedMax, CustomItemLooterSettings.ItemAutomaticSpeedMax * 16);
					ImGui::SliderInt("###ItemAutomaticSpeedMax", &CustomItemLooterSettings.ItemAutomaticSpeedMax, 10, 60, ItemAutomaticSpeedMaxText);
					if (ImGui::IsItemActive())
					{
						AllowDrag = false;
						if (CustomItemLooterSettings.ItemAutomaticSpeedMax < CustomItemLooterSettings.ItemAutomaticSpeedMin)
						{
							CustomItemLooterSettings.ItemAutomaticSpeedMin = CustomItemLooterSettings.ItemAutomaticSpeedMax;
						}
					}
					ValidateInt(&CustomItemLooterSettings.ItemAutomaticSpeedMin, 10, 60);
					ValidateInt(&CustomItemLooterSettings.ItemAutomaticSpeedMax, 10, 60);
					if (CustomItemLooterSettings.ItemAutomaticSpeedMax < CustomItemLooterSettings.ItemAutomaticSpeedMin)
					{
						CustomItemLooterSettings.ItemAutomaticSpeedMax = CustomItemLooterSettings.ItemAutomaticSpeedMin;
					}

					ButtonToggle("Weapons Enabled###ItemLooterWeaponsEnabled", &CustomItemLooterSettings.ItemLooterWeaponsEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###ItemLooterWeaponsDistance", &CustomItemLooterSettings.ItemLooterWeaponsDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomItemLooterSettings.ItemLooterWeaponsDistance, 0, 3000);

					ButtonToggle("Armor Enabled###ItemLooterArmorEnabled", &CustomItemLooterSettings.ItemLooterArmorEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###ItemLooterArmorDistance", &CustomItemLooterSettings.ItemLooterArmorDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomItemLooterSettings.ItemLooterArmorDistance, 0, 3000);

					ButtonToggle("Ammo Enabled###ItemLooterAmmoEnabled", &CustomItemLooterSettings.ItemLooterAmmoEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###ItemLooterAmmoDistance", &CustomItemLooterSettings.ItemLooterAmmoDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomItemLooterSettings.ItemLooterAmmoDistance, 0, 3000);

					ButtonToggle("Mods Enabled###ItemLooterModsEnabled", &CustomItemLooterSettings.ItemLooterModsEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###ItemLooterModsDistance", &CustomItemLooterSettings.ItemLooterModsDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomItemLooterSettings.ItemLooterModsDistance, 0, 3000);

					ButtonToggle("Magazines Enabled###ItemLooterMagazinesEnabled", &CustomItemLooterSettings.ItemLooterMagazinesEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###ItemLooterMagazinesDistance", &CustomItemLooterSettings.ItemLooterMagazinesDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomItemLooterSettings.ItemLooterMagazinesDistance, 0, 3000);

					ButtonToggle("Bobbleheads Enabled###ItemLooterBobbleheadsEnabled", &CustomItemLooterSettings.ItemLooterBobbleheadsEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###ItemLooterBobbleheadsDistance", &CustomItemLooterSettings.ItemLooterBobbleheadsDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomItemLooterSettings.ItemLooterBobbleheadsDistance, 0, 3000);

					ButtonToggle("Aid Enabled###ItemLooterAidEnabled", &CustomItemLooterSettings.ItemLooterAidEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###ItemLooterAidDistance", &CustomItemLooterSettings.ItemLooterAidDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomItemLooterSettings.ItemLooterAidDistance, 0, 3000);

					ButtonToggle("Known Plans Enabled###ItemLooterKnownPlansEnabled", &CustomItemLooterSettings.ItemLooterKnownPlansEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###ItemLooterKnownPlansDistance", &CustomItemLooterSettings.ItemLooterKnownPlansDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomItemLooterSettings.ItemLooterKnownPlansDistance, 0, 3000);

					ButtonToggle("Unknown Plans Enabled###ItemLooterUnknownPlansEnabled", &CustomItemLooterSettings.ItemLooterUnknownPlansEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###ItemLooterUnknownPlansDistance", &CustomItemLooterSettings.ItemLooterUnknownPlansDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomItemLooterSettings.ItemLooterUnknownPlansDistance, 0, 3000);

					ButtonToggle("Misc Enabled###ItemLooterMiscEnabled", &CustomItemLooterSettings.ItemLooterMiscEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###ItemLooterMiscDistance", &CustomItemLooterSettings.ItemLooterMiscDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomItemLooterSettings.ItemLooterMiscDistance, 0, 3000);

					ButtonToggle("Other Enabled###ItemLooterUnlistedEnabled", &CustomItemLooterSettings.ItemLooterUnlistedEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###ItemLooterUnlistedDistance", &CustomItemLooterSettings.ItemLooterUnlistedDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomItemLooterSettings.ItemLooterUnlistedDistance, 0, 3000);

					ButtonToggle("Item Formid List Enabled###ItemLooterListEnabled", &CustomItemLooterSettings.ItemLooterListEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###ItemLooterListDistance", &CustomItemLooterSettings.ItemLooterListDistance, 0, 3000, "Distance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomItemLooterSettings.ItemLooterListDistance, 0, 3000);

					LargeButtonToggle("Item Looter Blacklist Enabled###ItemLooterBlacklistToggle", &CustomItemLooterSettings.ItemLooterBlacklistToggle);

					if (ImGui::CollapsingHeader("Item Looter Formid List"))
					{
						for (int i = 0; i < 100; i++)
						{
							char ItemLooterEnabledText[sizeof("Item Looter Slot: 99")];
							char ItemLooterLabelText[sizeof("###ItemLooterList99")];
							sprintf_s(ItemLooterEnabledText, "Item Looter Slot: %d", i);
							sprintf_s(ItemLooterLabelText, "###ItemLooterList%d", i);
							ButtonToggle(ItemLooterEnabledText, &CustomItemLooterSettings.ItemLooterEnabledList[i]);
							ImGui::SameLine(235.0f);
							char FormidText[sizeof("00000000")];
							sprintf_s(FormidText, "%08lX", CustomItemLooterSettings.ItemLooterFormidList[i]);
							ImGui::SetNextItemWidth(224.0f);
							ImGui::InputText(ItemLooterLabelText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
							if (ImGui::IsItemActive()) AllowDrag = false;
							sscanf_s(FormidText, "%08lX", &CustomItemLooterSettings.ItemLooterFormidList[i]);
						}
					}

					if (ImGui::CollapsingHeader("Item Looter Blacklist"))
					{
						for (int i = 0; i < 64; i++)
						{
							char ItemLooterBlacklistEnabledText[sizeof("Item Looter Blacklist: 63")];
							char ItemLooterBlacklistLabelText[sizeof("###ItemLooterBlacklist63")];
							sprintf_s(ItemLooterBlacklistEnabledText, "Item Looter Blacklist: %d", i);
							sprintf_s(ItemLooterBlacklistLabelText, "###ItemLooterBlacklist%d", i);
							ButtonToggle(ItemLooterBlacklistEnabledText, &CustomItemLooterSettings.ItemLooterBlacklistEnabled[i]);
							ImGui::SameLine(235.0f);
							char FormidText[sizeof("00000000")];
							sprintf_s(FormidText, "%08lX", CustomItemLooterSettings.ItemLooterBlacklist[i]);
							ImGui::SetNextItemWidth(224.0f);
							ImGui::InputText(ItemLooterBlacklistLabelText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
							if (ImGui::IsItemActive()) AllowDrag = false;
							sscanf_s(FormidText, "%08lX", &CustomItemLooterSettings.ItemLooterBlacklist[i]);
						}
					}
				}

				if (ImGui::CollapsingHeader("NPC Looter (76m Distance Limit)"))
				{
					LargeButtonToggle("Automatic NPC Looting Enabled (Keybind: CTRL+COMMA)###NPCLooterEnabled", &NPCLooterSettings.EntityLooterEnabled);

					LargeButtonToggle("Draw NPC Looter Status###NPCLooterStatusEnabled", &NPCLooterSettings.EntityLooterStatusEnabled);

					ButtonToggle("All Weapons Enabled###NPCLooterAllWeaponsEnabled", &NPCLooterSettings.EntityLooterAllWeaponsEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("All Armor Enabled###NPCLooterAllArmorEnabled", &NPCLooterSettings.EntityLooterAllArmorEnabled);

					ButtonToggle("1* Weapons Enabled###NPCLooterOneStarWeaponsEnabled", &NPCLooterSettings.EntityLooterOneStarWeaponsEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("1* Armor Enabled###NPCLooterOneStarArmorEnabled", &NPCLooterSettings.EntityLooterOneStarArmorEnabled);

					ButtonToggle("2* Weapons Enabled###NPCLooterTwoStarWeaponsEnabled", &NPCLooterSettings.EntityLooterTwoStarWeaponsEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("2* Armor Enabled###NPCLooterTwoStarArmorEnabled", &NPCLooterSettings.EntityLooterTwoStarArmorEnabled);

					ButtonToggle("3* Weapons Enabled###NPCLooterThreeStarWeaponsEnabled", &NPCLooterSettings.EntityLooterThreeStarWeaponsEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("3* Armor Enabled###NPCLooterThreeStarArmorEnabled", &NPCLooterSettings.EntityLooterThreeStarArmorEnabled);

					ButtonToggle("Ammo Enabled###NPCLooterAmmoEnabled", &NPCLooterSettings.EntityLooterAmmoEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("Mods Enabled###NPCLooterModsEnabled", &NPCLooterSettings.EntityLooterModsEnabled);

					ButtonToggle("Caps Enabled###NPCLooterCapsEnabled", &NPCLooterSettings.EntityLooterCapsEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("Junk Enabled###NPCLooterJunkEnabled", &NPCLooterSettings.EntityLooterJunkEnabled);

					ButtonToggle("Aid Enabled###NPCLooterAidEnabled", &NPCLooterSettings.EntityLooterAidEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("Treasure Maps Enabled###NPCLooterTreasureMapsEnabled", &NPCLooterSettings.EntityLooterTreasureMapsEnabled);

					ButtonToggle("Known Plans Enabled###NPCLooterKnownPlansEnabled", &NPCLooterSettings.EntityLooterKnownPlansEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("Unknown Plans Enabled###NPCLooterUnknownPlansEnabled", &NPCLooterSettings.EntityLooterUnknownPlansEnabled);

					ButtonToggle("Misc Enabled###NPCLooterMiscEnabled", &NPCLooterSettings.EntityLooterMiscEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("Other Enabled###NPCLooterUnlistedEnabled", &NPCLooterSettings.EntityLooterUnlistedEnabled);

					LargeButtonToggle("NPC Looter Formid List Enabled###NPCLooterListEnabled", &NPCLooterSettings.EntityLooterListEnabled);

					LargeButtonToggle("NPC Looter Blacklist Enabled###NPCLooterBlacklistToggle", &NPCLooterSettings.EntityLooterBlacklistToggle);

					if (ImGui::CollapsingHeader("NPC Looter Formid List"))
					{
						for (int i = 0; i < 100; i++)
						{
							char NPCLooterEnabledText[sizeof("NPC Looter Slot: 99")];
							char NPCLooterLabelText[sizeof("###NPCLooterList99")];
							sprintf_s(NPCLooterEnabledText, "NPC Looter Slot: %d", i);
							sprintf_s(NPCLooterLabelText, "###NPCLooterList%d", i);
							ButtonToggle(NPCLooterEnabledText, &NPCLooterSettings.EntityLooterEnabledList[i]);
							ImGui::SameLine(235.0f);
							char FormidText[sizeof("00000000")];
							sprintf_s(FormidText, "%08lX", NPCLooterSettings.EntityLooterFormidList[i]);
							ImGui::SetNextItemWidth(224.0f);
							ImGui::InputText(NPCLooterLabelText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
							if (ImGui::IsItemActive()) AllowDrag = false;
							sscanf_s(FormidText, "%08lX", &NPCLooterSettings.EntityLooterFormidList[i]);
						}
					}

					if (ImGui::CollapsingHeader("NPC Looter Blacklist"))
					{
						for (int i = 0; i < 64; i++)
						{
							char NPCLooterBlacklistEnabledText[sizeof("NPC Looter Blacklist: 63")];
							char NPCLooterBlacklistLabelText[sizeof("###NPCLooterBlacklist63")];
							sprintf_s(NPCLooterBlacklistEnabledText, "NPC Looter Blacklist: %d", i);
							sprintf_s(NPCLooterBlacklistLabelText, "###NPCLooterBlacklist%d", i);
							ButtonToggle(NPCLooterBlacklistEnabledText, &NPCLooterSettings.EntityLooterBlacklistEnabled[i]);
							ImGui::SameLine(235.0f);
							char FormidText[sizeof("00000000")];
							sprintf_s(FormidText, "%08lX", NPCLooterSettings.EntityLooterBlacklist[i]);
							ImGui::SetNextItemWidth(224.0f);
							ImGui::InputText(NPCLooterBlacklistLabelText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
							if (ImGui::IsItemActive()) AllowDrag = false;
							sscanf_s(FormidText, "%08lX", &NPCLooterSettings.EntityLooterBlacklist[i]);
						}
					}
				}

				if (ImGui::CollapsingHeader("Container Looter (6m Distance Limit)"))
				{
					LargeButtonToggle("Automatic Container Looting Enabled (Keybind: CTRL+PERIOD)###ContainerLooterEnabled", &ContainerLooterSettings.EntityLooterEnabled);

					LargeButtonToggle("Draw Container Looter Status###ContainerLooterStatusEnabled", &ContainerLooterSettings.EntityLooterStatusEnabled);

					ButtonToggle("All Weapons Enabled###ContainerLooterAllWeaponsEnabled", &ContainerLooterSettings.EntityLooterAllWeaponsEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("All Armor Enabled###ContainerLooterAllArmorEnabled", &ContainerLooterSettings.EntityLooterAllArmorEnabled);

					ButtonToggle("1* Weapons Enabled###ContainerLooterOneStarWeaponsEnabled", &ContainerLooterSettings.EntityLooterOneStarWeaponsEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("1* Armor Enabled###ContainerLooterOneStarArmorEnabled", &ContainerLooterSettings.EntityLooterOneStarArmorEnabled);

					ButtonToggle("2* Weapons Enabled###ContainerLooterTwoStarWeaponsEnabled", &ContainerLooterSettings.EntityLooterTwoStarWeaponsEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("2* Armor Enabled###ContainerLooterTwoStarArmorEnabled", &ContainerLooterSettings.EntityLooterTwoStarArmorEnabled);

					ButtonToggle("3* Weapons Enabled###ContainerLooterThreeStarWeaponsEnabled", &ContainerLooterSettings.EntityLooterThreeStarWeaponsEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("3* Armor Enabled###ContainerLooterThreeStarArmorEnabled", &ContainerLooterSettings.EntityLooterThreeStarArmorEnabled);

					ButtonToggle("Ammo Enabled###ContainerLooterAmmoEnabled", &ContainerLooterSettings.EntityLooterAmmoEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("Mods Enabled###ContainerLooterModsEnabled", &ContainerLooterSettings.EntityLooterModsEnabled);

					ButtonToggle("Caps Enabled###ContainerLooterCapsEnabled", &ContainerLooterSettings.EntityLooterCapsEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("Junk Enabled###ContainerLooterJunkEnabled", &ContainerLooterSettings.EntityLooterJunkEnabled);

					ButtonToggle("Aid Enabled###ContainerLooterAidEnabled", &ContainerLooterSettings.EntityLooterAidEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("Treasure Maps Enabled###ContainerLooterTreasureMapsEnabled", &ContainerLooterSettings.EntityLooterTreasureMapsEnabled);

					ButtonToggle("Known Plans Enabled###ContainerLooterKnownPlansEnabled", &ContainerLooterSettings.EntityLooterKnownPlansEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("Unknown Plans Enabled###ContainerLooterUnknownPlansEnabled", &ContainerLooterSettings.EntityLooterUnknownPlansEnabled);

					ButtonToggle("Misc Enabled###ContainerLooterMiscEnabled", &ContainerLooterSettings.EntityLooterMiscEnabled);
					ImGui::SameLine(235.0f);
					ButtonToggle("Other Enabled###ContainerLooterUnlistedEnabled", &ContainerLooterSettings.EntityLooterUnlistedEnabled);

					LargeButtonToggle("Container Looter Formid List Enabled###ContainerLooterListEnabled", &ContainerLooterSettings.EntityLooterListEnabled);

					LargeButtonToggle("Container Looter Blacklist Enabled###ContainerLooterBlacklistToggle", &ContainerLooterSettings.EntityLooterBlacklistToggle);

					if (ImGui::CollapsingHeader("Container Looter Formid List"))
					{
						for (int i = 0; i < 100; i++)
						{
							char ContainerLooterEnabledText[sizeof("Container Looter Slot: 99")];
							char ContainerLooterLabelText[sizeof("###ContainerLooterList99")];
							sprintf_s(ContainerLooterEnabledText, "Container Looter Slot: %d", i);
							sprintf_s(ContainerLooterLabelText, "###ContainerLooterList%d", i);
							ButtonToggle(ContainerLooterEnabledText, &ContainerLooterSettings.EntityLooterEnabledList[i]);
							ImGui::SameLine(235.0f);
							char FormidText[sizeof("00000000")];
							sprintf_s(FormidText, "%08lX", ContainerLooterSettings.EntityLooterFormidList[i]);
							ImGui::SetNextItemWidth(224.0f);
							ImGui::InputText(ContainerLooterLabelText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
							if (ImGui::IsItemActive()) AllowDrag = false;
							sscanf_s(FormidText, "%08lX", &ContainerLooterSettings.EntityLooterFormidList[i]);
						}
					}

					if (ImGui::CollapsingHeader("Container Looter Blacklist"))
					{
						for (int i = 0; i < 64; i++)
						{
							char ContainerLooterBlacklistEnabledText[sizeof("Container Looter Blacklist: 63")];
							char ContainerLooterBlacklistLabelText[sizeof("###ContainerLooterBlacklist63")];
							sprintf_s(ContainerLooterBlacklistEnabledText, "Container Looter Blacklist: %d", i);
							sprintf_s(ContainerLooterBlacklistLabelText, "###ContainerLooterBlacklist%d", i);
							ButtonToggle(ContainerLooterBlacklistEnabledText, &ContainerLooterSettings.EntityLooterBlacklistEnabled[i]);
							ImGui::SameLine(235.0f);
							char FormidText[sizeof("00000000")];
							sprintf_s(FormidText, "%08lX", ContainerLooterSettings.EntityLooterBlacklist[i]);
							ImGui::SetNextItemWidth(224.0f);
							ImGui::InputText(ContainerLooterBlacklistLabelText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
							if (ImGui::IsItemActive()) AllowDrag = false;
							sscanf_s(FormidText, "%08lX", &ContainerLooterSettings.EntityLooterBlacklist[i]);
						}
					}
				}

				if (ImGui::CollapsingHeader("Flora Harvester (6m Distance Limit)"))
				{
					LargeButtonToggle("Automatic Flora Harvesting Enabled (Keybind: CTRL+P])###HarvesterEnabled", &CustomHarvesterSettings.HarvesterEnabled);

					LargeButtonToggle("Draw Flora Harvester Status###HarvesterStatusEnabled", &CustomHarvesterSettings.HarvesterStatusEnabled);

					LargeButtonToggle("Flora Harvester ESP Override (Uses Flora ESP Settings)", &CustomHarvesterSettings.HarvesterOverrideEnabled);

					for (int i = 0; i < 69; i++)
					{
						ButtonToggle(CustomHarvesterSettings.HarvesterNameList[i], &CustomHarvesterSettings.HarvesterEnabledList[i]);
						ImGui::SameLine(235.0f);
						char LabelText[sizeof("###HarvesterReadOnly68")];
						sprintf_s(LabelText, "###HarvesterReadOnly%d", i);
						char FormidText[sizeof("00000000")];
						sprintf_s(FormidText, "%08lX", CustomHarvesterSettings.HarvesterFormidList[i]);
						ImGui::SetNextItemWidth(224.0f);
						ImGui::InputText(LabelText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_ReadOnly);
						if (ImGui::IsItemActive()) AllowDrag = false;
					}
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Combat###CombatTab"))
			{
				if (ImGui::CollapsingHeader("Weapon Editor"))
				{
					ButtonToggle("No Recoil", &CustomWeaponSettings.NoRecoil);
					ImGui::SameLine(235.0f);
					ButtonToggle("Infinite Ammo", &CustomWeaponSettings.InfiniteAmmo);

					ButtonToggle("No Spread", &CustomWeaponSettings.NoSpread);
					ImGui::SameLine(235.0f);
					ButtonToggle("Instant Reload", &CustomWeaponSettings.InstantReload);

					ButtonToggle("No Sway", &CustomWeaponSettings.NoSway);
					ImGui::SameLine(235.0f);
					ButtonToggle("Automatic Flag###WeaponAutomatic", &CustomWeaponSettings.Automaticflag);

					ButtonToggle("Capacity###WeaponCapacityEnabled", &CustomWeaponSettings.CapacityEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###WeaponCapacity", &CustomWeaponSettings.Capacity, 0, 999, "Capacity: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomWeaponSettings.Capacity, 0, 999);

					ButtonToggle("Speed###WeaponSpeedEnabled", &CustomWeaponSettings.SpeedEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###WeaponSpeed", &CustomWeaponSettings.Speed, 0.0f, 100.0f, "Speed: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&CustomWeaponSettings.Speed, 0.0f, 100.0f);

					ButtonToggle("Reach###WeaponReachEnabled", &CustomWeaponSettings.ReachEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###WeaponReach", &CustomWeaponSettings.Reach, 0.0f, 999.0f, "Reach: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&CustomWeaponSettings.Reach, 0.0f, 999.0f);
				}

				if (ImGui::CollapsingHeader("Targeting Settings"))
				{
					ButtonToggle("Player Targeting (Keybind: T)", &CustomTargetSettings.LockPlayers);
					ImGui::SameLine(235.0f);
					ButtonToggle("NPC Targeting (Keybind: T)", &CustomTargetSettings.LockNPCs);

					ButtonToggle("Damage Redirection (Players)", &CustomTargetSettings.IndirectPlayers);
					ImGui::SameLine(235.0f);
					ButtonToggle("Damage Redirection (NPCs)", &CustomTargetSettings.IndirectNPCs);

					ButtonToggle("Send Damage (Players)", &CustomTargetSettings.DirectPlayers);
					ImGui::SameLine(235.0f);
					ButtonToggle("Send Damage (NPCs)", &CustomTargetSettings.DirectNPCs);

					SmallButtonToggle("Living###TargetLiving", &CustomTargetSettings.TargetLiving);
					ImGui::SameLine(122.0f);
					SmallButtonToggle("Downed###TargetDowned", &CustomTargetSettings.TargetDowned);
					ImGui::SameLine(235.0f);
					SmallButtonToggle("Dead###TargetDead", &CustomTargetSettings.TargetDead);
					ImGui::SameLine(349.0f);
					SmallButtonToggle("Unknown###TargetUnknown", &CustomTargetSettings.TargetUnknown);

					ButtonToggle("Ignore Render Distance###IgnoreRenderDistance", &CustomTargetSettings.IgnoreRenderDistance);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###TargetLockingFOV", &CustomTargetSettings.LockingFOV, 5.0f, 40.0f, "Targeting FOV: %.2f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&CustomTargetSettings.LockingFOV, 5.0f, 40.0f);

					ButtonToggle("Ignore Essential NPCs###IgnoreEssentialNPCs", &CustomTargetSettings.IgnoreEssentialNPCs);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::ColorEdit3("###TargetLockingColor", CustomTargetSettings.LockingColor);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateRGB(PlayerSettings.UnknownColor);

					ButtonToggle("Automatic Retargeting###TargetLockingRetargeting", &CustomTargetSettings.Retargeting);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					char TargetLockingCooldownText[sizeof("Cooldown: 120 (1920 ms)")];
					sprintf_s(TargetLockingCooldownText, "Cooldown: %d (%d ms)", CustomTargetSettings.Cooldown, CustomTargetSettings.Cooldown * 16);
					ImGui::SliderInt("###TargetLockingCooldown", &CustomTargetSettings.Cooldown, 0, 120, TargetLockingCooldownText);
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomTargetSettings.Cooldown, 0, 120);

					ImGui::SetNextItemWidth(224.0f);
					char SendDamageMinText[sizeof("Send Damage (Min): 60 (960 ms)")];
					sprintf_s(SendDamageMinText, "Send Damage (Min): %d (%d ms)", CustomTargetSettings.SendDamageMin, CustomTargetSettings.SendDamageMin * 16);
					ImGui::SliderInt("###SendDamageMin", &CustomTargetSettings.SendDamageMin, 1, 60, SendDamageMinText);
					if (ImGui::IsItemActive())
					{
						AllowDrag = false;
						if (CustomTargetSettings.SendDamageMax < CustomTargetSettings.SendDamageMin)
						{
							CustomTargetSettings.SendDamageMax = CustomTargetSettings.SendDamageMin;
						}
					}
					ValidateInt(&CustomTargetSettings.SendDamageMin, 1, 60);
					ValidateInt(&CustomTargetSettings.SendDamageMax, 1, 60);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					char SendDamageMaxText[sizeof("Send Damage (Max): 60 (960 ms)")];
					sprintf_s(SendDamageMaxText, "Send Damage (Max): %d (%d ms)", CustomTargetSettings.SendDamageMax, CustomTargetSettings.SendDamageMax * 16);
					ImGui::SliderInt("###SendDamageMax", &CustomTargetSettings.SendDamageMax, 1, 60, SendDamageMaxText);
					if (ImGui::IsItemActive())
					{
						AllowDrag = false;
						if (CustomTargetSettings.SendDamageMax < CustomTargetSettings.SendDamageMin)
						{
							CustomTargetSettings.SendDamageMin = CustomTargetSettings.SendDamageMax;
						}
					}
					ValidateInt(&CustomTargetSettings.SendDamageMin, 1, 60);
					ValidateInt(&CustomTargetSettings.SendDamageMax, 1, 60);
					if (CustomTargetSettings.SendDamageMax < CustomTargetSettings.SendDamageMin)
					{
						CustomTargetSettings.SendDamageMax = CustomTargetSettings.SendDamageMin;
					}

					char *FavoritedWeaponsPreview = nullptr;
					if (CustomTargetSettings.FavoriteIndex < 12)
					{
						FavoritedWeaponsPreview = GetFavoritedWeaponText(BYTE(CustomTargetSettings.FavoriteIndex));
						if (FavoritedWeaponsPreview == nullptr)
						{
							FavoritedWeaponsPreview = new char[sizeof("[?] Favorited Item Invalid")];
							sprintf_s(FavoritedWeaponsPreview, sizeof("[?] Favorited Item Invalid"), "[%c] Favorited Item Invalid", GetFavoriteSlot(BYTE(CustomTargetSettings.FavoriteIndex)));
						}
					}
					else
					{
						FavoritedWeaponsPreview = new char[sizeof("[?] No Weapon Selected")];
						sprintf_s(FavoritedWeaponsPreview, sizeof("[?] No Weapon Selected"), "[?] No Weapon Selected");
					}

					ImGui::SetNextItemWidth(451.0f);
					if (ImGui::BeginCombo("###BeginTempCombo", FavoritedWeaponsPreview))
					{
						FavoritedWeaponsArray = GetFavoritedWeapons();
						if (FavoritedWeaponsArray == nullptr)
						{
							FavoritedWeaponsArray = new char*[13];
							FavoritedWeaponsArray[0] = new char[sizeof("[?] No Weapon Selected")];
							sprintf_s(FavoritedWeaponsArray[0], sizeof("[?] No Weapon Selected"), "[?] No Weapon Selected");
							for (int i = 1; i < 13; i++)
							{
								FavoritedWeaponsArray[i] = new char[sizeof("[?] Favorited Item Invalid")];
								sprintf_s(FavoritedWeaponsArray[i], sizeof("[?] Favorited Item Invalid"), "[%c] Favorited Item Invalid", GetFavoriteSlot(BYTE(i - 1)));
							}
						}

						for (int i = 0; i < 13; i++)
						{
							if (ImGui::Selectable(FavoritedWeaponsArray[i]))
							{
								if (i)
								{
									CustomTargetSettings.FavoriteIndex = i - 1;
								}
								else
								{
									CustomTargetSettings.FavoriteIndex = 12;
								}
							}
						}

						ImGui::EndCombo();
						AllowDrag = false;
					}

					if (FavoritedWeaponsPreview != nullptr)
					{
						delete[]FavoritedWeaponsPreview;
						FavoritedWeaponsPreview = nullptr;
					}

					if (FavoritedWeaponsArray != nullptr)
					{
						for (int i = 0; i < 13; i++)
						{
							if (FavoritedWeaponsArray[i] != nullptr)
							{
								delete[]FavoritedWeaponsArray[i];
								FavoritedWeaponsArray[i] = nullptr;
							}
						}

						delete[]FavoritedWeaponsArray;
						FavoritedWeaponsArray = nullptr;
					}

					ValidateInt(&CustomTargetSettings.FavoriteIndex, 0, 12);
				}

				if (ImGui::CollapsingHeader("Melee Settings"))
				{
					LargeButtonToggle("Melee Enabled (Keybind: U)", &CustomMeleeSettings.MeleeEnabled);

					ImGui::SetNextItemWidth(224.0f);
					char MeleeSpeedMinText[sizeof("Melee Speed (Min): 60 (960 ms)")];
					sprintf_s(MeleeSpeedMinText, "Melee Speed (Min): %d (%d ms)", CustomMeleeSettings.MeleeSpeedMin, CustomMeleeSettings.MeleeSpeedMin * 16);
					ImGui::SliderInt("###MeleeSpeedMin", &CustomMeleeSettings.MeleeSpeedMin, 1, 60, MeleeSpeedMinText);
					if (ImGui::IsItemActive())
					{
						AllowDrag = false;
						if (CustomMeleeSettings.MeleeSpeedMax < CustomMeleeSettings.MeleeSpeedMin)
						{
							CustomMeleeSettings.MeleeSpeedMax = CustomMeleeSettings.MeleeSpeedMin;
						}
					}
					ValidateInt(&CustomMeleeSettings.MeleeSpeedMin, 1, 60);
					ValidateInt(&CustomMeleeSettings.MeleeSpeedMax, 1, 60);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					char MeleeSpeedMaxText[sizeof("Melee Speed (Max): 60 (960 ms)")];
					sprintf_s(MeleeSpeedMaxText, "Melee Speed (Max): %d (%d ms)", CustomMeleeSettings.MeleeSpeedMax, CustomMeleeSettings.MeleeSpeedMax * 16);
					ImGui::SliderInt("###MeleeSpeedMax", &CustomMeleeSettings.MeleeSpeedMax, 1, 60, MeleeSpeedMaxText);
					if (ImGui::IsItemActive())
					{
						AllowDrag = false;
						if (CustomMeleeSettings.MeleeSpeedMax < CustomMeleeSettings.MeleeSpeedMin)
						{
							CustomMeleeSettings.MeleeSpeedMin = CustomMeleeSettings.MeleeSpeedMax;
						}
					}
					ValidateInt(&CustomMeleeSettings.MeleeSpeedMin, 1, 60);
					ValidateInt(&CustomMeleeSettings.MeleeSpeedMax, 1, 60);
					if (CustomMeleeSettings.MeleeSpeedMax < CustomMeleeSettings.MeleeSpeedMin)
					{
						CustomMeleeSettings.MeleeSpeedMax = CustomMeleeSettings.MeleeSpeedMin;
					}
				}

				if (ImGui::CollapsingHeader("One Position Kill"))
				{
					LargeButtonToggle("OPK Players (Keybind: CTRL+B)", &CustomOpkSettings.PlayersEnabled);
					LargeButtonToggle("OPK NPCs (Keybind: CTRL+N)", &CustomOpkSettings.NpcsEnabled);
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Player###PlayerTab"))
			{
				if (ImGui::CollapsingHeader("Local Player Settings"))
				{
					LargeButtonToggle("Position Spoofing (Keybind CTRL+L)##LocalPlayerPositionSpoofingEnabled", &CustomLocalPlayerSettings.PositionSpoofingEnabled);
					ButtonToggle("Draw Position Status###LocalPlayerDrawPositionSpoofingEnabled", &CustomLocalPlayerSettings.DrawPositionSpoofingEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###LocalPlayerPositionSpoofingHeight", &CustomLocalPlayerSettings.PositionSpoofingHeight, -524287, 524287, "Spoofed Height: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomLocalPlayerSettings.PositionSpoofingHeight, -524287, 524287);

					ButtonToggle("Noclip (Keybind CTRL+Y)###NoclipEnabled", &CustomLocalPlayerSettings.NoclipEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderFloat("###NoclipSpeed", &CustomLocalPlayerSettings.NoclipSpeed, 0.0f, 2.0f, "Speed: %.5f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&CustomLocalPlayerSettings.NoclipSpeed, 0.0f, 2.0f);

					ButtonToggle("Client State", &CustomLocalPlayerSettings.ClientState);
					ImGui::SameLine(235.0f);
					ButtonToggle("Automatic Client State", &CustomLocalPlayerSettings.AutomaticClientState);

					LargeButtonToggle("Freeze Action Points###LocalPlayerFreezeApEnabled", &CustomLocalPlayerSettings.FreezeApEnabled);

					ButtonToggle("Action Points###LocalPlayerAPEnabled", &CustomLocalPlayerSettings.ActionPointsEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###LocalPlayerAP", &CustomLocalPlayerSettings.ActionPoints, 0, 99999, "Action Points: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomLocalPlayerSettings.ActionPoints, 0, 99999);

					ButtonToggle("Strength###LocalPlayerStrengthEnabled", &CustomLocalPlayerSettings.StrengthEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###LocalPlayerStrength", &CustomLocalPlayerSettings.Strength, 0, 99999, "Strength: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomLocalPlayerSettings.Strength, 0, 99999);

					ButtonToggle("Perception###LocalPlayerPerceptionEnabled", &CustomLocalPlayerSettings.PerceptionEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###LocalPlayerPerception", &CustomLocalPlayerSettings.Perception, 0, 99999, "Perception: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomLocalPlayerSettings.Perception, 0, 99999);

					ButtonToggle("Endurance###LocalPlayerEnduranceEnabled", &CustomLocalPlayerSettings.EnduranceEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###LocalPlayerEndurance", &CustomLocalPlayerSettings.Endurance, 0, 99999, "Endurance: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomLocalPlayerSettings.Endurance, 0, 99999);

					ButtonToggle("Charisma###LocalPlayerCharismaEnabled", &CustomLocalPlayerSettings.CharismaEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###LocalPlayerCharisma", &CustomLocalPlayerSettings.Charisma, 0, 99999, "Charisma: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomLocalPlayerSettings.Charisma, 0, 99999);

					ButtonToggle("Intelligence###LocalPlayerIntelligenceEnabled", &CustomLocalPlayerSettings.IntelligenceEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###LocalPlayerIntelligence", &CustomLocalPlayerSettings.Intelligence, 0, 99999, "Intelligence: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomLocalPlayerSettings.Intelligence, 0, 99999);

					ButtonToggle("Agility###LocalPlayerAgilityEnabled", &CustomLocalPlayerSettings.AgilityEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###LocalPlayerAgility", &CustomLocalPlayerSettings.Agility, 0, 99999, "Agility: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomLocalPlayerSettings.Agility, 0, 99999);

					ButtonToggle("Luck###LocalPlayerLuckEnabled", &CustomLocalPlayerSettings.LuckEnabled);
					ImGui::SameLine(235.0f);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::SliderInt("###LocalPlayerLuck", &CustomLocalPlayerSettings.Luck, 0, 99999, "Luck: %d");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateInt(&CustomLocalPlayerSettings.Luck, 0, 99999);
				}

				if (ImGui::CollapsingHeader("Character Settings"))
				{
					LargeButtonToggle("Character Appearance Editing Enabled###ChargenEditingEnabled", &CustomChargenSettings.ChargenEditingEnabled);

					ImGui::SetNextItemWidth(451.0f);
					ImGui::SliderFloat("###ChargenThin", &CustomChargenSettings.Thin, 0.0f, 1.0f, "Character Appearance (Thin): %f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&CustomChargenSettings.Thin, 0.0f, 1.0f);

					ImGui::SetNextItemWidth(451.0f);
					ImGui::SliderFloat("###ChargenMuscular", &CustomChargenSettings.Muscular, 0.0f, 1.0f, "Character Appearance (Muscular): %f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&CustomChargenSettings.Muscular, 0.0f, 1.0f);

					ImGui::SetNextItemWidth(451.0f);
					ImGui::SliderFloat("###ChargenLarge", &CustomChargenSettings.Large, 0.0f, 1.0f, "Character Appearance (Large): %f");
					if (ImGui::IsItemActive()) AllowDrag = false;
					ValidateFloat(&CustomChargenSettings.Large, 0.0f, 1.0f);
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Utility###UtilityTab"))
			{
				if (ImGui::CollapsingHeader("Utility"))
				{
					ButtonToggle("Draw Local Player Data", &CustomUtilitySettings.DebugPlayer);
					ImGui::SameLine(235.0f);
					ButtonToggle("ESP Debug Mode", &CustomUtilitySettings.DebugEsp);

					if (CustomUtilitySettings.PtrFormid)
					{
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 0.3f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.0f, 0.4f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 1.0f, 0.0f, 0.5f));
						if (ImGui::Button("Get Pointer###GetPointerEnabled", ImVec2(224.0f, 0.0f)))
						{
							GetPtrResult = GetPtr(CustomUtilitySettings.PtrFormid);
						}
						ImGui::PopStyleColor(3);
					}
					else
					{
						ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.3f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.4f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
						ImGui::Button("Get Pointer###GetPointerDisabled", ImVec2(224.0f, 0.0f));
						ImGui::PopStyleColor(3);
						ImGui::PopItemFlag();
					}

					ImGui::SameLine(235.0f);
					char PtrFormidText[sizeof("00000000")];
					sprintf_s(PtrFormidText, "%08lX", CustomUtilitySettings.PtrFormid);
					ImGui::SetNextItemWidth(80.0f);
					if (ImGui::InputText("###PtrFormidText", PtrFormidText, sizeof(PtrFormidText), ImGuiInputTextFlags_CharsHexadecimal))
					{
						GetPtrResult = 0;
					}
					if (ImGui::IsItemActive()) AllowDrag = false;
					sscanf_s(PtrFormidText, "%08lX", &CustomUtilitySettings.PtrFormid);

					ImGui::SameLine(318.0f);
					char PtrPointerText[sizeof("0000000000000000")];
					sprintf_s(PtrPointerText, "%016llX", GetPtrResult);
					ImGui::SetNextItemWidth(141.0f);
					ImGui::InputText("###PtrPointerText", PtrPointerText, sizeof(PtrPointerText), ImGuiInputTextFlags_ReadOnly);
					if (ImGui::IsItemActive()) AllowDrag = false;

					if (CustomUtilitySettings.AddressFormid)
					{
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 0.3f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.0f, 0.4f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 1.0f, 0.0f, 0.5f));
						if (ImGui::Button("Get Address###GetAddressEnabled", ImVec2(224.0f, 0.0f)))
						{
							GetAddressResult = GetAddress(CustomUtilitySettings.AddressFormid);
						}
						ImGui::PopStyleColor(3);
					}
					else
					{
						ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.3f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.4f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
						ImGui::Button("Get Address###GetAddressDisabled", ImVec2(224.0f, 0.0f));
						ImGui::PopStyleColor(3);
						ImGui::PopItemFlag();
					}

					ImGui::SameLine(235.0f);
					char AddressFormidText[sizeof("00000000")];
					sprintf_s(AddressFormidText, "%08lX", CustomUtilitySettings.AddressFormid);
					ImGui::SetNextItemWidth(80.0f);
					if (ImGui::InputText("###AddressFormidText", AddressFormidText, sizeof(AddressFormidText), ImGuiInputTextFlags_CharsHexadecimal))
					{
						GetAddressResult = 0;
					}
					if (ImGui::IsItemActive()) AllowDrag = false;
					sscanf_s(AddressFormidText, "%08lX", &CustomUtilitySettings.AddressFormid);

					ImGui::SameLine(318.0f);
					char AddressPointerText[sizeof("0000000000000000")];
					sprintf_s(AddressPointerText, "%016llX", GetAddressResult);
					ImGui::SetNextItemWidth(141.0f);
					ImGui::InputText("###AddressPointerText", AddressPointerText, sizeof(AddressPointerText), ImGuiInputTextFlags_ReadOnly);
					if (ImGui::IsItemActive()) AllowDrag = false;
				}

				if (ImGui::CollapsingHeader("Reference Editor"))
				{
					ButtonToggle("Source Formid###SwapperSourceFormidToggle", &SwapperSourceToggle);
					ImGui::SameLine(235.0f);
					char SourceFormidText[sizeof("00000000")];
					sprintf_s(SourceFormidText, "%08lX", CustomSwapperSettings.SourceFormid);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::InputText("###SwapperSourceFormidText", SourceFormidText, sizeof(SourceFormidText), ImGuiInputTextFlags_CharsHexadecimal);
					if (ImGui::IsItemActive()) AllowDrag = false;
					sscanf_s(SourceFormidText, "%08lX", &CustomSwapperSettings.SourceFormid);

					ButtonToggle("Destination Formid###SwapperDestinationFormidToggle", &SwapperDestinationToggle);
					ImGui::SameLine(235.0f);
					char DestinationFormidText[sizeof("00000000")];
					sprintf_s(DestinationFormidText, "%08lX", CustomSwapperSettings.DestinationFormid);
					ImGui::SetNextItemWidth(224.0f);
					ImGui::InputText("###SwapperDestinationFormidText", DestinationFormidText, sizeof(DestinationFormidText), ImGuiInputTextFlags_CharsHexadecimal);
					if (ImGui::IsItemActive()) AllowDrag = false;
					sscanf_s(DestinationFormidText, "%08lX", &CustomSwapperSettings.DestinationFormid);

					if (SwapperSourceToggle && CustomSwapperSettings.SourceFormid && SwapperDestinationToggle && CustomSwapperSettings.DestinationFormid)
					{
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 0.3f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.0f, 0.4f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 1.0f, 0.0f, 0.5f));
						if (ImGui::Button("Edit Reference (Overwrite Destination)###EditReferenceEnabled", ImVec2(451.0f, 0.0f)))
						{
							if (ReferenceSwap(&CustomSwapperSettings.SourceFormid, &CustomSwapperSettings.DestinationFormid))
							{
								CustomSwapperSettings.DestinationFormid = CustomSwapperSettings.SourceFormid;
								SwapperSourceToggle = false;
								SwapperDestinationToggle = false;
							}
						}
						ImGui::PopStyleColor(3);
					}
					else
					{
						ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.3f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.4f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
						ImGui::Button("Edit Reference (Overwrite Destination)###EditReferenceDisabled", ImVec2(451.0f, 0.0f));
						ImGui::PopStyleColor(3);
						ImGui::PopItemFlag();
					}
				}

				if (ImGui::CollapsingHeader("Item Transferring"))
				{
					SmallButtonToggle("Source###TransferSourceFormidToggle", &TransferSourceToggle);

					ImGui::SameLine(122.0f);
					char SourceFormidText[sizeof("00000000")];
					sprintf_s(SourceFormidText, "%08lX", CustomTransferSettings.SourceFormid);
					ImGui::SetNextItemWidth(110.0f);
					ImGui::InputText("###TransferSourceFormidText", SourceFormidText, sizeof(SourceFormidText), ImGuiInputTextFlags_CharsHexadecimal);
					if (ImGui::IsItemActive()) AllowDrag = false;
					sscanf_s(SourceFormidText, "%08lX", &CustomTransferSettings.SourceFormid);
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 0.3f));
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.0f, 0.4f));
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 1.0f, 0.0f, 0.5f));
					ImGui::SameLine(235.0f);
					if (ImGui::Button("Get Player###TransferSourceLocalPlayer", ImVec2(110.0f, 0.0f)))
					{
						CustomTransferSettings.SourceFormid = GetLocalPlayerFormid();
					}
					ImGui::SameLine(349.0f);
					if (ImGui::Button("Get STASH###TransferSourceSTASH", ImVec2(110.0f, 0.0f)))
					{
						CustomTransferSettings.SourceFormid = GetStashFormid();
					}
					ImGui::PopStyleColor(3);

					SmallButtonToggle("Destination###TransferDestinationFormidToggle", &TransferDestinationToggle);
					ImGui::SameLine(122.0f);
					char DestinationFormidText[sizeof("00000000")];
					sprintf_s(DestinationFormidText, "%08lX", CustomTransferSettings.DestinationFormid);
					ImGui::SetNextItemWidth(110.0f);
					ImGui::InputText("###TransferDestinationFormidText", DestinationFormidText, sizeof(DestinationFormidText), ImGuiInputTextFlags_CharsHexadecimal);
					if (ImGui::IsItemActive()) AllowDrag = false;
					sscanf_s(DestinationFormidText, "%08lX", &CustomTransferSettings.DestinationFormid);
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 0.3f));
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.0f, 0.4f));
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 1.0f, 0.0f, 0.5f));
					ImGui::SameLine(235.0f);
					if (ImGui::Button("Get Player###TransferDestinationLocalPlayer", ImVec2(110.0f, 0.0f)))
					{
						CustomTransferSettings.DestinationFormid = GetLocalPlayerFormid();
					}
					ImGui::SameLine(349.0f);
					if (ImGui::Button("Get STASH###TransferDestinationSTASH", ImVec2(110.0f, 0.0f)))
					{
						CustomTransferSettings.DestinationFormid = GetStashFormid();
					}
					ImGui::PopStyleColor(3);

					bool AllowTransfer = false;

					if (TransferSourceToggle && CustomTransferSettings.SourceFormid && TransferDestinationToggle && CustomTransferSettings.DestinationFormid)
					{
						if (CustomTransferSettings.UseWhitelist)
						{
							AllowTransfer = CheckItemTransferList();
						}
						else
						{
							AllowTransfer = true;
						}
					}

					if (AllowTransfer)
					{
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 0.3f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.0f, 0.4f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 1.0f, 0.0f, 0.5f));
						if (ImGui::Button("Transfer Items###TransferItemsEnabled", ImVec2(451.0f, 0.0f)))
						{
							TransferItems(CustomTransferSettings.SourceFormid, CustomTransferSettings.DestinationFormid);
						}
						ImGui::PopStyleColor(3);
					}
					else
					{
						ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.3f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.4f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
						ImGui::Button("Transfer Items###TransferItemsDisabled", ImVec2(451.0f, 0.0f));
						ImGui::PopStyleColor(3);
						ImGui::PopItemFlag();
					}

					LargeButtonToggle("Use Item Transfer Whitelist", &CustomTransferSettings.UseWhitelist);
					LargeButtonToggle("Use Item Transfer Blacklist", &CustomTransferSettings.UseBlacklist);

					if (ImGui::CollapsingHeader("Item Transfer Whitelist Settings"))
					{
						for (int i = 0; i < 32; i++)
						{
							char WhitelistedText[sizeof("Transfer Whitelist Slot: 31")];
							char WhitelistText[sizeof("###ItemTransferWhitelist31")];
							sprintf_s(WhitelistedText, "Transfer Whitelist Slot: %d", i);
							sprintf_s(WhitelistText, "###ItemTransferWhitelist%d", i);
							ButtonToggle(WhitelistedText, &CustomTransferSettings.Whitelisted[i]);
							ImGui::SameLine(235.0f);
							char FormidText[sizeof("00000000")];
							sprintf_s(FormidText, "%08lX", CustomTransferSettings.Whitelist[i]);
							ImGui::SetNextItemWidth(224.0f);
							ImGui::InputText(WhitelistText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
							if (ImGui::IsItemActive()) AllowDrag = false;
							sscanf_s(FormidText, "%08lX", &CustomTransferSettings.Whitelist[i]);
						}
					}

					if (ImGui::CollapsingHeader("Item Transfer Blacklist Settings"))
					{
						for (int i = 0; i < 32; i++)
						{
							char BlacklistedText[sizeof("Transfer Blacklist Slot: 31")];
							char BlacklistText[sizeof("###ItemTransferBlacklist31")];
							sprintf_s(BlacklistedText, "Transfer Blacklist Slot: %d", i);
							sprintf_s(BlacklistText, "###ItemTransferBlacklist%d", i);
							ButtonToggle(BlacklistedText, &CustomTransferSettings.Blacklisted[i]);
							ImGui::SameLine(235.0f);
							char FormidText[sizeof("00000000")];
							sprintf_s(FormidText, "%08lX", CustomTransferSettings.Blacklist[i]);
							ImGui::SetNextItemWidth(224.0f);
							ImGui::InputText(BlacklistText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
							if (ImGui::IsItemActive()) AllowDrag = false;
							sscanf_s(FormidText, "%08lX", &CustomTransferSettings.Blacklist[i]);
						}
					}
				}

				if (ImGui::CollapsingHeader("Nuke Codes"))
				{
					ButtonToggle("Automatic Nuke Codes", &CustomNukeCodeSettings.AutomaticNukeCodes);
					ImGui::SameLine(235.0f);
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 0.3f));
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.0f, 0.4f));
					ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 1.0f, 0.0f, 0.5f));
					if (ImGui::Button("Get Nuke Codes", ImVec2(224.0f, 0.0f)))
					{
						GetNukeCode(0x000921AE, AlphaCode);
						GetNukeCode(0x00092213, BravoCode);
						GetNukeCode(0x00092214, CharlieCode);
					}
					ImGui::PopStyleColor(3);

					ButtonToggle("Draw Nuke Code Alpha", &CustomNukeCodeSettings.DrawCodeAlpha);
					ImGui::SameLine(255.0f);
					ImGui::Text("%d %d %d %d %d %d %d %d - Alpha", AlphaCode[0], AlphaCode[1], AlphaCode[2], AlphaCode[3], AlphaCode[4], AlphaCode[5], AlphaCode[6], AlphaCode[7]);

					ButtonToggle("Draw Nuke Code Bravo", &CustomNukeCodeSettings.DrawCodeBravo);
					ImGui::SameLine(255.0f);
					ImGui::Text("%d %d %d %d %d %d %d %d - Bravo", BravoCode[0], BravoCode[1], BravoCode[2], BravoCode[3], BravoCode[4], BravoCode[5], BravoCode[6], BravoCode[7]);

					ButtonToggle("Draw Nuke Code Charlie", &CustomNukeCodeSettings.DrawCodeCharlie);
					ImGui::SameLine(255.0f);
					ImGui::Text("%d %d %d %d %d %d %d %d - Charlie", CharlieCode[0], CharlieCode[1], CharlieCode[2], CharlieCode[3], CharlieCode[4], CharlieCode[5], CharlieCode[6], CharlieCode[7]);
				}
				
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Teleporter###TeleporterTab"))
			{
				for (int i = 0; i < 16; i++)
				{
					char TeleportHeaderText[sizeof("Teleporter Slot: 15")];
					sprintf_s(TeleportHeaderText, "Teleport Slot: %d", i);
					if (ImGui::CollapsingHeader(TeleportHeaderText))
					{
						ImGui::SetNextItemWidth(110.0f);
						char TeleportDestinationTextX[sizeof("###TeleportDestinationX15")];
						sprintf_s(TeleportDestinationTextX, "###TeleportDestinationX%d", i);
						ImGui::InputFloat(TeleportDestinationTextX, &CustomTeleportSettings.TeleportEntryData[i].Destination[0]);
						if (ImGui::IsItemActive()) AllowDrag = false;
						ImGui::SameLine(122.0f);
						ImGui::SetNextItemWidth(110.0f);
						char TeleportDestinationTextY[sizeof("###TeleportDestinationY15")];
						sprintf_s(TeleportDestinationTextY, "###TeleportDestinationY%d", i);
						ImGui::InputFloat(TeleportDestinationTextY, &CustomTeleportSettings.TeleportEntryData[i].Destination[1]);
						if (ImGui::IsItemActive()) AllowDrag = false;
						ImGui::SameLine(235.0f);
						ImGui::SetNextItemWidth(110.0f);
						char TeleportDestinationTextZ[sizeof("###TeleportDestinationZ15")];
						sprintf_s(TeleportDestinationTextZ, "###TeleportDestinationZ%d", i);
						ImGui::InputFloat(TeleportDestinationTextZ, &CustomTeleportSettings.TeleportEntryData[i].Destination[2]);
						if (ImGui::IsItemActive()) AllowDrag = false;
						ImGui::SameLine(349.0f);
						ImGui::SetNextItemWidth(110.0f);
						char TeleportDestinationTextW[sizeof("###TeleportDestinationW15")];
						sprintf_s(TeleportDestinationTextW, "###TeleportDestinationW%d", i);
						ImGui::InputFloat(TeleportDestinationTextW, &CustomTeleportSettings.TeleportEntryData[i].Destination[3]);
						if (ImGui::IsItemActive()) AllowDrag = false;

						char FormidLabelText[sizeof("###TeleportCellFormid15")];
						sprintf_s(FormidLabelText, "###TeleportCellFormid%d", i);
						char FormidText[sizeof("00000000")];
						sprintf_s(FormidText, "%08lX", CustomTeleportSettings.TeleportEntryData[i].CellFormid);
						ImGui::SetNextItemWidth(110.0f);
						ImGui::InputText(FormidLabelText, FormidText, sizeof(FormidText), ImGuiInputTextFlags_CharsHexadecimal);
						if (ImGui::IsItemActive()) AllowDrag = false;
						sscanf_s(FormidText, "%08lX", &CustomTeleportSettings.TeleportEntryData[i].CellFormid);
						ImGui::SameLine(122.0f);
						char TeleportDestinationEnabledText[sizeof("Set Position###TeleportDestinationEnabled15")];
						sprintf_s(TeleportDestinationEnabledText, "Set Position###TeleportDestinationEnabled%d", i);
						char TeleportDestinationDisabledText[sizeof("Set Position###TeleportDestinationDisabled15")];
						sprintf_s(TeleportDestinationDisabledText, "Set Position###TeleportDestinationDisabled%d", i);
						if (!CustomTeleportSettings.TeleportEntryData[i].DisableSaving)
						{
							ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 0.3f));
							ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.0f, 0.4f));
							ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 1.0f, 0.0f, 0.5f));
							if (ImGui::Button(TeleportDestinationEnabledText, ImVec2(110.0f, 0.0f))) GetTeleportPosition(i);
							ImGui::PopStyleColor(3);
						}
						else
						{
							ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
							ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.3f));
							ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.4f));
							ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
							ImGui::Button(TeleportDestinationDisabledText, ImVec2(110.0f, 0.0f));
							ImGui::PopStyleColor(3);
							ImGui::PopItemFlag();
						}
						ImGui::SameLine(235.0f);
						char DisableSavingText[sizeof("Lock###DisableSaving15")];
						sprintf_s(DisableSavingText, "Lock###DisableSaving%d", i);
						SmallButtonToggle(DisableSavingText, &CustomTeleportSettings.TeleportEntryData[i].DisableSaving);
						ImGui::SameLine(349.0f);
						char TeleportRequestEnabledText[sizeof("Teleport###TeleportRequestEnabled15")];
						sprintf_s(TeleportRequestEnabledText, "Teleport###TeleportRequestEnabled%d", i);
						char TeleportRequestDisabledText[sizeof("Teleport###TeleportRequestDisabled15")];
						sprintf_s(TeleportRequestDisabledText, "Teleport###TeleportRequestDisabled%d", i);
						if (CustomTeleportSettings.TeleportEntryData[i].CellFormid)
						{
							ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 0.3f));
							ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 1.0f, 0.0f, 0.4f));
							ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 1.0f, 0.0f, 0.5f));
							if (ImGui::Button(TeleportRequestEnabledText, ImVec2(110.0f, 0.0f))) RequestTeleport(i);
							ImGui::PopStyleColor(3);
						}
						else
						{
							ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
							ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 0.3f));
							ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 0.0f, 0.0f, 0.4f));
							ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.0f, 0.0f, 0.5f));
							ImGui::Button(TeleportRequestDisabledText, ImVec2(110.0f, 0.0f));
							ImGui::PopStyleColor(3);
							ImGui::PopItemFlag();
						}
					}
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("BitMsgWriter###BitMsgWriterTab"))
			{
				LargeButtonToggle("Message Sender Enabled", &AllowMessages);
				ImGui::EndTabItem();
			}
			
			ImGui::EndTabBar();
		}

		if (ImGui::GetActiveID() == ImGui::GetWindowScrollbarID(ImGui::GetCurrentWindow(), ImGuiAxis_Y))
		{
			AllowDrag = false;
		}

		if (ImGui::IsMouseDragging(0) && AllowDrag)
		{
			if (!PointerDrag)
			{
				PointerOrigin = ImGui::GetMousePos();
				PointerDrag = true;
			}
		}
		else
		{
			if (PointerDrag)
			{
				PointerOrigin = { 0.0f, 0.0f };
				PointerDrag = false;
			}
		}

		if (PointerDrag)
		{
			DragMenu();
		}
	}

	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

bool ImGuiInitialize()
{
	ImGui::CreateContext();
	ImGuiContextCreated = true;

	if (!ImGui_ImplWin32_Init(WindowHwnd)) return false;
	else ImGuiWin32Initialized = true;

	if (!ImGui_ImplDX9_Init(D3D9Device)) return false;
	else ImGuiD3D9Initialized = true;

	return true;
}

void ImGuiCleanup()
{
	if (ImGuiD3D9Initialized)
	{
		ImGui_ImplDX9_Shutdown();
		ImGuiD3D9Initialized = false;
	}

	if (ImGuiWin32Initialized)
	{
		ImGui_ImplWin32_Shutdown();
		ImGuiWin32Initialized = false;
	}

	if (ImGuiContextCreated)
	{
		ImGui::DestroyContext();
		ImGuiContextCreated = false;
	}
}
