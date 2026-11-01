"""NitroSDK start-up and OS routines written in assembly.

INITi_DoAutoload walks crt0's autoload list and copies each block to its
destination, clears the block's .bss and flushes the caches over it, then
tail-calls the autoload callback. The test writes random lists into the
ROM's own list descriptor (BuildInfo) and replaces the callback with a
`bx lr`; every case compares the destination memory, the source cursor, the
final registers and the logged CP15 maintenance operations with the model.

Entry (crt0) runs up to `main`: the stubs for the CP15 set-up, the
decompressor, the autoload copier and the constructors log their calls, the
stacks, cleared areas and .bss flush are compared with the model.

OS_IrqHandler dispatches the lowest pending enabled interrupt to its handler
in OS_IRQTable; the handlers are logging stubs and OS_IrqHandler_ThreadSwitch
is replaced by `ldmia sp!, {pc}`. OS_IrqHandler_ThreadSwitch itself runs on
random thread lists and IRQ queues with a BIOS frame on the IRQ stack.
OSi_DoBoot and OSi_ReloadRomData are the last steps of a system reset: the
shared system area in the main RAM mirror, the I/O block and DTCM are mapped
as plain memory, Boot_ReadRom is a stub that logs each read, and the new
program's entry point is the return sentinel.

OS_SaveContext / OS_LoadContext and the exception routines change processor
mode: the cases start in every privileged mode with random flags, interrupt
masks and banked registers (Case.prepare) and compare the contexts, the user
and banked registers and the SPSRs with the model. OSi_ExceptionHandler never
returns; its run stops at the wait loop (Case.stop).
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


# -- thread contexts --------------------------------------------------------------------
# OSContext: cpsr, r0-r12, sp, lr, pc + 4, SVC-mode sp, then the divider context (CPContext).
CONTEXT = 0x02375000
CTX_CPSR, CTX_R, CTX_SP, CTX_LR, CTX_PC_PLUS4, CTX_SP_SVC, CTX_CP = 0x00, 0x04, 0x38, 0x3C, 0x40, 0x44, 0x48
CONTEXT_SIZE = 0x64
PRIVILEGED = (0x1F, 0x13, 0x12, 0x11, 0x17, 0x1B)
SVC = 0x13
SAVE_RESUME = 0x48                           # OS_SaveContext + 0x48: pc + 4 of its `bx lr`, where a resumed context returns 1


def logging_stub() -> bytes:
    """str r0, [pc, #0]; bx lr; .word 0 -- logs its argument in its own literal, clobbers nothing."""
    return struct.pack("<III", 0xE58F0000, 0xE12FFF1E, NO_HANDLER)


def random_state(rng, mode: int):
    """(cpsr, r1-r12, svc sp, banked sp/lr of `mode`) for a call made in `mode`."""
    flags = rng.getrandbits(4) << 28
    cpsr = flags | (rng.getrandbits(2) << 6) | mode
    return cpsr, [rng.getrandbits(32) for _ in range(12)], rng.getrandbits(30) << 2


def prepare_state(cpsr: int, regs, svc_sp: int):
    def prepare(cpu):
        cpu._write_cpsr(cpsr, 9)
        for i, value in enumerate(regs, 1):
            cpu.r[i] = value
        if cpsr & 0x1F != SVC:
            cpu.set_bank_register(SVC, 13, svc_sp)
    return prepare


def save_context_case(rng, mode: int, label: str):
    cpsr, regs, svc_sp = random_state(rng, mode)
    stub = address("CP_SaveContext")
    saved_sp = STACK_TOP if mode == SVC else svc_sp
    image = [cpsr, 1, CONTEXT + CTX_R, cpsr] + regs[2:] + [STACK_TOP, RETURN_SENTINEL,
                                                            address("OS_SaveContext") + SAVE_RESUME, saved_sp]
    expected = struct.pack("<18I", *image)
    garbage = rng.randbytes(CONTEXT_SIZE)

    def setup(mem):
        poke(mem, stub, logging_stub())
        poke(mem, CONTEXT, garbage)

    def check(cpu):
        problem = first_difference(cpu.mem.bytes(CONTEXT, len(expected)), expected, CONTEXT)
        if problem:
            return problem
        if struct.unpack("<I", cpu.mem.bytes(stub + 8, 4))[0] != CONTEXT + CTX_CP:
            return "CP_SaveContext not called with the divider context"
        if cpu.cpsr != cpsr or cpu.r[13] != STACK_TOP or cpu.bank_register(SVC, 13) != saved_sp:
            return "cpsr 0x%08x / sp / SVC sp changed (model cpsr 0x%08x)" % (cpu.cpsr, cpsr)
        return None

    return Case((CONTEXT,), regs={0: 0}, setup=setup, check=check, label=label,
                prepare=prepare_state(cpsr, regs, svc_sp))


def save_context_cases(rng):
    for mode in PRIVILEGED:
        for _ in range(20):
            yield save_context_case(rng, mode, "mode 0x%02x" % mode)


def load_context_case(rng, mode: int, label: str):
    """Load a context saved in `mode` while running in a random privileged mode."""
    context_cpsr = (rng.getrandbits(4) << 28) | (rng.getrandbits(2) << 6) | mode
    regs = [rng.getrandbits(32) for _ in range(13)]
    user_sp, user_lr, svc_sp = rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32)
    image = struct.pack("<18I", context_cpsr, *regs, user_sp, user_lr, RETURN_SENTINEL + 4, svc_sp)
    stub = address("CPi_RestoreContext")
    caller_cpsr, caller_regs, caller_svc_sp = random_state(rng, rng.choice(PRIVILEGED))

    def setup(mem):
        poke(mem, stub, logging_stub())
        poke(mem, CONTEXT, image)

    def check(cpu):
        if cpu.cpsr != context_cpsr:
            return "cpsr 0x%08x, model 0x%08x" % (cpu.cpsr, context_cpsr)
        user = [cpu.bank_register(0x10, i) for i in range(15)]
        if user != regs + [user_sp, user_lr]:
            return "user bank %s, model %s" % ([hex(v) for v in user], [hex(v) for v in regs + [user_sp, user_lr]])
        if (cpu.bank_register(SVC, 13), cpu.bank_register(SVC, 14)) != (svc_sp, RETURN_SENTINEL + 4):
            return "SVC sp/lr 0x%08x/0x%08x" % (cpu.bank_register(SVC, 13), cpu.bank_register(SVC, 14))
        if cpu.spsr.get("svc") != context_cpsr:
            return "SVC SPSR 0x%08x, model the context's cpsr" % cpu.spsr.get("svc", 0)
        if struct.unpack("<I", cpu.mem.bytes(stub + 8, 4))[0] != CONTEXT + CTX_CP:
            return "CPi_RestoreContext not called with the divider context"
        return None

    return Case((CONTEXT,), setup=setup, check=check, label=label,
                prepare=prepare_state(caller_cpsr, caller_regs, caller_svc_sp))


