#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x17];
    u8 nodeCount;
    u8 pad_18[0x28];
    u8 nodeDict[1];
} ModelResource;

typedef struct {
    u8 pad_000[0x24];
    ModelResource *model;
    u8 pad_028[0x2c];
    void *activeNodes;
    u8 pad_058[0xac];
    void *nodes;
    int rootNode;
    int animId;
    int frame;
    int playing;
    u8 pad_118[0x20];
} AnimState;

typedef struct {
    u8 kind;
    u8 pad_001[0x3a3];
    AnimState *anim;
} AnimActor;

extern char data_ov041_020cfa44[];
extern char data_ov041_020cfa58[];
extern char data_ov041_020cfa6c[];
extern char data_ov041_020cfa80[];
extern char data_ov041_020cfa90[];
extern char data_ov041_020cf6f0[];
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_0202ecf8(void *state, const char *path, int a, int b);
extern int FindResourceIndexByName_0201aafc(void *dict, const char *name);

void LoadActorAnimation_020c36ec(AnimActor *actor) {
    char path[20];
    AnimState *anim;
    void *dict;
    int rootNode;

    switch (actor->kind) {
    case 0xff:
        OS_SPrintf_02002428(path, data_ov041_020cfa44);
        break;
    case 0xfe:
        OS_SPrintf_02002428(path, data_ov041_020cfa58);
        break;
    case 0xfd:
        OS_SPrintf_02002428(path, data_ov041_020cfa6c);
        break;
    case 3:
        OS_SPrintf_02002428(path, data_ov041_020cfa80);
        break;
    case 0x10:
        OS_SPrintf_02002428(path, data_ov041_020cfa90);
        break;
    default:
        return;
    }
    anim = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(AnimState));
    actor->anim = anim;
    func_0202ecf8(anim, path, 1, 0x12);
    anim->nodes = NNSi_FndAllocFromDefaultHeap_0202a178(anim->model->nodeCount * 0x58);
    anim->activeNodes = anim->nodes;
    if (anim->model != NULL) {
        dict = anim->model->nodeDict;
    } else {
        dict = NULL;
    }
    if (dict != NULL) {
        rootNode = FindResourceIndexByName_0201aafc(dict, data_ov041_020cf6f0);
    } else {
        rootNode = -1;
    }
    anim->rootNode = rootNode;
    anim->playing = 0;
    anim->animId = -1;
}
