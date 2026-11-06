# Runtime task, heap, input and profile DATA (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

## Cross-symbol views

The two engine heaps each have a separate handle and allocator record. The global heap references point to those records and require another dereference for the heap handle. Task class heads are a separate 64-pointer array. Touch sampling owns five raw records although readers return four recent samples. The cached owner-message symbol is not a 58-byte pure string: its tail overlaps the shared-profile filtering flag. Preserve all of these storage boundaries in the native build.

## Inventory and evidence

### `main:02060394` → `gEngineHeapReferences`

Previous label `data_02060394`; existing ELF size **8 bytes**. Source: `eu/src/data/bss/Bss_main_02060394.c`.

8-byte BSS object containing two native heap-record references: special heap record at +0, default heap record at +4.

InitEngineHeaps creates both heaps, initializes their allocator records and publishes these references. Default alloc/free wrappers dereference +4 to obtain the heap handle. Class descriptors can use the +0 reference for special-heap work.

Limits: These are references to records, not direct heap handles. Preserve the separate neighboring default/special handle and allocator symbols; the larger native base-relative views are not this object size.

Pinned references:

- `eu/libs/nitro/nns/calls/NNS_FndAllocFromDefaultExpHeapEx.c` → `src/arm9/shared_engine/NNSi_FndAllocFromDefaultHeapEx_0202a19c.c`; reference line(s) 3, 8.
- `eu/libs/nitro/nns/calls/NNSi_FndFreeFromDefaultHeap.c` → `src/arm9/shared_engine/NNSi_FndFreeFromDefaultHeap_0202a1c4.c`; reference line(s) 3, 8.
- `eu/libs/nitro/nns/calls/NNSi_FndGetAllocatorForDefaultHeap.c` → `src/arm9/shared_engine/NNSi_FndGetAllocatorForDefaultHeap_0202a268.c`; reference line(s) 3, 8.
- `eu/src/calls/AllocFromHeapOrDefaultEx.c` → `src/arm9/shared_engine/AllocFromHeapOrDefaultEx_0202a210.c`; reference line(s) 3, 9.
- `eu/src/calls/CreateTaskObject.c` → `src/arm9/shared_engine/func_0202a448.c`; reference line(s) 3, 9.
- `eu/src/calls/DestroyRegisteredObject.c` → `src/arm9/runtime_data_utilities/DestroyRegisteredObject_0202a5b4.c`; reference line(s) 6, 28.
- `eu/src/calls/Heap_GetCurrent.c` → `src/arm9/shared_engine/func_0202a158.c`; reference line(s) 1, 4.
- `eu/src/calls/InitEngineHeaps.c` → `src/arm9/shared_engine/InitEngineHeaps_0202a040.c`; reference line(s) 3, 16, 17, 19, 20, 21.
- `eu/src/calls/InitFileLoader.c` → `src/arm9/filesystem/InitFileLoader_0202c20c.c`; reference line(s) 24, 58, 60, 61, 63.
- `eu/src/calls/InitSaveSystem.c` → `src/arm9/shared_engine/InitSaveSystem_02026dc0.c`; reference line(s) 14, 59.
- `eu/src/calls/InitSoundSystem.c` → `src/arm9/audio/InitSoundSystem_0204d050.c`; reference line(s) 4, 18.
- `eu/src/calls/NNSi_FndAllocFromDefaultHeap.c` → `src/arm9/shared_engine/NNSi_FndAllocFromDefaultHeap_0202a178.c`; reference line(s) 3, 8.
- `eu/src/calls/NNSi_FndAllocFromExpHeapEx.c` → `src/arm9/shared_engine/NNSi_FndAllocFromExpHeapEx_0202a1e4.c`; reference line(s) 3, 9.
- `eu/src/calls/NNSi_FndFreeToExpHeap.c` → `src/arm9/shared_engine/NNSi_FndFreeToExpHeap_0202a240.c`; reference line(s) 3, 9.
- `eu/src/calls/Obj_CreateWithTailWork.c` → `src/arm9/shared_engine/Obj_CreateWithTailWork_0202a47c.c`; reference line(s) 3, 9.
- `eu/src/calls/SetDefaultHeap.c` → `src/arm9/shared_engine/SetDefaultHeap_0202a134.c`; reference line(s) 1, 4, 5.
- `eu/src/calls/SetResourceLanguage.c` → `src/arm9/core_small/func_0202b760.c`; reference line(s) 4, 9.
- `eu/src/calls/main.c`; reference line(s) 62, 105.
- `eu/src/data/bss/Bss_main_02060394.c`; reference line(s) 3.
- `eu/src/data/gSceneSystemClassDescriptor.c`; reference line(s) 16, 24.

