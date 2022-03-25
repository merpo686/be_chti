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
	EXPORT CallbackSon
	EXPORT SortieSon
	import Son
	
; écrire le code ici		
CallbackSon proc
	ldr r0,i
	;r0=addresse de i
	mov r1,#5512
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
	ldr r3,[r2,r0]
	;r3= son qui nous interesse
	mov r1,#32768
	;r1=32768
	add r3,r1
	;r3=r3+r1
	mov r1,#91
	;r1=91
	sdiv r3,r1
	;r3=r3/r1
	ldr r2,=SortieSon
	;r2=addresse Sortie son
	str r3,[r2,r0]
	;Sortie_SOn[i]=r3
	mov r1,#1
	;r1=1
	add r0,r1
	;r0=r1+r0
	ldr r1,=i
	;r1=addresse i
	str r0,[r1]
	;r0=valeur de i
	add r0,#1
	;i+=1
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