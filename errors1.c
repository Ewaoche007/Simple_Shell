#include "shell.h"

/**
 * _erratoi - to convert  string to an int
 * @s: a string to convert
 * Return: 0 if no numb in string, convert numb otherwise
 *       -1 on error
 */
int _erratoi(char *s)
{
	int l = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (l = 0;  s[l] != '\0'; l++)
	{
		if (s[l] >= '0' && s[l] <= '9')
		{
			result *= 10;
			result += (s[l] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - to print error message
 * @info: a parameter & return info structure
 * @estr: the string that contains a specified error type
 * Return: 0 if no numb in string, converted numb otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - a function that prints a decimal (int) number (base 10)
 * @input: an input
 * @fd: the filedescriptor meant to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int l, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (l = 1000000000; l > 1; l /= 10)
	{
		if (_abs_ / l)
		{
			__putchar('0' + current / l);
			count++;
		}
		current %= l;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, of a clone of itoa
 * @num: numb
 * @base: the base
 * @flags: the argument flag(s)
 *
 * Return: a string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long h = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		h = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[h % base];
		h /= base;
	} while (h != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function that replace first instance of '#' with '\0'
 * @buf: address of a string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int l;

	for (l = 0; buf[l] != '\0'; l++)
		if (buf[l] == '#' && (!l || buf[l - 1] == ' '))
		{
			buf[l] = '\0';
			break;
		}
}
