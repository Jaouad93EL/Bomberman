#include "header.h"

int is_letter(char c)
{
    if (c != '\n' && c != '\0')
        return (1);
    return (0);
}

int count_line(char *str)
{
    int i = 0;
    int length = 0;
    char last;

    while (str[i]) {
        if (str[i] == '\n' && last != '\n')
            length++;
        last = str[i];
        i++;
    }
    if (str[i] == '\0')
        length++;
    return (length);
}

int count_letter(char *str, int i)
{
    int letter = 0;

    while (str[i] != '\n' && str[i] != '\0') {
        if (is_letter(str[i]))
            letter++;
        i++;
    }
    return (letter);
}

char **fill_tab(char **tab, char *str)
{
    int i = -1;
    int j = -1;
    int k = 0;
    int length = 0;

    while (++i < count_line(str)) {
        j = -1;
        while (str[k] == '\n')
            k++;
        length = count_letter(str, k);
        tab[i] = malloc(sizeof(char) * length + 1);
        if (tab[i] == NULL)
            return (NULL);
        while (++j < length) {
            if (is_letter(str[k]))
                tab[i][j] = str[k++];
        }
        tab[i][j] = '\0';
    }
    return (tab);
}

char **my_str_to_wordtab(char *str)
{
    char **tab;

    tab = malloc(sizeof(*tab) * count_line(str) + 1);
    if (tab == NULL)
        return (NULL);
    return (fill_tab(tab, str));
}