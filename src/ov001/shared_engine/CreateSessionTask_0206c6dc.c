#include "nitro/types.h"
#include "nnsys/fnd.h"

typedef struct SessionState {
    void *session;
    NNSFndList callbackList;
} SessionState;

extern u8 data_ov001_0209eb3c[];
extern SessionState g_sessionState_020a0488;
extern void *func_0202a448(void *descriptor, void *userData);

void CreateSessionTask_0206c6dc(void)
{
    g_sessionState_020a0488.session = func_0202a448(data_ov001_0209eb3c, NULL);
}
