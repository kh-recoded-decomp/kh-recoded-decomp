#include "nitro/types.h"
#include "nitro/os.h"

typedef int PXIFifoTag;
typedef enum {
    PXI_FIFO_SUCCESS = 0,
    PXI_FIFO_FAIL_SEND_ERR = -1,
    PXI_FIFO_FAIL_SEND_FULL = -2,
    PXI_FIFO_FAIL_RECV_ERR = -3,
    PXI_FIFO_FAIL_RECV_EMPTY = -4,
    PXI_FIFO_NO_CALLBACK_ENTRY = -5
} PXIFifoStatus;
#define PXI_FIFOMESSAGE_BITSZ_TAG   5
#define PXI_FIFOMESSAGE_BITSZ_ERR   1
#define PXI_FIFOMESSAGE_BITSZ_DATA  26
typedef union {
    struct {
        u32 tag : PXI_FIFOMESSAGE_BITSZ_TAG;
        u32 err : PXI_FIFOMESSAGE_BITSZ_ERR;
        u32 data : PXI_FIFOMESSAGE_BITSZ_DATA;
    } e;
    u32 raw;
} PXIFifoMessage;
typedef void (*PXIFifoCallback)(PXIFifoTag tag, u32 data, BOOL err);

#define reg_PXI_FIFO_CNT   (*(vu16 *)0x04000184)
#define reg_PXI_SEND_FIFO  (*(vu32 *)0x04000188)
#define reg_PXI_RECV_FIFO  (*(vu32 *)0x04100000)

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern PXIFifoCallback data_02057b8c[32];
#define FifoRecvCallbackTable data_02057b8c

static inline PXIFifoStatus PXIi_SetToFifo(u32 data)
{
    OSIntrMode enabled;

    if (reg_PXI_FIFO_CNT & REG_PXI_FIFO_CNT_ERR_MASK) {
        reg_PXI_FIFO_CNT |= (REG_PXI_FIFO_CNT_E_MASK | REG_PXI_FIFO_CNT_ERR_MASK);
        return PXI_FIFO_FAIL_SEND_ERR;
    }

    enabled = OS_DisableInterrupts();
    if (reg_PXI_FIFO_CNT & REG_PXI_FIFO_CNT_SEND_FULL_MASK) {
        (void)OS_RestoreInterrupts(enabled);
        return PXI_FIFO_FAIL_SEND_FULL;
    }

    reg_PXI_SEND_FIFO = data;
    (void)OS_RestoreInterrupts(enabled);
    return PXI_FIFO_SUCCESS;
}

static inline PXIFifoStatus PXIi_GetFromFifo(u32 *data_buf)
{
    OSIntrMode enabled;

    if (reg_PXI_FIFO_CNT & REG_PXI_FIFO_CNT_ERR_MASK) {
        reg_PXI_FIFO_CNT |= (REG_PXI_FIFO_CNT_E_MASK | REG_PXI_FIFO_CNT_ERR_MASK);
        return PXI_FIFO_FAIL_RECV_ERR;
    }

    enabled = OS_DisableInterrupts();
    if (reg_PXI_FIFO_CNT & REG_PXI_FIFO_CNT_RECV_EMP_MASK) {
        (void)OS_RestoreInterrupts(enabled);
        return PXI_FIFO_FAIL_RECV_EMPTY;
    }

    *data_buf = reg_PXI_RECV_FIFO;
    (void)OS_RestoreInterrupts(enabled);

    return PXI_FIFO_SUCCESS;
}

void PXIi_HandlerRecvFifoNotEmpty_0200e374(void)
{
    PXIFifoMessage fifomsg;
    PXIFifoStatus ret_code;
    PXIFifoTag tag;

    while (1) {
        ret_code = PXIi_GetFromFifo(&fifomsg.raw);

        if (ret_code == PXI_FIFO_FAIL_RECV_EMPTY)
            break;

        if (ret_code == PXI_FIFO_FAIL_RECV_ERR)
            continue;

        tag = (PXIFifoTag)fifomsg.e.tag;

        if (tag) {
            if (FifoRecvCallbackTable[tag]) {
                (FifoRecvCallbackTable[tag])(tag, fifomsg.e.data, (BOOL)fifomsg.e.err);
            } else {
                if (fifomsg.e.err) {
                } else {
                    fifomsg.e.err = TRUE;
                    (void)PXIi_SetToFifo(fifomsg.raw);
                }
            }
        } else {

        }
    }
}
