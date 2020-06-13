#include "header.h"

int my_cmp(char *s1, char *s2)
{
    int i = 0;

    while (s1[i] == s2[i] && s1[i] != '\0')
        i++;
    return (s1[i] - s2[i]);
}

int my_strlen(char *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    return (i);
}

char *my_strcpy(char *dest, char *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    *(dest + i) = '\0';
    return (dest);
}

char *my_strcat(char *dest, char *src)
{
    int i = 0;
    int j = my_strlen(dest);

    while (src[i] != '\0') {
        dest[j] = src[i];
        i = i + 1;
        j = j + 1;
    }
    return (dest);
}

char *my_strdup(char *arr)
{
    int size = my_strlen(arr) + 1;
    char *str = malloc(sizeof(char)* size);

    if (str == NULL)
        return (NULL);
    my_strcpy(str, arr);
    free(arr);
    return (str);
}