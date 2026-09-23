/* Advances the shared 64-bit linear congruential random state and returns its high word, optionally scaled to the requested range.
 * Evidence: LCG state fields and 64-bit arithmetic in source.
 * Uncertainty: The source claim that this is the game-wide generator is caller-supported in reference; target callers should confirm.
 * Source: src/calls/func_02023eb4.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */


typedef struct {
    char pad0[0xc];
    long long seed;
    long long mult;
    long long inc;
} RngState;

extern RngState data_020604d8;

unsigned int random_next_scaled_0202aa04(unsigned int upperBound)
{
    RngState *randomState = &data_020604d8;
    unsigned int randomValue;

    randomState->seed = randomState->mult * randomState->seed + randomState->inc;
    randomValue = (unsigned int)(randomState->seed >> 32);
    if (upperBound != 0)
        randomValue = (unsigned int)((unsigned long long)randomValue * upperBound >> 32);
    return randomValue;
}
