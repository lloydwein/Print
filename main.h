#ifndef MAIN_H
#define MAIN_H

/* Headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>

/* Flag Modifier Macros */
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_FLAG (flags & 1)
#define SPACE_FLAG ((flags >> 1) & 1)
#define HASH_FLAG ((flags >> 2) & 1)
#define ZERO_FLAG ((flags >> 3) & 1)
#define NEG_FLAG ((flags >> 4) & 1)

/* Length Modifier Macros */
#define SHORT 1
#define LONG 2

/**
 * struct buffer_s - A new type defining a buffer struct.
 * @buffer: A pointer to a character array.
 * @start: A pointer to the start of buffer.
 * @len: The length of the string stored in buffer.
 */
typedef struct buffer_s
{
	char *buffer;
	char *start;
	unsigned int len;
} buffer_t;

/**
 * struct converter_s - A new type defining a converter struct.
 * @specifier: A character representing a conversion specifier.
 * @func: A pointer to a conversion function corresponding to specifier.
 */
typedef struct converter_s
{
	unsigned char specifier;
	unsigned int (*func)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);
} converter_t;

/**
 * struct flag_s - A new type defining a flags struct.
 * @flag: A character representing a flag.
 * @value: The integer value of the flag.
 */
typedef struct flag_s
{
	unsigned char flag;
	unsigned char value;
} flag_t;

/* Convert Base Function */
unsigned int convert_ubase(buffer_t *output, unsigned long int num, char *base,
		unsigned char flags, int wid, int prec);
unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int wid, int prec);

/* Format Specifier Functions */
unsigned int print_width(buffer_t *buffer, unsigned int num_print,
		unsigned char conv_flags, int field_wid);
unsigned int print_string_width(buffer_t *buffer, unsigned int num_print,
		unsigned char conv_flags, int field_wid,
		int precision, int string_size);
unsigned int print_neg_width(buffer_t *buffer, unsigned int num_print,
		unsigned char conv_flags, int field_wid);

/* Hexadecimal conversion Functions */
unsigned int convert_x(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length);
unsigned int convert_X(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length);

/* Manager Functions */
unsigned char handle_flags(const char *flag_str, char *flag_index);
unsigned char handle_length(const char *modifier_str, char *modifier_index);
int handle_width(va_list args, const char *modifier_str, char *modifier_index);
int handle_precision(va_list args, const char *modifier_str,
		char *modifier_index);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char flags, int width, int precision,
		unsigned char length);

/* Memory Utilities Functions */
unsigned int _memcpy(buffer_t *dest, const char *source, unsigned int num_byte);
buffer_t *init_buffer(void);
void free_buffer(buffer_t *dest);

/* printf Functions */
void cleanup(va_list args, buffer_t *buffer);
int run_printf(const char *format, va_list args, buffer_t *buffer);
int _printf(const char *format, ...);

/* other conversions functions */
unsigned int convert_c(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length);
unsigned int convert_percent(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length);
unsigned int convert_p(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length);

/* Parse Integer Functions */
unsigned int convert_di(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length);
unsigned int convert_b(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length);
unsigned int convert_o(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length);
unsigned int convert_u(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length);

/* string Manipulation Function */
unsigned int convert_s(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width, int precision,
		int length);
unsigned int convert_S(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length);
unsigned int convert_r(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length);
unsigned int convert_r(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,

#endif		int precision, unsigned char length);
