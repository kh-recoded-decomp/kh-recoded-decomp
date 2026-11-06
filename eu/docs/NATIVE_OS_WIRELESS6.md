# OS launcher thread, arena heap records and WM command buffers (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

## Separate runtime owners

The initial launcher thread differs from the separately created idle thread. Arena heap entries are pointers to heap-info records. WM state borrows caller-provided work memory, while its free-command queue state, ten pointer slots and ten 256-byte command buffers have distinct global allocations. All native storage, types, cache transitions and error paths are preserved.

## Inventory and evidence

### `main:02056c3c` → `gOsLauncherThreadStorage`

Previous label `data_02056c3c`; existing ELF size **192 bytes**. Source: `eu/src/data/bss/Bss_main_02056c3c.c`.

192-byte native OSThread BSS object for the initial/current launcher thread.

OS_InitThread sets its priority 16, ID 0 and runnable state, publishes it as current and list head, initializes launcher-stack bounds/sentinels and join queue. It creates the separate OSi_IdleThread afterward.

Limits: This is not the idle-thread object. Preserve the full native 192 bytes and stack/current/list relationships; no host-thread model is introduced.

Pinned references:

- `eu/src/calls/OS_InitThread.c` → `src/arm9/library_nitro_os/OS_InitThread_0200274c.c`; reference line(s) 50, 75, 76, 77, 78, 79, 81, 82, 88, 89, 90, 92, 93, 95.
- `eu/src/data/bss/Bss_main_02056c3c.c`; reference line(s) 4.

### `main:02056dcc` → `gOsHeapInfoByArena`

Previous label `data_02056dcc`; existing ELF size **36 bytes**. Source: `eu/src/data/bss/Bss_main_02056dc4.c`.

36-byte BSS array of nine native OSHeapInfo pointers, indexed by OSArenaId.

OS_AllocFromHeap selects the entry for its arena ID, returns NULL if that entry is missing, and resolves negative heap handles through currentHeap before allocation. OS_FreeToHeap uses the same arena pointer and heap descriptor array.

Limits: The array stores references to heap-info records, not heap payloads or direct allocator handles. The native free path does not repeat the allocation path NULL guard; no bounds checks or layout changes are added.

Pinned references:

- `eu/libs/nitro/os/calls/OS_AllocFromHeap.c` → `src/arm9/nitro_os/func_020039a8.c`; reference line(s) 55, 56.
- `eu/libs/nitro/os/calls/OS_FreeToHeap.c` → `src/arm9/nitro_os/func_02003ab0.c`; reference line(s) 7, 13.
- `eu/src/data/bss/Bss_main_02056dc4.c`; reference line(s) 3.

### `main:020597fc` → `gWmState`

Previous label `data_020597fc`; existing ELF size **8 bytes**. Source: `eu/src/data/bss/Bss_main_020597fc.c`.

8-byte native WMiState BSS object: initialized u16 at 0, reserved halfword at 2 and WM9Buffer pointer at 4.

WMi_InitCore rejects reinitialization, validates supplied buffer/DMA/alignment/PXI readiness, initializes the borrowed WM buffer and command queue, installs WmReceiveFifo and finally sets initialized TRUE. Other WM helpers obtain state/channel/link information through this owner.

Limits: The supplied WM9Buffer is separate caller storage, not allocated within these eight bytes. Preserve reserved bits and the native error-code paths; this block does not infer a higher game session owner.

Pinned references:

- `eu/src/calls/GetSessionChannel.c` → `src/arm9/shared_engine/GetSessionChannel_02011394.c`; reference line(s) 6, 10.
- `eu/src/calls/GetSessionLinkState.c` → `src/arm9/shared_engine/GetSessionLinkState_020113b8.c`; reference line(s) 6, 10.
- `eu/src/calls/IsDeviceReady.c` → `src/arm9/shared_engine/IsDeviceReady_02011048.c`; reference line(s) 1, 4.
- `eu/src/calls/PollDeviceStatus.c` → `src/arm9/shared_engine/PollDeviceStatus_0201105c.c`; reference line(s) 3, 8, 9.
- `eu/src/calls/RegisterPxiPreSleepCallback.c` → `src/arm9/library_nitro_pxi/RegisterPxiPreSleepCallback_020113e0.c`; reference line(s) 17, 23, 24, 25.
- `eu/src/calls/SetCommandArg.c` → `src/arm9/shared_engine/SetCommandArg_02010f28.c`; reference line(s) 1, 4.
- `eu/src/calls/ShutdownWireless.c` → `src/arm9/shared_engine/ShutdownWireless_02010ee0.c`; reference line(s) 9, 24, 25.
- `eu/src/calls/WMi_CheckStateEx.c` → `src/arm9/library_nitro_wm/WMi_CheckStateEx_02011088.c`; reference line(s) 252, 253, 254.
- `eu/src/calls/WMi_GetSystemWork.c` → `src/arm9/shared_engine/func_0201103c.c`; reference line(s) 1, 4.
- `eu/src/calls/WMi_InitCore.c` → `src/arm9/library_nitro_wm/WMi_InitCore_02010d80.c`; reference line(s) 23, 56, 83, 84, 85, 86, 87, 89, 90, 91, 93, 94, 103.
- `eu/src/calls/WmInit.c` → `src/arm9/shared_engine/WmInit_02010d64.c`; reference line(s) 2, 9.
- `eu/src/calls/WmReceiveFifo.c` → `src/arm9/library_nitro_wm/WmReceiveFifo_020110d8.c`; reference line(s) 130, 131, 132.
- `eu/src/data/bss/Bss_main_020597fc.c`; reference line(s) 6.

