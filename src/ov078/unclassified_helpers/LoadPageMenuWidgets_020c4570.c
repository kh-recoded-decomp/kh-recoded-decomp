#include "nitro/types.h"

#define ARCHIVE_FILE_ID(handle, index) ((((u32)(handle) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

typedef struct ObjManagerConfig {
    u32 cellFileId;
    u32 unk_04;
    u32 unk_08;
    u32 unk_0C;
} ObjManagerConfig;

typedef struct PageMenu {
    void *archive;
    u8 pad_04[0x20];
    void *nodes[11];
} PageMenu;

extern const ObjManagerConfig data_ov078_020c4f90;

extern void *func_ov039_020bc1bc(void);
extern void InitObjManagerAndMark_020b9060(void *container, ObjManagerConfig *config);
extern void func_ov027_020b8f98(void *container, u32 fileId, int count);
extern void *FindWidgetById_020b90a4(void *container, int id);
extern void func_ov027_020b97b8(void *container, void *widget, int mode);
extern void func_ov027_020b95e4(void *container, void *widget);
extern void func_ov027_020b96a0(void *container, void *widget, int mode);
extern int ReadGlobalPackedBits_02027348(int bit, int width);

void LoadPageMenuWidgets_020c4570(PageMenu *menu)
{
    void *container = func_ov039_020bc1bc();
    ObjManagerConfig config = data_ov078_020c4f90;
    void *stars[5];
    int i;
    int cleared;

    config.cellFileId = ARCHIVE_FILE_ID(menu->archive, 1);
    InitObjManagerAndMark_020b9060(container, &config);
    func_ov027_020b8f98(container, ARCHIVE_FILE_ID(menu->archive, 2), 0x12);
    menu->nodes[0] = FindWidgetById_020b90a4(container, 0xe);
    menu->nodes[1] = FindWidgetById_020b90a4(container, 0);
    menu->nodes[2] = FindWidgetById_020b90a4(container, 4);
    menu->nodes[3] = FindWidgetById_020b90a4(container, 5);
    menu->nodes[4] = FindWidgetById_020b90a4(container, 6);
    menu->nodes[5] = FindWidgetById_020b90a4(container, 0xf);
    menu->nodes[6] = FindWidgetById_020b90a4(container, 0x10);
    menu->nodes[7] = FindWidgetById_020b90a4(container, 0x11);
    menu->nodes[8] = FindWidgetById_020b90a4(container, 1);
    menu->nodes[9] = FindWidgetById_020b90a4(container, 2);
    menu->nodes[10] = FindWidgetById_020b90a4(container, 3);
    for (i = 0; i < 6; i++) {
        func_ov027_020b97b8(container, menu->nodes[i + 2], 3);
    }
    stars[0] = FindWidgetById_020b90a4(container, 7);
    stars[1] = FindWidgetById_020b90a4(container, 8);
    stars[2] = FindWidgetById_020b90a4(container, 9);
    stars[3] = FindWidgetById_020b90a4(container, 10);
    stars[4] = FindWidgetById_020b90a4(container, 0xb);
    for (i = 0; i < 5; i++) {
        void *star = stars[i];
        func_ov027_020b95e4(container, star);
        func_ov027_020b96a0(container, star, 0);
    }
    cleared = ReadGlobalPackedBits_02027348(0xf38, 4);
    if (cleared > 5) {
        cleared = 5;
    }
    switch (cleared) {
    case 5:
        func_ov027_020b96a0(container, stars[4], 1);
    case 4:
        func_ov027_020b96a0(container, stars[3], 1);
    case 3:
        func_ov027_020b96a0(container, stars[2], 1);
    case 2:
        func_ov027_020b96a0(container, stars[1], 1);
    case 1:
        func_ov027_020b96a0(container, stars[0], 1);
        break;
    }
}
