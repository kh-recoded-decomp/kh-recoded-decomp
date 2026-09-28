#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x160];
    u8 container[0x6500];
} Ov015Scene;

extern Ov015Scene *data_ov015_020812e0;

extern void *func_ov027_020b90a4(void *container, int subitemId);
extern void ApplySelectedSubitemValues_020b94fc(void *container, void *subitem, BOOL useAlt);
extern void func_ov027_020b96e4(void *container, void *subitem);
extern void func_ov027_020b9620(void *container, void *subitem);
extern void func_ov027_020b95e4(void *container, void *subitem);

void SetContainerSubitem1Active_02078228(BOOL active) {
    void *subitem;

    if (active) {
        subitem = func_ov027_020b90a4(data_ov015_020812e0->container, 1);
        ApplySelectedSubitemValues_020b94fc(data_ov015_020812e0->container, subitem, TRUE);
        subitem = func_ov027_020b90a4(data_ov015_020812e0->container, 1);
        func_ov027_020b96e4(data_ov015_020812e0->container, subitem);
        subitem = func_ov027_020b90a4(data_ov015_020812e0->container, 1);
        func_ov027_020b9620(data_ov015_020812e0->container, subitem);
    } else {
        subitem = func_ov027_020b90a4(data_ov015_020812e0->container, 1);
        ApplySelectedSubitemValues_020b94fc(data_ov015_020812e0->container, subitem, FALSE);
        func_ov027_020b96e4(data_ov015_020812e0->container, NULL);
        subitem = func_ov027_020b90a4(data_ov015_020812e0->container, 1);
        func_ov027_020b95e4(data_ov015_020812e0->container, subitem);
    }
}
