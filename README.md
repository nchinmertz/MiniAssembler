This project simulates an assembler, translating simplified assembly code into machine code


It takes in a file, written in a simplified assemble code and translates it to machine code. The language is based on RISC-V architecture therefore each instruction is comprised of 24 bits. Instructions can either be oeprand instructions, with an opcode, addressing mode and specified operand, or operate instructions, containing only an opcode. Below is a comprehensive table detailing the assembly opcodes, their machine representations, supported addressing modes, and descriptions.
|Assembly|Machine|Addressing Modes|Description|
|---|:---:|:---:|---|
|LDA operand|00|0 through 9|ACC = operand|
|LDX operand|01|0 through 9|XR = operand|
|LDS operand|02|0 through 9|SP = operand|
|LDF operand|03|0 through 9|FP = operand|
|STA operand|04|2 through 9|operand = ACC|
|STX operand|05|2 through 9|XR = operand|
|STS operand|06|2 through 9|SP = operand|
|STF operand|07|2 through 9|FP = operand|
|PSH operand|08|0 through 9|Push operand onto stack and decrement SP|
|POP operand|09|2 through 9|Pop operand from stack into operand and increment SP|
|CLR operand|0A|2 through 9|operand = all zeros|
|EST operand|0B|2 through 9|operand = all ones|
|PSHA|FFF010|N/A|Push ACC onto stack and decrement SP|
|PSHX|FFF011|N/A|Push XR onto stack and decrement SP|
|PSHF|FFF012|N/A|Push FR onto stack and decrement SP|
|POPA|FFF013|N/A|Pop stack into ACC and increment SP|
|POPX|FFF014|N/A|Pop stack into XR and increment SP|
|POPF|FFF015|N/A|Pop stack into FP and increment SP|
|ADA operand|10|0 through 9|ACC += operand|
|ADX operand|11|0 through 9|XR += operand|
|ADS operand|12|0 through 9|SP += operand|
|ADF operand|13|0 through 9|FP += operand|
|SBA operand|14|0 through 9|ACC -= operand|
|SBX operand|15|0 through 9|XR -= operand|
|SBS operand|16|0 through 9|SP -= operand|
|SBF operand|17|0 through 9|FP -= operand|
|MUL operand|18|0 through 9|ACC *= operand|
|DIV operand|19|0 through 9|ACC /= operand|
|MOD operand|1A|0 through 9|ACC %= operand|
|CMA operand|20|0 through 9|Computes ACC - operand|
|CMX operand|21|0 through 9|Computes XR - operand|
|CMS operand|22|0 through 9|Computes SP - operand|
|CMF operand|23|0 through 9|Computes FP - operand|
|SHRA|FFF022|N/A|ACC >>= 1|
|SHLA|FFF023|N/A|ACC <<= 1|
|JSR operand|41|2 through 9|Push PC onto stack, decrement SP, and set PC = operand|
|RTN|FFF040|N/A|Pop stack into PC and increment SP|
|JEQ operand|48|2 through 9|if (EQ flag == 1) PC = operand|
|JLT operand|4A|2 through 9|if (LT flag == 1) PC = operand|
|JGE operand|4B|2 through 9|if (LT flag == 0) PC = operand|
|NOP|FFF038|N/A|Does nothing|
|HLT|FFFFFF|N/A|Stop the program|

Below a table showing the addressing modes, what it does and how they are represented in the assembly and machine languages. 
|Name|Assembly|Machine|Description|
|---|:---:|:---:|---|
|Immediate|inst # XXX|0|XXX|
|Direct|inst XXX|2|Memory[XXX]|
|Indexed|inst + XXX|4|Memory[XXX + XR]|
|Indirect|inst * XXX|6|Memory[Memory[XXX]]|
|Indirect Indexed|inst & XXX|8|Memory[Memory[XXX] + XR]|
|Frame Immediate|inst# ! XXX|1|XXX+FP|
|Frame Direct|inst ! XXX|3|Memory[XXX + FP]|
|Frame Indexed|inst +! XXX|5|Memory[XXX + FP + XR]|
|Frame Indirect|inst *! XXX|7|Memory[Memory[XXX + FP]]|
|Frame Indirect Indexed|inst &! XXX|9|Memory[Memory[XXX + FP] + XR]|

The opcode and adressing modes functionalities lie beyond the project's scope. However, knowing their representation does make it easier to understand the project. Operands consist of constants, either in base 10 or prefixed with `$` for base 16, or labels. Labels are always lowerrcase, start with a letter, and span no more than eight characters. A label's value is the address of the word containing the instruction or data following the label's creation. 

The program accepts infile and outfile names as command line arguements. The infile contains the the assembly code, while the outfile stores the corresponding machine code. A collection of test files in the `test_files` directory serve as potential infiles, the relative path name must be specified.

To compile, execute  `g++ -std=c++14 main.cpp -o main`

To run, use `./main infile outfile`
