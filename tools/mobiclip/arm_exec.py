#!/usr/bin/env python3
"""A small ARMv5TE interpreter (ARM state, and a strict THUMB subset) for replaying original code.

Hand-written middleware routines that live in DATA (the MobiClip decoder's
in-place kernels in ov022) cannot be compared with a C build, so their semantic
reimplementations are checked by running the ROM's own instructions on the same
inputs. This interpreter covers the ARM-state integer instruction set those
routines use: data processing with every shifter form, MUL/MLA and the long and
DSP multiplies, CLZ, single/halfword/doubleword transfers with every addressing
mode, LDM/STM, SWP/SWPB, B/BL/BX/BLX, MRS/MSR restricted to the CPSR condition flags
(the runtime compare helpers return their result there), and the ARM946E-S CP15
c7 cache and write-buffer maintenance MCRs, which change no architectural state
and are only recorded in `Cpu.cp15_log`. An ARM SWI is recorded in
`Cpu.swi_log` with r0-r3 and otherwise skipped: the BIOS is not emulated, so
the registers reach the next instruction unchanged. It refuses anything else
(other coprocessor operations, mode or control-field changes) instead of
guessing.

THUMB state covers the 16-bit formats the SDK's THUMB routines use: shifts by
an immediate, ADD/SUB register or 3-bit immediate, MOV/CMP/ADD/SUB 8-bit
immediate, the sixteen ALU operations, hi-register ADD/CMP/MOV and BX/BLX,
PC-relative LDR, loads and stores with a register or immediate offset (word,
byte, halfword, signed), PUSH/POP, LDMIA/STMIA, conditional and unconditional
B, the BL/BLX prefix-suffix pair (run as one 4-byte instruction) and SWI,
logged in `Cpu.swi_log` as (8-bit comment, r0-r3). SP-relative transfers,
ADD to SP/PC, BKPT, undefined and UNPREDICTABLE encodings are refused. BX,
BLX, POP {pc} and ARM LDR/LDM into pc switch state on bit 0 as ARMv5 does;
`call()` takes a THUMB entry as address | 1.

    cpu = Cpu(Memory())
    cpu.mem.map(0x020b715c, code_bytes)
    cpu.call(0x020b715c, [r0, r1, r2, r3])
"""

from __future__ import annotations

MASK = 0xFFFFFFFF
RETURN_SENTINEL = 0xFFFFFFF0


class ArmFault(Exception):
    pass


class Memory:
    """Flat little-endian memory made of mapped regions."""

    def __init__(self):
        self.regions = []                       # [start, end, bytearray]

    def map(self, start: int, data=None, size: int | None = None) -> bytearray:
        buf = bytearray(data if data is not None else bytes(size or 0))
        for lo, hi, _ in self.regions:
            if start < hi and lo < start + len(buf):
                raise ArmFault("region 0x%08x overlaps an existing mapping" % start)
        self.regions.append([start, start + len(buf), buf])
        return buf

    def _find(self, address: int, size: int):
        for lo, hi, buf in self.regions:
            if lo <= address and address + size <= hi:
                return buf, address - lo
        raise ArmFault("unmapped access of %d bytes at 0x%08x" % (size, address))

    def read(self, address: int, size: int) -> int:
        buf, off = self._find(address, size)
        return int.from_bytes(buf[off:off + size], "little")

    def write(self, address: int, size: int, value: int) -> None:
        buf, off = self._find(address, size)
        buf[off:off + size] = (value & ((1 << (8 * size)) - 1)).to_bytes(size, "little")

    def bytes(self, address: int, size: int) -> bytes:
        buf, off = self._find(address, size)
        return bytes(buf[off:off + size])


def _sx(value: int, bits: int) -> int:
    value &= (1 << bits) - 1
    return value - (1 << bits) if value >> (bits - 1) else value


def _s32(value: int) -> int:
    return _sx(value, 32)


