#include "mini_shell.h"

long long ft_atoll(const char *str) // para proteger supongo
{
    int         i;
    int         sign;
    long long   res;

    i = 0;
    res = 0;
    sign = 1;
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + str[i] - 48;
        i++;
    }
    return (res * sign);
}