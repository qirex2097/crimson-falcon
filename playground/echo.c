/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:23:25 by kahori            #+#    #+#             */
/*   Updated: 2024/08/11 15:21:16 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libc.h>

int builtin_echo(char **argv)
{
    size_t i = 0;

    while(argv[i])
    {
        i = 1;
        write(STDOUT_FILENO, argv[i], strlen(argv[i]));
        if(argv[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    write(1, "\n", 1);
    return(0);
}

int main(int ac, char **av)
{
    if(ac > 1)
        return(builtin_echo(av));
    return (0);
}