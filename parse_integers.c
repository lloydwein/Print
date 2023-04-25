#include "main.h"

/**
 * convert_di - Convert an argument to a signed integer and store
 * it in a buffer.
 * @args: A va_list of arguments.
 * @buffer: A pointer to a buffer_t struct.
 * @conv_flags: Conversion flags.
 * @max_width: Maximum width of the output.
 * @precision: Precision of the output.
 * @length: Length modifier.
 *
 * Return: The number of bytes written to the buffer.
 */
unsigned int convert_di(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length)
{
	long int d;
	int count = 0, wid;
	char pad, space = ' ', neg = '-', plus = '+';
	unsigned int value = 0;

	if (length == LONG)
		d = va_arg(args, long int);
	else
		d = va_arg(args, int);
	if (length == SHORT)
		d = (short)d;
	if (conv_flags & SPACE_FLAG && d >= 0)
		value += _memcpy(buffer, &space, 1);
	if (d == LONG_MIN)
		count = 19;
	else
	{	long int copy = (d < 0) ? -d : d;

		for (; copy > 0; copy /= 10)
			count++; }
	count += (d == 0) + (d < 0) + (conv_flags & PLUS_FLAG && d >= 0) +
		(conv_flags & SPACE_FLAG && d >= 0);

	if (conv_flags & ZERO_FLAG && conv_flags & PLUS_FLAG && d >= 0)
		value += _memcpy(buffer, &plus, 1);
	if (conv_flags & ZERO_FLAG && d < 0)
		value += _memcpy(buffer, &neg, 1);
	pad = (conv_flags & ZERO_FLAG) ? '0' : ' ';
	wid = max_width - count;
	for (; wid > 0; wid--)
		value += memcpy(buffer, &pad, 1);
	if (!(conv_flags & ZERO_FLAG) && d < 0)
		value += _memcpy(buffer, &neg, 1);
	if (!(conv_flags & ZERO_FLAG) && (conv_flags & PLUS_FLAG && d >= 0))
		value += _memcpy(buffer, &plus, 1);
	if (!(d == 0 && precision == 0))
		value += convert_sbase(buffer, d, "0123456789", conv_flags, 0,
				precision);
	value += print_neg_width(buffer, value, conv_flags, max_width - count);
	return (value);
}

/**
 * convert_b - Convert an usigned integer argument to binary and store
 * it in a buffer.
 * @args: A va_list of arguments.
 * @buffer: A pointer to a buffer_t struct.
 * @conv_flags: Conversion flags.
 * @max_width: Maximum width of the output.
 * @precision: Precision of the output.
 * @length: Length modifier.
 *
 * Return: The number of bytes written to the buffer.
 */
unsigned int convert_b(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length)
{
	unsigned int num;

	num = va_arg(args, unsigned int);
	(void)lenth;

	return (convert_ubase(buffer, num, "01", conv_flags, max_width,
				precision));
}

/**
 * convert_o - Convert an usigned integer argument to octal and store
 * it in a buffer.
 * @args: A va_list of arguments.
 * @buffer: A pointer to a buffer_t struct.
 * @conv_flags: Conversion flags.
 * @max_width: Maximum width of the output.
 * @precision: Precision of the output.
 * @length: Length modifier.
 *
 * Return: The number of bytes written to the buffer.
 */
unsigned int convert_o(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length)
{

	unsigned long int num;
	unsigned int value = 0;
	char zero = '0';

	if (length == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (length == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		value += _memcpy(buffer, &zero, 1);

	if (!(num == 0 && precision == 0))
		value += convert_ubase(buffer, num, "01234567",
				conv_flags, max_width, precision);

	value += print_neg_width(buffer, value, conv_flags, max_width);

	return (value);
}

/**
 * convert_u - Convert an usigned integer argument to decimal and store
 * it in a buffer.
 * @args: A va_list of arguments.
 * @buffer: A pointer to a buffer_t struct.
 * @conv_flags: Conversion flags.
 * @max_width: Maximum width of the output.
 * @precision: Precision of the output.
 * @length: Length modifier.
 *
 * Return: The number of bytes written to the buffer.
 */
unsigned int convert_u(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length)
{
	unsigned long int num;
	unsigned int value = 0;

	if (length == LONG)
		num = va_arg(args, unsigned long int);
	else
		num = va_arg(args, unsigned int);
	if (length == SHORT)
		num = (unsigned short)num;

	if (!(num == 0 && precision == 0))
		value += convert_ubase(buffer, num, "0123456789",
				conv_flags, max_width, precision);

	value += print_neg_width(buffer, value, cov_flags, max_width);

	return (value);
}
