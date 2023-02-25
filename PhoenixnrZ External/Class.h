#pragma once
#pragma once
class ClientGameLogic;
class AObject;
class ObjectManager;
class GameObject;
class obj_Player;

typedef ClientGameLogic* (__stdcall* tGetGame)(void);
tGetGame GetGame = (tGetGame)NULL;

typedef ObjectManager* (__stdcall* tGetGameWorld)(void);
tGetGameWorld GetGameWorld = (tGetGameWorld)NULL;

typedef r3dRenderLayer* (__stdcall* tRender)(void);
tRender GetRender = (tRender)NULL;

enum E_Bones // 62
{
	Bip01 = 0,
	Bip01_Pelvis = 1,
	Bip01_Spine = 2,
	Bip01_Spine1 = 3,
	Bip01_Spine2 = 4,
	Bip01_Neck = 5,
	Bip01_Head = 6,
	Bip01_L_Clavicle = 7,
	Bip01_L_UpperArm = 8,
	Bip01_L_Forearm = 9,
	Bip01_L_Hand = 10,
	Bip01_L_Finger0 = 11,
	Bip01_L_Finger01 = 12,
	Bip01_L_Finger02 = 13,
	Bip01_L_Finger1 = 14,
	Bip01_L_Finger11 = 15,
	Bip01_L_Finger12 = 16,
	Bip01_L_Finger2 = 17,
	Bip01_L_Finger21 = 18,
	Bip01_L_Finger22 = 19,
	Bip01_L_Finger3 = 20,
	Bip01_L_Finger31 = 21,
	Bip01_L_Finger32 = 22,
	Bip01_L_Finger4 = 23,
	Bip01_L_Finger41 = 24,
	Bip01_L_Finger42 = 25,
	Bip01_L_ForeTwist = 26,
	Bip01_L_ForeTwist1 = 27,
	Bip01_R_Clavicle = 28,
	Bip01_R_UpperArm = 29,
	Bip01_R_Forearm = 30,
	Bip01_R_Hand = 31,
	Bip01_R_Finger0 = 32,
	Bip01_R_Finger01 = 33,
	Bip01_R_Finger02 = 34,
	Bip01_R_Finger1 = 35,
	Bip01_R_Finger11 = 36,
	Bip01_R_Finger12 = 37,
	Bip01_R_Finger2 = 38,
	Bip01_R_Finger21 = 39,
	Bip01_R_Finger22 = 40,
	Bip01_R_Finger3 = 41,
	Bip01_R_Finger31 = 42,
	Bip01_R_Finger32 = 43,
	Bip01_R_Finger4 = 44,
	Bip01_R_Finger41 = 45,
	Bip01_R_Finger42 = 46,
	PrimaryWeaponBone = 47,
	Bip01_R_ForeTwist = 48,
	Bip01_R_ForeTwist1 = 49,
	Weapon_BackLeft = 50,
	Weapon_BackRPG = 51,
	Weapon_BackRight = 52,
	Bip01_L_Thigh = 53,
	Bip01_L_Calf = 54,
	Bip01_L_Foot = 55,
	Bip01_L_Toe0 = 56,
	Weapon_Side = 57,
	Bip01_R_Thigh = 58,
	Bip01_R_Calf = 59,
	Bip01_R_Foot = 60,
	Bip01_R_Toe0 = 61
};

#define OBJTYPE_HUMAN 0x20
#define OBJTYPE_HUMAN1 0x21

//#define OBJTYPE_ZOMBIE 0x20000
#define OBJTYPE_ZOMBIE1 0x20001

#define OBJTYPE_DroppedItem 0x240005

#define M_POSE_REST 0
#define M_POSE_ZOOM 1
#define M_POSE_CROUCH 2
#define M_POSE_WALKING 5
#define M_POST_RUNNING 6
#define M_POSE_PRONE_TRANSITION 10
#define M_POSE_PRONE 11
#define M_POSE_DEAD 12


enum E_PacketType : BYTE
{
	//�ԧ�ç

	PKT_C2C_PlayerFired = DM_Offset11, //Firepacket 31  27 �ԧ�ç
	PKT_C2C_PlayerHitDynamic = DM_Offset22, //<< hitpacket

	PKT_C2C_PlayerHitNothing,//1F
	PKT_C2C_PlayerHitStatic, // 1F hit static geometry

};



enum Playerstate_e
{
	PLAYER_INVALID = -1,

	PLAYER_IDLE = 0,
	PLAYER_IDLEAIM,

	PLAYER_MOVE_CROUCH,
	PLAYER_MOVE_CROUCH_AIM,
	PLAYER_MOVE_WALK_AIM,
	PLAYER_MOVE_RUN,
	PLAYER_MOVE_SPRINT,
	PLAYER_MOVE_PRONE,

