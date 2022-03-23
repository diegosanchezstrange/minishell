/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 16:14:18 by dsanchez          #+#    #+#             */
/*   Updated: 2022/03/23 16:23:35 by dsanchez         ###   ########.fr       */
/*                                                                            */ 
/* ************************************************************************** */

#include <minishell.h>
#include <readline/readline.h>

t_prog	g_env;

void	ft_cloneenv(char **environ)
{
	int	i;

	i = 0;
	g_env.l_cod = 0;
	g_env.env = (t_list **)ft_calloc(sizeof(t_list *), 1);
	while (environ[i] != NULL)
		ft_lstadd_back(g_env.env, ft_lstnew(ft_strdup(environ[i++])));
}

void	ft_print_tokens_list(t_list **tokens)
{
	t_list	**pointer;

	if (!tokens)
		return ;
	pointer = malloc(sizeof(void *));
	if (!pointer)
		return ;
	*pointer = *tokens;
	printf("------------------- TOKENS -------------------\n");
	while (*pointer)
	{
		printf("data: %s , type: %d\n", ((t_token *)((*pointer)->content))->data, ((t_token *)((*pointer)->content))->type);
		*pointer = (*pointer)->next;
	}
	printf("------------------- TOKENS -------------------\n");
	free(pointer);
}

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
			if (curr->type == T_DOUBLE_IN_NODE)
				unlink(curr->data);
			curr = curr->left;
		}
	}
}

int	ft_process(t_ast **tree)
{
	int	status;
	int	*l_pid;
	int pid;

	l_pid = ft_calloc(1, sizeof(int));
	if (ft_process_here_doc(tree))
		return (130);
	ft_exec_tree(*tree, 0, l_pid, NULL);
	if (*l_pid != 0)
	{
		waitpid(*l_pid, &status, 0);
		pid = waitpid(-1, NULL, 0);
		while (pid != -1)
		{
			pid = waitpid(-1, NULL, 0);
		}
		ft_rm_here_doc(tree);
		free(l_pid);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			write(1, "\n", 1);
			return (WTERMSIG(status) + 128);
		}
	}
	ft_rm_here_doc(tree);
	free(l_pid);
	return (0);
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
		status.data = readline("$ ");
		tree = NULL;
		if (status.data == NULL)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		if (status.data)
			add_history(status.data);
		status.curr = 0;
		status.error = 0;
		tokens = ft_get_tokens(&status);
		//ft_print_tokens_list(tokens);
		if (tokens && *tokens)
			tree = ft_generate_ast(tokens);
		if (tree)
			g_env.l_cod = ft_process(tree);
		free(status.data);
		ft_free_all(tree, tokens);
	}
	return (0);
}
