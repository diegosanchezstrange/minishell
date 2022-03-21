/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <mclerico@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:53:40 by mclerico          #+#    #+#             */
/*   Updated: 2022/03/17 19:29:27 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	my_prompt(int n)
{
	if (n == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_env.l_cod = 130;
	}
}

void	sig_here_doc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
}

void	my_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, my_prompt);
}

void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