def load_context_cases(rng):
    for mode in (0x10,) + PRIVILEGED:
        for _ in range(18):
            yield load_context_case(rng, mode, "context mode 0x%02x" % mode)


# -- exceptions -------------------------------------------------------------------------
def bss(name: str) -> int:
    import re
    from verify_sdklib import EU
    text = (EU / "config" / "arm9" / "symbols.txt").read_text(encoding="utf-8")
    return int(re.search(r"^%s kind:bss addr:0x([0-9a-f]+)" % name, text, re.M).group(1), 16)


EXCEPTION_STATE = bss("OSi_ExceptionState")  # debugger handler, user handler argument, -, user handler
EX_CONTEXT = bss("OSi_ExContext")
EX_CONTEXT_SIZE = 0x70
ITCM_END = 0x02000000
CALL_CURSOR = 0x02376000                     # call logger: cursor, then (r0, r1, cpsr, sp, lr) per call
CALL_LOG = 0x02376010
DEBUGGER = 0x02377000
HANDLER = 0x02377040
PU_LOGGER = 0x02377080
EXCEPTION_MODES = (0x17, 0x1B)


def call_logger() -> bytes:
    """mrs r2, cpsr; ldr ip, =CALL_CURSOR; ldr r3, [ip]; stmia r3!, {r0, r1, r2, sp, lr}; str r3, [ip]; bx lr"""
    words = (0xE10F2000, 0xE59FC010, 0xE59C3000, 0xE8A36007, 0xE58C3000, 0xE12FFF1E, 0xE1A00000, CALL_CURSOR)
    return b"".join(struct.pack("<I", w) for w in words)


