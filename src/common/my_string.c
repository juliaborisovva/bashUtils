#include "my_string.h"

#include <stdarg.h>
#include <stdlib.h>

char* my_strchr(const char* str, int ch) {
  int i = 0;
  while (str[i]) {
    if (str[i] == ch) break;
    i++;
  }
  char* ptr;
  if (ch == str[i])
    ptr = (char*)str + i;
  else
    ptr = my_NULL;
  return ptr;
}

my_size_t my_strlen(const char* str) {
  my_size_t len = 0;
  if (str != my_NULL) {
    for (; str[len]; len++) {
    }
  }
  return len;
}

char* my_strtok(char* str, const char* delim) {
  static char* buf = my_NULL;
  if (str == my_NULL) {
    if (buf != my_NULL) {
      buf++;
      str = buf;
    }
  }
  buf = my_NULL;
  if (str != my_NULL) {
    for (int i = 0; delim[i] != '\0'; i++) {
      char* find = my_strchr(str, delim[i]);
      if (find != my_NULL) {
        if (my_strlen(find) == my_strlen(str)) {
          str++;
          i = -1;
          buf = my_NULL;
          continue;
        }
        if ((buf == my_NULL) || (my_strlen(find) > my_strlen(buf))) {
          buf = find;
        }
      }
    }
    if (buf != my_NULL) *buf = '\0';
    if (*str == '\0') str = my_NULL;
  }
  return str;
}

char* my_strncpy(char* dest, const char* src, my_size_t n) {
  my_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) dest[i] = src[i];
  for (; i < n; i++) dest[i] = '\0';
  return dest;
}

char* my_strcat(char* dest, const char* src) {
  int len1 = my_strlen(dest), len2 = my_strlen(src);
  for (int i = len1, j = 0; i < len1 + len2; i++, j++) dest[i] = src[j];
  dest[len1 + len2] = '\0';
  return dest;
}

char* my_strrchr(char* str, int ch) {
  int i = 0, n = 0;
  while (str[i]) {
    if (str[i] == ch) n = i;
    i++;
  }
  char* ptr;
  if (ch != '\0') {
    if (ch == str[n])
      ptr = (char*)(str + n);
    else
      ptr = my_NULL;
  } else {
    ptr = (char*)(str + i);
  }
  return ptr;
}

char* my_strstr(const char* haystack, const char* needle) {
  int len2 = my_strlen(needle);
  char* ptr;
  if (len2 == 0) {
    ptr = (char*)haystack;
  } else {
    int i = 0, check = 0;
    while (haystack[i]) {
      if (haystack[i] == needle[0]) {
        if (len2 == 1) {
          check = 1;
          break;
        }
        int j = 0, i1 = i;
        while (needle[j]) {
          if (haystack[i1] != needle[j]) break;

          if (j + 1 == len2) check = 1;
          i1++;
          j++;
        }
      }
      if (check == 1) break;
      i++;
    }
    if (check == 1)
      ptr = (char*)haystack + i;
    else
      ptr = my_NULL;
  }
  return ptr;
}

char* my_strpbrk(const char* str1, const char* str2) {
  int i = 0, check = 0;
  while (str1[i]) {
    int j = 0;
    while (str2[j]) {
      if (str1[i] == str2[j]) {
        check = 1;
        break;
      }
      j++;
    }
    if (check == 1) break;
    i++;
  }
  char* ptr;
  if (check == 1)
    ptr = (char*)str1 + i;
  else
    ptr = my_NULL;
  return ptr;
}

my_size_t my_strspn(const char* str1, const char* str2) {
  int i = 0, len = 0;

  while (str1[i]) {
    int j = 0, check = 0;
    while (str2[j]) {
      if (str1[i] == str2[j]) {
        len++;
        check = 1;
        break;
      } else {
        check = 0;
      }
      j++;
    }
    if (check == 0) break;
    i++;
  }
  return len;
}

my_size_t my_strcspn(const char* str1, const char* str2) {
  int i = 0;

  while (str1[i]) {
    int j = 0, check = 0;
    while (str2[j]) {
      if (str1[i] == str2[j]) {
        check = 1;
        break;
      }
      j++;
    }
    if (check == 1) break;
    i++;
  }
  return i;
}

void* my_memchr(const void* str, int c, my_size_t n) {
  my_size_t i = 0, check = 0;
  char* p = (char*)str;
  while (i < n) {
    if (p[i] == c) {
      check = 1;
      break;
    }
    i++;
  }
  if (check)
    p = (char*)p + i;
  else
    p = my_NULL;
  return p;
}

