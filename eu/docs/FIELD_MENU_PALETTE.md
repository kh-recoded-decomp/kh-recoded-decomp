# Field-menu palette update

`UpdateFieldMenuPalette` (ov001, `0x02076ebc`) is matching C in
`src/overlays/ov001/calls/UpdateFieldMenuPalette.c`, with its two real inputs:
the menu view and an `advance` flag. CodeWarrior dsi/1.1 emits the original's
312 bytes and 11 relocations.

It matches only through two steering symbols, a documented exception (see
"Steering symbols" in [PROGRESS_POLICY.md](PROGRESS_POLICY.md)). The original
keeps the ramp table's address in r7 for the three fade reads, loads yellow
`0x03ff` from its literal pool and holds a second pool word for the same table
address. Written plainly, mwcc derives `0x03ff` from `0x0318` (`adds #0xe7`),
gives r7 to that constant and merges the two pool words. The source therefore
reads the fade colours through `gFieldMenuFadeRamps`, a second name for
`gFieldMenuStateRamps`, and passes the colour as the address of the
linker-absolute symbol `FieldMenuFadeYellow` (`0x3ff`); both are defined in
`tools/configure.py`. The original spelling is unknown. Every alternative tried
failed: the table as an array, a struct or three arrays, defined in the same
file; pointer variables; inline helpers; a loop over a target table; all 18
compiler versions; every `opt_*` pragma on and off; the optimisation levels;
and 32 prototype type combinations. A port should use the plain table and the
integer constant.

## Recovered state and data

`FieldMenuPalette.h` describes ARM32 views, not allocation sizes. Menu offsets
`0x68` and `0x6c` are signed current/previous modes; `0x70` and `0x71` are signed
byte fade level/step. The handle at `0x020a04d0` holds a palette pointer at `+8`
and three temporary colors at `+0x0c`, also named `data_ov001_020a04dc` in the
original inventory. The last accessed bytes are menu `+0x71` and handle `+0x11`;
compiler tail padding does not establish additional recovered fields.

`gFieldMenuStateRamps` is a `FieldMenuStateRamps` struct of three RGB555 rows at
`0x0209ee60`: blue, then red at `+6` and green at `+12`. Only the steering alias
above gives the same address a second name; no data is defined twice.

| Current mode | Selected row / action |
|---|---|
| `0`, `7` | Red. |
| `10` | Blue. |
| `11`, `13`, different from previous mode | Reset level to 0 and step to 2; select red without blending this time. |
| `11`, `13`, same as previous mode | Pulse the red row toward the three target colors. |
| Other values | Green. |

Mode `-1` first selects the previous mode, performs that mode's work, and restores
`-1` before queuing either transfer. Otherwise the current mode is copied to the
previous mode. Neither path skips transfers.

For an established pulse, level `>=8` sets step to `-2`; level `<=0` sets it to
`2`. The direction changes even when `advance` is false. A true flag adds the
step, stores the signed byte, then clamps the stored value to `0..8`. Preserve
that order if reproducing the original behavior for unexpected byte values.
Ordinary callers should maintain the `0..8` level invariant.

Each RGB555 channel interpolates with signed integer division toward zero:
`from + trunc((to-from)*level/8)`. The three target words are `0x0210`, `0x0318`
and `0x03ff`. In RGB555, `0x03ff` is yellow `(31,31,0)`, not white.

Both transfers use kind `15`, six source bytes, and destinations `0x138` then
`0x158`. Before the first call, the handle points to the selected static row or
its temporary fade words. The second call reloads the handle's pointer after
the first call; callback-visible changes must not be hidden by caching it. The
return values of both queue calls are ignored. The actual queue consumes source
pointers: a port must preserve its buffer-lifetime contract and provide the
graphics transfer backend. This routine alone does not establish when the queue
copies those bytes or how queue exhaustion is handled.

## Executable checks

Run from `eu/`:

```text
python tools/test_field_menu_palette.py -v
python ../tools/mobiclip/test_arm_exec_thumb_stack.py -v
```

The palette suite checks the original overlay against the ROM-derived function
index, checks all nine original color words, and runs 906 scenarios on each of
four instruction images: ROM, CodeWarrior dsi/1.1, GCC 12.2.Rel1 and Clang 22.1.3,
and checks that the relocated CodeWarrior image is identical to the ROM.
These cover mode selection/restoration, mode entry, every signed-byte level,
nonstandard steps, false and nonzero advance flags, both queue return values,
and pointer mutation by the first queue call. Out-of-range fade values are
machine-code stress inputs, not confirmed valid game states. Two additional
64-frame runs check the continuous pulse and retained `-1` sentinel.

The original RGB555 helper and `_s32_div_f` execute their actual ROM instructions.
Only the VRAM queue is modeled: its calls record arguments and the source bytes
visible at that boundary, optionally mutate the handle pointer, and poison
caller-saved registers and flags. Comparisons include complete menu/handle
buffers, unchanged static colors, transfer order, preserved registers and SP.
This does not emulate the queue, VRAM or display hardware.

`thumb_replay_link.py` creates private temporary images, with explicit external
address/state manifests. MWCC RELA calls are resolved in a private byte image;
GNU objects use GNU ld for local jump tables and interworking. Compiler objects,
ROM references and matching verifiers are untouched; the byte match itself is
proved by `tools/verify_idx.py` and the full gate. The interpreter's added Thumb stack/address formats have
separate boundary, flag-preservation and refusal checks.
