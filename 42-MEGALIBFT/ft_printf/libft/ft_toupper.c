/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kipouliq <kipouliq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:00:52 by lekix             #+#    #+#             */
/*   Updated: 2023/11/14 18:05:34 by kipouliq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	unsigned char	letter;

	letter = c;
	if (letter >= 'a' && letter <= 'z')
		return (letter - 32);
	else
		return (letter);
}
