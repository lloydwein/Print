#include "main.h"

/**
 * convert_s - Converts a string.
 *
 * @args: A va_list containing the string to be converted.
 * @buffer: The buffer to store the converted string.
 * @conv_flags: Flags that modify the behavior of the conversion.
 * @max_width: The maximum width of the converted string.
 * @precision: The maximum number of characters to be printed.
 * @length: The length modifier that specifies the size of the argument.
 *
 * Return: The number of characters stored in the buffer.
 */
unsigned int convert_s(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width, int precision,
		int length)
{
	char *string, *null = "(null)";
	int size;
	unsigned int value = 0;

	(void)conv_flags;
	(void)length;

	string = va_arg(args, char *);

	if (string == NULL)
	{
		return (_memcpy(buffer, null, 6));
	}

	size = _strlen(string);
	value += print_string_width(buffer, conv_flags, max_width, precision,
			size);

	precision = (precision == -1) ? size : precision;

	while (*string != '\0' && precision > 0)
	{
		value += _memcpy(buffer, string, 1);
		precision--;
		string++;
	}
	value += print_neg_width(buffer, value, conv_flags, max_width);

	return (value);
}

/**
 * convert_S - Converts a string to a printable string with special characters
 *             represented by hex codes
 * @args: A va_list of arguments containing the string to be converted
 * @buffer: A buffer_t struct containing a buffer to write the converted string
 * @conv_flags: Flags that modify the behavior of the conversion
 * @max_width: The maximum width of the converted string
 * @precision: The maximum number of characters to be printed for the
 * converted string
 * @length: The length modifier that specifies the size of the argument
 *
 * Return: The number of characters written to buffer
 */
unsigned int convert_S(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length)
{
	char *string, *null = "(null)",  *hex = "\\x", zero = '0';
	int size, index;
	unsigned int value = 0;

	(void)length;

	string = va_arg(args, char *);
	if (string == NULL)
		return (_memcpy(buffer, null, 6));

	for (size = 0; string[size]; size++)
		;

	value += print_string_width(buffer, conv_flags, max_width, precision,
			size);

	precision = (precision == -1) ? size : precision;
	for (index = 0; *(string + index) != '\0' && index < precision;
			index++)
	{
		if (*(string + index) < 32 || *(string + index) >= 127)
		{
			value += _memcpy(buffer, hex, 2);
			if (*(string + index) < 16)
				value += _memcpy(buffer, &zero, 1);
			value += convert_ubase(buffer, *(string + index),
					"0123456789ABCDEF", conv_flags, 0, 0);
			continue;
		}
		value += _memcpy(buffer, (string + index), 1);
	}
	value += print_neg_width(buffer, value, conv_flags, max_width);

	return (value);
}


/**
 * convert_r - Reverses a string and stores it in a buffer contained in a
 * struct
 * @args: A va_list containing the variadic arguments
 * @buffer: A pointer to the buffer_t struct containing the buffer
 * @conv_flags: Conversion flags
 * @max_width: The maximum field width
 * @precision: The precision
 * @length: The length modifier
 *
 * Return: The number of characters stored in the buffer
 */
unsigned int convert_r(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length)
{
	char *string, *null = "(null)";
	int size, end, index;
	unsigned int value = 0;

	(void)conv_flgas;
	(void)max_width;
	(void)precision;
	(void)length;

	string = va_arg(args, char *);
	if (string == NULL)
		return (_memcpy(buffer, null, 6));

	size = 0;
	while (*(string + size))
		size++;

	value += print_string_width(buffer, conv_flags, max_width,
			precision, size);

	end = size - 1;
	precision = (precision == -1) ? size : precision;
	for (index = 0; end >= 0 && index < precision; index++)
	{
		value += _memcpy(buffer, (string + end), 1);
		end--;
	}

	value += print_neg_width(buffer, value, conv_flags, max_width);

	size = value;
	for (index = 0; index < size / 2; index++)
	{
		char temp = buffer->start[index];

		buffer->start[index] = buffer->start[size - index - 1];
		buffer->start[size - index - 1] = temp;
	}

	return (value);
}

/**
 * convert_R - Converts a string to ROT13 and stores it to a buffer
 * @args: List of arguments
 * @buffer: Pointer to a buffer_t struct
 * @conv_flags: Conversion flags
 * @max_width: Maximum width
 * @precision: Precision
 * @length: Length modifier
 *
 * Return: The number of characters written to the buffer
 */
unsigned int convert_r(va_list args, buffer_t *buffer,
		unsigned char conv_flags, int max_width,
		int precision, unsigned char length)
{
	char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *string = va_arg(args, char *);
	char *null = "(null)";
	int i, j, size = 0;
	unsigned int value = 0;

	(void)conv_flags;
	(void)length;

	if (string == NULL)
		return (_memcpy(buffer, null, 6));

	for (size = 0; string[size]; size++)
		;

	value += print_string_width(buffer, conv_flags, max_width,
			precision, size);

	precision = (precision == -1) ? size : precision;
	for (i = 0; string[i] != '\0' && i < precision; i++)
	{
		for (j = 0; j < 52; j++)
		{
			if (string[i] == alpha[j])
			{
				value += _memcpy(buffer, rot13 + j, 1);
				break;
			}
		}
		if (j == 52)
			value += _memcpy(buffer, string + i, 1);
	}

	value += print_neg_width(buffer, value, conv_flags, max_width);

	return (value);
}
