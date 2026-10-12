#include "nitro/types.h"

typedef struct OverlayObjectSystemClass {
    u32 typeAndFlags;
    u32 (*initialize)(void);
    void (*shutdown)(void);
    u32 workSize;
    void *reserved;
} OverlayObjectSystemClass;

extern u32 InitOverlayObjectSystem(void);
extern void ShutdownOverlayObjectSystem(void);

/* Object-system lifecycle and the size of its manager-owned work area. */
OverlayObjectSystemClass gOverlayObjectSystemClass = {
    0x000d0010,
    InitOverlayObjectSystem,
    ShutdownOverlayObjectSystem,
    0x3f20,
    NULL
};
