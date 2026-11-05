# Movie scene, decoder, reader and caption contracts

This block identifies 50 EU entrypoints from their actual bodies, typed C/C++
consumers, scheduler registrations and format readers. Its source checkpoint is
`b15bdc31b7eabbe004ed38543d0d98c94fb98342`. These are descriptive behavior names;
the validation section records the existing toolchain checks after integration
on top of `bebdfa269e560b99118cb371ba6722c02363bde8`.
The documented interfaces do not add C or verified-library reconstruction credit.

## Distinct owners and state machines

| Owner | Established fields / relationship |
|---|---|
| Movie scene task work, pointer at `data_ov022_020b7da0` | `u16 active` at 0; script VM at +4; embedded caption renderer at `+0x830`; playback phase `s32 +0x8b0`; pending-transfer byte `+0x8b5`; fade level `s32 +0x8b8`. |
| Task handle at `data_ov022_020b7c00` | Created through the movie descriptor. The destroy adapter tests exactly -1; cleanup sets that sentinel and clears the work global. |
| Playback globals at `data_ov022_020b7da8` | Separate audio owner pointer at +4 and main frame-timer pointer at +8. |
| Frame timer | Decoder pointer at 0; decode-attempt count `+0x40`; consumed count `+0x44`; presented-page count `+0x48`; native 64-bit timing base at `+0x4c` (high word `+0x50`). |
| Caption renderer | Line height `+0x48`; pen X/Y `+0x4c/+0x50`; main cursor `+0x58`; insertion cursor `+0x5c`; source mode `+0x60`; alignment `+0x64`; main byte-string pointer `+0x68`; four insertion-source pointers follow. |
| Decoder | Reader pointer and separately owned frame/plane/audio/scratch/index storage. Reader and decoder allocations are different objects. |
| File reader | Native allocation is `0x14` bytes: vtable, file size, file position, borrowed file context at `+0x0c`, and pending state byte at `+0x10`. |

Scene `active==2` means its task has finished. Playback `phase==2` is the active
movie loop. A subtitle renderer's `+0x48` is line height, while a timer's `+0x48`
is the displayed-page counter. These values are not interchangeable.
`IsCurrentMovieScenePlaying` obtains work from the currently executing TaskObject;
its caller must be the movie task. It is not a globally safe decoder query.

`GetMoviePresentedFrameCount` follows the playback-global timer pointer and returns
-1 if it is null. Its counter advances when the VBlank callback actually swaps a
displayed framebuffer page. `DecodeMovieFrameAndAdvanceCounter` increments the
timer's decode-attempt word after its attempted decoder operation even when the
normalized operation result is false. Do not turn that word into a count of
successfully decoded frames without a separate behavior change.

The alarm uses consumed-frame count and its own timing base to calculate native
integer deadlines. The raw decoder time-base word feeds playback setup, which can
rescale it when audio is present. Its exact format scale is not established here;
do not silently interpret it as FPS, milliseconds or a host clock duration.

## Scene lifecycle, fade and transfer completion

`CreateMovieSceneTask` stores the task created with the exact movie descriptor and
forwarded caller argument. `RequestMovieSceneStart` queues sound kind 3 with value
20 and sets the scene's `u16 active` to 1; it does not allocate/open a decoder.
The scene interface installs `MovieSceneUpdateNoOp`, while the TaskObject's state
callback drives playback. When the state callback returns `MovieSceneStateNoOp`,
the scheduler installs it; that callback's zero return then retains itself.
Zero is not a movie failure status.

The close adapter only skips destruction when the stored handle is exactly -1.
Its cleanup releases caption glyph-cache entries, the font backing resource and
script-VM storage, clears movie script group 3 and the work global, and sets the
handle to -1. The destroy adapter does not independently rewrite the handle.

`SetupMovieDisplayAtFullFade` processes each display separately: cached brightness
-16 or +16 is retained, any other value becomes -16. It then resets display state,
sets up the movie screen hardware and sets power-control bit `0x8000`.
The cached values, later register publication and hardware setup remain separate
operations. `IsMovieFadeOutComplete` merely tests signed fade level >=16; it does
not advance a fade. The updater increments levels below 16, and its negative-level
path waits for a positive presented-frame count before selecting zero brightness.

`UpdateMovieTransfersFadeAndSound` returns immediately when movie work is absent.
Otherwise it services VRAM transfers only when work byte `+0x8b5` is nonzero,
clears that byte after the transfer call, then updates fade and sound.

`IsMovieCaptionTransferFlagClear` reads exactly that byte and returns true iff
it is zero; it does not wait or guard against absent work. The paired script
resume `MovieScriptWait_CaptionTransferFlagClear` normalizes this predicate to
1/0. The previous helper name `IsMoviePlaybackIdle` incorrectly implied decoder
or scene idleness. Neither corrected name promises that playback stopped or that
every hardware operation is complete.