### `main:02059814` → `gWmCommandFreeQueue`

Previous label `data_02059814`; existing ELF size **32 bytes**. Source: `eu/src/data/bss/Bss_main_020597fc.c`.

32-byte BSS native OSMessageQueue holding available command-buffer pointers.

WMi_InitCore calls OS_InitMessageQueue(thisQueue,queueSlots,10) and sends the ten command-buffer addresses into it. WmGetCommandBuffer4Arm7 receives a pointer without blocking and checks its accepted flag; send-command helpers return pointers to the queue on their demonstrated failure paths.

Limits: This object is queue state, not an array of eight messages. Preserve OS thread-queue internals and the separate forty-byte slot array.

Pinned references:

- `eu/src/calls/WMi_InitCore.c` → `src/arm9/library_nitro_wm/WMi_InitCore_02010d80.c`; reference line(s) 24, 96, 100.
- `eu/src/calls/WMi_SendCommand.c` → `src/arm9/library_nitro_wm/WMi_SendCommand_02010f80.c`; reference line(s) 269, 270.
- `eu/src/calls/WMi_SendCommandDirect.c` → `src/arm9/library_nitro_wm/WMi_SendCommandDirect_02010ff4.c`; reference line(s) 269, 270.
- `eu/src/calls/WmGetCommandBuffer4Arm7.c` → `src/arm9/library_nitro_wm/WmGetCommandBuffer4Arm7_02010f38.c`; reference line(s) 269, 270.
- `eu/src/data/bss/Bss_main_020597fc.c`; reference line(s) 4.

### `main:02059834` → `gWmCommandFreeQueueSlots`

Previous label `data_02059834`; existing ELF size **40 bytes**. Source: `eu/src/data/bss/Bss_main_020597fc.c`.

40-byte BSS array of ten native message/pointer slots backing the WM free-command queue.

WMi_InitCore supplies this address and count 10 to OS_InitMessageQueue, with data02059814 as the distinct queue state. It enqueues one pointer for each command buffer.

Limits: The forty bytes hold pointer slots, not ten command bodies or a forty-byte queue struct. Storage lifetime remains the native global lifetime.

Pinned references:

- `eu/src/calls/WMi_InitCore.c` → `src/arm9/library_nitro_wm/WMi_InitCore_02010d80.c`; reference line(s) 25, 96.
- `eu/src/data/bss/Bss_main_020597fc.c`; reference line(s) 3.

### `main:020598a0` → `gWmCommandBufferStorage`

Previous label `data_020598a0`; existing ELF size **2560 bytes**. Source: `eu/src/data/bss/Bss_main_0205989c.c`.

2560-byte BSS pool: ten 256-byte command buffers, each represented natively as 128 u16 words.

WMi_InitCore iterates ten buffers, writes accepted bit 0x8000 to each first halfword, stores that halfword to memory with DC_StoreRange and queues the buffer pointer. The free-queue client invalidates/tests that halfword before use.

Limits: Preserve complete 256-byte buffers and cache/FIFO ownership transitions. This naming block does not allocate, shrink, clear the remaining payload or define every WM command layout.

Pinned references:

- `eu/src/calls/WMi_InitCore.c` → `src/arm9/library_nitro_wm/WMi_InitCore_02010d80.c`; reference line(s) 26, 98, 99, 100.
- `eu/src/data/bss/Bss_main_0205989c.c`; reference line(s) 3.


## Byte-exact validation

98 DATA identities retain their source paths, native sizes and storage.
280/282 affected official function checks pass; the remaining
2 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 348 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
