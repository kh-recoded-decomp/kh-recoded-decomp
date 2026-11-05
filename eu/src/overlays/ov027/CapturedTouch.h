#ifndef EU_CAPTURED_TOUCH_H
#define EU_CAPTURED_TOUCH_H

#include "nitro/types.h"

/* Task-owned DS record. invalid == 0 is accepted by the capture scan;
 * the remaining values and the meaning of individual bits are not inferred.
 */
typedef struct CapturedTouchRecord {
    u16 x;
    u16 y;
    u16 touch;
    u16 invalid;
} CapturedTouchRecord;

typedef int (*CapturedTouchStep)(void);

typedef struct CapturedTouchTaskDescriptor {
    u16 classId;
    u16 subId;
    CapturedTouchStep (*initialize)(void *userData);
    void (*shutdown)(void);
    u32 workSize;
    void ***heapReference;
} CapturedTouchTaskDescriptor;

typedef char CapturedTouchRecordSizeCheck[sizeof(CapturedTouchRecord) == 8 ? 1 : -1];
typedef char CapturedTouchDescriptorSizeCheck[sizeof(CapturedTouchTaskDescriptor) == 20 ? 1 : -1];

extern CapturedTouchRecord *gCapturedTouchRecord;
extern CapturedTouchTaskDescriptor gCapturedTouchTaskDescriptor;

CapturedTouchStep InitCapturedTouchTask(void *userData);
int UpdateCapturedTouchTask(void);
void ShutdownCapturedTouchTask(void);
void CaptureLatestOnScreenTouch(void);
void ClearCapturedTouchState(void);

#endif
