extern volatile unsigned int data_02057c10;

asm void RtcWaitBusy_0200e8cc(void)
{
    ldr       r12, =data_02057c10
@loop:
    ldr       r0, [r12]
    cmp       r0, #1
    beq       @loop
    bx        lr
}
