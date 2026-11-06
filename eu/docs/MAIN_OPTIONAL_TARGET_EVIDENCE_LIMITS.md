# Retained MAIN optional-target setter

`main:0202d620` remains `func_0202d620`, with the existing `void (u32 value)` source declaration. The native 20-byte range and current Ghidra view agree: read the optional target pointer from BSS anchor `02060764 +4`; if nonzero, store the input word at target +0x600; otherwise return.

`ResumeFieldFromPause` calls it with 1 after restoring graphics. That placement does not establish the target type, ownership, renderer role, paused state or dirty-flag meaning. The only current Ghidra reference to pointer slot `02060768` is the setter's read at `0202d622`.

The additional bounded initialization trail inspected the immediately preceding allocation, `gFileLoaderMessages`, at `02060664..02060763`. Its 64 pointer slots end exactly before the unknown eight-byte anchor. `InitFileLoader` passes that array with capacity 64 to `OS_InitMessageQueue` for queue `02060584`; native `0202c2f4/0202c2f8` loads the queue/buffer, `0202c300` supplies count 0x40 and `0202c304` invokes the queue initializer. `OS_InitMessageQueue` stores the buffer pointer in queue +0x10 and capacity in queue +0x14. Those writes do not register the optional target at `02060768`.

Source: `src/arm9/filesystem/InitFileLoader_0202c20c.c:72`, `eu/src/filesystem/FileLoaderState.h:28`, `eu/src/data/bss/Bss_main_02060764.c:3`, and `src/arm9/unclassified_helpers/func_0202d60c.c:10`. The source wrapper keeps the original shared-US aliases. The heap allocations and callback setup in the file-loader initializer do not prove a shared target owner for this separate BSS allocation.

No new global raw-ROM scan was performed. This bounded trail excludes a plausible adjacent-buffer explanation; it does not prove absence of calculated or externally registered pointers. A meaningful rename still needs an actual nonzero writer or registration of anchor +4 and a same-owner constructor/consumer for target +0x600. A generic address-based cleanup name would hide that missing evidence, so no rename or field/type change is proposed.

## Bounded ARM7 check

The original BK9P ARM7 payload was also checked as a possible external literal writer. Its validated 156,716-byte segment contains no complete little-endian 0x02060764, 0x02060768 or 0x02060769 word at any offset, including unaligned offsets. This excludes that specific literal trail; it does not exclude calculated addressing or prove the target unused. ARM7 code coverage remains outside the EU ARM9 matching figures.

## Active source links

- [Retained setter](../src/calls/func_0202d620.c).
- [Resume caller](../src/overlays/ov001/calls/ResumeFieldFromPause.c).
- [Eight-byte BSS allocation](../src/data/bss/Bss_main_02060764.c).

The current naming block changes none of these definitions or their declarations. The complete linked gate retains all 108 ARM9 module hashes; no original type or purpose is inferred for this target.
