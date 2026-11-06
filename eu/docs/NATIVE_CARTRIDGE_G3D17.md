# Cartridge, heap registry and G3D cache DATA (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

Cartridge handshake, module initialization and API initialization are different fields. Its 192-byte header is split 4+188; its worker owns a 232-byte thread/work view and a separate 36-byte global task record. The global task record crosses a native boundary into the first eight bytes of the following 1032-byte allocation. The remaining 1024 bytes are the worker stack, ending just before the heap-registry initialized flag.

The G3D caches also use strided views across split native objects. The Maya reader only proves inverse-scale vectors at stride 24; it does not name the intervening twelve-byte portions. Node-mix cache records are 100 bytes (clip 64 + vector 36), with the first record split at that matrix boundary. Preserve these spans rather than converting local pointer declarations directly into host allocations.

## Inventory and evidence

### `main:0205a2a0` → `gCartridgeEnabled`

Previous label `data_0205a2a0`; size **4 bytes**; source `eu/src/data/bss/Bss_main_0205a2a0.c`.

4 BSS bytes: the cartridge enable word.

CTRDG_Enable stores its enable argument in this word. The same base view used by CTRDG_IsExisting places the shared handshake/lock work immediately afterward at +4.

Limits: Keep the word width. This name does not imply that physical presence or completed cartridge identification follows merely from the enable flag.

Pinned direct/base-view references:

- `eu/src/calls/CTRDG_Enable.c` → `src/arm9/library_nitro_ctrdg/CTRDG_Enable_020124e8.c`; line(s) 7, 27.
- `eu/src/calls/CTRDG_IsExisting.c` → `src/arm9/library_nitro_ctrdg/CTRDG_IsExisting_02012364.c`; line(s) 7, 31, 50.
- `eu/src/calls/CTRDGi_InitCommon.c` → `src/arm9/library_nitro_ctrdg/CTRDGi_InitCommon_0201233c.c`; line(s) 5, 10.
- `eu/src/data/bss/Bss_main_0205a2a0.c`; line(s) 3.

### `main:0205a2a4` → `gCartridgeHandshakeAndLock`

Previous label `data_0205a2a4`; size **4 bytes**; source `eu/src/data/bss/Bss_main_0205a2a4.c`.

4 BSS bytes: volatile subprocessor-initialized halfword and lock-ID halfword.

CTRDGi_InitCommon clears this work and obtains OS_GetLockID for its second halfword. CTRDGi_InitCallback sets the first halfword on the initialization notification; CTRDGi_InitModuleInfo waits for it and uses the lock ID around cartridge-header access. include/nitro/ctrdg.h proves CTRDGWork field order.

Limits: These are distinct halfwords; do not reduce the object to a single initialized BOOL or confuse the handshake with the separate API/module initialization flags.

Pinned direct/base-view references:

- `eu/src/calls/CTRDGi_InitCallback.c` → `src/arm9/library_nitro_ctrdg/CTRDGi_InitCallback_02012714.c`; line(s) 2, 6.
- `eu/src/calls/CTRDGi_InitCommon.c` → `src/arm9/library_nitro_ctrdg/CTRDGi_InitCommon_0201233c.c`; line(s) 4, 9.
- `eu/src/calls/CTRDGi_InitModuleInfo.c` → `src/arm9/library_nitro_ctrdg/CTRDGi_InitModuleInfo_020125c8.c`; line(s) 14, 73, 88, 113.
- `eu/src/data/bss/Bss_main_0205a2a4.c`; line(s) 4.

### `main:0205a2a8` → `gCartridgeRuntimeWork`

Previous label `data_0205a2a8`; size **56 bytes**; source `eu/src/data/bss/Bss_main_0205a2a4.c`.

56 BSS bytes containing cartridge module/API initialization and callback state, with an opaque tail.

CTRDGi_InitModuleInfo tests/sets the first word. CTRDG_Init independently tests/sets +8, clears +0xc and +0x18, and registers PXI callbacks. The pulled-out callback checks/sets +0xc and invokes the callback word at +0x18; the channel-17 callback clears +4.

