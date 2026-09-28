#include "nitro/types.h"

extern void movie_video_hardware_setup_020a7b3c(void);
extern void SetupSubScreenForMovie_020a7c58(void);

void SetupMovieScreenHardware_020a831c(int useMainScreen)
{
    if (useMainScreen != 0) {
        movie_video_hardware_setup_020a7b3c();
        return;
    }
    SetupSubScreenForMovie_020a7c58();
}