### `main:0206039c` → `gSceneHeapReference`

Previous label `data_0206039c`; existing ELF size **4 bytes**. Source: `eu/src/data/bss/Bss_main_0206039c.c`.

4-byte BSS reference initialized to the default heap record.

InitEngineHeaps stores &data020603a0 through heapReferencesBase+8. AdvancePendingScene passes this reference to ResetSceneHeapRecord after old scene teardown; FreeResourceBufferAndProbeHeap dereferences it before the heap-space probe.

Limits: No evidence establishes it as a mutable current-thread heap selector. This name describes its scene-reset use without introducing a new heap allocation.

Pinned references:

- `eu/src/calls/AdvancePendingScene.c` → `src/arm9/scene_dispatch/AdvancePendingScene_02025570.c`; reference line(s) 17, 36.
- `eu/src/calls/FreeResourceBufferAndProbeHeap.c` → `src/arm9/shared_engine/FreeResourceBufferAndProbeHeap_02001474.c`; reference line(s) 8, 15.
- `eu/src/data/bss/Bss_main_0206039c.c`; reference line(s) 3.

### `main:020603a0` → `gDefaultEngineHeap`

Previous label `data_020603a0`; existing ELF size **4 bytes**. Source: `eu/src/data/bss/Bss_main_020603a0.c`.

4-byte BSS heap handle; the following allocator is a separate 16-byte symbol.

CreateEngineHeaps returns the second heap built from the remaining aligned arena. InitEngineHeaps stores it here through base+0xc, initializes the following allocator and publishes this record as the default reference.

Limits: The native local is misleadingly called defaultHeapSize; the writer and allocator consumer establish a heap handle. Do not copy that local label as a byte-count contract.

Pinned references:

- `eu/src/calls/InitEngineHeaps.c` → `src/arm9/shared_engine/InitEngineHeaps_0202a040.c`; reference line(s) 4, 20, 21.
- `eu/src/data/bss/Bss_main_020603a0.c`; reference line(s) 4.

### `main:020603a4` → `gDefaultEngineHeapAllocator`

Previous label `data_020603a4`; existing ELF size **16 bytes**. Source: `eu/src/data/bss/Bss_main_020603a0.c`.

16-byte BSS native allocator record immediately after the default heap handle.

InitEngineHeaps passes this address, the default heap handle and alignment 4 to NNS_FndInitAllocatorForExpHeap. NNSi_FndGetAllocatorForDefaultHeap returns heapRecord+4, which resolves to this allocator for the initialized default reference.

Limits: Keep the exact native allocator record and do not replace it with a host allocator or a smaller inferred struct in the matching build.

Pinned references:

- `eu/src/calls/InitEngineHeaps.c` → `src/arm9/shared_engine/InitEngineHeaps_0202a040.c`; reference line(s) 5, 19.
- `eu/src/data/bss/Bss_main_020603a0.c`; reference line(s) 3.

### `main:020603b4` → `gSpecialEngineHeap`

Previous label `data_020603b4`; existing ELF size **4 bytes**. Source: `eu/src/data/bss/Bss_main_020603b4.c`.

4-byte BSS heap handle; the following 16-byte allocator remains a separate symbol.

CreateEngineHeaps first allocates 0xc2800 arena bytes and creates the special expanded heap. InitEngineHeaps stores the returned handle here through base+0x20 and publishes &thisHandle in the first heap reference.

Limits: 0xc2800 is the arena reservation passed to heap creation, not a guarantee of usable payload capacity. Preserve handle/allocator boundary.

Pinned references:

- `eu/src/calls/InitEngineHeaps.c` → `src/arm9/shared_engine/InitEngineHeaps_0202a040.c`; reference line(s) 6, 17.
- `eu/src/data/bss/Bss_main_020603b4.c`; reference line(s) 4.

### `main:020603b8` → `gSpecialEngineHeapAllocator`

Previous label `data_020603b8`; existing ELF size **16 bytes**. Source: `eu/src/data/bss/Bss_main_020603b4.c`.

