# Pending field-menu palette update

`src/nonmatching/UpdateFieldMenuPalette.c` reconstructs EU
`func_ov001_02076ebc` with its two real inputs: the menu view and an `advance`
flag. It is excluded from the linked build and matching-C coverage. CodeWarrior
dsi/1.1 currently emits 312 bytes, the same size as the ROM, but the instructions
and relocation positions still differ. Equal size and behavior are not a match.

## Recovered state and data

`FieldMenuPalette.h` describes ARM32 views, not allocation sizes. Menu offsets
`0x68` and `0x6c` are signed current/previous modes; `0x70` and `0x71` are signed
byte fade level/step. The handle at `0x020a04d0` holds a palette pointer at `+8`
and three temporary colors at `+0x0c`, also named `data_ov001_020a04dc` in the
original inventory. The last accessed bytes are menu `+0x71` and handle `+0x11`;
compiler tail padding does not establish additional recovered fields.

The existing `gFieldMenuStateRamps[3][3]` owns the three adjacent RGB555 rows at
`0x0209ee60`. This reconstruction uses that real array, including its red row at
`+6` and green row at `+12`. It does not create overlapping data definitions.

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
and `0x03ff`. In RGB555, `0x03ff` is yellow `(31,31,0)`, not white. EU expresses
it as an integer constant; an invented absolute object address is not an
acceptable substitute merely to obtain a literal-pool entry.

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
four instruction images: ROM, CodeWarrior dsi/1.1, GCC 12.2.Rel1 and Clang 22.1.3.
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
ROM references and matching verifiers are untouched. This test awards no
matching receipt. The interpreter's added Thumb stack/address formats have
separate boundary, flag-preservation and refusal checks.
