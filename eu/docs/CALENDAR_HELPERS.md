# MSL calendar conversion helpers

These names describe the actual EU operations and their calendar callers.
`src/runtime/CalendarFields.h` provides the established native storage and
logical helper interfaces without treating that storage as a host `struct tm`.

| Previous symbol | Current name | Established operation |
|---|---|---|
| `func_02022570` | `ParseDecimalLong` | Calls `strtol(text, NULL, 10)` and forwards its result. |
| `func_02022584` | `IsLeapYearSince1900` | Tests the Gregorian leap condition on `tm_year`, not on a full civil year. |
| `func_02022688` | `NormalizeCalendarFieldWithCarry` | Writes a floor-division remainder back to one field and checked-adds the quotient to its next larger field. |
| `func_020229dc` | `NormalizeCalendarToTime` | Converts a local calendar copy, copies normalization back only on success and returns the 32-bit time word or -1. |

The leap test deliberately accepts centuries with `tm_year % 400 == 100`.
For `tm_year = civilYear - 1900`, this is the ordinary civil-year multiple-of-400
case. `TimeToCalendar` counts years from zero after its `0x83aa7e80` seconds bias
and stores that count in `tm_year`; `__msl_mktime` uses the inverse
`0x7c558180` bias. Changing this predicate to `% 400 == 0` would change behavior.

`__msl_mktime` applies normalization to seconds/60, minutes/60, hours/24 and
months/12. The normalization helper is **not transactional**: it stores the
remainder before attempting the checked addition to the carry. On overflow,
the source field may already have changed. Preserve the floor-division helper's
signed behavior instead of substituting ordinary truncating C division.

The wrapper at `0x020229dc` copies exactly 36 bytes to a local object before
calling `__msl_mktime`. On failure it returns -1 and leaves the caller's object
unchanged. On success it copies all 36 bytes back and returns the time word.
Eight fields are established by `TimeToCalendar`: seconds, minutes, hours,
day-of-month, month, year-since-1900, weekday and year-day. The ninth word is
preserved but its meaning is not established here. Keep it reserved; do not
invent `tm_isdst` or timezone semantics from its familiar position.

The helpers now expose their proven logical inputs: the decimal parser takes
`const char *` and returns native `long`; the carry helper takes field, divisor
and carry pointers/word; the conversion wrapper takes one `CalendarFields *`.
Unused reconstructed register slots are removed from those definitions rather
than assigned invented meanings. Their unchanged instructions and relocations
are required by the official checks.

`CalendarFields` preserves nine native words (36 bytes). Its first eight fields
are named from the converter's accesses; `reserved20` is deliberately opaque.
The wrapper's copy includes that word on both input and successful output.
The common header does not change the older converter's prefix-view interface
or make every shared caller's erased pointer declaration a host API.

A host port must separate the native 32-bit time word from host `time_t`, keep
the origin/overflow behavior explicit, and preserve the copy-on-success rule.
A result word equal to `0xffffffff` and a conversion failure are not necessarily
distinguished by the wrapper alone. No host timezone or daylight-saving policy
is introduced by these names.

Evidence: `src/arm9/math/func_02022570.c`,
`src/arm9/math/func_02022674.c`,
`src/arm9/unclassified_helpers/func_020229c8.c`,
`src/arm9/library_msl_c/TimeToCalendar_020226b4.c`,
`src/arm9/library_msl_c/__msl_mktime_020227fc.c` and the EU alias wrappers.


## Reproduction

From `eu/`:

```sh
python tools/rebuild_index.py --write --refresh-reloc-names
python tools/verify_idx.py src/calls/ParseDecimalLong.c ParseDecimalLong
python tools/verify_idx.py src/calls/IsLeapYearSince1900.c IsLeapYearSince1900
python tools/verify_idx.py src/calls/NormalizeCalendarFieldWithCarry.c NormalizeCalendarFieldWithCarry
python tools/verify_idx.py src/calls/NormalizeCalendarToTime.c NormalizeCalendarToTime
bash tools/gate.sh
```

The four primary functions pass their official byte/relocation checks. All
nine reviewed production functions retain instructions, resolved targets/types
and addends. The fresh linked gate passes 108/108 modules with every hash
unchanged.
Naming and type recovery add no C or DATA reconstruction credit. Native `long`
is 32 bits here; do not silently adopt the host parser's wider range or host
timezone/DST conventions when replacing the native library in a port.
