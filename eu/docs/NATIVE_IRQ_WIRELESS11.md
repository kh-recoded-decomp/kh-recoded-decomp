# IRQ callback and wireless notification DATA (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

## Logical spans

The IRQ callback table has eight twelve-byte records: four DMA slots followed by four timer slots. Its 96 bytes are split natively into 4+4+40+4+4+40 bytes. The record order is function, keep-enabled word, argument pointer. DMA keep-enabled values may be raw interrupt masks; timer registration uses 1. The dispatcher clears the handler before invoking it and then tests keep-enabled.

The WM connection notification view is 68 bytes split 20+16+28+4. WmReceiveFifo builds one temporary event and reuses it while iterating the registered port callbacks. This buffer is distinct from actual incoming receive/FIFO buffers. The native TGID state needs a full word because 0x10000 is its initial sentinel.

## Inventory and evidence

### `main:02056ae8` → `gDmaIrqCallback0Function`

Previous label `data_02056ae8`; size **4 bytes**; source `eu/src/data/bss/Bss_main_02056ae8.c`.

4 BSS bytes: function word of DMA IRQ callback slot 0. The logical eight-slot callback table spans 96 bytes from 02056ae8 to 02056b48.

OSi_EnterDmaCallback writes handler, keep-enabled mask and argument at twelve-byte stride. OS_SetIrqFunction maps DMA interrupt bits 8..11 to slots 0..3; OS_GetIrqFunction reads the same handlers. OSi_IrqCallback clears the selected function before invoking it with the stored argument.

Limits: This object is only the first function word. The typed OSiIrqSlot array view reaches subsequent native fragments, including timer slots 4..7; preserve all existing boundaries.

Pinned references:

- `eu/libs/nitro/os/calls/OS_GetIrqFunction.c` → `src/arm9/library_nitro_os/OS_GetIrqFunction_02001e18.c`; line(s) 4, 17, 20.
- `eu/libs/nitro/os/calls/OS_SetIrqFunction.c` → `src/arm9/library_nitro_os/OS_SetIrqFunction_02001d90.c`; line(s) 4, 18, 20.
- `eu/libs/nitro/os/calls/OSi_EnterDmaCallback.c` → `src/arm9/library_nitro_os/OSi_EnterDmaCallback_02001ea4.c`; line(s) 11, 20, 21, 22.
- `eu/libs/nitro/os/calls/OSi_EnterTimerCallback.c` → `src/arm9/library_nitro_os/OSi_EnterTimerCallback_02001eec.c`; line(s) 11, 15.
- `eu/libs/nitro/os/calls/OSi_IrqCallback.c` → `src/arm9/library_nitro_os/OSi_IrqCallback_02001c70.c`; line(s) 13, 25, 27, 29, 34.
- `eu/src/data/bss/Bss_main_02056ae8.c`; line(s) 3.
- `eu/libs/nitro/os/calls/OS_GetIrqFunction.c` → `src/arm9/library_nitro_os/OS_GetIrqFunction_02001e18.c`; line(s) 4, 17, 20.
- `eu/libs/nitro/os/calls/OS_SetIrqFunction.c` → `src/arm9/library_nitro_os/OS_SetIrqFunction_02001d90.c`; line(s) 4, 18, 20.
- `eu/libs/nitro/os/calls/OSi_EnterDmaCallback.c` → `src/arm9/library_nitro_os/OSi_EnterDmaCallback_02001ea4.c`; line(s) 11, 20, 21, 22.
- `eu/libs/nitro/os/calls/OSi_EnterTimerCallback.c` → `src/arm9/library_nitro_os/OSi_EnterTimerCallback_02001eec.c`; line(s) 11, 15.
- `eu/libs/nitro/os/calls/OSi_IrqCallback.c` → `src/arm9/library_nitro_os/OSi_IrqCallback_02001c70.c`; line(s) 13, 25, 27, 29, 34.
- `eu/src/data/bss/Bss_main_02056ae8.c`; line(s) 3.

### `main:02056aec` → `gDmaIrqCallback0KeepEnabled`

Previous label `data_02056aec`; size **4 bytes**; source `eu/src/data/bss/Bss_main_02056aec.c`.

4 BSS bytes at callback table +4: the first DMA slot keep-enabled word.

The OSiIrqSlot view in OSi_EnterDmaCallback and OSi_IrqCallback places bKeepEnabled at offset 4. Registration stores the previous OS_EnableIrqMask(mask) & mask; callback dispatch disables that interrupt when the stored word is zero.

Limits: The DMA writer may store a raw mask rather than normalized BOOL. Do not narrow this native word or substitute a single common interpretation for all writers.

Pinned references:

