#ifndef MINISHELL_H
# define MINISHELL_H

#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>

// parser
char	**ft_get_tokens(char *line);

#endif
