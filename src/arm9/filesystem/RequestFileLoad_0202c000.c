#include "nitro/types.h"

typedef struct FileLoader {
    void *reader;
    void *reader2;
    void *work;
    void (*hookA)(void);
    void (*hookB)(void);
    void **heap;
} FileLoader;

extern FileLoader data_02060564;
extern u8 data_02053260[0x80];

extern void *func_0202b810(void);
extern void func_0200b394(void *file);
extern void FSi_WaitForCardThread_01ff8140(void);
extern void openFileFromNitroRomArchive_0202ce60(void *file, u32 id);
extern int func_0202ce18(u32 id);
extern int Strlen_02021e44(const char *s);
extern char *Msg_BuildLangPath_0202b798(const char *name);
extern int CallSelectionHandler_0200b740(void *file, char *path);
extern void *AllocFromHeapOrDefaultEx_0202a210(u32 size, int align, void **heap);
extern void func_0202b9a4(void *handle, void *file, int a, int b, void **heap, int alignMode, int param3);
extern void func_0200b5b0(void *file);
extern void OS_SendMessage(void *queue, void *msg, int flags);
extern u8 message_queue_02060584;

typedef struct LoadHandle {
    u8 pad_00[4];
    s32 mode;
    u32 field8;
    u32 fileStart;
    u32 fileEnd;
    u8 pad_14[0x28 - 0x14];
    void *buffer;
    s32 size;
} LoadHandle;

u32 RequestFileLoad_0202c000(u32 data, int alignMode, int param3, u32 param4)
{
    u8 file[72];
    LoadHandle *handle;
    int nameLen;
    int compressed;

    handle = func_0202b810();
    if (handle == 0) {
        return 0;
    }

    func_0200b394(file);
    FSi_WaitForCardThread_01ff8140();

    if (data & 0x80000000) {
        openFileFromNitroRomArchive_0202ce60(file, data);
        compressed = func_0202ce18(data);
    } else {
        nameLen = Strlen_02021e44((char *)data);
        CallSelectionHandler_0200b740(file, Msg_BuildLangPath_0202b798((char *)data));
        compressed = 0;
        if (((s8 *)data)[nameLen - 2] == '.') {
            s32 c = ((s8 *)data)[nameLen - 1];
            if (c >= 0 && c < 0x80) {
                c = data_02053260[c];
            }
            if (c == 'Z') {
                compressed = 1;
            }
        }
    }

    handle->field8 = *(u32 *)(file + 8);
    handle->fileStart = *(u32 *)(file + 0x24);
    handle->fileEnd = *(u32 *)(file + 0x28);

    if (compressed != 0) {
        func_0202b9a4(handle, file, 0, 0, data_02060564.heap, alignMode, param3);
        handle->mode = 1;
    } else {
        handle->size = handle->fileEnd - handle->fileStart;
        if (alignMode != 0) {
            handle->buffer = AllocFromHeapOrDefaultEx_0202a210(handle->size, 0xffffffe0, data_02060564.heap);
        } else {
            handle->buffer = AllocFromHeapOrDefaultEx_0202a210(handle->size, 0x20, data_02060564.heap);
        }
        handle->mode = 0;
    }
    data_02060564.heap = 0;
    func_0200b5b0(file);
    OS_SendMessage(&message_queue_02060584, handle, 1);
    return (u32)handle->buffer;
}
