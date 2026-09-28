#include "nitro/types.h"

typedef struct LoadStream {
    u8 sector[2][0x200];
    u8 decompressState[0x14];
    u8 readIndex;
    u8 useIndex;
    u8 pad_416[2];
    s32 readLen[2];
} LoadStream;

typedef struct FileLoader {
    LoadStream *reader;
    void *reader2;
    void *work;
    void (*hookA)(void);
    void (*hookB)(void);
    void **heap;
} FileLoader;

extern FileLoader data_02060564;
extern u8 data_02053260[0x80];

extern void func_0200b394(void *file);
extern void FSi_WaitForCardThread_01ff8140(void);
extern BOOL openFileFromNitroRomArchive_0202ce60(void *file, u32 id);
extern int func_0202ce18(u32 id);
extern int Strlen_02021e44(const char *s);
extern char *Msg_BuildLangPath_0202b798(const char *name);
extern BOOL CallSelectionHandler_0200b740(void *file, char *path);
extern void *func_0202b894(LoadStream *stream, void *file, void *dest, u32 *pSize, void **heap, int alignMode,
                           int kind, int *pDone);
extern void func_0200b1e4(void *file);
extern int func_0200b6c8(void *file, void *dst, int size);
extern void RunResetCallbackAndIdle_02004cf0(void);
extern int func_02005794(void *context, void *src, int len);
extern void func_020033e0(void);
extern void func_0200344c(void *buffer, u32 size);
extern u32 PXI_Init_0200b750(void *file);
extern void *AllocFromHeapOrDefaultEx_0202a210(u32 size, int align, void **heap);
extern void func_0200b674(void *file, void *dst, u32 size);
extern void func_0200b5b0(void *file);

void *FileLoader_LoadAlloc_0202bde4(u32 data, int alignMode, int kind, u32 unused)
{
    u8 file[0x48];
    u32 size;
    int done;
    int opened;
    int compressed;
    void *buffer;
    LoadStream *stream = data_02060564.reader;

    func_0200b394(file);
    FSi_WaitForCardThread_01ff8140();

    if (data & 0x80000000) {
        opened = openFileFromNitroRomArchive_0202ce60(file, data);
        compressed = func_0202ce18(data);
    } else {
        int nameLen = Strlen_02021e44((char *)data);
        opened = CallSelectionHandler_0200b740(file, Msg_BuildLangPath_0202b798((char *)data));
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

    if (opened == 0) {
        return 0;
    }

    if (compressed != 0) {
        buffer = func_0202b894(stream, file, 0, &size, data_02060564.heap, alignMode, kind, &done);
        if (done == 0) {
            do {
                stream->readIndex ^= 1;
                stream->useIndex ^= 1;
                func_0200b1e4(file);
                stream->readLen[stream->readIndex] = func_0200b6c8(file, stream->sector[stream->readIndex], 0x200);
                if (stream->readLen[stream->useIndex] != 0 && stream->readLen[stream->useIndex] == -1) {
                    RunResetCallbackAndIdle_02004cf0();
                }
            } while (func_02005794(stream->decompressState, stream->sector[stream->useIndex],
                                   stream->readLen[stream->useIndex]) != 0);
        }
        if (size >= 0x2400) {
            func_020033e0();
        } else {
            func_0200344c(buffer, size);
        }
        func_0200b1e4(file);
    } else {
        size = PXI_Init_0200b750(file);
        if (alignMode != 0) {
            buffer = AllocFromHeapOrDefaultEx_0202a210(size, -0x20, data_02060564.heap);
        } else {
            buffer = AllocFromHeapOrDefaultEx_0202a210(size, 0x20, data_02060564.heap);
        }
        if (buffer != 0) {
            func_0200b674(file, buffer, size);
        }
    }
    data_02060564.heap = 0;
    func_0200b5b0(file);
    return buffer;
}
