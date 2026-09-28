#include "nitro/types.h"

typedef struct ModelHolder {
    u8 pad_00[0x24];
    u8 *modelResource;
} ModelHolder;

extern char data_ov001_020a04e4[];
extern void func_01ff86fc(u32 data, void *dst, u32 size);
extern char *strcpy_02021e60(char *dst, const char *src);
extern int FindResourceIndexByName_0201aafc(const void *dict, const void *name);

int FindModelResourceIndexByName_0208950c(ModelHolder *holder, const char *name)
{
    void *dict = NULL;

    func_01ff86fc(0, data_ov001_020a04e4, 0x10);
    strcpy_02021e60(data_ov001_020a04e4, name);
    if (holder->modelResource != NULL) {
        dict = holder->modelResource + 0x40;
    }
    if (dict != NULL) {
        return FindResourceIndexByName_0201aafc(dict, data_ov001_020a04e4);
    }
    return -1;
}
