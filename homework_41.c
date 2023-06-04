/* Just homework from Casey's course.
 * Never use this code, it's bad and probably buggy.
 * ... Definitely smells too.
 */

#include <stdio.h>


// Homework from Casey.
#define HOMEWORK_0037 "\x89\xD9"
#define HOMEWORK_0037_LEN  2

#define HOMEWORK_0038 "\x89\xD9\x88\xE5\x89\xDA\x89\xDE\x89\xFB\x88\xC8\x88\xED\x89\xC3\x89\xF3\x89\xFC\x89\xC5"
#define HOMEWORK_0038_LEN  22

#define HOMEWORK_0039 "\x89\xDE\x88\xC6\xB1\x0C\xB5\xF4\xB9\x0C\x00\xB9\xF4\xFF\xBA\x6C\x0F\xBA\x94\xF0\x8A\x00\x8B\x1B\x8B\x56\x00\x8A\x60\x04\x8A\x80\x87\x13\x89\x09\x88\x0A\x88\x6E\x00"
#define HOMEWORK_0039_LEN  41

#define HOMEWORK_0040 "\x8B\x41\xDB\x89\x8C\xD4\xFE\x8B\x57\xE0\xC6\x03\x07\xC7\x85\x85\x03\x5B\x01\x8B\x2E\x05\x00\x8B\x1E\x82\x0D\xA1\xFB\x09\xA1\x10\x00\xA3\xFA\x09\xA3\x0F\x00"
#define HOMEWORK_0040_LEN  39

#define HOMEWORK_0041 "\x03\x18\x03\x5E\x00\x83\xC6\x02\x83\xC5\x02\x83\xC1\x08\x03\x5E\x00\x03\x4F\x02\x02\x7A\x04\x03\x7B\x06\x01\x18\x01\x5E\x00\x01\x5E\x00\x01\x4F\x02\x00\x7A\x04\x01\x7B\x06\x80\x07\x22\x83\x82\xE8\x03\x1D\x03\x46\x00\x02\x00\x01\xD8\x00\xE0\x05\xE8\x03\x04\xE2\x04\x09\x2B\x18\x2B\x5E\x00\x83\xEE\x02\x83\xED\x02\x83\xE9\x08\x2B\x5E\x00\x2B\x4F\x02\x2A\x7A\x04\x2B\x7B\x06\x29\x18\x29\x5E\x00\x29\x5E\x00\x29\x4F\x02\x28\x7A\x04\x29\x7B\x06\x80\x2F\x22\x83\x29\x1D\x2B\x46\x00\x2A\x00\x29\xD8\x28\xE0\x2D\xE8\x03\x2C\xE2\x2C\x09\x3B\x18\x3B\x5E\x00\x83\xFE\x02\x83\xFD\x02\x83\xF9\x08\x3B\x5E\x00\x3B\x4F\x02\x3A\x7A\x04\x3B\x7B\x06\x39\x18\x39\x5E\x00\x39\x5E\x00\x39\x4F\x02\x38\x7A\x04\x39\x7B\x06\x80\x3F\x22\x83\x3E\xE2\x12\x1D\x3B\x46\x00\x3A\x00\x39\xD8\x38\xE0\x3D\xE8\x03\x3C\xE2\x3C\x09\x75\x02\x75\xFC\x75\xFA\x75\xFC\x74\xFE\x7C\xFC\x7E\xFA\x72\xF8\x76\xF6\x7A\xF4\x70\xF2\x78\xF0\x75\xEE\x7D\xEC\x7F\xEA\x73\xE8\x77\xE6\x7B\xE4\x71\xE2\x79\xE0\xE2\xDE\xE1\xDC\xE0\xDA\xE3\xD8"
#define HOMEWORK_0041_LEN  247


/* 8086 doesn't have instruction "types",
 * but there are common encoding formats.
 * RISC-V has instruction types, which is handy.
 * So I made up some bullshit names that we'll use for decoding.
 * These names suck, but that's ok. */
enum i8086_decode_type {
	// Move setups.
	I86___ = 0, // Unknown type.
	I86_TF, // 'FULL'      type.
	I86_TL, // 'Long'      type.
	I86_TS, // 'Short'     type.
	I86_TA, // 'Accum'     type.
	I86_TG, // 'seG'       type.
	I86_TT, // 'Two-byte'  type.
};

