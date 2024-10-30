#ifndef SRC_COMMON_MY_STRING_H_
#define SRC_COMMON_MY_STRING_H_

typedef long unsigned my_size_t;
#define my_NULL ((void*)0)

char* my_strcat(char* dest, const char* src);

char* my_strrchr(char* str, int ch);

char* my_strstr(const char* haystack, const char* needle);

char* my_strpbrk(const char* str1, const char* str2);

my_size_t my_strspn(const char* str1, const char* str2);

my_size_t my_strcspn(const char* str1, const char* str2);

void* my_memchr(const void* str, int c, my_size_t n);

void* my_memcpy(void* dest, const void* src, my_size_t n);

char* my_strerror(int errnum);

void* my_memmove(void* dest, const void* src, my_size_t n);

int my_memcmp(const void* str1, const void* str2, my_size_t n);

void* my_memset(void* str, int c, my_size_t n);

char* my_strncat(char* dest, const char* src, my_size_t n);

int my_strcmp(const char* str1, const char* str2);

int my_strncmp(const char* str1, const char* str2, my_size_t n);

char* my_strcpy(char* dest, const char* src);

char* my_strchr(const char* str, int ch);

my_size_t my_strlen(const char* str);

char* my_strtok(char* str, const char* delim);

char* my_strncpy(char* dest, const char* src, my_size_t n);

int my_sprintf(char* str, const char* format, ...);

void* my_to_upper(const char* str);

void* my_to_lower(const char* str);

void* my_insert(const char* src, const char* str, my_size_t start_index);

void* my_trim(const char* src, const char* trim_chars);

#endif  // SRC_COMMON_MY_STRING_H_
