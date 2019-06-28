#include "varargs.h"
// #define �� ���� �����
__declspec(naked) unsigned long varargs_num() {
	_asm {
		mov ecx,[ebp+4]			// ������ ����� ��������
		xor eax,eax
		mov dx,word ptr [ecx]	// ����������� � ���������� �� ������ ��������
		cmp dx,0C483h			// ��������, ��� add esp,����
		jne not_byte
		mov al,byte ptr [ecx+2]	// ���������� ���� ����
		ret
not_byte:
		cmp dx,0C481h			// �������� ���, ��� ��� add esp,�������_�����
		jne not_dword
		mov eax,dword ptr [ecx+2]	// ���������� ���
not_dword:
		ret						// �� � ���� ��� �� ���� �� ������� - 0
	}
}

__declspec(naked) void* varargs_first() {
	_asm {
		lea eax,[ebp+8]
		ret
	}	// ����� ������: �������� �� ������ ebp+8, ��� ������ ����������
		// ������� ��� ��������� (��� ��� ������� �����)
}

#pragma push(warning)
#pragma warning(disable:4731)
int varargs_probe_frame() {
#ifndef _DEBUG		// ���� ����� �������� �� �����, ���� ����������� ��� ���
	_asm {
		xor eax,eax
		inc eax
		cmp esp,ebp	// ���� ��� �����, ������ ��� ������������ ��...
		jne done
		pop ebp		// ... � ����� ������������ ebp
		dec eax		// � ������� 0
	done:			// ���� �� ���, �� 1
		ret
	}
#else
	return 0;		// ���� ������� �����, �� ����������� ���
#endif
}

// ����������, ����������� ��������� �� (1) ��� ��� (0)
static const int varargs_omit_frame=varargs_probe_frame();
#pragma pop(warning)

__declspec(naked) void varargs_prep() {
	if (varargs_omit_frame) _asm {	// ���� �� �����������, ����� ������� ������
		mov eax,[esp]
		sub eax,5					// ��� ����� ��� ����� ������ sub esp,...
		lea ebp,[esp+1]
		cmp word ptr [eax],0xEC81	// ...�������_�����
		jne not_dword
		add ebp,[eax+2]
		jmp not_byte
	not_dword:
		sub eax,3
		cmp word ptr [eax],0xEC83	// ...����
		jne not_byte
		xor ebx,ebx
		mov bl,[eax+2]
		add ebp,ebx
	not_byte:
		ret							// ���� ��� �� ��������.
			/*
				��� ������� ������ ������ ����� ������ ��������
				� ���������� �-�, �.�. ��� ���������� � ����
				���������� �-�, �������� ������ ������ ������� ����� ���
				��������� ����������. ������ �� ���� ��� �������� ���������
				���������� EBP. �� ��� ���������� � ������ �������� ��
				VC++8.0 (�� ������� ���� ���� ��������� ���). �����
				�������� ��������� ��-��, ��-��������, ������ � �����������,
				��������� ������� ���������� ��������� ���������� ���������
				�� ��� ��������� �����������. ;(
			*/
	}
	else _asm ret					// ���� ��� - �������
}

__declspec(naked) void varargs_probe(char&) {
	if (varargs_omit_frame) _asm mov ebp,[esp]
	_asm ret
}