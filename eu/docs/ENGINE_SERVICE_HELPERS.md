# Engine service helpers: timing, loading, audio and random state

Names follow the matched bodies and their actual consumers. The wrappers retain
their native operation order and underlying implementations. Logical arguments
are documented where old shared parameter labels were misleading; no new
compiler trick, runtime parameter or instruction substitution is introduced.

## Tween state and clock contract

The same native 28-byte state is used by initialization, configuration, start,
pause and the sampler. It is not a separate stopwatch object.

| Offset | Proven value |
|---|---|
| 0x00 | Curve/mode. |
| 0x04 | Duration. |
| 0x08 / 0x0c | From/to values. |
| 0x10 | 64-bit raw tick value. |
| 0x18 | Started mask 1, paused mask 2, finished mask 4. |

`ConfigureTween(state, mode, from, to, duration)` writes duration from the **fifth
machine argument** to +4. Misleading private typedefs at callers do not change
this order. It clears the started, paused and finished masks and does not start
timing. `InitTween` instead marks the freshly cleared state as finished and not
started. Both clear exactly 0x1c bytes.

`StartTween` always stores `OS_GetTick()` as the new origin and sets started,
clearing paused and finished. It does not change mode, duration or endpoints.
`SetTweenPaused` changes state only on a pause/unpause transition. On either
transition it stores `now - tickValue`: paused storage is elapsed raw ticks;
unpaused storage is a start timestamp. Repeating the same requested state is a
no-op, and this helper has no started-state guard. Preserve the 64-bit tick
arithmetic and the sampler's actual duration conversion rather than relabeling
raw ticks as milliseconds. Native bitfield adapters and alignment are not a
portable host serialization format.

## Random generator and split storage

`NextSharedRandom16Scaled(range)` uses exactly the three words owned by
`Bss_main_020604d8.c`: current state, multiplier and increment. It first performs
`state = state * multiplier + increment` modulo 32 bits, stores the new state,
and takes its upper 16 bits. Range zero returns those upper bits directly.
Otherwise it multiplies that value by range using a **32-bit product**, shifts
right 16, then truncates to 16 bits.

A host port must preserve that intermediate wrap: widening the product changes
results for large ranges. This is not promised to be uniform or below every
arbitrary 32-bit range. The seed routine also writes neighboring split storage;
those neighboring owners are not merged into a guessed nine-word RNG allocation.
The native C declaration now expresses the real three-word array extent.
The separately named `SetGeometryDmaFastMode` controls GX DMA and is not this RNG.

## File/resource and audio boundaries

The tail file-loader wrapper supplies alignment mode 1 to the synchronous
loader. Plain files allocate with -0x20 alignment; compressed files forward mode
1 to their decompression allocation path. Compression is selected by the file
ID/path (.Z), not by this alignment mode. Releasing a loader request does not itself prove that a returned resource
buffer has been freed. The per-function entries below record which object is
released and the ownership boundaries that remain native.

`SetFileLoaderTextureUploadQueueMode(0)` selects direct texture and palette
upload hooks; nonzero selects queued submission. Preserve this choice and the
upload-before-archive-trim ordering when separating the renderer from assets.
Submission is not automatically completion. `RelocateArchiveSectionsWithDefaultFlags`
retains its exact default option words; it is not permission to relocate unknown
asset formats. `ReleaseMapLayoutReference` retains the original reference-count
and final-release behavior.

Sound command IDs and queue fields in the names are literal operations, not
unproved sound-event meanings. The stream helper starts a previously prepared
stream only under its actual status predicate; the name does not promise a
fresh resource load or playback at a nonzero position.

## Cached brightness and platform clock

`GetVBlankCounter` exposes the raw 32-bit counter through a legacy `int(void)`
getter. The underlying word is incremented by the VBlank interrupt; a port should
interpret its bits as u32. It can wrap and can move backwards when
`ClosePanelAndResume` restores a saved counter through `SetVBlankStateWord`,
alongside restoration of the OS tick. It is not a monotonic or 64-bit wall clock.
`GetMainBrightnessSetting` and `GetSubBrightnessSetting` return the signed cached
bytes published later to the corresponding master-brightness registers. They do
not read the current hardware register. `CacheMainBrightnessAndTestZero` caches
the main value at panel +0x9c and tests zero; that alone is not a fade-completion
protocol. `ConfigureArm9MemorySystem` retains its ARM9 memory/cache setup; a port
must replace the platform operation deliberately, rather than attach gameplay
meaning to its hardware calls.

