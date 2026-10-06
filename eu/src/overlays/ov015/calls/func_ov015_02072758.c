#include "nitro/types.h"

extern void PlaySoundEffect(int a, int b);
extern void func_ov027_020b9380(void *state, u32 param, int *outBuf, int flags);
extern u32 FindWidgetById(void *state, int id);
extern void func_ov027_020b91e8(void *state, u32 value, int *outBuf, int flags);
extern void SetFocusedWidget(void *state, u32 value);
extern u8 *data_ov015_0207e960;

void func_ov015_02072758(u32 param) {
    int outBuf[2];
    u32 value;

    data_ov015_0207e960[0xe0] |= 2;
    func_ov027_020b9380(data_ov015_0207e960 + 0x6ac0, param, outBuf, 0);
    outBuf[0] = outBuf[0] - 0x2c000;
    value = FindWidgetById(data_ov015_0207e960 + 0x6ac0, 0xb);
    func_ov027_020b91e8(data_ov015_0207e960 + 0x6ac0, value, outBuf, 0);
    value = FindWidgetById(data_ov015_0207e960 + 0x6ac0, 9);
    SetFocusedWidget(data_ov015_0207e960 + 0x6ac0, value);
    PlaySoundEffect(2, 1);
}
