/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:28:51 by kahori            #+#    #+#             */
/*   Updated: 2024/08/11 09:39:30 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stdio.h>

int builtin_pwd(char **argv)
{
    char buff[PATH_MAX];
    
    getcwd(buff, PATH_MAX);
    printf("%s\n", buff);
    return(0);
}

int main()
{
    builtin_pwd(NULL);
    return(0);
}