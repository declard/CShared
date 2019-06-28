__declspec(naked) long __fastcall Lock(long volatile *Semaphor,long NewValue,long TestValue) {
	__asm {
		pop	eax
		lock	cmpxchg	[ecx],edx
		ret
	}
}