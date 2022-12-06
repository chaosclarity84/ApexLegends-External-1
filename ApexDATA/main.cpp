#include <Windows.h>
#include <iostream>
#include "overlay.h"
#include "memory.h"
#include "struct.h"
#include "auth.hpp"
#include "protect/protectmain.h"
#include "xorstr.hpp"
ImColor cRainbow = ImColor(255,255,182);
	
bool showmenu;
bool esp = true;
bool corneredbox = false;
bool aimbot = true;
bool NoRecoilCheckBox = true;
bool Snapline = true;
bool healthbar = true;
bool paintinside = true;
bool Distance = true;
bool headesp = false;
bool glow;
bool itemglow;
bool skinchanger;
float height;
float width;
float middle;
int espmetre = 300;
int fov = 60;
int smooth = 6;
#define COLOUR(x) x/255
Vector3 oldPunch = { 0.f, 0.f, 0.f };
void NoRecoil()
{
	while (true)
	{
		glocalplayer = driver.read<uintptr_t>(g_base + LOCALPLAYER);
		if (NoRecoilCheckBox)
		{
			Vector3 viewAngles = driver.read<Vector3>(glocalplayer + VIEWANGLES);
			Vector3 punchAngle = driver.read<Vector3>(glocalplayer + AIMPUNCH);
			Vector3 newAngle = viewAngles + (oldPunch - punchAngle);
			newAngle.Normalize();
			driver.write<Vector2>(glocalplayer + VIEWANGLES, { newAngle.x, newAngle.y });
			driver.write<Vector2>(glocalplayer + VIEWANGLES, { newAngle.x, newAngle.y });
			driver.write<Vector2>(glocalplayer + VIEWANGLES, { newAngle.x, newAngle.y });
			oldPunch = punchAngle;
		}

		if (skinchanger)
		{
			if (driver.read<int>(GetWeapon(glocalplayer) + NSKIN) != static_cast<int>(skin_id)) {
				driver.write<int>(GetWeapon(glocalplayer) + NSKIN, static_cast<int>(skin_id));
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

bool GetKey(int key)
{
	realkey = key;
	return true;
}
void ChangeKey(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				aimkey = i;
				keystatus = 0;
				return;
			}
		}
	}
}
static const char* keyNames[] = {
	"",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};
static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}
void HotkeyButton(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
		Items_ArrayGetter(keyNames, aimkey, &preview_value);

	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = skCrypt("Select Key");
	else
		aimkeys = preview_value;

	if (status == 1)
	{
		aimkeys = skCrypt("Press key to bind");
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 20)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}