void* my_memcpy(void* dest, const void* src, my_size_t n) {
  if (dest != my_NULL && src != my_NULL) {
    char* n1 = (char*)src;
    char* n2 = (char*)dest;
    for (my_size_t i = 0; i < n; i++) n2[i] = n1[i];
  }
  return dest;
}

char* my_strerror(int errnum) {
  static char msg[50];
  my_memset(msg, '\0', 50);
#if defined(__linux__)

  const char lin[150][50] = {
      "Success",
      "Operation not permitted",
      "No such file or directory",
      "No such process",
      "Interrupted system call",
      "Input/output error",
      "No such device or address",
      "Argument list too long",
      "Exec format error",
      "Bad file descriptor",
      "No child processes",
      "Resource temporarily unavailable",
      "Cannot allocate memory",
      "Permission denied",
      "Bad address",
      "Block device required",
      "Device or resource busy",
      "File exists",
      "Invalid cross-device link",
      "No such device",
      "Not a directory",
      "Is a directory",
      "Invalid argument",
      "Too many open files in system",
      "Too many open files",
      "Inappropriate ioctl for device",
      "Text file busy",
      "File too large",
      "No space left on device",
      "Illegal seek",
      "Read-only file system",
      "Too many links",
      "Broken pipe",
      "Numerical argument out of domain",
      "Numerical result out of range",
      "Resource deadlock avoided",
      "File name too long",
      "No locks available",
      "Function not implemented",
      "Directory not empty",
      "Too many levels of symbolic links",
      "Unknown error 41",
      "No message of desired type",
      "Identifier removed",
      "Channel number out of range",
      "Level 2 not synchronized",
      "Level 3 halted",
      "Level 3 reset",
      "Link number out of range",
      "Protocol driver not attached",
      "No CSI structure available",
      "Level 2 halted",
      "Invalid exchange",
      "Invalid request descriptor",
      "Exchange full",
      "No anode",
      "Invalid request code",
      "Invalid slot",
      "Unknown error 58",
      "Bad font file format",
      "Device not a stream",
      "No data available",
      "Timer expired",
      "Out of streams resources",
      "Machine is not on the network",
      "Package not installed",
      "Object is remote",
      "Link has been severed",
      "Advertise error",
      "Srmount error",
      "Communication error on send",
      "Protocol error",
      "Multihop attempted",
      "RFS specific error",
      "Bad message",
      "Value too large for defined data type",
      "Name not unique on network",
      "File descriptor in bad state",
      "Remote address changed",
      "Can not access a needed shared library",
      "Accessing a corrupted shared library",
      ".lib section in a.out corrupted",
      "Attempting to link in too many shared libraries",
      "Cannot exec a shared library directly",
      "Invalid or incomplete multibyte or wide character",
      "Interrupted system call should be restarted",
      "Streams pipe error",
      "Too many users",
      "Socket operation on non-socket",
      "Destination address required",
      "Message too long",
      "Protocol wrong type for socket",
      "Protocol not available",
      "Protocol not supported",
      "Socket type not supported",
      "Operation not supported",
      "Protocol family not supported",
      "Address family not supported by protocol",
      "Address already in use",
      "Cannot assign requested address",
      "Network is down",
      "Network is unreachable",
      "Network dropped connection on reset",
      "Software caused connection abort",
      "Connection reset by peer",
      "No buffer space available",
      "Transport endpoint is already connected",
      "Transport endpoint is not connected",
      "Cannot send after transport endpoint shutdown",
      "Too many references: cannot splice",
      "Connection timed out",
      "Connection refused",
      "Host is down",
      "No route to host",
      "Operation already in progress",
      "Operation now in progress",
      "Stale file handle",
      "Structure needs cleaning",
      "Not a XENIX named type file",
      "No XENIX semaphores available",
      "Is a named type file",
      "Remote I/O error",
      "Disk quota exceeded",
      "No medium found",
      "Wrong medium type",
      "Operation canceled",
      "Required key not available",
      "Key has expired",
      "Key has been revoked",
      "Key was rejected by service",
      "Owner died",
      "State not recoverable",
      "Operation not possible due to RF-kill",
      "Memory page has hardware error"};

  char* answer;
  char s[20];
  char u[40] = "Unknown error ";
  int egor = errnum;
  if (egor < 0) {
    egor *= (-1);
    u[14] = '-';
  }
  for (int i = 0; i < 20; i++) s[i] = '\0';
  for (int i = 0; egor; i++) {
    for (int j = 19; j > 0; j--) s[j] = s[j - 1];
    s[0] = egor % 10 + 48;
    egor /= 10;
  }
  if (errnum >= 0 && errnum < 134)
    my_memmove(msg, (char*)lin[errnum], my_strlen((char*)lin[errnum]) + 1);
  else
    my_memmove(msg, my_strcat(u, s), my_strlen(u) + my_strlen(s) + 1);
  answer = msg;
#elif defined(__APPLE__) || defined(__MACH__)
  const char Mac[150][50] = {"Undefined error: 0",
                             "Operation not permitted",
                             "No such file or directory",
                             "No such process",
                             "Interrupted system call",
                             "Input/output error",
                             "Device not configured",
                             "Argument list too long",
                             "Exec format error",
                             "Bad file descriptor",
                             "No child processes",
                             "Resource deadlock avoided",
                             "Cannot allocate memory",
                             "Permission denied",
                             "Bad address",
                             "Block device required",
                             "Resource busy",
                             "File exists",
                             "Cross-device link",
                             "Operation not supported by device",
                             "Not a directory",
                             "Is a directory",
                             "Invalid argument",
                             "Too many open files in system",
                             "Too many open files",
                             "Inappropriate ioctl for device",
                             "Text file busy",
                             "File too large",
                             "No space left on device",
                             "Illegal seek",
                             "Read-only file system",
                             "Too many links",
                             "Broken pipe",
                             "Numerical argument out of domain",
                             "Result too large",
                             "Resource temporarily unavailable",
                             "Operation now in progress",
                             "Operation already in progress",
                             "Socket operation on non-socket",
                             "Destination address required",
                             "Message too long",
                             "Protocol wrong type for socket",
                             "Protocol not available",
                             "Protocol not supported",
                             "Socket type not supported",
                             "Operation not supported",
                             "Protocol family not supported",
                             "Address family not supported by protocol family",
                             "Address already in use",
                             "Can't assign requested address",
                             "Network is down",
                             "Network is unreachable",
                             "Network dropped connection on reset",
                             "Software caused connection abort",
                             "Connection reset by peer",
                             "No buffer space available",
                             "Socket is already connected",
                             "Socket is not connected",
                             "Can't send after socket shutdown",
                             "Too many references: can't splice",
                             "Operation timed out",
                             "Connection refused",
                             "Too many levels of symbolic links",
                             "File name too long",
                             "Host is down",
                             "No route to host",
                             "Directory not empty",
                             "Too many processes",
                             "Too many users",
                             "Disc quota exceeded",
                             "Stale NFS file handle",
                             "Too many levels of remote in path",
                             "RPC struct is bad",
                             "RPC version wrong",
                             "RPC prog. not avail",
                             "Program version wrong",
                             "Bad procedure for program",
                             "No locks available",
                             "Function not implemented",
                             "Inappropriate file type or format",
                             "Authentication error",
                             "Need authenticator",
                             "Device power is off",
                             "Device error",
                             "Value too large to be stored in data type",
                             "Bad executable (or shared library)",
                             "Bad CPU type in executable",
                             "Shared library version mismatch",
                             "Malformed Mach-o file",
                             "Operation canceled",
                             "Identifier removed",
                             "No message of desired type",
                             "Illegal byte sequence",
                             "Attribute not found",
                             "Bad message",
                             "EMULTIHOP (Reserved)",
                             "No message available on STREAM",
                             "ENOLINK (Reserved)",
                             "No STREAM resources",
                             "Not a STREAM",
                             "Protocol error",
                             "STREAM ioctl timeout",
                             "Operation not supported on socket",
                             "Policy not found",
                             "State not recoverable",
                             "Previous owner died",
                             "Interface output queue is full"};

  char* answer;
  char s[20];
  char u[40] = "Unknown error: ";
  int egor = errnum;
  if (egor < 0) {
    egor *= (-1);
    u[15] = '-';
  }
  for (int i = 0; i < 20; i++) s[i] = '\0';
  for (int i = 0; egor; i++) {
    for (int j = 19; j > 0; j--) s[j] = s[j - 1];
    s[0] = egor % 10 + 48;
    egor /= 10;
  }

  if (errnum >= 0 && errnum < 107)
    my_memmove(msg, (char*)Mac[errnum], my_strlen((char*)Mac[errnum]) + 1);
  else
    my_memmove(msg, my_strcat(u, s), my_strlen(u) + my_strlen(s) + 1);
  answer = msg;
#endif
  return answer;
}

