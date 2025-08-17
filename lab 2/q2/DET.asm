ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL DET
HERE: SJMP HERE
ORG 130H

DET:

MOV A, 61H
MOV B, 62H
MUL AB 		//b*c
MOV R4, B 	//UPPER BYTE
MOV R5, A 	//LOWER BYTE
MOV A, 60H
MOV B, 63H
MUL AB 		//a*d
MOV R2, B  //UPPER BYTE IN B
CLR C
SUBB A, R5 //a*d lower byte - b*c lower byte
MOV 71H, A
MOV A, R2 
SUBB A, R4 //a*d upper byte - b*c upper byte
MOV 70H, A
RET 
END