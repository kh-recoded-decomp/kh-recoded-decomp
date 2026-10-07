#include "nitro/types.h"

extern u8 data_ov061_020d8569[];
extern void CreateAuraBattleObject(void);
extern void CreateBossBattleObject(void);
extern void CreateBurstBattleObject(void);
extern void CreateMarkedSceneTask(void);
extern void CreateOv067BossObject(void);
extern void CreateOv068BossObject(void);
extern void CreateOv069BossObject(void);
extern void CreateOv070BossObject(void);
extern void CreateOv071SceneTask(void);
extern void CreateOv072SceneTask(void);
extern void CreateSceneTask(void);

const u32 data_ov021_020b508c[38] = {
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

void *const data_ov021_020b502c[24] = {
    (void *)CreateBurstBattleObject,
    (void *)0x0000003D,
    (void *)CreateBossBattleObject,
    (void *)0x0000003E,
    (void *)CreateSceneTask,
    (void *)0x0000003F,
    (void *)CreateMarkedSceneTask,
    (void *)0x00000040,
    (void *)CreateAuraBattleObject,
    (void *)0x00000041,
    (void *)data_ov061_020d8569,
    (void *)0x00000042,
    (void *)CreateOv067BossObject,
    (void *)0x00000043,
    (void *)CreateOv068BossObject,
    (void *)0x00000044,
    (void *)CreateOv069BossObject,
    (void *)0x00000045,
    (void *)CreateOv070BossObject,
    (void *)0x00000046,
    (void *)CreateOv071SceneTask,
    (void *)0x00000047,
    (void *)CreateOv072SceneTask,
    (void *)0x00000048,
};

const u32 data_ov021_020b5014[6] = {
    0x00000003, 0x00000004, 0x00000001, 0x00000000,
    0x00000001, 0x00000009,
};
