#pragma once

#define VALID( x ) ( x != NULL && HIWORD( x ) )

#define dwRenderAddress                        0x1256A7C - 0x400000                    // r3dRender.h

#define PHYSICS_Adr                     0x1252958 - 0x400000       // ASSERT at file %s, line %d: g_pPhysicsWorld  \nTime between load endand game start :


#define matTmp_off			                   0x220		                           // PS_DS_SSR_VS
#define matView_off			                   0x1A0		                           // PS_DS_SSR_VS

#define pGame_Adr                            0x12BB24C	 - 0x400000      //  clientgame - g_pClientLo Grenade_Generic_PinPull 0x128BB98
#define pGame_Xor                                       0x003A0A000//  0x1735146A  0x7329531B
#define pGameWorld_Adr                       0x12BB624  - 0x400000      //  gameworld Available memory: %d MB  8B C6 5E 83 C4 08 C3
#define pGameWorld_Xor                                  0x001B0A00//  0xFC5AD98D		

#define GetLocalPlayer_off                     0x0D0130                  // pl_%u localplayer
#define GetLocalPlayer_xor                     0x5817810B               // pl_%u

#define XOR_OBJLIST_MAX	                       0x13E1855C                         // !bInited   2C
#define XOR_OBJLIST_PTR                        0x304CFD16								 // !bInited  44

#define m_pSkeleton_off			               0x1230                          // PrimaryWeaponBone
#define BoneCoeff_off			               0x147C	                           // PrimaryWeaponBone
#define CSkeleton_off			               0x28                                    // Bip01_Head

#define FastPickupIteam_off				       0x1290                  // obj_Gravestone
#define PlayerGetYaw  				           0x1404								   // player%02d
#define SuperJump_off                          0x136B                // PLAYER_JUMPING_F 

#define Dx3sec                                 0x3EC       //_root.api.setThreat เลื่อนลง FSUB 



#define Get5555_Offset                  0x13F0                     //  storecat_MEl        ลดดีด  D9 9F C4 13 00 00

#define NoSpread                        0x3A0                      //  _root.api.showSlots บน    addss   ลดกระจาย                 F3 0F 11 ?? ?? ?? 00 00


#define NameLenAddress                         0x420						           // ReceivedTradeRequestFromPlr
#define NameAddress							   0x3E0                         // ReceivedTradeRequestFromPlr

#define clanset                         0x444                   //  team clan _root.api.setCarInfoVisibility 
#define teamset                         0x3FC                  //  team clan _root.api.setCarInfoVisibility 

#define GetHealth_off			               0x4E4                          // Health
#define Objecttype_off                         0x210                               // Weapon owner must be obj_Player            isObjType(OBJTYPE_H   
#define Getposition_off                        0x24                           // F3 0F 7E 07 66 0F D6 86 ?? ?? ?? ?? 8B 47 08


DWORD DM_Offset = 0x1a;                                 // ยิงแรง 
DWORD DM_Offset1 = 0x1e;                                // ล่าง
#define DM_Offset11  26                                 // ยิงตัวโดนหัว
#define DM_Offset22  30                                 // ล่าง
DWORD GhostMode_Offset = 0x74;                          // หายตัว
DWORD GhostMode_Offset1 = 0x75;                         // ล่าง