Limits: The first initialization flag and the API flag at +8 are different fields. Preserve all 56 bytes; roles for unused-looking tail fields are not inferred from absence of direct symbol tokens.

Pinned direct/base-view references:

- `eu/src/calls/CTRDG_Init.c` → `src/arm9/library_nitro_ctrdg/CTRDG_Init_02012550.c`; line(s) 18, 24, 27, 29, 37.
- `eu/src/calls/CTRDGi_Channel17Callback.c` → `src/arm9/library_nitro_ctrdg/func_02012778.c`; line(s) 1, 4.
- `eu/src/calls/CTRDGi_InitModuleInfo.c` → `src/arm9/library_nitro_ctrdg/CTRDGi_InitModuleInfo_020125c8.c`; line(s) 15, 61, 64.
- `eu/src/calls/CTRDGi_PulledOutCallback.c` → `src/arm9/library_nitro_ctrdg/CTRDGi_PulledOutCallback_02012730.c`; line(s) 3, 9, 11, 14.
- `eu/src/data/bss/Bss_main_0205a2a4.c`; line(s) 3.

### `main:0205a2e0` → `gCartridgeHeaderStartWord`

Previous label `data_0205a2e0`; size **4 bytes**; source `eu/src/data/bss/Bss_main_0205a2e0.c`.

4 BSS bytes: first word of the logical 192-byte CTRDGHeader view.

CTRDGi_InitModuleInfo uses this address as the complete CTRDGHeader base, fills the ROM-header suffix at +0x80 and the logo at +4, reads module/maker/game fields and publishes the header address to the ARM7 through PXI. The header type names its first word startAddress.

Limits: This ARM9 path does not fill the first word from cartridge ROM; its role follows the passed header layout. Keep BSS initialization and the separate 188-byte continuation.

Pinned direct/base-view references:

- `eu/src/calls/CTRDGi_InitModuleInfo.c` → `src/arm9/library_nitro_ctrdg/CTRDGi_InitModuleInfo_020125c8.c`; line(s) 16, 81, 82, 92, 106, 107, 111.
- `eu/src/data/bss/Bss_main_0205a2e0.c`; line(s) 5.

### `main:0205a2e4` → `gCartridgeHeaderTail`

Previous label `data_0205a2e4`; size **188 bytes**; source `eu/src/data/bss/Bss_main_0205a2e0.c`.

188 BSS bytes following the first header word, completing the 192-byte native header.

The logical header view has logo[0x9c], title, game/maker codes, machine/device fields, external-LSI IDs, version/checksum and module ID. CTRDGi_InitModuleInfo copies the logo from system ROM and the suffix from cartridge ROM before dispatching the header address.

Limits: The prefix and continuation are separate native symbols. Preserve the original copies and field layout; do not treat all 188 bytes as a title string or an owned cartridge image.

Pinned direct/base-view references:

- `eu/src/data/bss/Bss_main_0205a2e0.c`; line(s) 4.
- `eu/src/calls/CTRDGi_InitModuleInfo.c` → `src/arm9/library_nitro_ctrdg/CTRDGi_InitModuleInfo_020125c8.c`; line(s) 16, 81, 82, 92, 106, 107, 111.
- `eu/src/data/bss/Bss_main_0205a2e0.c`; line(s) 5.

### `main:0205a3a0` → `gCartridgeTaskThreadWork`

Previous label `data_0205a3a0`; size **232 bytes**; source `eu/src/data/bss/Bss_main_0205a2e0.c`.

232 BSS bytes: native thread prefix, pending-task pointer at +0xc0 and 36-byte work record at +0xc4.

CTRDG_Init passes this address to CTRDGi_InitTaskThread. That initializer clears the +0xc4 work using MIi_CpuFill24 (whose actual body clears 0x24 bytes), clears +0xc0, creates the worker thread with this same argument and wakes it. The worker sleeps until the pending-task pointer is set.

Limits: The complete allocation is larger than the native OSThread prefix. Keep the pending pointer and work tail, and preserve priority 0x14 and stack placement as native behavior rather than importing a host thread structure.

Pinned direct/base-view references:

