# Card, sound-player and stage-script native DATA views (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

Native allocations split several logical owners. The CARDiCommon extends across1152+128+32 bytes; the32 sound players span8+16+4+1004+24+96 bytes; the handler table spans128+128+68 bytes. This pass keeps every fragment and exposes its proven owner rather than declaring new independent arrays.
The sound table is live runtime BSS. BuildInfo also points at two interior addresses as autoload-list bounds; those startup metadata fields remain intact and do not establish that runtime sound bytes contain autoload descriptors.

## Per-symbol inventory

### `main:02057460` → `gCardCommonStackAndTaskStateTail`

Previous `data_02057460`; **128 bytes**; source `eu/src/data/bss/Bss_main_02057460.c`.

128 BSS bytes, CARDiCommon offsets 0x480..0x4ff: 104 bytes of the thread-stack tail, task callback, completion callback and argument, busy queue and source word.

card_rom_internal.h fixes the thread stack at common+0xe8..0x4e7 and task/request fields after it. CARDi_RequestStreamCommand loads the literal 02057460 and writes the source through its common+0x4fc view. The native cardi_common allocation ends at +0x480; this fragment continues the same logical owner.

Limits: Do not allocate a second stack/task object or resize the 1152-byte native prefix. Preserve this fragment and its source path. The 104 bytes are the tail of the existing 1024-byte stack, not another stack.

Evidence sources:

- `eu/src/data/bss/Bss_main_02057460.c`; frozen lines 3.
- `eu/libs/nitro/card/calls/CARDi_RequestStreamCommand.c` → `src/arm9/library_nitro_card/CARDi_RequestStreamCommand_02009a0c.c`; full frozen body and its hash are in the plan.
- eu/libs/nitro/card/card_rom_internal.h (published136e view; same field offsets in frozen consumers).

### `main:020574e0` → `gCardCommonTransferStateTail`

Previous `data_020574e0`; **32 bytes**; source `eu/src/data/bss/Bss_main_020574e0.c`.

32 BSS bytes, CARDiCommon offsets 0x500..0x51f: destination, length, DMA channel/interface, request type/retry/mode and current ARM9 thread.

CARDi_RequestStreamCommand, CARDi_OnFifoRecv, CARDi_ReadRomWithDMA and CARDi_DmaReadPageCallback load this physical base or use the matching common offsets. The logical CARDiCommon ends exactly at 02057500, where CARDiHookChain starts.

Limits: These fields share the cardi_common lifetime. The common prefix, previous128-byte fragment and this32-byte fragment remain separate native objects. Do not confuse the following CARDiHookChain with the currentThread word at +0x51c.

Evidence sources:

- `eu/src/data/bss/Bss_main_020574e0.c`; frozen lines 3.
- `eu/libs/nitro/card/calls/CARDi_RequestStreamCommand.c` → `src/arm9/library_nitro_card/CARDi_RequestStreamCommand_02009a0c.c`; full frozen body and its hash are in the plan.
- `eu/libs/nitro/card/calls/CARDi_OnFifoRecv.c`; full frozen body and its hash are in the plan.
- `eu/libs/nitro/card/calls/CARDi_ReadRomWithDMA.c`; full frozen body and its hash are in the plan.
- `eu/libs/nitro/card/calls/CARDi_DmaReadPageCallback.c`; full frozen body and its hash are in the plan.
- eu/libs/nitro/card/card_rom_internal.h (published136e view; same field offsets in frozen consumers).

### `main:0205dd00` → `gSndPlayersFirstListAndHeapList`

Previous `data_0205dd00`; **16 bytes**; source `eu/src/data/bss/Bss_main_0205dcf8.c`.

16 BSS bytes, sSndPlayers+8..+23: first player-list count/offset and the complete first heap list.

NNSSndPlayer has two12-byte NNSFndList fields followed by playableSeqCount at24. NNS_SndPlayerCountPlayingSeqByPlayerNo loads 0205dd00 and indexes by36. NNSi_SndPlayerInit initializes all32 records with the same layout.

Limits: This is a fragment of the1152-byte32-player table, not four independent player records. Preserve the native8-byte sSndPlayers prefix and every following fragment.

Evidence sources:

- `eu/src/data/bss/Bss_main_0205dcf8.c`; frozen lines 3.
- `eu/libs/nns/snd/calls/NNS_SndPlayerCountPlayingSeqByPlayerNo.c` → `src/arm9/library_nns_snd/NNS_SndPlayerCountPlayingSeqByPlayerNo_0201d6c0.c`; full frozen body and its hash are in the plan.
- `eu/libs/nns/snd/calls/NNSi_SndPlayerInit.c` → `src/arm9/library_nns_snd/func_0201d8c0.c`; full frozen body and its hash are in the plan.

### `main:0205dd10` → `gSndPlayersFirstPlayableSeqCount`

Previous `data_0205dd10`; **4 bytes**; source `eu/src/data/bss/Bss_main_0205dd10.c`.

4 BSS bytes: player0.playableSeqCount at sSndPlayers+24.

NNS_SndPlayerSetPlayableSeqCount uses literal0205dd10 with36-byte player stride; NNSi_SndPlayerInit sets this field to1 for32 players.

Limits: The native setter narrows seqCount to u16 before storing into the word. This rename does not alter that behavior, width or native fragmented storage.

Evidence sources:

- `eu/src/data/bss/Bss_main_0205dd10.c`; frozen lines 4.
- `eu/libs/nns/snd/calls/NNS_SndPlayerSetPlayableSeqCount.c` → `src/arm9/library_nns_snd/func_0201d414.c`; full frozen body and its hash are in the plan.
- `eu/libs/nns/snd/calls/NNSi_SndPlayerInit.c` → `src/arm9/library_nns_snd/func_0201d8c0.c`; full frozen body and its hash are in the plan.

