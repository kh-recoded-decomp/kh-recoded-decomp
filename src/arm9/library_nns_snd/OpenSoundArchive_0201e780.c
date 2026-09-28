#include "nitro/types.h"

typedef struct {
    void *arcPtr;
    u32 value;
} FileId;

typedef struct {
    u8 pad_00[0x30];
    BOOL fileOpen;
    u8 file[0x48];
    FileId fileId;
    u32 unk_84;
    u32 unk_88;
    u32 unk_8c;
    void *fat;
    void *symbol;
    void *info;
    s32 loadBlockSize;
} SndArc;

extern int func_0200b408(FileId *fileId);
extern void func_0200b394(void *file);
extern int func_0200b4d4(void *file, FileId fileId);
extern int func_0200b52c(void *file, void *path, int flag);
extern BOOL NNS_SndArcSetup_0201e838(SndArc *arc, void *heap, BOOL symbolLoadFlag);
extern SndArc *data_0205e2e4;

void OpenSoundArchive_0201e780(SndArc *arc, void *filePath, void *heap, BOOL symbolLoadFlag)
{
    int ok;

    arc->info = NULL;
    arc->fat = NULL;
    arc->symbol = NULL;
    arc->loadBlockSize = 0;
    arc->unk_84 = 0;
    arc->unk_88 = 0;
    arc->unk_8c = 0;

    if (func_0200b408(&arc->fileId) != 0) {
        func_0200b394(arc->file);
        ok = func_0200b4d4(arc->file, arc->fileId);
        if (!ok) return;
    } else {
        arc->fileId.arcPtr = NULL;
        arc->fileId.value = 0xffffffff;
        ok = func_0200b52c(arc->file, filePath, 1);
        if (!ok) return;
    }

    arc->fileOpen = TRUE;
    if (NNS_SndArcSetup_0201e838(arc, heap, symbolLoadFlag)) {
        data_0205e2e4 = arc;
    }
}
