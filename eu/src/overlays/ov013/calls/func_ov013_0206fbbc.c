#include "nitro/types.h"

extern int FindWidgetById(int panel, int value);
extern void SetFocusedWidget(int panel, int value);
extern void func_ov027_020b9380(int panel, int value, void *buffer, int flag);
extern void func_ov027_020b91e8(int panel, int value, void *buffer, int flag);
extern int data_ov013_02074ce0;

/* Reconfigures the panel object with an updated tint value. */
void func_ov013_0206fbbc(void) {
    u32 buffer[2];
    int result = FindWidgetById(data_ov013_02074ce0 + 0x6818, *(s8 *)(data_ov013_02074ce0 + 0x2ee) + 0x14);
    SetFocusedWidget(data_ov013_02074ce0 + 0x6818, result);
    func_ov027_020b9380(data_ov013_02074ce0 + 0x6818, result, buffer, 0);
    buffer[1] = *(int *)(data_ov013_02074ce0 + 0xa8) + *(int *)(data_ov013_02074ce0 + 0x2fc) * 0x1000;
    buffer[0] = 0x8000;
    result = FindWidgetById(data_ov013_02074ce0 + 0x6818, 0);
    func_ov027_020b91e8(data_ov013_02074ce0 + 0x6818, result, buffer, 0);
}
