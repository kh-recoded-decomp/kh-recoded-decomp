#include "nitro/types.h"

typedef struct RewardEntry {
    s16 id;
    s16 reward;
    u8 low;
    u8 high;
} RewardEntry;

typedef struct RewardSpec {
    s16 reward;
    u8 low;
    u8 high;
} RewardSpec;

typedef struct UnlockRequest {
    int skipModeCheck;
    int entry;
    int dropOnLock;
    int dropOnUnlock;
    u32 flagEntry;
    u32 flagSlot;
} UnlockRequest;

extern int GetEntryUnlockState_02087478(BOOL skipModeCheck, u32 flagOffset, u32 entryId, u32 slot);
extern RewardEntry *func_ov001_02086928(int index);
extern s16 *func_ov001_0208694c(int index);
extern void GetModeDataRegion_0208698c(u32 *offset, u32 *size);
extern void func_ov001_020645dc(u32 flag);
extern u32 func_ov001_020664f0();
extern void func_ov001_02086978(u32 entryId, u32 slot, int useAlt);
extern void RollRewardOrbDrop_020665bc(int dropIndex, void *target);
extern int func_ov001_020644b0(void);
extern void func_ov001_02086a28(int reward, void *target);

void GrantEntryUnlockReward_02087518(u8 *owner, UnlockRequest *request) {
    switch (GetEntryUnlockState_02087478(request->skipModeCheck, request->entry, request->flagEntry, request->flagSlot)) {
    case 0:
        if (request->entry >= 0) {
            RewardEntry *entry = func_ov001_02086928(request->entry);
            u32 offset;
            u32 size;
            GetModeDataRegion_0208698c(&offset, &size);
            func_ov001_020645dc(offset + request->entry);
            if (entry != NULL) {
                RewardSpec spec;
                spec.reward = entry->reward;
                spec.high = entry->high;
                spec.low = entry->low;
                func_ov001_020664f0(6, *(u32 *)&spec, owner + 0x38, 0);
            }
        }
        break;
    case 1:
        func_ov001_02086978(request->flagEntry, request->flagSlot, 1);
        if (request->dropOnUnlock >= 0) {
            RollRewardOrbDrop_020665bc(request->dropOnUnlock, owner + 0x38);
            if (request->entry >= 0 && func_ov001_020644b0() == 900) {
                s16 *reward = func_ov001_0208694c(request->entry);
                if (reward != NULL && *reward != -1) {
                    func_ov001_020664f0(6, *reward, owner + 0x38, 0);
                }
            }
        } else if (request->entry >= 0) {
            int reward = -1;
            s16 *found;
            if (request->skipModeCheck == 0) {
                found = (s16 *)func_ov001_02086928(request->entry);
                if (found != NULL) {
                    reward = *found;
                }
            } else {
                found = func_ov001_0208694c(request->entry);
                if (found != NULL) {
                    reward = *found;
                }
            }
            if (reward != -1) {
                func_ov001_02086a28(reward, owner + 0x38);
            }
        }
        break;
    case 2:
        if (request->dropOnLock >= 0) {
            RollRewardOrbDrop_020665bc(request->dropOnLock, owner + 0x38);
        }
        break;
    }
}
