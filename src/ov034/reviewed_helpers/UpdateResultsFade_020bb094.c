#include "nitro/types.h"

typedef struct ResultsWork {
    u8 pad_00[0x5c];
    u8 fadeTarget[0x649c];
    int fadeReady;
    int fadeActive;
    u8 pad_6500[0x694];
    u16 fadeParam;
    u8 pad_6b96[0x1a];
    int fadeMode;
    int syncSecondary;
    int brightness;
} ResultsWork;

extern ResultsWork *resultsState_020c0f80[2];
#define resultsWork (resultsState_020c0f80[1])
extern void func_ov027_020b8c94(void *target, u16 param);
extern void SetBrightnessAndSyncMain_02029e7c(int brightness);
extern void SetSecondaryBrightness_02029ed0(int brightness);

void UpdateResultsFade_020bb094(void)
{
    int mode;

    if (resultsWork->fadeActive == 0 || resultsWork->fadeReady == 0) {
        goto done;
    }
    func_ov027_020b8c94(resultsWork->fadeTarget, resultsWork->fadeParam);
    mode = resultsWork->fadeMode;
    if (mode == 1 && resultsWork->brightness != 0) {
        if (resultsWork->brightness < 0) {
            resultsWork->brightness += 3;
            if (resultsWork->brightness > 0) {
                resultsWork->brightness = 0;
            }
        } else {
            resultsWork->brightness -= 1;
            if (resultsWork->brightness < 0) {
                resultsWork->brightness = 0;
            }
        }
        SetBrightnessAndSyncMain_02029e7c(resultsWork->brightness);
        if (resultsWork->syncSecondary != 0) {
            SetSecondaryBrightness_02029ed0(resultsWork->brightness);
        }
    } else if (mode == 0 && resultsWork->brightness > -16) {
        resultsWork->brightness -= 6;
        if (resultsWork->brightness < -16) {
            resultsWork->brightness = -16;
        }
        SetBrightnessAndSyncMain_02029e7c(resultsWork->brightness);
        if (resultsWork->syncSecondary != 0) {
            SetSecondaryBrightness_02029ed0(resultsWork->brightness);
        }
    } else if (mode == 2 && resultsWork->brightness < 16) {
        resultsWork->brightness += 6;
        if (resultsWork->brightness > 16) {
            resultsWork->brightness = 16;
        }
        SetBrightnessAndSyncMain_02029e7c(resultsWork->brightness);
        if (resultsWork->syncSecondary != 0) {
            SetSecondaryBrightness_02029ed0(resultsWork->brightness);
        }
    }
done:
    resultsWork->fadeActive = 0;
}
