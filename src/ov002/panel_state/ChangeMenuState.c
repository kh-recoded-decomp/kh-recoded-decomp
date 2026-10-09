#include "nitro/types.h"

typedef struct MenuStateCallbacks {
    void (*enter)(void);
    void (*update)(void);
    void (*leave)(void);
} MenuStateCallbacks;

typedef struct MenuContextHeader {
    s8 state;
} MenuContextHeader;

extern MenuContextHeader *data_ov002_0206c464;
extern MenuStateCallbacks gMenuStateTable[];

void ChangeMenuState(s8 nextState)
{
    if (data_ov002_0206c464->state != -1) {
        gMenuStateTable[data_ov002_0206c464->state].leave();
    }
    data_ov002_0206c464->state = nextState;
    gMenuStateTable[data_ov002_0206c464->state].enter();
}
