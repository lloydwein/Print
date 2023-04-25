#include "main.h"

/**
 * cleanup - Peforms cleanup operations for _printf.
 * @args: A va_list of arguments provided to _printf.
 * @buffer: A buffer_t struct.
 */
void cleanup(va_list args, buffer_t *buffer)
{
	va_end(args);
	write(1, buffer->start, buffer->len);
	free_buffer(buffer);
}

/**
 * run_printf - reads through the format string for _printf and formats
 * the output according to the given format directives.
 * @format: format string
 * @args: arguments list
 * @buffer: output buffer
 *
 * Return: number of characters printed, or -1 on failure
 */
int run_printf(const char *format, va_list args, buffer_t *buffer)
{
	int ind, wid, prec, chars = 0;
	char temp;
	unsigned char flags, length;
	unsigned int (*f)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);

	for (ind = 0; format[ind]; ind++)
	{
		length = 0;
		if (format[ind] == '%')
		{
			temp = 0;
			flags = handle_flags(format + ind + 1, &temp);
			wid = handle_width(args, format + ind + temp + 1, &temp);
			prec = handle_precision(args, format + ind + temp + 1, &temp);
			length = handle_length(format + ind + temp + 1, &temp);

			f = handle_specifiers(format + ind + temp + 1);
			if (f != NULL)
			{
				ind += temp + 1;
				chars += f(args, buffer, conv_flags, max_width,
						precision, length);
				continue;
			}
			else if (format[ind + temp + 1] == '\0')
			{
				chars = -1;
				break;
			}
		}
		chars += _memcpy(buffer, (format + ind), 1);
		ind += (length != 0) ? 1 : 0;
	}
	cleanup(args, buffer);
	return (chars);
}

/**
 * _printf - Outputs a formatted string.
 * @format: Character string to print - may contain directives.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
	buffer_t *output;
	va_list args;
	int ret;

	if (format == NULL)
		return (-1);
	output = init_buffer();
	if (output == NULL)
		return (-1);

	va_start(args, format);

	ret = run_printf(format, args, output);

	return (ret);
}