static int widthh = 576;
static int heightt = 326;
static int MenuSayfasi = 1;
static int tab = 1;
void draw_menu()
{
	auto s = ImVec2{}, p = ImVec2{}, gs = ImVec2{ 620, 485 };
	ImGui::SetNextWindowSize(ImVec2(gs));
	ImGui::SetNextWindowBgAlpha(1.0f);
	ImGui::Begin(skCrypt("ALIEN CHEATS - (ver. 0.0.2)"), NULL, ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
	{

		ImGui::SetCursorPosX(121);
		s = ImVec2(ImGui::GetWindowSize().x - ImGui::GetStyle().WindowPadding.x * 2, ImGui::GetWindowSize().y - ImGui::GetStyle().WindowPadding.y * 2); p = ImVec2(ImGui::GetWindowPos().x + ImGui::GetStyle().WindowPadding.x, ImGui::GetWindowPos().y + ImGui::GetStyle().WindowPadding.y); auto draw = ImGui::GetWindowDrawList();
		draw->AddRectFilled(p, ImVec2(p.x + s.x, p.y + s.y), ImColor(15, 17, 19), 5);
		draw->AddRectFilled(ImVec2(p.x, p.y + 40), ImVec2(p.x + s.x, p.y + s.y), ImColor(18, 20, 21), 5, ImDrawCornerFlags_Bot);

		//draw->AddImage(lg, ImVec2(p.x - 60, p.y - 30), ImVec2(p.x + 110, p.y + 70), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 102));

		ImGui::PushFont(icons);
		auto logo_size = ImGui::CalcTextSize(skCrypt("A"));
		draw->AddText(ImVec2(p.x + 28 - logo_size.x / 2, p.y + 29 - (logo_size.y / 2) + 4), cRainbow, skCrypt("A"));
		ImGui::PopFont();

		ImGui::PushFont(main_font2);
		auto logo_size2 = ImGui::CalcTextSize(skCrypt("A"));
		draw->AddText(ImVec2(p.x + 42 - logo_size2.x / 2, p.y + 29 - logo_size2.y), cRainbow, skCrypt("AlienCheats"));
		ImGui::PopFont();

		ImGui::PushFont(main_font);
		ImGui::BeginGroup();
		ImGui::SameLine(110);
		if (ImGui::tab(skCrypt("AIMBOT"), tab == 1))tab = 1; ImGui::SameLine();
		if (ImGui::tab(skCrypt("Visuals"), tab == 2))tab = 2;
		ImGui::EndGroup();
		ImGui::PopFont();

		if (tab == 1)
		{
			ImGui::PushFont(main_font);
			{//left upper
				ImGui::SetCursorPosY(50);
				ImGui::BeginGroup();
				ImGui::SetCursorPosX(15);
				ImGui::MenuChild(skCrypt("Aimbot"), ImVec2(285, 415), false);
				{
					ImGui::Checkbox(skCrypt("AimBot"), &aimbot);
					ImGui::Text(skCrypt("")); ImGui::SameLine(); HotkeyButton(aimkey, ChangeKey, keystatus); ImGui::SameLine(); ImGui::Text(skCrypt("Aimbot Key"));
					ImGui::Text(skCrypt("")); ImGui::SameLine(8); ImGui::Combo(skCrypt("Hitbox"), &selected_hit, hitbox, IM_ARRAYSIZE(hitbox));
					ImGui::Checkbox(skCrypt("NoRecoil"), &NoRecoilCheckBox);
					ImGui::SliderInt(skCrypt("AimFov"), &fov, 1.0f, 280.f);
					ImGui::SliderInt(skCrypt("Smooth"), &smooth, 1.0f, 15.0f);
				}	
				ImGui::EndChild();
				ImGui::EndGroup();
			}
			{//right
				ImGui::SetCursorPosY(50);
				ImGui::BeginGroup();
				ImGui::SetCursorPosX(320);
				ImGui::MenuChild(skCrypt(" "), ImVec2(285, 415), false);
				{

				}
				ImGui::EndChild();
				ImGui::EndGroup();
				ImGui::PopFont();
			}
		}
		if (tab == 2)
		{
			ImGui::PushFont(main_font);
			{//left upper
				ImGui::SetCursorPosY(50);
				ImGui::BeginGroup();
				ImGui::SetCursorPosX(15);
				ImGui::MenuChild(skCrypt("esp"), ImVec2(285, 415), false);
				{
					ImGui::Checkbox(skCrypt("2D Box"), &esp);
					if (esp == true)
					{
						corneredbox = false;
					}
					ImGui::Checkbox(skCrypt("Cornered Box"), &corneredbox);
					if (corneredbox == true)
					{
						esp = false;
					}
					ImGui::Checkbox(skCrypt("Fill Box"), &paintinside);
					ImGui::Checkbox(skCrypt("Snapline"), &Snapline);
					ImGui::Checkbox(skCrypt("Health ESP"), &healthbar);
					ImGui::Checkbox(skCrypt("Distance Esp"), &Distance);
					ImGui::SliderInt(skCrypt("Distance"), &espmetre, 100.0f, 1000.f);
				}
				ImGui::EndChild();
				ImGui::EndGroup();
			}
			{//right
				ImGui::SetCursorPosY(50);
				ImGui::BeginGroup();
				ImGui::SetCursorPosX(320);
				ImGui::MenuChild(skCrypt("visuals"), ImVec2(285, 415), false);
				{
					ImGui::Checkbox(skCrypt("Glow"), &glow);
					ImGui::Checkbox(skCrypt("Item Glow"), &itemglow);
					ImGui::Checkbox(skCrypt("Skin Changer"), &skinchanger);
					ImGui::SliderInt(skCrypt("SkinID"), &skin_id, 1.0f, 20.f);
				}
				ImGui::EndChild();
				ImGui::EndGroup();
				ImGui::PopFont();
			}
		}
	}
}

int r = 255;
int g = 255;
int b = 255;
std::string PlayerName(DWORD64 pEntity)
{
	if (!pEntity)
		return "";
	int INDEX = driver.read<int>((pEntity + 0x8) - 0x10000);
	DWORD64 namelist = driver.read<DWORD64>(g_base + NameList);
	DWORD64 nameent = driver.read<DWORD64>(namelist + ((INDEX - 1) << 4));
	std::string name = driver.read<std::string>(nameent);
	return name;
}
std::string getIName(uint64_t Entity)
{
	uint64_t nameAddress = driver.read<uint64_t>(Entity + m_iName);
	char buffer[255];
	driver.read_array(nameAddress, buffer, 255);

	return std::string(buffer);
}
int get_item_id(uintptr_t entity) {
	return driver.read<int>(entity + ITEM_ID);
}
struct GlowMode
{
	int8_t GeneralGlowMode, BorderGlowMode, BorderSize, TransparentLevel;
};

enum WeaponId
{
	r301 = 0,
	sentinel = 1,
	bow = 2,
	sheila = 9, //placed
	rampage = 17,
	melee_survival = 25,
	mobile_sheila = 80, //mobile
	snipersmark = 100,
	alternator,
	re45,
	chargerifle,
	devotion,
	longbow,
	havoc,
	eva8,
	flatline,
	scout,
	hemlock,
	kraber,
	lstar,
	mastiff,
	mozambique,
	prowler,
	peacekeeper,
	r99,
	p2020,
	spitfire,
	tripletake,
	wingman,
	volt,
	repeater,
	car, //124
	knife = 126,
	thermite = 127,
	frag_grenade = 128,
	arcstar = 129,
};

void DrawHealthBarr(float health, Vector3 tempHead, Vector3 tempFeet)
{
	{
		float height = (tempHead.y - tempFeet.y);
		float width = height / 6.0f;
		float Entity_x = tempFeet.x - width;
		float Entity_y = tempFeet.y;
		float flBoxes = std::ceil(health / 10.f);
		float flX = Entity_x + 6; float flY = Entity_y;
		float flHeight = height / 10.f;
		float flMultiplier = 12 / 360.f; flMultiplier *= flBoxes - 1;
		int G = (255 * health / 100);
		int R = 255 - G;
		RGBA healthcol = { R, G, 0, 255 };

		DrawFilledRect(flX, flY, 2, flHeight * 10 + 2, &Col.black);
		DrawFilledRect(flX + 2, flY, 2, flHeight * 10 + 2, &Col.black);

		DrawFilledRect(flX + 1, flY, 2, flHeight * flBoxes + 1, &healthcol);
	}
}
static void DrawFilledRectImGui(int x, int y, int w, int h, ImVec4 color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(color), 0, 0);
}
void ESP(DWORD64 pEntity, Matrix m, DWORD64 Shield, AimContext* Ctx)
{
	Vector3 entHead = BonePosition(pEntity, 8); // get head position
	Vector3 w2sHead = entHead.ScreenPosition(m); if (w2sHead.z <= 0.f) return;


	Vector3 entPos = Position(pEntity);
	Vector3 w2sPos = entPos.ScreenPosition(m); if (w2sPos.z <= 0.f) return;

	height = abs(abs(w2sHead.y) - abs(w2sPos.y));
	width = height / 2.f;
	middle = w2sPos.x - (width / 2.f);


	DWORD64 Health = driver.read<DWORD64>(pEntity + m_iHealth);

	int G = (255 * Health / 100);
	int R = 255 - G;
	RGBA healthcol = { R, G, 0, 255 };
	std::string healthESP = std::to_string(Health);
	std::string ShieldESP = std::to_string(Shield / 125);
	//std::string PlayerNAME = PlayerName(pEntity).c_str();

	int distance = (int)distanceToLocal(pEntity) / 50.f;
	std::string DistanceESP = "[" + std::to_string(distance) + "m]";


	if (Health <= 0) return;

	if (distance <= espmetre) {
		if (abs(Ctx->crosshairX - w2sPos.x) < abs(Ctx->crosshairX - Ctx->closestX) && abs(Ctx->crosshairX - w2sPos.x) < Ctx->FOV2 && abs(Ctx->crosshairY - w2sPos.y) < abs(Ctx->crosshairY - Ctx->closestY) && abs(Ctx->crosshairY - w2sPos.y) < Ctx->FOV2)
		{
			ImGui::SetNextWindowSize(ImVec2(180, 60));
			ImGui::SetNextWindowPos(ImVec2(1670, 1080 / 1080));
			ImGui::Begin(skCrypt("TargetPlayer"), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

			//ImGui::Text("Name:"); ImGui::SameLine();
			//ImGui::TextColored(ImColor(255, 255, 255), PlayerNAME.c_str());

			ImGui::Text("Health:"); ImGui::SameLine();
			ImGui::TextColored(ImColor(R, G, 0), healthESP.c_str());

			ImGui::Text("Shield:"); ImGui::SameLine();
			ImGui::TextColored(ImColor(30, 144, 255), ShieldESP.c_str());

			ImGui::Text("Distance:"); ImGui::SameLine();
			ImGui::TextColored(ImColor(255, 255, 255), DistanceESP.c_str());

			ImGui::End();
		}

		//uintptr_t actWeaponID = driver.read<uintptr_t>(pEntity + M_LASTESTPRIMARYWINDOWS) & 0xFFFF;
		//std::string ActiveWeaponID = std::to_string(actWeaponID);

		//DrawString(13, w2sHead.x + 1, (w2sHead.y + 20), &Col.white, true, false, ActiveWeaponID.c_str());

		//if (!IsAlive(pEntity))
		//	return;
		if (pEntity == 0)
			return;
		if (IsTeam(glocalplayer, pEntity))
			return;

		if (!isKnocked(pEntity))
		{
			if (esp)
			{
				DrawRectImGui(w2sHead.x - (width / 2) - 1, w2sHead.y - 1, width + 2, height + 2, ImVec4(0.f, 0.f, 0.f, 255.f), 1.0f);
				DrawRectImGui(w2sHead.x - (width / 2), w2sHead.y, width, height, ImVec4(255.f, 255.f, 255.f, 255.f), 1.f);
				DrawRectImGui(w2sHead.x - (width / 2) + 1, w2sHead.y + 1, width - 2, height - 2, ImVec4(0.f, 0.f, 0.f, 255.f), 1.0f);
			}	
			if (corneredbox)
			{
				DrawCorneredBox(w2sHead.x - (width / 2) - 1, w2sHead.y - 1, width + 2, height + 2, ImVec4(0.f, 0.f, 0.f, 255.f), 1.0f);
				DrawCorneredBox(w2sHead.x - (width / 2), w2sHead.y, width, height, ImVec4(255.f, 255.f, 255.f, 255.f), 1.0f);
				DrawCorneredBox(w2sHead.x - (width / 2) + 1, w2sHead.y + 1, width - 2, height - 2, ImVec4(0.f, 0.f, 0.f, 255.f), 1.0f);
			}
			if (paintinside)
			{
				DrawFilledRectImGui(w2sPos.x - (width / 2), w2sHead.y, width, height, ImVec4(COLOUR(0.0f), COLOUR(0.0f), COLOUR(0.0f), COLOUR(100.0f)));
			}
			if (Snapline)
			{
				DrawLine(ImVec2(GetSystemMetrics(SM_CXSCREEN) / 2, GetSystemMetrics(SM_CYSCREEN)), ImVec2(w2sPos.x, w2sPos.y), ImGui::ColorConvertFloat4ToU32(ImVec4(0.f, 0.f, 0.f, 255.f)), 1.f); // ASAGIDAN
			}
			if (headesp)
			{
				ImGui::GetOverlayDrawList()->AddCircle(ImVec2(w2sHead.x, w2sHead.y), 4, ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 155)), 12, 0);
				ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(w2sHead.x, w2sHead.y), 3, ImGui::ColorConvertFloat4ToU32(ImVec4(r, g, b, 155)), 12);
			}
			if (Distance)
			{
				DrawString(12, w2sPos.x, (w2sPos.y + 15), &Col.white, true, true, DistanceESP.c_str());
			}
			if (healthbar)
			{
				float entHp = Health;
				if (entHp > 101) entHp = 100;
				float HealthHeightCalc = ((float)entHp / 100) * (float)height;

				DrawFilledRectImGui(w2sHead.x - (width / 2), w2sHead.y, 2, height, ImVec4(COLOUR(30.0f), COLOUR(30.0f), COLOUR(30.0f), COLOUR(220.0f)));
				DrawFilledRectImGui(w2sHead.x - (width / 2), w2sHead.y, 2, HealthHeightCalc, ImVec4(COLOUR(80.0f), COLOUR(220.0f), COLOUR(100.0f), COLOUR(255.0f)));
			}
		}
		else
		{
			DrawString(12, w2sHead.x + 1, (w2sHead.y), &Col.red, true, true, "WOUNDED");
		}
		//DrawLine(ImVec2(BonePosition(pEntity, 8).ScreenPosition(m).x, BonePosition(pEntity, 8).ScreenPosition(m).y), ImVec2(BonePosition(pEntity, 7).ScreenPosition(m).x, BonePosition(pEntity, 7).ScreenPosition(m).y), ImColor(r, g, b), 1.f);
		//DrawLine(ImVec2(BonePosition(pEntity, 7).ScreenPosition(m).x, BonePosition(pEntity, 7).ScreenPosition(m).y), ImVec2(BonePosition(pEntity, 5).ScreenPosition(m).x, BonePosition(pEntity, 5).ScreenPosition(m).y), ImColor(r, g, b), 1.f);
		//DrawLine(ImVec2(BonePosition(pEntity, 5).ScreenPosition(m).x, BonePosition(pEntity, 5).ScreenPosition(m).y), ImVec2(BonePosition(pEntity, 11).ScreenPosition(m).x, BonePosition(pEntity, 11).ScreenPosition(m).y), ImColor(r, g, b), 1.f);
		//DrawLine(ImVec2(BonePosition(pEntity, 11).ScreenPosition(m).x, BonePosition(pEntity, 11).ScreenPosition(m).y), ImVec2(BonePosition(pEntity, 13).ScreenPosition(m).x, BonePosition(pEntity, 13).ScreenPosition(m).y), ImColor(r, g, b), 1.f);
		//DrawLine(ImVec2(BonePosition(pEntity, 13).ScreenPosition(m).x, BonePosition(pEntity, 13).ScreenPosition(m).y), ImVec2(BonePosition(pEntity, 15).ScreenPosition(m).x, BonePosition(pEntity, 15).ScreenPosition(m).y), ImColor(r, g, b), 1.f);
		//DrawLine(ImVec2(BonePosition(pEntity, 5).ScreenPosition(m).x, BonePosition(pEntity, 5).ScreenPosition(m).y), ImVec2(BonePosition(pEntity, 35).ScreenPosition(m).x, BonePosition(pEntity, 35).ScreenPosition(m).y), ImColor(r, g, b), 1.f);
		//DrawLine(ImVec2(BonePosition(pEntity, 35).ScreenPosition(m).x, BonePosition(pEntity, 35).ScreenPosition(m).y), ImVec2(BonePosition(pEntity, 37).ScreenPosition(m).x, BonePosition(pEntity, 37).ScreenPosition(m).y), ImColor(r, g, b), 1.f);
		//DrawLine(ImVec2(BonePosition(pEntity, 37).ScreenPosition(m).x, BonePosition(pEntity, 37).ScreenPosition(m).y), ImVec2(BonePosition(pEntity, 39).ScreenPosition(m).x, BonePosition(pEntity, 39).ScreenPosition(m).y), ImColor(r, g, b), 1.f);
		//DrawLine(ImVec2(BonePosition(pEntity, 5).ScreenPosition(m).x, BonePosition(pEntity, 5).ScreenPosition(m).y), ImVec2(BonePosition(pEntity, 3).ScreenPosition(m).x, BonePosition(pEntity, 3).ScreenPosition(m).y), ImColor(r, g, b), 1.f);
		//DrawLine(ImVec2(BonePosition(pEntity, 3).ScreenPosition(m).x, BonePosition(pEntity, 3).ScreenPosition(m).y), ImVec2(BonePosition(pEntity, 2).ScreenPosition(m).x, BonePosition(pEntity, 2).ScreenPosition(m).y), ImColor(r, g, b), 1.f);
		//DrawLine(ImVec2(BonePosition(pEntity, 2).ScreenPosition(m).x, BonePosition(pEntity, 2).ScreenPosition(m).y), ImVec2(BonePosition(pEntity, 62).ScreenPosition(m).x, BonePosition(pEntity, 62).ScreenPosition(m).y), ImColor(r, g, b), 1.f);
		//DrawLine(ImVec2(BonePosition(pEntity, 62).ScreenPosition(m).x, BonePosition(pEntity, 62).ScreenPosition(m).y), ImVec2(BonePosition(pEntity, 63).ScreenPosition(m).x, BonePosition(pEntity, 63).ScreenPosition(m).y), ImColor(r, g, b), 1.f);
		//DrawLine(ImVec2(BonePosition(pEntity, 63).ScreenPosition(m).x, BonePosition(pEntity, 63).ScreenPosition(m).y), ImVec2(BonePosition(pEntity, 65).ScreenPosition(m).x, BonePosition(pEntity, 65).ScreenPosition(m).y), ImColor(r, g, b), 1.f);
		//DrawLine(ImVec2(BonePosition(pEntity, 65).ScreenPosition(m).x, BonePosition(pEntity, 65).ScreenPosition(m).y), ImVec2(BonePosition(pEntity, 57).ScreenPosition(m).x, BonePosition(pEntity, 57).ScreenPosition(m).y), ImColor(r, g, b), 1.f);
		//DrawLine(ImVec2(BonePosition(pEntity, 57).ScreenPosition(m).x, BonePosition(pEntity, 57).ScreenPosition(m).y), ImVec2(BonePosition(pEntity, 58).ScreenPosition(m).x, BonePosition(pEntity, 58).ScreenPosition(m).y), ImColor(r, g, b), 1.f);
		//DrawLine(ImVec2(BonePosition(pEntity, 58).ScreenPosition(m).x, BonePosition(pEntity, 58).ScreenPosition(m).y), ImVec2(BonePosition(pEntity, 60).ScreenPosition(m).x, BonePosition(pEntity, 60).ScreenPosition(m).y), ImColor(r, g, b), 1.f);
	}
}



