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
#define HOMEWORK_0040_LEN 39

enum INS_TYPE_HEADER {
	_I_ = 0, // Invalid instruction.
	MOV1, // Move register/memory to/from register.
	MOV2, // Move immediate to register/memory.
	MOV3, // Move immediate to register.
	MOV4, // Move memory to accumilator.
	MOV5, // Move accumilator to memory.
};

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

const unsigned char instruction_table[256] = {
//       0    1    2    3      4    5    6    7      8    9    A    B      C    D    E    F
	_I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_, //  0
	_I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_, // 10
	_I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_, // 20
	_I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_, // 30
	_I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_, // 40
	_I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_, // 50
	_I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_, // 60
	_I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_, // 70
	_I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   MOV1,MOV1,MOV1,MOV1,  _I_, _I_, _I_, _I_, // 80
	_I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_, // 90
	MOV4,MOV4,MOV5,MOV5,  _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_, // A0
	MOV3,MOV3,MOV3,MOV3,  MOV3,MOV3,MOV3,MOV3,  MOV3,MOV3,MOV3,MOV3,  MOV3,MOV3,MOV3,MOV3,// B0
	_I_, _I_, _I_, _I_,   _I_, _I_, MOV2,MOV2,  _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_, // C0
	_I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_, // D0
	_I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_, // E0
	_I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_,   _I_, _I_, _I_, _I_, // F0
};

void mov_print_format(char f)
{
	switch (f) {
	case ',' : printf(", ");  break;
	case '\n': putchar('\n'); break;
	default  : putchar(' ');  break;
	}
}

void mov_print_rm(int rm_index, int offset, char format)
{
	putchar('[');
	printf("%s", rm_name[rm_index]);
	if (offset)
		printf(" + %d", offset);
	putchar(']');

	mov_print_format(format);
}

void mov_print_reg(int reg, char format)
{
	printf("%s", reg_name[reg]);
	mov_print_format(format);
}

int diss(unsigned char* bytes, int len)
{
	switch (instruction_table[*bytes]) {
	case MOV1: {
		/* [1000 10 (DW 2bits)]  [(MOD 2bits) (REG 3bits) (R/M 3bits)]  [DISP-LO]  [DISP-HI]
		 *
		 * If 'D' is 1, then the reg field is the destination.
		 * If 'W' is 1, then we're moving 16 bits (registers are 16 wide).
		 *
		 * MOD is simple:
		 * 00 = [address] *!
		 *   (unless R/M is 110!!! then it's a 16 bit displacement!)
		 * 01 = [ ... +  8 bit offset].
		 * 10 = [ ... + 16 bit offset].
		 * 11 = Register to register.
		 *
		 * R/M is what determines the '...' above in the MOD field!
		 *
		 * */

		printf("mov ");

		int wide = (*bytes & 1) ? REGISTER_WIDE_OFFSET : 0;
		int dest = *bytes & 2;
		int reg  = ((bytes[1] >> 3) & 7) + wide;
		int rm   = bytes[1] & 7;

		// Get the mod field.
		switch (bytes[1] >> 6) {
		case 0: { // Address (*)
			// RM == 110, which is an exception!
			// Doing direct address here!
			// I'm assuming the address is always 16 bits...
			if (rm == 6) {
				mov_print_reg(reg, ',');
				int num = bytes[2];
				if (wide)
					num |= bytes[3] << 8;
				printf("[%d]\n", num);

				return wide ? 4 : 3;
			}
			else {
				if (dest) {
					mov_print_reg(reg, ',');
					mov_print_rm(rm, 0, '\n');
				}
				else {
					mov_print_rm(rm, 0, ',');
					mov_print_reg(reg, '\n');
				}
				return 2;
			}
		} break;
		case 1: case 2: { // reg + 8 and 16 bit offset
			int num = bytes[2];

			if (bytes[1] >> 6 == 2)
				num |= (bytes[3] << 8);

			if (dest) {
				mov_print_reg(reg, ',');
				mov_print_rm(bytes[1] & 7, num, '\n');
			}
			else {
				mov_print_rm(bytes[1] & 7, num, ',');
				mov_print_reg(reg, '\n');
			}

			return (bytes[1] >> 6 == 2) ? 4 : 3;
		} break;
		case 3: { // Register to register.
			int regs[2]; // HACK: Just to make things easier to print.
			regs[!dest] = reg;
			regs[ dest] = (bytes[1] & 7) + wide;

			printf("%s, %s\n", reg_name[regs[0]], reg_name[regs[1]]);
			return 2;
		} break;
		}

		return 0; // Error!
	} break;



	case MOV2: {
		int wide = bytes[0] & 1;
		int mod = bytes[1] >> 6;
		int rm = bytes[1] & 7;
		int addr = bytes[2];
		if (wide)
			addr |= bytes[3] << 8;

		printf("mov ");

		switch (mod) {
		case 0: {
			if (rm == 6) {
				// TODO: Finish this part :/
				printf("UNFINISHED!\n");
				return 0;
			}
			// Implicit else statement.

			mov_print_rm(rm, 0, ',');
			printf("%s %d\n", wide ? "word" : "byte", addr);
			return wide ? 4 : 3;
		} break;
		case 2: {
			mov_print_rm(rm, addr, ',');
			addr = bytes[4];
			if (wide)
				addr |= bytes[5] << 8;
			printf("%s %d\n", wide ? "word" : "byte", addr);
			return wide ? 6 : 5;
		} break;
		}

		return 0;
	} break;



	case MOV3: {
		/* HACK: Since we've already structured reg_name
		 * to consider the 'w' bit to be the most significant,
		 * we can just operate directly on the least significant
		 * 4 bits, rather than 3.
		 * And thus, if the reg number/index is larger than 7,
		 * then return 3 bytes, rather than 2, as we read more data. */

		int reg = bytes[0] & 0x0F;

		printf("mov %s, ", reg_name[reg]);

		int num = bytes[1];
		if (reg > 7)
			num |= bytes[2] << 8;

		printf("%d\n", num);

		return (reg > 7) ? 3 : 2;
	} break;



	case MOV4: {
		int wide = bytes[0] & 1;
		printf("mov %s, [%d]\n", reg_name[8],
			(int) (bytes[1] | (wide ? (bytes[2] << 8) : 0)));
		return wide ? 3 : 2;
		} break;



	case MOV5: {
		int wide = bytes[0] & 1;
		printf("mov [%d], %s\n",
			(int) (bytes[1] | (wide ? (bytes[2] << 8) : 0)),
			reg_name[8]);
		return wide ? 3 : 2;
	} break;
	}

	printf("Unknown instruction\n");
	return 0;
}

void homework(int num)
{
	printf("\n\n\nHomework %.4d\n", num);
}

int main()
{
	homework(37);
	diss(HOMEWORK_0037, HOMEWORK_0037_LEN);

	homework(38);
	for (int i = 0; i < HOMEWORK_0038_LEN; ) {
		int n = diss(HOMEWORK_0038 + i, 2);
		if (!n)
			break;
		i += n;
	}

	homework(39);
	for (int i = 0; i < HOMEWORK_0039_LEN; ) {
		int n = diss(HOMEWORK_0039 + i, 2);
		if (!n)
			break;
		i += n;
	}

	homework(40);
	for (int i = 0; i < HOMEWORK_0040_LEN; ) {
		int n = diss(HOMEWORK_0040 + i, 2);
		if (!n)
			break;
		i += n;
		// printf("   (%d)   \n", n);
	}
}
