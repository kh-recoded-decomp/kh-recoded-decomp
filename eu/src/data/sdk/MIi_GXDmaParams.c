#include "libs/nitro/mi/mi_dma_internal.h"

typedef char GXDmaParamsMustBe32Bytes[sizeof(MIiGXDmaParams) == 32 ? 1 : -1];

/* Shared state for the asynchronous geometry-FIFO DMA transfer. */
MIiGXDmaParams MIi_GXDmaParams;
