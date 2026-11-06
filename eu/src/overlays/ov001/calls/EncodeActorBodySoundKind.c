#include "nitro/types.h"

int EncodeActorBodySoundKind(int value)
{
    switch (value) {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 5;
    }
    return value + 4;
}