- `eu/src/calls/CTRDG_Init.c` → `src/arm9/library_nitro_ctrdg/CTRDG_Init_02012550.c`; line(s) 20, 38.
- `eu/src/data/bss/Bss_main_0205a2e0.c`; line(s) 3.

### `main:0205a488` → `gCartridgeTaskThread`

Previous label `data_0205a488`; size **4 bytes**; source `eu/src/data/bss/Bss_main_0205a488.c`.

4 BSS bytes: pointer to the cartridge task thread/work owner.

CTRDGi_InitTaskThread guards initialization with this pointer and sets it to the supplied thread work. JobQueue_WorkerLoop_02012808 tests it to decide whether to continue or exit after the completion callback.

Limits: The thread owner and the global task-info record immediately after this word are distinct. Do not combine the pointer with a host thread handle of arbitrary width.

Pinned direct/base-view references:

- `eu/src/calls/CTRDGi_InitTaskThread.c` → `src/arm9/library_nitro_ctrdg/CTRDGi_InitTaskThread_02012784.c`; line(s) 10, 16, 17.
- `eu/src/calls/JobQueue_WorkerLoop_02012808.c` → `src/arm9/library_nitro_mi/JobQueue_WorkerLoop_020127f4.c`; line(s) 8, 34, 38.
- `eu/src/data/bss/Bss_main_0205a488.c`; line(s) 5.

### `main:0205a48c` → `gCartridgeTaskInfoPrefix`

Previous label `data_0205a48c`; size **28 bytes**; source `eu/src/data/bss/Bss_main_0205a488.c`.

28 BSS bytes: prefix of the 36-byte global task-info record.

CTRDGi_InitTaskThread clears 0x24 bytes from this address. The worker uses a 36-byte task view with run/done callbacks, result and remaining words; its global busy-byte clear at gCartridgeTaskThread+0x26 reaches task byte 34.

Limits: The final eight bytes lie at the start of the next native object. Roles of all remaining task words are not newly assigned, and the callback ABI stays unchanged.

Pinned direct/base-view references:

- `eu/src/calls/CTRDGi_InitTaskThread.c` → `src/arm9/library_nitro_ctrdg/CTRDGi_InitTaskThread_02012784.c`; line(s) 11, 19.
- `eu/src/data/bss/Bss_main_0205a488.c`; line(s) 4.

### `main:0205a4a8` → `gCartridgeTaskInfoTailAndStack`

Previous label `data_0205a4a8`; size **1032 bytes**; source `eu/src/data/bss/Bss_main_0205a488.c`.

1032 BSS bytes: final eight bytes of the 36-byte task-info record, followed by the 1024-byte worker stack.

The task-info clear starts at 0205a48c and ends at 0205a4b0. OS_CreateThread receives stack top 0205a8b0 and size 0x400, which places the stack in [0205a4b0,0205a8b0). The worker busy-byte update reaches 0205a4ae in this record tail.

Limits: Preserve both parts and the exclusive stack-top boundary. The following heap-initialized word is at the top address but is not included in the downward-growing 1024-byte stack.

Pinned direct/base-view references:

- `eu/src/data/bss/Bss_main_0205a488.c`; line(s) 3.
- `eu/src/calls/CTRDGi_InitTaskThread.c` → `src/arm9/library_nitro_ctrdg/CTRDGi_InitTaskThread_02012784.c`; line(s) 10, 16, 17.
- `eu/src/calls/JobQueue_WorkerLoop_02012808.c` → `src/arm9/library_nitro_mi/JobQueue_WorkerLoop_020127f4.c`; line(s) 8, 34, 38.
- `eu/src/data/bss/Bss_main_0205a488.c`; line(s) 5.
- `eu/src/calls/CTRDGi_InitTaskThread.c` → `src/arm9/library_nitro_ctrdg/CTRDGi_InitTaskThread_02012784.c`; line(s) 11, 19.
- `eu/src/data/bss/Bss_main_0205a488.c`; line(s) 4.
- `eu/libs/nitro/nns/calls/NNSi_FndInitHeapHead.c` → `src/arm9/library_nitro_nns/func_02012b3c.c`; line(s) 26, 47, 49.
- `eu/src/calls/CTRDGi_InitTaskThread.c` → `src/arm9/library_nitro_ctrdg/CTRDGi_InitTaskThread_02012784.c`; line(s) 12, 21.
- `eu/src/data/bss/Bss_main_0205a8b0.c`; line(s) 4.

