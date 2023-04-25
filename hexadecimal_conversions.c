#include "main.h"

/**
 * convert_x - Convert an usigned integer argument to hexadecimal using
 * lowercase and store it in a buffer contained in a struct.
 * @args: A va_list of arguments.
 * @buffer: A pointer to a buffer_t struct.
 * @conv_flags: Conversion flags.
 * @max_width: Maximum width of the output.
 * @precision: Precision of the output.
 * @length: Length modifier.
 *
 * Return: The number of bytes written to the buffer.
 */
unsigned int convert_x(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length)
{
	unsigned long int num;
	unsigned int value = 0;
	char *head = "0x";

	if (length == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (length == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		value += _memcpy(buffer, head, 2);

	if (!(num == 0 && precision == 0))
		value += convert_ubase(buffer, num, "0123456789abcdef",
				conv_flags, max_width, precision);

	value += print_neg_width(buffer, value, conv_flags, max_width);

	return (value);
}

/**
 * convert_X - Convert an usigned integer argument to hexadecimal using
 * uppercase and store it in a buffer contained in a struct.
 * @args: A va_list of arguments.
 * @buffer: A pointer to a buffer_t struct.
 * @conv_flags: Conversion flags.
 * @max_width: Maximum width of the output.
 * @precision: Precision of the output.
 * @length: Length modifier.
 *
 * Return: The number of bytes written to the buffer.
 */
unsigned int convert_X(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length)
{
	unsigned long int num;
	unsigned int value = 0;
	char *head = "0x";

	if (length == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (length == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		value += _memcpy(buffer, head, 2);

	if (!(num == 0 && precision == 0))
		value += convert_ubase(buffer, num, "0123456789ABCDEF",
				conv_flags, max_width, precision);

	value += print_neg_width(buffer, value, conv_flags, max_width);

	return (value);
}