void* my_memmove(void* dest, const void* src, my_size_t n) {
  if (dest != my_NULL && src != my_NULL) {
    char* dest_s = (char*)dest;
    char* src_s = (char*)src;
    if (dest_s > src_s && (src_s + n) > dest_s) {
      dest_s += n - 1;
      src_s += n - 1;
      while (n--) *dest_s-- = *src_s--;
    } else {
      while (n--) *dest_s++ = *src_s++;
    }
  }
  return dest;
}

int my_memcmp(const void* str1, const void* str2, my_size_t n) {
  const unsigned char *temp1, *temp2;
  int res = 0;
  for (temp1 = str1, temp2 = str2; 0 < n; ++temp1, ++temp2, n--)
    if ((res = *temp1 - *temp2) != 0) break;
  return res;
}

void* my_memset(void* str, int c, my_size_t n) {
  char* p = (char*)str;
  for (my_size_t i = 0; i < n; i++) p[i] = c;
  return str;
}

char* my_strncat(char* dest, const char* src, my_size_t n) {
  int len1 = my_strlen(dest);
  for (my_size_t i = len1; i < len1 + n; i++, src++) dest[i] = *src;
  dest[len1 + n] = '\0';
  return dest;
}

int my_strcmp(const char* str1, const char* str2) {
  while (*str1 && *str2 && *str1 == *str2) str1++, str2++;
  return *str1 - *str2;
}

