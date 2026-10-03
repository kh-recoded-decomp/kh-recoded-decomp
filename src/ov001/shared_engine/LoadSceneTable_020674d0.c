#include "nitro/types.h"

typedef struct SceneEntry {
    u8 pad_00[0x1c];
    u16 *name;
    u32 dataA;
    u32 dataB;
} SceneEntry;

typedef struct SceneTableFile {
    u8 count;
    u8 pad_01[3];
    u16 *title;
    SceneEntry *entries[1];
} SceneTableFile;

typedef struct SceneContext {
    SceneTableFile *table;
    u8 pad_04[4];
    void *archive;
    s8 currentId;
    u8 pad_0d[0x10bc - 0xd];
    u16 *caption;
} SceneContext;

extern SceneContext *data_ov001_020a046c;
extern char data_ov001_0209ea8c[];
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *path, int mode, int flags);
extern SceneTableFile *func_0202c478(u32 fileId, u32 flags);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern u16 *GetGridTableValue_02051f70(int row, int column);
extern u16 *GetGridTableValue_02051f48(int row, int column);
extern int LengthTerminatedHalfwords(u16 *text);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff869c(const void *src, void *dst, u32 size);

void LoadSceneTable_020674d0(int sceneId)
{
    SceneContext *context = data_ov001_020a046c;
    char path[32];
    int i;
    SceneTableFile *file;
    int slot;
    SceneTableFile *table;
    SceneEntry *entry;
    u16 *text;
    u16 *copy;
    u32 size;

    OS_SPrintf_02002428(path, data_ov001_0209ea8c, sceneId + 1);
    context->archive = Msg_OpenContainerAndReadHeader_0202cc6c(path, 2, 0);
    file = func_0202c478(0x80000000 | (((u32)context->archive + 0x8000) & 0xfffffc) << 7, 2);
    context->table = file;
    for (i = 0; i < file->count; i++) {
        file->entries[i] = (SceneEntry *)((u8 *)file + (u32)file->entries[i]);
    }
    for (i = 0; i < file->count; i++) {
        entry = file->entries[i];
        entry->dataA += (u32)entry;
        entry->dataB += (u32)entry;
    }
    table = context->table;
    AcquireRecordSlot_02051d3c(0xd, 1);
    for (slot = 0; slot < table->count; slot++) {
        entry = table->entries[slot];
        text = GetGridTableValue_02051f70(sceneId, slot);
        if (text != NULL) {
            size = (LengthTerminatedHalfwords(text) + 1) * 2;
            copy = NNSi_FndAllocFromDefaultHeap_0202a178(size);
            entry->name = copy;
            func_01ff869c(text, copy, size);
        }
    }
    ReleaseRecordSlot_02051dfc(0xd);
    AcquireRecordSlot_02051d3c(2, 1);
    text = GetGridTableValue_02051f48(sceneId, -1);
    size = (LengthTerminatedHalfwords(text) + 1) * 2;
    copy = NNSi_FndAllocFromDefaultHeap_0202a178(size);
    table->title = copy;
    func_01ff869c(text, copy, size);
    text = GetGridTableValue_02051f48(9, -1);
    size = (LengthTerminatedHalfwords(text) + 1) * 2;
    copy = NNSi_FndAllocFromDefaultHeap_0202a178(size);
    context->caption = copy;
    func_01ff869c(text, copy, size);
    ReleaseRecordSlot_02051dfc(2);
    context->currentId = sceneId;
}
