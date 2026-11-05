# Task runtime, input state and script-buffer helpers

This block names the matched operations listed below. The evidence is their
actual implementations and callers, including EU aliases of shared sources.
An SDK-like legacy filename does not establish an SDK role.

| Previous name | Current name | Bytes / mode |
|---|---|---|
| `func_0200eddc` | `LockSoundCommandMutex` | 20 / arm |
| `func_0202a438` | `ResetTaskManagerState` | 36 / thumb |
| `func_0202a45c` | `CreateTaskObject` | 52 / arm |
| `func_0202a768` | `GetCurrentTaskObject` | 16 / arm |
| `func_0202a7b8` | `GetTaskUpdateCount` | 16 / arm |
| `NNSi_FndGetCurrentRootHeap` | `GetRunningTaskWork` | 20 / arm |
| `func_0202a734` | `CollectFinishedTask` | 52 / arm |
| `PXI_Init_0202a64c` | `DestroyTaskObjectWrapper` | 12 / arm |
| `func_0202abbc` | `ResetPadSampleState` | 32 / thumb |
| `func_0204f5a0` | `InitKeyRepeatState` | 76 / thumb |
| `func_0202b5e8` | `StartTouchSamplingRing` | 68 / arm |
| `func_02011050` | `WMi_GetSystemWork` | 12 / thumb |
| `func_02012284` | `WM_StartKeySharing` | 20 / thumb |
| `func_0201278c` | `CTRDGi_Channel17Callback` | 12 / thumb |
| `func_020257d8` | `AllocateScriptVmBuffer` | 32 / thumb |
| `func_020257f8` | `ReleaseScriptVmBuffer` | 40 / thumb |
| `func_0202b774` | `SetResourceLanguage` | 40 / thumb |
| `func_02051724` | `LoadRecordManagerArchiveEntry3` | 76 / thumb |
| `func_02051770` | `LoadRecordManagerArchiveEntry4` | 76 / thumb |
| `func_0205182c` | `LoadRecordManagerArchiveEntry6` | 76 / thumb |
| `func_02051878` | `LoadRecordManagerArchiveEntry7` | 76 / thumb |
| `func_02051ab8` | `LoadRecordManagerArchiveEntry11` | 76 / thumb |

## Task ownership and native layout

`CreateTaskObject` allocates a **44-byte task header**, then calls the existing
constructor with the descriptor, user argument and head-allocation selector 0.
That constructor allocates/clears the descriptor-sized work area, links the task,
sets its parent to the previously current task and temporarily makes it current
while calling the descriptor constructor. No allocation-failure behavior is added.

`src/runtime/TaskRuntime.h` records the native header and manager views used by
the getters. Compile-time checks retain the 44-byte header and work offset 0x20.
The state word at +0x14 can contain a callback address **or -1/-2 sentinels**;
its encoded native word is not exported as a host function pointer. Likewise the
native destructor and heap words retain their bit representation. The header
is a DS view, not a portable in-memory save format or a full host scheduler API.

| Task offset | Proven role |
|---|---|
| 0x00 | Flags. |
| 0x04 / 0x08 / 0x0c | Parent / previous / next task links. |
| 0x10 / 0x12 | Class and subclass halfwords. |
| 0x14 | State/callback word, including the -1 and -2 sentinels. |
| 0x18 | Destructor callback word used by the destruction path. |
| 0x1c | Heap word used while running task code. |
| 0x20 / 0x24 | Work pointer / descriptor-defined work size. |
| 0x28 | Reserved word initialized to zero; no further meaning assigned. |

The manager's current pointer is +4, update count +8 and list head +0xc. Its
64 class buckets occupy a separate 256-byte native pointer table.
`ResetTaskManagerState` clears the buckets/current/count/head and preserves
manager word 0. It does not destroy tasks or free their work; callers must have
established the correct lifecycle before resetting links.

`GetCurrentTaskObject` returns the borrowed current pointer, which may be NULL
outside constructors or updates. `GetRunningTaskWork` dereferences that pointer
and returns its +0x20 work field **without a null check**. Its old name
`NNSi_FndGetCurrentRootHeap` was misleading: this is a game task lookup, not a
heap lookup. Its historical library directory is retained for build continuity.
`GetTaskUpdateCount` counts unpaused update passes, with native 32-bit behavior;
it is not the hardware VBlank clock.

