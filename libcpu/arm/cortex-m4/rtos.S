;汇编程序

;关总中断和开总中断
		EXPORT	OS_CPU_SaveSR
		EXPORT	OS_CPU_RestoreSR

		IMPORT	p_OS_TCB_Cur			;当前任务控制块指针
		IMPORT	p_OS_TCB_HighRdy		;最高优先级任务控制块指针

		EXPORT	OS_TASK_StartHighRdy
		EXPORT	OS_SW
NVIC_SYSPRI14   EQU     0xE000ED22                              ; System priority register (priority 14).
NVIC_PENDSV_PRI EQU         0xFFFF                              ; PendSVºÍµÎ´ð¶¨Ê±Æ÷ÓÅÏÈ¼¶ÉèÖÃÎª×îµÍ

        AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
        REQUIRE8
        PRESERVE8

;关总中断和开总中断

OS_CPU_SaveSR					;关总中断
		MRS 	R0, PRIMASK		;读取PSIMASK到r0,r0为返回值					
		CPSID 	I 				;PRIMASK=1,关中断(NMI和硬件FAULT可以响应)
		BX 		LR				;返回

OS_CPU_RestoreSR				;开总中断
 		MSR 	PRIMASK,R0		;读取r0到PSIMASK中,r0为参数
		CPSIE	I 				;PRIMASK=0,开中断
		BX 		LR				;


;根据设定的栈结构顺序出栈
POP_ALL
		LDMFD	SP!,{R4}		;PSR出栈
		MSR		PSR,R4
		LDMFD	SP!,{R0-R12,PC}	;R0-R12,LR,PC出栈	;去掉了LR
		BX 		LR

OS_TASK_StartHighRdy
		LDR     R0, =NVIC_SYSPRI14      ; Set the PendSV exception priority
		LDR     R1, =NVIC_PENDSV_PRI
		STRB    R1, [R0]
		
		LDR		R4,=p_OS_TCB_HighRdy	;取出最高优先级就绪任务的TCB地址
		LDR		R4,[R4]					;取任务的栈顶指针(因为Task_Ctr_Block地址也是OS_TCB_StkPtr的地址)
		LDR		SP,[R4]					;任务的栈顶指针赋给SP
		B		POP_ALL					;根据设定的栈结构顺序出栈
		BX 		LR

;OS相关
OS_SW						;任务级的任务切换
;		STMFD	SP!,{LR}		;PC入栈
		STMFD	SP!,{R0-R12,LR}	;R0-R12,LR入栈
				
		B		GetHigTcbSP
		BX 		LR

;´ýÔËÐÐµÄÈÎÎñµÄÕ»¶¥Ö¸Õë×°ÔØµ½CPUµÄSP
GetHigTcbSP								;È¡³ö¸ü¸ßÓÅÏÈ¼¶ÈÎÎñµÄ¶ÑÕ»Ö¸Õëµ½SP,SP=TCB[OSPrioCur].OSTCBStkPtr
		LDR		R6,=p_OS_TCB_HighRdy	;È¡³ö¸ü¸ßÓÅÏÈ¼¶¾ÍÐ÷ÈÎÎñµÄTCBµØÖ·
		LDR		R6,[R6]
		LDR		SP,[R6]			;È¡³ö¸ü¸ßÓÅÏÈ¼¶¾ÍÐ÷ÈÎÎñµÄ¶Ñ¶¥Ö¸Õëµ½SP
		B		POP_ALL			;È¡³öÉè¶¨µÄÕ»½á¹¹Ë³Ðò³öÕ»
		BX 		LR

		END