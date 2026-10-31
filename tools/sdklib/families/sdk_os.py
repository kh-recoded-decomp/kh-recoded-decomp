"""NitroSDK start-up and OS routines written in assembly.

INITi_DoAutoload walks crt0's autoload list and copies each block to its
destination, clears the block's .bss and flushes the caches over it, then
tail-calls the autoload callback. The test writes random lists into the
ROM's own list descriptor (BuildInfo) and replaces the callback with a
`bx lr`; every case compares the destination memory, the source cursor, the
final registers and the logged CP15 maintenance operations with the model.

OS_IrqHandler dispatches the lowest pending enabled interrupt to its handler
in OS_IRQTable; the handlers are logging stubs and OS_IrqHandler_ThreadSwitch
is replaced by `ldmia sp!, {pc}`. OSi_DoBoot and OSi_ReloadRomData are the
last steps of a system reset: the shared system area in the main RAM mirror,
the I/O block and DTCM are mapped as plain memory, Boot_ReadRom is a stub
that logs each read, and the new program's entry point is the return
sentinel.
"""

import struct

from families.sdk_misc import first_difference, poke
from verify_sdklib import STACK_TOP, Case, Routine, load_symbols

MASK = 0xFFFFFFFF
DOC = "docs/library/sdk_os.md"
SYMBOLS = load_symbols()
BX_LR = struct.pack("<I", 0xE12FFF1E)


def address(name: str) -> int:
    return SYMBOLS[name][0]


# -- crt0 autoload ----------------------------------------------------------------------
AUTOLOAD_INFO = 0x02000B88                    # BuildInfo: list start, list end, source cursor (the routine's literal)
LISTS = 0x02370000                            # autoload list entries
SOURCE = 0x02371000                           # packed block images
DEST = 0x02380000                             # destination window
DEST_SIZE = 0x4000


def autoload(mem: bytearray, base: int, blocks, source: int):
    """Copy, clear and flush each (dest, size, bss) block; return the final registers and the CP15 log.

    The copy loop runs while dest - end is negative (MI), the clear loop while
    dest is below end (CC), the flush loop at least once and while the line is
    below end as a signed compare (LT), as the original does."""
    log = []
    r1, r3 = None, source
    r4 = r5 = r6 = r7 = None
    for dest, size, bss in blocks:
        r5, r7 = dest, size
        r6 = (dest + size) & MASK
        r4 = dest
        while (r4 - r6) & 0x80000000:
            word = struct.unpack_from("<I", mem, r3 - SOURCE + 0x10000)[0]
            struct.pack_into("<I", mem, r4 - base, word)
            r3 += 4
            r4 += 4
        r7 = bss
        r6 = (r4 + bss) & MASK
        r7 = 0
        while r4 < r6:
            struct.pack_into("<I", mem, r4 - base, 0)
            r4 += 4
        r4 = r5 & ~0x1F
        while True:
            log += [(10, 4, r7), (5, 1, r4), (14, 1, r4)]
            r4 = (r4 + 0x20) & MASK
            diff = (r4 - r6) & MASK
            n, v = diff >> 31, ((r4 ^ r6) & (r4 ^ diff)) >> 31
            if n == v:
                break
    return r3, r4, r5, r6, r7, log


