"""Differential behavior tests for the recovered contact-motion C.

Both the original and compiled candidate execute their ARM instructions, including
the SDK vector helpers. Only the DIV/SQRT register results used by VEC_Normalize
are modeled. The model completes synchronously and rejects unsupported modes,
negative division operands and division by zero; it makes no timing claim.
"""
import math
import os
from pathlib import Path
import random
import struct
import sys
import tempfile
import unittest

from project import BUILD_DIR, FUNC_INDEX, MWCC_DIR, ROOT

sys.path.insert(0, str(ROOT.parent / "tools" / "mobiclip"))
from arm_exec import ArmFault, Cpu, Memory

MASK64 = (1 << 64) - 1
DIV = 0x04000280


def signed(value, bits=32):
    value &= (1 << bits) - 1
    return value - (1 << bits) if value >> (bits - 1) else value


def fx_round(value):
    return signed((signed(value + 0x800, 64) >> 12))


def dot(a, b):
    return fx_round(sum(x * y for x, y in zip(a, b)))


def cross(a, b):
    return (fx_round(a[1] * b[2] - a[2] * b[1]),
            fx_round(a[2] * b[0] - a[0] * b[2]),
            fx_round(a[0] * b[1] - a[1] * b[0]))


def normalized(vector):
    length_squared = sum(x * x for x in vector)
    if not length_squared:
        raise ValueError("normalization of a zero vector is outside this model")
    factor = (((1 << 56) // length_squared) * math.isqrt(length_squared << 2)) & MASK64
    return tuple(signed(signed(factor * x + (1 << 44), 64) >> 45) for x in vector)


def project(motion, normals, selected, mode):
    a, b, c = (normals[i] for i in selected)
    if mode == 0:
        return motion, "unchanged"
    if mode in (1, 2):
        if abs(dot(a, b)) < 0xff0:
            return (0, 0, 0), "plane_rejected"
        scale = dot(motion, a)
        component = tuple(fx_round(x * scale) for x in a)
        return tuple(signed(x - y) for x, y in zip(motion, component)), "plane_projected"
    if mode == 3:
        if any(abs(dot(x, y)) > 0xff0 for x, y in ((a, b), (a, c), (b, c))):
            return (0, 0, 0), "pair_rejected"
        axis = normalized(cross(a, b))
        if abs(dot(axis, c)) > 0x10:
            return (0, 0, 0), "axis_rejected"
        scale = dot(motion, axis)
        return tuple(fx_round(x * scale) for x in axis), "axis_projected"
    return (0, 0, 0), "default_zero"


class VectorMathMemory(Memory):
    """Functional results for positive 64/64 DIV and unsigned 64-bit SQRT."""
    def __init__(self):
        super().__init__()
        self.map(DIV, size=0x40)

    def read(self, address, size):
        if DIV + 0x20 <= address < DIV + 0x30:
            if super().read(DIV, 2) != 2:
                raise ArmFault("only DIV mode 2 is supported")
            numerator = signed(super().read(DIV + 0x10, 8), 64)
            denominator = signed(super().read(DIV + 0x18, 8), 64)
            if numerator < 0 or denominator <= 0:
                raise ArmFault("only nonnegative numerator / positive denominator is supported")
            result = numerator // denominator if address < DIV + 0x28 else numerator % denominator
            offset = address - (DIV + (0x20 if address < DIV + 0x28 else 0x28))
            return (result >> (8 * offset)) & ((1 << (8 * size)) - 1)
        if address == DIV + 0x34:
            if size != 4 or super().read(DIV + 0x30, 2) != 1:
                raise ArmFault("only 64-bit SQRT mode 1 is supported")
            return math.isqrt(super().read(DIV + 0x38, 8))
        return super().read(address, size)


class ContactMotionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not FUNC_INDEX.is_file():
            raise unittest.SkipTest("requires the local EU ROM-derived function index")
        if not (MWCC_DIR / "dsi/1.3p1/mwccarm.exe").is_file():
            raise unittest.SkipTest("requires CodeWarrior dsi/1.3p1")
        import match
        import verify_idx
        from elftools.elf.elffile import ELFFile
        cls.index = verify_idx._index()
        cls.addresses = verify_idx.SYM_ADDR
        cls.entry = cls.addresses["func_02034d78"]
        cls.original = bytes.fromhex(cls.index["func_02034d78"]["hex"])
        source = ROOT / "src/calls/func_02034d78.c"
        previous = match._COMPILER_MAP
        previous_cwd = Path.cwd()
        try:
            os.chdir(ROOT)
            match._COMPILER_MAP = {source.relative_to(ROOT).as_posix(): "dsi/1.3p1"}
            with tempfile.TemporaryDirectory(prefix="contact-motion-", dir=BUILD_DIR) as temporary:
                output = Path(temporary) / "candidate.o"
                match.compile_c(str(source), out=str(output))
                code, refs = match.text_relocs(str(output), "func_02034d78")
                with output.open("rb") as stream:
                    elf = ELFFile(stream)
                    section_index = match.func_section(elf, "func_02034d78")
                    addends = {relocation["r_offset"]: relocation["r_addend"]
                               for section in elf.iter_sections()
                               if section["sh_type"] == "SHT_RELA" and section["sh_info"] == section_index
                               for relocation in section.iter_relocations()}
                cls.candidate = bytearray(code)
                expected = dict(cls.index["func_02034d78"]["relocs"])
                if set(refs) != set(expected):
                    raise AssertionError("candidate relocation offsets differ")
                for offset, (name, kind) in refs.items():
                    destination = cls.addresses[name]
                    if destination != cls.addresses[expected[offset]]:
                        raise AssertionError("candidate relocation target differs")
                    if kind == 1 and addends.get(offset) == -8:
                        word = int.from_bytes(code[offset:offset + 4], "little")
                        word = (word & 0xff000000) | (((destination - cls.entry - offset - 8) >> 2) & 0xffffff)
                    elif kind == 2:
                        word = destination + addends.get(offset, 0)
                    else:
                        raise AssertionError("unsupported candidate relocation")
                    cls.candidate[offset:offset + 4] = struct.pack("<I", word)
        finally:
            match._COMPILER_MAP = previous
            os.chdir(previous_cwd)

    def cpu(self, code):
        memory = VectorMathMemory()
        memory.map(self.entry, code)
        for name in ("AbsDotProduct", "VEC_DotProduct", "VEC_Subtract",
                     "VEC_CrossProduct", "VEC_Normalize", "ScaleVecFx32InPlace", "CollisionQuery_Init"):
            memory.map(self.addresses[name], bytes.fromhex(self.index[name]["hex"]))
        memory.map(self.addresses["gZeroVecFx32"], bytes(12))
        memory.map(0x01000000, size=0x10000)
        return Cpu(memory)

    def vector_call(self, cpu, function, vector):
        start, out = 0x01000040, 0x01000080
        self.write_vector(cpu, start, vector)
        cpu.call(self.addresses[function], [start, out], sp=0x0100fff0, limit=5000)
        return self.read_vector(cpu, out)

    @staticmethod
    def write_vector(cpu, address, values):
        for i, value in enumerate(values):
            cpu.mem.write(address + 4 * i, 4, value)

    @staticmethod
    def read_vector(cpu, address):
        return struct.unpack("<3i", cpu.mem.bytes(address, 12))

    def test_sdk_normalization_uses_original_instructions(self):
        cpu = self.cpu(self.original)
        rng = random.Random(0x01ff9f88)
        inputs = [(4096, 0, 0), (0, -4096, 0), (1, 2, 3), (-8192, 4096, 0)]
        inputs += [tuple(rng.randint(-8192, 8192) for _ in range(3)) for _ in range(256)]
        for vector in inputs:
            with self.subTest(vector=vector):
                self.assertEqual(self.vector_call(cpu, "VEC_Normalize", vector), normalized(vector))

    def test_original_and_pending_c_match_the_portable_model(self):
        cpus = [self.cpu(self.original), self.cpu(self.candidate)]
        motion_address, contacts = 0x01000040, 0x01000100
        rng = random.Random(0x02034d78)
        triples = [((4096, 0, 0), (0, 4096, 0), (0, 0, 4096)),
                   ((4096, 0, 0), (-4096, 0, 0), (0, 4096, 0)),
                   ((4096, 0, 0), (0, 4096, 0), normalized((1, 1, 0)))]
        triples += [((4096, 0, 0), (x, 360, 0), (0, 0, 4096)) for x in (4079, 4080, 4081)]
        triples += [((4096, 0, 0), (0, 4096, 0), (2896, 2896, z)) for z in (-17, -16, 16, 17)]
        triples += [tuple(normalized(tuple(rng.randint(-4096, 4096) for _ in range(3)))
                          for _ in range(3)) for _ in range(200)]
        outcomes = set()
        cases = 0
        for triple in triples:
            normals = [(4096, 0, 0)] * 16
            selected = tuple(rng.sample(range(16), 3))
            for index, normal in zip(selected, triple):
                normals[index] = normal
            motion = tuple(rng.randint(-16384, 16384) for _ in range(3))
            for mode in (0, 1, 2, 3, 4, 255):
                expected, outcome = project(motion, normals, selected, mode)
                outcomes.add(outcome)
                for cpu in cpus:
                    for i in range(0x1a4):
                        cpu.mem.write(contacts + i, 1, 0xa5)
                    for i, normal in enumerate(normals):
                        self.write_vector(cpu, contacts + 0xc0 + 12 * i, normal)
                    for i, index in enumerate(selected):
                        cpu.mem.write(contacts + 0x181 + i, 1, index)
                    cpu.mem.write(contacts + 0x1a1, 1, mode)
                    before = cpu.mem.bytes(contacts, 0x1a4)
                    self.write_vector(cpu, motion_address, motion)
                    cpu.mem.write(motion_address - 4, 4, 0x5a5a5a5a)
                    cpu.mem.write(motion_address + 12, 4, 0x5a5a5a5a)
                    cpu.call(self.entry, [motion_address, contacts], sp=0x0100fff0, limit=5000)
                    self.assertEqual(self.read_vector(cpu, motion_address), expected, (mode, triple, motion))
                    self.assertEqual(cpu.mem.bytes(contacts, 0x1a4), before)
                    self.assertEqual(cpu.mem.read(motion_address - 4, 4), 0x5a5a5a5a)
                    self.assertEqual(cpu.mem.read(motion_address + 12, 4), 0x5a5a5a5a)
                cases += 1
        self.assertEqual(cases, 1260)
        self.assertEqual(outcomes, {"unchanged", "plane_rejected", "plane_projected",
                                    "pair_rejected", "axis_rejected", "axis_projected", "default_zero"})

    def test_mmio_rejects_unsupported_division(self):
        memory = VectorMathMemory()
        with self.assertRaises(ArmFault):
            memory.read(DIV + 0x20, 4)
        memory.write(DIV, 2, 2)
        with self.assertRaises(ArmFault):
            memory.read(DIV + 0x20, 4)

    def test_motion_may_alias_a_selected_normal(self):
        contacts = 0x01000100
        selected = (0, 1, 2)
        triples = [((4096, 0, 0), (0, 4096, 0), (0, 0, 4096)),
                   ((4096, 0, 0), (-4096, 0, 0), (0, 4096, 0)),
                   ((4096, 0, 0), (0, 4096, 0), normalized((1, 1, 0)))]
        for code in (self.original, self.candidate):
            cpu = self.cpu(code)
            for triple in triples:
                normals = list(triple) + [(4096, 0, 0)] * 13
                for mode in (0, 1, 2, 3, 4, 255):
                    for i in range(0x1a4):
                        cpu.mem.write(contacts + i, 1, 0xa5)
                    for i, normal in enumerate(normals):
                        self.write_vector(cpu, contacts + 0xc0 + 12 * i, normal)
                    for i, index in enumerate(selected):
                        cpu.mem.write(contacts + 0x181 + i, 1, index)
                    cpu.mem.write(contacts + 0x1a1, 1, mode)
                    expected = bytearray(cpu.mem.bytes(contacts, 0x1a4))
                    projected, _ = project(normals[0], normals, selected, mode)
                    struct.pack_into("<3i", expected, 0xc0, *projected)
                    cpu.call(self.entry, [contacts + 0xc0, contacts], sp=0x0100fff0, limit=5000)
                    self.assertEqual(cpu.mem.bytes(contacts, 0x1a4), expected, (mode, triple))

    def test_query_initialization_preserves_unwritten_workspace_and_query_bytes(self):
        cpu = self.cpu(self.original)
        query, workspace, stack = 0x01000100, 0x01000400, 0x0100fef0
        for query_id, kind, first, second, extra in ((0, 0, 0, 0, 0), (15, 9, 1, 1, -1),
                                                    (0xffff, 255, 255, 128, 0x12345678)):
            actor, shape = 0x02001000, 0x02002000
            expected = bytearray([0xa5] * 0x60)
            struct.pack_into("<H", expected, 0xe, query_id)
            for offset, value in ((0x10, actor), (0x14, 0), (0x24, shape), (0x28, workspace),
                                  (0x2c, 0x3000), (0x30, -1), (0x34, -1), (0x38, -1),
                                  (0x44, extra), (0x48, 0), (0x50, 0), (0x58, 0)):
                struct.pack_into("<I", expected, offset, value & 0xffffffff)
            expected[0x3c:0x3f] = bytes((first, second, 1))
            expected[0x40] = kind
            for i in range(0x60):
                cpu.mem.write(query + i, 1, 0xa5)
            for i in range(0x1a4):
                cpu.mem.write(workspace + i, 1, 0xa5)
            for i, value in enumerate((first, second, shape, workspace, extra)):
                cpu.mem.write(stack + 4 * i, 4, value)
            cpu.call(self.addresses["CollisionQuery_Init"], [query, query_id, actor, kind], sp=stack, limit=5000)
            expected_workspace = bytearray([0xa5] * 0x1a4)
            expected_workspace[0x180] = expected_workspace[0x1a1] = 0
            self.assertEqual(cpu.mem.bytes(query, 0x60), expected)
            self.assertEqual(cpu.mem.bytes(workspace, 0x1a4), expected_workspace)


if __name__ == "__main__":
    unittest.main()
