#include "_getline.h"

/**
 * _getline - returns a line from the given file descriptor
 * @fd: file descriptor to read from
 * return: a null-terminated string that does not include the newline character
 * or NULL if there are no more lines to return or if there's an error
 */
char *_getline(const int fd)
{
	static char buffer[READ_SIZE];
	static ssize_t bytes_in_buffer = 0;
	static ssize_t buffer_index = 0;
	char *line = NULL;
	size_t line_size = 0;

	if (fd <0)
	{
		return (NULL);
	}

	while (1)
	{
		if (buffer_index >= bytes_in_buffer)
		{
			/* refill the buffer and reset index */
			bytes_in_buffer = read(fd, buffer, READ_SIZE);
			buffer_index = 0;

			/* on EOF or error, return what's been read so far */
			if (bytes_in_buffer <= 0)
			{
				return (line);
			}
		}

		/* add chars from the buffer to line until newline, EOF, or error */
		while (buffer_index < bytes_in_buffer)
		{
			char c = buffer[buffer_index++];
			/* return line once a newline is found */
			if (c == '\n')
			{
				/* if line is empty, it hasn't been allocated yet. */
				/* but since the 1st char is \n, we shouldn't return null */
				/* because that would indicate that it reached EOF. */
				if (line == NULL)
				{
					/* set line as empty str to avoid indicating EOF */
					line = malloc(1);
					if (line == NULL)
					{
						/* indicate error if malloc fails */
						return (NULL);
					}
					line[0] = '\0';
				}
				return (line);
			}

			/* reallocate line to fit one more char (plus null-terminator) */
			line = realloc(line, line_size + 2);
			/* if realloc failed, return null to indicate error */
			if (line == NULL)
			{
				return (NULL);
			}

			/* add this character to the line and null-terminate it */
			line[line_size++] = c;
			line[line_size] = '\0';
		}
	}
}