## Movie script commands and returns

`gStreamScriptCommandHandlers` is installed as field/panel ScriptVm group 3. Its
12 native function words represent six run/resume pairs:

| Entry | Run | Resume |
|---:|---|---|
|0|`StartSubtitlePlaybackAndReturnState6`|None|
|1|`MovieScriptCmd_SetCaptionText`|None|
|2|`MovieScriptCmd_OpenCaptionScreen`|None|
|3|`MovieScriptCmd_WaitPresentedFrame`|`MovieScriptWait_PresentedFrame`|
|4|`MovieScriptCmd_CommitCaptionText`|`MovieScriptWait_CaptionTransferFlagClear`|
|5|`CmdPrepareStream_020a7a08`|None|

Use the existing field/panel ScriptVm protocol, not overlay021's stage-script
result enum. In ordinary main-slot execution, run result 1 advances the cursor;
result 0 yields at the same command and registers its paired resume. A main resume
result 0 keeps waiting and 1 advances. The auxiliary-slot path has its own handling
and advances after installing a waiter. Command results do not indicate successful
movie opening, playback, text fitting or asynchronous I/O.

The open-caption-screen and set-caption-text commands resolve a pointer through
`ByteCode_ResolveOperand`; they do not read an integer frame target. The frame-wait
command does read an integer, stores it as the VM resume argument, and checks the
current movie task's playback phase. While phase 2 persists, a requested target 0
keeps waiting; otherwise the signed presented count is compared with the target.
Outside phase 2 the waiter returns 1. It polls displayed-page count, not decoded
or subtitle-line progress. The wait command's nested legacy declarations still
need typed ABI recovery; do not invent an additional movie handle from leftover
register values.

The set-text path uses `strcpy` into the task's current caption bytes at `+0x8c0`.
Commit copies that string to the saved buffer at `+0x9c0`, draws the current text,
and sets the pending-transfer byte. The two native buffers are each `0x100` bytes;
there is no bounded-copy or truncation promise in these helpers. Input text only
needs to survive the copy, while the scene owns its retained strings. Commit's
run result is 0 so its paired transfer-flag waiter can resume the script.

## Caption byte format, layout and lifetimes

The movie caption parser reads a main **byte** source and four insertion sources.
Printable ASCII and the implemented two-/three-byte UTF-8 forms produce 16-bit
glyph values. Native control bytes select insertion sources, change layout or
advance lines. This is the observed caption format, not unrestricted UTF-8 or a
complete Unicode validator; do not infer UTF-16 storage from the 16-bit glyph
value. The separate small language prompt is explicitly converted by
`Utf8ToUcs2` before the normal text drawing call.

`HasMovieSubtitleCodeUnit` tests main `text[cursor]!=0` in source mode 0, returns
true for modes 1 through 4, and false for other modes. Insertion mode true is
parser state, not proof of a visible glyph: the parser can encounter its terminator
and switch back to main mode.

Alignment mode 0 places pen X at zero. Mode 1 measures the first line, centers it,
clamps a negative origin to zero and caches that origin in the existing shared
movie storage; continuation lines reuse the cached value. Mode 2 right-aligns
without the same negative clamp. Other modes leave the pen unchanged. The setter
only writes the mode; it does not recompute pen position or make text visible.
`MeasureSubtitleLinesMaxAndResetCursor` recursively preserves the widest measured
line, applies its signed minimum-width argument and resets the main cursor.
It is not a pure measurement getter.

`DrawMovieSubtitleText` temporarily installs the caller's main text pointer and
runs the parser until `HasMovieSubtitleCodeUnit` is false. The glyph helper's BOOL
is ignored, so draining input does not guarantee all glyphs were rendered or fit.
Afterward it clears main text pointer `+0x68`, main cursor `+0x58` and source mode
`+0x60`, and sets renderer dirty word `+0x44`. It does not clear every insertion
pointer, alternate cursor or pen field. Main text and insertion sources are
borrowed while consumed; glyph-cache nodes and payloads are separately owned.

`ReleaseMovieCaptionGlyphCache` walks the list at renderer `+4`, frees each payload
at node `+0x24` and each node, and forwards the cleanup's native result 1. Its old
pointer return is not a live owned object. It frees neither the renderer nor its
outer task work, and it does not clear the list links. The native task cleanup
releases the font resource after this cache teardown.

## Decoder format and audio quantities

