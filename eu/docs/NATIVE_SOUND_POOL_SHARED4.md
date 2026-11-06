# Sound command pool partitions and shared work (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

## One logical pool, three native symbols

The sound-command pool is a proven 6144-byte range of 256 records at 24 bytes each. The native build partitions it into 4096,2024 and 24-byte ELF symbols, splitting record170 between the first two. The last 24-byte object is record255. Original ROM instructions establish the base, stride, loop bound, final next-pointer clear and free-tail pointer. The following object is the 96-byte sound-alarm handler array; it is outside the pool.

SOUND_POOL_NATIVE_SPAN_CLOSURE_AUDIT.json records exact ROM instruction addresses, the function hash and native ELF boundaries. This resolves the earlier apparent 4096-versus-6144 conflict without changing source, layout or verifiers. The C initializer currently expresses the whole pool through one array view; any source/prototype or relocation metadata adjustment remains a separate task.

## Inventory and evidence

### `main:02057f20` → `gSoundCommandPoolPrefix`

Previous label `data_02057f20`; existing ELF size **4096 bytes**. Source: `eu/src/data/bss/Bss_main_02057c34.c`.

4096-byte native BSS prefix of the logical 256-record sound-command pool. It holds complete records 0..169 and the first 16 bytes of record 170.

Original SND_CommandInit ARM 0200ee04 loads this base at 0200ee0c and links records using stride 0x18 while index < 0xff. The full pool continues through two separate native BSS symbols and ends at 02059720.

Limits: Do not call this symbol a complete 4096-byte pool or resize it to 6144 bytes. Preserve the split inside record 170, generic filenames and existing C views. Full-array source declarations cross native object boundaries.

Pinned references:

- `eu/libs/nitro/snd/calls/SND_FlushCommand.c` → `src/arm9/audio/audio_flush_reserved_commands_0200f080.c`; reference line(s) 21, 54, 66.
- `eu/src/calls/SND_CommandInit.c` → `src/arm9/library_nitro_snd/func_0200edf0.c`; reference line(s) 54, 55.
- `eu/src/data/bss/Bss_main_02057c34.c`; reference line(s) 3.

### `main:02058f20` → `gSoundCommandPoolMiddle`

Previous label `data_02058f20`; existing ELF size **2024 bytes**. Source: `eu/src/data/bss/Bss_main_02058f20.c`.

2024-byte native BSS middle span: last 8 bytes of record 170 plus complete records 171..254 of the same pool.

The preceding 4096-byte symbol, this 2024-byte symbol and final 24-byte symbol are contiguous and total 6144 bytes =256*24. Original SND_CommandInit loads this middle base at 0200ee44 and clears next of record 255 through offset 0x7e8 at 02059708.

Limits: This is not a second independent pool. Preserve its exact 2024 bytes and literal/relocation boundary; source rewriting is a separate follow-up.

Pinned references:

- `eu/src/data/bss/Bss_main_02058f20.c`; reference line(s) 3.

### `main:02059708` → `gSoundCommandPoolLastRecord`

Previous label `data_02059708`; existing ELF size **24 bytes**. Source: `eu/src/data/bss/Bss_main_02059708.c`.

24-byte native BSS symbol containing sound-command record 255.

ROM SND_CommandInit clears this record next pointer via middleBase+0x7e8, separately loads its address at 0200ee50 and stores it as free-list tail at queueState+0x10. Its end 02059720 equals the next sound-alarm handler array start.

Limits: The existing command struct has next/id/four argument words. Only next is explicitly set by this initializer; other bytes rely on BSS initialization or later allocation. Keep this as a 24-byte fragment/record, not a new allocation.

Pinned references:

- `eu/src/data/bss/Bss_main_02059708.c`; reference line(s) 4.

### `main:02057ca0` → `gSoundSharedWorkStorage`

Previous label `data_02057ca0`; existing ELF size **640 bytes**. Source: `eu/src/data/bss/Bss_main_02057c34.c`.

640-byte native BSS shared-work buffer.

SND_CommandInit loads its base at 0200ee78, publishes it through SNDi_SharedWork at 02059780, calls SNDi_InitSharedWork and enqueues command 0x1d with this pointer as argument 0.

Limits: The forward-declared native shared-work type is not a new portable layout. Preserve 640 bytes and the ARM7 communication contract; detailed fields remain outside this naming block.

Pinned references:

- `eu/src/calls/SND_CommandInit.c` → `src/arm9/library_nitro_snd/func_0200edf0.c`; reference line(s) 52, 53.
- `eu/src/data/bss/Bss_main_02057c34.c`; reference line(s) 4.


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