`CollectFinishedTask` returns 0 unless the state word equals -2. In that case
it calls the destructor wrapper only when task flag bit 0 is set, then returns 1.
The normal update loop destroys finished tasks when that same bit is clear.
Thus completion does not prove that the collector freed the object in every
case. Do not use a flagged task after successful collection.
`DestroyTaskObjectWrapper(task)` forwards to `DestroyRegisteredObject`, whose
result is the next task pointer after unlinking, work/header release and heap
restoration. Its old PXI template omitted the live incoming task argument;
the recovered definition now states the actual input and next-pointer return.

The shared constructor, task updater and destruction bodies remain in
`../src/arm9/shared_engine/Obj_Construct_0202a4b0.c`,
`../src/arm9/shared_engine/Obj_UpdateAll_0202a644.c` and
`../src/arm9/runtime_data_utilities/DestroyRegisteredObject_0202a5b4.c`.
Existing shared callers still have some erased word declarations. A host port
must normalize those callers together rather than copy DS integer pointer views.

## Sound mutex and input sampling

`LockSoundCommandMutex` passes the **address** of `data_02057c38` to
`OS_LockMutex`. `SND_Init` initializes that storage as an OSMutex and
`SNDi_UnlockMutex` passes the same address to its unlock partner. The old factory
and function-pointer labels are false. An opaque mutex declaration expresses the
proven operation without inventing its layout. The name avoids conflating this
mutex with the separate existing symbol `SNDi_LockMutex` at another address.

`ResetPadSampleState` clears the held/previous/pressed halfwords and twelve
VBlank transition timestamps, returning 1. This is a software-state reset, not
hardware input initialization. Nearby DATA is split between owners; its apparent
six-byte prefix must not be merged into a differently sized allocation.

`InitKeyRepeatState` clears the existing 26-byte state and ten repeat counters.
Null/negative configuration fields select per-field defaults 15 and 4; zero is
permitted. `UpdateKeyRepeat` uses twice those values in VBlank counts, not
milliseconds. The global transition table's twelve entries and per-state ten
repeat counters are distinct extents.

`StartTouchSamplingRing` requests TP auto sampling with vcount 0, frequency 4
and five eight-byte samples in the existing 40-byte buffer. It waits for command
mask 2 to clear and returns whether the corresponding start error mask is zero.
The asynchronous SDK function name does not make this wrapper nonblocking, and
a successful start does not validate every future coordinate sample.

## Wireless and cartridge callbacks

`WMi_GetSystemWork` returns the borrowed WM9 buffer pointer from initialized
wireless state +4, without allocating or checking initialization.
`WM_StartKeySharing(sharingBuffer, port)` invokes data sharing with AID mask
0xffff, payload size 2 and double-buffer mode enabled. Its C now returns the
actual SDK error word that the wireless caller checks; the second argument is a
port, not a size. Shared legacy declarations elsewhere still require deliberate
host-ABI recovery.

`CTRDGi_Channel17Callback` is installed as the PXI receive callback for channel
17 and clears the cartridge state word at +4. The transport binding is proved;
the field's further meaning and any PhiClock interpretation remain unknown.
Ignored incoming transport words are not assigned invented meanings.

## Script buffer lifetime and language paths

`AllocateScriptVmBuffer` stores size at VM +0x634, an opaque parameter at +0x638
and a default-heap allocation at +0x63c. The file-loading path fills that buffer
before `ScriptVm_Start` uses it as PKAC/raw script data. The old PCM/audio source
classification was misleading. Allocation does not initialize the full VM or
free a previous buffer, and the parameter's meaning remains unresolved.

`ReleaseScriptVmBuffer` frees a nonzero +0x63c buffer, clears its pointer, then
clears size and parameter. It does not stop every VM callback or clear all frame
pointers. Callers must establish that borrowed bytecode references are no longer
live before release; no new ownership or allocation-failure contract is added.

`SetResourceLanguage` lazily allocates one shared 64-byte path buffer and stores
the language as a signed halfword. `Msg_BuildLangPath` uses it to select the
language code and substitute the path. The setter does not bounds-check or
renumber language IDs; `main` supplies supported firmware IDs with an English
fallback. The output buffer is shared, not allocated per request.

## Record-manager archive entries

The five loaders retain literal archive-entry names because no more specific
asset format is established. Each uses the manager archive handle, selects the
existing head/tail loader path and stores the result at the offset below.

| Archive entry | Manager destination offset |
|---|---|
| 3 | 0x30 |
| 4 | 0x34 |
| 6 | 0x3c |
| 7 | 0x40 |
| 11 | 0x70 |

