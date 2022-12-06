#ifndef VECTOR_3_H
#define VECTOR_3_H
#include <d3d9.h>
#include <math.h>

#pragma once
//GAME
#define LOCALPLAYER 0x1e4f288
#define cl_entitylist 0x1a9e778
#define ClientState 0x13c3c80
#define ViewRender 0x75cc210
#define ViewMatrix 0x11a210
#define m_iName 0x589
#define NameList 0xbacf590
#define m_iHealth 0x43C
#define m_shieldHealth 0x0170
#define m_bleedoutState 0x26d0 // m_bleedoutState=0x26d0
#define m_shieldHealthMax 0x0174 
#define m_iTeamNum 0x44C
#define lastVisibleTime 0x1a48
#define m_ammoInClip 0x253c // m_ammoPoolCapacity
#define m_vecAbsOrigin 0x014c // //m_vecAbsOrigin
#define BONES 0xED0 // m_bConstrainBetweenEndpoints
#define VIEWANGLES m_ammoInClip - 0x14
#define AIMPUNCH 0x2440 // m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
#define OFFSET_CURRENT_WEAPON 0x19ec //m_latestPrimaryWeapons
#define M_LASTESTPRIMARYWINDOWS 0x19ec // m_latestPrimaryWeapons
#define NSKIN 0x0e48
#define LIFESTATE 0x798
#define BLEEDOUTSTATE 0x26d0 // m_bleedoutState
#define BULLET_SPEED 0x1eb0 // m_flProjectileSpeed
#define BULLET_SCALE 0x1eb8	// m_flProjectileScale
#define CAMERAPOS 0x1ee0 // camera_origin
//GLOW
#define GLOW_ENABLE 0x3C8
#define GLOW_THROUGH_WALLS 0x3D0
#define GLOW_TYPE 0x2C4
#define GLOW_R 0x1D0
#define GLOW_G 0x1D4
#define GLOW_B 0x1D8
#define ITEM_ID 0x1628

#define UCONST_Pi 3.1415926535
#define RadianToURotation 180.0f / UCONST_Pi
struct Matrix {
	float matrix[16];
};

class Vector3 {
public:
	Vector3() : x(0.f), y(0.f), z(0.f) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	~Vector3() {}

	float x;
	float y;
	float z;

	inline float Dot(Vector3 v) {
		return x * v.x + y * v.y + z * v.z;
	}

	inline float Distance(Vector3 v) {
		return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
	}

	Vector3 operator+(Vector3 v) {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(Vector3 v) {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	inline float Length() {
		return sqrtf((x * x) + (y * y) + (z * z));
	}
	Vector3 operator*(float Scale) {

		return Vector3(x * Scale, y * Scale, z * Scale);
	}

	float Length2D()
	{
		return sqrt((x * x) + (y * y));
	}
	float DistTo(Vector3 ape)
	{
		return (*this - ape).Length();
	}
	void Normalize()
	{
		while (x > 89.0f)
			x -= 180.f;

		while (x < -89.0f)
			x += 180.f;

		while (y > 180.f)
			y -= 360.f;

		while (y < -180.f)
			y += 360.f;
	}
	float Dist2D(Vector3 ape)
	{
		return (*this - ape).Length2D();
	}

	struct Vector3 ScreenPosition(struct Matrix matrix) {
		struct Vector3 out;
		float _x = matrix.matrix[0] * x + matrix.matrix[1] * y + matrix.matrix[2] * z + matrix.matrix[3];
		float _y = matrix.matrix[4] * x + matrix.matrix[5] * y + matrix.matrix[6] * z + matrix.matrix[7];
		out.z = matrix.matrix[12] * x + matrix.matrix[13] * y + matrix.matrix[14] * z + matrix.matrix[15];

		_x *= 1.f / out.z;
		_y *= 1.f / out.z;

		int width = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);

		out.x = width * .5f;
		out.y = height * .5f;

		out.x += 0.5f * _x * width + 0.5f;
		out.y -= 0.5f * _y * height + 0.5f;

		return out;

	}

	float distancee(Vector3 vec)
	{
		return sqrt(
			pow(vec.x - x, 2) +
			pow(vec.y - y, 2)
		);
	}

};


struct Vector2 {
public:
	float x;
	float y;