### `main:0205a8b0` → `gHeapRegistryInitialized`

Previous label `data_0205a8b0`; size **4 bytes**; source `eu/src/data/bss/Bss_main_0205a8b0.c`.

4 BSS bytes: NNS heap-registry initialization flag.

NNSi_FndInitHeapHead initializes the following root list with link offset 4 when this flag is zero, sets it to 1, and then appends the new heap through FindListContainHeap.

Limits: CTRDGi_InitTaskThread also uses the address as an exclusive stack top; that address use is not a write to this flag and does not give it cartridge ownership.

Pinned direct/base-view references:

- `eu/libs/nitro/nns/calls/NNSi_FndInitHeapHead.c` → `src/arm9/library_nitro_nns/func_02012b3c.c`; line(s) 26, 47, 49.
- `eu/src/calls/CTRDGi_InitTaskThread.c` → `src/arm9/library_nitro_ctrdg/CTRDGi_InitTaskThread_02012784.c`; line(s) 12, 21.
- `eu/src/data/bss/Bss_main_0205a8b0.c`; line(s) 4.

### `main:0205a8b4` → `gHeapRootList`

Previous label `data_0205a8b4`; size **12 bytes**; source `eu/src/data/bss/Bss_main_0205a8b0.c`.

12 BSS bytes: native NNSFndList root heap list.

NNSi_FndInitHeapHead initializes this list once with link offset 4. FindListContainHeap starts its recursive containment lookup from this global list; the caller appends a heap to the selected list.

Limits: The native list contains two pointers and two halfwords. It is a root registry, not the current allocation heap, and its host representation requires an explicit pointer-width decision.

Pinned direct/base-view references:

- `eu/libs/nitro/nns/calls/FindListContainHeap.c` → `src/arm9/library_nitro_nns/func_02012b14.c`; line(s) 2, 5.
- `eu/libs/nitro/nns/calls/NNSi_FndInitHeapHead.c` → `src/arm9/library_nitro_nns/func_02012b3c.c`; line(s) 27, 48.
- `eu/src/data/bss/Bss_main_0205a8b0.c`; line(s) 3.

### `main:0205ab64` → `gG3dMaterialCacheStorage`

Previous label `data_0205ab64`; size **3596 bytes**; source `eu/src/data/bss/Bss_main_0205ab60.c`.

3596 BSS bytes used through the material-animation result cache base; the span includes 3584 bytes for 64 native 56-byte material results plus a 12-byte tail.

NNSi_G3dFuncSbcMAT indexes matCache by material ID for cached results, sets validity bits and fills material colors, polygon/texture parameters and animation results. Its NNSG3dMatAnmResult layout is 56 bytes.

Limits: Keep all 3596 bytes. The last 12 bytes are not assigned a role by this consumer, and this name does not claim the allocation is exactly an array of 64 records or impose a bounds check.

Pinned direct/base-view references:

- `eu/src/calls/NNSi_G3dFuncSbcMAT.c` → `src/itcm/library_nitro_nns/NNSi_G3dFuncSbcMAT_01ffe3d8.c`; line(s) 178, 205, 210, 228.
- `eu/src/data/bss/Bss_main_0205ab60.c`; line(s) 3.

### `main:0205b970` → `gG3dJointInverseScale0X`

Previous label `data_0205b970`; size **4 bytes**; source `eu/src/data/bss/Bss_main_0205b970.c`.

4 BSS bytes: X component of the first indexed inverse-scale vector.

NNSi_G3dGetJointScaleMaya writes values[3] here for node 0 when command flag 2 is set. It accesses inverse-scale vectors with a 24-byte node stride and copies the parent vector into scaleEx0 when the cached parent is non-identity.

Limits: Only the leading word is independently allocated. Preserve the strided array view; do not create a separate heap object per node from the split labels.

Pinned direct/base-view references:

