extern unsigned int *resourceContexts_020bc4e8[];
#define puRam020c006c resourceContexts_020bc4e8[1]
extern unsigned int func_0202a1c4();

void func_ov035_020bc0c4(void)

{
  unsigned int *buffers;

  buffers = puRam020c006c;
  func_0202a1c4(*puRam020c006c);
  func_0202a1c4(buffers[1]);
  func_0202a1c4(buffers[3]);
  func_0202a1c4(buffers[2]);
  puRam020c006c = (unsigned int *)0x0;
  return;
}
