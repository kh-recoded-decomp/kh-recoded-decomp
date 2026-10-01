extern unsigned int *resourceContexts_020c0068[];
#define puRam020c006c resourceContexts_020c0068[1]
extern unsigned int func_0202a1c4();

void ReleaseGroupResourceBuffers_020bbb24(void)

{
  unsigned int *buffers;
  
  buffers = puRam020c006c;
  func_0202a1c4(*puRam020c006c);
  func_0202a1c4(buffers[1]);
  func_0202a1c4(buffers[2]);
  func_0202a1c4(buffers[3]);
  puRam020c006c = (unsigned int *)0x0;
  return;
}
