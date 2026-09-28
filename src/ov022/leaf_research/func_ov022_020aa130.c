/* Independent reconstruction of a straight-line leaf from BK9E instructions.
 * Higher-level field and return meanings remain unclassified. */
typedef unsigned int u32;
u32 BindMovieReaderToFileContext_020aa130(u32 reader, u32 fileContext) {
    *(u32 *)((reader + 0xcU)) = fileContext;
    u32 value1 = *(const u32 *)((fileContext + 0x28U));
    u32 value2 = *(const u32 *)((fileContext + 0x24U));
    u32 value3 = 0x0U;
    u32 value4 = (value1) - (value2);
    *(u32 *)((reader + 0x4U)) = value4;
    u32 value6 = *(const u32 *)((reader + 0xcU));
    u32 value7 = *(const u32 *)((value6 + 0x2cU));
    u32 value8 = *(const u32 *)((value6 + 0x24U));
    u32 value9 = (value7) - (value8);
    *(u32 *)((reader + 0x8U)) = value9;
    *(unsigned char *)((reader + 0x10U)) = value3;
    u32 value12 = 0x1U;
    return value12;
}
