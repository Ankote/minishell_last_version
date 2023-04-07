/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 08:53:18 by aankote           #+#    #+#             */
/*   Updated: 2023/04/06 23:00:03 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define EMPTY 0
# define CMD 1
# define INFILE 3
# define OUTFILE 4
# define APPOUT 5
# define ARG 6
# define LIMITER 7
# define TRUNC 8
# define APPEND 9
# define INPUT 10
# define PIPE 11
# define HERDOC 12

/********exit status*******/

# define ERROR 1
# define ERROR2 2
# define SUCCESS 0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127
# define SYNTAX_ERROR 258

/************************/

typedef struct s_token
{
	int				type;
	char			*val;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_g_dependences
{
	int				exit_status;
	char			**files;
	char			**env;
	char			**env_copy;
	char			*pwd;
	char			*str;
	char			**content;
	char			**staar;
}					t_dependences;

typedef struct s_list
{
	char			*cmd;
	char			**args;
	int				infile;
	int				outfile;
	int				append_in;
	int				perror;
	struct s_list	*next;
}					t_list;
/*******UTILS********/
char				*ft_charjoin(char *s, char c);
char				*ft_trim(char *arg);
char				*ft_join_free(char *s1, char *s2);
void				print_error(char *str1, char *str2);
void				ft_lstadd_back(t_token **lst, t_token *new);
int					ft_listsize(t_list *list);
void				add_list(t_list **lst, t_list *new);
int					quotes(char *line, int index);
char				**ft_realloc(char **p, char *str);
int					ft_strcmp(const char *s1, const char *s2);
void				free_double(char **p);
t_token				*ft_lstnew(int type, char *val);
/***************************lexer****************************/
void				get_cmd(t_list **list, t_token **token);
int					type_arg(t_token *token);
void				get_infile(t_list *list, char *val);
void				get_outfile(t_list *list, char *val, int type);
void				ft_add_str(char *ln, t_token **token, int *i);
void				ft_add_opr(char *ln, t_token **token, int *i);
int					ignore_sep(char c, char *line, int index);
int					is_std(char *val, t_list *list);
void				get_token(char *line, t_token **token);
int					tokens(char *line, t_token **token);
int					check_spac(char *str);
void				get_characters(char *str, int *i, char **p);
void				add_command(t_list **list, t_list **new);
void				list_init(t_list *list);
void				get_token(char *line, t_token **token);
/******************* expanding an herdoc**********************/
char				*ft_get_arg(char **env, char *str, int *i);
char				*ft_expand(char **env, char *str);
void				get_val(int *check, int *i, char *str, char **p);
char				*get_value(char **env, char *var);
char				*here_doc(char *limiter, char **env);
void				unlink_files(char **files);
char				*ft_herd_exp(char **env, char *str);
void				handle_signal(int sg);
int					do_exp_inp(char *limiter);
int					open_her(t_token **token, char **env);
/********************** Builtins ***********************/
void				echo(t_list *list);
int					ft_exit(t_list *data);
void				*ft_cd(t_list *list);
void				ft_env(int inf);
void				ft_unset(t_list *lst);
char				*get_pwd(char *str);
void				ft_export(t_list *list);
/********************** EXECUTION **********************/
char				*ft_search(char *str, char c);
char				*ft_search_1(char *str, char c);
void				ft_exec(t_list *list);
char				*get_arg(void);
void				main_execution(t_list *list);
void				ft_next_check(char *str);
void				ft_next_export(t_list *list, int i, int j);
int					check_if_builtin(t_list *list);
/***************************SYNTAX ERROR**************/
int					is_error_char(char c);
int					pipe_errors(t_token **token);
int					is_opr(int type);
int					check_oper(t_token **token);
int					ft_error_char(char *str);
int					check_command(char *str);
int					check_token_syntax(t_token **token);
int					check_quotes(char *str);
int					check_cmd_syntax(char *str);
int					check_herdoc(t_token **token);
int					is_dir(char *str);
/**********************MAIN UTILS**********************/
void				print_test(char *str, int fd);
void				export(t_list *list);
void				ft_free_token(t_token **list);
void				free_list(t_list *list);
void				ft_ck(t_list **lst);
void				handle_signal1(int s);
void				handle_signal2(int s);
void				ft(int c);
/****************** Replace Line **********************/
extern void			rl_replace_line(const char *str, int c);
/************* Norminette Update ***********/
int					parssing(char *c);
void				update_old_pwd(void);
void				ft_error(char *msg);
void				update_pwd(char *path);
void				next_error(char *header, char *arg, char *msg);
int					ft_check_for_existence(char *str, char c);
void				add_new_var(char *str);
void				add_var_remove_p(char *str);
void				ft_append(int index, char *str);
char				*ft_check_for_equal(char *str);
void				ft_child_process(int pid, t_list *list, int *stdin,
						int *fd);
void				change_value(char *str, int index);
char				**ft_help_env(char **env, int n);
void				helper_export(char *str, int i, int *check, char *suffix);
int					ftsearch(char *haystack, char *needle, size_t len);
void				init_vars(char **env, int ac, char **av);
int					checker(char **env);
/************* Globale struct **************/
int					is_std_out(char *val, t_list *list);
t_dependences		g_dep;
#endif