def logged_calls(mem):
    cursor = struct.unpack("<I", mem.bytes(CALL_CURSOR, 4))[0]
    data = mem.bytes(CALL_LOG, cursor - CALL_LOG)
    return [struct.unpack_from("<5I", data, i) for i in range(0, len(data), 20)]


def return_address_logger() -> bytes:
    """str lr, [pc, #4]; bx lr; nop; .word -- logs its return address, clobbers nothing."""
    return struct.pack("<IIII", 0xE58FE004, 0xE12FFF1E, 0xE1A00000, NO_HANDLER)


def exception_case(rng, mode: int, debugger: bool, label: str):
    """Run OSi_ExceptionHandler in `mode` up to its final wait loop."""
    entry = address("OSi_ExceptionHandler")
    cpsr, regs, _ = random_state(rng, mode)
    args = (rng.getrandbits(32),)
    lr = entry + 0x14 if debugger else RETURN_SENTINEL              # `movne lr, pc` before the debugger call
    saved = struct.pack("<6I", args[0], *regs[0:3], STACK_TOP, lr)
    calls = []
    if mode in EXCEPTION_MODES:     # flags: Z from the TEQ that matched, C from the earlier CMP #0
        calls = [(STACK_TOP & 1, mode, 0x60000000 | (cpsr & 0xC0) | mode, ITCM_END - 0x18,
                  entry + (0x38 if mode == 0x17 else 0x48))]

    def setup(mem):
        poke(mem, EXCEPTION_STATE, struct.pack("<I", DEBUGGER if debugger else 0))
        poke(mem, DEBUGGER, return_address_logger())
        poke(mem, address("OSi_GetAndDisplayContext"), call_logger())
        poke(mem, CALL_CURSOR, struct.pack("<I", CALL_LOG))

    def check(cpu):
        problem = first_difference(cpu.mem.bytes(ITCM_END - 0x18, 0x18), saved, ITCM_END - 0x18)
        if problem:
            return "saved registers: " + problem
        if cpu.r[15] != entry + 0x54 or cpu.z != int(not debugger) or cpu.r[13] != ITCM_END - 0x18:
            return "stopped at 0x%08x Z=%d sp=0x%08x" % (cpu.r[15], cpu.z, cpu.r[13])
        logged = struct.unpack("<I", cpu.mem.bytes(DEBUGGER + 12, 4))[0]
        if logged != (entry + 0x14 if debugger else NO_HANDLER):
            return "debugger handler log 0x%08x" % logged
        got = logged_calls(cpu.mem)
        if got != calls:
            return "OSi_GetAndDisplayContext calls %s, model %s" % (got, calls)
        if cpu.mode != mode:
            return "mode 0x%02x, model 0x%02x" % (cpu.mode, mode)
        return None

    return Case(args, setup=setup, check=check, label=label, prepare=prepare_state(cpsr, regs, 0),
                stop=(entry + 0x54,))


def exception_cases(rng):
    for mode in PRIVILEGED:
        for debugger in (False, True):
            for _ in range(10):
                yield exception_case(rng, mode, debugger, "mode 0x%02x, debugger %s" % (mode, debugger))


