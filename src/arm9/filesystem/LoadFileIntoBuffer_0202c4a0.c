#include "nitro/types.h"

typedef struct FileLoader {
    void *reader;
    void *reader2;
    void *work;
    void (*hookA)(void);
    void (*hookB)(void);
} FileLoader;

extern FileLoader data_02060564;
extern u8 data_02053260[0x80];

extern void func_0200b394(void *file);
extern void FSi_WaitForCardThread_01ff8140(void);
extern void openFileFromNitroRomArchive_0202ce60(void *file, u32 id);
extern int func_0202ce18(u32 id);
extern int Strlen_02021e44(const char *s);
extern char *Msg_BuildLangPath_0202b798(const char *name);
extern int CallSelectionHandler_0200b740(void *file, char *path);
extern int PXI_Init_0200b750(void *file);
extern void func_0200b674(void *file, void *dst, int size);
extern int func_0202b894(void *rd, void *file, void *dest, u32 *pSize, int heap, int unused1, int unused2,
                         int *pDone);
extern void func_0200b1e4(void *file);
extern int func_0200b6c8(void *file, void *dst, int size);
extern void RunResetCallbackAndIdle_02004cf0(void);
extern int func_02005794(void *ctx, void *src, int len);
extern void func_0200344c(void *dst, u32 size);
extern void func_020033e0(void);
extern void func_0200b5b0(void *file);

u32 LoadFileIntoBuffer_0202c4a0(u32 data, void *buffer, u32 size, u32 param4)
{
    u8 file[72];
    int done;
    int compressed;
    int nameLen;
    u32 result;
    u8 *rd;

    rd = data_02060564.reader;
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

    if (compressed != 0) {
        func_0202b894(rd, file, buffer, &size, 0, 0, 0, &done);
        result = size;
        if (done == 0) {
            do {
                rd[0x414] ^= 1;
                rd[0x415] ^= 1;
                func_0200b1e4(file);
                *(u32 *)(rd + rd[0x414] * 4 + 0x418) = func_0200b6c8(file, rd + (rd[0x414] << 9), 0x200);
                {
                    s32 status = *(u32 *)(rd + rd[0x415] * 4 + 0x418);
                    if (status != 0 && status == -1) {
                        RunResetCallbackAndIdle_02004cf0();
                    }
                }
            } while (func_02005794(rd + 0x400, rd + (rd[0x415] << 9), *(u32 *)(rd + rd[0x415] * 4 + 0x418)) != 0);
        }
        if (result >= 0x2400) {
            func_020033e0();
        } else {
            func_0200344c(buffer, result);
        }
        func_0200b1e4(file);
    } else {
        result = PXI_Init_0200b750(file);
        if ((s32)result > (s32)size) {
            result = 0xffffffff;
        } else {
            func_0200b674(file, buffer, result);
        }
    }
    func_0200b5b0(file);
    return result;
}