The existing decoder constructor reads a `0x30`-byte header into its format view.
Its observed acceptance checks are literal: initial bytes `MODSN`, version ASCII
`2` or `3`, the header's checked 16-bit field equal to decimal 10, audio kind in
0..4, width no greater than `0x100`, and at least six requested frame slots.
The `N3` path reads extension tag/skip fields and seeks until tag `HE`. Other
height, track, offset, arithmetic and allocation assumptions remain native;
these checks do not establish a complete general-purpose file validator.
The current playback factory requests ten frame slots.

Decoder `+0x20` is the raw audio sample-rate word. `GetMovieAudioBlockSamples`
returns 0 when that word is zero; otherwise it returns 128 if word `+0x28` is
nonzero and 256 if it is zero. Playback's private field called `channels` holds
this **samples-per-block** quantity: the stereo flush uses it for copy/cache-store
lengths and ring movement. Actual audio-track count is separate. Do not reinterpret
128/256 as framebuffer bits or a channel count.

The nullable queue, decode, render and drop adapters return true only when the
underlying result is exactly 1; every other status becomes false. They do not
propagate the decoder's full status space. Rendering needs four logical inputs:
decoder, destination, destination stride in pixels and render mode. The stride
becomes bytes for `MobiClip_BlitRows`; the frame-alarm caller passes 256 and mode 0.
The old one-input wrapper declaration leaves R1/R2/R3 live and is not a finished
portable rendering interface.

`GetMovieLookupTableArenaCapacity` returns `0x2580`, or 9,600 bytes. Setup caps its
DTCM-backed lookup arena with this value. It is distinct from decoder code size,
frame allocations and any claimed total movie memory requirement.

## Allocation, reader I/O and destruction

`MovieAllocAligned32` receives a byte size in R0 and calls the default exp-heap
allocator with alignment 32. The decoder and file-reader allocation adapters
remain distinct entrypoints even though they forward to it; the native factory
uses `0xd8` and `0x14` bytes respectively. Several matched adapters omit the real
input in their C declaration. The deallocation adapters consume the allocation
pointer in R0; an old pointer-shaped or residual return does not establish a new
success result.

Reader nondeleting destructors are empty. Their deleting forms free the outer
object and retain its original pointer word as a destructor ABI return; that word
is not a live pointer for later use. Preserve both vtable entries rather than
substituting null or folding their call identities.

`WaitMovieReaderPendingIo` calls `FS_WaitAsync` only for pending byte ==1, ignores
the wait result, and clears the byte afterward; other byte values are cleared
without waiting. The reader's virtual Close dispatch delegates through its
`+0x14` virtual entry to this wait. It does not call `FS_CloseFile`.
Decoder internal cleanup calls that Close, deletes the reader and frees its owned
frame state, plane tables/planes, working planes, two scratch buffers, index and
audio-track storage. `DeleteMovieDecoder` then frees the decoder allocation.
The outer `StopMoviePlayback` routine closes the file-bank handle afterward,
then frees timer/other playback storage. File context, reader object, decoder
buffers and playback-global timer/audio owners therefore have distinct lifetimes.
The decoder's cached code/table pointers are not all per-decoder allocations.
Native arena setup backs up the reused decoder-code region into a heap buffer.
The shutdown helper currently named `FreeMovieFileBuffer` copies that backup back
to the original code address with `MI_CpuCopy8`, then frees the backup. It is not
merely an independent file-data allocation; preserve this ownership/restoration
boundary when replacing the platform-specific code arena.

## Entrypoint inventory

Each identity below is EU `ov022:address`, with its configured native mode and
extent. Target wrapper paths are the intended post-rename names; shared US
filename suffixes are not EU identities. Existing C/C++ consumers and vtables must
be updated by the normal repository renamer and checked separately. Logical
inputs here do not authorize register-forcing parameters or prototype rewrites.

