/* Copies two observed chunk-header values into the current movie record.
 * Evidence: Ghidra shows one unsigned input byte stored at record +4 and one signed halfword at input +2 stored at record +0.
 * Uncertainty: The header fields' meanings and the specific chunk type that uses them are unknown.
 * Source: Reconstructed from build/ghidra/decompiled/ov022_func_ov022_020aaac8.c; no upstream body copied.
 */
void copyMovieChunkHeaderFields_020aaac8(int *chunkRecord, unsigned char *chunkData)
{
    chunkRecord[1] = (unsigned int)chunkData[0];
    chunkRecord[0] = (int)*(short *)(chunkData + 2);
}
