#include "nitro/types.h"

typedef struct {
    u8 data[0x28];
} MessageLoader;

typedef struct {
    u32 state;
    MessageLoader common;
    MessageLoader localized[3];
} MessageLoaderSet;

extern char data_ov001_0209eb50[];
extern char data_ov001_0209eb54[];
extern char data_ov001_0209eb64[];
extern void OS_SPrintf_02002428(char *dest, const char *format, ...);
extern char *Msg_BuildLangPath_0202b798(const char *path);
extern void func_ov001_0206c77c(MessageLoader *loader, const char *path, int localized);
extern void RegisterSessionCallback_0206c704(void (*callback)(void));
extern void func_ov001_0206ca34(void);

void InitMessageLoaders_0206c924(MessageLoaderSet *set)
{
    char path[128];
    int i;

    OS_SPrintf_02002428(path, data_ov001_0209eb50, data_ov001_0209eb54);
    i = 0;
    func_ov001_0206c77c(&set->common, path, 0);
    OS_SPrintf_02002428(path, data_ov001_0209eb50, Msg_BuildLangPath_0202b798(Msg_BuildLangPath_0202b798(data_ov001_0209eb64)));
    for (; i < 3; i++) {
        func_ov001_0206c77c(&set->localized[i], path, 1);
    }
    set->state = 0;
    RegisterSessionCallback_0206c704(func_ov001_0206ca34);
}
