/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaslan <alaslan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:13:10 by alaslan           #+#    #+#             */
/*   Updated: 2024/08/15 07:20:04 by alaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(char *src)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*src == ' ' || (*src >= 9 && *src <= 13))
		src++;
	if (*src == '-' || *src == '+' || *src == '\"')
	{
		if (*src++ == '-')
			sign *= -1;
	}
	if (*src == '-' || *src == '+' || *src == '\"')
	{
		if (*src == '-')
			sign *= -1;
		src++;
	}
	while (*src >= '0' && *src <= '9')
	{
		res *= 10;
		res += *src - '0';
		src++;
	}
	return (sign * res);
}
