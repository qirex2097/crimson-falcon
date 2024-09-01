/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kahori <kahori@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:48:20 by kahori            #+#    #+#             */
/*   Updated: 2024/07/24 22:05:25 by kahori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// environ変数の宣言
extern char **environ;

int main() {
    char **env = environ;

    while (*env) {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}