- `eu/src/data/bss/Bss_main_02056aec.c`; line(s) 4.
- `eu/libs/nitro/os/calls/OS_GetIrqFunction.c` → `src/arm9/library_nitro_os/OS_GetIrqFunction_02001e18.c`; line(s) 4, 17, 20.
- `eu/libs/nitro/os/calls/OS_SetIrqFunction.c` → `src/arm9/library_nitro_os/OS_SetIrqFunction_02001d90.c`; line(s) 4, 18, 20.
- `eu/libs/nitro/os/calls/OSi_EnterDmaCallback.c` → `src/arm9/library_nitro_os/OSi_EnterDmaCallback_02001ea4.c`; line(s) 11, 20, 21, 22.
- `eu/libs/nitro/os/calls/OSi_EnterTimerCallback.c` → `src/arm9/library_nitro_os/OSi_EnterTimerCallback_02001eec.c`; line(s) 11, 15.
- `eu/libs/nitro/os/calls/OSi_IrqCallback.c` → `src/arm9/library_nitro_os/OSi_IrqCallback_02001c70.c`; line(s) 13, 25, 27, 29, 34.
- `eu/src/data/bss/Bss_main_02056ae8.c`; line(s) 3.

### `main:02056af0` → `gDmaIrqCallbackTableTail`

Previous label `data_02056af0`; size **40 bytes**; source `eu/src/data/bss/Bss_main_02056aec.c`.

40 BSS bytes: DMA slot 0 argument pointer, followed by all three twelve-byte DMA slots 1..3.

The 4+4+40-byte fragments form four OSiIrqSlot records. OSi_EnterDmaCallback writes each argument at slot+8 and OSi_IrqCallback passes that word to the selected handler.

Limits: This fragment is neither ten independent pointers nor a new allocation per slot. Preserve the first partial record and the native twelve-byte record stride.

Pinned references:

- `eu/src/data/bss/Bss_main_02056aec.c`; line(s) 3.
- `eu/libs/nitro/os/calls/OS_GetIrqFunction.c` → `src/arm9/library_nitro_os/OS_GetIrqFunction_02001e18.c`; line(s) 4, 17, 20.
- `eu/libs/nitro/os/calls/OS_SetIrqFunction.c` → `src/arm9/library_nitro_os/OS_SetIrqFunction_02001d90.c`; line(s) 4, 18, 20.
- `eu/libs/nitro/os/calls/OSi_EnterDmaCallback.c` → `src/arm9/library_nitro_os/OSi_EnterDmaCallback_02001ea4.c`; line(s) 11, 20, 21, 22.
- `eu/libs/nitro/os/calls/OSi_EnterTimerCallback.c` → `src/arm9/library_nitro_os/OSi_EnterTimerCallback_02001eec.c`; line(s) 11, 15.
- `eu/libs/nitro/os/calls/OSi_IrqCallback.c` → `src/arm9/library_nitro_os/OSi_IrqCallback_02001c70.c`; line(s) 13, 25, 27, 29, 34.
- `eu/src/data/bss/Bss_main_02056ae8.c`; line(s) 3.

### `main:02056b18` → `gTimerIrqCallback0Function`

Previous label `data_02056b18`; size **4 bytes**; source `eu/src/data/bss/Bss_main_02056b18.c`.

4 BSS bytes: timer callback slot 0 function, at global callback slot 4.

OSi_EnterTimerCallback uses &data_02056ae8[4] and writes function/argument/keepEnabled at twelve-byte stride. OS_SetIrqFunction maps timer interrupt bits 3..6 to global slots 4..7. Callback dispatch clears the selected function before invoking it.

Limits: The timer subtable shares the same full callback-table view. Its first function remains a separate four-byte native allocation.

Pinned references:

- `eu/src/data/bss/Bss_main_02056b18.c`; line(s) 3.
- `eu/libs/nitro/os/calls/OS_GetIrqFunction.c` → `src/arm9/library_nitro_os/OS_GetIrqFunction_02001e18.c`; line(s) 4, 17, 20.
- `eu/libs/nitro/os/calls/OS_SetIrqFunction.c` → `src/arm9/library_nitro_os/OS_SetIrqFunction_02001d90.c`; line(s) 4, 18, 20.
- `eu/libs/nitro/os/calls/OSi_EnterDmaCallback.c` → `src/arm9/library_nitro_os/OSi_EnterDmaCallback_02001ea4.c`; line(s) 11, 20, 21, 22.
- `eu/libs/nitro/os/calls/OSi_EnterTimerCallback.c` → `src/arm9/library_nitro_os/OSi_EnterTimerCallback_02001eec.c`; line(s) 11, 15.
- `eu/libs/nitro/os/calls/OSi_IrqCallback.c` → `src/arm9/library_nitro_os/OSi_IrqCallback_02001c70.c`; line(s) 13, 25, 27, 29, 34.
- `eu/src/data/bss/Bss_main_02056ae8.c`; line(s) 3.

