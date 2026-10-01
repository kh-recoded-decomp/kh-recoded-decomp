#include "nitro/types.h"

typedef struct SeqRequest {
    int seqArcNo;
    int seqIndex;
    int fadeFrames;
    int pendingAction;
} SeqRequest;

typedef struct SeqRequestOwner {
    u8 pad_00[0x10];
    SeqRequest requests[2];
} SeqRequestOwner;

extern void func_0204d8d0(int seqArcNo, int seqIndex);
extern void StopSeqArcOrDefault_0204d960(int seqArcNo, int seqIndex, int fadeFrames);

void ApplyPendingSeqRequests_02089a14(SeqRequestOwner *owner)
{
    int requestIndex;

    for (requestIndex = 0; requestIndex < 2; requestIndex++) {
        switch (owner->requests[requestIndex].pendingAction) {
        case 1:
            func_0204d8d0(owner->requests[requestIndex].seqArcNo, owner->requests[requestIndex].seqIndex);
            break;
        case 2:
            StopSeqArcOrDefault_0204d960(owner->requests[requestIndex].seqArcNo, owner->requests[requestIndex].seqIndex, owner->requests[requestIndex].fadeFrames);
            break;
        }
        owner->requests[requestIndex].pendingAction = 0;
    }
}
