/* Behavior: Prepares a local video header copy and passes it to a stream-opening helper.
 * Inputs/outputs and evidence: Calls a header conversion helper into an eight-halfword local array, then forwards it with the context and other arguments.
 * Uncertainty: Video stream interpretation comes from nearby media functions; helper internals are not included.
 * Source: khdays-decomp/src/overlays/ov024/calls/func_ov024_02083590.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
extern void func_020a8934(int streamContext, unsigned short *dst, unsigned short *sourceHeader);
extern void func_02001494(unsigned int *streamContext, int streamOption, unsigned int streamFlags, unsigned short *preparedHeader);

void openVideoStreamFromHeader_020a8a04(unsigned int *streamContext, int streamOption, unsigned int streamFlags, unsigned short *sourceHeader) {
    unsigned short preparedHeader[8];
    func_020a8934((int)streamContext, preparedHeader, sourceHeader);
    func_02001494(streamContext, streamOption, streamFlags, preparedHeader);
}