void render()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//ImVec2 curPos = ImGui::GetCursorPos();
	//ImVec2 curWindowPos = ImGui::GetWindowPos();
	//curPos.x += curWindowPos.x;
	//curPos.y += curWindowPos.y;
	//static float flRainbow;
	//float flSpeed = 0.0025f;
	//flRainbow += flSpeed;
	//if (flRainbow > 1.f) flRainbow = 0.f;
	//for (int i = 0; i < 485; i++)
	//{
	//	float hue = (1.f / (float)485) * i;
	//	hue -= flRainbow;
	//	if (hue < 0.f) hue += 1.f;

	//	cRainbow = ImColor::HSV(hue, 1.f, 1.f);
	//	//ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(curPos.x + i, 10), ImVec2(curPos.x + 485, curPos.y - 3), cRainbow);
	//}

	if (aimbot)
	{
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), fov, IM_COL32_WHITE, 10000, 1);
	}

	glocalplayer = driver.read<uintptr_t>(g_base + LOCALPLAYER);

	uint64_t viewRenderer = driver.read<uint64_t>(g_base + ViewRender);
	uint64_t viewMatrix = driver.read<uint64_t>(viewRenderer + ViewMatrix);
	Matrix m = driver.read<Matrix>(viewMatrix);

	AimContext aimCtx; aimCtx.closestX = 50000; aimCtx.closestY = 50000; aimCtx.FOV = fov; aimCtx.aSmoothAmount = smooth;
	for (int i = 0; i < 100; i++)
	{
		DWORD64 Entity = GetEntityById(i, g_base);

		DWORD64 EntityHandle = driver.read<DWORD64>(Entity + m_iName);

		DWORD64 EntityShield = driver.read<DWORD64>(Entity + m_shieldHealth);
	
		std::string Identifier = driver.read<std::string>(EntityHandle);
		LPCSTR IdentifierC = Identifier.c_str();
		if (strcmp(IdentifierC, "player"))	
		{
			ImGui::PushFont(main_font);
			ESP(Entity, m, EntityShield, &aimCtx);
			ImGui::PopFont();
			if (aimbot)
			{
				if (IsVisible(Entity, i))
				{
					Aimbot(Entity, glocalplayer, m, &aimCtx, i);
				}
			}
		}
	}
	if (aimbot)
	{
		AimbotMove(&aimCtx);
	}

	/*for (int i = 0; i < 10000; i++)
	{

		DWORD64 Entity = GetEntityById(i, g_base);

		DWORD64 SignifierName = driver.read<DWORD64>(Entity + 0x589);
		std::string Identifier = driver.read<std::string>(SignifierName);
		LPCSTR IdentifierC = Identifier.c_str();
		if (strcmp(IdentifierC, "prop_survival") && get_item_id(Entity) >= 1 && get_item_id(Entity) <= 241) {
			if (itemglow)
			{	
				driver.write<int>(Entity + GLOW_ENABLE, 1);
				driver.write<int>(Entity + GLOW_THROUGH_WALLS, 2);	
				driver.write<GlowMode>(Entity + GLOW_TYPE, { 0, 118, 100, 100 });
				float r;
				float g;
				float b;
				for (auto const& [key, val] : items::item_list) {
					if (get_item_id(Entity) == key) {
						switch (val.m_rarity) {
						case items::COMMON:
							r = 255.0f; g = 255.0f; b = 255.0f;
							break;
						case items::RARE:
							r = 0.0f; g = 0.0f; b = 255.0f;
							break;
						case items::EPIC:
							r = 120.0f; g = 0.0f; b = 128.0f;
							break;
						case items::LEGENDARY:
							r = 255.0f; g = 255.0f; b = 0.0f;
							break;
						case items::HEIRLOOM:
							r = 255.0f; g = 0.0f; b = 0.0f;
							break;	
						}
					}
				}
				driver.write<float>(Entity + GLOW_R, r);
				driver.write<float>(Entity + GLOW_G, g);
				driver.write<float>(Entity + GLOW_B, b);

			}
			else
			{
				driver.write<int>(Entity + GLOW_ENABLE, 2);
			}
		}
	}*/


	if (GetAsyncKeyState(VK_INSERT) & 1) { showmenu = !showmenu; }
	
	if (showmenu) { draw_menu(); }
	ImGui::EndFrame();
	p_Device->SetRenderState(D3DRS_ZENABLE, false);
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	p_Device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	p_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (p_Device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		p_Device->EndScene();
	}

	HRESULT result = p_Device->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && p_Device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		p_Device->Reset(&d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}

