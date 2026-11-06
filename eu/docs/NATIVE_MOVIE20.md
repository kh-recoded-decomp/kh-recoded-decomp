# Movie DATA and skip prompts (EU)

Pinned review baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. This block names 19 numeric DATA symbols and corrects one descriptive table name. Native source paths, declarations, object boundaries, bytes and relocations stay intact. Official matching belongs to integration; this review did not run a compiler or gate.

## Owners and data spans

The movie scene task, playback timer/audio, file/code-backup state and decoder cache arenas are separate owners. Their globals must not be merged into one portable movie object without preserving those lifetimes. The clamp table is a proven 384-byte logical byte span split across two existing symbols of 160 and 224 bytes. Keep that split in the native build.

The inherited `gStreamBufferTables` name is incorrect: `DrawMovieCaption` indexes six localized UTF-8 skip prompts by language and converts them with `Utf8ToUcs2`. The replacement name is `gMovieSkipPromptByLanguage`; the six strings retain every game-font glyph code, NUL and padding byte.

## Inventory and evidence

### `ov022:020b76a8` → `gMoviePixelClampTablePrefix`

Previous label `data_ov022_020b76a8`; existing ELF size **160 bytes**. Source: `eu/src/ov022/data/Rodata_ov022_020b76a8.c`.

160-byte initialized prefix of a logical 384-byte clamp table; the adjacent 224-byte tail is a distinct native symbol.

GetCachedPixelClampTable copies 0x180 bytes beginning here into the cache, or returns this address if the arena is too small. Reading both exact ROM slices gives table[i] = clamp(i-64,0,255) for 0<=i<384.

Limits: Do not resize this symbol to 384 bytes, merge the tail into it or change the existing u32 declaration. The copy range, not direct symbolic xrefs to the tail, establishes the shared table.

Pinned references:

- `eu/src/ov022/data/Rodata_ov022_020b76a8.c`; reference line(s) 71.
- `eu/src/overlays/ov022/calls/GetCachedPixelClampTable.c` → `src/ov022/video_playback/GetCachedPixelClampTable_020aaa58.c`; reference line(s) 3, 12, 16.

### `ov022:020b7748` → `gMoviePixelClampTableTail`

Previous label `data_ov022_020b7748`; existing ELF size **224 bytes**. Source: `eu/src/ov022/data/Rodata_ov022_020b76a8.c`.

224-byte initialized continuation of the clamp table beginning at 020b76a8; offset 160 in that logical table.

The 0x180-byte source span copied by GetCachedPixelClampTable contains both objects. Exact concatenated ROM bytes implement clamp(i-64,0,255); this tail starts with byte 96 and ends with saturation bytes 255.

Limits: A missing direct C reference to the tail is not evidence of unused storage. Preserve both native object boundaries and the generic multi-symbol source filename.

Pinned references:

- `eu/src/ov022/data/Rodata_ov022_020b76a8.c`; reference line(s) 54.
- `eu/src/overlays/ov022/calls/GetCachedPixelClampTable.c`; reference line(s) 12.

### `ov022:020b7828` → `gMoviePixelSaturationTable`

Previous label `data_ov022_020b7828`; existing ELF size **768 bytes**. Source: `eu/src/ov022/data/Rodata_ov022_020b76a8.c`.

768 initialized bytes, represented natively as u32[192].

get_cached_movie_saturation_table copies exactly 0x300 bytes from this object into its cache arena or returns the ROM address. Exact byte values implement clamp(floor((i-256)/8),0,31) over i=0..767.

Limits: The formula describes the existing bytes; this proposal does not replace the table with arithmetic or change the decoder interpretation of its index.

Pinned references:

- `eu/src/ov022/data/Rodata_ov022_020b76a8.c`; reference line(s) 3.
- `eu/src/overlays/ov022/calls/get_cached_movie_saturation_table.c` → `src/ov022/movie/get_cached_movie_saturation_table_020aa9e8.c`; reference line(s) 3, 12, 16.

### `ov022:020b7b28` → `gMovieAdpcmIndexAdjustments`

