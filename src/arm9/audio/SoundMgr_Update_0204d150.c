#include "nitro/types.h"
#include "nnsys/snd.h"

typedef struct SoundSlot {
    struct SoundSlot *next;
    u8 pad_04[0x12];
    s16 playerNo;
} SoundSlot;

typedef struct {
    u8 pad_00000[0xb44d8];
    NNSSndHandle bgmHandle;
    u8 pad_b44dc[0xb471c - 0xb44dc];
    SoundSlot *activeSlots;
    u8 pad_b4720[0xb472a - 0xb4720];
    s16 currentBgmId;
    s16 pendingBgmId;
    u8 phase;
    u8 bgmVolume;
    int fadeTimer;
    s16 savedSeqVar;
    s16 savedBgmId;
    u8 pad_b4738[0xb47be - 0xb4738];
    u8 command;
    u8 commandSoundId;
    u16 commandFadeFrames;
    u8 pad_b47c2[0xb47d3 - 0xb47c2];
    u8 commandReady;
} SoundWork;

extern SoundWork *g_soundWork_0206084c;
extern const u8 data_020559d8[];
extern void func_0204cae4(void);
extern void func_0204cedc(void);
extern int func_0204cf58(int value);
extern void func_0204d004(u16 fadeFrames);
extern void func_0204ccf0(SoundSlot *slot);
extern void func_0204cd64(SoundSlot *slot);
extern void RequestSoundLoad_0204cfac(u32 soundId);
extern void NNS_SndPlayerPause_0201d4d0(NNSSndHandle *handle, BOOL flag);
extern int NNS_SndPlayerCountPlayingSeqByPlayerNo_0201d6c0(int playerNo);
extern void func_0201d740(NNSSndHandle *handle, int targetVolume, int frames);
extern BOOL func_0201d850(NNSSndHandle *handle, int varNo, s16 *var);
extern BOOL func_0201d898(NNSSndHandle *handle, int varNo, s16 var);
extern BOOL func_0201fd34(NNSSndHandle *handle, int seqNo);
extern void func_0201d290(void);

void SoundMgr_Update_0204d150(void)
{
    SoundWork *work = g_soundWork_0206084c;

    func_0204cae4();

    switch (work->phase) {
    case 0:
        if (work->commandReady != 0) {
            func_0204cedc();
            switch (work->command) {
            case 1:
            case 2:
            case 4:
                work->pendingBgmId = -1;
                if (work->command != 1) {
                    work->command = 2;
                }
                RequestSoundLoad_0204cfac(work->commandSoundId);
                break;
            default:
                work->command = 0;
                break;
            }
        }
        break;

    case 3:
        if (work->commandReady != 0) {
            s16 target = work->currentBgmId;
            u8 command;
            u8 soundId;

            func_0204cedc();
            command = work->command;
            soundId = work->commandSoundId;

            switch (command) {
            case 0:
                break;
            case 1:
            case 2:
                work->pendingBgmId = -1;
                RequestSoundLoad_0204cfac(soundId);
                break;
            case 3:
                work->pendingBgmId = -1;
                func_0204d004(work->commandFadeFrames);
                break;
            case 4:
                work->pendingBgmId = -1;
                if (target == soundId) {
                    break;
                }
                if (target >= 0) {
                    work->currentBgmId = -1;
                    if (data_020559d8[target] == 1) {
                        func_0201d850(&work->bgmHandle, 0, &work->savedSeqVar);
                        work->savedBgmId = target;
                    }
                    NNS_SndPlayerPause_0201d4d0(&work->bgmHandle, work->commandFadeFrames);
                    work->fadeTimer = work->commandFadeFrames;
                    work->phase = 4;
                } else {
                    RequestSoundLoad_0204cfac(soundId);
                }
                break;
            }
        }
        break;

    case 2:
        switch (work->command) {
        case 0:
            func_0204cedc();
            break;
        case 1: {
            u8 command;

            if (func_0204cf58(0) == 0) {
                break;
            }
            func_0204cedc();
            command = work->command;
            if (command == 2 || command == 4) {
                u8 soundId = work->commandSoundId;
                if (work->currentBgmId != soundId) {
                    RequestSoundLoad_0204cfac(soundId);
                    break;
                }
            }
            if (command == 3) {
                work->pendingBgmId = -1;
                func_0204d004(work->commandFadeFrames);
            }
            break;
        }
        case 2:
        case 4: {
            BOOL resumed = FALSE;

            func_0201fd34(&work->bgmHandle, work->currentBgmId);
            if (data_020559d8[work->currentBgmId] == 1) {
                if (work->currentBgmId == work->savedBgmId) {
                    func_0201d898(&work->bgmHandle, 0, work->savedSeqVar);
                    func_0201d740(&work->bgmHandle, work->bgmVolume, 0x14);
                    resumed = TRUE;
                } else {
                    work->savedSeqVar = 0;
                    work->savedBgmId = work->currentBgmId;
                }
            }
            if (!resumed) {
                func_0201d898(&work->bgmHandle, 0, 0);
                func_0201d740(&work->bgmHandle, work->bgmVolume, 0);
            }
            work->command = 0;
            work->phase = 3;
            break;
        }
        case 3:
            break;
        }
        break;

    case 4: {
        int timer = work->fadeTimer;
        if (timer > 0) {
            work->fadeTimer = timer - 1;
        }
        if (work->fadeTimer != 0) {
            break;
        }
        if (work->command == 4) {
            RequestSoundLoad_0204cfac(work->commandSoundId);
        } else {
            work->command = 0;
            work->phase = 0;
        }
        break;
    }
    }

    {
        SoundSlot *slot = work->activeSlots;
        while (slot != NULL) {
            s16 playerNo = slot->playerNo;
            SoundSlot *next = slot->next;
            if (NNS_SndPlayerCountPlayingSeqByPlayerNo_0201d6c0(playerNo) == 0) {
                func_0204ccf0(slot);
            } else {
                func_0204cd64(slot);
            }
            slot = next;
        }
    }
    func_0201d290();
}
