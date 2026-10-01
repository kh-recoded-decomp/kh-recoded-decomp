extern int subtitleContexts_020b7d88[];
#define activeStream_020b7d90 subtitleContexts_020b7d88[2]

void ActivateSubtitleStream_020a88f0(void)

{
  if (activeStream_020b7d90 != 0) {
    if (*(unsigned char *)(activeStream_020b7d90 + 0x38) == '\0') {
      *(unsigned char *)(activeStream_020b7d90 + 0x38) = 1;
    }
    return;
  }
  return;
}