| EU identity | Mode / bytes | Name | Inputs and return | Target wrapper |
|---|---|---|---|---|
| `ov022:020a6f44` | arm / 68 | `UpdateMovieTransfersFadeAndSound` | none; uses exact movie-work global -> void | `eu/src/overlays/ov022/calls/UpdateMovieTransfersFadeAndSound.c` |
| `ov022:020a73f8` | arm / 28 | `IsCurrentMovieScenePlaying` | none; current TaskObject must be the movie task -> BOOL: phase+0x8b0 == 2 | `eu/src/overlays/ov022/calls/IsCurrentMovieScenePlaying.c` |
| `ov022:020a7414` | arm / 32 | `IsMovieFadeOutComplete` | none; movie-work global -> BOOL: signed fadeLevel+0x8b8 >= 16 | `eu/src/overlays/ov022/calls/IsMovieFadeOutComplete.c` |
| `ov022:020a77b0` | arm / 8 | `MovieSceneStateNoOp` | no logical input consumed -> 0 / NULL state replacement | `eu/src/overlays/ov022/auto/MovieSceneStateNoOp.c` |
| `ov022:020a77b8` | arm / 88 | `SetupMovieDisplayAtFullFade` | none -> void | `eu/src/overlays/ov022/calls/SetupMovieDisplayAtFullFade.c` |
| `ov022:020a7810` | arm / 36 | `CreateMovieSceneTask` | caller argument forwarded to movie descriptor constructor -> void | `eu/src/overlays/ov022/calls/CreateMovieSceneTask.c` |
| `ov022:020a7834` | arm / 32 | `DestroyMovieSceneTaskIfSet` | none; stored movie task handle -> void | `eu/src/overlays/ov022/calls/DestroyMovieSceneTaskIfSet.c` |
| `ov022:020a7854` | arm / 36 | `RequestMovieSceneStart` | none -> void | `eu/src/overlays/ov022/calls/RequestMovieSceneStart.c` |
| `ov022:020a7878` | arm / 4 | `MovieSceneUpdateNoOp` | none -> void | `eu/src/overlays/ov022/auto/MovieSceneUpdateNoOp.c` |
| `ov022:020a787c` | arm / 32 | `IsMovieSceneFinished` | none -> BOOL: active u16 == 2 | `eu/src/overlays/ov022/calls/IsMovieSceneFinished.c` |
| `ov022:020a795c` | thumb / 14 | `MovieScriptCmd_OpenCaptionScreen` | ScriptVm*, operand buffer resolved as a pointer -> script run result 1 | `eu/src/overlays/ov022/calls/MovieScriptCmd_OpenCaptionScreen.c` |
| `ov022:020a7978` | thumb / 54 | `MovieScriptCmd_WaitPresentedFrame` | ScriptVm*, integer target operand -> 1 outside playing phase or at reached signed target; otherwise 0 | `eu/src/overlays/ov022/calls/MovieScriptCmd_WaitPresentedFrame.c` |
| `ov022:020a79b0` | thumb / 40 | `MovieScriptWait_PresentedFrame` | unused VM word, saved signed target -> 1 outside phase 2;0 for target 0; otherwise presented>=target | `eu/src/overlays/ov022/calls/MovieScriptWait_PresentedFrame.c` |
| `ov022:020a79d8` | thumb / 14 | `MovieScriptCmd_SetCaptionText` | ScriptVm*, operand buffer resolved as text pointer -> script run result 1 | `eu/src/overlays/ov022/calls/MovieScriptCmd_SetCaptionText.c` |
| `ov022:020a79e8` | thumb / 10 | `MovieScriptCmd_CommitCaptionText` | no logical input consumed -> script run result 0 | `eu/src/overlays/ov022/calls/MovieScriptCmd_CommitCaptionText.c` |
| `ov022:020a79f4` | thumb / 18 | `MovieScriptWait_CaptionTransferFlagClear` | resume inputs unused -> script resume result 1 iff movieWork+0x8b5 is0, else0 | `eu/src/overlays/ov022/calls/MovieScriptWait_CaptionTransferFlagClear.c` |
| `ov022:020a7a1c` | arm / 16 | `MovieAllocAligned32` | byte size in R0 -> allocated pointer / allocator result | `eu/src/overlays/ov022/calls/MovieAllocAligned32.c` |
| `ov022:020a7a2c` | arm / 12 | `MovieFree` | allocation pointer in R0 despite empty declaration -> logical deallocation; old pointer return is not a portable result | `eu/src/overlays/ov022/calls/MovieFree.c` |
| `ov022:020a809c` | arm / 32 | `DecodeMovieFrameAndAdvanceCounter` | MovieFrameTimer* -> void | `eu/src/overlays/ov022/calls/DecodeMovieFrameAndAdvanceCounter.c` |
| `ov022:020a8a64` | arm / 12 | `ReleaseMovieCaptionGlyphCache` | caption renderer in R0 despite empty declaration -> forwards list cleanup result 1; old pointer return is not a live object | `eu/src/overlays/ov022/calls/ReleaseMovieCaptionGlyphCache.c` |
| `ov022:020a8a90` | arm / 8 | `SetMovieSubtitleAlignment` | renderer, mode word -> native renderer word in R0, unused by typed callers | `eu/src/overlays/ov022/auto/SetMovieSubtitleAlignment.c` |
| `ov022:020a8ef8` | arm / 36 | `MeasureSubtitleLinesMaxAndResetCursor` | renderer, signed minimum width -> signed max(measured width, minimum) | `eu/src/overlays/ov022/calls/MeasureSubtitleLinesMaxAndResetCursor.c` |
| `ov022:020a9118` | arm / 84 | `DrawMovieSubtitleText` | renderer, borrowed byte-string pointer -> void | `eu/src/overlays/ov022/calls/DrawMovieSubtitleText.c` |
| `ov022:020a9294` | arm / 20 | `DeleteMovieFileReader` | reader this pointer -> original now-freed pointer word (destructor ABI) | `eu/src/overlays/ov022/calls/DeleteMovieFileReader.c` |
| `ov022:020a92a8` | arm / 32 | `DeleteMovieDecoder` | decoder pointer -> void | `eu/src/overlays/ov022/calls/DeleteMovieDecoder.c` |
| `ov022:020a92c8` | arm / 24 | `GetMovieAudioSampleRateIfPresent` | nullable decoder -> 0 if null, otherwise raw sample-rate word | `eu/src/overlays/ov022/calls/GetMovieAudioSampleRateIfPresent.c` |
| `ov022:020a92e0` | arm / 24 | `GetMovieFrameTimeBaseIfPresent` | nullable decoder -> 0 if null, otherwise raw time-base word | `eu/src/overlays/ov022/calls/GetMovieFrameTimeBaseIfPresent.c` |
| `ov022:020a92f8` | arm / 24 | `GetMovieAudioBlockSamplesIfPresent` | nullable decoder -> 0 if null, otherwise 0/128/256 samples | `eu/src/overlays/ov022/calls/GetMovieAudioBlockSamplesIfPresent.c` |
| `ov022:020a9310` | arm / 36 | `QueueMovieFrameIfPresent` | nullable decoder -> BOOL: nonnull and queue result exactly 1 | `eu/src/overlays/ov022/calls/QueueMovieFrameIfPresent.c` |
| `ov022:020a9334` | arm / 36 | `DecodeMovieFrameIfPresent` | nullable decoder -> BOOL: nonnull and decode result exactly 1 | `eu/src/overlays/ov022/calls/DecodeMovieFrameIfPresent.c` |
| `ov022:020a9358` | arm / 36 | `RenderMovieFrameIfPresent` | nullable decoder, destination, destination stride in pixels, render mode -> BOOL: nonnull and render result exactly 1 | `eu/src/overlays/ov022/calls/RenderMovieFrameIfPresent.c` |
| `ov022:020a937c` | arm / 36 | `DropMovieFrameIfPresent` | nullable decoder -> BOOL: nonnull and drop result exactly 1 | `eu/src/overlays/ov022/calls/DropMovieFrameIfPresent.c` |
| `ov022:020a93a0` | arm / 24 | `GetMoviePendingAudioBlocksIfPresent` | nullable decoder -> 0 if null, otherwise current chunk audio-block count | `eu/src/overlays/ov022/calls/GetMoviePendingAudioBlocksIfPresent.c` |
| `ov022:020a93dc` | arm / 4 | `MovieBaseReaderDestructorNoOp` | reader this pointer not consumed -> logical destructor void; body empty | `eu/src/overlays/ov022/auto/MovieBaseReaderDestructorNoOp.c` |
| `ov022:020a93e0` | arm / 20 | `DeleteMovieBaseReader` | base-reader this pointer -> original now-deallocated pointer word | `eu/src/overlays/ov022/calls/DeleteMovieBaseReader.c` |
| `ov022:020a93f4` | arm / 12 | `AllocMovieDecoderAligned32` | byte size in R0 despite empty declaration -> allocated pointer | `eu/src/overlays/ov022/calls/AllocMovieDecoderAligned32.c` |
| `ov022:020a9400` | arm / 12 | `FreeMovieDecoder` | allocation pointer in R0 despite empty declaration -> logical free; native residual word not a stable result | `eu/src/overlays/ov022/calls/FreeMovieDecoder.c` |
| `ov022:020a9b64` | arm / 8 | `GetMovieAudioSampleRate` | valid decoder pointer -> u32 word at+0x20 | `eu/src/overlays/ov022/auto/GetMovieAudioSampleRate.c` |
| `ov022:020a9b6c` | arm / 8 | `GetMovieFrameTimeBase` | valid decoder pointer -> u32 word at+0x18 | `eu/src/overlays/ov022/auto/GetMovieFrameTimeBase.c` |
| `ov022:020a9f78` | arm / 16 | `GetMoviePendingAudioBlocks` | valid decoder pointer -> word from+0x88 indexed by current parity+0x90 | `eu/src/overlays/ov022/auto/GetMoviePendingAudioBlocks.c` |
| `ov022:020aa138` | arm / 12 | `AllocMovieFileReaderAligned32` | byte size in R0 despite empty declaration -> allocated pointer | `eu/src/overlays/ov022/calls/AllocMovieFileReaderAligned32.c` |
| `ov022:020aa144` | arm / 12 | `FreeMovieFileReader` | allocation pointer in R0 despite empty declaration -> logical free; native residual word not a stable result | `eu/src/overlays/ov022/calls/FreeMovieFileReader.c` |
| `ov022:020aa2c0` | arm / 40 | `WaitMovieReaderPendingIo` | reader pointer -> void; FS wait result discarded | `eu/src/overlays/ov022/calls/WaitMovieReaderPendingIo.c` |
| `ov022:020aa2fc` | arm / 4 | `MovieFileReaderDestructorNoOp` | reader this pointer not consumed -> logical destructor void; body empty | `eu/src/overlays/ov022/auto/MovieFileReaderDestructorNoOp.c` |
| `ov022:020aa8cc` | arm / 8 | `GetMovieLookupTableArenaCapacity` | none -> u32 constant 0x2580 (9600 bytes) | `eu/src/overlays/ov022/auto/GetMovieLookupTableArenaCapacity.c` |
| `ov022:020a8f1c` | arm / 152 | `UpdateMovieSubtitleLineAlignment` | renderer pointer -> void | `eu/src/overlays/ov022/calls/UpdateMovieSubtitleLineAlignment.c` |
| `ov022:020a90c8` | arm / 80 | `HasMovieSubtitleCodeUnit` | renderer pointer -> BOOL: mode 0 tests main byte at cursor; modes 1..4 true; others false | `eu/src/overlays/ov022/calls/HasMovieSubtitleCodeUnit.c` |
| `ov022:020a8938` | arm / 28 | `GetMoviePresentedFrameCount` | none -> signed presented counter, or -1 when main timer is null | `eu/src/overlays/ov022/calls/GetMoviePresentedFrameCount.c` |
| `ov022:020a9b74` | arm / 36 | `GetMovieAudioBlockSamples` | valid decoder pointer -> 0 if sample-rate word +0x20==0; otherwise 128 if word +0x28!=0 else 256 | `eu/src/overlays/ov022/auto/GetMovieAudioBlockSamples.c` |
| `ov022:020a791c` | arm / 32 | `IsMovieCaptionTransferFlagClear` | none; exact movie-work global -> BOOL: pending-transfer byte +0x8b5 == 0 | `eu/src/overlays/ov022/calls/IsMovieCaptionTransferFlagClear.c` |