def set_ex_context_case(rng, mode: int, target: int, label: str):
    """OSi_SetExContext called in `mode` for an exception taken in `target` mode."""
    cpsr, regs, _ = random_state(rng, mode)
    block, bios = 0x02377100, 0x02377200
    saved_cpsr = (rng.getrandbits(4) << 28) | (rng.getrandbits(3) << 5) | target    # I, F and T random
    words = [rng.getrandbits(32) for _ in range(9)]                                  # r0-r3, lr, BIOS words 0, 2, 3, arg
    target_sp, target_lr = rng.getrandbits(32), rng.getrandbits(32)
    same_bank = Cpu_bank(mode) == Cpu_bank(target)
    if same_bank:
        target_sp, target_lr = STACK_TOP, RETURN_SENTINEL
    garbage = bytearray(rng.randbytes(EX_CONTEXT_SIZE))
    expected = bytearray(garbage)
    struct.pack_into("<5I", expected, 0x00, saved_cpsr, *words[0:4])
    struct.pack_into("<8I", expected, 0x14, *regs[3:11])
    struct.pack_into("<4I", expected, 0x34, words[6], target_sp, target_lr, words[7])
    struct.pack_into("<I", expected, 0x64, words[5])
    struct.pack_into("<I", expected, 0x6C, words[8])
    regs = list(regs)
    regs[11] = block                                                                 # r12 points at the saved block
    stack = bios | rng.getrandbits(1)                                                # bit 0 is masked off

    def setup(mem):
        poke(mem, EX_CONTEXT, bytes(garbage))
        poke(mem, block, struct.pack("<6I", *words[0:4], stack, words[4]))
        poke(mem, bios, struct.pack("<4I", words[5], saved_cpsr, words[6], words[7]))

    def prepare(cpu):
        prepare_state(cpsr, regs, 0)(cpu)
        if not same_bank:
            cpu.set_bank_register(target, 13, target_sp)
            cpu.set_bank_register(target, 14, target_lr)

    def check(cpu):
        problem = first_difference(cpu.mem.bytes(EX_CONTEXT, EX_CONTEXT_SIZE), bytes(expected), EX_CONTEXT)
        if problem:
            return problem
        if cpu.cpsr != cpsr:
            return "cpsr 0x%08x, model 0x%08x" % (cpu.cpsr, cpsr)
        if not same_bank and (cpu.bank_register(target, 13), cpu.bank_register(target, 14)) != (target_sp, target_lr):
            return "target mode sp/lr changed"
        return None

    return Case((words[8],), setup=setup, check=check, label=label, prepare=prepare)


def Cpu_bank(mode: int) -> str:
    from arm_exec import Cpu
    return Cpu.MODES[mode]


def set_ex_context_cases(rng):
    for mode in PRIVILEGED:
        for target in PRIVILEGED:
            for _ in range(4):
                yield set_ex_context_case(rng, mode, target, "in 0x%02x for 0x%02x" % (mode, target))


def display_ex_context_case(rng, mode: int, handler: bool, label: str):
    entry = address("OSi_DisplayExContext")
    cpsr, regs, _ = random_state(rng, mode)
    arg, sys_sp = rng.getrandbits(32), rng.getrandbits(30) << 2
    sys_bank = Cpu_bank(mode) == "usr"
    exception_sp = STACK_TOP - 8                                     # after the C prologue's push {r3, lr}
    if sys_bank:
        sys_sp = exception_sp
    if handler:
        after = (HANDLER & 0x80000000) | 0x20000000 | (cpsr & 0xFF)   # CMP handler, #0: N from bit 31, C set
        calls = [(exception_sp, sys_sp, 0x9F, exception_sp - 8, entry + 0x34),
                 (EX_CONTEXT, arg, 0x9F, exception_sp - 8, entry + 0x50),
                 (EX_CONTEXT, arg, 0x9F, exception_sp - 8, entry + 0x54)]
    else:
        after = 0x60000000 | (cpsr & 0xFF)
        calls = []

    def setup(mem):
        poke(mem, EXCEPTION_STATE + 4, struct.pack("<III", arg, 0, HANDLER if handler else 0))
        poke(mem, HANDLER, call_logger())
        poke(mem, PU_LOGGER, call_logger())
        for stub in (address("OS_EnableProtectionUnit"), address("OS_DisableProtectionUnit")):
            poke(mem, stub, struct.pack("<II", 0xE51FF004, PU_LOGGER))     # ldr pc, [pc, #-4]: 16-byte neighbours
        poke(mem, CALL_CURSOR, struct.pack("<I", CALL_LOG))

    def prepare(cpu):
        prepare_state(cpsr, regs, 0)(cpu)
        if not sys_bank:
            cpu.set_bank_register(0x1F, 13, sys_sp)

    def check(cpu):
        got = logged_calls(cpu.mem)
        if got != calls:
            return "calls %s, model %s" % ([tuple(map(hex, c)) for c in got], [tuple(map(hex, c)) for c in calls])
        if cpu.cpsr != after:
            return "cpsr 0x%08x, model 0x%08x" % (cpu.cpsr, after)
        if cpu.r[13] != STACK_TOP or cpu.bank_register(0x1F, 13) != (STACK_TOP if sys_bank else sys_sp):
            return "sp 0x%08x / system sp 0x%08x not restored" % (cpu.r[13], cpu.bank_register(0x1F, 13))
        return None

    return Case((), setup=setup, check=check, label=label, prepare=prepare)