def autoload_case(rng, blocks, label):
    """`blocks` are (dest offset, size, bss) inside the destination window."""
    window = bytearray(rng.randbytes(DEST_SIZE))
    images = bytearray(rng.randbytes(0x1000))
    entries = b"".join(struct.pack("<III", DEST + off, size, bss) for off, size, bss in blocks)
    end = LISTS + len(entries)
    # the model works on one buffer: the window at DEST, the images 0x10000 above it
    model = bytearray(window) + bytearray(0x10000 - DEST_SIZE) + images
    r3, r4, r5, r6, r7, log = autoload(model, DEST, [(DEST + o, s, b) for o, s, b in blocks], SOURCE)
    after = bytes(model[:DEST_SIZE])
    regs = {0: AUTOLOAD_INFO, 1: end, 2: end, 3: r3}
    if blocks:
        regs.update({4: r4, 5: r5, 6: r6, 7: r7})

    def setup(mem):
        poke(mem, AUTOLOAD_INFO, struct.pack("<III", LISTS, end, SOURCE))
        poke(mem, LISTS, entries)
        poke(mem, SOURCE, bytes(images))
        poke(mem, DEST, bytes(window))
        poke(mem, address("AutoloadCallback"), BX_LR)

    def check(cpu):
        got, cpu.cp15_log = cpu.cp15_log, []
        if got != log:
            return "%d CP15 ops %s.., model %d %s.." % (len(got), got[:3], len(log), log[:3])
        return first_difference(cpu.mem.bytes(DEST, DEST_SIZE), after, DEST)

    return Case((), regs=regs, setup=setup, check=check, label=label)


def autoload_cases(rng):
    yield autoload_case(rng, [], "empty list")
    yield autoload_case(rng, [(0, 0, 0)], "empty block")
    yield autoload_case(rng, [(0x40, 0x20, 0)], "copy only")
    yield autoload_case(rng, [(0x40, 0, 0x20)], "bss only")
    yield autoload_case(rng, [(0x44, 0x1c, 0x24)], "unaligned to the cache line")
    yield autoload_case(rng, [(0x100, 6, 3)], "sizes not word multiples")
    for _ in range(140):
        blocks, cursor = [], rng.randrange(0, 0x40) * 4
        for _ in range(rng.randrange(1, 4)):
            size = rng.choice((0, 4, rng.randrange(1, 0x100), rng.randrange(0, 0x40) * 4))
            bss = rng.choice((0, 4, rng.randrange(1, 0x100), rng.randrange(0, 0x40) * 4))
            if cursor + size + bss + 0x40 > DEST_SIZE:
                break
            blocks.append((cursor, size, bss))
            cursor += ((size + 3) & ~3) + ((bss + 3) & ~3) + rng.randrange(0, 0x10) * 4
        yield autoload_case(rng, blocks, "%d blocks" % len(blocks))


# -- IRQ dispatch -----------------------------------------------------------------------
IO = 0x04000000
REG_IME, REG_IE, REG_IF = 0x04000208, 0x04000210, 0x04000214
IRQ_TABLE = 0x027E0000                        # SDK_AUTOLOAD_DTCM_START: OS_IRQTable, 32 handlers
DTCM_SIZE = 0x4000
HANDLERS = 0x02372000                         # one logging stub per interrupt source
HANDLER_LOG = 0x02373000                      # (source number, lr) of the handler that ran
NO_HANDLER = 0xDEADBEEF
POP_PC = struct.pack("<I", 0xE8BD8000)        # ldmia sp!, {pc}


def handler_stub(source: int) -> bytes:
    """mov r0, #source; ldr r1, =HANDLER_LOG; stmia r1, {r0, lr}; bx lr"""
    words = (0xE3A00000 | source, 0xE59F1004, 0xE8814001, 0xE12FFF1E, HANDLER_LOG)
    return b"".join(struct.pack("<I", w) for w in words)


def ensure_mapped(mem, start: int, size: int) -> None:
    if not any(lo <= start < hi for lo, hi, _ in mem.regions):
        mem.map(start, size=size)


def irq_dispatch(ime: int, enabled: int, pending: int):
    """(source handled or None, IF after the call): the lowest pending enabled source wins and is acknowledged."""
    if ime == 0:
        return None, pending
    active = enabled & pending
    if active == 0:
        return None, pending
    source = (active & -active).bit_length() - 1
    return source, 1 << source


