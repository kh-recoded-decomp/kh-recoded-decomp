#include "nitro/types.h"

typedef struct {
    u32 pixelFmt;
    u32 mapingType;
    u32 characterFmt;
    u32 unk_0C;
    u32 szByte;
    void *pRawData;
} CharacterData;

typedef struct {
    u32 active;
    u8 modeState[0xc];
    s32 layout;
    u8 pad_14[0xe4];
    BOOL skipLoad;
} ActiveContext;

extern ActiveContext *g_activeContext_020a04c4;

extern void *func_ov027_020ba1d8(void *resource);
extern void func_ov027_020ba1e0(void *resource, BOOL freeData);
extern BOOL func_02014d38(void *file, CharacterData **out);
extern void func_ov001_02078ba8(void *charData, int layout);
extern void func_020033e0(void);
extern void GX_LoadBG1Char_020079b0(const void *src, u32 offset, u32 size);
extern void func_ov001_0207a1a8(void *modeState, int layout);

void LoadModeBg1Characters_02078d24(void *resource)
{
    ActiveContext *context = g_activeContext_020a04c4;
    CharacterData *charData;

    if (context->skipLoad) {
        func_ov027_020ba1e0(resource, TRUE);
        return;
    }
    func_02014d38(func_ov027_020ba1d8(resource), &charData);
    func_ov001_02078ba8(charData->pRawData, context->layout);
    func_020033e0();
    GX_LoadBG1Char_020079b0(charData->pRawData, 0x1c00, 0x3840);
    func_ov001_0207a1a8(context->modeState, context->layout);
    func_ov027_020ba1e0(resource, TRUE);
}