	PLAYER_PRONE_AIM,
	PLAYER_PRONE_UP,
	PLAYER_PRONE_DOWN,
	PLAYER_PRONE_IDLE,

	PLAYER_SWIM_IDLE,
	PLAYER_SWIM_SLOW,
	PLAYER_SWIM,
	PLAYER_SWIM_FAST,

	PLAYER_VEHICLE_DRIVER,
	PLAYER_VEHICLE_PASSENGER,

	PLAYER_DIE,

	PLAYER_NUM_STATES,
};

enum EGameObjectType
{
	OBJTYPE_Generic = (1 << 0),
	OBJTYPE_Terrain = (1 << 1),		// terrain object
	OBJTYPE_Mesh = (1 << 2),		// mesh object
	OBJTYPE_Road = (1 << 3),		// road object
	OBJTYPE_Building = (1 << 4),		// building object
	OBJTYPE_Human = 0x20,
	OBJTYPE_Particle = (1 << 6), // particle emitter
	OBJTYPE_Sound = (1 << 7), // sound emitter
	OBJTYPE_Trees = (1 << 8), // all world trees
	OBJTYPE_ApexDestructible = (1 << 11),
	OBJTYPE_AnimMesh = (1 << 12),
	OBJTYPE_DecalProxy = (1 << 13),
	OBJTYPE_Sprite = (1 << 15),
	OBJTYPE_Vehicle = (1 << 16),
	OBJTYPE_Zombie = (1 << 17),
	OBJTYPE_GameplayItem = (1 << 18),
	OBJTYPE_CollectionProxy = (1 << 19),
	OBJTYPE_ItemSpawnPoint = (1 << 20),
	OBJTYPE_SharedUsableItem = (1 << 21),
};

D3DXMATRIX matProj, matView, matWorld;

void MatrixToScreen()
{
	D3DXMATRIX matTmp = *(D3DXMATRIX*)((DWORD)pRenderer + matTmp_off);
	if (matTmp.m[3][3] != 1.f)
	{
		matProj = matTmp;
		matView = *(D3DXMATRIX*)((DWORD)pRenderer + matView_off);
	}
}

bool ProjectToScreen(const D3DXVECTOR3& pvPos, D3DXVECTOR3* pvOut, LPDIRECT3DDEVICE9 pDevice)
{
	D3DVIEWPORT9 ViewPort;
	D3DXMatrixIdentity(&matWorld);
	pDevice->GetViewport(&ViewPort);

	ViewPort.X = ViewPort.Y = 0;
	ViewPort.MinZ = 0;
	ViewPort.MaxZ = 1;

	D3DXVec3Project(pvOut, &pvPos, &ViewPort, &matProj, &matView, &matWorld);

	if (pvOut->z >= 1 || pvOut->z < 0 || pvOut->x > ViewPort.Width || pvOut->x < 0)
	{
		return false;

	}

	return true;
}

class r3dRenderLayer
{

public:
	/*D3DXMATRIX GetViewPosition()
	{
		D3DXMATRIX inverseView;
		D3DXMatrixInverse(&inverseView, NULL, &matView);
		return D3DXVECTOR3(inverseView._41, inverseView._42, inverseView._43);
	}*/
};

DWORD CallGetPlayer;
class ClientGameLogic
{
public:
	int getPing()
	{
		int nPing = *(int*)((DWORD)(this) + 0x10);
		return nPing;
	}

	obj_Player* GetLocalPlayer()
	{
		obj_Player* pLocalPlayer = (obj_Player*)(*(DWORD*)((DWORD)(this) + GetLocalPlayer_off));

		pLocalPlayer = (obj_Player*)((DWORD)pLocalPlayer ^ GetLocalPlayer_xor);

		return pLocalPlayer;
	}
};

DWORD pGetFirstObject = 0, pGetNextObject = 0;

class ObjectManager
{
public:
	char _0x0000[8];
	__int32 m_FrameId; //0x0008 
	char _0x000C[32];
	__int32 MaxObjects; //0x002C 
	char _0x0030[12];
	__int32 bInited; //0x003C 
	char _0x0040[4];
	DWORD pObjectArray; //0x0044 
	char _0x0048[1016];

	GameObject* GetFirstObject()
	{
		__asm
		{
			mov ecx, this
			call pGetFirstObject
		}
	}

	GameObject* GetNextObject(GameObject* obj)
	{
		__asm
		{
			push obj
			mov ecx, this
			call pGetNextObject
		}
	}

	DWORD getMaxObjects()
	{
		return MaxObjects ^ XOR_OBJLIST_MAX;
	}