enum i8086_opcode {
	i8086_NONE = -1,
	i8086_MOV = 0x100,
	i8086_ADD,
	i8086_SUB,
	i8086_CMP,
	i8086_JMP,
	// Loops.
	i8086_LOOPNZ = 0xE0,
	i8086_LOOPZ,
	i8086_LOOP,
	i8086_JCXS,
	// Conditional jump instructions.
	i8086_JO = 0x70,
	i8086_JNO,
	i8086_JB,
	i8086_JNB,
	i8086_JE,
	i8086_JNE,
	i8086_JBE,
	i8086_JA,
	i8086_JS,
	i8086_JNS,
	i8086_JP,
	i8086_JNP,
	i8086_JL,
	i8086_JNL,
	i8086_JLE,
	i8086_JG,

};

/* To make priting easier, we'll have a
 * decode function that returns this (unoptimized) struct,
 * and a separate function to print the ASM.
 * This is just so I can print the bytes and ASM.
 * (1: Decode. 2: Print bytes. 3: Print ASM.) */
typedef struct struct_ins {
	int opcode;
	int length;
	int type;
	union { int s, d; };
	int w, mod, reg, rm, sr;
	union { int disp, addr, ipinc8; };
	int data;
} ins8086;


// List of register names.
// If the 'wide' flag is set, then just add 8.
// In this list, the 'w' flag is the most significant bit.
#define REGISTER_WIDE_OFFSET  8
const char* reg_name[] = {
	"al", "cl", "dl",
	"bl", "ah", "ch",
	"dh", "bh", "ax",
	"cx", "dx", "bx",
	"sp", "bp", "si",
	"di"
};

/* If the MOD field is 11, then this is never used!
 * If the MOD field is 00, then you use these directly
 * UNLESS R/M is 110, in which case it's a direct address.
 * Otherwise if MOD is 01 or 10, then you need to specify
 * a " + " D8 or D16. */
const char* rm_name[] = {
	"bx + si",
	"bx + di",
	"bp + si",
	"bp + di",
	"si",
	"di",
	"bp",
	"bx",
};

const char* tt_table_name[] = {
/*
 0   1   2   3   4   5   6   7   8   9   a   b   c   d   e   f */
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // 00
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // 10
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // 20
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // 30
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // 40
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // 50
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // 60
"jo", "jno", "jb", "jnb", "je", "jne", "jbe", "ja", "js", "jns", "jp", "jnp", "jl", "jnl", "jle", "jg", // 70
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // 80
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // 90
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // a0
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // b0
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // c0
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // d0
"loopnz", "loopz", "loop", "jcxs", "", "", "", "", "", "", "", "", "", "", "", "", // e0
"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // f0
// Extras with no specific place:
"mov", "add", "sub", "cmp"
};


const unsigned char ins_table_type[256] = {
/* 0       1       2       3       4       5       6       7       8       9       a       b       c       d       e       f */
I86_TF, I86_TF, I86_TF, I86_TF, I86_TA, I86_TA, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, // 00
I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, // 10
I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86_TF, I86_TF, I86_TF, I86_TF, I86_TA, I86_TA, I86___, I86___, // 20
I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86_TF, I86_TF, I86_TF, I86_TF, I86_TA, I86_TA, I86___, I86___, // 30
I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, // 40
I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, // 50
I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, // 60
I86_TT, I86_TT, I86_TT, I86_TT, I86_TT, I86_TT, I86_TT, I86_TT, I86_TT, I86_TT, I86_TT, I86_TT, I86_TT, I86_TT, I86_TT, I86_TT, // 70
I86_TL, I86_TL, I86_TL, I86_TL, I86___, I86___, I86___, I86___, I86_TF, I86_TF, I86_TF, I86_TF, I86_TG, I86___, I86_TG, I86___, // 80
I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, // 90
I86_TA, I86_TA, I86_TA, I86_TA, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, // a0
I86_TS, I86_TS, I86_TS, I86_TS, I86_TS, I86_TS, I86_TS, I86_TS, I86_TS, I86_TS, I86_TS, I86_TS, I86_TS, I86_TS, I86_TS, I86_TS, // b0
I86___, I86___, I86___, I86___, I86___, I86___, I86_TL, I86_TL, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, // c0
I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, // d0
I86_TT, I86_TT, I86_TT, I86_TT, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, // e0
I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, I86___, // f0
};