Previous label `data_ov022_020b7b28`; existing ELF size **16 bytes**. Source: `eu/src/ov022/data/Rodata_ov022_020b7b28.c`.

16 initialized signed-byte adjustment values, currently stored as four u32 words; the eight-value sequence [-1,-1,-1,-1,2,4,6,8] is duplicated.

decodeMovieAdpcmSamples indexes this table with the three low bits of each nibble and clamps the resulting step index to 0..0x58.

Limits: The visible decoder accesses indices 0..7. Preserve all 16 bytes and native C++ extern-C bindings; do not discard the repeated half or assume every possible decoder path was audited.

Pinned references:

- `eu/src/ov022/data/Rodata_ov022_020b7b28.c`; reference line(s) 18.
- `eu/src/overlays/ov022/calls/decodeMovieAdpcmSamples.cpp` → `src/ov022/video_playback/decodeMovieAdpcmSamples_020aaadc.cpp`; reference line(s) 19, 36, 69.

### `ov022:020b7b38` → `gMovieAdpcmStepSizeStorage`

Previous label `data_ov022_020b7b38`; existing ELF size **180 bytes**. Source: `eu/src/ov022/data/Rodata_ov022_020b7b28.c`.

180 initialized bytes: 89 signed 16-bit step sizes (178 bytes) followed by a zero halfword.

decodeMovieAdpcmSamples loads a signed halfword using the current index; it clamps updates to 0..88 and clamps samples to -32768..32767. Two nibbles produce two packed output samples.

Limits: Keep the final zero halfword and u32 source representation. The native declaration is not changed into a new 89-entry allocation.

Pinned references:

- `eu/src/ov022/data/Rodata_ov022_020b7b28.c`; reference line(s) 3.
- `eu/src/overlays/ov022/calls/decodeMovieAdpcmSamples.cpp` → `src/ov022/video_playback/decodeMovieAdpcmSamples_020aaadc.cpp`; reference line(s) 18, 35, 68.

### `ov022:020b7c00` → `gMovieSceneTaskHandle`

Previous label `data_ov022_020b7c00`; existing ELF size **4 bytes**. Source: `eu/src/ov022/data/Data_ov022_020b7c00.c`.

4-byte initialized task handle with inactive sentinel 0xffffffff.

CreateMovieSceneTask stores CreateTaskObject result using the neighboring class descriptor. DestroyMovieSceneTaskIfSet tests the sentinel and destroys the handle; the registered destructor clears scene globals and restores the sentinel.

Limits: Task object handle is separate from scene work and playback runtime globals. Preserve its raw word representation.

Pinned references:

- `eu/src/ov022/data/Data_ov022_020b7c00.c`; reference line(s) 16.
- `eu/src/overlays/ov022/calls/CreateMovieSceneTask.c` → `src/ov022/reviewed_helpers/func_ov022_020a77f0.c`; reference line(s) 3, 6.
- `eu/src/overlays/ov022/calls/DestroyMovieSceneTaskIfSet.c`; reference line(s) 2, 5.
- `eu/src/overlays/ov022/calls/InitMovieOverlayState.c` → `src/ov022/video_playback/InitMovieOverlayState_020a722c.c`; reference line(s) 8, 20.

### `ov022:020b7c04` → `gMoviePlaybackTaskClass`

Previous label `data_ov022_020b7c04`; existing ELF size **20 bytes**. Source: `eu/src/ov022/data/Data_ov022_020b7c00.c`.

20-byte class descriptor: packed class/subclass word 0x000d0008; StartMoviePlaybackState constructor at +4; InitMovieOverlayState destructor at +8; workSize 0xad4 at +0xc; NULL heapRef at +0x10.

CreateMovieSceneTask passes this descriptor to CreateTaskObject. The constructor publishes current task work and returns RunMoviePlaybackState; the destructor occupies the different +8 slot despite its inherited Init name.

Limits: The existing callback names are preserved by this DATA block. Do not infer that +8 is another constructor or the per-frame update.

Pinned references:

