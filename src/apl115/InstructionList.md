

Code  |   Meaning                                 | Complexity  | Implemented  | Tested
------|-------------------------------------------|-------------|--------------|----------
ADD   |  Add (with overflow)                      | 2  XX       | YES             |
ADDI  |  Add immediate (with overflow)            | 2  XX       ||
ADDIU |  Add immediate unsigned (no overflow)     | 2  XX       ||
ADDU  |  Add unsigned (no overflow)               | 1  X        | YES |
AND   |  Bitwise and                              | 1  X        | YES |
ANDI  |  Bitwise and immediate                    | 2  XX       | |
BEQ   |  Branch on equal                          | 3  XXX      | |
BGEZ  |  Branch on greater than or equal to zero  | 3  XXX      ||
BGEZAL|  Branch on non-negative (>=0) and link    | 4  XXXX     ||
BGTZ  |  Branch on greater than zero              | 3  XXX      ||
BLEZ  |  Branch on less than or equal to zero     | 3  XXX      ||
BLTZ  |  Branch on less than zero                 | 3  XXX      ||
BLTZAL|  Branch on less than zero and link        | 4  XXXX     ||
BNE   |  Branch on not equal                      | 3  XXX      ||
DIV   |  Divide                                   | 4  XXXX     ||
DIVU  |  Divide unsigned                          | 4  XXXX     ||
J     |  Jump                                     | 3  XXX      ||
JALR  |  Jump and link register                   | 4  XXXX     ||
JAL   |  Jump and link                            | 4  XXXX     ||
JR    |  Jump register                            | 3  XXX      |
LB    |  Load byte                                | 3  XXX      |
LBU   |  Load byte unsigned                       | 3  XXX      |
LH    |  Load half-word                           | 3  XXX      | 
LHU   |  Load half-word unsigned                  | 3  XXX      | 
LUI   |  Load upper immediate                     | 2  XX       |
LW    |  Load word                                | 2  XX       |
LWL   |  Load word left                           | 5  XXXXX    |
LWR   |  Load word right                          | 5  XXXXX    |
MFHI  |  Move from HI                             | 3  XXX      |
MFLO  |  Move from LO                             | 3  XXX      |
MTHI  |  Move to HI                               | 3  XXX      |
MTLO  |  Move to LO                               | 3  XXX      |
MULT  |  Multiply                                 | 4  XXXX     |
MULTU |  Multiply unsigned                        | 4  XXXX     |
OR    |  Bitwise or                               | 1  X        | YES
ORI   |  Bitwise or immediate                     | 2  XX       |
SB    |  Store byte                               | 3  XXX      |
SH    |  Store half-word                          | 3  XXX      |
SLL   |  Shift left logical                       | 2  XX       | YES
SLLV  |  Shift left logical variable              | 3  XXX      | 
SLT   |  Set on less than (signed)                | 2  XX       |
SLTI  |  Set on less than immediate (signed)      | 3  XXX      |
SLTIU |  Set on less than immediate unsigned      | 3  XXX      |
SLTU  |  Set on less than unsigned                | 1  X        | YES
SRA   |  Shift right arithmetic                   | 2  XX       | YES
SRAV  |  Shift right arithmetic                   | 2  XX       |
SRL   |  Shift right logical                      | 2  XX       | YES
SRLV  |  Shift right logical variable             | 3  XXX      | 
SUB   |  Subtract                                 | 2  XX       | YES
SUBU  |  Subtract unsigned                        | 1  X        | YES
SW    |  Store word                               | 2  XX       |
XOR   |  Bitwise exclusive or                     | 1  X        | YES
XORI  |  Bitwise exclusive or immediate           | 2  XX       |
