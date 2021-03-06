.386
DATA SEGMENT USE16
in_num	DB 6
		DB ?
		DB 6 DUP(0)
multi	DW 1,10,100,1000,10000
BUF 	DW 0
FLAG	DB 0
MSG		DB 'Error input!$'
DATA ENDS
STACK SEGMENT USE16 STACK
	DB 200 DUP(0)
STACK ENDS
CODE SEGMENT USE16
	ASSUME DS:DATA,CS:CODE,SS:STACK
START:
		MOV AX,DATA
		MOV DS,AX
CON:
		LEA DX,in_num
		MOV AH,10
		INT 21H
		MOV BL,in_num+1
		MOV BH,0
		MOV BYTE PTR in_num+2[BX],'$'			
		CMP BYTE PTR in_num+1,0H   ;仅输入回车符号，不进行修改
		JE QUIT	
		
		CALL STR_NUM
		CMP FLAG,1
		JE NEXT
		MOV DL,0AH
		MOV AH,2
		INT 21H
		MOV DL,0DH
		MOV AH,2
		INT 21H		
		LEA DX,MSG
		MOV AH,9
		INT 21H
		MOV DL,0AH
		MOV AH,2
		INT 21H
		MOV DL,0DH
		MOV AH,2
		INT 21H			
		JMP CON		
NEXT:		
		OUT 70H,AL
		IN AL,71H
		
		MOV AH,AL
		AND AL,0FH
		SHR AH,4
		ADD AX,3030H
		
		MOV BX,AX
		LEA SI,BUF
		MOV WORD PTR [SI],BX
		
		MOV DL,0AH
		MOV AH,2
		INT 21H
		MOV DL,0DH
		MOV AH,2
		INT 21H		
		
		MOV DL,BH
		MOV AH,2
		INT 21H
		MOV DL,BL
		MOV AH,2
		INT 21H	
		
		MOV DL,0AH
		MOV AH,2
		INT 21H
		MOV DL,0DH
		MOV AH,2
		INT 21H		
		JMP CON		
QUIT:		
		MOV AH,4CH
		INT 21H
;子模块 STR_NUM
	;功能：将in_num中的字符串转化为数字存入到AX中,BX、SI、DI被保护
	;入口参数：无
	;出口参数：AX
STR_NUM PROC NEAR
		PUSH SI
		PUSH DI
		PUSH BX
				
		MOV EBX,0
		MOV CL,BYTE PTR in_num+1
		MOV CH,0
		MOV SI,0
		MOV DI,CX
		MOVZX EDI,DI
LOOPH:		
		MOVZX EAX,BYTE PTR in_num+2[SI]
		
		CMP EAX,30H
		JB WRONG_CHANGE
		CMP EAX,39H
		JA WRONG_CHANGE
	
		MOV FLAG,1
		SUB EAX,30H
		MOVZX EDX,WORD PTR multi+[EDI*2-2]
		MUL EDX
		ADD EBX,EAX
		
		DEC EDI
		INC SI
		CMP EDI,0
		JNE LOOPH
		
		MOV EAX,EBX	
		JMP END_CHANGE
WRONG_CHANGE:
		MOV FLAG,0	
END_CHANGE:
		POP BX
		POP DI
		POP SI
		RET
STR_NUM ENDP
CODE ENDS
	END START