int my_strncmp(const char* str1, const char* str2, my_size_t n) {
  int out = 0;
  my_size_t i = 0;
  while (*str2 && *str1 && i < n && (str1[i] == str2[i])) i++;
  if (i < n && n > 0) out = str1[i] - str2[i];
  return out;
}

char* my_strcpy(char* dest, const char* src) {
  int i = 0;
  while (*(src + i) != '\0') {
    *(dest + i) = *(src + i);
    i++;
  }
  *(dest + i) = '\0';
  return dest;
}

typedef struct {
  int flag_minus;
  int flag_plus;
  int flag_space;
  int width;
  int precision_number;
  int length_h;
  int length_l;
  int specifier;
} parsing;

void width_s_or_c(char* str, int len_string, int* len, parsing pars) {
  int prec = 0;
  if (pars.width != 0 && !pars.flag_minus) {
    if (!prec) prec = len_string;

    for (int w = pars.width - prec; w > 0; w--) str[(*len)++] = ' ';
  }
}

void precision(char* str, int i, int* len, parsing pars) {
  for (int w = pars.precision_number - i; w > 0; w--, (*len)++) str[*len] = '0';
}

void width_minus(char* str, int i, int* len, parsing pars) {
  int main_width = 0;
  if (pars.precision_number > i)
    main_width = pars.precision_number;
  else
    main_width = i;

  if (pars.flag_minus) {
    for (int w = pars.width - main_width; w > 0; w--) str[(*len)++] = ' ';
  }
}

void width_minus_s(char* str, int i, int* len, parsing pars) {
  int main_width = i;
  if (pars.flag_minus) {
    for (int w = pars.width - main_width; w > 0; w--) str[(*len)++] = ' ';
  }
}

void width_minus_d(char* str, int i, int* len, parsing pars, int d) {
  int main_widht = 0;
  int check = 0;
  if (d < 0 || pars.flag_plus == 1 || pars.flag_space == 1) check = 1;
  if (pars.precision_number > i)
    main_widht = pars.precision_number + check;
  else
    main_widht = i + check;
  if (pars.flag_minus) {
    for (int w = pars.width - main_widht; w > 0; w--) str[(*len)++] = ' ';
  }
}

void write_str(int i, char* r, char* str, int* len) {
  for (int j = i - 1; j >= 0; j--) str[(*len)++] = r[j];
}

void width_d(char* str, long d, int* len, parsing pars) {
  int check = 0;
  if (d < 0 || pars.flag_plus == 1 || pars.flag_space == 1) check = 1;
  int i = 0;
  if (d == 0 && pars.precision_number != 0) {
    i++;
  }
  while (d != 0) {
    i++;
    d /= 10;
  }
  int main_widht = 0;
  if (pars.precision_number > i)
    main_widht = pars.precision_number;
  else
    main_widht = i;

  for (int w = pars.width - (main_widht + check); w > 0; w--)
    str[(*len)++] = ' ';
}