## Source evidence and remaining ABI boundaries

The block contains 45 address-name replacements and five corrections of existing
descriptive names. The wrappers above, interpreted through their EU aliases, provide direct evidence
for every operation. The paired owners and consumers are established by these
repository sources:

- `eu/src/overlays/ov022/calls/RunMoviePlaybackState.c`,
  `eu/src/overlays/ov022/calls/InitMovieSceneCallbacks.c` and
  `src/arm9/shared_engine/Obj_UpdateAll_0202a644.c`: scene phases, callback slots
  and zero/nonzero task-state replacement.
- `src/ov022/video_playback/OpenMoviePlayback_020a8338.c`,
  `src/ov022/movie/movie_frame_alarm_callback_020a7f3c.c` and
  `src/ov022/video_playback/SwapCaptionPagesOnVBlank_020a8154.c`:
  audio/timer owners and distinct counters.
- `src/ov022/video_playback/UpdateMovieFadeOut_020a6ec0.c` and
  `eu/src/overlays/ov022/calls/IsMovieCaptionTransferFlagClear.c` and
  `src/ov022/video_playback/IsMoviePlaybackIdle_020a78fc.c`: exact fade and
  transfer-byte predicates; the shared source's legacy playing label is not
  evidence for decoder/playback idleness.
- `eu/src/overlays/ov022/data/tables/gStreamScriptCommandHandlers.c`,
  `src/ov022/video_playback/SetMovieStateText_020a791c.c` and
  `src/ov022/video_playback/CommitMovieStateText_020a78c8.c`:
  run/resume pairing and current/saved text.
