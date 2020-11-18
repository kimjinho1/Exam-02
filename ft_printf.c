#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

typedef struct  s_flag
{
    int     width;
    int     prec;
    int     dot;
    int     base;
    char    type;
}               t_flag;

int     ft_putchar(char c) {
    write(1, &c, 1);
    return (1);
}

int     ft_strlen(char* s) {
    int i = 0;

    while (s[i])
        i++;
    return (i);
}

int     ft_nbrlen(int n, int base) {
    int i = 0;

    if (n == 0)
        return (1);
    while (n) {
        n /= base;
        i++;
    }
    return (i);
}

char    ft_strchr(char* s, int c) {
    int i = 0;

    while (s[i]) {
        if (s[i] == c)
            return (s[i]);
        i++;
    }
    return (0);
}

void    init_flag(t_flag* flag) {
    flag->width = 0;
    flag->prec = -1;
    flag->dot = 0;
}

void    parse_flag(char* s, int i, t_flag* flag) {
    if ((s[i] >= '0' && s[i] <= '9') && !flag->dot)
        flag->width = flag->width * 10 + (s[i] - '0');
    else if (s[i] == '.')
    {
        flag->dot = 1;
        flag->prec = 0;
    }
    else if ((s[i] >= '0' && s[i] <= '9') && flag->dot)
        flag->prec = flag->prec * 10 + (s[i] - '0');
}

int     print_str(char* s, t_flag* flag) {
    int ret, i, prec;
    ret = i = 0;

    if (flag->prec < 0)
        prec = ft_strlen(s);
    else
        prec = flag->prec < ft_strlen(s) ? flag->prec : ft_strlen(s);
    while (i < flag->width - prec) {
        ret += ft_putchar(' ');
        i++;
    }
    i = 0;
    while (i < prec)
        ret += ft_putchar(s[i++]);
    return (ret);
}

void	ft_putnbr_base(int num, int base)
{
    char* dec = "0123456789";
    char* hex = "0123456789abcdef";

    if (num >= base)
    {
        ft_putnbr_base(num / base, base);
        ft_putnbr_base(num % base, base);
    }
    else
    {
        if (base == 10)
            write(1, &dec[num], 1);
        else if (base == 16)
            write(1, &hex[num], 1);
    }
}

int     print_nbr(long long n, t_flag* flag) {
    int ret, i, prec, n_len;
    ret = i = 0;
    flag->base = flag->type == 'd' ? 10 : 16;
    n_len = ft_nbrlen(n, flag->base);

    if (flag->prec < 0)
        prec = n_len;
    else
        prec = flag->prec < n_len ? n_len : flag->prec;
    while (i < flag->width - (prec + (n >= 0 ? 0 : 1))) {
        ret += ft_putchar(' ');
        i++;
    }
    i = 0;
    if (n < 0) {
        ret += ft_putchar('-');
        n *= -1;
    }
    if (n == 0 && flag->prec != 0)
        ret += ft_putchar('0');
    i = -1;
    while (++i < prec - n_len)
        ret += ft_putchar('0');
    if (n) {
        ft_putnbr_base(n, flag->base);
        ret += n_len;
    }
    return (ret);
}

int     print_type(t_flag* flag, va_list ap) {
    int ret;

    if (flag->type == 's')
        ret = print_str(va_arg(ap, char*), flag);
    else if (flag->type == 'd')
        ret = print_nbr(va_arg(ap, int), flag);
    else if (flag->type == 'x')
        ret = print_nbr(va_arg(ap, long long), flag);
    return (ret);
}

int     check_format(char* s, va_list ap) {
    int     ret, i;
    t_flag* flag;

    ret = i = 0;
    if (!(flag = malloc(sizeof(t_flag))))
        return (-1);
    while (s[i]) {
        if (s[i] == '%') {
            init_flag(flag);
            while (s[++i] && !ft_strchr("sdx", s[i])) {
                parse_flag(s, i, flag);
            }
            flag->type = s[i++];
            ret += print_type(flag, ap);
        }
        else {
            ret += ft_putchar(s[i++]);
        }
    }
    return (ret);
}

int     ft_printf(const char* s, ...) {
    int     ret;
    va_list ap;

    va_start(ap, s);
    ret = check_format((char*)s, ap);
    va_end(ap);
    return (ret);
}

int main() {
    ft_printf("Hello World!\n\n");

    ft_printf("10.0s |%10.0s1\n", "Hello");
    ft_printf("10.s  |%10.s1\n", "Hello");
    ft_printf("10s   |%10s1\n", "Hello");
    ft_printf("10.4s |%10.4s1\n", "HEllo");
    ft_printf("10.7s |%10.7s1\n", "HEllo");
    ft_printf(".7s   |%.7s1\n", "HEllo");
    ft_printf(".3s   |%.3s1\n\n", "HEllo");

    ft_printf("d    |%d\n", 1234);
    ft_printf("3d   |%3d\n", 1234);
    ft_printf("7d   |%7d\n", 1234);
    ft_printf(".d   |%.d\n", 1234);
    ft_printf(".3d  |%.3d\n", 1234);
    ft_printf(".6d  |%.6d\n", 1234);
    ft_printf(".6d  |%.6d\n", -1234);
    ft_printf("3.3d |%3.3d\n", 1234);
    ft_printf("3.3d |%3.3d\n", -1234);
    ft_printf("6.3d |%6.3d\n", 1234);
    ft_printf("6.3d |%6.3d\n", -1234);
    ft_printf("3.7d |%3.7d\n", 1234);
    ft_printf("3.7d |%3.7d\n", -1234);
    ft_printf("9.7d |%9.7d\n", 1234);
    ft_printf("9.7d |%9.7d\n", -1234);
}