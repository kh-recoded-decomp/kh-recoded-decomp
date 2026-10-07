#include "nitro/types.h"

typedef struct SelectionSession {
    s32 result;
    s32 status;
} SelectionSession;

extern s32 data_ov000_020639cc[];

extern SelectionSession *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov039_020bbb8c(void *arg);
extern BOOL IsStatePhaseIdle(void);
extern int RuntimeState_GetObjectId(void);
extern void func_ov039_020bbe80(int arg);

int UpdateOv039Selection(void)
{
    SelectionSession *session = NNSi_FndGetCurrentRootHeap();
    int result;

    switch (session->status) {
    case 0:
        func_ov039_020bbb8c(NULL);
        if (IsStatePhaseIdle()) {
            result = RuntimeState_GetObjectId();
            if (result != -1) {
                result = data_ov000_020639cc[RuntimeState_GetObjectId()];
            }
            session->result = result;
            func_ov039_020bbe80(0);
            if (result >= 0) {
                session->status = 1;
            } else {
                session->status = 2;
            }
        }
        break;
    case 1:
    case 2:
        break;
    }
    return 0;
}
