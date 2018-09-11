.386
DATA 	SEGMENT USE16
XUEHAO 	DB 6,2,7,7
BUF		DB 4 DUP(0)
DATA 	ENDS

STACK 	SEGMENT USE16	STACK
		DB	200 DUP(0)
STACK 	ENDS

CODE 	SEGMENT USE16
		ASSUME CS:CODE,SS:STACK,DS:DATA

START:	MOV AX,DATA
		MOV	DS,AX
	
		MOV	SI,OFFSET XUEHAO
		MOV DI,OFFSET BUF
		MOV AL,[SI]
		MOV [DI],AL	;寄存器间接寻址方法

		MOV SI,1			
		LEA BX,XUEHAO
		MOV AL,[BX+SI]
		LEA BX,BUF
		MOV [BX+SI],AL ;基址加变址方式
		
		MOV AL,DS:[2H]
		MOV DS:[6H],AL	;直接寻址方式
		
		MOV BYTE PTR DS:[7H],7H	;立即寻址方式
		
		MOV AH,4CH
		INT 21H		
CODE 	ENDS
		END		START
	
	