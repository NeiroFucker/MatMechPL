#include "../headers/Tokinezer.h"
#include <iostream>


// ([�-�\-]{2,})|([�-�]+)

Tokenizer::Tokenizer(std::string path)
{
	connect = std::ifstream(path);
	word_exp = std::regex("([�-�\-]{3,})");
	sentence_exp = std::regex("[�-�][^\.!?]*[\.!?]");
}

std::vector<Token> Tokenizer::GetTokens()
{
	std::string text = ReadAllFile();
	
	std::smatch sentence_m, word_m;
	std::string sentence_str, last_word;

	std::vector<Token> result = std::vector<Token>();
	while (std::regex_search(text, sentence_m, sentence_exp))
	{
		sentence_str = sentence_m[0];
		while (std::regex_search(sentence_str, word_m, word_exp))
		{
			if (last_word == "") last_word = NormalizeString(word_m[0]);
			else
			{
				std::string next_word = NormalizeString(word_m[0]);
				result.push_back(Token(last_word, next_word)); last_word = next_word;
			}
			sentence_str = word_m.suffix().str();
		}
		last_word = ""; text = sentence_m.suffix().str();
	}
	return result;
}

std::string Tokenizer::ReadAllFile()
{
	std::string text = "";
	std::string temp_str = "";

	while (!connect.eof()) 
	{
		getline(connect, temp_str);
		text += temp_str;
	}
	return text;
}

std::string Tokenizer::NormalizeString(std::string str)
{
	for (int i = 0; i < str.length(); i++)
		if (-64 <= str[i] && str[i] <= -33)
			str.replace(i, 1, 1, str[i] + 32);	
	return str;
}
