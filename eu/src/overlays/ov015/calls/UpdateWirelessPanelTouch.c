#include "src/overlays/ov015/Ov015PanelWork.h"

typedef struct TouchSample {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TouchSample;

extern int CopyRecentTouchPoints(TouchSample *samples);

void UpdateWirelessPanelTouch(void)
{
    TouchSample samples[4];
    s16 previousCount = gOv015PanelWork->touchSampleCount;
    int count;
    int index;
    s16 *averageX;
    s16 *averageY;

    if (previousCount <= 0) {
        gOv015PanelWork->previousTouch.x = -1;
        gOv015PanelWork->previousTouch.y = -1;
    } else {
        gOv015PanelWork->previousTouch.x = gOv015PanelWork->touchSamples[previousCount - 1].x;
        gOv015PanelWork->previousTouch.y = gOv015PanelWork->touchSamples[previousCount - 1].y;
    }
    count = CopyRecentTouchPoints(samples);
    if (count > 0) {
        averageX = &gOv015PanelWork->averageTouch.x;
        averageY = &gOv015PanelWork->averageTouch.y;
        *averageX = 0;
        *averageY = 0;
        for (index = 0; index < count; index++) {
            Ov015TouchPoint *point = &gOv015PanelWork->touchSamples[index];
            point->x = samples[index].x;
            point->y = samples[index].y;
            if (point->x >= 256) {
                point->x = 255;
            } else if (point->x < 0) {
                point->x = 0;
            }
            if (point->y >= 192) {
                point->y = 191;
            } else if (point->y < 0) {
                point->y = 0;
            }
            *averageX += point->x;
            *averageY += point->y;
        }
        *averageX /= count;
        *averageY /= count;
    } else {
        gOv015PanelWork->touchSamples[0].x = -1;
        gOv015PanelWork->touchSamples[0].y = -1;
    }
    gOv015PanelWork->touchSampleCount = count;
}
