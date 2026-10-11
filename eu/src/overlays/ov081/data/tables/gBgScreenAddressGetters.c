#include "src/overlays/ov081/BgTextTransfers.h"

extern void *G2_GetBG0ScrPtr(void);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2_GetBG2ScrPtr(void);
extern void *G2_GetBG3ScrPtr(void);

const BgScreenAddressGetter gBgScreenAddressGetters[4] = {
    G2_GetBG0ScrPtr,
    G2_GetBG1ScrPtr,
    G2_GetBG2ScrPtr,
    G2_GetBG3ScrPtr,
};
