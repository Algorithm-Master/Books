#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "c_string.h"

int main(int argc, const char* argv[])
{
	const char* ctx = "zerok is ok \r\n yes fuck you \r\n udp 100000000 pre\r\n, haha basic ok\r\n, c-string test\r\n";
	const char* sub = "zerok ok!";
	const char* v1 = "yes2";
	const char* v2 = "yes2ZZZ";

	cstring s, d;
	int32_t	cmp = 0;
	int64_t num = 0;
	
	printf("test init \r\n");
	s = cstr_initchar(ctx, strlen(ctx));
	cstr_dump(s);

	printf("#####s = %s\r\n####\n", s);
	cstr_destroy(s);
	printf("*************cat*************\r\n");

	s = cstr_init();
	cstr_dump(s);
	s = cstr_catchar(s, sub, strlen(sub));
	cstr_dump(s);
	printf("**************copy************\r\n");

	d = cstr_initchar(sub, strlen(sub));
	cstr_dump(d);
	d = cstr_cpychar(d, ctx, strlen(ctx));
	cstr_dump(d);
	d = cstr_cpy(d, s);
	cstr_dump(d);

	printf("**************cmp************\r\n");
	s = cstr_cpychar(s, v1, strlen(v1));
	d = cstr_cpychar(d, v2, strlen(v2));
	cmp = cstr_cmp(s, d);
	if(cmp == 0)
		printf("s = d \r\n");
	else if(cmp < 0)
		printf("s < d\r\n");
	else if(cmp > 0)
		printf("s > d\r\n");
	printf("*********lower upper**********\r\n");
	cstr_dump(d);
	cstr_tolower(d);
	cstr_dump(d);
	cstr_toupper(d);
	cstr_dump(d);
	printf("**********trim clear*********\r\n");
	s = cstr_cpychar(s, "  zerok  ", strlen("  zerok  "));
	cstr_dump(s);
	cstr_trim(s, " zk");
	cstr_dump(s);
	cstr_clear(s);
	cstr_dump(s);
	printf("*********str_printf********\r\n");
	s = str_printf(s, "zerok = %d, id = %d, \r\n", 100000000, 10);
	cstr_dump(s);

	s = itocstr(s, 198766363644);
	cstr_dump(s);
	num = cstrtoi(s);
	printf("num = %lld\r\n", num);

	cstr_destroy(s);
	cstr_destroy(d);
}