def irq_case(ime: int, enabled: int, pending: int, label: str):
    source, if_after = irq_dispatch(ime, enabled, pending)
    handled = (source, address("OS_IrqHandler_ThreadSwitch")) if source is not None else (NO_HANDLER, NO_HANDLER)

    def setup(mem):
        ensure_mapped(mem, IO, 0x1000)
        ensure_mapped(mem, IRQ_TABLE, DTCM_SIZE)
        poke(mem, HANDLERS, b"".join(handler_stub(k).ljust(0x20, b"\0") for k in range(32)))
        poke(mem, IRQ_TABLE, b"".join(struct.pack("<I", HANDLERS + 0x20 * k) for k in range(32)))
        poke(mem, address("OS_IrqHandler_ThreadSwitch"), POP_PC)
        poke(mem, HANDLER_LOG, struct.pack("<II", NO_HANDLER, NO_HANDLER))
        poke(mem, REG_IME, struct.pack("<I", ime))
        poke(mem, REG_IE, struct.pack("<II", enabled, pending))

    def check(cpu):
        got = struct.unpack("<II", cpu.mem.bytes(HANDLER_LOG, 8))
        if got != handled:
            return "handler log %s, model %s" % (got, handled)
        register_if = struct.unpack("<I", cpu.mem.bytes(REG_IF, 4))[0]
        if register_if != if_after:
            return "IF = 0x%08x, model 0x%08x" % (register_if, if_after)
        if cpu.r[13] != STACK_TOP:
            return "sp = 0x%08x after return" % cpu.r[13]
        return None

    return Case((), setup=setup, check=check, label=label)


def irq_cases(rng):
    yield irq_case(0, MASK, MASK, "IME off")
    yield irq_case(1, 0, MASK, "nothing enabled")
    yield irq_case(1, MASK, 0, "nothing pending")
    yield irq_case(0x80000000, 1 << 31, 1 << 31, "IME high bit, source 31")
    for source in range(32):
        yield irq_case(1, 1 << source, 1 << source, "source %d" % source)
        yield irq_case(1, MASK, (MASK << source) & MASK, "sources %d.." % source)
    for _ in range(100):
        ime = rng.choice((0, 1, rng.getrandbits(32)))
        enabled = rng.getrandbits(32) & rng.getrandbits(32)
        pending = rng.getrandbits(32) & rng.getrandbits(32)
        yield irq_case(ime, enabled, pending, "random")


# -- reboot into a new program ----------------------------------------------------------
REG_IPCSYNC = 0x04000180
IRQ_CHECK = 0x027E3FFC                       # DTCM word the BIOS IRQ handler ORs into (OS_IRQ check flags)
SHARED = 0x02FFF000                          # main RAM mirror holding the system work area
SHARED_SIZE = 0x1000
RETURN_SENTINEL = 0xFFFFFFF0


def do_boot(shared: bytearray, ipcsync: int):
    """Return (shared area after, final r0-r12, IPCSYNC after) for OSi_DoBoot.

    Clears 0x02FFFD80-0x02FFFDFF but keeps the word at 0x02FFFF9C (moved to
    0x02FFFD9C), clears 0x02FFFF80-0x02FFFF97, zeroes the halfword at
    0x02FFFF98, clears 0x02FFFF9C-0x02FFFFFF, then loads r0-r10 from
    0x02FFFF80 and jumps to the ARM9 entry stored at 0x02FFFE24."""
    def at(address):
        return address - SHARED
    kept = shared[at(0x02FFFF9C):at(0x02FFFF9C) + 4]
    shared[at(0x02FFFD80):at(0x02FFFD80) + 0x80] = bytes(0x80)
    shared[at(0x02FFFD9C):at(0x02FFFD9C) + 4] = kept
    shared[at(0x02FFFF80):at(0x02FFFF80) + 0x18] = bytes(0x18)
    shared[at(0x02FFFF98):at(0x02FFFF98) + 2] = bytes(2)
    shared[at(0x02FFFF9C):at(0x02FFFF9C) + 0x64] = bytes(0x64)
    entry = struct.unpack_from("<I", shared, at(0x02FFFE24))[0]
    regs = list(struct.unpack_from("<11I", shared, at(0x02FFFF80))) + [0, entry]
    return shared, regs, (ipcsync & 0xFFFF0000)