	GameObject* getObject(int id)
	{
		if (/* m_MaxObjects && m_ObjectList*/ getMaxObjects() > id && id > 0)
		{
			GameObject** pObjectList = (GameObject**)(pObjectArray ^ XOR_OBJLIST_PTR);
			return (GameObject*)pObjectList[id];
		}
		return NULL;
	}
};

class AObject
{
	class AClass* Class;		// 0000
	unsigned char _0004[0x4];	// 0004
};

class CBone {

public:
	char* m_BoneName;       //0x00  
	char        pad_04[136];      //0x04
	D3DXMATRIX  BoneMatrix;       //0x8C  
	D3DXMATRIX  SomeMatrix;       //0xCC  
};
class CBoneInfo {

public:
	char       pad_00[20];//new 0x20 v2-v1 0x24
	DWORD      oneNum;            //0x14 
	CBone* pBones;            //0x18
};

class CSkeleton {

public:
	char       pad_00[CSkeleton_off];
	CBoneInfo* BonePtr;           //0x28 
};

class GameObject : public AObject
{
public:
	char _0x0000[36];
	D3DXVECTOR3 vPos; //0x0024 
	char _0x0030[1040];

	D3DXVECTOR3 getPosition()
	{
		D3DXVECTOR3 vPlayer = *(D3DXVECTOR3*)((DWORD)(this) + Getposition_off);
		return vPlayer;
	}

	EGameObjectType getObjType()
	{
		EGameObjectType ObjTypeFlags = *(EGameObjectType*)((DWORD)(this) + Objecttype_off);
		return ObjTypeFlags;
	}

	bool isObjType(EGameObjectType i)
	{
		return (getObjType() & i);
	}
};//Size=0x0440

DWORD WEAPON_XOR = 0x02600590;
class CWeaponArmory
{
public:
	char _0x0000[20]; //0x0000 
	char* szName; //0x0014 
	char _0x0018[72]; //0x0018 
	float m_fBulletGravity; //0x0060 
	float m_weaponVelocity; //0x0064 
	char _0x0068[28]; //0x0068 
	int m_Spread; //0x0084 
	char _0x0088[4]; //0x0088 
	int RecoilXored; //0x008C 
	char _0x0090[4]; //0x0090
	int FireRateXored; //0x0094
	char _0x0098[8];
	int ReloadTime; //0x00A0
};

class CWeapon
{
public:
	char _0x0000[36];
	DWORD Armory; //0x0024

	CWeaponArmory* GetArmory()
	{
		return (CWeaponArmory*)(Armory ^ WEAPON_XOR);
	}
	/*CWeaponArmory* GetArmory()
	{
	return (CWeaponArmory*)(Armory);
	}*/
};

extern obj_Player* localPlayer;
class obj_Player
{
public:
	virtual void vFunc0();
	virtual void vFunc1();
	virtual void vFunc2();
	virtual void vFunc3();
	virtual void vFunc4();
	virtual void vFunc5();
	virtual void vFunc6();
	virtual void vFunc7();
	virtual void vFunc8();
	virtual void vFunc9();
	virtual void vFunc10();
	virtual void vFunc11();
	virtual void vFunc12();
	virtual void SetPosition(const D3DXVECTOR3& pos);
	int m_SelectedWeapon; //0x122C
	D3DXVECTOR3 m_vPosition; //0x000C

	D3DXVECTOR3 GetPosition()
	{
		return *(D3DXVECTOR3*)((DWORD)this + Getposition_off);
	}

	float GetYAW()
	{
		return *(float*)((DWORD)this + PlayerGetYaw);
	}

	CSkeleton* m_Skeleton()
	{
		return *(CSkeleton**)((DWORD)this + m_pSkeleton_off);
	}

	D3DXMATRIX m_BoneCoeff()
	{
		return *(D3DXMATRIX*)((DWORD)this + BoneCoeff_off);
	}

	float Gethealth()
	{
		return *(float*)((DWORD)(this) + GetHealth_off);
	}
	bool isAlive()
	{
		return (this->Gethealth() > 0);
	}
	

	/////////////////////////////////////////////////////////  Team

	int TeamID(void)
	{
		return *(int*)((DWORD)(this) + teamset);
	}

	int myTeamID(void)
	{
		return *(int*)((DWORD)localPlayer + teamset);
	}

	int EnemyTeam()
	{
		return  *(int*)((DWORD)this + teamset);
	}

	bool IsPlayerTeam()
	{
		if (myTeamID() > 0 && myTeamID() == EnemyTeam())
			return true;

		return false;
	}

	/////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////  Clan

