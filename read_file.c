#include "header.h"

char *my_realloc(char *file, int size)
{
    int i = 0;
    char *str = malloc(sizeof(char) * size);

    if (str == NULL)
        return NULL;
    while (file[i] != '\0') {
        str[i] = file[i];
        i++;
    }
    str[i] = '\0';
    free(file);
    return (str);
}

char *read_file(int fd)
{
    int i = 0;
    char c;
    char *str = malloc(sizeof(*str));
    int readable = read(fd, &c, 1);

    if (fd < 0 || str == NULL)
        return NULL;
    if (readable == 1) {
        while (c != '\0' && readable == 1) {
            str[i++] = c;
            str = my_realloc(str, (i + 1) * sizeof(char *));
            readable = read(fd, &c, 1);
        }
    }
    str[i] = '\0';
    close(fd);
    return (str);
}