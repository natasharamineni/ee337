ORG 0H
LJMP MAIN
ORG 100H
MAIN: 
CALL SORT
HERE: SJMP HERE
ORG 130H

SORT:
MOV R0, #60H		//for storing the input array into the desired location
MOV R1, #70H
MOV R7, #08H
LOOP1:
MOV A, @R0
MOV @R1, A
INC R0
INC R1
DJNZ R7, LOOP1

MOV R6, #7 		//counter for one loop
LOOP3: MOV R0, #70H
MOV R2, 06H
LOOP2: MOV A, @R0  //content of 70h in a
INC R0
MOV R3, A //temp storage of content of 70h
CLR C
SUBB A, @R0 //70h - 71h
JC NEXT //if 71h is > 70h then we need to go to the next cycle without swapping
MOV A, @R0 //71h in a
DEC R0 //70H
MOV @R0, A // 71H in 70h
INC R0 //71H
MOV A, R3 //70h in A
MOV @R0, A //70H in 71h
NEXT: DJNZ R2, LOOP2 //we need 2 loops
DJNZ R6, LOOP3

RET

END


