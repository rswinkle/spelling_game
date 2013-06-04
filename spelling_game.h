#ifndef SPELLING_GAME_H
#define SPELLING_GAME_H

#include <string.h>
#include <ctype.h>
#include "cvector.h"

int compare_strings(const void* a, const void* b)
{
	return strcmp(*(const char**)a, *(const char**)b);
}


int compare_strings_1(const void* a, const void* b)
{
	return strncmp(*(const char**)a, *(const char**)b, 1);
}

int compare_strings_2(const void* a, const void* b)
{
	//printf("%s\t%s\n", *(const char**)a, *(const char**)b);
	return strncmp(*(const char**)a, *(const char**)b, 2);
}

int compare_strings_3(const void* a, const void* b)
{
	return strncmp(*(const char**)a, *(const char**)b, 3);
}

int compare_strings_4(const void* a, const void* b)
{
	return strncmp(*(const char**)a, *(const char**)b, 4);
}



int (*compare_str_funcs[])(const void*, const void*) =
{
	compare_strings_1, compare_strings_2, compare_strings_3, compare_strings_4
};




#define CLEAR_SCREEN "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" \
                     "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" \
                     "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"


int is_good_word(char* word)
{
	int seen_lower = 0;
	for (char* c=word; *c; ++c) {
		if (!isalpha(*c))
			return 0;
		if (islower(*c))
			seen_lower = 1;
		*c = tolower(*c);
	}
	if (!seen_lower) //it's an acronym
		return 0;

	return 1;

}


void* mybsearch(const void *key, const void *buf, size_t num, size_t size, int (*compare)(const void *, const void *))
{
	size_t min = 0, max = num-1;
	size_t cursor;

	while (min <= max) {
		cursor = min + ((max - min) / 2);
		int ret = compare(&key, (const char*)buf+cursor*size);
		if (!ret) {
			return (char*)buf + cursor*size;
		} else if (ret < 0) {
			max = cursor - 1;  //overflow possibilities here and below
		} else {
			min = cursor + 1;
		}
	}
	return NULL;
}

void find_match_range(vector_str* wordlist, int n_chars, char* prefix, int n, int* first, int* last)
{
	int initial = n;
	while (n >= 0) {
		if (compare_str_funcs[n_chars-1](&prefix, &wordlist->a[n])) {
			break;
		}
		--n;
	}
	*first = ++n;
	n = initial;
	while (n < wordlist->size) {
		if (compare_str_funcs[n_chars-1](&prefix, &wordlist->a[n])) {
			break;
		}
		++n;
	}
	*last = --n;

	return;
}	

#endif
