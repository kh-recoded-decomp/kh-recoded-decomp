#include "nitro/types.h"

typedef struct PageMenu {
    void *bufferA;
    void *bufferB;
    void *bufferC;
    void *imageA;
    u8 pad_10[8];
    void *imageB;
    u8 pad_1c[0x5d0 - 0x1c];
    int cursor;
    int page;
} PageMenu;

typedef struct LayoutEntry {
    int start;
    u8 pad_04[8];
    int count;
    int stride;
    u8 pad_14[0x10];
} LayoutEntry;

extern PageMenu *data_ov078_020c51c0;
extern LayoutEntry data_ov078_020c5004[];
extern char data_ov078_020c5148[];
extern char data_ov078_020c515c[];
extern char data_ov078_020c5170[];
extern char data_ov078_020c5180[];
extern u8 *data_0205fe0c;

extern void func_01ff8830(void *dest, int value, u32 size);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *path, int heapId, int flags);
extern void LoadPackedFileView_020ba25c(void **out, const void *path, int flags);
extern void AcquireRecordManager_02051c80(void);
extern void AcquireRecordSlot_02051d3c(int slot, int flags);
extern void func_ov078_020c43c0(PageMenu *menu);
extern void func_ov078_020c4570(PageMenu *menu);
extern void InitSequence_020c471c(PageMenu *menu);

BOOL InitPageMenu_020c4260(PageMenu *menu)
{
    int i;
    int cursor;

    func_01ff8830(menu, 0, sizeof(PageMenu));
    data_ov078_020c51c0 = menu;
    data_ov078_020c5004[0].start = 1;
    for (i = 1; i < 9; i++) {
        data_ov078_020c5004[i].start = data_ov078_020c5004[i - 1].start +
                                       data_ov078_020c5004[i - 1].count * data_ov078_020c5004[i - 1].stride;
    }
    cursor = 0;
    menu->bufferA = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov078_020c5148, 0xe, 0);
    menu->bufferB = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov078_020c515c, 0xe, 0);
    menu->bufferC = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov078_020c5170, 0xe, 0);
    LoadPackedFileView_020ba25c(&menu->imageA, data_ov078_020c5180, 0);
    LoadPackedFileView_020ba25c(&menu->imageB,
                                (const void *)(((((u32)menu->bufferC + 0x8000) & 0xfffffc) << 7) | 0x80000000), 0);
    AcquireRecordManager_02051c80();
    AcquireRecordSlot_02051d3c(2, 0);
    AcquireRecordSlot_02051d3c(0, 0);
    func_ov078_020c43c0(menu);
    func_ov078_020c4570(menu);
    if ((s8)data_0205fe0c[0x28d4] < 5) {
        cursor = (s8)data_0205fe0c[0x28d4];
    }
    menu->cursor = cursor;
    InitSequence_020c471c(menu);
    return TRUE;
}
