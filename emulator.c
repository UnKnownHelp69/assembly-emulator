#include <stdio.h>
#include <stdlib.h>

// global input array cause we need to free it from functions if error
int *input = NULL;

// All registers
enum reg {
    A = 0, B, C, D
};

// Opcodes encoding
enum opcode_t {
    MOVI = 0, ADD = 8, SUB, MUL, DIV, IN, OUT
};

// Struct of operand
union operand_t {
    int rop;
    int imm;
    struct { int rd, rs; } ops;
};

// Struct of inctruction
struct instr_t {
    enum opcode_t opcode;
    union operand_t operand;
};

// Imitatiin of registers memory
struct {
    unsigned char A;
    unsigned char B;
    unsigned char C;
    unsigned char D;
} reg_values = {0};

// function of decode from assembly
struct instr_t decode_cmd(unsigned char cmd) {
    struct instr_t instr; 
    int rf1, rf2;

    // MOVI
    if ((cmd >> 7) == 0) {
        instr.opcode = MOVI;
        instr.operand.imm = cmd;
        return instr;
    }
    
    // IN, OUT
    if (((cmd >> 6) & 1) == 1) {
        
        if ((cmd >> 2) == 0x30){
            instr.opcode = IN;
        } else if ((cmd >> 2) == 0x31) {
            instr.opcode = OUT;
        } else {
            free(input); 
            fprintf(stderr, "Bad input: %x\n", (unsigned) cmd);
            abort();
        }

        rf1 = cmd & 0x3;
        instr.operand.rop = rf1;

        return instr;

    } 
    
    // arithmetic operants
    rf1 = cmd & 0x3;
    rf2 = (cmd >> 2) & 0x3;

    instr.operand.ops.rs = rf1;
    instr.operand.ops.rd = rf2;

    switch (cmd >> 4) {
    case 8: instr.opcode = ADD; return instr;
    case 9: instr.opcode = SUB; return instr;
    case 10: instr.opcode = MUL; return instr;
    case 11: instr.opcode = DIV; return instr;
    }

    // error, nothing to return 
    free(input); 
    fprintf(stderr, "Unrecognised instruction: %x\n", (unsigned) cmd);
    abort();
}


// instruction for in operator
void in_op(int reg) {
    int num;
    scanf("%d", &num);
    switch (reg) {
    case A:
        reg_values.A = num;
        break;
    case B:
        reg_values.B = num;
        break;
    case C:
        reg_values.C = num;
        break;
    case D:
        reg_values.D = num;
        break;
    default:
        free(input); 
        fprintf(stderr, "Not a register: %d\n", reg);
        abort();
    }
}

// instruction for out operationn
void out_op(int reg) {
    int num;
    switch (reg) {
    case A:
        printf("%d \n", reg_values.A);
        break;
    case B:
        printf("%d \n", reg_values.B);
        break;
    case C:
        printf("%d \n", reg_values.C);
        break;
    case D:
        printf("%d \n", reg_values.D);
        break;
    default:
        free(input); 
        fprintf(stderr, "Not a register: %d\n", reg);
        abort();
    }
}

// function to parse value of register 
unsigned char value_reg(int reg) {
    switch (reg) {
    case A: 
        return reg_values.A;
        break;
    case B: 
        return reg_values.B;
        break;
    case C: 
        return reg_values.C;
        break;
    case D: 
        return reg_values.D;
        break;
    default:
        free(input); 
        fprintf(stderr, "Not a register: %d", reg);
        abort();
    }
}

// instruction for arithmetic operations
void calc_op(int op, int rd, int rs) {
    int val = 0;

    switch (rd) {
    case A:
        switch (op) {
        case ADD:
            val = reg_values.A + value_reg(rs);
            break;
        case SUB:
            val = reg_values.A - value_reg(rs);
            break;
        case MUL:
            val = reg_values.A * value_reg(rs);
            break;
        case DIV:
            val = reg_values.A / value_reg(rs);
            break;
        default:
            free(input); 
            fprintf(stderr, "Not an operand: %d", op);
            abort();
        }
        reg_values.A = val;
        break;
    case B:
        switch (op) {
        case ADD:
            val = reg_values.B + value_reg(rs);
            break;
        case SUB:
            val = reg_values.B - value_reg(rs);
            break;
        case MUL:
            val = reg_values.B * value_reg(rs);
            break;
        case DIV:
            val = reg_values.B / value_reg(rs);
            break;
        default:
            free(input); 
            fprintf(stderr, "Not an operand: %d", op);
            abort();
        }
        reg_values.B = val;
        break;
    case C:
        switch (op) {
        case ADD:
            val = reg_values.C + value_reg(rs);
            break;
        case SUB:
            val = reg_values.C - value_reg(rs);
            break;
        case MUL:
            val = reg_values.C * value_reg(rs);
            break;
        case DIV:
            val = reg_values.C / value_reg(rs);
            break;
        default:
            free(input); 
            fprintf(stderr, "Not an operand: %d", op);
            abort();
        }
        reg_values.C = val;
        break;
    case D:
        switch (op) {
        case ADD:
            val = reg_values.D + value_reg(rs);
            break;
        case SUB:
            val = reg_values.D - value_reg(rs);
            break;
        case MUL:
            val = reg_values.D * value_reg(rs);
            break;
        case DIV:
            val = reg_values.D / value_reg(rs);
            break;
        default:
            free(input); 
            fprintf(stderr, "Not an operand: %d", op);
            abort();
        } 
        reg_values.D = val;
        break;
    }

}

// function which do binary code
void print_and_calculate(struct instr_t instr) {
    switch (instr.opcode) {
    case MOVI:
        reg_values.D = instr.operand.imm;
        break;
    case IN:
        in_op(instr.operand.rop);
        break;
    case OUT:
        out_op(instr.operand.rop);
        break;
    case ADD:
    case SUB:
    case MUL:
    case DIV:
        calc_op(instr.opcode, instr.operand.ops.rd, instr.operand.ops.rs);
        break;
    default:
        free(input); 
        fprintf(stderr, "Unsupported instruction\n");
        abort();
    }
}


int main() {
    int size = 0;
    int capacity = 10;
    int value;
    
    // array which save input
    input = malloc(capacity * sizeof(int));
    if (!input) {
        fprintf(stderr, "Malloc error\n");
        abort();
    }

    // parse input
    while (scanf("%x", &value) == 1 && value != 0xf0) {
       if (size >= capacity) {
            capacity *= 2;
            int *temp = realloc(input, capacity * sizeof(int));
            if (!temp) {
                free(input);
                fprintf(stderr, "Realloc error\n");
                abort();
            }
            input = temp;
        }
        input[size++] = value;
    }
    int i = 0;
    
    // decode and do assembly
    for (int i = 0; i < size; ++i) {
        struct instr_t instr;
        
        unsigned char cmd = input[i] & 0xff;
        
        instr = decode_cmd(cmd);
        print_and_calculate(instr);
    }

    free(input); 
    return 0;
}