- `eu/src/ov022/data/Data_ov022_020b7c00.c`; reference line(s) 8.
- `eu/src/overlays/ov022/calls/CreateMovieSceneTask.c` → `src/ov022/reviewed_helpers/func_ov022_020a77f0.c`; reference line(s) 2, 6.

### `ov022:020b7c90` → `gMovieSkipPromptJapanese`

Previous label `data_ov022_020b7c90`; existing ELF size **28 bytes**. Source: `eu/src/ov022/data/Data_ov022_020b7c64.c`.

28 initialized bytes: NUL-terminated UTF-8 prompt plus preserved native padding. Decoded bytes: '㌶㍑㍗でスキップ'.

This object is pointer-table slot 0. DrawMovieCaption uses GetLanguageIndex to select that table entry, converts it with Utf8ToUcs2 and draws the result when hasCaption is nonzero.

Limits: The Unicode prefix contains game-font glyph codes; their button/icon roles are not inferred here. Preserve all bytes and padding; no retranslation or encoding conversion is proposed.

Pinned references:

- `eu/src/ov022/data/Data_ov022_020b7c64.c`; reference line(s) 12.
- `eu/src/overlays/ov022/data/tables/gStreamBufferTables.c`; reference line(s) 3, 11.

### `ov022:020b7c30` → `gMovieSkipPromptEnglish`

Previous label `data_ov022_020b7c30`; existing ELF size **16 bytes**. Source: `eu/src/ov022/data/Data_ov022_020b7c30.c`.

16 initialized bytes: NUL-terminated UTF-8 prompt plus preserved native padding. Decoded bytes: '㌶㍑㍗ Skip'.

This object is pointer-table slot 1. DrawMovieCaption uses GetLanguageIndex to select that table entry, converts it with Utf8ToUcs2 and draws the result when hasCaption is nonzero.

Limits: The Unicode prefix contains game-font glyph codes; their button/icon roles are not inferred here. Preserve all bytes and padding; no retranslation or encoding conversion is proposed.

Pinned references:

- `eu/src/ov022/data/Data_ov022_020b7c30.c`; reference line(s) 5.
- `eu/src/overlays/ov022/data/tables/gStreamBufferTables.c`; reference line(s) 4, 12.

### `ov022:020b7c50` → `gMovieSkipPromptFrench`

Previous label `data_ov022_020b7c50`; existing ELF size **20 bytes**. Source: `eu/src/ov022/data/Data_ov022_020b7c40.c`.

20 initialized bytes: NUL-terminated UTF-8 prompt plus preserved native padding. Decoded bytes: '㌶㍑㍗ Passer'.

This object is pointer-table slot 2. DrawMovieCaption uses GetLanguageIndex to select that table entry, converts it with Utf8ToUcs2 and draws the result when hasCaption is nonzero.

Limits: The Unicode prefix contains game-font glyph codes; their button/icon roles are not inferred here. Preserve all bytes and padding; no retranslation or encoding conversion is proposed.

Pinned references:

- `eu/src/ov022/data/Data_ov022_020b7c40.c`; reference line(s) 5.
- `eu/src/overlays/ov022/data/tables/gStreamBufferTables.c`; reference line(s) 5, 13.

### `ov022:020b7c78` → `gMovieSkipPromptGerman`

Previous label `data_ov022_020b7c78`; existing ELF size **24 bytes**. Source: `eu/src/ov022/data/Data_ov022_020b7c64.c`.

24 initialized bytes: NUL-terminated UTF-8 prompt plus preserved native padding. Decoded bytes: '㌶㍑㍗ Überspringen'.

This object is pointer-table slot 3. DrawMovieCaption uses GetLanguageIndex to select that table entry, converts it with Utf8ToUcs2 and draws the result when hasCaption is nonzero.

Limits: The Unicode prefix contains game-font glyph codes; their button/icon roles are not inferred here. Preserve all bytes and padding; no retranslation or encoding conversion is proposed.

Pinned references:

