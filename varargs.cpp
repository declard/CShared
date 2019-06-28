#include "varargs.h"
// #define КС кадр стэка
__declspec(naked) unsigned long varargs_num() {
	_asm {
		mov ecx,[ebp+4]			// Достаёт адрес возврата
		xor eax,eax
		mov dx,word ptr [ecx]	// Заглядывает в инструкцию по адресу возврата
		cmp dx,0C483h			// Возможно, там add esp,байт
		jne not_byte
		mov al,byte ptr [ecx+2]	// Возвращаем этот байт
		ret
not_byte:
		cmp dx,0C481h			// Возможно ещё, что там add esp,двойное_слово
		jne not_dword
		mov eax,dword ptr [ecx+2]	// Возвращаем его
not_dword:
		ret						// Ну а если нет ни того ни другого - 0
	}
}

__declspec(naked) void* varargs_first() {
	_asm {
		lea eax,[ebp+8]
		ret
	}	// Очень просто: проходим по адресу ebp+8, где должна начинаться
		// область под аргументы (или она нулевой длины)
}

#pragma push(warning)
#pragma warning(disable:4731)
int varargs_probe_frame() {
#ifndef _DEBUG		// Если дебаг выключен то узнаём, есть оптимизация или нет
	_asm {
		xor eax,eax
		inc eax
		cmp esp,ebp	// Если они равны, значит был сгенерирован КС...
		jne done
		pop ebp		// ... и нужно восстановить ebp
		dec eax		// и вернуть 0
	done:			// Если не был, то 1
		ret
	}
#else
	return 0;		// Если включен дебаг, то оптимизации нет
#endif
}

// Показывает, подавляется генерация КС (1) или нет (0)
static const int varargs_omit_frame=varargs_probe_frame();
#pragma pop(warning)

__declspec(naked) void varargs_prep() {
	if (varargs_omit_frame) _asm {	// Если КС подавляется, нужно ставить руками
		mov eax,[esp]
		sub eax,5					// Тут вроде как может лежать sub esp,...
		lea ebp,[esp+1]
		cmp word ptr [eax],0xEC81	// ...двойное_слово
		jne not_dword
		add ebp,[eax+2]
		jmp not_byte
	not_dword:
		sub eax,3
		cmp word ptr [eax],0xEC83	// ...байт
		jne not_byte
		xor ebx,ebx
		mov bl,[eax+2]
		add ebp,ebx
	not_byte:
		ret							// Жаль оно не работает.
			/*
				Эта функция должна стоять самой первой командой
				в вызывающей ф-е, т.к. она обращается к коду
				вызывающей ф-и, доставая оттуда размер области стэка под
				локальные переменные. Именно по нему она способна правильно
				выставлять EBP. Всё это колдовство с бубном работает на
				VC++8.0 (по крайней мере было задуманно так). Бубен
				пришлось применять из-за, по-видимому, ошибки в компиляторе,
				благодаря которой невозможно отключить подавление генерации
				КС при включеной оптимизации. ;(
			*/
	}
	else _asm ret					// Если нет - ненужно
}

__declspec(naked) void varargs_probe(char&) {
	if (varargs_omit_frame) _asm mov ebp,[esp]
	_asm ret
}