int decode_opcode(int bits)
{
	// Here Odin would have been nice.

	if (bits >= 0x580 && bits <= 0x583) {
		return i8086_SUB;
	} else if (bits >= 0x780 && bits <= 0x783) {
		return i8086_CMP;
	} else if (bits >= 0x70 && bits <= 0x7F) {
		return i8086_JMP;
	} else if (bits >= 0xE0 && bits <= 0xE2) {
		return i8086_LOOP;
	}

	switch (bits) {
	case 0x80: case 0x81: case 0x82: case 0x83:
		return i8086_ADD;
		break;
	case 0xC6: case 0xC7:
		return i8086_MOV;
		break;
	case 0xB0: /* B0 to BF, masked off below. */
		return i8086_MOV;
		break;
	case 0x00: case 0x01: case 0x02: case 0x03:
		return i8086_ADD;
		break;
	case 0x04: case 0x05:
		return i8086_ADD;
		break;
	case 0x38: case 0x39: case 0x3a: case 0x3b:
		return i8086_CMP;
		break;
	case 0x3C: case 0x3D:
		return i8086_CMP;
		break;
	case 0x2C: case 0x2D:
		return i8086_SUB;
		break;
	case 0x28: case 0x29: case 0x2a: case 0x2b:
		return i8086_SUB;
		break;
	case 0x88: case 0x89: case 0x8a: case 0x8b:
		return i8086_MOV;
		break;
	case 0xA0: case 0xA1: case 0xA2: case 0xA3:
		return i8086_MOV;
		break;
	default: return i8086_NONE; break;
	}
}

// GOD DAMN I write utter garbage...
// Given that the pattern "[Disp Low] [Disp High] [Data] [Data if w]"
// is so common and is used in several places,
// I figured it would be nice to have as its own function.
// Ideally, in Odin, this would be a procedure only defined
// and accessible within the "decode" function... But C ain't fun like that.
// Returns the amount of bytes read!
int decode_disp_and_data(unsigned char* b,
	int mod, int rm, int w, int s, // pass 0 to s on f-type and the like!
	int *disp, // NULL if not needed.
	int *data) // NULL if not needed.
{
	int i = 0;

	if (disp) {
		switch (mod) {
		case 0b00:
			if (rm == 0b110)
				goto weirdo;
			break;
		case 0b01:
			*disp = b[i++];
			break;
		case 0b10:
		weirdo:
			*disp  = b[i++];
			*disp |= b[i++] << 8;
			break;
		case 0b11: /* No displacement. */ break;
		}
	}

	if (data) {
		*data = b[i++];
		if (w && !s)
			*data |= b[i++] << 8;
	}

	return i;
}

ins8086 decode(unsigned char *b, int len)
{
	ins8086 tmp = { 0 };

	tmp.type = ins_table_type[*b];
	switch (tmp.type) {
	case I86_TF:
		tmp.opcode = decode_opcode((int) *b);
		tmp.w    =  b[0] & 1;
		tmp.d    =  b[0] & 2;
		tmp.mod  = (b[1] & 0300) >> 6;
		tmp.reg  = (b[1] & 0070) >> 3;
		tmp.rm   = (b[1] & 0007);
		tmp.length = 2 + decode_disp_and_data(b + 2,
			tmp.mod, tmp.rm, tmp.w, 0,
			&tmp.disp, NULL);
		break;
	
	
	case I86_TL:
		tmp.opcode = decode_opcode(b[0] | ((b[1] & 0070) << 5));
		tmp.w   =  b[0] & 1;
		tmp.s   =  b[0] & 2; // Non-MOV cases.
		tmp.mod = (b[1] & 0300) >> 6;
		tmp.rm  = (b[1] & 0007);
		tmp.length = 2 + decode_disp_and_data(b + 2,
			tmp.mod, tmp.rm, tmp.w,
			// This ternary check is a bit of a hack...
			tmp.opcode == i8086_MOV ? 0 : tmp.s,
			&tmp.disp, &tmp.data);
		break;


	case I86_TS:
		tmp.opcode = decode_opcode(b[0] & 0xF0);
		tmp.w    = (b[0] & 0010) >> 3;
		tmp.reg  =  b[0] & 0007;
		tmp.data =  b[1];
		if (tmp.w) {
			tmp.data |= b[2] << 8;
			tmp.length = 3;
		} else {
			tmp.length = 2;
		}
		break;


	case I86_TA:
		tmp.opcode = decode_opcode(b[0]);
		tmp.w = b[0] & 1;
		tmp.d = b[0] & 2; // NOT DOCUMENTED, JUST A GUESS!
		tmp.addr = b[1];
		if (tmp.w) {
			tmp.addr |= b[2] << 8;
			tmp.length = 3;
		} else {
			tmp.length = 2;
		}
		break;


	case I86_TT:
		tmp.opcode = b[0];
		tmp.ipinc8 = b[1];
		tmp.length = 2;
		break;


	default: printf("Decode thing not done yet :(\n"); break;
	}

	return tmp;
}