16-byte BSS native allocator record following the special heap handle.

InitEngineHeaps initializes this allocator with the special heap handle and alignment 4 before publishing the corresponding heap record.

Limits: The record is native SDK allocator state, not the special heap allocation itself. No field layout beyond the demonstrated initializer API is newly asserted.

Pinned references:

- `eu/src/calls/InitEngineHeaps.c` → `src/arm9/shared_engine/InitEngineHeaps_0202a040.c`; reference line(s) 7, 16.
- `eu/src/data/bss/Bss_main_020603b4.c`; reference line(s) 3.

### `main:020603d8` → `gTaskClassHeads`

Previous label `data_020603d8`; existing ELF size **256 bytes**. Source: `eu/src/data/bss/Bss_main_020603c8.c`.

256-byte BSS array of 64 native TaskObject pointers, indexed by classId.

ResetTaskManagerState clears exactly 0x100 bytes. Obj_LinkNode uses node->classId to find an existing class run, searches neighboring classes 0..63 to preserve linked order, and stores the first task for new classes. unlink_object_registry_node advances or clears a class head when that task is removed.

Limits: Class IDs are not task priorities or array lengths supplied by the caller. The code does not add bounds checks. Keep the task-manager head/current fields separate from this array.

Pinned references:

- `eu/src/calls/Obj_LinkNode.c` → `src/arm9/shared_engine/Obj_LinkNode_0202a290.c`; reference line(s) 19, 35, 40, 49, 50, 55, 66.
- `eu/src/calls/ResetTaskManagerState.c` → `src/arm9/core_small/func_0202a424.c`; reference line(s) 3, 7.
- `eu/src/calls/unlink_object_registry_node.c` → `src/arm9/graphics/unlink_object_registry_node_0202a3a8.c`; reference line(s) 2, 14, 18, 20.
- `eu/src/data/bss/Bss_main_020603c8.c`; reference line(s) 3.

### `main:02060534` → `gRawTouchSamplingRing`

Previous label `data_02060534`; existing ELF size **40 bytes**. Source: `eu/src/data/bss/Bss_main_02060534.c`.

40-byte BSS buffer of five 8-byte raw touch samples (u16 x, y, touch, validity).

StartTouchSamplingRing supplies this buffer and ring count 5 to TP_RequestAutoSamplingStartAsync. CopyRecentInputRecords calibrates/copies four recent records. CopyRecentTouchPoints additionally requires raw touch!=0 and validity==0, then accepts calibrated x<=255 and y<=191.

Limits: This stores raw sampling records, not four already calibrated points. Keep five slots even though readers return at most four recent samples. No pixel/time rate is inferred from the other sampling arguments.

Pinned references:

- `eu/src/calls/CopyRecentInputRecords.c` → `src/arm9/input_history/CopyRecentInputRecords_0202b6d0.c`; reference line(s) 13, 32.
- `eu/src/calls/CopyRecentTouchPoints.c` → `src/arm9/input_history/CopyRecentTouchPoints_0202b618.c`; reference line(s) 13, 35.
- `eu/src/calls/StartTouchSamplingRing.c` → `src/arm9/runtime/func_0202b5d4.c`; reference line(s) 1, 7.
- `eu/src/data/bss/Bss_main_02060534.c`; reference line(s) 3.

### `main:0205fdc8` → `gCallbackSlotArguments`

Previous label `data_0205fdc8`; existing ELF size **12 bytes**. Source: `eu/src/data/bss/Bss_main_0205fdc4.c`.

12-byte BSS array of three native callback argument words/pointers.

ResetCallbackTable clears all three entries of this array and the parallel function array. setDualArrayEntry stores the argument selected by index; InvokeCallbackSlot passes it to the matching non-NULL callback.

Limits: No bounds checks are added. Argument types depend on the registered slot; do not impose one owner type on all three words.

Pinned references:

- `eu/src/calls/InvokeCallbackSlot.c` → `src/arm9/shared_engine/InvokeCallbackSlot_02025464.c`; reference line(s) 6, 15.
- `eu/src/calls/ResetCallbackTable.c` → `src/arm9/shared_engine/ResetCallbackTable_020253f8.c`; reference line(s) 4, 13.
- `eu/src/calls/setDualArrayEntry.c` → `src/arm9/shared_engine/setDualArrayEntry_02025448.c`; reference line(s) 2, 5.
- `eu/src/data/bss/Bss_main_0205fdc4.c`; reference line(s) 3.