def display_ex_context_cases(rng):
    for mode in PRIVILEGED:
        for handler in (False, True):
            for _ in range(10):
                yield display_ex_context_case(rng, mode, handler, "mode 0x%02x, handler %s" % (mode, handler))


# -- IRQ thread switch ------------------------------------------------------------------
IRQ_THREAD_QUEUE = 0x027E00A0                # OSi_IrqThreadQueue (DTCM): head, tail
THREAD_INFO = bss("OSi_ThreadInfo")          # u16 isNeedRescheduling, u16 irqDepth, current, list, switchCallback
THREADS = 0x02378000                         # OSThread: OSContext, state (+0x64), list next (+0x68), queue fields
THREAD_STRIDE = 0x100
SWITCH_CALLBACK = 0x023770C0
FRAME = STACK_TOP                            # IRQ stack: lr pushed by OS_IrqHandler, then the BIOS's r0-r3, r12, lr


def thread_switch(info, threads, queue, spsr_irq, frame, user, svc_sp):
    """Model OS_IrqHandler_ThreadSwitch on a snapshot; returns the expected snapshot and outcome.

    `threads` maps an address to a bytearray(0x84); `info` = [resched, current, list, callback];
    `queue` = thread addresses waiting for the IRQ; `user` = the interrupted user-bank r0-r14 view
    (r0-r3 and r12 come from `frame`)."""
    out = {"calls": [], "cpsr": None, "frame": list(frame), "spsr": spsr_irq, "svc_sp": svc_sp, "user": list(user)}
    for t in queue:
        struct.pack_into("<I", threads[t], 0x64, 1)
        struct.pack_into("<III", threads[t], 0x78, 0, 0, 0)
    if queue:
        info[0] = 1
    if info[0] & 0xFFFF == 0:
        return out
    info[0] = 0
    target = info[2]
    while target and struct.unpack_from("<H", threads[target], 0x64)[0] != 1:
        target = struct.unpack_from("<I", threads[target], 0x68)[0]
    if target == 0 or target == info[1]:
        out["cpsr"] = 0x92
        return out
    old = info[1]
    if info[3]:
        out["calls"].append(("callback", old, target))
    info[1] = target
    ctx = threads[old]
    regs = frame[1:5] + user[4:12] + [frame[5]] + user[13:15]          # r0-r3, r4-r11, r12, sp, lr
    struct.pack_into("<15I", ctx, 0x00, spsr_irq, *regs[:14])
    struct.pack_into("<I", ctx, 0x3C, regs[14])
    struct.pack_into("<II", ctx, 0x40, frame[6], svc_sp)
    out["calls"].append(("save", old + CTX_CP))
    out["calls"].append(("restore", target + CTX_CP))
    new = struct.unpack_from("<18I", threads[target], 0)
    out["svc_sp"] = new[17]
    out["spsr"] = (spsr_irq & 0x00FFFF00) | (new[0] & 0xFF0000FF)
    out["user"] = list(new[1:16])
    out["frame"] = [frame[0]] + list(new[1:5]) + [new[13], new[16]]
    out["cpsr"] = 0xD2
    return out