void width_f(char* str, int f, int* len, parsing pars, int sign) {
  int check = 0;
  int d = f;  // f == 0

  if (sign == -1 || pars.flag_plus == 1 || pars.flag_space == 1) check = 1;
  int i = 0;
  while (d != 0) {
    i++;
    d /= 10;
  }
  if (i == 0) i++;
  int main_widht = 0;

  if (pars.precision_number == -1)
    main_widht += 7 + i;
  else if (pars.precision_number == 0)
    main_widht += i;
  else
    main_widht += pars.precision_number + 1 + i;
  for (int w = pars.width - (main_widht + check); w > 0; w--)
    str[(*len)++] = ' ';
}

void width_u(char* str, unsigned long d, int* len, parsing pars) {
  int i = 0;
  if (d == 0 && pars.precision_number != 0) {
    i++;
  }
  while (d != 0) {
    i++;
    d /= 10;
  }
  int main_widht = 0;
  if (pars.precision_number > i)
    main_widht = pars.precision_number;
  else
    main_widht = i;
  for (int w = pars.width - main_widht; w > 0; w--) str[(*len)++] = ' ';
}

int len_width(const char* format, int* i) {
  int len = 0;
  while (format[*i] >= '0' && format[*i] <= '9')
    len = len * 10 + format[(*i)++] - 48;
  return len;
}

void String_to_char(char* str, char* string, int* len, parsing pars) {
  int prec = 0;

  if (pars.precision_number >= 0) {  // точность от 0 и больше
    if (my_strlen(string) >= (my_size_t)pars.precision_number)
      prec = pars.precision_number;
    else
      prec = my_strlen(string);
    width_s_or_c(str, prec, len, pars);
    str[*len] = '\0';
    my_strncat(str, string, pars.precision_number);
  } else if (pars.precision_number == -1) {  // без точности и точность 0
    prec = my_strlen(string);
    width_s_or_c(str, prec, len, pars);
    str[*len] = '\0';
    my_strcat(str, string);
  }
  *len = my_strlen(str);
  width_minus_s(str, prec, len, pars);
}

void Symbol_to_char(char* str, int string, int* len, parsing pars) {
  width_s_or_c(str, 1, len, pars);
  str[(*len)++] = string;
  width_minus(str, 1, len, pars);
}

void translate_int_to_char(long d, char* r, int* i) {
  if (d == 0) r[(*i)++] = '0';
  while (d != 0) {
    r[(*i)++] = d % 10 + 48;
    d /= 10;
  }
}

void translate_unsigned_long_int_to_char(unsigned long int d, char* r, int* i,
                                         int precision_var) {
  if (d == 0) {
    while (*i != precision_var) {
      r[(*i)++] = '0';
    }
  }
  while (d != 0) {
    r[(*i)++] = d % 10 + 48;
    d /= 10;
  }
}

void Unsigned_int_to_char(char* str, unsigned long d, int* len, parsing pars) {
  if (pars.length_h == 1)
    d = (unsigned short)d;
  else if (pars.length_l == 0)
    d = (unsigned int)d;
  if (pars.width != 0 && !pars.flag_minus) width_u(str, d, len, pars);
  char r[1000];
  int i = 0;
  translate_unsigned_long_int_to_char(d, r, &i, 1);
  r[i] = '\0';
  if (pars.precision_number >= 0) precision(str, i, len, pars);
  if (d == 0 && pars.precision_number == 0) {
    i--;
  } else {
    write_str(i, r, str, len);
  }
  width_minus(str, i, len, pars);
}

void Int_to_char(char* str, long d, int* len, parsing pars) {
  int sign = 1;
  if (pars.length_h == 1)
    d = (short)d;
  else if (pars.length_l == 0)
    d = (int)d;
  if (pars.width != 0 && !pars.flag_minus) width_d(str, d, len, pars);
  if (d < 0) {
    d *= -1;
    sign = -1;
    str[(*len)++] = '-';
  } else if (pars.flag_plus == 1) {
    str[(*len)++] = '+';
  } else if (pars.flag_space == 1) {
    str[(*len)++] = ' ';
  }

  char r[1000];
  int i = 0;

  translate_int_to_char(d, r, &i);
  r[i] = '\0';
  if (pars.precision_number >= 0) precision(str, i, len, pars);

  if (d == 0 && pars.precision_number == 0) {
    i--;
  } else {
    write_str(i, r, str, len);
  }
  width_minus_d(str, i, len, pars, sign);
}