	inline Vector2() : x(0), y(0) {}
	inline Vector2(float x, float y) : x(x), y(y) {}

	inline float Distance(Vector2 v) {
		return sqrtf(((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y)));
	}

	inline Vector2 operator+(const Vector2& v) const {
		return Vector2(x + v.x, y + v.y);
	}

	inline Vector2 operator-(const Vector2& v) const {
		return Vector2(x - v.x, y - v.y);
	}
	void Normalize()
	{
		if (x > 89.0f)
			x -= 180.f;

		if (x < -89.0f)
			x += 180.f;

		if (y > 180.f)
			y -= 360.f;

		if (y < -180.f)
			y += 360.f;
	}
};
float Calc2D_Distt(const Vector2& Src, const Vector3& Dst) {
	return sqrt(powf(Src.x - Dst.x, 2) + powf(Src.y - Dst.y, 2));
}

struct AimContext {
	int FOV;
	int FOV2 = 25;
	int aSmoothAmount;

	int crosshairX = GetSystemMetrics(SM_CXSCREEN) / 2;
	int crosshairY = GetSystemMetrics(SM_CYSCREEN) / 2;

	int entX = 0;
	int entY = 0;

	int closestX = 0;
	int closestY = 0;

	int aX = 0;
	int aY = 0;

	float entNewVisTime = 0;
	float entOldVisTime[100];
	int visCooldownTime[100];
};
struct Bone {
	BYTE thing[0xCC];
	float x;
	BYTE thing2[0xC];
	float y;
	BYTE thing3[0xC];
	float z;
};
uintptr_t glocalplayer;

DWORD64 GetEntityById(int Ent, DWORD64 Base)
{
	DWORD64 EntityList = Base + cl_entitylist;
	DWORD64 BaseEntity = driver.read<DWORD64>(EntityList);
	if (!BaseEntity)
		return NULL;
	return driver.read<DWORD64>(EntityList + (Ent << 5));
}
bool IsTeam(uintptr_t localplayer, DWORD64 entity)
{
	int a = driver.read<int>(localplayer + m_iTeamNum);
	int b = driver.read<int>(entity + m_iTeamNum);
	if (a == b)
		return true;

	return false;
}
Vector3 Position(uintptr_t entity) {
	return driver.read<Vector3>(entity + m_vecAbsOrigin);
}
float distanceToLocal(DWORD64 pEntity) {
	return Position(pEntity).distancee(Position(glocalplayer));
}
Vector3 BonePosition(uintptr_t Entity, int boneIndex)
{
	Bone bone = {};
	Vector3 vec_bone = Vector3();
	Vector3 pos = Position(Entity);
		
	ULONG64 bone_array = driver.read<ULONG64>(Entity + BONES);
	ULONG64 bone_location = (boneIndex * 0x30);

	bone = driver.read<Bone>(bone_array + bone_location);
	vec_bone.x = bone.x + pos.x;
	vec_bone.y = bone.y + pos.y;
	vec_bone.z = bone.z + pos.z;
	return vec_bone;
}

void PredictPosition(uintptr_t local, Vector3* bonePos, uintptr_t entitylist, DWORD64 entity)
{
	uintptr_t actWeaponID = driver.read<uintptr_t>(local + M_LASTESTPRIMARYWINDOWS) & 0xFFFF;
	uintptr_t currentWeapon = driver.read<uintptr_t>(entitylist + (actWeaponID << 5));

	if (currentWeapon != 0)
	{
		float bulletSpeed = driver.read<float>(currentWeapon + BULLET_SPEED);
		float bulletGravity = driver.read<float>(currentWeapon + BULLET_SCALE);

		if (bulletSpeed > 1.f)
		{
			Vector3 muzzle = driver.read<Vector3>(local + CAMERAPOS);
			float time = bonePos->DistTo(muzzle) / bulletSpeed;
			bonePos->z += (700.f * bulletGravity * 0.5f) * (time * time);
			Vector3 velDelta = (driver.read<Vector3>(entity + m_vecAbsOrigin - 0xC) * time);
			bonePos->x += velDelta.x;
			bonePos->y += velDelta.y;
			bonePos->z += velDelta.z;
		}
	}
}


DWORD64 GetWeapon(DWORD64 entity)
{
	DWORD64 WeaponHandle = driver.read<DWORD64>(entity + M_LASTESTPRIMARYWINDOWS);
	WeaponHandle &= 0xffff;
	return driver.read<DWORD64>(g_base + cl_entitylist + (WeaponHandle << 5));
}
float LastVisTime(uintptr_t entity)
{
	return driver.read<float>(entity + lastVisibleTime);
}
float oVisTime[100];
bool IsVisible(uintptr_t entity, int i) {
	const auto VisCheck = LastVisTime(entity);
	const auto IsVis = VisCheck > oVisTime[i] || VisCheck < 0.f && oVisTime[i] > 0.f;
	oVisTime[i] = VisCheck;
	return IsVis;
}
bool IsAlive(uintptr_t player) {
	return driver.read<int>(player + LIFESTATE) == 0 && driver.read<int>(player + BLEEDOUTSTATE) == 0;
}
inline bool IsDummy(uintptr_t ent)
{
	uint64_t team = driver.read<uint64_t>(ent + m_iTeamNum);
	return (team == 97);
}
int isKnocked(uintptr_t entity) {
	return driver.read<int>(entity + BLEEDOUTSTATE);
}
int iTeam(uintptr_t entity) {
	return driver.read<int>(entity + m_iTeamNum);
}

namespace items {
	enum rarity { HEIRLOOM, LEGENDARY, EPIC, RARE, COMMON };