## Entrypoints and evidence

Evidence paths are repository-relative; current helper paths are relative to
`eu/`. Shared US source filenames remain unchanged and are interpreted through
the current EU symbol aliases.

### `QueueSoundCommand0A`

Previously `func_0200ea60`; 40 bytes, arm. Source: `src/calls/QueueSoundCommand0A.c`.

- Forwards three words to PushCommand_impl(command0xA,a,b,c,0). Evidence: `src/arm9/core_small/func_0200ea4c.c`:2.
- Allocates SND command, writes command ID and4argument words, then appends reserved list. Evidence: `src/arm9/library_nitro_snd/func_0200ed4c.c`:4.

Numeric opcode retained because its complete SDK command meaning is not established here. Does not flush or wait for hardware command completion.

### `AppendReservedSoundCommand`

Previously `func_0200f05c`; 56 bytes, arm. Source: `src/calls/AppendReservedSoundCommand.c`.

- Disables interrupts, appends command to manager reservedHead/reservedTail, writes next=null and restores interrupts. Evidence: `src/arm9/core_small/func_0200f048.c`:9.
- Flusher submits same reservedHead and clears same head/tail. Evidence: `src/arm9/audio/audio_flush_reserved_commands_0200f080.c`:32.

No null/double-enqueue guard. No host mutex/thread-safety claim. Keep original command manager sizes; tail update does not submit sound itself.

### `CountReservedSoundCommands`

Previously `func_0200f354`; 60 bytes, arm. Source: `src/calls/CountReservedSoundCommands.c`.

- Disables interrupts; walks next words from manager+8 reservedHead; counts and restores interrupts. Evidence: `src/arm9/core_small/func_0200f340.c`:8.

Counts reserved linked list, not sent blocks or free commands. No cycle protection.

### `ReleaseLoaderRequest`

Previously `func_0202b880`; 40 bytes, arm. Source: `src/calls/ReleaseLoaderRequest.c`.

- Pushes node to gFileLoader+0x18 under interrupt mask. Evidence: `src/arm9/shared_records/func_0202b86c.c`:13.
- Same slot is named freeList, popped by allocator and next cleared. Evidence: `src/arm9/filesystem/AllocLoaderRequest_0202b810.c`:7.

Returns request descriptor to pool; does not free client file buffer or validate null/node state.

### `LoadFileAllocFromHeapTail`

Previously `func_0202c4a0`; 20 bytes, arm. Source: `src/calls/LoadFileAllocFromHeapTail.c`.

- Calls FileLoader_LoadAlloc(fileOrPath,1,second,fourth). Evidence: `src/arm9/filesystem/func_0202c48c.c`:3.
- For compressed files, forwards alignMode=1; plain files allocate with -0x20. Compression follows the file ID/path, not this mode. Reads then closes the file before returning. Evidence: `src/arm9/filesystem/FileLoader_LoadAlloc_0202bde4.c`:79.
- Existing Archive_LoadFile counterpart supplies selector0. Evidence: `src/arm9/filesystem/func_0202c478.c`:3.

Synchronous loader wrapper, distinct from queued RequestFileLoadFromHeapTail. Retain legacy source slots without inventing logical meaning for unused third word; current fourth word is forwarded to backend unused slot. Returned buffer ownership remains client responsibility.

### `SetFileLoaderTextureUploadQueueMode`

Previously `func_0202c6a4`; 60 bytes, arm. Source: `src/calls/SetFileLoaderTextureUploadQueueMode.c`.

- Sets loader hooks+0xc/+0x10: mode0 selects direct texture/palette loaders, nonzero selects enqueue wrappers. Evidence: `src/arm9/core_small/func_0202c690.c`:8.
- Direct texture helper wraps GX_BeginLoadTex/GX_LoadTex/GX_EndLoadTex. Evidence: `src/arm9/core_small/func_0202c19c.c`:1.
- Queue helper registers VRAM transfer task type0, forwarding source/destination/size. Evidence: `src/arm9/shared_engine/EnqueueGfxCmd0_0202c184.c`:1.

