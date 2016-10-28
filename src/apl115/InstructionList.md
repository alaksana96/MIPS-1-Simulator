

No.|Code  |   Meaning                                 | Complexity  | Implemented  | Tested   | New Test
---|------|-------------------------------------------|-------------|--------------|----------|----------
1|ADD   |  Add (with overflow)                      | 2  XX       | YES             |         | YES
2|ADDI  |  Add immediate (with overflow)            | 2  XX       | YES  	||YES
3|ADDIU |  Add immediate unsigned (no overflow)     | 2  XX       | YES |	| YES
4|ADDU  |  Add unsigned (no overflow)               | 1  X        | YES | | YES
5|AND   |  Bitwise and                              | 1  X        | YES | | YES
6|ANDI  |  Bitwise and immediate                    | 2  XX       | YES | | YES
7|BEQ   |  Branch on equal                          | 3  XXX      | YES | Bit more testing | UPDATED BEEQ
8|BGEZ  |  Branch on greater than or equal to zero  | 3  XXX      | YES | Bit more testing | YES
9|BGEZAL|  Branch on non-negative (>=0) and link    | 4  XXXX     | YES | Bit more testing | YES
10|BGTZ  |  Branch on greater than zero              | 3  XXX      | YES | NEED TO TEST | YES
11|BLEZ  |  Branch on less than or equal to zero     | 3  XXX      | YES | NEED TO TEST | YES
12|BLTZ  |  Branch on less than zero                 | 3  XXX      | YES | NEED TO TEST | YES
13|BLTZAL|  Branch on less than zero and link        | 4  XXXX     | YES | NEED TO TEST | YES
14|BNE   |  Branch on not equal                      | 3  XXX      | YES | NEED TO TEST | YES
15|DIV   |  Divide                                   | 4  XXXX     |     |
16|DIVU  |  Divide unsigned                          | 4  XXXX     |     |
17|J     |  Jump                                     | 3  XXX      |     |
18|JALR  |  Jump and link register                   | 4  XXXX     |     |
19|JAL   |  Jump and link                            | 4  XXXX     |     |
20|JR    |  Jump register                            | 3  XXX      |     |
21|LB    |  Load byte                                | 3  XXX      | YES | | YES
22|LBU   |  Load byte unsigned                       | 3  XXX      | YES    | | YES
23|LH    |  Load half-word                           | 3  XXX      | YES    | Test for Sign extend | YES
24|LHU   |  Load half-word unsigned                  | 3  XXX      | YES    | Test for 0 extend | YES
25|LUI   |  Load upper immediate                     | 2  XX       | YES    |
26|LW    |  Load word                                | 2  XX       | YES | | YES
27|LWL   |  Load word left                           | 5  XXXXX    |
28|LWR   |  Load word right                          | 5  XXXXX    |
29|MFHI  |  Move from HI                             | 3  XXX      | YES
30|MFLO  |  Move from LO                             | 3  XXX      | YES
31|MTHI  |  Move to HI                               | 3  XXX      | YES | Tested for N-1, need to check N-2 | YES
32|MTLO  |  Move to LO                               | 3  XXX      | YES | Not tested |YES
33|MULT  |  Multiply                                 | 4  XXXX     |
34|MULTU |  Multiply unsigned                        | 4  XXXX     |
35|OR    |  Bitwise or                               | 1  X        | YES | |YES
36|ORI   |  Bitwise or immediate                     | 2  XX       | YES | |YES
37|SB    |  Store byte                               | 3  XXX      | YES | Checked for all except +4 but im sure it works | YES
38|SH    |  Store half-word                          | 3  XXX      | YES | Need to check for unaligned | YES
39|SLL   |  Shift left logical                       | 2  XX       | YES | | YES
40|SLLV  |  Shift left logical variable              | 3  XXX      | YES | | YES
41|SLT   |  Set on less than (signed)                | 2  XX       | YES | | YES
42|SLTI  |  Set on less than immediate (signed)      | 3  XXX      | YES | | YES
43|SLTIU |  Set on less than immediate unsigned      | 3  XXX      | YES | | YES
44|SLTU  |  Set on less than unsigned                | 1  X        | YES | | YES
45|SRA   |  Shift right arithmetic                   | 2  XX       | YES
46|SRAV  |  Shift right arithmetic                   | 2  XX       | YES
47|SRL   |  Shift right logical                      | 2  XX       | YES
48|SRLV  |  Shift right logical variable             | 3  XXX      | YES
49|SUB   |  Subtract                                 | 2  XX       | YES
50|SUBU  |  Subtract unsigned                        | 1  X        | YES
51|SW    |  Store word                               | 2  XX       | YES
52|XOR   |  Bitwise exclusive or                     | 1  X        | YES
53|XORI  |  Bitwise exclusive or immediate           | 2  XX       | YES
