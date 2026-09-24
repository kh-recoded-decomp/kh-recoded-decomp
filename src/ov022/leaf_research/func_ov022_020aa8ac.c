/* Movie decoder cache arena sizing helper.
 * BK9E reads this capacity while configuring the table-copy arena; its
 * getters consume 0x2580 bytes across the decode, saturation, and clamp tables.
 * This is a constant-size helper, not decoder implementation code.
 */
unsigned int GetMovieCacheTableArenaCapacity_020aa8ac(void) {
    return 0x2580;
}
