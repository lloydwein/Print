#include "main.h"

/**
 * print_width - prints width to output buffer
 * @buffer: pointer to the buffer_t struct
 * @num_print: the number of characters printed so far
 * @conv_flags: the flags to modify the conversion
 * @field_wid: the width of the conversion
 * Return: the number of characters printed
 */
unsigned int print_width(buffer_t *buffer, unsigned int num_print,
		unsigned char conv_flags, int field_wid)
{
	unsigned int chars = 0;
	char width = ' ';

	if ((conv_flags & NEG_FLAG) == 0)
	{
		for (field_wid -= num_print; field_wid > 0; field_wid--)
			chars += _memcpy(buffer, &width, 1);
	}

	return (chars);
}

/**
 * print_string_width - prints the width of a string
 * @buffer: pointer to a buffer_t struct
 * @num_print: number of characters already printed
 * @conv_flags: conversion flags
 * @field_wid: field width
 * @precision: precision
 * @string_size: size of string
 *
 * Return: number of characters printed
 */
unsigned int print_string_width(buffer_t *buffer, unsigned int num_print,
		unsigned char conv_flags, int field_wid,
		int precision, int string_size)
{
	unsigned int chars = 0;
	char width = ' ';

	if (NEG_FLAG == 0)
	{
		field_wid -= (precision == -1) ? string_size : precision;
		for (; field_wid > 0; field_wid--)
			chars += _memcpy(buffer, &width, 1);
	}

	return (chars);
}

/**
 * print_neg_width - Adds padding to the left of the printed string if
 * necessary.
 * @buffer: A pointer to the buffer_t struct.
 * @num_print: The number of characters printed so far.
 * @conv_flags: Conversion flags.
 * @field_wid: The minimum field width.
 *
 * Return: The number of characters added as padding.
 */
unsigned int print_neg_width(buffer_t *buffer, unsigned int num_print,
		unsigned char conv_flags, int field_wid)
{
	unsigned int chars = 0;
	char padding_char = ' ';
	int padding_width;

	if (NEG_FLAG == 1)
	{
		padding_width = field_wid - num_print;

		for (; padding_width > 0; padding_width--)
			chars += _memcpy(buffer, &padding_char, 1);
	}

	return (chars);
}
