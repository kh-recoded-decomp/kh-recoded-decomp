#include "nitro/types.h"

extern u8 data_ov061_020d8549[];
extern void CreateAuraBattleObject_020d8400(void);
extern void CreateBossBattleObject_020d83dc(void);
extern void CreateBurstBattleObject_020d8360(void);
extern void CreateMarkedSceneTask_020d86e8(void);
extern void CreateOv067BossObject_020d83c4(void);
extern void CreateOv068BossObject_020d851c(void);
extern void CreateOv069BossObject_020d88a4(void);
extern void CreateOv070BossObject_020d8894(void);
extern void CreateOv071SceneTask_020d954c(void);
extern void CreateOv072SceneTask_020d9aac(void);
extern void CreateSceneTask_020d859c(void);

const u32 data_ov021_020b506c[38] = {
    0x00000020, 0x00000001, 0x00000022, 0x00000001,
    0x00000024, 0x00000001, 0x00000026, 0x00000001,
    0x00000016, 0x00000003, 0x00000018, 0x00000003,
    0x0000001A, 0x00000003, 0x0000001C, 0x00000003,
    0x0000001E, 0x00000003, 0x0000000C, 0x00000001,
    0x0000000E, 0x00000001, 0x00000010, 0x00000001,
    0x00000012, 0x00000001, 0x00000014, 0x00000001,
    0x00000060, 0x00000001, 0x00000062, 0x00000001,
    0x00000064, 0x00000001, 0x00000066, 0x00000001,
    0x00000068, 0x00000001,
};

void *const data_ov021_020b500c[24] = {
    (void *)CreateBurstBattleObject_020d8360,
    (void *)0x0000003D,
    (void *)CreateBossBattleObject_020d83dc,
    (void *)0x0000003E,
    (void *)CreateSceneTask_020d859c,
    (void *)0x0000003F,
    (void *)CreateMarkedSceneTask_020d86e8,
    (void *)0x00000040,
    (void *)CreateAuraBattleObject_020d8400,
    (void *)0x00000041,
    (void *)data_ov061_020d8549,
    (void *)0x00000042,
    (void *)CreateOv067BossObject_020d83c4,
    (void *)0x00000043,
    (void *)CreateOv068BossObject_020d851c,
    (void *)0x00000044,
    (void *)CreateOv069BossObject_020d88a4,
    (void *)0x00000045,
    (void *)CreateOv070BossObject_020d8894,
    (void *)0x00000046,
    (void *)CreateOv071SceneTask_020d954c,
    (void *)0x00000047,
    (void *)CreateOv072SceneTask_020d9aac,
    (void *)0x00000048,
};

const u32 data_ov021_020b4ff4[6] = {
    0x00000003, 0x00000004, 0x00000001, 0x00000000,
    0x00000001, 0x00000009,
};