def thread_switch_case(rng, label: str):
    count = rng.randrange(1, 5)
    addresses = [THREADS + THREAD_STRIDE * k for k in range(count)]
    threads = {a: bytearray(rng.randbytes(0x84)) for a in addresses}
    order = addresses[:]
    rng.shuffle(order)
    for a, nxt in zip(order, order[1:] + [0]):
        struct.pack_into("<I", threads[a], 0x68, nxt)
        struct.pack_into("<I", threads[a], 0x64, rng.choice((0, 1, 1, 2)))
        mode = rng.choice((0x1F, 0x1F, 0x10, 0x13))
        struct.pack_into("<I", threads[a], 0x00, (rng.getrandbits(4) << 28) | (rng.getrandbits(2) << 6) | mode)
    queue = rng.sample(addresses, rng.choice((0, 0, 1, 2)) if count > 1 else 0)
    for a, nxt in zip(queue, queue[1:] + [0]):
        struct.pack_into("<I", threads[a], 0x80, nxt)
    current = rng.choice(addresses + [addresses[0]])
    info = [rng.choice((0, 0, 1)), current, order[0], rng.choice((0, SWITCH_CALLBACK))]
    frame = [RETURN_SENTINEL] + [rng.getrandbits(32) for _ in range(6)]
    user = [rng.getrandbits(32) for _ in range(15)]
    spsr_irq = (rng.getrandbits(4) << 28) | (rng.getrandbits(16) << 8) | rng.choice((0x1F, 0x10, 0x13))
    svc_sp = 0x0237A000 - 4 * rng.randrange(0x100)                # the switch pushes on the SVC stack
    before = {a: bytes(b) for a, b in threads.items()}
    info_before = list(info)
    expected = {a: bytearray(b) for a, b in threads.items()}
    out = thread_switch(info, expected, queue, spsr_irq, frame, user, svc_sp)
    resched_after = info[0]

    def setup(mem):
        ensure_mapped(mem, IRQ_TABLE, DTCM_SIZE)
        for a, b in before.items():
            poke(mem, a, b)
        poke(mem, IRQ_THREAD_QUEUE, struct.pack("<II", queue[0] if queue else 0, queue[-1] if queue else 0))
        poke(mem, THREAD_INFO, struct.pack("<HHIII", info_before[0], 0, *info_before[1:]))
        poke(mem, SWITCH_CALLBACK, call_logger())
        poke(mem, CALL_CURSOR, struct.pack("<I", CALL_LOG))
        poke(mem, address("CP_SaveContext"), logging_stub())
        poke(mem, address("CPi_RestoreContext"), logging_stub())
        poke(mem, FRAME, struct.pack("<7I", *frame))

    def prepare(cpu):
        cpu._write_cpsr(0x92, 1)                                        # IRQ mode as the BIOS enters it
        cpu.spsr["irq"] = spsr_irq
        for i in range(4, 12):
            cpu.r[i] = user[i]
        cpu.set_bank_register(0x10, 13, user[13])
        cpu.set_bank_register(0x10, 14, user[14])
        cpu.set_bank_register(SVC, 13, svc_sp)

    def check(cpu):
        for a, b in expected.items():
            problem = first_difference(cpu.mem.bytes(a, 0x84), bytes(b), a)
            if problem:
                return "thread: " + problem
        head = cpu.mem.bytes(IRQ_THREAD_QUEUE, 8)
        if queue and head != bytes(8):
            return "IRQ thread queue not emptied"
        got_info = struct.unpack("<HHII", cpu.mem.bytes(THREAD_INFO, 12))
        if (got_info[0], got_info[2]) != (resched_after, info[1]):
            return "reschedule flag / current thread %s, model %s" % (got_info, (resched_after, info[1]))
        calls = []
        for name, stub in (("save", "CP_SaveContext"), ("restore", "CPi_RestoreContext")):
            value = struct.unpack("<I", cpu.mem.bytes(address(stub) + 8, 4))[0]
            if value != NO_HANDLER:
                calls.append((name, value))
        logged = logged_calls(cpu.mem)
        if logged:
            calls.insert(0, ("callback", logged[0][0], logged[0][1]))
            if len(logged) != 1 or logged[0][2:] != (0x200000D2, FRAME - 12 + 0x0, address("OS_IrqHandler_ThreadSwitch") + 0xC4):
                return "callback state %s" % ([hex(v) for v in logged[0]],)
        if calls != out["calls"]:
            return "calls %s, model %s" % (calls, out["calls"])
        if out["cpsr"] is not None and cpu.cpsr & 0xFF != out["cpsr"]:
            return "cpsr 0x%08x, model control 0x%02x" % (cpu.cpsr, out["cpsr"])
        if cpu.r[13] != FRAME + 4 or cpu.spsr.get("irq") != out["spsr"]:
            return "IRQ sp 0x%08x / SPSR 0x%08x (model 0x%08x)" % (cpu.r[13], cpu.spsr.get("irq", 0), out["spsr"])
        if struct.unpack("<7I", cpu.mem.bytes(FRAME, 28)) != tuple(out["frame"]):
            return "IRQ frame %s, model %s" % (struct.unpack("<7I", cpu.mem.bytes(FRAME, 28)), out["frame"])
        if out["calls"] and [cpu.bank_register(0x10, i) for i in range(15)] != out["user"]:
            return "user bank not loaded from the new context"
        if cpu.bank_register(SVC, 13) != out["svc_sp"]:
            return "SVC sp 0x%08x, model 0x%08x" % (cpu.bank_register(SVC, 13), out["svc_sp"])
        return None

    return Case((), setup=setup, check=check, label=label, prepare=prepare)


