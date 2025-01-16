#ifndef ATLAS_SYSTEM_LINUX__GETLINE_H
#define ATLAS_SYSTEM_LINUX__GETLINE_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define READ_SIZE 2048

void *reset(char buffer[], ssize_t *bytes_in_buffer, ssize_t *buffer_index,
			char *line);
char *_getline(const int fd);


#endif /* ATLAS_SYSTEM_LINUX__GETLINE_H */
