# Overlay 044 five-word writers: bounded Days reference check

The local Days reference was checked at commit
`93535afd7ca082f3d856bbf1cadae65be16d44ba`. This check did not establish a
corresponding output type or consumer for either Re:coded writer.

The Re:coded contracts remain exact:

| EU identity | Writes at destination+0/+4/+8/+c/+10 |
|---|---|
| ov044:020d0000 | {0x1922,0x2b8,0x333,0,0xa000} |
| ov044:020d0020 | {0x1922,0x666,0x666,0,0x14000} |

Both use incoming R0 as the destination and preserve it natively. The
generated definitions' extra three formal words are not proof of three
logical inputs. No actual caller has established a logical return API.
The own-bank table at 020d0df8 still contains pointers 020d0001/020d0021
in slots 2/3, but its invoker and the destination allocation remain unknown.

Pinned Days source queries for 1922/6434 and 2b8 in motor/scene/screen/system
subtrees found no corresponding preset. The available generated index has
no identical native body and no small function with the literal 1922 word.
That index was used only as a locator; its provenance and alternative code
generation do not justify a claim that every possible Days representation
has been excluded.

A bounded structural query also checked small functions that write words
at offsets 0/4/8/c/10. The three exact-five-word candidates are different:

- [EventRecord_Init](https://github.com/Yokimitsuro/khdays-decomp/blob/93535afd7ca082f3d856bbf1cadae65be16d44ba/src/engine/EventRecord_Init.c)
  copies a payload, tag and duration and writes additional byte/halfword
  fields; it is not a constant-only preset writer.
- [Ov002_InitBlockCursor](https://github.com/Yokimitsuro/khdays-decomp/blob/93535afd7ca082f3d856bbf1cadae65be16d44ba/src/overlays/scenes/ov002_field/Ov002_InitBlockCursor.c)
  initializes pointers and a cached flag from a supplied resource buffer.
- [Ov025_InitBlockCursor](https://github.com/Yokimitsuro/khdays-decomp/blob/93535afd7ca082f3d856bbf1cadae65be16d44ba/src/overlays/screens/ov025_camp_menu_2/Ov025_InitBlockCursor.c)
  is another resource cursor, with no matching constant tuple.

Repeated 1922 values in angle/enemy code provide no Re:coded ownership
evidence. No camera, FOV, motion-unit or gameplay interpretation is added.
Even an identical Days function would need a Re:coded caller/owner link
before its type or name could be transferred.

The next proof is still a bank-qualified table load/copy and invocation
showing slot 2/3 and the concrete incoming-R0 destination, or a proved
reader of those five output words. The separate scalar drift presets and
the excluded ov052 same-RAM reference do not establish that chain.

Re:coded evidence sources:

- `eu/src/overlays/ov044/calls/func_ov044_020d0000.c`
- `eu/src/overlays/ov044/calls/func_ov044_020d0020.c`
- `eu/src/ov044/data/Data_ov044_020d0de0.c`

Both complete original functions and the six-pointer table were checked
against the extracted EU module. No source, compiler or verifier was
changed; no candidate was compiled and no new name is proposed.