class Cpu:
    def __init__(self, mem: Memory):
        self.mem = mem
        self.r = [0] * 16
        self.n = self.z = self.c = self.v = 0
        self.thumb = False
        self.steps = 0
        self.cp15_log = []                      # (CRm, opcode2, Rd value) per c7 maintenance op
        self.swi_log = []                       # (comment, (r0, r1, r2, r3)) per SWI: 24-bit ARM, 8-bit THUMB

    # -- helpers -----------------------------------------------------------------
    def _reg(self, index: int, pc_offset: int = 8) -> int:
        if index == 15:
            return (self.pc + pc_offset) & MASK
        return self.r[index]

    def _cond(self, cond: int) -> bool:
        n, z, c, v = self.n, self.z, self.c, self.v
        return [
            z, not z, c, not c, n, not n, v, not v,
            c and not z, (not c) or z, n == v, n != v,
            (not z) and n == v, z or n != v, True,
        ][cond] if cond < 15 else False

    def _shift(self, value: int, kind: int, amount: int, by_register: bool):
        """Barrel shifter: returns (result, carry_out)."""
        c = self.c
        if kind == 0:                                   # LSL
            if amount == 0:
                return value, c
            if amount < 32:
                return (value << amount) & MASK, (value >> (32 - amount)) & 1
            if amount == 32:
                return 0, value & 1
            return 0, 0
        if kind == 1:                                   # LSR
            if amount == 0:
                if by_register:
                    return value, c
                amount = 32
            if amount < 32:
                return value >> amount, (value >> (amount - 1)) & 1
            if amount == 32:
                return 0, value >> 31
            return 0, 0
        if kind == 2:                                   # ASR
            if amount == 0:
                if by_register:
                    return value, c
                amount = 32
            if amount < 32:
                return (_s32(value) >> amount) & MASK, (value >> (amount - 1)) & 1
            bit = value >> 31
            return (MASK if bit else 0), bit
        # ROR / RRX
        if amount == 0:
            if by_register:
                return value, c
            return ((c << 31) | (value >> 1)) & MASK, value & 1
        amount &= 31
        if amount == 0:
            return value, value >> 31
        result = ((value >> amount) | (value << (32 - amount))) & MASK
        return result, result >> 31

    def _operand2(self, ins: int):
        if ins & (1 << 25):
            imm = ins & 0xFF
            rot = ((ins >> 8) & 0xF) * 2
            value = ((imm >> rot) | (imm << (32 - rot))) & MASK if rot else imm
            return value, (value >> 31 if rot else self.c)
        rm = ins & 0xF
        kind = (ins >> 5) & 3
        if ins & 0x10:
            amount = self._reg((ins >> 8) & 0xF) & 0xFF
            return self._shift(self._reg(rm, 12), kind, amount, True)
        return self._shift(self._reg(rm), kind, (ins >> 7) & 0x1F, False)

    def _set_nz(self, value: int) -> None:
        self.n = value >> 31
        self.z = int(value == 0)

    def _write_reg(self, index: int, value: int) -> None:
        value &= MASK
        if index == 15:
            if value & 1:
                raise ArmFault("switch to THUMB state at 0x%08x" % self.pc)
            self.next_pc = value & ~3
        else:
            self.r[index] = value

    def _interwork(self, target: int) -> None:
        """BX-style branch: bit 0 selects THUMB; an ARM target must be word-aligned."""
        target &= MASK
        if target & 1:
            self.thumb = True
            self.next_pc = target & ~1
        elif target & 2:
            raise ArmFault("unaligned ARM branch target 0x%08x at 0x%08x" % (target, self.pc))
        else:
            self.thumb = False
            self.next_pc = target

    def _load_reg(self, index: int, value: int) -> None:
        """A loaded value: into pc it interworks (ARMv5 LDR/LDM/POP)."""
        if index == 15:
            self._interwork(value)
        else:
            self.r[index] = value & MASK

    # -- instruction classes -----------------------------------------------------
    def _data_processing(self, ins: int) -> None:
        opcode = (ins >> 21) & 0xF
        s = (ins >> 20) & 1
        rn = (ins >> 16) & 0xF
        rd = (ins >> 12) & 0xF
        op2, shifter_carry = self._operand2(ins)
        a = self._reg(rn, 12 if (not ins & (1 << 25) and ins & 0x10) else 8)
        c_in = self.c
        logical = opcode in (0, 1, 8, 9, 12, 13, 14, 15)
        if opcode in (0, 8):
            result = a & op2
        elif opcode in (1, 9):
            result = a ^ op2
        elif opcode in (2, 10):
            result, carry, overflow = self._add(a, (~op2) & MASK, 1)
        elif opcode == 3:
            result, carry, overflow = self._add(op2, (~a) & MASK, 1)
        elif opcode in (4, 11):
            result, carry, overflow = self._add(a, op2, 0)
        elif opcode == 5:
            result, carry, overflow = self._add(a, op2, c_in)
        elif opcode == 6:
            result, carry, overflow = self._add(a, (~op2) & MASK, c_in)
        elif opcode == 7:
            result, carry, overflow = self._add(op2, (~a) & MASK, c_in)
        elif opcode == 12:
            result = a | op2
        elif opcode == 13:
            result = op2
        elif opcode == 14:
            result = a & ~op2 & MASK
        else:
            result = (~op2) & MASK
        if 8 <= opcode <= 11:
            if not s:
                raise ArmFault("unsupported status-register instruction 0x%08x" % ins)
        else:
            if s and rd == 15:
                raise ArmFault("mode-changing data processing at 0x%08x" % self.pc)
            self._write_reg(rd, result)
        if s:
            self._set_nz(result)
            if logical:
                self.c = shifter_carry
            else:
                self.c, self.v = carry, overflow

    @staticmethod
    def _add(a: int, b: int, carry_in: int):
        total = a + b + carry_in
        result = total & MASK
        carry = int(total > MASK)
        overflow = int(((a ^ result) & (b ^ result)) >> 31 & 1)
        return result, carry, overflow

    def _multiply(self, ins: int) -> None:
        rd = (ins >> 16) & 0xF
        rn = (ins >> 12) & 0xF
        rs = (ins >> 8) & 0xF
        rm = ins & 0xF
        result = (self.r[rm] * self.r[rs]) & MASK
        if ins & (1 << 21):
            result = (result + self.r[rn]) & MASK
        self._write_reg(rd, result)
        if ins & (1 << 20):
            self._set_nz(result)

    def _multiply_long(self, ins: int) -> None:
        hi = (ins >> 16) & 0xF
        lo = (ins >> 12) & 0xF
        rs = (ins >> 8) & 0xF
        rm = ins & 0xF
        signed = ins & (1 << 22)
        a = _s32(self.r[rm]) if signed else self.r[rm]
        b = _s32(self.r[rs]) if signed else self.r[rs]
        product = a * b
        if ins & (1 << 21):
            product += (self.r[hi] << 32) | self.r[lo]
        product &= (1 << 64) - 1
        self.r[lo] = product & MASK
        self.r[hi] = product >> 32
        if ins & (1 << 20):
            self.n = product >> 63
            self.z = int(product == 0)

    def _dsp_multiply(self, ins: int) -> None:
        op = (ins >> 21) & 3
        rd = (ins >> 16) & 0xF
        rn = (ins >> 12) & 0xF
        rs = (ins >> 8) & 0xF
        rm = ins & 0xF
        x = (ins >> 5) & 1
        y = (ins >> 6) & 1
        m = _sx(self.r[rm] >> (16 * x), 16)
        s = _sx(self.r[rs] >> (16 * y), 16)
        if op == 0:                                     # SMLAxy
            product = m * s
            total = product + _s32(self.r[rn])
            self._write_reg(rd, total)
        elif op == 1:                                   # SMLAWy / SMULWy
            product = (_s32(self.r[rm]) * s) >> 16
            if x:
                self._write_reg(rd, product)
            else:
                self._write_reg(rd, product + _s32(self.r[rn]))
        elif op == 2:                                   # SMLALxy
            acc = ((self.r[rd] << 32) | self.r[rn]) + m * s
            acc &= (1 << 64) - 1
            self.r[rn] = acc & MASK
            self.r[rd] = acc >> 32
        else:                                           # SMULxy
            self._write_reg(rd, m * s)

    def _address(self, base: int, offset: int, pre: bool, up: bool):
        target = (base + offset if up else base - offset) & MASK
        return (target if pre else base), target

    def _single_transfer(self, ins: int) -> None:
        pre = (ins >> 24) & 1
        up = (ins >> 23) & 1
        byte = (ins >> 22) & 1
        wb = (ins >> 21) & 1
        load = (ins >> 20) & 1
        rn = (ins >> 16) & 0xF
        rd = (ins >> 12) & 0xF
        if ins & (1 << 25):
            if ins & 0x10:
                raise ArmFault("register-shifted transfer offset at 0x%08x" % self.pc)
            offset, _ = self._shift(self._reg(ins & 0xF), (ins >> 5) & 3, (ins >> 7) & 0x1F, False)
        else:
            offset = ins & 0xFFF
        base = self._reg(rn)
        address, updated = self._address(base, offset, pre, up)
        if load:
            if byte:
                value = self.mem.read(address, 1)
            else:
                word = self.mem.read(address & ~3, 4)
                rot = (address & 3) * 8
                value = ((word >> rot) | (word << (32 - rot))) & MASK if rot else word
        else:
            value = self._reg(rd, 12)
            if byte:
                self.mem.write(address, 1, value)
            else:
                self.mem.write(address & ~3, 4, value)
        if (not pre or wb) and not (load and rn == rd):
            self._write_reg(rn, updated)
        if load:
            self._load_reg(rd, value)

    def _halfword_transfer(self, ins: int) -> None:
        pre = (ins >> 24) & 1
        up = (ins >> 23) & 1
        wb = (ins >> 21) & 1
        load = (ins >> 20) & 1
        rn = (ins >> 16) & 0xF
        rd = (ins >> 12) & 0xF
        sh = (ins >> 5) & 3
        if ins & (1 << 22):
            offset = ((ins >> 4) & 0xF0) | (ins & 0xF)
        else:
            offset = self._reg(ins & 0xF)
        base = self._reg(rn)
        address, updated = self._address(base, offset, pre, up)
        writes_base = (not pre or wb)
        if load:
            if sh == 1:
                value = self.mem.read(address, 2)
            elif sh == 2:
                value = _sx(self.mem.read(address, 1), 8) & MASK
            else:
                value = _sx(self.mem.read(address, 2), 16) & MASK
            if writes_base and rn != rd:
                self._write_reg(rn, updated)
            self._write_reg(rd, value)
            return
        if sh == 1:                                     # STRH
            self.mem.write(address, 2, self._reg(rd, 12))
        elif sh == 2:                                   # LDRD
            if rd & 1 or rd == 14:
                raise ArmFault("LDRD with an odd register at 0x%08x" % self.pc)
            lo = self.mem.read(address, 4)
            hi = self.mem.read(address + 4, 4)
            if writes_base:
                self._write_reg(rn, updated)
            self._write_reg(rd, lo)
            self._write_reg(rd + 1, hi)
            return
        else:                                           # STRD
            if rd & 1 or rd == 14:
                raise ArmFault("STRD with an odd register at 0x%08x" % self.pc)
            self.mem.write(address, 4, self._reg(rd, 12))
            self.mem.write(address + 4, 4, self._reg(rd + 1, 12))
        if writes_base:
            self._write_reg(rn, updated)

    def _block_transfer(self, ins: int) -> None:
        pre = (ins >> 24) & 1
        up = (ins >> 23) & 1
        if ins & (1 << 22):
            raise ArmFault("user-bank LDM/STM at 0x%08x" % self.pc)
        wb = (ins >> 21) & 1
        load = (ins >> 20) & 1
        rn = (ins >> 16) & 0xF
        regs = [i for i in range(16) if ins & (1 << i)]
        if not regs:
            raise ArmFault("empty register list at 0x%08x" % self.pc)
        base = self.r[rn]
        count = len(regs)
        if up:
            start = base + 4 if pre else base
            final = base + 4 * count
        else:
            start = base - 4 * count if pre else base - 4 * count + 4
            final = base - 4 * count
        start &= MASK
        address = start
        values = {}
        for reg in regs:
            if load:
                values[reg] = self.mem.read(address, 4)
            else:
                self.mem.write(address, 4, self._reg(reg, 12))
            address += 4
        if wb and not (load and rn in regs):
            self.r[rn] = final & MASK
        for reg in regs:
            if reg in values:
                self._load_reg(reg, values[reg])

    def _swap(self, ins: int) -> None:
        """SWP/SWPB Rd, Rm, [Rn]: read the old value, then write Rm, as one locked access.

        Refuses the UNPREDICTABLE forms (any register r15, Rn equal to Rd or
        Rm) and a word swap on an unaligned address."""
        byte = (ins >> 22) & 1
        rn = (ins >> 16) & 0xF
        rd = (ins >> 12) & 0xF
        rm = ins & 0xF
        if 15 in (rn, rd, rm) or rn in (rd, rm):
            raise ArmFault("unpredictable swap 0x%08x at 0x%08x" % (ins, self.pc))
        address = self.r[rn]
        if not byte and address & 3:
            raise ArmFault("unaligned SWP at 0x%08x" % self.pc)
        size = 1 if byte else 4
        old = self.mem.read(address, size)
        self.mem.write(address, size, self.r[rm])
        self._write_reg(rd, old)

    def _status_access(self, ins: int) -> None:
        """MRS from CPSR and MSR to the CPSR flag field only."""
        flags = (self.n << 31) | (self.z << 30) | (self.c << 29) | (self.v << 28)
        if (ins & 0x0FFF0FFF) == 0x010F0000:            # MRS rd, CPSR
            self._write_reg((ins >> 12) & 0xF, flags | 0x1F)
            return
        if (ins & 0x0FFFFFF0) == 0x0128F000:            # MSR CPSR_f, rm
            value = self.r[ins & 0xF]
        elif (ins & 0x0FFFF000) == 0x0328F000:          # MSR CPSR_f, #imm
            rotate = ((ins >> 8) & 0xF) * 2
            value = ((ins & 0xFF) >> rotate | (ins & 0xFF) << (32 - rotate)) & MASK
        else:
            raise ArmFault("status-register access 0x%08x at 0x%08x" % (ins, self.pc))
        self.n, self.z, self.c, self.v = (value >> 31) & 1, (value >> 30) & 1, (value >> 29) & 1, (value >> 28) & 1

    # ARM946E-S CP15 c7 operations (CRm, opcode2) on caches and the write buffer:
    # invalidate I-cache (all / line), invalidate D-cache (all / line), clean D line
    # (address / index), drain write buffer, prefetch I line, clean+invalidate D line
    # (address / index). Wait-for-interrupt (c0,4 and c8,2) is not among them.
    CP15_C7_MAINTENANCE = {(5, 0), (5, 1), (6, 0), (6, 1), (10, 1), (10, 2), (10, 4), (13, 1), (14, 1), (14, 2)}

    def _coprocessor(self, ins: int) -> None:
        """MCR p15, 0, Rd, c7, CRm, op2 for cache/write-buffer maintenance only: recorded, no effect."""
        crm, opcode2, rd = ins & 0xF, (ins >> 5) & 7, (ins >> 12) & 0xF
        if (ins & 0x0FFF0F10) != 0x0E070F10 or (crm, opcode2) not in self.CP15_C7_MAINTENANCE or rd == 15:
            raise ArmFault("coprocessor instruction 0x%08x at 0x%08x" % (ins, self.pc))
        self.cp15_log.append((crm, opcode2, self.r[rd]))

    # -- THUMB state ---------------------------------------------------------------
    def _thumb_fault(self, ins: int, what: str = "unsupported THUMB instruction"):
        raise ArmFault("%s 0x%04x at 0x%08x" % (what, ins, self.pc))

    def _thumb_step(self) -> None:
        self.pc = self.r[15]
        if self.pc & 1:
            raise ArmFault("odd THUMB pc 0x%08x" % self.pc)
        ins = self.mem.read(self.pc, 2)
        self.next_pc = (self.pc + 2) & MASK
        self.steps += 1
        self._thumb_execute(ins)
        self.r[15] = self.next_pc

    def _thumb_execute(self, ins: int) -> None:
        top = ins >> 11
        if top <= 2:                                    # format 1: LSL/LSR/ASR Rd, Rs, #imm5
            value, carry = self._shift(self.r[(ins >> 3) & 7], top, (ins >> 6) & 0x1F, False)
            self.r[ins & 7] = value
            self._set_nz(value)
            self.c = carry
        elif top == 3:                                  # format 2: ADD/SUB Rd, Rs, Rn|#imm3
            a = self.r[(ins >> 3) & 7]
            b = (ins >> 6) & 7 if ins & 0x400 else self.r[(ins >> 6) & 7]
            if ins & 0x200:
                result, self.c, self.v = self._add(a, (~b) & MASK, 1)
            else:
                result, self.c, self.v = self._add(a, b, 0)
            self.r[ins & 7] = result
            self._set_nz(result)
        elif top <= 7:                                  # format 3: MOV/CMP/ADD/SUB Rd, #imm8
            op, rd, imm = (ins >> 11) & 3, (ins >> 8) & 7, ins & 0xFF
            if op == 0:
                result = imm
            elif op == 2:
                result, self.c, self.v = self._add(self.r[rd], imm, 0)
            else:
                result, self.c, self.v = self._add(self.r[rd], (~imm) & MASK, 1)
            if op != 1:
                self.r[rd] = result
            self._set_nz(result)
        elif (ins >> 10) == 0x10:                       # format 4: ALU operations
            self._thumb_alu(ins)
        elif (ins >> 10) == 0x11:                       # format 5: hi-register operations, BX/BLX
            self._thumb_hi(ins)
        elif top == 9:                                  # format 6: LDR Rd, [pc, #imm8*4]
            address = ((self.pc + 4) & ~3) + (ins & 0xFF) * 4
            self.r[(ins >> 8) & 7] = self.mem.read(address, 4)
        elif (ins >> 12) == 5:                          # formats 7/8: register offset
            address = (self.r[(ins >> 3) & 7] + self.r[(ins >> 6) & 7]) & MASK
            kind = ("str", "strh", "strb", "ldrsb", "ldr", "ldrh", "ldrb", "ldrsh")[(ins >> 9) & 7]
            self._thumb_transfer(ins & 7, address, kind)
        elif (ins >> 13) == 3:                          # format 9: immediate offset, word/byte
            byte, load = (ins >> 12) & 1, (ins >> 11) & 1
            offset = ((ins >> 6) & 0x1F) * (1 if byte else 4)
            address = (self.r[(ins >> 3) & 7] + offset) & MASK
            self._thumb_transfer(ins & 7, address, ("str", "ldr", "strb", "ldrb")[byte * 2 + load])
        elif (ins >> 12) == 8:                          # format 10: immediate offset, halfword
            address = (self.r[(ins >> 3) & 7] + ((ins >> 6) & 0x1F) * 2) & MASK
            self._thumb_transfer(ins & 7, address, "ldrh" if ins & 0x800 else "strh")
        elif (ins & 0xF600) == 0xB400:                  # format 14: PUSH {list, lr} / POP {list, pc}
            self._thumb_push_pop(ins)
        elif (ins >> 12) == 0xC:                        # format 15: LDMIA/STMIA Rb!, {list}
            self._thumb_multiple(ins)
        elif (ins >> 12) == 0xD:
            cond = (ins >> 8) & 0xF
            if cond == 0xF:                             # format 17: SWI, logged, BIOS not run
                self.swi_log.append((ins & 0xFF, tuple(self.r[0:4])))
            elif cond == 0xE:
                self._thumb_fault(ins, "undefined THUMB instruction")
            elif self._cond(cond):                      # format 16: B<cond>
                self.next_pc = (self.pc + 4 + (_sx(ins & 0xFF, 8) << 1)) & MASK
        elif top == 0x1C:                               # format 18: B
            self.next_pc = (self.pc + 4 + (_sx(ins & 0x7FF, 11) << 1)) & MASK
        elif top == 0x1E:                               # format 19: BL/BLX prefix + suffix
            self._thumb_long_branch(ins)
        else:
            self._thumb_fault(ins)

    def _thumb_transfer(self, rd: int, address: int, kind: str) -> None:
        size = {"ldr": 4, "str": 4, "ldrh": 2, "strh": 2, "ldrsh": 2}.get(kind, 1)
        if address % size:
            raise ArmFault("unaligned THUMB %s at 0x%08x (address 0x%08x)" % (kind, self.pc, address))
        if kind.startswith("str"):
            self.mem.write(address, size, self.r[rd])
            return
        value = self.mem.read(address, size)
        if kind == "ldrsb":
            value = _sx(value, 8) & MASK
        elif kind == "ldrsh":
            value = _sx(value, 16) & MASK
        self.r[rd] = value

    def _thumb_alu(self, ins: int) -> None:
        op, rd, rm = (ins >> 6) & 0xF, ins & 7, (ins >> 3) & 7
        a, b = self.r[rd], self.r[rm]
        write = True
        if op == 0:                                     # AND
            result = a & b
        elif op == 1:                                   # EOR
            result = a ^ b
        elif op in (2, 3, 4, 7):                        # LSL, LSR, ASR, ROR by register
            result, self.c = self._shift(a, {2: 0, 3: 1, 4: 2, 7: 3}[op], b & 0xFF, True)
        elif op == 5:                                   # ADC
            result, self.c, self.v = self._add(a, b, self.c)
        elif op == 6:                                   # SBC
            result, self.c, self.v = self._add(a, (~b) & MASK, self.c)
        elif op == 8:                                   # TST
            result, write = a & b, False
        elif op == 9:                                   # NEG
            result, self.c, self.v = self._add(0, (~b) & MASK, 1)
        elif op == 10:                                  # CMP
            (result, self.c, self.v), write = self._add(a, (~b) & MASK, 1), False
        elif op == 11:                                  # CMN
            (result, self.c, self.v), write = self._add(a, b, 0), False
        elif op == 12:                                  # ORR
            result = a | b
        elif op == 13:                                  # MUL (ARMv5: C and V unaffected)
            result = (a * b) & MASK
        elif op == 14:                                  # BIC
            result = a & ~b & MASK
        else:                                           # MVN
            result = (~b) & MASK
        if write:
            self.r[rd] = result
        self._set_nz(result)

    def _thumb_hi(self, ins: int) -> None:
        op, h1, h2 = (ins >> 8) & 3, (ins >> 7) & 1, (ins >> 6) & 1
        rd, rm = (ins & 7) | (h1 << 3), ((ins >> 3) & 7) | (h2 << 3)
        value = (self.pc + 4) & MASK if rm == 15 else self.r[rm]
        if op == 3:                                     # BX / BLX Rm
            if ins & 7:
                self._thumb_fault(ins, "BX/BLX with non-zero SBZ bits")
            if h1:
                if rm == 15:
                    self._thumb_fault(ins, "BLX pc")
                self.r[14] = ((self.pc + 2) | 1) & MASK
            self._interwork(value)
            return
        if not (h1 or h2):
            self._thumb_fault(ins, "UNPREDICTABLE low-register hi operation")
        current = (self.pc + 4) & MASK if rd == 15 else self.r[rd]
        if op == 1:                                     # CMP
            result, self.c, self.v = self._add(current, (~value) & MASK, 1)
            self._set_nz(result)
            return
        result = (current + value) & MASK if op == 0 else value
        if rd == 15:                                    # ADD/MOV pc: branch, stays THUMB
            self.next_pc = result & ~1
        else:
            self.r[rd] = result

    def _thumb_push_pop(self, ins: int) -> None:
        load, extra = (ins >> 11) & 1, (ins >> 8) & 1
        regs = [i for i in range(8) if ins & (1 << i)] + ([15 if load else 14] if extra else [])
        if not regs:
            self._thumb_fault(ins, "empty PUSH/POP list")
        sp = self.r[13]
        if sp & 3:
            raise ArmFault("unaligned sp 0x%08x at 0x%08x" % (sp, self.pc))
        if load:
            values = [self.mem.read(sp + 4 * k, 4) for k in range(len(regs))]
            self.r[13] = (sp + 4 * len(regs)) & MASK
            for reg, value in zip(regs, values):
                self._load_reg(reg, value)
        else:
            sp = (sp - 4 * len(regs)) & MASK
            for k, reg in enumerate(regs):
                self.mem.write(sp + 4 * k, 4, self.r[reg])
            self.r[13] = sp

    def _thumb_multiple(self, ins: int) -> None:
        load, rb = (ins >> 11) & 1, (ins >> 8) & 7
        regs = [i for i in range(8) if ins & (1 << i)]
        if not regs:
            self._thumb_fault(ins, "empty LDMIA/STMIA list")
        if not load and rb in regs and rb != regs[0]:
            self._thumb_fault(ins, "UNPREDICTABLE STMIA storing a written-back base")
        base = self.r[rb]
        if base & 3:
            raise ArmFault("unaligned LDMIA/STMIA base 0x%08x at 0x%08x" % (base, self.pc))
        values = {}
        for k, reg in enumerate(regs):
            if load:
                values[reg] = self.mem.read(base + 4 * k, 4)
            else:
                self.mem.write(base + 4 * k, 4, self.r[reg])
        if not (load and rb in regs):                   # ARMv5: no writeback when the base is loaded
            self.r[rb] = (base + 4 * len(regs)) & MASK
        for reg, value in values.items():
            self.r[reg] = value

    def _thumb_long_branch(self, ins: int) -> None:
        """BL/BLX prefix (11110) and its suffix (11111 BL, 11101 BLX) as one instruction."""
        suffix = self.mem.read(self.pc + 2, 2)
        kind = suffix >> 11
        if kind not in (0x1F, 0x1D):
            self._thumb_fault(ins, "BL/BLX prefix without a suffix")
        target = (self.pc + 4 + (_sx(ins & 0x7FF, 11) << 12) + ((suffix & 0x7FF) << 1)) & MASK
        self.r[14] = ((self.pc + 4) | 1) & MASK
        if kind == 0x1F:
            self.next_pc = target
        else:
            if suffix & 1:
                self._thumb_fault(suffix, "BLX suffix with bit 0 set")
            self.thumb = False
            self.next_pc = target & ~3

    # -- execution ---------------------------------------------------------------
    def step(self) -> None:
        if self.thumb:
            self._thumb_step()
            return
        self.pc = self.r[15]
        if self.pc & 3:
            raise ArmFault("unaligned ARM pc 0x%08x" % self.pc)
        ins = self.mem.read(self.pc, 4)
        self.next_pc = (self.pc + 4) & MASK
        cond = ins >> 28
        self.steps += 1
        if cond == 0xF:
            if (ins & 0x0E000000) == 0x0A000000:        # BLX immediate: always to THUMB
                self.r[14] = (self.pc + 4) & MASK
                self.thumb = True
                self.next_pc = (self.pc + 8 + (_sx(ins & 0xFFFFFF, 24) << 2) + ((ins >> 23) & 2)) & MASK
                self.r[15] = self.next_pc
                return
            raise ArmFault("unconditional-space instruction 0x%08x at 0x%08x" % (ins, self.pc))
        if self._cond(cond):
            self._execute(ins)
        self.r[15] = self.next_pc

    def _execute(self, ins: int) -> None:
        if (ins & 0x0FFFFFF0) == 0x012FFF10:            # BX
            self._interwork(self._reg(ins & 0xF))
        elif (ins & 0x0FFFFFF0) == 0x012FFF30:          # BLX register
            if ins & 0xF == 15:
                raise ArmFault("BLX pc at 0x%08x" % self.pc)
            target = self.r[ins & 0xF]
            self.r[14] = (self.pc + 4) & MASK
            self._interwork(target)
        elif (ins & 0x0FFF0FF0) == 0x016F0F10:          # CLZ
            value = self.r[ins & 0xF]
            self._write_reg((ins >> 12) & 0xF, 32 - value.bit_length())
        elif (ins & 0x0FC000F0) == 0x00000090:
            self._multiply(ins)
        elif (ins & 0x0F8000F0) == 0x00800090:
            self._multiply_long(ins)
        elif (ins & 0x0F900090) == 0x01000080:
            self._dsp_multiply(ins)
        elif (ins & 0x0E000090) == 0x00000090 and (ins & 0x60):
            self._halfword_transfer(ins)
        elif (ins & 0x0FB00FF0) == 0x01000090:
            self._swap(ins)
        elif (ins & 0x0F900FF0) == 0x01000050:
            raise ArmFault("saturating instruction 0x%08x at 0x%08x" % (ins, self.pc))
        elif (ins & 0x0C000000) == 0x00000000:
            if (ins & 0x01900000) == 0x01000000:
                self._status_access(ins)
                return
            self._data_processing(ins)
        elif (ins & 0x0C000000) == 0x04000000:
            if (ins & 0x02000010) == 0x02000010:
                raise ArmFault("undefined instruction 0x%08x at 0x%08x" % (ins, self.pc))
            self._single_transfer(ins)
        elif (ins & 0x0E000000) == 0x08000000:
            self._block_transfer(ins)
        elif (ins & 0x0E000000) == 0x0A000000:
            if ins & (1 << 24):
                self.r[14] = (self.pc + 4) & MASK
            self.next_pc = (self.pc + 8 + (_sx(ins & 0xFFFFFF, 24) << 2)) & MASK
        elif (ins & 0x0F000010) == 0x0E000010:
            self._coprocessor(ins)
        elif (ins & 0x0F000000) == 0x0F000000:          # SWI: logged, BIOS not run
            self.swi_log.append((ins & 0xFFFFFF, tuple(self.r[0:4])))
        else:
            raise ArmFault("unsupported instruction 0x%08x at 0x%08x" % (ins, self.pc))

    def call(self, entry: int, args=(), sp: int | None = None, limit: int = 50_000_000) -> int:
        """Run a function (THUMB if entry bit 0 is set) until it returns to the sentinel; returns r0.

        The sentinel is an ARM address, so a THUMB routine's `bx lr` or `pop {pc}`
        returns to it by switching state, as it would to an ARM caller."""
        for i, value in enumerate(args):
            self.r[i] = value & MASK
        if sp is not None:
            self.r[13] = sp
        self.r[14] = RETURN_SENTINEL
        self.thumb = bool(entry & 1)
        self.r[15] = entry & ~1
        start = self.steps
        while self.thumb or self.r[15] != RETURN_SENTINEL:
            if self.steps - start > limit:
                raise ArmFault("step limit reached at 0x%08x" % self.r[15])
            self.step()
        return self.r[0]