- `eu/src/ov022/data/Data_ov022_020b7c64.c`; reference line(s) 17.
- `eu/src/overlays/ov022/data/tables/gStreamBufferTables.c`; reference line(s) 6, 14.

### `ov022:020b7c40` → `gMovieSkipPromptItalian`

Previous label `data_ov022_020b7c40`; existing ELF size **16 bytes**. Source: `eu/src/ov022/data/Data_ov022_020b7c40.c`.

16 initialized bytes: NUL-terminated UTF-8 prompt plus preserved native padding. Decoded bytes: '㌶㍑㍗ Salta'.

This object is pointer-table slot 4. DrawMovieCaption uses GetLanguageIndex to select that table entry, converts it with Utf8ToUcs2 and draws the result when hasCaption is nonzero.

Limits: The Unicode prefix contains game-font glyph codes; their button/icon roles are not inferred here. Preserve all bytes and padding; no retranslation or encoding conversion is proposed.

Pinned references:

- `eu/src/ov022/data/Data_ov022_020b7c40.c`; reference line(s) 10.
- `eu/src/overlays/ov022/data/tables/gStreamBufferTables.c`; reference line(s) 7, 15.

### `ov022:020b7c64` → `gMovieSkipPromptSpanish`

Previous label `data_ov022_020b7c64`; existing ELF size **20 bytes**. Source: `eu/src/ov022/data/Data_ov022_020b7c64.c`.

20 initialized bytes: NUL-terminated UTF-8 prompt plus preserved native padding. Decoded bytes: '㌶㍑㍗: Saltar'.

This object is pointer-table slot 5. DrawMovieCaption uses GetLanguageIndex to select that table entry, converts it with Utf8ToUcs2 and draws the result when hasCaption is nonzero.

Limits: The Unicode prefix contains game-font glyph codes; their button/icon roles are not inferred here. Preserve all bytes and padding; no retranslation or encoding conversion is proposed.

Pinned references:

- `eu/src/ov022/data/Data_ov022_020b7c64.c`; reference line(s) 22.
- `eu/src/overlays/ov022/data/tables/gStreamBufferTables.c`; reference line(s) 8, 16.

### `ov022:020b7c18` → `gMovieSkipPromptByLanguage`

Previous label `gStreamBufferTables`; existing ELF size **24 bytes**. Source: `eu/src/overlays/ov022/data/tables/gStreamBufferTables.c`.

24-byte initialized array of six native pointers, ordered Japanese, English, French, German, Italian, Spanish.

DrawMovieCaption selects this table by GetLanguageIndex, calls Utf8ToUcs2 into a 0x40-u16 local buffer, then DrawTextAnchored. Each relocation points to one of the six proven prompt strings.

Limits: Corrects the existing misleading gStreamBufferTables name. These are text pointers, not buffer configurations. Preserve relocation expressions and generic source placement; no language bounds check is added.

Pinned references:

- `eu/src/overlays/ov022/calls/DrawMovieCaption.c` → `src/ov022/video_playback/DrawMovieCaption_020a6f68.c`; reference line(s) 14, 34.
- `eu/src/overlays/ov022/data/tables/gStreamBufferTables.c`; reference line(s) 10.

### `ov022:020b7cac` → `gMovieCaptionPalette`

Previous label `data_ov022_020b7cac`; existing ELF size **64 bytes**. Source: `eu/src/ov022/data/Data_ov022_020b7c64.c`.

64 initialized bytes, retained as native u32[16].

StartMoviePlaybackState calls GX_LoadBGPltt and GXS_LoadBGPltt with this address, destination offset 0x1a0 and byte length 0x40.

Limits: Both BG palette uploads use the same bytes. Do not infer a new color struct, memory lifetime or file-backed palette owner.

Pinned references:

- `eu/src/ov022/data/Data_ov022_020b7c64.c`; reference line(s) 5.
- `eu/src/overlays/ov022/calls/StartMoviePlaybackState.c` → `src/ov022/video_playback/StartMoviePlaybackState_020a7000.c`; reference line(s) 48, 95, 96.

### `ov022:020b7da0` → `gMovieSceneGlobals`

