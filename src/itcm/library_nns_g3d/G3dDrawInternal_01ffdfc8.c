
#include "nitro/types.h"

typedef struct NNSG3dResMdl {
    u32 field00;
    u32 ofsData04;
    u32 ofsData08;
    u32 ofsData0c;
    u8 pad10_15[5];
    u8 index15;
    u8 index16;
    u8 pad17_1c[5];
    u32 field1c;
    u32 field20;
    u8 pad24_40[0x1c];
    u8 data40[1];
} NNSG3dResMdl;

struct NNSG3dRenderState;

typedef void (*NNSG3dRenderInitCallback)(struct NNSG3dRenderState *);
typedef void (*NNSG3dSbcHandler)(struct NNSG3dRenderState *, u32);

typedef struct NNSG3dRenderObj {
    u32 flags;
    NNSG3dResMdl * volatile pResMdl;
    u8 pad08_20[0x18];
    void *pUserData;
    u8 userSlot;
    u8 userByte;
    u8 pad26_28[2];
    NNSG3dRenderInitCallback initCallback;
    u8 pad2c_30[4];
    void *pSbc;
} NNSG3dRenderObj;

typedef struct NNSG3dRenderState {
    u8 *pSbc;
    NNSG3dRenderObj *pRenderObj;
    u32 flags;
    void *userSlots[32];
    u8 userBytes[32];
    u8 pad0ac_0c4[0x18];
    u32 initialized;
    u8 pad0c8_0d4[0x0c];
    void *pResData40;
    void *pResData08;
    void *pResData0c;
    u32 field0e0;
    u32 field0e4;
    u32 field0e8;
    u32 field0ec;
    u32 field0f0;
    u8 pad0f4_188[0x94];
} NNSG3dRenderState;

extern void MIi_CpuClearFast_01ff8740(u32 data, void *dest, u32 size);
extern const u32 data_02055d70[];
extern const u32 data_02055d64[];
extern const u32 data_02055d7c[];
extern NNSG3dSbcHandler data_027e01f8[];

void G3dDrawInternal_01ffdfc8(NNSG3dRenderState *state, NNSG3dRenderObj *renderObj)
{
    NNSG3dResMdl *resource;
    u8 *pSbc;

    MIi_CpuClearFast_01ff8740(0, state, sizeof(*state));
    state->initialized = 1;
    state->flags = 1;

    pSbc = renderObj->pSbc;
    if (pSbc == 0) {
        resource = renderObj->pResMdl;
        pSbc = (u8 *)resource + resource->ofsData04;
    }
    state->pSbc = pSbc;
    state->pRenderObj = renderObj;

    resource = renderObj->pResMdl;
    state->pResData40 = resource != 0 ? resource->data40 : 0;

    resource = renderObj->pResMdl;
    state->pResData08 =
        (resource != 0 && resource->ofsData08 != 0) ?
        (u8 *)resource + resource->ofsData08 : 0;

    resource = renderObj->pResMdl;
    state->pResData0c =
        (resource != 0 && resource->ofsData0c != 0) ?
        (u8 *)resource + resource->ofsData0c : 0;

    state->field0e8 = data_02055d70[renderObj->pResMdl->index15];
    state->field0ec = data_02055d64[renderObj->pResMdl->index15];
    state->field0f0 = data_02055d7c[renderObj->pResMdl->index16];
    state->field0e0 = renderObj->pResMdl->field1c;
    state->field0e4 = renderObj->pResMdl->field20;

    if (renderObj->pUserData != 0 && renderObj->userSlot < 32) {
        state->userSlots[renderObj->userSlot] = renderObj->pUserData;
        state->userBytes[renderObj->userSlot] = renderObj->userByte;
    }

    state->flags |= (renderObj->flags << 28) >> 21;

    if (renderObj->initCallback != 0) {
        renderObj->initCallback(state);
    }

    do {
        u32 command;

        state->flags &= ~0x40;
        command = *state->pSbc;
        data_027e01f8[command & 0x1f](state, command & 0xe0);
    } while ((state->flags & 0x20) == 0);

    renderObj->flags &= ~1;
}
