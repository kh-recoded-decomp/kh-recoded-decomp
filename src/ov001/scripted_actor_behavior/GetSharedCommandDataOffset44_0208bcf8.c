/* Returns the shared command-data pointer stored at 0x020a04f4, advanced by
 * 0x44 bytes. Its record meaning and game-facing role remain unknown. */
typedef unsigned char u8;
extern u8 *data_ov001_020a04f4;

void *GetSharedCommandDataOffset44_0208bcf8(void)
{
    return data_ov001_020a04f4 + 0x44;
}
