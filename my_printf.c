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
	int i, wid, prec, ret = 0;
	char tmp;
	unsigned char flags, len;
	unsigned int (*f)(va_list, buffer_t *,
			unsigned char conv_flags, int max_width,
			int precision, unsigned char arg_len);

	for (i = 0; *(format + i); i++)
	{
		len = 0;
		if (*(format + i) == '%')
		{
			tmp = 0;
			flags = handle_flags(format + i + 1, &tmp);
			wid = handle_width(args, format + i + tmp + 1, &tmp);
			prec = handle_precision(args, format + i + tmp + 1,
					&tmp);
			len = handle_length(format + i + tmp + 1, &tmp);

			f = handle_specifiers(format + i + tmp + 1);
			if (f != NULL)
			{
				i += tmp + 1;
				ret += f(args, output, flags, wid, prec, len);
				continue;
			}
			else if (*(format + i + tmp + 1) == '\0')
			{
				ret = -1;
				break;
			}
		}
		ret += _memcpy(output, (format + i), 1);
		i += (len != 0) ? 1 : 0;
	}
	cleanup(args, output);
	return (ret);
}
