.486
.model flat
option casemap :none
.code

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;; VoidCast class implementation ;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;public: __thiscall VoidCast::operator void *(void)
??BVoidCast@@QAEPAXXZ PROC
	mov eax,[ecx]		; Just return itself
	retn
??BVoidCast@@QAEPAXXZ ENDP
nop

;public: class VoidCast & __thiscall VoidCast::operator=(class VoidCast const &)
??4VoidCast@@QAEAAV0@ABV0@@Z PROC
	mov eax,[esp+4]
	mov edx,[eax]
	mov [ecx],edx
	mov eax,ecx
	ret 4
??4VoidCast@@QAEAAV0@ABV0@@Z ENDP
nop

;public: __cdecl VoidCast::VoidCast(...)
??0VoidCast@@QAA@ZZ PROC
	mov edx,[esp+8]	; Casting ptr
	mov eax,[esp+4]	; 'this' ptr
	mov [eax],edx	; Store it in object
	ret
??0VoidCast@@QAA@ZZ ENDP
nop


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;; Delegate class implementation ;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Class 'Delegate' fields offset list:
DOBJ	equ	0
DMET	equ 	4
DTYP	equ	8
DESP	equ	12
DEBP	equ	16
DRET	equ	20
DESP0	equ	24
DESP1	equ	28
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Supported calling types list:
DTC	equ	0	; Non-static thiscall
DCC	equ	1	; Non-static cdecl
DSC	equ	2	; Non-static stdcal
DFC	equ	3	; Non-static fastcall
DSCC	equ	4	; Static cdecl
DSSC	equ	5	; Static stdcall
DSFC	equ	6	; Static fastcall
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;public: __thiscall DelegateBase::DelegateBase(class DelegateBase const & )
;public: class DelegateBase & __thiscall DelegateBase::operator=(class DelegateBase const &)
??4DelegateBase@@QAE@ABV0@@Z PROC
??4DelegateBase@@QAEAAV0@ABV0@@Z PROC
	mov eax,[esp+4]
	cmp ecx,eax
	je RETURN
	mov edx,[eax+DOBJ]
	mov [ecx+DOBJ],edx
	mov edx,[eax+DMET]
	mov [ecx+DMET],edx
	mov edx,[eax+DTYP]
	mov [ecx+DTYP],edx
	mov eax,ecx
RETURN:ret 4
??4DelegateBase@@QAEAAV0@ABV0@@Z ENDP
??4DelegateBase@@QAE@ABV0@@Z ENDP
nop

;public: __thiscall DelegateBase::DelegateBase(class VoidCast,class VoidCast,int)
??0DelegateBase@@QAE@VVoidCast@@0H@Z PROC
	mov eax,[esp+4]
	mov edx,[esp+8]
	mov [ecx+DOBJ],eax	; Store object
	mov [ecx+DMET],edx	; Store method
	mov eax,[esp+12]
	mov [ecx+DTYP],eax	; Set type
	mov eax,ecx
	ret 12
??0DelegateBase@@QAE@VVoidCast@@0H@Z ENDP
nop

;public: __thiscall DelegateBase::operator bool(void)
??BDelegateBase@@QAE_NXZ PROC
	xor eax,eax
	xor edx,edx
	test dword ptr [ecx+DOBJ],-1
	setnz dl
	mov al,[ecx+DTYP]
	and al,4
	or dl,al
	setz dl
	dec edx
	test edx,[ecx+DMET]
	setnz al
	ret
??BDelegateBase@@QAE_NXZ ENDP
nop

;public:void * __cdecl DelegateBase::operator()(...)
??RDelegateBase@@QAAPAXZZ PROC
	mov ecx,[esp+4]		; Extract 'this' pointer
	call ??BDelegateBase@@QAE_NXZ	; Check if object is empty or not
	test eax,eax
	jz RETURN
	mov edx,[ecx+DTYP]
	cmp edx,7
	jae RETURN		; Unsupported calling convention
	mov [ecx+DEBP],ebp
	pop dword ptr [ecx+DRET]	; Save return address
	pop ebp			; i REALLY hope, callee won't modify EBP (or register must be saved), 'cos it now contains 'this' pointer
	mov eax,[ebp+DMET]
	mov ecx,[ebp+DOBJ]
	jmp DJUMP_MAP[edx*4]

DTCL:	mov [ebp+DESP],esp
	call eax
	mov esp,[ebp+DESP]
	jmp DONE