using namespace KeyAuth;

std::string namee = "Apex Cheat"; // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = "jHHXUBClti"; // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = "82f5cba9edc99ede835076812b48caec93efe96f5847929dbde0081ee30dfb36"; // app secret, the blurred text on licenses tab and other tabs
std::string version = "1.0"; // leave alone unless you've changed version on website
std::string url = "https://auth.aliencheats.com/api/1.1/"; // change if you're self-hosting
std::string sslPin = "ssl pin key (optional)"; // don't change unless you intend to pin public certificate key. you can get here in the "Pin SHA256" field https://www.ssllabs.com/ssltest/analyze.html?d=keyauth.win&latest. If you do this you need to be aware of when SSL key expires so you can update it
api KeyAuthApp(namee, ownerid, secret, version, url, sslPin);


int main()
{	
	SetConsoleTitleA(skCrypt("APEX LEGENDS V1"));
	int horizontal = 0, vertical = 0;
	int x = 350, y = 250; //// alta doðru
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	SetConsoleCursorInfo(out, &cursorInfo);
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 15;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	system("color 4");
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	HWND hwnd = GetConsoleWindow();
	MoveWindow(hwnd, 0, 0, x, y, TRUE);
	LONG lStyle = GetWindowLong(hwnd, GWL_STYLE);
	lStyle &= ~(WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU);
	SetWindowLong(hwnd, GWL_STYLE, lStyle);
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(console, &csbi);
	COORD scrollbar = {
		csbi.srWindow.Right - csbi.srWindow.Left + 1,
		csbi.srWindow.Bottom - csbi.srWindow.Top + 1
	};
	if (console == 0)
		throw 0;
	else
		SetConsoleScreenBufferSize(console, scrollbar);
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd, 0, 225, LWA_ALPHA);
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);

	SetConsoleTitle("APEX LEGENDS V1");
	mainprotect();

	std::string DosyaKonumu = (_xor_("C:\\Windows\\System\\ApexLegendsLicense.txt"));

	KeyAuthApp.init();
