/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 16:14:18 by dsanchez          #+#    #+#             */
/*   Updated: 2022/02/02 21:37:30 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <readline/readline.h>

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
void	ft_cloneenv(void)
{
	int	i;

	i = 1;
	while(environ[i] != NULL)
		ft_lstadd_back(&g_env, ft_lstnew(environ[i++]));
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

void	ft_free_token(void *t)
{
	t_token	*token;

	token = (t_token *)t;
	free(token->data);
	free(token);
}

/*void	my_prompt(int n)
{
	n = 0;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void my_signal(void)
{

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, my_prompt);
}*/
void	ft_use_builtins(t_ast *tree)
{
	if (ft_strncmp(tree->data, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(tree->data, "echo", 4) == 0)
		ft_echo(tree);
	else if (ft_strncmp(tree->data, "exit", 4) == 0)
		ft_exit();
	else if (ft_strncmp(tree->data, "env", 3) == 0)
		ft_env();
	else if (ft_strncmp(tree->data, "unset", 5) == 0)
		ft_unset(tree);
}

int	main(void)
{
	t_list		**tokens;
	t_ast		**tree;
	int			state;
	t_pstatus	status;

	state = 1;
	ft_cloneenv();
	while (state)
	{
		//my_signal();
		status.data = readline(CYAN"$"NC" ");
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
		ft_print_tokens_list(tokens);
		if (tokens)
			tree = ft_generate_ast(tokens);
		if (tree)
			ft_exec_tree(*tree, 0);
		ft_lstclear(tokens, ft_free_token);
		free(tokens);
	}
	return (0);
}
