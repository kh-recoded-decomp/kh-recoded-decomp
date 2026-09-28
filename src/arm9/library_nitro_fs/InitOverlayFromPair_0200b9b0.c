#include "nitro/types.h"

typedef struct {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 mode;
    u32 field_10;
    u32 field_14;
    u32 field_18;
    u32 field_1c;
} State;

typedef struct {
    u32 typeTag;
    u32 value;
} TypeTagPair;

typedef struct {
    u8 pad_00[4];
    void *base;
    u8 pad_08[0x10];
    u32 value;
} Overlay;

extern void func_0200b394(State *state);
extern void MakeTypeTagPair_0200b824(TypeTagPair *result, Overlay *source);
extern int func_0200b4d4(State *state, TypeTagPair pair);
extern int FSi_GetOverlayBinarySize_0200b7cc(void *obj);
extern void FS_InitializeOverlayMemory_0200b7e8(int *ov);
extern int func_0200b6c8(State *state, void *base, int size);
extern BOOL func_0200b5b0(void *object);

BOOL InitOverlayFromPair_0200b9b0(Overlay *overlay, State *state) {
    TypeTagPair pair;
    TypeTagPair *pairPtr = &pair;
    BOOL success = FALSE;

    func_0200b394(state);
    MakeTypeTagPair_0200b824(pairPtr, overlay);
    if (func_0200b4d4(state, *pairPtr) != 0) {
        int size = FSi_GetOverlayBinarySize_0200b7cc(overlay);
        FS_InitializeOverlayMemory_0200b7e8((int *)overlay);
        int result = func_0200b6c8(state, overlay->base, size);
        if (size == result) {
            success = TRUE;
        } else {
            func_0200b5b0(state);
        }
    }
    return success;
}
