#include "string_util.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *const_string_reverse(const char *str){
	size_t n = strlen(str);
	char *new_str = calloc(n+1,1);
	size_t j = 0;
	for(size_t i = n-1; i < n; i--) {
		new_str[j++]=str[i];
	}
	return new_str;
}

void string_reverse(char *str){
	size_t n = strlen(str);
	for(size_t i = 0, j = n-1; i < j; i++, j--) {
		char tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
	}
}
