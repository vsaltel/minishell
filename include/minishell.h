/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaltel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:43:02 by vsaltel           #+#    #+#             */
/*   Updated: 2019/03/18 12:29:18 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "lexer.h"
# include "builtin.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>

int						g_pid;
int						g_wait_quote;

int						minishell(t_shell *shell);
int						parser(t_shell *shell);
int						fill_lexer(char *s, t_shell *shell);
void					free_lexer(t_lexer *lexer);
void					free_tab(char **tab);
char					*str_pathfile(const char *s1, const char *s2);
int						test_access(char *path);
int						execute(t_shell *shell, int argc, char **argv);
char					**copy_env(char **env, int add_variable);
void					tilde_exception(t_token *token, char **env);
void					dollar_exceptions(char **text, char **env, int lastret);
char					**create_variable(int argc, char **argv, char ***env);
char					*get_env_variable(char *cmp, int lenght, char **env);
int						is_directory(char *path, char *display);
char					**create_env_variable(char *name, char *value,
		char **env);
char					**delete_env_variable(char *name, char **env);
int						error_exec(int no, char *prog, char *display, int ret);
char					*get_string_path(int *ret, char **argv, char **env);
t_token					*create_token(const char *text, size_t text_size,
							t_token_type type);
char					*sstrncpy(char *dst, const char *src, size_t len);
char					*sstrchr(const char *s, int c);
char					*ft_strfjoin(char const *s1, char const *s2,
		char const *f);
char					*ft_strfdup(const char *s1, const char *f);
void					display_env(char **env, int *ret);
int						is_dir(int *ret, char *str, char *display);

#endif