- `eu/src/calls/NNSi_G3dGetJointScaleMaya.c`; line(s) 21, 41, 42, 43, 53.
- `eu/src/data/bss/Bss_main_0205b970.c`; line(s) 3.

### `main:0205b974` → `gG3dJointInverseScale0Y`

Previous label `data_0205b974`; size **4 bytes**; source `eu/src/data/bss/Bss_main_0205b974.c`.

4 BSS bytes: Y component at inverse-scale base +4.

The same Maya joint-scale function writes values[4] at base + nodeId*24 +4 and reads the parent vector as a three-word value.

Limits: This word is reached through the preceding base array, not a separate direct C token. Its native allocation remains four bytes.

Pinned direct/base-view references:

- `eu/src/data/bss/Bss_main_0205b974.c`; line(s) 4.
- `eu/src/calls/NNSi_G3dGetJointScaleMaya.c`; line(s) 21, 41, 42, 43, 53.
- `eu/src/data/bss/Bss_main_0205b970.c`; line(s) 3.

### `main:0205b978` → `gG3dJointInverseScaleCacheTail`

Previous label `data_0205b978`; size **1516 bytes**; source `eu/src/data/bss/Bss_main_0205b974.c`.

1516 BSS bytes: first inverse-scale vector Z word and the remaining strided cache span.

The Maya scale consumer writes Z at base + nodeId*24 +8 and reads three-word parent inverse scales. The physical span holds the final first-vector word plus 63 further 24-byte strides, ending at 0205bf64.

Limits: The intervening 12-byte portions are not assigned a role by this function. Preserve all 1516 bytes; do not replace the strided view by a packed VecFx32 array or add twelve bytes beyond the native span.

Pinned direct/base-view references:

- `eu/src/data/bss/Bss_main_0205b974.c`; line(s) 3.
- `eu/src/calls/NNSi_G3dGetJointScaleMaya.c`; line(s) 21, 41, 42, 43, 53.
- `eu/src/data/bss/Bss_main_0205b970.c`; line(s) 3.

### `main:0205bf64` → `gG3dNodeMixClipMatrix0`

Previous label `data_0205bf64`; size **64 bytes**; source `eu/src/data/bss/Bss_main_0205bf64.c`.

64 BSS bytes: first 4x4 clip matrix of the node-mix cache.

NNSi_G3dFuncSbcNODEMIX computes nodeId*100 for a cache entry, fills its clip matrix with G3X_GetClipMtx when invalid and weights selected matrix elements into the position accumulator.

Limits: A complete cache record also has a 36-byte vector matrix in the next object. Preserve native matrix size/order and the separate allocation.

Pinned direct/base-view references:

- `eu/src/calls/NNSi_G3dFuncSbcNODEMIX.c`; line(s) 57, 111.
- `eu/src/data/bss/Bss_main_0205bf64.c`; line(s) 4.

### `main:0205bfa4` → `gG3dNodeMixCacheTail`

Previous label `data_0205bfa4`; size **6336 bytes**; source `eu/src/data/bss/Bss_main_0205bf64.c`.

6336 BSS bytes: first 3x3 vector matrix followed by 63 complete 100-byte node-mix records. Together with the 64-byte prefix the span is 6400 bytes.

NNSi_G3dFuncSbcNODEMIX obtains previousVector at this base + nodeId*100, fills it with G3X_GetVectorMtx and weights it into the vector accumulator. Its validity flags are in the render-state owner, not this cache allocation.

Limits: The tail is not an array solely of MtxFx33 despite its local declaration. Keep the 100-byte shared clip/vector stride, all 6336 bytes and the native input assumptions.

Pinned direct/base-view references:

- `eu/src/calls/NNSi_G3dFuncSbcNODEMIX.c`; line(s) 58, 136.
- `eu/src/data/bss/Bss_main_0205bf64.c`; line(s) 3.

Additional layout/clear proof: `include/nitro/ctrdg.h`, `eu/src/calls/MIi_CpuFill24.c`, `eu/src/calls/CTRDGi_InitTaskThread.c`, `eu/src/calls/NNSi_G3dGetJointScaleMaya.c` and `eu/src/calls/NNSi_G3dFuncSbcNODEMIX.c` at the pinned baseline.


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