void insprintbytes(unsigned char* b, int len)
{
	int i = 0;

	if (len == 0)
		len = 6;

	for (; i < len; i++)
		printf("%.2X ", b[i]);
	for (; i < 6; i++)
		printf("   ");
}

void asm_print_format(char f)
{
	switch (f) {
	case ',' : printf(", ");  break;
	}
}

void asm_print_rm(ins8086 i, int offset, char format)
{
	int br = 0;

	switch (i.mod) {
	case 0b00:
		br = 1; putchar('[');
		if (i.rm == 0b110)
			printf("%d", offset);
		else
			printf("%s", rm_name[i.rm]);
		break;
	case 0b01: // Fall-through!
	case 0b10:
		br = 1; putchar('[');
		printf("%s", rm_name[i.rm]);
		if (offset)
			printf(" + %d", offset);
		break;
	case 0b11:
		printf("%s", reg_name[i.rm + (i.w ? REGISTER_WIDE_OFFSET : 0)]);
		break;
	}

	if (br)
		putchar(']');

	asm_print_format(format);
}

void asm_print_reg(int reg, int w, char format)
{
	printf("%s", reg_name[reg + (w ? REGISTER_WIDE_OFFSET : 0)]);
	asm_print_format(format);
}

void insprint(ins8086 i)
{
	if (i.opcode == i8086_NONE)
		return;
	
	printf("%s ", tt_table_name[i.opcode]);

	switch (i.type) {
	case I86_TF:
		if (i.d) {
			asm_print_reg(i.reg, i.w, ',');
			asm_print_rm(i, i.disp, 0);
		} else {
			asm_print_rm(i, i.disp, ',');
			asm_print_reg(i.reg, i.w, 0);
		}
		break;
	case I86_TL:
		asm_print_rm(i, i.disp, ',');
		printf("%s %d", i.w ? "word" : "byte", i.data);
		break;
	case I86_TS:
		printf("%s, %d", reg_name[i.reg + (i.w ? REGISTER_WIDE_OFFSET : 0)], i.data);
		break;
	case I86_TA:
		if (i.d)
			printf("%d, %s", i.addr, reg_name[i.w ? 8 : 0] /* al/x */);
		else
			printf("%s, %d", reg_name[i.w ? 8 : 0] /* al/x */, i.addr);
		break;
	case I86_TT:
		printf("%d", i.ipinc8 > 127 ? i.ipinc8 - 256 : i.ipinc8);
		break;
	}

	putchar('\n');
}

void homework(int num, unsigned char *b, int len)
{
	ins8086 ins;

	printf("\n; Homework %.4d\n", num);
	for (int i = 0; i < len; ) {
		ins = decode(b + i, 2);
		printf("%.4X   ", i);
		insprintbytes(b + i, ins.length);
		printf("  ");
		insprint(ins);

		if (ins.length == 0)
			break;

		i += ins.length;
	}
}

int main()
{
	homework(37, HOMEWORK_0037, HOMEWORK_0037_LEN);
	homework(38, HOMEWORK_0038, HOMEWORK_0038_LEN);
	homework(39, HOMEWORK_0039, HOMEWORK_0039_LEN);
	homework(40, HOMEWORK_0040, HOMEWORK_0040_LEN);
	homework(41, HOMEWORK_0041, HOMEWORK_0041_LEN);

	return 0;
}