### `main:0205dd14` → `gSndPlayersChannelFlagsAndRecordsTail`

Previous `data_0205dd14`; **1004 bytes**; source `eu/src/data/bss/Bss_main_0205dd10.c`.

1004 BSS bytes, sSndPlayers+28..+1031: first allocatable-channel word, first volume/padding and subsequent records up to player28.heapList.

NNS_SndPlayerSetAllocatableChannel loads0205dd14 and indexes by36. The32-record initializer and NNSSndPlayer declaration prove this entire contiguous slice belongs to the same player table.

Limits: This mixed fragment is not a standalone channel-mask array. It ends immediately before player28.playableSeqCount and must keep all1004 native bytes.

Evidence sources:

- `eu/src/data/bss/Bss_main_0205dd10.c`; frozen lines 3.
- `eu/libs/nns/snd/calls/NNS_SndPlayerSetAllocatableChannel.c` → `src/arm9/library_nns_snd/NNS_SndPlayerSetAllocatableChannel_0201d434.c`; full frozen body and its hash are in the plan.
- `eu/libs/nns/snd/calls/NNSi_SndPlayerInit.c` → `src/arm9/library_nns_snd/func_0201d8c0.c`; full frozen body and its hash are in the plan.

### `main:0205e100` → `gSndPlayersLateRecordFields`

Previous `data_0205e100`; **24 bytes**; source `eu/src/data/bss/Bss_main_0205e100.c`.

24 BSS bytes, table offsets1032..1055: player28 playable-count/channel-mask/volume block and player29 playerList.

The NNSi_SndPlayerInit loop over32 records of36 bytes reaches this slice. The next slice begins at player29.heapList. BuildInfo also stores this address as autoloadListStart; that startup metadata is recorded separately from the proven runtime owner.

Limits: Do not interpret runtime contents as an autoload table or infer a new allocation from the24-byte span. Both the existing BuildInfo pointer and the BSS player-table lifetime are preserved; startup reuse is not fully reconstructed here.

Evidence sources:

- `eu/libs/nitro/init/data/tables/BuildInfo.c`; frozen lines 17, 22.
- `eu/src/data/bss/Bss_main_0205e100.c`; frozen lines 4.
- `eu/libs/nns/snd/calls/NNSi_SndPlayerInit.c` → `src/arm9/library_nns_snd/func_0201d8c0.c`; full frozen body and its hash are in the plan.

### `main:0205e118` → `gSndPlayersFinalRecordsTail`

Previous `data_0205e118`; **96 bytes**; source `eu/src/data/bss/Bss_main_0205e100.c`.

96 BSS bytes, table offsets1056..1151: player29 heapList and trailing fields, followed by players30 and31.

The32*36-byte sSndPlayers view ends at0205e178, exactly the next sSndStrmInitialized allocation. NNSi_SndPlayerInit writes the lists, volume, playable-count and channel-mask of these final records. BuildInfo also points here as autoloadListEnd.

Limits: Keep the96-byte allocation and the BuildInfo relocation. The end-pointer role in startup metadata does not make these96 runtime bytes an autoload-list suffix.

Evidence sources:

- `eu/libs/nitro/init/data/tables/BuildInfo.c`; frozen lines 18, 23.
- `eu/src/data/bss/Bss_main_0205e100.c`; frozen lines 3.
- `eu/libs/nns/snd/calls/NNSi_SndPlayerInit.c` → `src/arm9/library_nns_snd/func_0201d8c0.c`; full frozen body and its hash are in the plan.

### `ov021:020b575c` → `gStageScriptHandlerEntries32To63`

Previous `data_ov021_020b575c`; **128 bytes**; source `eu/src/overlays/ov021/data/bss/Bss_ov021_020b575c.c`.

128 BSS bytes: logical handler-table entries32 through63.

InitScriptHandlerTable begins at gScriptHandlerTable=020b56dc and writes entries0..78. Its decodedLDR at020b48b0 references this native tail. Entry32 is at020b575c and entry64 at020b57dc.

Limits: This is one shared handler table, not a separately initialized dispatch registry. Preserve the128-byte native gScriptHandlerTable prefix and the final68-byte slice.

Evidence sources:

- `eu/src/overlays/ov021/data/bss/Bss_ov021_020b575c.c`; frozen lines 3.
- `eu/src/overlays/ov021/calls/InitScriptHandlerTable.c` → `src/ov021/script_ops/InitScriptHandlerTable_020b4884.c`; full frozen body and its hash are in the plan.

### `ov021:020b57dc` → `gStageScriptHandlerFinalEntriesStorage`

Previous `data_ov021_020b57dc`; **68 bytes**; source `eu/src/overlays/ov021/data/bss/Bss_ov021_020b57dc.c`.

68 BSS bytes: entries64..78 occupy60 bytes, followed by eight retained opaque bytes.

InitScriptHandlerTable writes indices through78 from020b56dc; the configured Thumb function loads literal020b57dc at020b48b6. The last proven entry ends at020b5818, while native storage ends020b5820.

Limits: Do not claim two more live handlers from the extraeight bytes or resize the allocation. The handler targets retain their original calling conventions and returns.

Evidence sources:

- `eu/src/overlays/ov021/data/bss/Bss_ov021_020b57dc.c`; frozen lines 3.
- `eu/src/overlays/ov021/calls/InitScriptHandlerTable.c` → `src/ov021/script_ops/InitScriptHandlerTable_020b4884.c`; full frozen body and its hash are in the plan.


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
