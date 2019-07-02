#ifndef ZEROK_C_STRING_H
#define ZEROK_C_STRING_H

#include <stdint.h>

typedef char* cstring;

/*init and destory*/
cstring		cstr_init();
cstring		cstr_initchar(const char* v, size_t v_size);
void		cstr_destroy(cstring s);

/*get string context*/
char*		cstr_value(cstring s);
/*cstring size*/
size_t		cstr_size(cstring s);
uint8_t		cstr_empty(cstring s);
/*update size by '\0'*/
void		cstr_update(cstring s);
/*cstring cat*/
cstring		cstr_cat(cstring dst, cstring src);
cstring		cstr_catchar(cstring dst, const char* v, size_t v_size);
/*cstring copy*/
cstring		cstr_cpy(cstring dst, cstring src);
cstring		cstr_cpychar(cstring dst, const char* v, size_t v_size);
/*cstring cmp*/
int32_t		cstr_cmp(cstring s1, cstring s2);
int32_t		cstr_cmpchar(cstring s, const char* v, size_t v_size);
/*cstring lower upper*/
void		cstr_tolower(cstring s);
void		cstr_toupper(cstring s);
/*del cset from cstring*/
cstring		cstr_trim(cstring s, const char* cset);
void		cstr_clear(cstring s);
/*sprintf format*/
cstring		str_printf(cstring s, const char* fmt, ...);
/*number to cstring*/
cstring		itocstr(cstring s, int64_t v);
/*cstring to number*/
int64_t		cstrtoi(cstring s);

/*cstring dump*/
void		cstr_dump(cstring s);
#endif
