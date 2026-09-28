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
} FileState;

typedef struct FSFile FSFile;

extern void func_0200b394(FileState *state);
extern void FSi_WaitForCardThread_01ff8140();
extern BOOL openFileFromNitroRomArchive_0202ce60(FSFile *file, u32 fileId);
extern u32 func_0202ce18(u32 packedCoordinate);
extern int Strlen_02021e44(const u8 *str);
extern char *Msg_BuildLangPath_0202b798(const char *src);
extern int CallSelectionHandler_0200b740(FSFile *file, char *langPath);
extern u32 func_0200b750(FSFile *file);
extern void func_0200b674(FSFile *file, int value, u32 size);
extern const u8 data_02053260[];
extern int *data_02060564[];

u32 func_0202cb7c(u32 fileId)
{
    u8 buffer[0x48];
    u32 state = (u32)buffer;
    int compressed;

    func_0200b394((FileState *)state);
    FSi_WaitForCardThread_01ff8140();

    if (fileId & 0x80000000) {
        u32 opened = openFileFromNitroRomArchive_0202ce60((FSFile *)state, fileId);
        compressed = func_0202ce18(fileId);
        state = opened;
    } else {
        int length = Strlen_02021e44((const u8 *)fileId);
        char *langPath = Msg_BuildLangPath_0202b798((const char *)fileId);
        u32 opened = CallSelectionHandler_0200b740((FSFile *)state, langPath);

        compressed = 0;
        if (((const s8 *)fileId)[length - 2] == '.') {
            int c = ((const s8 *)fileId)[length - 1];

            if (c >= 0 && c < 0x80) {
                c = data_02053260[c];
            }
            if (c == 0x5a) {
                compressed = 1;
            }
        }
        state = opened;
    }

    if (state == 0) {
        return 0;
    }
    if (compressed == 0) {
        goto Simple;
    }
    {
        int *ptr = data_02060564[0];
        func_0200b674((FSFile *)buffer, (int)ptr, 0x200);
        return (u32)*ptr >> 8;
    }

Simple:
    return func_0200b750((FSFile *)buffer);
}
