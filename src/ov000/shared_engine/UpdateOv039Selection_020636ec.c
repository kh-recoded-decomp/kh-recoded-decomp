#include "nitro/types.h"

typedef struct SelectionSession {
    s32 result;
    s32 status;
} SelectionSession;

extern s32 data_ov000_020639cc[];

extern SelectionSession *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void UpdateOverlayFrame_020bbb6c(void *arg);
extern BOOL IsStatePhaseIdle_020bcad0(void);
extern int func_ov039_020bcd80(void);
extern void ShutdownOverlay_020bbe60(int arg);

int UpdateOv039Selection_020636ec(void)
{
    SelectionSession *session = NNSi_FndGetCurrentRootHeap_0202a764();
    int result;

    switch (session->status) {
    case 0:
        UpdateOverlayFrame_020bbb6c(NULL);
        if (IsStatePhaseIdle_020bcad0()) {
            result = func_ov039_020bcd80();
            if (result != -1) {
                result = data_ov000_020639cc[func_ov039_020bcd80()];
            }
            session->result = result;
            ShutdownOverlay_020bbe60(0);
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