Selects callbacks; performs no upload itself and no queue flush. Use queue-vs-direct wording, not a promise of thread or DMA completion behavior.

### `RelocateArchiveSectionsWithDefaultFlags`

Previously `func_0202d328`; 20 bytes, arm. Source: `src/calls/RelocateArchiveSectionsWithDefaultFlags.c`.

- Calls RelocateArchiveSections(archive,0,extra). Evidence: `src/arm9/archive_startup/func_0202d314.c`:3.
- Backend relocates up to8section offset lists once, optional dispatch controlled by third input. Evidence: `src/arm9/archive_startup/RelocateArchiveSections_0202d248.c`:12.

Zero flags does not suppress third-argument dispatch. No validation or independent allocation.

### `ReleaseMapLayoutReference`

Previously `func_02050a58`; 60 bytes, thumb. Source: `src/calls/ReleaseMapLayoutReference.c`.

- If global map layout nonnull, decrements word0; on zero frees owned pointer+0x9c, clears it, frees layout and clears global. Evidence: `src/arm9/reviewed_helpers/func_02050a44.c`:5.

One decrement per call, free only on transition to zero. Do not describe this as unconditional unload. No underflow or concurrency guard; other field layout remains unknown.

### `InitTween`

Previously `func_020524fc`; 44 bytes, arm. Source: `src/calls/InitTween.c`.

- Clears28bytes and sets bit2 of flags+0x18 while clearing bits0/1. Evidence: `src/arm9/core_small/func_020524e8.c`:4.
- Tween layout establishes mode,duration,from,to,startTick and started/paused/finished bits. Evidence: `src/arm9/runtime_data_utilities/SampleTweenValue_0205258c.c`:7.

Initial state is not started and marked finished. Does not begin timing.

### `ConfigureTween`

Previously `func_02052528`; 72 bytes, arm. Source: `src/calls/ConfigureTween.c`.

- Clears28bytes, writes first input at0, second at8, third atC, fourth at4 and leaves started/paused/finished clear. Evidence: `src/arm9/record_management/func_02052514.c`:12.
- Sampler uses offset0 as curve/mode, offset4 as duration, offsets8/C endpoints. Evidence: `src/arm9/runtime_data_utilities/SampleTweenValue_0205258c.c`:7.
- Caller passes (mode0,from0,toFX32_ONE,duration) confirming parameter ordering. Evidence: `src/ov045/animation/StartUnitTween_020bf1f8.c`:5.

Actual logical argument order is mode,from,to,duration. Several shared caller typedefs/parameter names label these in the opposite order; do not change machine argument ordering to follow those labels. Does not call OS_GetTick or start timing.

### `StartTween`

Previously `func_02052570`; 48 bytes, arm. Source: `src/calls/StartTween.c`.

- Sets startTick at+0x10 from OS_GetTick, started1, paused0, finished0. Evidence: `src/arm9/core_small/func_0205255c.c`:1.
- Sampler uses same tick/flags and elapsed duration to compute value. Evidence: `src/arm9/runtime_data_utilities/SampleTweenValue_0205258c.c`:32.

Restarts time origin on every call. Does not change curve,endpoints or duration.

### `SetTweenPaused`

Previously `setStopwatchHeld`; 120 bytes, arm. Source: `src/calls/SetTweenPaused.c`.

- On flag transition, toggles bit1 and replaces stored64-bit tick value with OS_GetTick-minus-value. Evidence: `src/arm9/timing/setStopwatchHeld_02052648.c`:17.
- When paused, stored value is elapsed rawticks; otherwise it is start timestamp. Evidence: `src/arm9/runtime_data_utilities/SampleTweenValue_0205258c.c`:32.

Already-correct state is no-op. Pause/unpause preserve elapsed time; no started-state guard. This is the same28-byte Tween layout, not a separate stopwatch class.

### `StopSequencePlayersFrom2`

Previously `func_0204d994`; 40 bytes, arm. Source: `src/calls/StopSequencePlayersFrom2.c`.

- Loops player indices2..31 and calls NNS_SndPlayerStopSeqByPlayerNo(index,0). Evidence: `src/arm9/core_small/func_0204d980.c`:2.

Do not say stop all players: players0/1 are deliberately skipped. No inferred primary/music/effect roles.