- `src/ov022/video_playback/decodeMovieSubtitleCodeUnit_020a8b90.c`,
  `src/ov022/video_playback/HandleMovieStreamEvent_020a8acc.c`,
  `src/ov022/video_playback/DrawNextSubtitleGlyph_020a8f94.c`,
  `eu/src/overlays/ov022/calls/MeasureMovieSubtitleWidth_020a8d00.c` and
  `eu/src/overlays/ov003/calls/MeasureMovieSubtitleWidth.c`:
  actual byte parser, insertion sources, width recursion and drawing.
- `src/ov022/video_playback/initializeMovieDecodeContext_020a9430.cpp`,
  `src/ov022/video_playback/createMovieStream_020a91a0.cpp` and
  `src/ov022/video_playback/releaseMovieDecodeContext_020a99dc.cpp`:
  header checks, native allocations and internal destruction.
- `src/ov022/audio/flushPendingStereoAudioBlocks_020a809c.c`,
  `src/ov022/video_playback/renderDecodedMovieFrame_020a9d94.c` and
  `eu/libs/mobiclip/video/asm_stubs/auto/MobiClip_BlitRows.s`:
  block-sample meaning and destination stride conversion.
- `eu/src/overlays/ov022/data/tables/gStreamIoCallbacks.c`,
  `eu/src/overlays/ov022/data/tables/gStreamStateHandlers.c`,
  `src/ov022/shared_engine/CallVirt14_020aa2c8.c` and
  `src/ov022/video_playback/StopMoviePlayback_020a8674.c`:
  destructor/Close dispatch and the separate outer file close.
