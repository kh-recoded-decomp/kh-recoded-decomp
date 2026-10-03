#include "nitro/types.h"

typedef struct BoardState {
    int resourceA;
    int resourceB;
    void *widget;
    char pad000c[0x28 - 0xc];
    char animSet[0x74 - 0x28];
    char objectSet[0x64f0 - 0x74];
    void *listener;
    char pad64f4[0x66e0 - 0x64f4];
    int useChannel;
} BoardState;

extern BoardState *data_ov024_020b7520;
extern char data_ov024_020b74fc[];
extern void func_02001154(int channel, void *target, int arg);
extern void func_ov001_020715ac(void *listener);
extern void func_ov024_020b5dc0(void);
extern void func_ov027_020b7dfc(void *animSet);
extern void func_ov027_020b8c58(void *objectSet);
extern void func_ov027_020b9a60(void *widget);
extern void func_ov001_0207b200(int value);
extern void func_0202cd78(int handle);
extern void func_ov024_020b6730(void);

void DestroyBoardScreen_020b6d78(void)
{
    if (data_ov024_020b7520->useChannel) {
        func_02001154(1, data_ov024_020b74fc, 0);
    } else {
        func_ov001_020715ac(data_ov024_020b7520->listener);
    }
    func_ov024_020b5dc0();
    func_ov027_020b7dfc(data_ov024_020b7520->animSet);
    func_ov027_020b8c58(data_ov024_020b7520->objectSet);
    if (data_ov024_020b7520->useChannel) {
        func_ov027_020b9a60(data_ov024_020b7520->widget);
    } else {
        func_ov001_0207b200(0);
    }
    func_0202cd78(data_ov024_020b7520->resourceA);
    func_0202cd78(data_ov024_020b7520->resourceB);
    func_ov024_020b6730();
    data_ov024_020b7520 = NULL;
}