Previous label `data_ov022_020b7da0`; existing ELF size **8 bytes**. Source: `eu/src/overlays/ov022/data/bss/Bss_ov022_020b7da0.c`.

8-byte BSS object: scene task-work pointer at +0 and script-skip request word at +4.

StartMoviePlaybackState publishes current task work and clears the request word. RunMoviePlaybackState sets skipRequested in the demonstrated input paths; scene/caption/fade queries read the same owner.

Limits: This scene work pointer is not the decoder itself. Caption-transfer flag at work+0x8b5 is distinct from playback activity. Keep the word-sized request representation.

Pinned references:

- `eu/src/overlays/ov022/calls/CommitMovieStateText.c` → `src/ov022/video_playback/CommitMovieStateText_020a78c8.c`; reference line(s) 11, 17, 19.
- `eu/src/overlays/ov022/calls/DrawMovieCaption.c` → `src/ov022/video_playback/DrawMovieCaption_020a6f68.c`; reference line(s) 13, 24.
- `eu/src/overlays/ov022/calls/InitMovieOverlayState.c` → `src/ov022/video_playback/InitMovieOverlayState_020a722c.c`; reference line(s) 9, 21.
- `eu/src/overlays/ov022/calls/IsMovieCaptionTransferFlagClear.c` → `src/ov022/video_playback/IsMoviePlaybackIdle_020a78fc.c`; reference line(s) 8, 11.
- `eu/src/overlays/ov022/calls/IsMovieFadeOutComplete.c`; reference line(s) 8, 12.
- `eu/src/overlays/ov022/calls/IsMovieSceneFinished.c`; reference line(s) 3, 6.
- `eu/src/overlays/ov022/calls/RequestMovieSceneStart.c`; reference line(s) 3, 8.
- `eu/src/overlays/ov022/calls/RunMoviePlaybackState.c`; reference line(s) 32, 90, 103.
- `eu/src/overlays/ov022/calls/SetMovieStateText.c` → `src/ov022/video_playback/SetMovieStateText_020a791c.c`; reference line(s) 3, 8.
- `eu/src/overlays/ov022/calls/StartMovieCaptionScreen.c` → `src/ov022/video_playback/StartMovieCaptionScreen_020a7288.c`; reference line(s) 32, 43.
- `eu/src/overlays/ov022/calls/StartMoviePlaybackState.c` → `src/ov022/video_playback/StartMoviePlaybackState_020a7000.c`; reference line(s) 46, 82, 138.
- `eu/src/overlays/ov022/calls/StartSubtitlePlayback.c` → `src/ov022/video_playback/StartSubtitlePlayback_020a73b0.c`; reference line(s) 10, 15.
- `eu/src/overlays/ov022/calls/UpdateMovieTransfersFadeAndSound.c`; reference line(s) 3, 11, 12, 15, 17.
- `eu/src/overlays/ov022/data/bss/Bss_ov022_020b7da0.c`; reference line(s) 5.

### `ov022:020b7da8` → `gMoviePlaybackGlobals`

Previous label `data_ov022_020b7da8`; existing ELF size **12 bytes**. Source: `eu/src/overlays/ov022/data/bss/Bss_ov022_020b7da0.c`.

12-byte BSS object: stopped byte at +0 (remaining three bytes of first word unspecified), MovieAudio pointer at +4 and MovieFrameTimer pointer at +8.

OpenMoviePlayback allocates timer/audio and publishes the pointers; timer/frame/subtitle consumers use the +8 pointer. StopMoviePlayback cancels the timer alarm, frees audio buffers/audio, deletes the decoder, closes the file, frees the timer, and clears the two pointers.

Limits: The inherited SubtitleStream view of the +8 pointer is a partial timer view, not a separate third allocation. The stopped byte and the scene skip-request word belong to different globals.

Pinned references:

