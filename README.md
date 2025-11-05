# assembly-emulator

The emulating simple assembly architecture in calculator.

### Register File

The processor contains four 8-bit registers:

| Register | Encoding |
|----------|----------|
| A        | 00       |
| B        | 01       |
| C        | 10       |
| D        | 11       |

### Instructions

| Instruction | Description | Binary Encoding |
|-------------|-------------|-----------------|
| `MOVI Imm`  | Move immediate value to register D | `0!!!!!!!` |
| `ADD R, R`  | Add two registers | `1000RRRR` |
| `SUB R, R`  | Subtract two registers | `1001RRRR` |
| `MUL R, R`  | Multiply two registers | `1010RRRR` |
| `DIV R, R`  | Divide two register | `1011RRRR` |
| `IN R`      | Read input to register R | `110000RR` |
| `OUT R`     | Write register R to output | `110001RR` |
