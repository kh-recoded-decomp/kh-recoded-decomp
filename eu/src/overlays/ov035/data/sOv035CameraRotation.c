#include "nitro/fx_types.h"

typedef struct MovieCameraRotation {
    fx32 m[3][3];
} MovieCameraRotation;

const MovieCameraRotation sOv035CameraRotation = {
    {
        { FX32_ONE, 0, 0 },
        { 0, FX32_ONE, 0 },
        { 0, 0, FX32_ONE },
    },
};
