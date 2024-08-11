/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:23:25 by kahori            #+#    #+#             */
/*   Updated: 2024/08/11 16:10:40 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libc.h>
#include <stdbool.h>

bool    check_n_option(const char *argv)
{
    size_t i;

    if(strncmp(argv, "-n", 2) != 0)
        return (false);
    
    i = 2;
    while(argv[i] != '\0')
    {
        if(argv[i]!= 'n')
            return (false);
        i++;
    }
    return true;
}

int builtin_echo(char **argv)
{
    size_t i = 1;
    bool    print_newline = true;

    while(argv[i] && check_n_option(argv[i]))
    {
        print_newline = false;
        i++;
    }

    while(argv[i])
    {
        write(STDOUT_FILENO, argv[i], strlen(argv[i]));
        if(argv[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    if(print_newline == true)
        write(1, "\n", 1);
    return(0);
}

int main(int ac, char **av)
{
    if(ac > 0)
        builtin_echo(av);
    return 0;
}