### `StartPreparedStreamIfReady`

Previously `func_0204de64`; 64 bytes, arm. Source: `src/calls/StartPreparedStreamIfReady.c`.

- If stream byte state at work+0xb44ce+index*8 equals2, calls NNS_SndArcStrmStartPrepared on handle at+0xb44c0+index*4 and returns1; otherwise0. Evidence: `src/arm9/reviewed_helpers/func_0204de50.c`:6.

Return indicates call was issued, not playback completion. No local bounds guard or state update.

### `InitCellAnimationFromSequenceIndex`

Previously `func_0204e564`; 56 bytes, arm. Source: `src/calls/InitCellAnimationFromSequenceIndex.c`.

- Negative sequence index returns; otherwise narrowsu16, gets NNS_G2d animation sequence and initializes cell animation. Evidence: `src/arm9/core_small/func_0204e550.c`:2.

No upper-bound validation, >=65536 values wrap to16bits. Keep allocation/sequence ownership separate.

### `SetIndexedRecordAnimationSpeed`

Previously `func_0204f2ac`; 40 bytes, arm. Source: `src/calls/SetIndexedRecordAnimationSpeed.c`.

- Negative record index returns; otherwise invokes NNS_G2dSetCellAnimationSpeed at array+index*0x8c+0x18. Evidence: `src/arm9/core_small/func_0204f298.c`:1.

Same indexed-cell-animation controller offset as already named frame accessors. No upper-bound validation.

### `UnlinkActiveIndexedRecord`

Previously `func_0204f0d4`; 68 bytes, arm. Source: `src/calls/UnlinkActiveIndexedRecord.c`.

- Rejects negative index; if bit0 at record+0x7c is set, unlinks payload at record+4 and clears bit0. Evidence: `src/arm9/record_management/func_0204f0c0.c`:1.

Does not free record contents or storage. No action if inactive; no upper bound.

### `ConfigureArm9MemorySystem`

Previously `func_02000a78`; 232 bytes, arm. Source: `src/calls/ConfigureArm9MemorySystem.c`.

- Reads/writes CP15 control; cache invalidate/drain,8region registers, ITCM/DTCM, cacheability/write-buffer/access permissions, final control mask. Evidence: `eu/src/calls/ConfigureArm9MemorySystem.c`:8.

Preserve selected existing compiler, builtins and hard-register declarations. This proposal adds no assembly and suggests no code rewrite. Detailed permission-bit names and region policies require architecture constants; name is intentionally broad.

### `GetVBlankCounter`

Previously `func_01ff80d4`; 16 bytes, arm. Source: `src/calls/GetVBlankCounter.c`.

- Returns first word of gVBlankCallbackState. Evidence: `eu/src/calls/GetVBlankCounter.c`:1.
- First word is counter, incremented once per VBlank interrupt. Evidence: `eu/src/calls/OSi_VBlankInterruptHandler.c`:9.
- Read before/after update and used as frame-target wait counter. Evidence: `eu/src/calls/main.c`:113.

Unsigned32-bit wrap counter, no wall-clock duration or monotonic64 guarantee. Prefer u32 result after exact check.

### `GetMainBrightnessSetting`

Previously `func_02029f5c`; 16 bytes, arm. Source: `src/calls/GetMainBrightnessSetting.c`.

- Returns signed byte at data02060388+1. Evidence: `src/arm9/shared_engine/func_02029f48.c`:1.
- Bit0 publishes byte+1 to main master-brightness register0x0400006c; flags are then cleared. Evidence: `eu/src/calls/OSi_VBlankInterruptHandler.c`:31.

Reads cached/requested setting, not a hardware register; value survives after request is applied.

### `GetSubBrightnessSetting`

Previously `func_02029f6c`; 16 bytes, arm. Source: `src/calls/GetSubBrightnessSetting.c`.

- Returns signed byte at data02060388+2. Evidence: `src/arm9/shared_engine/func_02029f58.c`:1.
- Bit1 publishes byte+2 to sub master-brightness register0x0400106c. Evidence: `eu/src/calls/OSi_VBlankInterruptHandler.c`:31.

Reads cached/requested setting, not a hardware register.

### `CacheMainBrightnessAndTestZero`

Previously `func_0202858c`; 40 bytes, thumb. Source: `src/calls/CacheMainBrightnessAndTestZero.c`.

