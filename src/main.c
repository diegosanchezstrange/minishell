/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 16:14:18 by dsanchez          #+#    #+#             */
/*   Updated: 2022/03/01 21:19:13 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <readline/readline.h>

t_list	*g_env;

char	*ft_get_path(char *arg)
{
	char	*env;
	char	**path;
	char	*command;

	if (access(arg, F_OK) == 0)
		return (arg);
	env = getenv("PATH");
	if (!env)
		return ("");
	path = ft_split(env, ':');
	while (*path)
	{
		command = ft_strjoin(*path, ft_strjoin("/", arg));
		if (access(command, F_OK) == 0)
			return (command);
		path++;
	}
	return ("");
}

void	ft_cloneenv(char **environ)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
		ft_lstadd_back(&g_env, ft_lstnew(ft_strdup(environ[i++])));
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

void	my_prompt(int n)
{
	if (n == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
void my_signal(void)
{

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, my_prompt);
}


void	ft_process(t_ast **tree)
{
	int	pid;
	int	*l_pid;

	l_pid = ft_calloc(1, sizeof(int));
	pid = fork();
	if (pid == 0)
	{
		ft_exec_tree(*tree, 0, l_pid);
		printf("L_PID : %d\n", *l_pid);
		waitpid(*l_pid, NULL, 0);
		free(l_pid);
		exit(0);
	}
	else 
	{
		waitpid(pid, NULL, 0);
		free(l_pid);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_list		**tokens;
	t_ast		**tree;
	t_pstatus	status;

	ft_cloneenv(envp);
	if (argc > 1 || argv[1])
		return (1);
	while (1)
	{
		my_signal();
		status.data = readline("$ ");
		tree = NULL;
		if (status.data == NULL)
		{
			write(1, "exit", 5);
			exit(0);
		}
		if (status.data)
			add_history(status.data);
		status.curr = 0;
		status.error = 0;
		tokens = ft_get_tokens(&status);
		//ft_print_tokens_list(tokens);
		if (tokens)
			tree = ft_generate_ast(tokens);
		if (tree)
		{
			ft_process(tree);
			ft_free_tree(tree);
		}
		free(tree);
		ft_lstclear(tokens, ft_free_token);
		free(tokens);
	}
	return (0);
}
