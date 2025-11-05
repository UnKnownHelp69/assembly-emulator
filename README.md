# assembly-emulator

The emulating simple assembly architecture in calculator.
# Processor Architecture Specification

## Register File

The processor contains four 8-bit registers:

| Register | Encoding |
|----------|----------|
| A        | 00       |
| B        | 01       |
| C        | 10       |
| D        | 11       |

## Instruction Set Architecture

| Instruction | Description | Binary Encoding |
|-------------|-------------|-----------------|
| `MOVI Imm`  | Move immediate value to register D | `0!!!!!!!` |
| `ADD R, R`  | Add two registers (modulo 256) | `1000RRRR` |
| `SUB R, R`  | Subtract two registers (modulo 256) | `1001RRRR` |
| `MUL R, R`  | Multiply two registers (modulo 256) | `1010RRRR` |
| `DIV R, R`  | Divide two registers (modulo 256) | `1011RRRR` |
| `IN R`      | Read input to register R | `110000RR` |
| `OUT R`     | Write register R to output | `110001RR` |

### Encoding Notes:
- `!` represents immediate value bits
- `R` represents register selection bits (2 bits per register)
- Instructions using two registers encode both register selections in the `RRRR` field