void float_to_char(char* str, double f, int* len, parsing pars) {
  char r[1000];
  int len_float = 0;  // полная длина
  int len_num = 0;    // частичная длина

  int sign = 1;
  if (f < 0) {
    f *= -1;
    sign = -1;
  }

  int integ_part = (int)f;  // целая часть

  double d = f - integ_part;  // дробная часть
  long int d1;

  int precision_var = pars.precision_number;  // число точности
  // если точности нет, то 6 знаков после запятой
  if (pars.precision_number == -1) precision_var = 6;

  if (precision_var == 0) {  // округление до целого
    if (d > 0.5)             // обычное округление
      integ_part++;
    else if (d == 0.5 && integ_part % 2 == 1)  // бухгалтерское
      integ_part++;
  }

  if (precision_var != 0) {
    for (int i = 0; i < precision_var; i++)  // умножаем на точность
      d *= 10;
    d1 = d;
    if (d - d1 >= 0.5) d1 += 1;

    int count = 0;  // смотрим количество цифр в дробной части
    long int d2 = d1;
    while (d2 != 0) {
      count++;
      d2 /= 10;
    }
    if (count > precision_var) {  // если больше precision_var,
      integ_part++;               // то целое увеличиваем
      d1 %= 10;  // дробное добиваем до нужных значений
    }
  }

  if (pars.width != 0 && !pars.flag_minus)  // отступ слева
    width_f(str, integ_part, len, pars, sign);
  if (sign == -1) {
    str[(*len)++] = '-';  // расстановка знаков
    len_float++;
  } else if (pars.flag_plus == 1) {
    str[(*len)++] = '+';  // расстановка знаков
    len_float++;
  } else if (pars.flag_space == 1) {
    str[(*len)++] = ' ';  // расстановка знаков
    len_float++;
  }
  translate_int_to_char(integ_part, r, &len_num);  // записываем целое
  write_str(len_num, r, str, len);
  len_float += len_num;
  len_num = 0;

  if (precision_var != 0) {
    str[(*len)++] = '.';
    len_float++;

    translate_unsigned_long_int_to_char(
        d1, r, &len_num, precision_var);  // перевод дробной части в чары
    // выставления нулей в случае 0.0032
    int bound = len_num;
    while (bound != precision_var && bound < precision_var) {
      r[len_num++] = '0';
      bound++;
    }
    len_float += len_num;

    write_str(len_num, r, str, len);
  }

  width_minus(str, len_float, len, pars);
}

int my_sprintf(char* str, const char* format, ...) {
  parsing pars;
  int len = 0;
  va_list factor;
  va_start(factor, format);
  int i = 0;
  while (format[i] != '\0') {
    if (format[i] != '%') {
      str[len] = format[i];
      len++;
      i++;
      continue;
    }
    pars.flag_minus = 0;
    pars.flag_plus = 0;
    pars.flag_space = 0;
    pars.specifier = 0;
    pars.precision_number = -1;
    pars.length_h = 0;
    pars.length_l = 0;
    pars.width = 0;

    i++;
    while (pars.specifier == 0) {
      switch (format[i]) {
        case '-':
          pars.flag_minus = 1;
          i++;
          break;
        case '+':
          pars.flag_plus = 1;
          i++;
          break;
        case ' ':
          pars.flag_space = 1;
          i++;
          break;
        case 'd':
          pars.specifier = 1;
          Int_to_char(str, va_arg(factor, long), &len, pars);
          i++;
          break;
        case 'i':
          pars.specifier = 1;
          Int_to_char(str, va_arg(factor, long), &len, pars);
          i++;
          break;
        case 'u':
          pars.specifier = 1;
          Unsigned_int_to_char(str, va_arg(factor, unsigned long), &len, pars);
          i++;
          break;
        case 's':
          pars.specifier = 1;
          String_to_char(str, va_arg(factor, char*), &len, pars);
          i++;
          break;
        case 'c':
          pars.specifier = 1;
          Symbol_to_char(str, va_arg(factor, int), &len, pars);
          i++;
          break;
        case 'f':
          pars.specifier = 1;
          float_to_char(str, va_arg(factor, double), &len, pars);
          i++;
          break;
        case '.':
          i++;
          pars.precision_number = len_width(format, &i);
          break;
        case '%':
          pars.specifier = 1;
          str[len] = format[i];
          len++;
          i++;
          break;
        case 'h':
          pars.length_h = 1;
          i++;
          break;
        case 'l':
          pars.length_l = 1;
          i++;
          break;
        default:
          if (format[i] >= '0' && format[i] <= '9') {
            pars.width = len_width(format, &i);
          }
          break;
      }
    }
  }
  va_end(factor);
  str[len] = '\0';
  return len;
}

