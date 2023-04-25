#include "main.h"

/**
 * convert_c - Convert an argument to an ussigned char store it in a buffer
 * contained in a struct.
 * @args: A va_list of arguments.
 * @buffer: A pointer to a buffer_t struct.
 * @conv_flags: Conversion flags.
 * @max_width: Maximum width of the output.
 * @precision: Precision of the output.
 * @length: Length modifier.
 *
 * Return: The number of bytes written to the buffer.
 */
unsigned int convert_c(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length)
{
	char chars;

	usigned int value = 0;

	(void)precision;
	(void)length;

	chars = va_arg(args, int);

	value += print_width(buffer, value, conv_flags, max_width);
	value += _memcpy(buffer, &chars, 1);
	value += print_neg_width(buffer, value, conv_flags, max_width);

	return (value);
}

/**
 * convert_percent - store a percent sign in a buffer contained in a struct.
 * @args: A va_list of arguments.
 * @buffer: A pointer to a buffer_t struct.
 * @conv_flags: Conversion flags.
 * @max_width: Maximum width of the output.
 * @precision: Precision of the output.
 * @length: Length modifier.
 *
 * Return: The number of bytes written to the buffer.
 */
unsigned int convert_percent(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length)
{
	char percent = '%';
	unsigned int value = 0;

	(void)args;
	(void)precision;
	(void)length;

	value += print_width(buffer, value, conv_flags, max_width);
	value += _memcpy(buffer, &chars, 1);
	value += print_neg_width(buffer, value, conv_flags, max_width);

	return (value);
}

/**
 * convert_p - Convert the address of an argument to hexadecimal
 * and store it in a buffer contained in a struct.
 * @args: A va_list of arguments.
 * @buffer: A pointer to a buffer_t struct.
 * @conv_flags: Conversion flags.
 * @max_width: Maximum width of the output.
 * @precision: Precision of the output.
 * @length: Length modifier.
 *
 * Return: The number of bytes written to the buffer.
 */
unsigned int convert_p(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length)
{
	char *null = "(nil)";
	unsigned long int address;
	unsigned int value = 0;

	(void)length;

	address = va_arg(args, unsigned long int);
	if (address == '\0')
		return (_memcpy(buffer, null, 5));

	conv_flags |= 32;
	value += convert_ubase(buffer, address, "0123456789abcdef",
			conv_flags, max_width, precision);
	value += print_neg_width(buffer, value, conv_flags, max_width);

	return (value);
}
