/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 19:51:08 by mclerico          #+#    #+#             */
/*   Updated: 2022/04/06 13:56:33 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <readline/readline.h>

t_prog	g_env;

void	ft_rm_here_doc(t_ast **tree)
{
	t_ast	*curr;

	if ((*tree)->type == T_PIPE_NODE)
	{
		ft_rm_here_doc(&((*tree)->left));
		ft_rm_here_doc(&((*tree)->right));
	}
	else
	{
		curr = (*tree)->right->left;
		while (curr)
		{
			if (curr->type == T_DOUBLE_IN_NODE && access(curr->data, F_OK) == 0)
			{
				unlink(curr->data);
				free(curr->data);
			}
			curr = curr->left;
		}
	}
}

int	ft_procaux(int *l_pid, t_ast **tree)
{
	int	pid;
	int	status;

	waitpid(*l_pid, &status, 0);
	pid = waitpid(-1, NULL, 0);
	while (pid != -1)
		pid = waitpid(-1, NULL, 0);
	ft_rm_here_doc(tree);
	free(l_pid);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		return (WTERMSIG(status) + 128);
	}
	return (status);
}

int	ft_process(t_ast **tree)
{
	int	*l_pid;

	l_pid = ft_calloc(1, sizeof(int));
	if (ft_process_here_doc(tree))
	{
		ft_rm_here_doc(tree);
		free(l_pid);
		return (130);
	}
	ft_exec_tree(*tree, 0, l_pid, NULL);
	if (*l_pid != 0)
		return (ft_procaux(l_pid, tree));
	ft_rm_here_doc(tree);
	free(l_pid);
	return (0);
}

void	ft_status(t_pstatus *status)
{
	status->data = readline("$ ");
	if (status->data == NULL)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	if (status->data)
		add_history(status->data);
	status->curr = 0;
	status->error = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_list		**tokens;
	t_ast		**tree;
	t_pstatus	status;

	ft_cloneenv(envp);
	if (argc > 1 || argv[1])
		return (1);
	status.l_error = g_env.l_cod;
	while (1)
	{
		my_signal();
		tree = NULL;
		ft_status(&status);
		tokens = ft_get_tokens(&status);
		if (tokens && *tokens)
			tree = ft_generate_ast(tokens);
		if (tree)
			g_env.l_cod = ft_process(tree);
		free(status.data);
		ft_free_all(tree, tokens);
	}
	return (0);
}