def boot_case(rng, ipcsync: int, label: str):
    shared = bytearray(rng.randbytes(SHARED_SIZE))
    struct.pack_into("<I", shared, 0x02FFFE24 - SHARED, RETURN_SENTINEL)
    before = bytes(shared)
    after, regs, ipcsync_after = do_boot(bytearray(before), ipcsync)

    def setup(mem):
        ensure_mapped(mem, IO, 0x1000)
        ensure_mapped(mem, IRQ_TABLE, DTCM_SIZE)
        ensure_mapped(mem, SHARED, SHARED_SIZE)
        poke(mem, SHARED, before)
        poke(mem, REG_IPCSYNC, struct.pack("<I", ipcsync))
        poke(mem, REG_IME, struct.pack("<I", 1))
        poke(mem, IRQ_CHECK, struct.pack("<I", 0xFFFFFFFF))

    def check(cpu):
        problem = first_difference(cpu.mem.bytes(SHARED, SHARED_SIZE), bytes(after), SHARED)
        if problem:
            return problem
        for reg, value in enumerate(regs):
            if cpu.r[reg] != value:
                return "r%d = 0x%08x, model 0x%08x" % (reg, cpu.r[reg], value)
        if cpu.r[14] != RETURN_SENTINEL:
            return "lr = 0x%08x, model the entry point" % cpu.r[14]
        words = [struct.unpack("<I", cpu.mem.bytes(a, 4))[0] for a in (REG_IME, IRQ_CHECK, REG_IPCSYNC)]
        if words != [IO, 0, ipcsync_after]:
            return "IME, IRQ check, IPCSYNC = %s, model %s" % ([hex(w) for w in words],
                                                              [hex(w) for w in (IO, 0, ipcsync_after)])
        return None

    return Case((), setup=setup, check=check, label=label)


def boot_cases(rng):
    yield boot_case(rng, 1, "IPCSYNC = 1")
    for _ in range(120):
        yield boot_case(rng, (rng.getrandbits(28) << 4) | 1, "random shared area")


# -- reload the program from the card ---------------------------------------------------
ROM_OFFSET = 0x02FFFC2C                      # card offset of the running program (0 for the cartridge itself)
HEADER = 0x02FFFE00                          # copy of the card header
READ_CURSOR = 0x02374000                     # Boot_ReadRom stub: log cursor, then (src, dst, size) triples
READ_LOG = 0x02374010


def read_logger() -> bytes:
    """ldr ip, =READ_CURSOR; ldr r3, [ip]; stmia r3!, {r0-r2}; str r3, [ip]; bx lr"""
    words = (0xE59FC00C, 0xE59C3000, 0xE8A30007, 0xE58C3000, 0xE12FFF1E, READ_CURSOR)
    return b"".join(struct.pack("<I", w) for w in words)


def s32(value: int) -> int:
    return value - (1 << 32) if value & 0x80000000 else value


def reload_rom(first_boot: int, rom_offset: int, header: bytes):
    """(Boot_ReadRom calls, CP15 log) of OSi_ReloadRomData."""
    offset = 0 if first_boot else rom_offset
    reads = []
    if offset >= 0x8000:
        reads.append((offset, HEADER, 0x160))
    arm9_rom, _, arm9_ram, arm9_size, arm7_rom, _, arm7_ram, arm7_size = struct.unpack_from("<8I", header, 0x20)
    src = (arm9_rom + offset) & MASK
    below = (src - 0x8000) & MASK
    if (below >> 31) != (((src ^ 0x8000) & (src ^ below)) >> 31):      # LT: start inside the secure area
        src, arm9_ram, arm9_size = 0x8000, (arm9_ram - below) & MASK, (arm9_size + below) & MASK
    if s32(arm9_size) > 0:
        reads.append((src, arm9_ram, arm9_size))
    if s32(arm7_size) > 0:
        reads.append(((arm7_rom + offset) & MASK, arm7_ram, arm7_size))
    log = [(10, 2, way | line) for way in (0, 0x40000000, 0x80000000, 0xC0000000) for line in range(0, 0x400, 0x20)]
    return reads, log + [(6, 0, 0), (5, 0, 0), (10, 4, 0)]