DCCL:	push ecx
	call eax
	pop eax
	jmp DONE

DSCL:	mov [ebp+DESP],esp
	push ecx
	call eax
	mov esp,[ebp+DESP]
	jmp DONE

DFCL:	pop edx
	mov [ebp+DESP0],edx
	mov [ebp+DESP],esp
	call eax
	mov esp,[ebp+DESP]
	push dword ptr [ebp+DESP0]
	jmp DONE

DSCCL:	call eax	; STATIC CDECL is fastest
	jmp DONE

DSSCL:	mov [ebp+DESP],esp
	call eax
	mov esp,[ebp+DESP]
	jmp DONE

DSFCL:	pop ecx
	pop edx
	mov [ebp+DESP0],ecx
	mov [ebp+DESP1],edx
	mov [ebp+DESP],esp
	call eax
	mov esp,[ebp+DESP]
	push [ebp+DESP1]
	push [ebp+DESP0]

DONE:	mov edx,ebp		; Well, if func saved or haven't modified EBP, then it must work
	mov ebp,[edx+DEBP]
	push edx
	push dword ptr [edx+DRET]
RETURN:ret
DJUMP_MAP dd DTCL,DCCL,DSCL,DFCL,DSCCL,DSSCL,DSFCL
??RDelegateBase@@QAAPAXZZ ENDP
nop


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;; Event class implementation ;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Class 'Event' fields offset list:
EESP	equ	0
EEBP	equ	4
EEBX	equ	8
ERET	equ	12
EESP0	equ	16
EESP1	equ	20
ELIST	equ	24
LOBJ	equ	0
LMET	equ	4
LTYP	equ	8
LNEXT	equ	12
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Supported calling types list:
;DSCC	equ	1	; Static cdecl
;DSSC	equ	2	; Static stdcall
;DSFC	equ	3	; Static fastcall
;DTC	equ	4	; Non-static thiscall
;DCC	equ	5	; Non-static cdecl
;DSC	equ	6	; Non-static stdcal
;DFC	equ	7	; Non-static fastcall
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;public:void __cdecl Event::operator()(...)
??REvent@@QAAXZZ PROC
	mov eax,[esp+4]		; Extract 'this' pointer into EAX (temporary)
	mov edx,[eax+ELIST]
	test edx,edx
	jz RETURN
	mov [eax+EEBP],ebp	; Store stack frame...
	mov [eax+EEBX],ebx	; ...and base register
	pop dword ptr [eax+ERET]	; Store return address
	pop ebp			; i REALLY hope, callee won't modify EBP (or register must be saved), 'cos it now contains 'this' pointer
	mov ebx,edx
	jmp FIRST
NEXT:	mov ebx,[ebx+LNEXT]
	test ebx,ebx
	jz DONE
FIRST:	mov edx,[ebx+LTYP]
	mov eax,[ebx+LMET]
	mov ecx,[ebx+LOBJ]
	jmp EJUMP_MAP[edx*4]

DTCL:	mov [ebp+EESP],esp
	call eax
	mov esp,[ebp+EESP]
	jmp NEXT

DCCL:	push ecx
	call eax
	pop eax
	jmp NEXT

DSCL:	mov [ebp+EESP],esp
	push ecx
	call eax
	mov esp,[ebp+EESP]
	jmp NEXT

DFCL:	pop edx
	mov [ebp+EESP],esp
	mov [ebp+EESP0],edx
	call eax
	mov esp,[ebp+EESP]
	push dword ptr [ebp+EESP0]
	jmp NEXT

DSCCL:	call eax
	jmp NEXT

DSSCL:	mov [ebp+EESP],esp
	call eax
	mov esp,[ebp+EESP]
	jmp NEXT

DSFCL:	pop ecx
	pop edx
	mov [ebp+EESP0],ecx
	mov [ebp+EESP1],edx
	mov [ebp+EESP],esp
	call eax
	mov esp,[ebp+EESP]
	push [ebp+EESP1]
	push [ebp+EESP0]
	jmp NEXT

DONE:	mov edx,ebp
	mov ebp,[edx+EEBP]
	mov ebx,[edx+EEBX]
	push edx
	push dword ptr [edx+ERET]
RETURN:ret
EJUMP_MAP dd DTCL,DCCL,DSCL,DFCL,DSCCL,DSSCL,DSFCL
??REvent@@QAAXZZ ENDP

end