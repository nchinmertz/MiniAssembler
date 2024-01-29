This project is meant to simulate an assembler. It takes in a file, written in a simplified assemble code and translates it to machine code. The language is based on RISC-V therefore each instruction is 24 bits. The instructions can either be a oeprand instruction, which has an opcode, an addressing mode and a stated operand, or a operate instruction which is only an opcode. Below is a table showing the opcode in the assembly language, what it does, how it is represented in machine code, and what adressing modes it supports.

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

What the opcode and adressing modes mean, do not really matter in the scope of this project. However, it does make more sense to know what they are representing. Operands are either constants, in base 10 or base 16 which is denoted with a `$` before the value, or labels. Labels are always lowerrcase, start with a letter, and are no more than eight characters. A labels value is the address of the word containing the instruction or data that immedietly follows the label's creation. 

The project takes in an infile and outfile as command line arguements. The infile is a "program" in this assembly language and the outfile is the "machine" code output. There are a bunch of testing files in the `test_files` folder which can be used for an infile, the relative path name must be specified.

To compile use  `g++ -std=c++14 main.cpp -o main`

To run use `./main infile outfile`
