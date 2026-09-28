void copyMovieChunkHeaderFields_020aaac8(int *chunkRecord, unsigned char *chunkData)
{
    chunkRecord[1] = (unsigned int)chunkData[0];
    chunkRecord[0] = (int)*(short *)(chunkData + 2);
}