- `eu/src/overlays/ov022/calls/ActivateSubtitleStream.c` → `src/ov022/video_playback/ActivateSubtitleStream_020a88f0.c`; reference line(s) 1, 2.
- `eu/src/overlays/ov022/calls/GetMoviePresentedFrameCount.c` → `src/ov022/video_playback/GetSubtitleStreamFrame_020a8918.c`; reference line(s) 14, 17.
- `eu/src/overlays/ov022/calls/OpenMoviePlayback.c` → `src/ov022/video_playback/OpenMoviePlayback_020a8338.c`; reference line(s) 52, 90, 91, 92, 96, 97, 99, 100, 106, 109, 110, 111, 112, 115, 157, 164.
- `eu/src/overlays/ov022/calls/StopMoviePlayback.c` → `src/ov022/video_playback/StopMoviePlayback_020a8674.c`; reference line(s) 28, 44, 45, 60, 64, 65.
- `eu/src/overlays/ov022/calls/SwapCaptionPagesOnVBlank.c` → `src/ov022/video_playback/SwapCaptionPagesOnVBlank_020a8154.c`; reference line(s) 23, 37.
- `eu/src/overlays/ov022/calls/TickSubtitleTimer.c` → `src/ov022/video_playback/TickSubtitleTimer_020a88c4.c`; reference line(s) 14, 20.
- `eu/src/overlays/ov022/calls/runMovieSlotState.c` → `src/ov022/video_playback/runMovieSlotState_020a8730.c`; reference line(s) 43, 68.
- `eu/src/overlays/ov022/data/bss/Bss_ov022_020b7da0.c`; reference line(s) 4.

### `ov022:020b7db4` → `gMovieFileAndDecoderBackupState`

Previous label `data_ov022_020b7db4`; existing ELF size **92 bytes**. Source: `eu/src/overlays/ov022/data/bss/Bss_ov022_020b7da0.c`.

92-byte BSS object: native FSFile region +0..0x47, decoder-code backup pointer +0x48, backup size +0x4c, original code address +0x50, option +0x54 and stopping word +0x58.

OpenMoviePlayback initializes and opens the FSFile prefix. SetupMovieDecoderArenas copies the selected code-address range to an allocated backup, records size/address and configures code/table arenas. StopMoviePlayback guards stopping, drains work, closes the file and invokes FreeMovieFileBuffer.

Limits: FreeMovieFileBuffer currently declares the second MI_CpuCopy8 argument as an integer and calls it fill; SetupMovieDecoderArenas proves it stores the original address. This block records backup ownership but does not repair that prototype, rename the function, or promise pointers are cleared after backup free.

Pinned references:

- `eu/src/overlays/ov022/calls/FreeMovieFileBuffer.c` → `src/ov022/video_playback/FreeMovieFileBuffer_020a82f4.c`; reference line(s) 10, 16, 17.
- `eu/src/overlays/ov022/calls/OpenMoviePlayback.c` → `src/ov022/video_playback/OpenMoviePlayback_020a8338.c`; reference line(s) 51, 81, 94.
- `eu/src/overlays/ov022/calls/SetupMovieDecoderArenas.c` → `src/ov022/video_playback/SetupMovieDecoderArenas_020a8264.c`; reference line(s) 10, 23.
- `eu/src/overlays/ov022/calls/StopMoviePlayback.c` → `src/ov022/video_playback/StopMoviePlayback_020a8674.c`; reference line(s) 27, 43.
- `eu/src/overlays/ov022/calls/SwapCaptionPagesOnVBlank.c` → `src/ov022/video_playback/SwapCaptionPagesOnVBlank_020a8154.c`; reference line(s) 24, 58, 59.
- `eu/src/overlays/ov022/calls/TickSubtitleTimer.c` → `src/ov022/video_playback/TickSubtitleTimer_020a88c4.c`; reference line(s) 15, 23.
- `eu/src/overlays/ov022/calls/runMovieSlotState.c` → `src/ov022/video_playback/runMovieSlotState_020a8730.c`; reference line(s) 44, 91.
- `eu/src/overlays/ov022/data/bss/Bss_ov022_020b7da0.c`; reference line(s) 3.

### `ov022:020b7e10` → `gMovieCenteredSubtitleLead`

