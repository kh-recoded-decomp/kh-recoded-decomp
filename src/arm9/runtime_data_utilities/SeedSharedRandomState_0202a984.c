extern int shared_rng_state[];

void SeedSharedRandomState_0202a984(int seed_word_0, int seed_word_1, int seed_word_2) {
    shared_rng_state[3] = seed_word_1;
    shared_rng_state[4] = seed_word_2;
    shared_rng_state[5] = 0x6c078965;
    shared_rng_state[6] = 0x5d588b65;
    shared_rng_state[7] = 0x269ec3;
    shared_rng_state[8] = 0;
    shared_rng_state[0] = seed_word_0;
    shared_rng_state[1] = 0x5d588b65;
    shared_rng_state[2] = 0x269ec3;
}
