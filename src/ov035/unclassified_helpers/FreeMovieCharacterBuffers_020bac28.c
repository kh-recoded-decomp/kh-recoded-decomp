#include "nitro/types.h"

typedef struct CharacterValues {
    u8 pad_00[0x10];
    void *entries;
    u8 pad_14[0x10];
    void *names;
    void *icons;
    void *values;
} CharacterValues;

typedef struct MovieContext {
    u8 pad_00[0x40];
    CharacterValues characters;
} MovieContext;

extern MovieContext *g_movieContext_020bc4e0;
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void FreeMovieCharacterBuffers_020bac28(void)
{
    MovieContext *context = g_movieContext_020bc4e0;
    CharacterValues *characters = &context->characters;

    if (context->characters.entries != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(context->characters.entries);
        context->characters.entries = NULL;
    }
    if (characters->names != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(characters->names);
        characters->names = NULL;
    }
    if (characters->icons != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(characters->icons);
        characters->icons = NULL;
    }
    if (characters->values != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(characters->values);
        characters->values = NULL;
    }
}