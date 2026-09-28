#include "nitro/types.h"

extern int func_02010c74(void);
extern int func_0200b288(u8 *path, int len);

int func_0200b350(u8 *path) {
    int len = func_02010c74();
    int pos = func_0200b288(path, len);
    if (pos >= 0 && (path[pos] == '/' || path[pos] == '\\')) {
        path[pos] = 0;
        len = pos;
    }
    return len;
}
