#include "nitro/types.h"

typedef struct PanelResources {
    u8 pad_00[0x30];
    u8 fontA[0xc];
    u8 fontB[0x118 - 0x3c];
    u8 messagesA[0xc];
    u8 messagesB[0xc];
} PanelResources;

typedef struct PanelPaths {
    const char *fontB;
    const char *fontA;
    const char *messagesB;
    const char *messagesA;
} PanelPaths;

extern PanelResources *data_ov002_0206c460;
extern PanelPaths data_ov002_0206c280;
extern void ResetDisplayHardware_02029bfc(void);
extern int func_02001458(void *font, const char *path);
extern void func_ov027_020ba25c(void *messages, const char *path, int flags);
extern void func_ov002_02062254(void);
extern void func_ov002_02062368(void);

void ReloadPanelResources_02062938(void)
{
    ResetDisplayHardware_02029bfc();
    func_02001458(data_ov002_0206c460->fontA, data_ov002_0206c280.fontA);
    func_02001458(data_ov002_0206c460->fontB, data_ov002_0206c280.fontB);
    func_ov027_020ba25c(data_ov002_0206c460->messagesA, data_ov002_0206c280.messagesA, 1);
    func_ov027_020ba25c(data_ov002_0206c460->messagesB, data_ov002_0206c280.messagesB, 1);
    func_ov002_02062254();
    func_ov002_02062368();
}