EnBasaDon:
	std::string License;
	FILE* Dosya;
	if (Dosya = fopen((DosyaKonumu.c_str()), skCrypt("r"))) {
		std::ifstream DosyaOku(DosyaKonumu.c_str());
		std::string Anahtar;
		std::getline(DosyaOku, Anahtar);
		DosyaOku.close();
		fclose(Dosya);
		License = Anahtar;
		goto LisansaGit;
	}
	else
	{
		SetConsoleTitleA(skCrypt("  "));

		system(skCrypt("cls"));
		std::cout << skCrypt("\n\n  [+] Connecting..");
		std::cout << skCrypt("\n\n  [+] Enter License: ");
		std::cin >> License;
	LisansaGit:
		std::ofstream key; key.open(DosyaKonumu.c_str());
		key << License;
		key.close();
		KeyAuthApp.license(License);
		if (!KeyAuthApp.data.success)
		{
			std::cout << _xor_("\n Status: ").c_str() + KeyAuthApp.data.message;
			Sleep(1500);
			remove(DosyaKonumu.c_str());
			goto EnBasaDon;
			//exit(0);
		}
		system(skCrypt("cls"));
		Sleep(300);
		std::cout << skCrypt("\n\n  [+] License Activated.") << std::endl;;
	}

r8:
	if (!driver.init())
	{
	r7:
		if (FindWindow(skCrypt("Apex Legends"), NULL))
		{
			printf(skCrypt("[>] close game please...\n"));
			Sleep(1000);
			goto r7;
		}
		if (LoadDriver())
		{
			printf(skCrypt("[>] driver loaded!\n"));
			Sleep(1000);
			system("cls");
			goto r8;
		}
	}
	HWND Entryhwnd = NULL;
	while (Entryhwnd == NULL)
	{
		printf(skCrypt("[>] waiting for game\n"));
		Sleep(1);
		g_pid = get_pid();
		Entryhwnd = get_process_wnd(g_pid);
		Sleep(1);
	}
	printf(skCrypt("[>] pid: %d\n"), g_pid);
	driver.attach(g_pid);
	setup_window();
	init_wndparams(MyWnd);
	g_base = driver.get_process_base(g_pid);
	if (!g_base) { printf(skCrypt("[>] g_base can't found!\n")); return 0; }
	printf("[>] g_base: 0x%p\n", g_base);
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));
	Style();
	std::thread(NoRecoil).detach();
	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, MyWnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();


		if (hwnd_active == GameWnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(MyWnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(GameWnd, &rc);
		ClientToScreen(GameWnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = GameWnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;
		if (GetAsyncKeyState(0x1)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom) {

			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			p_Params.BackBufferWidth = Width;
			p_Params.BackBufferHeight = Height;
			SetWindowPos(MyWnd, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			p_Device->Reset(&p_Params);
		}
		render();
		Sleep(10);
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	cleanup_d3d();
	DestroyWindow(MyWnd);
	return Message.wParam;
}