Previous label `data_ov022_020b7e10`; existing ELF size **4 bytes**. Source: `eu/src/overlays/ov022/data/bss/Bss_ov022_020b7e10.c`.

4-byte BSS word containing the cached horizontal lead for centered subtitle alignment.

UpdateMovieSubtitleLineAlignment mode1 computes max((width-measuredWidth)/2,0) on the first line (stream+0x50==0), stores it here and reuses it for subsequent lines. Other alignment modes use different calculations without this cache.

Limits: The cache is global rather than per-stream. No independent allocation or lifetime beyond the native movie overlay is asserted.

Pinned references:

- `eu/src/overlays/ov022/calls/UpdateMovieSubtitleLineAlignment.c` → `src/ov022/video_playback/updateMovieStreamLeadTime_020a8efc.c`; reference line(s) 2, 18, 20.
- `eu/src/overlays/ov022/data/bss/Bss_ov022_020b7e10.c`; reference line(s) 4.

### `ov022:020b7e14` → `gMovieDecoderCacheArenaStorage`

Previous label `data_ov022_020b7e14`; existing ELF size **44 bytes**. Source: `eu/src/overlays/ov022/data/bss/Bss_ov022_020b7e10.c`.

44-byte BSS object: saturation cache pointer +0, decode-table cache +4, decoder-code cache +8, table bytes remaining +0xc, table cursor +0x10, code bytes remaining +0x14, code cursor +0x18, opaque +0x1c, clamp-table cache +0x20; final eight bytes opaque.

ResetMovieDecoderCodeArena resets the code cursor/size and cache. ResetMovieLookupTableArena resets table cursor/size and clears its three table caches. Cache getters copy exact byte counts when capacity suffices, otherwise return original code/table addresses.

Limits: Arena bases are supplied and borrowed; this BSS object does not own their allocations. Keep size alignment to four bytes and all 44 bytes. A failed cache copy-capacity test returns the original data; it does not fail playback.

Pinned references:

- `eu/src/overlays/ov022/calls/GetCachedMovieDecodeTable.c` → `src/ov022/video_playback/GetCachedMovieDecodeTable_020aa978.c`; reference line(s) 2, 8, 9, 10, 11, 13, 14, 19.
- `eu/src/overlays/ov022/calls/GetCachedMovieDecoderCode.c` → `src/ov022/movie/get_cached_movie_decoder_code_020aa8fc.c`; reference line(s) 2, 8, 9, 10, 11, 13, 14, 19.
- `eu/src/overlays/ov022/calls/GetCachedPixelClampTable.c` → `src/ov022/video_playback/GetCachedPixelClampTable_020aaa58.c`; reference line(s) 2, 8, 9, 10, 11, 13, 14, 19.
- `eu/src/overlays/ov022/calls/ResetMovieDecoderCodeArena.c` → `src/ov022/reviewed_helpers/func_ov022_020aa8b4.c`; reference line(s) 13, 16, 17, 18.
- `eu/src/overlays/ov022/calls/ResetMovieLookupTableArena.c` → `src/ov022/reviewed_helpers/func_ov022_020aa8d4.c`; reference line(s) 13, 16, 17, 18, 19, 20.
- `eu/src/overlays/ov022/calls/get_cached_movie_saturation_table.c` → `src/ov022/movie/get_cached_movie_saturation_table_020aa9e8.c`; reference line(s) 2, 8, 9, 10, 11, 13, 14, 19.
- `eu/src/overlays/ov022/data/bss/Bss_ov022_020b7e10.c`; reference line(s) 3.

## Porting follow-up kept separate

The backup-restore function still has a legacy copy prototype and name; its original-address field is established by the writer. Correcting that API or proving all decoder paths is separate work. The cache globals contain opaque native storage beyond their proven prefix; the tables also retain repeated or padding entries that the visible consumer does not index. Naming does not authorize shrinking any of them.


## Byte-exact validation

103 DATA identities retain their source paths, native sizes and storage.
405/410 affected official function checks pass; the remaining
5 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 474 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