- Reads main brightness helper; stores to gPanelState+0x9c; returns abs(value)==0. Evidence: `src/arm9/unclassified_helpers/func_02028578.c`:1.

Existing pointer declarations for scalar value and abs are wrong legacy views; native int prototype is justified, but preserve original compiled behavior. No assumed fade-complete or panel-state meaning beyond zero test.

### `NextSharedRandom16Scaled`

Previously `func_0202a9e4`; 52 bytes, arm. Source: `src/calls/NextSharedRandom16Scaled.c`.

- Updates state0 = state1*state0+state2 modulo2^32. range0 returns upper16; nonzero scales those16 bits by u32range, right shifts16 and truncatesu16. Evidence: `src/arm9/core_small/func_0202a9d0.c`:3.
- Writes same initial state, multiplier0x5d588b65 and increment0x269ec3. Evidence: `src/arm9/runtime_data_utilities/SeedSharedRandomState_0202a984.c`:3.
- Callers request small ranges and interpret result as random selection. Evidence: `eu/src/overlays/ov001/calls/RollRandomRewardStats.c`:10.

Do not promise RandomBelow for arbitraryu32range: product wraps32bits and final result truncates16bits. range0 means raw16bits, not empty range. SeedSharedRandomState writes9words across split global storage; Bss_main_020604d8 owns only3words, avoid full-struct overwrite based on that symbol alone.

## Verification

From `eu/`:

```sh
python tools/verify_idx.py src/calls/QueueSoundCommand0A.c QueueSoundCommand0A
python tools/verify_idx.py src/calls/AppendReservedSoundCommand.c AppendReservedSoundCommand
python tools/verify_idx.py src/calls/CountReservedSoundCommands.c CountReservedSoundCommands
python tools/verify_idx.py src/calls/ReleaseLoaderRequest.c ReleaseLoaderRequest
python tools/verify_idx.py src/calls/LoadFileAllocFromHeapTail.c LoadFileAllocFromHeapTail
python tools/verify_idx.py src/calls/SetFileLoaderTextureUploadQueueMode.c SetFileLoaderTextureUploadQueueMode
python tools/verify_idx.py src/calls/RelocateArchiveSectionsWithDefaultFlags.c RelocateArchiveSectionsWithDefaultFlags
python tools/verify_idx.py src/calls/ReleaseMapLayoutReference.c ReleaseMapLayoutReference --thumb
python tools/verify_idx.py src/calls/InitTween.c InitTween
python tools/verify_idx.py src/calls/ConfigureTween.c ConfigureTween
python tools/verify_idx.py src/calls/StartTween.c StartTween
python tools/verify_idx.py src/calls/SetTweenPaused.c SetTweenPaused
python tools/verify_idx.py src/calls/StopSequencePlayersFrom2.c StopSequencePlayersFrom2
python tools/verify_idx.py src/calls/StartPreparedStreamIfReady.c StartPreparedStreamIfReady
python tools/verify_idx.py src/calls/InitCellAnimationFromSequenceIndex.c InitCellAnimationFromSequenceIndex
python tools/verify_idx.py src/calls/SetIndexedRecordAnimationSpeed.c SetIndexedRecordAnimationSpeed
python tools/verify_idx.py src/calls/UnlinkActiveIndexedRecord.c UnlinkActiveIndexedRecord
python tools/verify_idx.py src/calls/ConfigureArm9MemorySystem.c ConfigureArm9MemorySystem
python tools/verify_idx.py src/calls/GetVBlankCounter.c GetVBlankCounter
python tools/verify_idx.py src/calls/GetMainBrightnessSetting.c GetMainBrightnessSetting
python tools/verify_idx.py src/calls/GetSubBrightnessSetting.c GetSubBrightnessSetting
python tools/verify_idx.py src/calls/CacheMainBrightnessAndTestZero.c CacheMainBrightnessAndTestZero --thumb
python tools/verify_idx.py src/calls/NextSharedRandom16Scaled.c NextSharedRandom16Scaled
bash tools/gate.sh
```

Integration retains baseline objects and compares production texts, resolved
relocation targets/types and addends. All 108 linked module hashes must remain
byte-exact. Naming and documenting these operations adds no code or DATA credit.