	wchar_t* CLAN(void)
	{
		return (wchar_t*)((DWORD)(this) + clanset + 0x8); // 8D 86 ? ? ? ? BA ? ? ? ? BD ? ? ? ?
	}
	int ClanColor(void)
	{
		return *(int*)((DWORD)(this) + clanset + 0x8 - 0x4);
	}

	int ClanID(void)
	{
		return *(int*)((DWORD)(this) + clanset + 0x8 - 0x8);
	}

	int myclanid(void)
	{
		return *(int*)((DWORD)localPlayer + clanset + 0x8 - 0x8);
	}

	int Encmyclanid(void)
	{
		return *(int*)((DWORD)this + clanset + 0x8 - 0x8);
	}

	bool IsPlayerClan()
	{
		if (myclanid() > 0 && myclanid() == Encmyclanid())
			return true;

		return false;
	}

	/////////////////////////////////////////////////////////

	int NameColor(void)
	{
		return *(int*)((DWORD)(this) + 0x458);
	}


};

class wiInventoryItem
{
public:
	__int32 InventoryID; //0x0000  
	__int32 pad;
	__int32 itemID; //0x0008  
	__int32 amount; //0x000C  
	__int32 ammoAmount; //0x0010  
	__int32 ammoItemID; //0x0014  
	__int32 unk1;
	__int32 unk2;
};//Size=0x0020

class CObject_Zombie
{
public:

	int m_typeIndex()
	{
		int vPlayer = *(int*)((DWORD)(this) + 0x330);
		return vPlayer;
	}

	D3DXVECTOR3 Position()
	{
		D3DXVECTOR3 vPlayer = *(D3DXVECTOR3*)((DWORD)(this) + 0x24);
		return vPlayer;
	}
};

class CObject_DroppedItem : public GameObject
{
public:
	char* name()
	{
		return *(char**)((DWORD)this + 0x384);
	}
	wchar_t* Name()
	{
		return *(wchar_t**)((DWORD)this + 0x394);
	}
	wiInventoryItem* getInventoryItem()
	{
		return (wiInventoryItem*)((DWORD)(this) + 0x3A4);
	}
	DWORD ItemId()
	{
		return *(DWORD*)((DWORD)this + 0x03B0);
	}
};


class CNetwork
{
public:
	DWORD* impl; // 0000
	int dumpStats_; // 0004
	int lastPing_; // 0008
	//DWORD		firstBindIP_;
	//const static int FIRST_FREE_PACKET_ID = 0;
	//const static int RAKNET_USER_PACKET = 134; // must be more that RakNet::ID_USER_PACKET_ENUM
};//Size=0x0018

struct serverSendData_t
{
	BYTE FirstFreeEventID;
	BYTE PacketType;		//0000
	BYTE  EventID; //0000
	WORD  NetworkID;				//0001
	unsigned char data[1024];		//0003
};

class PlayerFired_c : public serverSendData_t
{
public:
	DWORD	localId;	// local game object ID for server tracking purpuses
	//WORD	spawnID;	// network ID, for reconnecting a RelayPacket generated flare-gun flare with the network mover
	BYTE		fireSeqNo;	// used for shotgun bullets

	D3DXVECTOR3	fire_from; // position of character when he is firing
	D3DXVECTOR3	fire_to;
	float		holding_delay; // if any, used for grenades. THIS IS TEMP until grenades are moved to server(!!)
	BYTE		debug_wid;	// weapon index for debug
};

class PlayerHitNothing_s : public serverSendData_t
{
public:
	DWORD	localId;	// local game object ID for server tracking purpuses
};

class PlayerHitDynamic_s : public serverSendData_t
{
public:
	DWORD	localId;	// local game object ID for server tracking purpuses
	D3DXVECTOR3	muzzler_pos; // for anti cheat
	D3DXVECTOR3	hit_pos; // where your bullet hit
	WORD	targetId; // what you hit
	BYTE		hit_body_bone; // which bone we hit (for ragdoll)
	BYTE		state; // [0] - from player in air [1] target player in air

					   // NEEDED FOR SERVER ONLY. TEMP. WILL BE REFACTORED AND MOVED TO SERVER.
	BYTE		hit_body_part;// where we hit player (head, body, etc)
	BYTE		damageFromPiercing; // 0 - no reduction, 100 - no damage at all
};

class obj_DroppedItem : public GameObject
{
public:
	D3DXVECTOR3 Position()
	{
		D3DXVECTOR3 vPlayer = *(D3DXVECTOR3*)((DWORD)(this) + 0x24);
		return vPlayer;
	}
	int ItemId()
	{
		return *(int*)((DWORD)(this) + 0x03B0);
	}
};

typedef int(WINAPI* vSendToHost)(CNetwork* Network, serverSendData_t* pPacket, int packetSize);
extern vSendToHost pSendToHost;