### `main:02056b1c` → `gTimerIrqCallback0KeepEnabled`

Previous label `data_02056b1c`; size **4 bytes**; source `eu/src/data/bss/Bss_main_02056b1c.c`.

4 BSS bytes: timer slot 0 keep-enabled word.

OSi_EnterTimerCallback enables the requested timer interrupt and stores 1 into this field of the selected slot. OSi_IrqCallback tests the word when deciding whether to disable the interrupt after dispatch.

Limits: Preserve word width and the generic setter semantics; the DMA side of this table has a raw-mask writer.

Pinned references:

- `eu/src/data/bss/Bss_main_02056b1c.c`; line(s) 4.
- `eu/libs/nitro/os/calls/OS_GetIrqFunction.c` → `src/arm9/library_nitro_os/OS_GetIrqFunction_02001e18.c`; line(s) 4, 17, 20.
- `eu/libs/nitro/os/calls/OS_SetIrqFunction.c` → `src/arm9/library_nitro_os/OS_SetIrqFunction_02001d90.c`; line(s) 4, 18, 20.
- `eu/libs/nitro/os/calls/OSi_EnterDmaCallback.c` → `src/arm9/library_nitro_os/OSi_EnterDmaCallback_02001ea4.c`; line(s) 11, 20, 21, 22.
- `eu/libs/nitro/os/calls/OSi_EnterTimerCallback.c` → `src/arm9/library_nitro_os/OSi_EnterTimerCallback_02001eec.c`; line(s) 11, 15.
- `eu/libs/nitro/os/calls/OSi_IrqCallback.c` → `src/arm9/library_nitro_os/OSi_IrqCallback_02001c70.c`; line(s) 13, 25, 27, 29, 34.
- `eu/src/data/bss/Bss_main_02056ae8.c`; line(s) 3.

### `main:02056b20` → `gTimerIrqCallbackTableTail`

Previous label `data_02056b20`; size **40 bytes**; source `eu/src/data/bss/Bss_main_02056b1c.c`.

40 BSS bytes: timer slot 0 argument pointer followed by complete timer slots 1..3.

The 4+4+40-byte timer fragments are the second four records of the 96-byte table. Indexed timer registration and generic IRQ callback dispatch access this continuation through the base array view.

Limits: Keep the native split and opaque pointer values; this review changes no callback prototypes, bounds or interrupt sequencing.

Pinned references:

- `eu/src/data/bss/Bss_main_02056b1c.c`; line(s) 3.
- `eu/libs/nitro/os/calls/OS_GetIrqFunction.c` → `src/arm9/library_nitro_os/OS_GetIrqFunction_02001e18.c`; line(s) 4, 17, 20.
- `eu/libs/nitro/os/calls/OS_SetIrqFunction.c` → `src/arm9/library_nitro_os/OS_SetIrqFunction_02001d90.c`; line(s) 4, 18, 20.
- `eu/libs/nitro/os/calls/OSi_EnterDmaCallback.c` → `src/arm9/library_nitro_os/OSi_EnterDmaCallback_02001ea4.c`; line(s) 11, 20, 21, 22.
- `eu/libs/nitro/os/calls/OSi_EnterTimerCallback.c` → `src/arm9/library_nitro_os/OSi_EnterTimerCallback_02001eec.c`; line(s) 11, 15.
- `eu/libs/nitro/os/calls/OSi_IrqCallback.c` → `src/arm9/library_nitro_os/OSi_IrqCallback_02001c70.c`; line(s) 13, 25, 27, 29, 34.
- `eu/src/data/bss/Bss_main_02056ae8.c`; line(s) 3.

### `main:02055c48` → `gWmTgidCounter`

Previous label `data_02055c48`; size **4 bytes**; source `eu/libs/nitro/spi/data/pm_power_data.c`.

4 initialized DATA bytes, initially 0x00010000 as the not-yet-seeded sentinel.

WM_GetNextTgid checks the sentinel, initializes RTC, and on successful RTC_GetTime sets the word to (u16)(second + (minute << 8)). It then stores (u16)(word + 1) and returns that halfword.

Limits: The first returned value is incremented after seeding. RTC failure still leads to the narrowed increment; the word must retain the initial 17-bit sentinel rather than being shrunk to u16.

Pinned references:

