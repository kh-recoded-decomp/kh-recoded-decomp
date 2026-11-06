#include "nitro/types.h"

extern u8 gMovieSkipPromptJapanese[];
extern u8 gMovieSkipPromptEnglish[];
extern u8 gMovieSkipPromptFrench[];
extern u8 gMovieSkipPromptGerman[];
extern u8 gMovieSkipPromptItalian[];
extern u8 gMovieSkipPromptSpanish[];

void *gMovieSkipPromptByLanguage[6] = {
    gMovieSkipPromptJapanese,
    gMovieSkipPromptEnglish,
    gMovieSkipPromptFrench,
    gMovieSkipPromptGerman,
    gMovieSkipPromptItalian,
    gMovieSkipPromptSpanish,
};