No previous-owner release or new validation is implied. Their shared native
adapters still contain an unused slot and an extra forwarded word; those are
not evidence of additional decoded asset parameters. Decode the real loader
contract before exporting a portable header.

## Reproduction and evidence index

The production filenames match the current symbols in the table. The following
commands cover the recovered native returns/interfaces; all renamed functions
also receive their own official index check during integration.

```sh
python tools/verify_idx.py src/calls/GetCurrentTaskObject.c GetCurrentTaskObject
python tools/verify_idx.py libs/nitro/nns/calls/GetRunningTaskWork.c GetRunningTaskWork
python tools/verify_idx.py src/calls/GetTaskUpdateCount.c GetTaskUpdateCount
python tools/verify_idx.py src/calls/DestroyTaskObjectWrapper.c DestroyTaskObjectWrapper
python tools/verify_idx.py src/calls/LockSoundCommandMutex.c LockSoundCommandMutex
python tools/verify_idx.py src/calls/WM_StartKeySharing.c WM_StartKeySharing --thumb
bash tools/gate.sh
```

Run from `eu/`. Integration preserves baseline objects, compares production
texts and resolved relocation targets/types/addends, then requires all 108
linked modules to retain their byte-exact hashes. Names add no C or DATA credit.

Evidence references for operations beyond the task core:

- `LockSoundCommandMutex`: `eu/src/calls/func_0200eddc.c` (1); `src/arm9/library_nitro_snd/func_0200ed90.c` (62); `eu/libs/nitro/snd/calls/SNDi_UnlockMutex.c` (1).
- `ResetPadSampleState`: `src/arm9/core_small/func_0202aba8.c` (1); `src/arm9/input_history/Pad_Sample_0202abc8.c` (3).
- `InitKeyRepeatState`: `src/arm9/runtime/func_0204f58c.c` (1); `eu/src/calls/UpdateKeyRepeat.c` (3).
- `StartTouchSamplingRing`: `src/arm9/runtime/func_0202b5d4.c` (1); `src/arm9/library_nitro_spi/TP_RequestAutoSamplingStartAsync_0200fdd8.c` (3); `eu/src/data/bss/Bss_main_02060534.c` (1).
- `WMi_GetSystemWork`: `src/arm9/shared_engine/func_0201103c.c` (1); `src/arm9/library_nitro_wm/WMi_InitCore_02010d80.c` (3); `src/arm9/library_nitro_wm/WMi_InitCore_02010d80.c` (81); `eu/src/calls/WmDataSharingSetDataCallback.c` (1).
- `WM_StartKeySharing`: `src/arm9/unclassified_helpers/func_02012270.c` (1); `eu/src/overlays/ov015/calls/func_ov015_02073c48.c` (3).
- `CTRDGi_Channel17Callback`: `src/arm9/library_nitro_ctrdg/func_02012778.c` (1); `src/arm9/library_nitro_ctrdg/CTRDG_Init_02012550.c` (3).
- `AllocateScriptVmBuffer`: `src/arm9/audio/func_020257c4.c` (1); `src/arm9/archive_startup/RoundAndInitArchive_020258b0.c` (3); `src/arm9/shared_engine/ScriptVm_Start_0202580c.c` (29); `eu/src/overlays/ov003/calls/MovieScene_Init.c` (100).
- `ReleaseScriptVmBuffer`: `src/arm9/audio/func_020257e4.c` (1); `src/arm9/shared_engine/ScriptVm_Start_0202580c.c` (29).
- `SetResourceLanguage`: `src/arm9/core_small/func_0202b760.c` (1); `src/arm9/shared_engine/Msg_BuildLangPath_0202b798.c` (3); `eu/src/calls/main.c` (78).
- `LoadRecordManagerArchiveEntry3`: `src/arm9/reviewed_helpers/func_02051710.c` (1).
- `LoadRecordManagerArchiveEntry4`: `src/arm9/reviewed_helpers/func_0205175c.c` (1).
- `LoadRecordManagerArchiveEntry6`: `src/arm9/reviewed_helpers/func_02051818.c` (1).
- `LoadRecordManagerArchiveEntry7`: `src/arm9/reviewed_helpers/func_02051864.c` (1).
- `LoadRecordManagerArchiveEntry11`: `src/arm9/reviewed_helpers/func_02051aa4.c` (1).