- `src/arm9/record_management/DestroyFndObjectList_020014f0.c` and
  `src/ov022/video_playback/InitMovieOverlayState_020a722c.c`:
  glyph-cache child ownership and task teardown order.
- `src/ov022/video_playback/SetupMovieDecoderArenas_020a8264.c`,
  `src/ov022/video_playback/FreeMovieFileBuffer_020a82f4.c` and
  `eu/src/overlays/ov022/calls/FreeMovieFileBuffer.c`:
  lookup-arena capacity, code backup/restore and the real copy-helper alias.

Remaining Native ABI work includes omitted allocator/free inputs, the render
wrapper's live extra registers, the width helper's renderer argument, legacy
wait-setup return declarations and C++ destructor/vtable types. Existing native
integer/pointer declarations must not be copied as a portable API solely because
their instruction sequence matches. Recover typed interfaces and validate those
changes separately; the checks below establish byte-exact preservation for this naming block.

## Reproducible byte-exact validation

Run from `eu/`. The 50 renamed entrypoints and the shared C++ stream constructor
pass the official verifier, with their native ARM/Thumb modes:

```sh
python tools/verify_idx.py src/overlays/ov022/calls/UpdateMovieTransfersFadeAndSound.c UpdateMovieTransfersFadeAndSound
python tools/verify_idx.py src/overlays/ov022/calls/IsCurrentMovieScenePlaying.c IsCurrentMovieScenePlaying
python tools/verify_idx.py src/overlays/ov022/calls/IsMovieFadeOutComplete.c IsMovieFadeOutComplete
python tools/verify_idx.py src/overlays/ov022/auto/MovieSceneStateNoOp.c MovieSceneStateNoOp
python tools/verify_idx.py src/overlays/ov022/calls/SetupMovieDisplayAtFullFade.c SetupMovieDisplayAtFullFade
python tools/verify_idx.py src/overlays/ov022/calls/CreateMovieSceneTask.c CreateMovieSceneTask
python tools/verify_idx.py src/overlays/ov022/calls/DestroyMovieSceneTaskIfSet.c DestroyMovieSceneTaskIfSet
python tools/verify_idx.py src/overlays/ov022/calls/RequestMovieSceneStart.c RequestMovieSceneStart
python tools/verify_idx.py src/overlays/ov022/auto/MovieSceneUpdateNoOp.c MovieSceneUpdateNoOp
python tools/verify_idx.py src/overlays/ov022/calls/IsMovieSceneFinished.c IsMovieSceneFinished
python tools/verify_idx.py src/overlays/ov022/calls/MovieScriptCmd_OpenCaptionScreen.c MovieScriptCmd_OpenCaptionScreen --thumb
python tools/verify_idx.py src/overlays/ov022/calls/MovieScriptCmd_WaitPresentedFrame.c MovieScriptCmd_WaitPresentedFrame --thumb
python tools/verify_idx.py src/overlays/ov022/calls/MovieScriptWait_PresentedFrame.c MovieScriptWait_PresentedFrame --thumb
python tools/verify_idx.py src/overlays/ov022/calls/MovieScriptCmd_SetCaptionText.c MovieScriptCmd_SetCaptionText --thumb
python tools/verify_idx.py src/overlays/ov022/calls/MovieScriptCmd_CommitCaptionText.c MovieScriptCmd_CommitCaptionText --thumb
python tools/verify_idx.py src/overlays/ov022/calls/MovieScriptWait_CaptionTransferFlagClear.c MovieScriptWait_CaptionTransferFlagClear --thumb
python tools/verify_idx.py src/overlays/ov022/calls/MovieAllocAligned32.c MovieAllocAligned32
python tools/verify_idx.py src/overlays/ov022/calls/MovieFree.c MovieFree
python tools/verify_idx.py src/overlays/ov022/calls/DecodeMovieFrameAndAdvanceCounter.c DecodeMovieFrameAndAdvanceCounter
python tools/verify_idx.py src/overlays/ov022/calls/ReleaseMovieCaptionGlyphCache.c ReleaseMovieCaptionGlyphCache
python tools/verify_idx.py src/overlays/ov022/auto/SetMovieSubtitleAlignment.c SetMovieSubtitleAlignment
python tools/verify_idx.py src/overlays/ov022/calls/MeasureSubtitleLinesMaxAndResetCursor.c MeasureSubtitleLinesMaxAndResetCursor
python tools/verify_idx.py src/overlays/ov022/calls/DrawMovieSubtitleText.c DrawMovieSubtitleText
python tools/verify_idx.py src/overlays/ov022/calls/DeleteMovieFileReader.c DeleteMovieFileReader
python tools/verify_idx.py src/overlays/ov022/calls/DeleteMovieDecoder.c DeleteMovieDecoder
python tools/verify_idx.py src/overlays/ov022/calls/GetMovieAudioSampleRateIfPresent.c GetMovieAudioSampleRateIfPresent
python tools/verify_idx.py src/overlays/ov022/calls/GetMovieFrameTimeBaseIfPresent.c GetMovieFrameTimeBaseIfPresent
python tools/verify_idx.py src/overlays/ov022/calls/GetMovieAudioBlockSamplesIfPresent.c GetMovieAudioBlockSamplesIfPresent
python tools/verify_idx.py src/overlays/ov022/calls/QueueMovieFrameIfPresent.c QueueMovieFrameIfPresent
python tools/verify_idx.py src/overlays/ov022/calls/DecodeMovieFrameIfPresent.c DecodeMovieFrameIfPresent
python tools/verify_idx.py src/overlays/ov022/calls/RenderMovieFrameIfPresent.c RenderMovieFrameIfPresent
python tools/verify_idx.py src/overlays/ov022/calls/DropMovieFrameIfPresent.c DropMovieFrameIfPresent
python tools/verify_idx.py src/overlays/ov022/calls/GetMoviePendingAudioBlocksIfPresent.c GetMoviePendingAudioBlocksIfPresent
python tools/verify_idx.py src/overlays/ov022/auto/MovieBaseReaderDestructorNoOp.c MovieBaseReaderDestructorNoOp
python tools/verify_idx.py src/overlays/ov022/calls/DeleteMovieBaseReader.c DeleteMovieBaseReader
python tools/verify_idx.py src/overlays/ov022/calls/AllocMovieDecoderAligned32.c AllocMovieDecoderAligned32
python tools/verify_idx.py src/overlays/ov022/calls/FreeMovieDecoder.c FreeMovieDecoder
python tools/verify_idx.py src/overlays/ov022/auto/GetMovieAudioSampleRate.c GetMovieAudioSampleRate
python tools/verify_idx.py src/overlays/ov022/auto/GetMovieFrameTimeBase.c GetMovieFrameTimeBase
python tools/verify_idx.py src/overlays/ov022/auto/GetMoviePendingAudioBlocks.c GetMoviePendingAudioBlocks
python tools/verify_idx.py src/overlays/ov022/calls/AllocMovieFileReaderAligned32.c AllocMovieFileReaderAligned32
python tools/verify_idx.py src/overlays/ov022/calls/FreeMovieFileReader.c FreeMovieFileReader
python tools/verify_idx.py src/overlays/ov022/calls/WaitMovieReaderPendingIo.c WaitMovieReaderPendingIo
python tools/verify_idx.py src/overlays/ov022/auto/MovieFileReaderDestructorNoOp.c MovieFileReaderDestructorNoOp
python tools/verify_idx.py src/overlays/ov022/auto/GetMovieLookupTableArenaCapacity.c GetMovieLookupTableArenaCapacity
python tools/verify_idx.py src/overlays/ov022/calls/UpdateMovieSubtitleLineAlignment.c UpdateMovieSubtitleLineAlignment
python tools/verify_idx.py src/overlays/ov022/calls/HasMovieSubtitleCodeUnit.c HasMovieSubtitleCodeUnit
python tools/verify_idx.py src/overlays/ov022/calls/GetMoviePresentedFrameCount.c GetMoviePresentedFrameCount
python tools/verify_idx.py src/overlays/ov022/auto/GetMovieAudioBlockSamples.c GetMovieAudioBlockSamples
python tools/verify_idx.py src/overlays/ov022/calls/IsMovieCaptionTransferFlagClear.c IsMovieCaptionTransferFlagClear
python tools/verify_idx.py src/overlays/ov022/calls/createMovieStream.cpp createMovieStream
bash tools/gate.sh
```

The fresh official gate passes all 108 linked modules. Affected function bytes,
resolved relocation targets/types and addends, and all module hashes match the
preserved pre-rename baseline. Shared C++ aliases retain their reference-region
macro identifiers and map only their EU targets; this also preserves the
constructor's decoder-free target rather than the same-address EU reader-delete
entrypoint. No shared US body is changed.
