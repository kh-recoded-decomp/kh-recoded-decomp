#ifndef EU_ACTOR_BOX_DISPLAY_LIST_H
#define EU_ACTOR_BOX_DISPLAY_LIST_H

#include "nitro/types.h"

typedef struct BoxDrawCommandGroup {
    u32 commands;
    u32 parameters[5];
} BoxDrawCommandGroup;

typedef struct BoxDrawCommands {
    BoxDrawCommandGroup groups[6];
    u32 finalCommands;
    u32 finalPositions[2];
    u32 nop;
} BoxDrawCommands;

typedef struct ActorBoxDisplayList {
    u32 textureAndPolygonCommands;
    u32 textureParameters;
    u32 firstPolygonAttributes;
    BoxDrawCommands firstBox;
    u32 polygonCommand;
    u32 secondPolygonAttributes;
    BoxDrawCommands secondBox;
} ActorBoxDisplayList;

extern ActorBoxDisplayList gActorBoxDisplayList;

#endif
