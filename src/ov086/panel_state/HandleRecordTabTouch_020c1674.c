#include "nitro/types.h"

typedef struct {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TouchSample;

typedef struct {
    u8 pad000[0x134];
    int group;
    int pad138;
    int subPage;
    u8 pad140[0xa0];
    TouchSample lastTouch;
} RecordPanel;

extern BOOL func_ov087_020c7c18(void);
extern BOOL IsStatePhaseActive_020bca60(void);
extern BOOL GetCameraToTargetDistance_020bca30(void);
extern int CopySourceBlock_020b9f7c(TouchSample *dst);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void func_ov086_020c080c(RecordPanel *panel);

BOOL HandleRecordTabTouch_020c1674(RecordPanel *panel, BOOL playMissSound)
{
    TouchSample touch;
    int offset;

    if (func_ov087_020c7c18()) {
        return FALSE;
    }
    if (IsStatePhaseActive_020bca60() || GetCameraToTargetDistance_020bca30()) {
        return FALSE;
    }
    CopySourceBlock_020b9f7c(&touch);
    if (touch.touch != 1 || touch.touch == panel->lastTouch.touch) {
        return FALSE;
    }
    if (touch.validity != 0) {
        return FALSE;
    }
    if (touch.y < 5 || touch.y >= 0x15) {
        if (playMissSound) {
            PlaySoundEffect_0204d924(0, 2);
        }
        return TRUE;
    }
    if (panel->group == 3) {
        if (touch.x < 0xae || touch.x >= 0xee) {
            if (playMissSound) {
                PlaySoundEffect_0204d924(0, 2);
            }
            return TRUE;
        }
        offset = touch.x - 0xae;
    } else if (panel->group == 6) {
        if (touch.x < 0xbe || touch.x >= 0xee) {
            if (playMissSound) {
                PlaySoundEffect_0204d924(0, 2);
            }
            return TRUE;
        }
        offset = touch.x - 0xbe;
    } else {
        if (touch.x < 0xce || touch.x >= 0xee) {
            if (playMissSound) {
                PlaySoundEffect_0204d924(0, 2);
            }
            return TRUE;
        }
        offset = touch.x - 0xce;
    }
    panel->subPage = offset / 16;
    func_ov086_020c080c(panel);
    PlaySoundEffect_0204d924(0, 2);
    return TRUE;
}
