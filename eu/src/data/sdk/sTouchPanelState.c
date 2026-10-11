#include "libs/nitro/spi/tp_state_internal.h"

typedef char TouchPanelStateMustBe60Bytes[
    sizeof(TPiTouchPanelState) == 60 ? 1 : -1];
typedef char TouchCalibrationMustStartAt28Bytes[
    (u32)&((TPiTouchPanelState *)0)->calibration == 28 ? 1 : -1];

/* TP_Init, the sampling requests and calibration helpers share this state.
 * sTouchPanelCalibration is the existing view of calibration at +0x1c. */
TPiTouchPanelState sTouchPanelState;
