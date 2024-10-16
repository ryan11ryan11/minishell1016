/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:30:25 by jbober            #+#    #+#             */
/*   Updated: 2024/10/16 14:16:48 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <asm/termbits.h>
# include <sys/types.h>
# include <sys/wait.h> 

extern int	g_lastexit;

// #define BUFFER_SIZE 1024

typedef struct s_data	t_data;
typedef struct s_exe	t_exe;
typedef struct s_list	t_list;
typedef struct s_node	t_node;

typedef struct s_exe
{
	int		tube[2];
	int		pipehowmuch;
	char	*path;
	char	**paths;
	int		std_fd[2];
	int		endline;
}	t_exe;

typedef struct s_data
{
	char	*currinput;
	char	**currstr;
	char	**cstrl;
	t_list	*currmds;
	t_list	*lstart;
	pid_t	pid;
	char	**env;
	t_exe	exe;
}	t_data;


typedef struct s_list
{
	t_node			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_node
{
	char	**cmd;
	char	*infd;
	char	*outfd;
	int		status;
	int		oper;
}	t_node;

/*
	--- asd ---
*/

// envp

void	ms_cpy_env(t_data *data, char **arg);
void	ms_envp(t_data *data, char **envp);

// freerror

extern void	ms_error(t_data *data, char *str, int brexit);
extern void	ms_free(t_data *data, int modus);

// minishell

void	ms_initialize(t_data *data, char **envp);
void	ms_prompt(t_data *data);
int		ms_read_input(t_data *data);

// signals

void	ms_strc(int sig);
char	*ms_expandlexit(t_data *data);

// ut1ls

char	**ms_split(t_data *data, char *str, char split);
int		*ms_countsplit(t_data *data, char *str, char split);
int		ms_sepcount(char *str, char split);
char	*ms_substr(t_data *data, char *str, int i, int j);
char	*ms_speciasplit(t_data *data, char *str);

// ut2ls

int		ms_strinlst(t_data *data, char *str);
int		ms_strncmp(char	*set, char *str, int len);
int		ms_strcontains(char *str, char *bigstr);
char	*ms_strdup(char *str);
char	*ms_strjoin(char *str1ng, char *str2ng);

// ut3ls

int		ms_strrchr(char *str, char find, int modus);
int		ms_strlen(char *str);
t_list	*ms_lstnew(t_data *data);
void	ms_lstadd_back(t_data *data, t_list **lst);
t_list	*ms_lstlast(t_list *lst);

// ut4ls

char	*ms_substrrev(char *str, int start, int len);
char	*ms_itoa(int n);
int		ms_findexpanse(t_data *data, char *str);
void	ms_ctrlitialize(t_data *data);
void	ms_ctrlfill(t_data *data, int k, char *str);
int		ms_cinset(char c, char *set, int modus);

// ut5ls

extern int	ms_check_qt(char c, int *weakqt, int *strongqt);
extern void	ms_envp(t_data *data, char **envp);

/*
	--- parse ---
*/

// parse

extern void	ms_parse_ctrl(t_data *data);

// parsefk1 + b

extern char	*ms_parsefk1_ctrl(t_data *data);
extern char	*ms_add_32(char *str, int i, int weakqt, int strongqt);

// parsefk2

extern char	*ms_parsefk2_ctrl(t_data *data);

// parsefk3

extern char	*ms_parsefk3_ctrl(t_data *data);

// parsefk4

extern char	*ms_parsefk4_ctrl(t_data *data);

// parsefk5

extern char	*ms_parsefk5_ctrl(t_data *data);

#endif