void* my_to_upper(const char* str) {
  void* p = my_NULL;
  if (str != my_NULL) {
    int len = my_strlen(str);
    char* newstr = (char*)malloc(sizeof(char) * (len + 1));
    if (newstr != my_NULL) {
      for (int i = 0; i < len; i++) {
        if (str[i] >= 97 && str[i] <= 122) {
          newstr[i] = str[i] - 32;
        } else if (str[i] == -48 && str[i + 1] >= -80 && str[i + 1] <= -65) {
          newstr[i] = str[i];
          i++;
          newstr[i] = str[i] - 32;
        } else if (str[i] == -47 && str[i + 1] <= -111) {
          newstr[i] = str[i] - 1;
          i++;
          if (str[i] != -111)
            newstr[i] = str[i] + 32;
          else
            newstr[i] = str[i] - 16;
        } else {
          newstr[i] = str[i];
        }
      }
      newstr[len] = '\0';
      p = newstr;
    }
  }
  return p;
}

void* my_to_lower(const char* str) {
  void* p = my_NULL;
  if (str != my_NULL) {
    int len = my_strlen(str);
    char* newstr = (char*)malloc(sizeof(char) * (len + 1));
    if (newstr != my_NULL) {
      for (int i = 0; i < len; i++) {
        if (str[i] >= 65 && str[i] <= 90) {
          newstr[i] = str[i] + 32;
        } else if (str[i] == -48 && str[i + 1] >= -112 && str[i + 1] <= -97) {
          newstr[i] = str[i];
          i++;
          newstr[i] = str[i] + 32;
        } else if (str[i] == -48 && str[i + 1] >= -127 && str[i + 1] <= -81) {
          newstr[i] = str[i] + 1;
          i++;
          if (str[i] != -127)
            newstr[i] = str[i] - 32;
          else
            newstr[i] = str[i] + 16;
        } else {
          newstr[i] = str[i];
        }
      }
      newstr[len] = '\0';
      p = newstr;
    }
  }
  return p;
}

void* my_insert(const char* src, const char* str, my_size_t start_index) {
  void* p = my_NULL;
  if (src != my_NULL && str != my_NULL) {
    my_size_t len1 = my_strlen(src);
    my_size_t len2 = my_strlen(str);
    if (len1 >= start_index) {
      char* newstr = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
      if (newstr != my_NULL) {
        for (my_size_t i = 0; i < start_index; i++) newstr[i] = src[i];
        for (my_size_t i = start_index; i < start_index + len2; i++)
          newstr[i] = str[i - start_index];
        for (my_size_t i = start_index + len2; i < len1 + len2; i++)
          newstr[i] = src[i - len2];
        newstr[len1 + len2] = '\0';
        p = newstr;
      }
    }
  }
  return p;
}

void* my_trim(const char* src, const char* trim_chars) {
  void* p = my_NULL;
  if (src != my_NULL && trim_chars != my_NULL) {
    int len1 = my_strlen(src);
    int len2 = my_strlen(trim_chars);
    int left = 0, right = 0, count = 0, choice = 0;
    for (int i = 0; i < len1; i++) {
      int check = 0;
      for (int j = 0; j < len2; j++) {
        if (src[i] == trim_chars[j]) {
          count++;
          check++;
        }
      }
      if (check == 0) {
        if (choice == 0 || i == 0) {
          left = count;
          choice++;
        }
        count = 0;
      }
    }
    right = count;
    char* newstr = (char*)malloc(sizeof(char) * (len1 - left - right + 1));
    if (newstr != my_NULL) {
      for (int i = left, j = 0; i < len1 - right; i++, j++) newstr[j] = src[i];
      newstr[len1 - left - right] = '\0';
      p = newstr;
    }
  }
  return p;
}
