#include "shell.h"

/**
 * input_buf - to buffer comm chain
 * @info: par structure
 * @buffer: buffer of address
 * @len: len var location
 *
 * Return: read bytes
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t g = 0;
	size_t len_p = 0;

	if (!*len) /* fill if nothing in the buffer */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		g = getline(buf, &len_p, stdin);
#else
		g = _getline(info, buf, &len_p);
#endif
		if (g > 0)
		{
			if ((*buf)[g - 1] == '\n')
			{
				(*buf)[g - 1] = '\0'; /* to remove trailing newline */
				g--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is a command chain? */
			{
				*len = g;
				info->cmd_buf = buf;
			}
		}
	}
	return (g);
}

/**
 * get_input - brings a line without the newline
 * @info: a parameter struct
 *
 * Return: read bytes
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t l, k, len;
	ssize_t g = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	g = input_buf(info, &buf, &len);
	if (g == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		k = l; /* init new iterator to current buf position */
		p = buf + l; /* get pointer for return */

		check_chain(info, buf, &k, l, len);
		while (k < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &k))
				break;
			k++;
		}

		l = k + 1; /* increment past nulled ';'' */
		if (l >= len) /* reached end of buffer? */
		{
			l = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (g); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t g = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (g >= 0)
		*i = g;
	return (g);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t l, len;
	size_t h;
	ssize_t g = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (l == len)
		l = len = 0;

	g = read_buf(info, buf, &len);
	if (g == -1 || (g == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	h = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + l, h - l);
	else
		_strncpy(new_p, buf + l, h - l + 1);

	s += h - l;
	l = h;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: it is signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