def thread_switch_cases(rng):
    for _ in range(160):
        yield thread_switch_case(rng, "random threads")


# -- crt0 entry -------------------------------------------------------------------------
PALETTE, OAM = 0x05000000, 0x07000000
BSS_WINDOW = 0x0237B000
BSS_WINDOW_SIZE = 0x1000
DTCM_END = IRQ_TABLE + DTCM_SIZE
SVC_SP = DTCM_END - 0x40                     # SVC stack top: DTCM + 0x3FC0
IRQ_SP = SVC_SP - 0x40 - 4                   # IRQ stack, 8-byte rounding leaves 0x027E3F7C
SYS_SP = ((IRQ_SP + 4 - 0x800 - 4) & ~7)     # system stack below the 0x800-byte IRQ stack: 0x027E3778


def entry_case(rng, mode: int, bss_start: int, bss_size: int, label: str):
    entry = address("Entry")
    dtcm, palette, oam = rng.randbytes(DTCM_SIZE), rng.randbytes(0x400), rng.randbytes(0x400)
    window = bytearray(rng.randbytes(BSS_WINDOW_SIZE))
    compressed_end = rng.getrandbits(32)
    start, end = BSS_WINDOW + bss_start, BSS_WINDOW + bss_start + bss_size
    after = bytearray(window)
    p = start
    while p < end:
        struct.pack_into("<I", after, p - BSS_WINDOW, 0)
        p += 4
    log, line = [], start & ~0x1F
    while True:
        log += [(10, 4, 0), (5, 1, line), (14, 1, line)]
        line += 0x20
        if not s32((line - end) & MASK) < 0:
            break
    dtcm_after = bytearray(DTCM_SIZE)
    struct.pack_into("<I", dtcm_after, DTCM_SIZE - 4, address("OS_IrqHandler"))
    calls = [(address("func_02000a78"), entry + 0x18), (address("MIi_UncompressBackward"), entry + 0xA4),
             (address("INITi_DoAutoload"), entry + 0xA8), (address("RunGlobalConstructors"), entry + 0x10C)]

    def setup(mem):
        ensure_mapped(mem, IO, 0x1000)
        ensure_mapped(mem, IRQ_TABLE, DTCM_SIZE)
        ensure_mapped(mem, SHARED, SHARED_SIZE)
        ensure_mapped(mem, PALETTE, 0x400)
        ensure_mapped(mem, OAM, 0x400)
        poke(mem, IRQ_TABLE, dtcm)
        poke(mem, PALETTE, palette)
        poke(mem, OAM, oam)
        poke(mem, BSS_WINDOW, bytes(window))
        poke(mem, REG_IME, struct.pack("<I", 1))
        poke(mem, IO + 6, struct.pack("<H", 0))                       # VCOUNT: already on line 0
        poke(mem, 0x02FFFF9C, struct.pack("<I", 0xFFFFFFFF))
        info = bytearray(mem.bytes(AUTOLOAD_INFO, 0x18))
        struct.pack_into("<III", info, 0x0C, start, end, compressed_end)
        poke(mem, AUTOLOAD_INFO, bytes(info))
        for target, _ in calls:
            poke(mem, target, call_logger())
        poke(mem, CALL_CURSOR, struct.pack("<I", CALL_LOG))

    def check(cpu):
        got_log, cpu.cp15_log = cpu.cp15_log, []
        if got_log != log:
            return "%d CP15 ops, model %d" % (len(got_log), len(log))
        for base, want, what in ((IRQ_TABLE, bytes(dtcm_after), "DTCM"), (PALETTE, bytes(0x400), "palette"),
                                 (OAM, struct.pack("<I", 0x200) * 0x100, "OAM"), (BSS_WINDOW, bytes(after), "bss")):
            problem = first_difference(cpu.mem.bytes(base, len(want)), want, base)
            if problem:
                return what + ": " + problem
        words = [struct.unpack("<I", cpu.mem.bytes(a, 4))[0] for a in (REG_IME, 0x02FFFF9C)]
        if words != [IO, 0]:
            return "IME / boot word %s" % [hex(w) for w in words]
        got = logged_calls(cpu.mem)
        if [(c[4]) for c in got] != [lr for _, lr in calls]:
            return "calls returning to %s, model %s" % ([hex(c[4]) for c in got], [hex(lr) for _, lr in calls])
        if got[1][0] != compressed_end:
            return "MIi_UncompressBackward(0x%08x), model 0x%08x" % (got[1][0], compressed_end)
        if [c[2] & 0xFF for c in got[1:]] != [0x1F] * 3 or [c[3] for c in got[1:]] != [SYS_SP] * 3:
            return "later calls not in system mode on the system stack"
        if cpu.r[15] != address("main") or cpu.r[14] != 0xFFFF0000 or cpu.cpsr & 0xFF != 0x1F:
            return "stopped at 0x%08x, lr 0x%08x, cpsr 0x%08x" % (cpu.r[15], cpu.r[14], cpu.cpsr)
        stacks = (cpu.r[13], cpu.bank_register(0x12, 13), cpu.bank_register(SVC, 13))
        if stacks != (SYS_SP, IRQ_SP, SVC_SP):
            return "system/IRQ/SVC sp %s, model %s" % ([hex(s) for s in stacks], [hex(s) for s in (SYS_SP, IRQ_SP, SVC_SP)])
        return None

    def prepare(cpu):
        cpu._write_cpsr(0xC0 | mode, 1)                                 # reset state: interrupts masked

    return Case((), setup=setup, check=check, label=label, prepare=prepare, stop=(address("main"),))