	struct c_prop {
		std::string item_name;
		rarity m_rarity;
	};

	std::map<uint32_t, c_prop> item_list = {
		{ 1, { ("Kraber"), rarity::HEIRLOOM }},
		{ 2, { ("Mastiff"), rarity::COMMON }},
		{ 6, { ("Mastiff Gold"), rarity::LEGENDARY }},
		{ 7, { ("LStar"), rarity::COMMON }},
		{ 11, { ("LStar Gold"), rarity::LEGENDARY }},
		{ 12, { ("Havoc"), rarity::COMMON }},
		{ 16, { ("Havoc Gold"), rarity::LEGENDARY }},
		{ 17, { ("Devotion"), rarity::COMMON }},
		{ 21, { ("Devotion Gold"), rarity::LEGENDARY }},
		{ 22, { ("Triple Take"), rarity::HEIRLOOM }},
		{ 23, { ("Flatline"), rarity::COMMON }},
		{ 27, { ("Flatline Gold"), rarity::LEGENDARY }},
		{ 28, { ("Hemlock"), rarity::COMMON }},
		{ 32, { ("Hemlock Gold"), rarity::LEGENDARY }},
		{ 33, { ("G7 Scout"), rarity::COMMON }},
		{ 37, { ("G7 Scout Gold"), rarity::LEGENDARY }},
		{ 38, { ("Alternator"), rarity::HEIRLOOM }},
		{ 39, { ("R99"), rarity::COMMON }},
		{ 43, { ("R99 Gold"), rarity::LEGENDARY }},
		{ 44, { ("Prowler"), rarity::COMMON }},
		{ 48, { ("Prowler Gold"), rarity::LEGENDARY }},
		{ 49, { ("Volt"), rarity::COMMON }},
		{ 53, { ("Volt Gold"), rarity::LEGENDARY }},
		{ 54, { ("Longbow"), rarity::COMMON }},
		{ 58, { ("Longbow Gold"), rarity::LEGENDARY }},
		{ 59, { ("Charge Rifle"), rarity::COMMON }},
		{ 63, { ("Charge Rifle Gold"), rarity::LEGENDARY }},
		{ 64, { ("Spitfire"), rarity::HEIRLOOM }},
		{ 65, { ("R301"), rarity::COMMON }},
		{ 69, { ("R301 Gold"), rarity::LEGENDARY }},
		{ 70, { ("Eva-8 Auto"), rarity::COMMON }},
		{ 74, { ("Eva-8 Auto Gold"), rarity::LEGENDARY }},
		{ 75, { ("Peacekeeper"), rarity::COMMON }},
		{ 79, { ("Peacekeeper Gold"), rarity::LEGENDARY }},
		{ 80, { ("Mozambique"), rarity::COMMON }},
		{ 84, { ("Mozambique Gold"), rarity::LEGENDARY }},
		{ 85, { ("Wingman"), rarity::COMMON }},
		{ 89, { ("Wingman Gold"), rarity::LEGENDARY }},
		{ 90, { ("P2020"), rarity::COMMON }},
		{ 94, { ("P2020 Gold"), rarity::LEGENDARY }},
		{ 95, { ("RE45"), rarity::COMMON }},
		{ 99,  {("RE45 Gold"), rarity::LEGENDARY }},
		{ 100, { ("Sentinel"), rarity::COMMON }},
		{ 104, { ("Sentinel Gold"), rarity::LEGENDARY }},
		{ 105, { ("Bocek Bow"), rarity::COMMON }},
		{ 109, { ("Bocek Bow Gold"), rarity::LEGENDARY }},
		{ 110, { ("30 30 Repeater"), rarity::COMMON }},
		{ 114, { ("30 30 Repeater Gold"), rarity::LEGENDARY }},

		{ 115, { ("Light Ammo"), rarity::COMMON }},
		{ 116, { ("Energy Ammo"), rarity::COMMON }},
		{ 117, { ("Shotgun Ammo"), rarity::COMMON }},
		{ 118, { ("Heavy Ammo"), rarity::COMMON }},
		{ 119, { ("Sniper Ammo"), rarity::COMMON }},
		{ 120, { ("Arrow"), rarity::COMMON }},

		{ 121, { ("Rampage"), rarity::COMMON }},
		{ 125, { ("Rampage Gold"), rarity::LEGENDARY }},

		{ 151, { ("Ultimate Accelerant"), rarity::RARE }},
		{ 152, { ("Pheonix Kit"), rarity::EPIC }},
		{ 153, { ("Med Kit"), rarity::RARE }},
		{ 154, { ("Syringe"), rarity::COMMON }},
		{ 155, { ("Shield Battery"), rarity::RARE }},
		{ 156, { ("Shield Cell"), rarity::COMMON }},

		{ 157, { ("Helmet"), rarity::COMMON }},
		{ 158, { ("Helmet"), rarity::RARE }},
		{ 159, { ("Helmet"), rarity::EPIC }},
		{ 160, { ("Helmet"), rarity::LEGENDARY }},

		{ 161, { ("Body Armor"), rarity::COMMON }},
		{ 162, { ("Body Armor"), rarity::RARE }},
		{ 163, { ("Body Armor"), rarity::EPIC }},
		{ 164, { ("Body Armor"), rarity::LEGENDARY }},
		{ 165, { ("Body Armor"), rarity::HEIRLOOM }},

		{ 166, { ("Evo Body Armor"), rarity::COMMON }},
		{ 167, { ("Evo Body Armor"), rarity::RARE }},
		{ 168, { ("Evo Body Armor"), rarity::EPIC }},
		{ 169, { ("Evo Body Armor"), rarity::HEIRLOOM }},

		{ 170, { ("Heat Shield"), rarity::HEIRLOOM }},

		{ 171, { ("Knockdown Shield"), rarity::COMMON }},
		{ 172, { ("Knockdown Shield"), rarity::RARE }},
		{ 173, { ("Knockdown Shield"), rarity::EPIC }},
		{ 174, { ("Knockdown Shield"), rarity::LEGENDARY }},

		{ 175, { ("Backpack"), rarity::COMMON }},
		{ 176, { ("Backpack"), rarity::RARE }},
		{ 177, { ("Backpack"), rarity::EPIC }},
		{ 178, { ("Backpack"), rarity::LEGENDARY }},

		{ 179, { ("Thermite Grenade"), rarity::COMMON }},
		{ 180, { ("Frag Grenade"), rarity::COMMON }},
		{ 181, { ("Arc Star"), rarity::COMMON }},

		{ 182, { ("1x HCOG 'Classic'"), rarity::COMMON }},
		{ 183, { ("2x HCOG 'Bruiser'"), rarity::RARE }},
		{ 184, { ("1x Holo"), rarity::COMMON }},
		{ 185, { ("1x-2x Variable Holo"), rarity::RARE }},
		{ 186, { ("1x Digital Threat"), rarity::LEGENDARY }},
		{ 187, { ("3x HCOG 'Ranger'"), rarity::EPIC }},
		{ 188, { ("2x-4x Variable AOG"), rarity::EPIC }},
		{ 189, { ("6x Sniper"), rarity::RARE }},
		{ 190, { ("4x-8x Variable Sniper"), rarity::EPIC }},
		{ 191, { ("4x-10x Digital Sniper Threat"), rarity::LEGENDARY }},

		{ 192, { ("Barrel Stabilizer"), rarity::COMMON }},
		{ 193, { ("Barrel Stabilizer"), rarity::RARE }},
		{ 194, { ("Barrel Stabilizer"), rarity::EPIC }},
		{ 195, { ("Barrel Stabilizer"), rarity::LEGENDARY }}, // Unobtainable?

		{ 196, { ("Light Magazine"), rarity::COMMON }},
		{ 197, { ("Light Magazine"), rarity::RARE }},
		{ 198, { ("Light Magazine"), rarity::EPIC }},
		{ 199, { ("Light Magazine"), rarity::LEGENDARY }},

		{ 200, { ("Heavy Magazine"), rarity::COMMON }},
		{ 201, { ("Heavy Magazine"), rarity::RARE }},
		{ 202, { ("Heavy Magazine"), rarity::EPIC }},
		{ 203, { ("Heavy Magazine"), rarity::LEGENDARY }},

		{ 204, { ("Energy Magazine"), rarity::COMMON }},
		{ 205, { ("Energy Magazine"), rarity::RARE }},
		{ 206, { ("Energy Magazine"), rarity::EPIC }},
		{ 207, { ("Energy Magazine"), rarity::LEGENDARY }},

		{ 208, { ("Sniper Magazine"), rarity::COMMON }},
		{ 209, { ("Sniper Magazine"), rarity::RARE }},
		{ 210, { ("Sniper Magazine"), rarity::EPIC }},
		{ 211, { ("Sniper Magazine"), rarity::LEGENDARY }},

		{ 212, { ("Shotgun Bolt"), rarity::COMMON }},
		{ 213, { ("Shotgun Bolt"), rarity::RARE }},
		{ 214, { ("Shotgun Bolt"), rarity::EPIC }},

		{ 215, { ("Standard Stock"), rarity::COMMON }},
		{ 216, { ("Standard Stock"), rarity::RARE }},
		{ 217, { ("Standard Stock"), rarity::EPIC }},

		{ 218, { ("Sniper Stock"), rarity::COMMON }},
		{ 219, { ("Sniper Stock"), rarity::RARE }},
		{ 220, { ("Sniper Stock"), rarity::EPIC }},

		{ 221, { ("Turbocharger"), rarity::LEGENDARY }},
		{ 222, { ("Skull Piercer"), rarity::LEGENDARY }},
		{ 223, { ("Hammer Point"), rarity::EPIC }},
		{ 224, { ("Anvil Receiver"), rarity::LEGENDARY }},
		{ 225, { ("Graffiti Mod"), rarity::COMMON }},
		{ 226, { ("Paintball 1"), rarity::HEIRLOOM }}, // TODO: Find this rarity
		{ 227, { ("Paintball 2"), rarity::HEIRLOOM }}, // TODO: Find this rarity
		{ 228, { ("Deadeye's Tempo"), rarity::EPIC }},
		{ 229, { ("Quickdraw Holster"), rarity::EPIC }}, // Might be 229
		{ 230, { ("Shatter Caps"), rarity::EPIC }},
		{ 231, { ("Boosted Loader"), rarity::LEGENDARY }},
		{ 232, { ("Mobile Respawn Beacon"), rarity::RARE }},
		{ 233, { ("Vault Key"), rarity::HEIRLOOM }},
		{ 234, { ("Steel Cut"), rarity::HEIRLOOM }}, // Might be overwritten every season/every time there's a new charm.
		{ 235, { ("Treasure Pack"), rarity::HEIRLOOM }},
		{ 236, { ("Survival Doubler"), rarity::HEIRLOOM }}, // TODO: Find this rarity
		{ 237, { ("Survival Quadrupler"), rarity::HEIRLOOM }}, // TODO: Find this rarity
		{ 238, { ("Heat Shield"), rarity::RARE }},
		{ 239, { ("Mobile Respawn Beacon 2"), rarity::RARE }},
		{ 240, { ("MRVN Arm"), rarity::EPIC }},
		{ 241, { ("Vault Key"), rarity::HEIRLOOM }}
	};
}
int skin_id;
int selected_hit;
const char* hitbox[] = { "Head", "Neck", "Body" };
int realkey;
int keystatus;
int aimkey = VK_XBUTTON2;

void Aimbot(uintptr_t pEntity, uintptr_t pLocal, Matrix m, AimContext* Ctx, int index) {
	int hit;
	if (selected_hit == 0)
		hit == 8;
	else if (selected_hit == 1)
		hit == 7;
	else if (selected_hit == 2)
		hit == 5;
	Vector3 entAimPos = BonePosition(pEntity, 8); //0 Hips //5 Body //7 Neck //8 Head
	uintptr_t entitylist = driver.read<uintptr_t>(g_base + cl_entitylist);
	PredictPosition(pLocal, &entAimPos, entitylist, pEntity);

	Vector3 w2sEntAimPos = entAimPos.ScreenPosition(m); if (w2sEntAimPos.z <= 0.f) return;

	int entX = w2sEntAimPos.x;
	int entY = w2sEntAimPos.y;

	Ctx->entNewVisTime = driver.read<float>(pEntity + lastVisibleTime);
	int entKnockedState = isKnocked(pEntity);
	int playerTeamID = iTeam(pLocal);
	int entTeamID = iTeam(pEntity);

	if (entTeamID != playerTeamID) {

		if (Ctx->entNewVisTime != Ctx->entOldVisTime[index])
		{
			Ctx->visCooldownTime[index] = 24;

			if (entKnockedState == 0)
			{

				if (abs(Ctx->crosshairX - entX) < abs(Ctx->crosshairX - Ctx->closestX) && abs(Ctx->crosshairX - entX) < Ctx->FOV && abs(Ctx->crosshairY - entY) < abs(Ctx->crosshairY - Ctx->closestY) && abs(Ctx->crosshairY - entY) < Ctx->FOV)
				{
					Ctx->closestX = entX;
					Ctx->closestY = entY;
				}
			}
			Ctx->entOldVisTime[index] = Ctx->entNewVisTime;
		}
		if (Ctx->visCooldownTime[index] >= 0) Ctx->visCooldownTime[index] -= 1;
	}
}
void AimbotMove(AimContext* Ctx) {

	if (Ctx->closestX != 50000 && Ctx->closestY != 50000)
	{
		if (GetAsyncKeyState(aimkey))
		{
			Ctx->aX = (Ctx->closestX - Ctx->crosshairX) / Ctx->aSmoothAmount;
			Ctx->aY = (Ctx->closestY - Ctx->crosshairY) / Ctx->aSmoothAmount;

			CURSORINFO ci = { sizeof(CURSORINFO) };
			if (GetCursorInfo(&ci))
			{
				if (ci.flags == 0)
					mouse_event(MOUSEEVENTF_MOVE, Ctx->aX, Ctx->aY, 0, 0);
			}
		}
	}
}

#endif