#include "nitro/types.h"

typedef struct {
    s8 mode;
} SceneContext;

extern void ScrollDriftingElementsHorizontal_0206fff0(void);
extern void ScrollDriftingElementsVertical_02070174(void);
extern SceneContext *data_ov015_0207e960;

void UpdateDriftingElementsByMode_0206ffa0(void) {
    switch (data_ov015_0207e960->mode) {
    case 0:
    case 1:
    case 7:
        ScrollDriftingElementsHorizontal_0206fff0();
        break;
    case 2:
    case 3:
    case 6:
        ScrollDriftingElementsVertical_02070174();
        break;
    }
}