### `main:0205fdd4` → `gCallbackSlotFunctions`

Previous label `data_0205fdd4`; existing ELF size **12 bytes**. Source: `eu/src/data/bss/Bss_main_0205fdd4.c`.

12-byte BSS array of three native callback function words.

setDualArrayEntry pairs each function with the argument in gCallbackSlotArguments. InvokeCallbackSlot returns 0 for NULL, otherwise returns callback(argument). ResetCallbackTable clears all three functions and arguments.

Limits: Callback results are forwarded, not universally BOOL. Preserve native function/integer declarations and the independent argument array.

Pinned references:

- `eu/src/calls/InvokeCallbackSlot.c` → `src/arm9/shared_engine/InvokeCallbackSlot_02025464.c`; reference line(s) 5, 10.
- `eu/src/calls/ResetCallbackTable.c` → `src/arm9/shared_engine/ResetCallbackTable_020253f8.c`; reference line(s) 3, 12.
- `eu/src/calls/setDualArrayEntry.c` → `src/arm9/shared_engine/setDualArrayEntry_02025448.c`; reference line(s) 1, 4.
- `eu/src/data/bss/Bss_main_0205fdd4.c`; reference line(s) 3.

### `main:02060088` → `gVramTransferTaskStorage`

Previous label `data_02060088`; existing ELF size **768 bytes**. Source: `eu/src/data/bss/Bss_main_02060088.c`.

768-byte BSS storage supplied as the VRAM transfer task queue backing buffer.

InitEngine passes this address and capacity 0x30 (48) to NNS_GfdInitVramTransferManager. That initializer stores the base pointer and capacity into its queue owner and resets queue state.

Limits: This buffer is distinct from the SDK queue owner/state objects. The naming block does not add a new task struct or infer ownership of texture/palette source memory.

Pinned references:

- `eu/src/calls/InitEngine.c` → `src/arm9/runtime/InitEngine_02029b54.c`; reference line(s) 22, 44.
- `eu/src/data/bss/Bss_main_02060088.c`; reference line(s) 3.

### `main:02060878` → `gCachedOwnerNickname`

Previous label `data_02060878`; existing ELF size **22 bytes**. Source: `eu/src/data/bss/Bss_main_02060878.c`.

22-byte BSS nickname cache, addressed as u16 code units by the native writer (11 halfwords).

InitProfilePanel obtains owner information, copies the nickname to this destination and calls CensorBannedWords with the native 0x16 size argument. GetCachedOwnerNickname returns this exact address through a legacy function-typed declaration.

Limits: Do not copy the function-typed declaration to a portable header or claim a character count that excludes/guarantees termination without the string API contract. The physical size remains 22 bytes.

Pinned references:

- `eu/src/data/bss/Bss_main_02060878.c`; reference line(s) 4.
- `eu/src/overlays/ov002/calls/GetCachedOwnerNickname.c`; reference line(s) 1, 4.
- `eu/src/overlays/ov002/calls/InitProfilePanel.c`; reference line(s) 33, 83, 85.

### `main:0206088e` → `gCachedOwnerMessageStorage`

Previous label `data_0206088e`; existing ELF size **58 bytes**. Source: `eu/src/data/bss/Bss_main_02060878.c`.

58-byte BSS symbol: native message writer uses a 54-byte prefix (27 halfwords); following bytes include a shared-profile censored flag at offset 54, with other trailing bytes opaque.

InitProfilePanel copies owner.message here and calls CensorBannedWords with 0x36. Its larger SharedSettings view begins at 0206085c; the censored bitfield at+0x68 addresses 020608c4, which is messageStorage+54. That flag is set after both nickname/message filtering. GetCachedOwnerMessage returns the message-storage address.

Limits: Do not type all 58 bytes as a 29-character string, discard the trailing 4 bytes, or move the censored flag into a new allocation. The native writer has overlapping views across separate DATA owners.

Pinned references:

- `eu/src/data/bss/Bss_main_02060878.c`; reference line(s) 3.
- `eu/src/overlays/ov002/calls/GetCachedOwnerMessage.c`; reference line(s) 1, 4.
- `eu/src/overlays/ov002/calls/InitProfilePanel.c`; reference line(s) 34, 84, 86.


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
