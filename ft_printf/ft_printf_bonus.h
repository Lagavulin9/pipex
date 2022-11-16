/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:27:43 by jinholee          #+#    #+#             */
/*   Updated: 2022/08/23 12:55:19 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <sys/types.h>
# include <stdarg.h>

typedef struct s_info
{
	int		ljust;
	int		zfill;
	char	format;
	char	*fill;
	char	*radix;
	char	*pos_sign;
	char	*ret;
	long	width;
	long	precision;
	long	total;
}			t_info;

int		is_digit(char c);
int		is_flag(char c);
int		is_format(char c);
int		is_num_format(char c);
int		null_print(t_info *info);
int		format_write(char *str, size_t *i, va_list ap);
int		ft_printf(const char *str, ...);
long	get_precision(char *str, size_t *i);
void	ft_memcpy(char *dst, char *src, size_t n);
size_t	ft_strlen(const char *str);
size_t	num_in_base_len(unsigned long num, int base_len);
char	*ft_ltoa(long num, t_info *info);
char	*ft_hex_convert(unsigned long num, t_info *info);
char	*ft_strcat(char *dst, char *src);
char	*ft_chrdup(char c);
char	*ft_strdup(char *str);
char	*to_uppercase(char *str);
char	*str_slice(char *result, t_info *info, long len);
char	*precision_fill(t_info *info);
void	init(t_info *info);
void	set_flags(t_info *info, char *str, size_t *i);
void	set_ret(t_info *info, char format, va_list ap);
size_t	get_len(t_info *info);
char	*width_fill(char *result, t_info *info);
char	*join(t_info *info);
char	*ljust(t_info *info);

#endif