- `eu/libs/nitro/spi/data/pm_power_data.c`; line(s) 9.
- `eu/src/calls/WM_GetNextTgid.c` → `src/arm9/library_nitro_wm/WM_GetNextTgid_02011658.c`; line(s) 198, 203.

### `main:0205985c` → `gWmConnectionPortEventPrefix`

Previous label `data_0205985c`; size **20 bytes**; source `eu/src/data/bss/Bss_main_0205985c.c`.

20 BSS bytes: the prefix through aid of a 68-byte WMPortRecvCallback-compatible synthesized event.

For connected/disconnected/disconnected-from-self state changes, WmReceiveFifo clears the full 68-byte view, sets apiid=130 and errcode=0, assigns state/aid and NULL data/receive pointers, then sends the same event to each registered port callback.

Limits: This is shared temporary callback storage, not the incoming FIFO buffer. The entire logical event spans the following 16+28+4-byte native allocations; preserve all four fragments.

Pinned references:

- `eu/src/calls/WmReceiveFifo.c` → `src/arm9/library_nitro_wm/WmReceiveFifo_020110d8.c`; line(s) 134, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 279, 281, 283, 284, 287, 289, 290.
- `eu/src/data/bss/Bss_main_0205985c.c`; line(s) 3.
- `eu/src/calls/WmReceiveFifo.c` → `src/arm9/library_nitro_wm/WmReceiveFifo_020110d8.c`; line(s) 134, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 279, 281, 283, 284, 287, 289, 290.
- `eu/src/data/bss/Bss_main_0205985c.c`; line(s) 3.

### `main:02059870` → `gWmConnectionPortEventPeerState`

Previous label `data_02059870`; size **16 bytes**; source `eu/src/data/bss/Bss_main_02059870.c`.

16 BSS bytes at event +20: MAC address[6], sequence halfword, callback argument pointer, own aid and connected-aid bitmap.

WmReceiveFifo copies six MAC bytes, sets seqNo=0xffff, stores myAid/connectedAidBitmap, and replaces arg for each port using that port's callback argument before dispatch.

Limits: Every port callback receives a borrowed pointer to the same event. A callback needing persistence must copy the relevant event; this review introduces no ownership transfer or per-port allocation.

Pinned references:

- `eu/src/data/bss/Bss_main_02059870.c`; line(s) 4.
- `eu/src/calls/WmReceiveFifo.c` → `src/arm9/library_nitro_wm/WmReceiveFifo_020110d8.c`; line(s) 134, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 279, 281, 283, 284, 287, 289, 290.
- `eu/src/data/bss/Bss_main_0205985c.c`; line(s) 3.

### `main:02059880` → `gWmConnectionPortEventSsidAndReason`

Previous label `data_02059880`; size **28 bytes**; source `eu/src/data/bss/Bss_main_02059870.c`.

28 BSS bytes at event +36: 24 SSID bytes, reason halfword and reserved halfword.

WmReceiveFifo copies 24 SSID bytes for parent-side notifications or clears them when no SSID pointer is available, then stores the notification reason. The initial full-view clear also initializes the reserved halfword.

Limits: SSID is fixed byte storage; no NUL termination or text encoding is established by this path. Preserve all 28 bytes, including the reserved word.

Pinned references:

- `eu/src/data/bss/Bss_main_02059870.c`; line(s) 3.
- `eu/src/calls/WmReceiveFifo.c` → `src/arm9/library_nitro_wm/WmReceiveFifo_020110d8.c`; line(s) 134, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 279, 281, 283, 284, 287, 289, 290.
- `eu/src/data/bss/Bss_main_0205985c.c`; line(s) 3.

### `main:0205989c` → `gWmConnectionPortEventTransferLimits`

Previous label `data_0205989c`; size **4 bytes**; source `eu/src/data/bss/Bss_main_0205989c.c`.

4 BSS bytes at event +64: maxSendDataSize and maxRecvDataSize halfwords.

WmReceiveFifo assigns parentSize/childSize in opposite order depending on whether myAid is zero, then exposes them through the port event callback.

Limits: These are the reported data-size fields, not allocated buffer sizes. Keep their exact halfword widths and parent/child selection.

Pinned references:

- `eu/src/data/bss/Bss_main_0205989c.c`; line(s) 4.
- `eu/src/calls/WmReceiveFifo.c` → `src/arm9/library_nitro_wm/WmReceiveFifo_020110d8.c`; line(s) 134, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 279, 281, 283, 284, 287, 289, 290.
- `eu/src/data/bss/Bss_main_0205985c.c`; line(s) 3.

For fragments without a direct C symbol token, the base-array/base-struct writers and consumers above prove their role by offset. Lack of a direct token is not a lack of ROM references or proof that a fragment is unused.


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
