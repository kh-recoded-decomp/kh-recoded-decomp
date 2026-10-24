#ifndef NITRO_OS_INTERRUPT_STATE_H
#define NITRO_OS_INTERRUPT_STATE_H

/* The original leaf routine leaves these three results in r0-r2. */
typedef struct OSInterruptState {
    unsigned previousMask;
    unsigned previousStatus;
    unsigned updatedStatus;
} OSInterruptState;

#if defined(__clang__)
#define OS_INTERRUPT_STATE_RESULT __attribute__((swiftcall))
#else
#define OS_INTERRUPT_STATE_RESULT __declspec(value_in_regs)
#endif

OS_INTERRUPT_STATE_RESULT OSInterruptState OS_RestoreInterrupts_IrqAndFiq(unsigned state);

#endif