def reload_case(rng, first_boot: int, rom_offset: int, header: bytes, label: str):
    reads, log = reload_rom(first_boot, rom_offset, header)

    def setup(mem):
        ensure_mapped(mem, SHARED, SHARED_SIZE)
        poke(mem, ROM_OFFSET, struct.pack("<I", rom_offset))
        poke(mem, HEADER, header)
        poke(mem, address("Boot_ReadRom"), read_logger())
        poke(mem, READ_CURSOR, struct.pack("<I", READ_LOG))

    def check(cpu):
        got_log, cpu.cp15_log = cpu.cp15_log, []
        if got_log != log:
            return "%d CP15 ops, model %d" % (len(got_log), len(log))
        cursor = struct.unpack("<I", cpu.mem.bytes(READ_CURSOR, 4))[0]
        got = [struct.unpack_from("<III", cpu.mem.bytes(READ_LOG, cursor - READ_LOG), i)
               for i in range(0, cursor - READ_LOG, 12)]
        if got != reads:
            return "reads %s, model %s" % ([tuple(map(hex, r)) for r in got], [tuple(map(hex, r)) for r in reads])
        if cpu.r[4] != 0 or cpu.r[13] != STACK_TOP:
            return "r4 or sp not preserved"
        return None

    return Case((first_boot,), setup=setup, check=check, label=label)


def reload_cases(rng):
    def header(arm9_rom, arm9_size, arm7_rom, arm7_size):
        data = bytearray(rng.randbytes(0x40))
        struct.pack_into("<IIII", data, 0x20, arm9_rom, rng.getrandbits(32), 0x02000000 + rng.randrange(0x100000), arm9_size)
        struct.pack_into("<IIII", data, 0x30, arm7_rom, rng.getrandbits(32), 0x02380000 + rng.randrange(0x10000), arm7_size)
        return bytes(data)
    yield reload_case(rng, 1, 0x12345678, header(0x4000, 0x100000, 0x200000, 0x20000), "first boot, cartridge layout")
    yield reload_case(rng, 0, 0, header(0x4000, 0x8000, 0x60000, 0), "reboot, offset 0")
    yield reload_case(rng, 0, 0x8000, header(0x4000, 0x100, 0x6000, 0x100), "offset at the secure-area end")
    yield reload_case(rng, 0, 0x7FFF, header(0x8000, 0x100, 0x9000, 0x100), "offset just below")
    yield reload_case(rng, 0, 0, header(0x4000, 0x3000, 0x5000, 0x80000000), "secure area swallows the ARM9 block")
    for _ in range(140):
        first = rng.choice((0, 0, 1, rng.getrandbits(32)))
        offset = rng.choice((0, rng.randrange(0x8000), rng.randrange(0x8000, 0x1000000), rng.getrandbits(32)))
        arm9_rom = rng.choice((0x4000, rng.randrange(0x10000), rng.getrandbits(32)))
        sizes = [rng.choice((0, rng.randrange(1, 0x200000), rng.getrandbits(32), 0x80000000)) for _ in range(2)]
        yield reload_case(rng, first, offset, header(arm9_rom, sizes[0], rng.getrandbits(32), sizes[1]), "random")


ROUTINES = [
    Routine("INITi_DoAutoload", "src/asm_stubs/calls/INITi_DoAutoload.c", DOC, autoload_cases),
    Routine("OS_IrqHandler", "libs/nitro/os/asm_stubs/calls/OS_IrqHandler.c", DOC, irq_cases),
    Routine("OSi_DoBoot", "libs/nitro/os/asm_stubs/calls/OSi_DoBoot.c", DOC, boot_cases),
    Routine("OSi_ReloadRomData", "libs/nitro/os/asm_stubs/calls/OSi_ReloadRomData.c", DOC, reload_cases,
            object_gate=True),
]
