/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarita <anarita@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:42:53 by miduarte &        #+#    #+#             */
/*   Updated: 2025/09/01 12:49:38 by anarita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_cwd(char *buf, size_t size)
{
    if (getcwd(buf, size) == NULL)
    {
        perror(RED"getcwd"RST);
        exit(EXIT_FAILURE);
    }
    return (buf);
}

void *do_malloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr)
    {
        perror(RED"malloc"RST);
        exit(EXIT_FAILURE);
    }
    return (ptr);
}

void print_banner(void)
{
    printf(
        C
        "┏┳┓╻┏┓╻╻┏━┓╻ ╻┏━╸╻  ╻     ┏━┓╻ ╻┏━╸╻┏ ┏━┓\n"
        "┃┃┃┃┃┗┫┃┗━┓┣━┫┣╸ ┃  ┃     ┗━┓┃ ┃┃  ┣┻┓┗━┓\n"
        "╹ ╹╹╹ ╹╹┗━┛╹ ╹┗━╸┗━╸┗━╸   ┗━┛┗━┛┗━╸╹ ╹┗━┛\n"
        RST);
}