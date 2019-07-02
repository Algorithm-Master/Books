#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

#include "c_string.h"
/*init size*/
#define INIT_CSTRING_SIZE	64
#define MAX_CSTRING_ALLOC	(1024*1024)

#ifndef max
#define max(x, y) ((x) > (y) ? (x) : (y))
#endif

#ifndef min
#define min(x, y) ((x) < (y) ? (x) : (y))
#endif

/*define string struct*/
typedef struct string_s{
    int32_t len;
    int32_t free;
    char buf[];
}string_t;

#define STRING_T(s) (string_t *)(s - sizeof(string_t))

cstring cstr_init()
{
	string_t* s;
	s = (string_t *)malloc(sizeof(string_t) + INIT_CSTRING_SIZE + 1);
	if(s == NULL)
		return NULL;
	
	s->free = INIT_CSTRING_SIZE;
	s->len = 0;
	s->buf[s->len] = '\0';

	return (char*)s->buf;
}

cstring cstr_initchar(const char* v, size_t v_size)
{
	string_t* s = NULL;
	size_t size = (v_size < INIT_CSTRING_SIZE) ? INIT_CSTRING_SIZE : v_size;

	s = (string_t *)malloc(sizeof(string_t) + size + 1);
	if(s == NULL)
		return NULL;

	if(v != NULL && v_size > 0 ){
		memcpy(s->buf, v, v_size);
	}

	s->len = v_size;
	s->free = size - v_size;
	s->buf[s->len] = '\0';

	return (char*)s->buf;
}

void cstr_destroy(cstring s)
{
	if(s != NULL){
		free(STRING_T(s));
	}
}

char* cstr_value(cstring s)
{
	return s;
}

size_t cstr_size(cstring s)
{
	string_t* str = STRING_T(s);
	return str->len;
}

uint8_t cstr_empty(cstring s)
{
	string_t* str = STRING_T(s);
	if(str->len == 0)
		return -1;
	else
		return 0;
}

void cstr_update(cstring s)
{
	string_t* str = STRING_T(s);
	size_t len = strlen(str->buf);
	str->free += str->len - len;
	str->len = len;
}

cstring cstr_realloc(cstring s, size_t size)
{
	string_t* str = STRING_T(s);
	size_t str_size = str->free + str->len;
	
	/*resize mem */
	if(str_size < size){
		str_size = size;
		if(str_size < MAX_CSTRING_ALLOC)
			str_size *= 2;
		else
			str_size += MAX_CSTRING_ALLOC;

		str = (string_t *)realloc(str, sizeof(string_t) + str_size + 1);
		if(str == NULL)
			return NULL;

		str->free = str_size - str->len;
		str->buf[str->len] = '\0';
	}

	return (char *)str->buf;
}

cstring cstr_catchar(cstring dst, const char* v, size_t v_size)
{
	string_t* d = STRING_T(dst);
	dst = cstr_realloc(dst, d->len + v_size);
	if(dst == NULL)
		return NULL;

	d = STRING_T(dst);

	memcpy(dst + d->len, v, v_size);
	d->free -= v_size;
	d->len += v_size;
	d->buf[d->len] = '\0';

	return (char *)d->buf;
}

cstring cstr_cat(cstring dst, cstring src)
{
	string_t* s = STRING_T(src);
	return cstr_catchar(dst, s->buf, s->len);
}

cstring cstr_cpy(cstring dst, cstring src)
{
	string_t* s = STRING_T(src);
	return cstr_cpychar(dst, s->buf, s->len);
}

cstring cstr_cpychar(cstring dst, const char* v, size_t v_size)
{
	string_t* d;
	dst = cstr_realloc(dst, v_size);
	if(dst == NULL || v == NULL)
		return NULL;

	d = STRING_T(dst);
	memcpy(d->buf, v, v_size);
	d->free = d->free + d->len - v_size;
	d->len = v_size;
	d->buf[d->len] = '\0';

	return (char *)d->buf;
}

int32_t cstr_cmp(cstring s1, cstring s2)
{
	size_t len1, len2, min_len;
	int32_t cmp;

	len1 = cstr_size(s1);
	len2 = cstr_size(s2);
	min_len = min(len1, len2);

	cmp = memcmp(s1, s2, min_len);
	if(cmp == 0)
		return len1 - len2;
	
	return cmp;
}

int32_t cstr_cmpchar(cstring s, const char* v, size_t v_size)
{
	int32_t cmp;
	string_t* str = STRING_T(s);
	size_t min_len = min(str->len, v_size);

	if(v == NULL)
		return 1;
	
	cmp = memcmp(s, v, min_len);
	if(cmp == 0)
		return str->len - v_size;

	return cmp;
}

void cstr_tolower(cstring s)
{
	size_t len = cstr_size(s);
	size_t i = 0;

	for(i = 0; i < len; i++)
		s[i] = tolower(s[i]);
}

void cstr_toupper(cstring s)
{
	size_t len = cstr_size(s);
	size_t i = 0;

	for(i = 0; i < len; i++)
		s[i] = toupper(s[i]);
}

void cstr_clear(cstring s)
{
	string_t* str = STRING_T(s);
	str->free += str->len;
	str->len = 0;
	str->buf[0] = '\0';
}

cstring cstr_trim(cstring s, const char* cset)
{
	string_t* sh = STRING_T(s);
	char *start, *end, *sp, *ep;
	size_t len;

	sp = start = s;
	ep = end = s + cstr_size(s) - 1;
	/*delete head*/
	while(sp <= end && strchr(cset, *sp)) sp ++;
	/*delete tail*/
	while(ep > start && strchr(cset, *ep)) ep --;
	len = (sp > ep) ? 0 : ((ep - sp) + 1);

	if (sh->buf != sp) 
		memmove(sh->buf, sp, len);

	sh->buf[len] = '\0';
	sh->free = sh->free+(sh->len-len);
	sh->len = len;

	return s;
}

cstring str_printf(cstring s, const char* fmt, ...)
{
	va_list ap;
	cstring t;
	char *buf;
	size_t buflen = INIT_CSTRING_SIZE;
	
	va_start(ap, fmt);
	while(1){
		buf = (char *)malloc(buflen);
		if (buf == NULL) 
			return NULL;

		buf[buflen-2] = '\0';
#ifdef WIN32
		_vsnprintf(buf, buflen, fmt, ap);
#else
		vsnprintf(buf, buflen, fmt, ap);
#endif
		if (buf[buflen-2] != '\0') {
			free(buf);
			buflen *= 2;
			continue;
		}
		break;
	}

	t = cstr_cpychar(s, buf, strlen(buf));
	free(buf);

	va_end(ap);

	return t;
}

cstring itocstr(cstring s, int64_t v)
{
	return str_printf(s, "%lld", v);
}

int64_t cstrtoi(cstring s)
{
	int64_t ret = 0;
	char* pos = (char*)s;
	int32_t minus = 0;
	string_t* sh = STRING_T(s);

	if(s != NULL && sh->len > 0){
		while(*pos != '\0'){
			if(*pos >= '0' && *pos <= '9'){
				ret *= 10;
				ret += *pos - '0';
			}
			else if(pos == s && *pos == '-')
				minus = 1;
			else
				break;
			pos ++;
		}
	}

	if(minus)
		ret = 0 - ret;

	return ret;
}

void cstr_dump(cstring s)
{
	string_t* str = STRING_T(s);
	printf("string = %s, len = %d, free = %d\r\n", str->buf, str->len, str->free);
}