def entry_cases(rng):
    for mode in (SVC, 0x1F):
        yield entry_case(rng, mode, 0, 0, "empty .bss")
        yield entry_case(rng, mode, 0x40, 0x20, "one cache line")
        yield entry_case(rng, mode, 0x44, 0x1E, "unaligned .bss")
    for _ in range(100):
        start = rng.randrange(0, 0x200) * 4
        size = rng.choice((0, 4, rng.randrange(1, 0x200), rng.randrange(0, 0x100) * 4))
        yield entry_case(rng, rng.choice((SVC, SVC, 0x1F, 0x12)), start, size, "random .bss")


ROUTINES = [
    Routine("Entry", "src/asm_stubs/calls/Entry.c", DOC, entry_cases),
    Routine("INITi_DoAutoload", "src/asm_stubs/calls/INITi_DoAutoload.c", DOC, autoload_cases),
    Routine("OS_IrqHandler", "libs/nitro/os/asm_stubs/calls/OS_IrqHandler.c", DOC, irq_cases),
    Routine("OS_IrqHandler_ThreadSwitch", "src/asm_stubs/calls/OS_IrqHandler_ThreadSwitch.c", DOC,
            thread_switch_cases),
    Routine("OSi_DoBoot", "libs/nitro/os/asm_stubs/calls/OSi_DoBoot.c", DOC, boot_cases),
    Routine("OSi_ReloadRomData", "libs/nitro/os/asm_stubs/calls/OSi_ReloadRomData.c", DOC, reload_cases,
            object_gate=True),
    Routine("OS_SaveContext", "libs/nitro/os/asm_stubs/calls/OS_SaveContext.c", DOC, save_context_cases),
    Routine("OS_LoadContext", "libs/nitro/os/asm_stubs/calls/OS_LoadContext.c", DOC, load_context_cases),
    Routine("OSi_ExceptionHandler", "libs/nitro/os/asm_stubs/calls/OSi_ExceptionHandler.c", DOC, exception_cases,
            unreachable=((address("OSi_ExceptionHandler") + 0x60, address("OSi_ExceptionHandler") + 0x6C),)),
    Routine("OSi_SetExContext", "libs/nitro/os/asm_stubs/calls/OSi_SetExContext.c", DOC, set_ex_context_cases),
    Routine("OSi_DisplayExContext", "libs/nitro/os/asm_stubs/calls/OSi_DisplayExContext.c", DOC,
            display_ex_context_cases),
]
