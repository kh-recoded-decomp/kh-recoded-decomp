#include "src/graphics/CameraState.h"

CameraStateCallback GetSavedCameraRestoreCallback(void)
{
    return RestoreSavedCamera;
}
