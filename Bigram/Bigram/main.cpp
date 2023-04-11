﻿#include <iostream>
#include <fstream>
#include <string>
#include <regex>


int main()
{
	setlocale(0, "rus");
	std::regex r("[а-яА-Я0-9]+");
	std::smatch m;

	std::string s = "Привет, 10 друзья! Сегодня я готовлю невероятно вкусную и сочную курицу в духовке. Это блюдо всегда будет на вашем столе и обязательно порадует всех ваших гостей. Куриный рулет в фольге - это отличный вариант для праздничного стола, а также для будничного ужина. У каждой хозяйки есть свой фирменный рецепт приготовления куриного рулета в фольге, но есть и общие правила.";

	std::regex_search(s, m, r);

	while (std::regex_search(s, m, r)) 
	{
		
		std::cout << m[0] << std::endl;
		s = m.suffix().str();
	}
}
