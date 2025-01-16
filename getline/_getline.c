#include "_getline.h"

/**
 * reset - resets all statics vars and frees everything
 * @buffer: the buffer variable to free
 * @bytes_in_buffer: static variable to reset to 0
 * @buffer_index: static variable to reset to 0
 * @line: the line variable to free
 * Return: always NULL
 */
void *reset(char buffer[], ssize_t *bytes_in_buffer,
		   ssize_t *buffer_index, char *line)
{
	memset(buffer, 0, READ_SIZE);
	*bytes_in_buffer = 0;
	*buffer_index = 0;
	free(line);
	line = NULL;
	return (NULL);
}

/**
 * _getline - returns a line from the given file descriptor
 * @fd: file descriptor to read from
 * Return: a null-terminated string that does not include the newline character
 * or NULL if there are no more lines to return or if there's an error
 */
char *_getline(const int fd)
{
	static char buffer[READ_SIZE];
	static ssize_t bytes_in_buffer;
	static ssize_t buffer_index;
	char *line = NULL;
	size_t line_size = 0;

	if (fd < 0)
		return (reset(buffer, &bytes_in_buffer, &buffer_index, line));
	while (1)
	{
		if (buffer_index >= bytes_in_buffer)
		{ /* refill the buffer and reset index */
			bytes_in_buffer = read(fd, buffer, READ_SIZE);
			buffer_index = 0;
			if (bytes_in_buffer <= 0) /* on EOF or error... */
				return (line); /* return what's been read so far */
		} /* add chars from the buffer to line until newline, EOF, or error */
		while (buffer_index < bytes_in_buffer)
		{
			char c = buffer[buffer_index++];

			if (c == '\n') /* return line once a newline is found */
			{
				if (line == NULL)
				{ /* set line as empty str to avoid indicating EOF */
					line = malloc(1);
					if (line == NULL)
						return (NULL); /* indicate error if malloc fails */
					line[0] = '\0';
				}
				return (line);
			} /* reallocate line to fit one more char (plus null-terminator) */
			line = realloc(line, line_size + 2);
			if (line == NULL) /* if realloc failed... */
				return (NULL); /* return null to indicate error */
			/* add this character to the line and null-terminate it */
			line[line_size++] = c;
			line[line_size] = '\0';
		}
	}
}
