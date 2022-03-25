	PRESERVE8
	THUMB   
		

; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
SortieSon dcw 0  
i dcd 0 

	
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
	export i	
	EXPORT CallbackSon
	EXPORT SortieSon
	import Son
	import LongueurSon
	include Driver/DriverJeuLaser.inc
		
	
; écrire le code ici		
CallbackSon proc
	ldr r3,=i
	ldr R0,[r3]
	;r0= i
	ldr r3, =LongueurSon
	ldr r1, [r3]
	
	;r1=5512
	cmp r0,r1
	;comparer i et 5512
	bne danslaboucle
	;si pas égal on va dans la boucle
	bx lr
	;retour main sinon
danslaboucle
	ldr r2,=Son
	;r2=addresse tableau Son
	ldrsh r3,[r2,r0]
	;r3= son qui nous interesse
	mov r1,#32768
	;r1=32768
	;mul r3,#720;asr r3,#16
	add r3,r1
	;r3=r3+r1
	mov r1,#92
	;r1=92
	sdiv r3,r1
	;r3=r3/r1
	ldr r2,=SortieSon
	
	;r2=addresse Sortie son
	strh r3,[r2]
	;Sortie_SOn[i]=r3
	mov r1,#2
	;r1=1
	add r0,r1
	;r0=r1+r0
	ldr r1,=i
	;r1=addresse i
	str r0,[r1]
	;r0=valeur de i
	mov r0,r3
	push {lr}
	bl PWM_Set_Value_TIM3_Ch3
	pop {lr}
	bx lr
	;retour main
	
	endp
			
		
	END	
		/*
callbackson
{
if (i<5512)
{
SortieSon=(Son[i]+32768)/91;
i++;
}
}
*/