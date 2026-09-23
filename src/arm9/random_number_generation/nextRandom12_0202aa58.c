/* Behavior: Advances the global 64-bit linear congruential generator and returns twelve high bits.
 * Inputs/outputs and evidence: Updates seed = seed times multiplier plus increment, then returns the new seed's top twelve bits.
 * Uncertainty: The state fields are structurally clear; callers' random-number use is unknown.
 * Source: khdays-decomp/src/auto/func_02023f08.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
typedef struct {
    char pad0[0xc];
    unsigned long long seed;
    unsigned long long multiplier;
    unsigned long long increment;
} RandomGeneratorState;

extern RandomGeneratorState data_020604d8;

int nextRandom12_0202aa58(void)
{
    RandomGeneratorState *state = &data_020604d8;
    unsigned int newSeedHighWord;

    state->seed = state->multiplier * state->seed + state->increment;
    newSeedHighWord = (unsigned int)(state->seed >> 32);
    return (int)(((unsigned long long)newSeedHighWord << 12) >> 32);
}
