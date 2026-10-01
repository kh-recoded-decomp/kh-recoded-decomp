#include "nitro/types.h"

typedef struct ModeArchiveContext {
    u8 pad_000[0x140];
    u8 archive[0x648];
    u8 archiveExtra[0x4c];
    void *workBuffer;
    u8 pad_7d8[0x184];
    u8 workArea[0x3584];
    void *container;
    u8 pad_3ee4[8];
    u8 resourceName[0x10];
    int loadedMode;
} ModeArchiveContext;

extern ModeArchiveContext *data_ov001_020a04e0;
extern char data_ov001_0209f2e0[];
extern signed char GetCtxModeByte_02068084(void);
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern int findSharedResourceByName_0202cd8c(void *table, void *name);
extern int RoundAndInitArchive_020258b0(void *record, int flags, int flag, void *extra);
extern void SetLoaderCallbacks_02025914(void *context, void *writeHandler, void *readHandler);
extern void func_ov001_0206459c();
extern void func_ov001_02064574();

void ReloadModeMessageArchive_020883fc(void)
{
    ModeArchiveContext *context = data_ov001_020a04e0;
    char name[16];
    int resource;

    if (context->container == NULL || context->loadedMode != GetCtxModeByte_02068084()) {
        OS_SPrintf_02002428(name, data_ov001_0209f2e0, GetCtxModeByte_02068084() + 1);
        context->container = Msg_OpenContainerAndReadHeader_0202cc6c(name, 0xd, FALSE);
        context->loadedMode = GetCtxModeByte_02068084();
    }
    context->workBuffer = context->workArea;
    resource = findSharedResourceByName_0202cd8c(context->container, context->resourceName);
    RoundAndInitArchive_020258b0(context->archive,
                                 (((u32)context->container + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (resource & 0x1ff),
                                 0, context->archiveExtra);
    SetLoaderCallbacks_02025914(context->archive, func_ov001_0206459c, func_ov001_02064574);
}
