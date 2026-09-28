#include "nitro/types.h"

extern void func_01ff86fc(u32 data, void *dst, u32 size);
extern int advanceTextStringCursor_0208c474(int textBytes, int *byteCursor);
extern char *strcpy_02021e60(char *dst, const char *src);
extern void func_02021f28(char *dst, const char *src, int n);

BOOL SplitTextAtLineBreak_0208c4d8(char *text, char *dest)
{
    int cursor;
    char lineBuffer[256];

    cursor = 0;
    func_01ff86fc(0, dest, 0x100);
    if (advanceTextStringCursor_0208c474((int)text, &cursor) != 0) {
        func_01ff86fc(0, lineBuffer, 0x100);
        strcpy_02021e60(dest, text + cursor);
        func_02021f28(lineBuffer, text, cursor + -2);
        strcpy_02021e60(text, lineBuffer);
        return TRUE;
    }
    return FALSE;
}
