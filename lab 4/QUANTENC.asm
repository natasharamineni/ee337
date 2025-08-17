ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL TAKE_INP
CALL QUANT_ENC
CALL LED_DISP
HERE: SJMP HERE
ORG 130H

TAKE_INP:
MOV P1, #0FH //to set as input ins
MOV R0, #60H //where we want to store input
MOV R2, #8 //8 times led displays
MOV R3, #0F1H //for led
INP: MOV A, R3
SWAP A
MOV P1, A //xF in port
ACALL DELAY_10S
MOV @R0, P1 //x(onehalf) in mem
INC R3 
INC R0
DJNZ R2, INP
MOV R0, #60H //to edit inputs
MOV R2, #8
MOV R3, #01H //0x 
INPNIB: MOV A, @R0
SWAP A //(half)x
CLR C
SUBB A, R3 //(half)x - 0x
MOV @R0, A 
INC R0
INC R3
DJNZ R2, INPNIB
MOV R0, #60H //to make inp into 8 bits
MOV R1, #70H
MOV R2, #4
INPFIN: MOV A, @R0 //first half of input (half)0
MOV R3, A
INC R0
MOV A, @R0 //second half of input 
SWAP A //0(2half)
ADD A, R3 //(1half)(2half)
MOV @R1, A
INC R1
INC R0
DJNZ R2, INPFIN
RET

QUANT_ENC:
MOV R0, #70H
MOV R1, #60H
MOV R2, #4
LOOP: MOV A, @R0
CLR C
SUBB A, #1EH
JNC OP1
MOV A, @R0
CLR C
SUBB A, #14H
JNC OP2
MOV A, @R0
CLR C
SUBB A, #0AH
JNC OP3
MOV @R1, #01H
SJMP NEXT
OP3: MOV @R1, #02H
SJMP NEXT
OP2: MOV @R1, #04H
SJMP NEXT
OP1: MOV @R1, #08H
NEXT: INC R0
INC R1
DJNZ R2, LOOP
RET

LED_DISP:
INF: MOV R0, #60H
MOV R2, #4
LEDLOOP: MOV A, @R0
SWAP A
MOV P1, A
ACALL DELAY_5S
INC R0
DJNZ R2, LEDLOOP
MOV R0, #60H
MOV R2, #4
SJMP INF
RET

DELAY_10S:
push 00h
mov r0, #2
h5: acall DELAY_5S
djnz r0, h5
pop 00h
ret

DELAY_5S:
push 00h
mov r0, #20
h4: acall delay_250ms
djnz r0, h4
pop 00h
ret

delay_250ms:
push 00h
mov r0, #250
h3: acall delay_1ms
djnz r0, h3
pop 00h
ret

delay_1ms:
push 00h
mov r0, #4
h2: acall delay_250us
djnz r0, h2
pop 00h
ret

delay_250us:
push 00h
mov r0, #244
h1: djnz r0, h1
pop 00h
ret

RET
END