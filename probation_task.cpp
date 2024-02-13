#include <iostream>
#include <string>
#include <vector>
#include <fstream>

void swap(std::vector<std::string>& persons, int i, int j) 
{
	std::string tmp = persons[i];
	persons[i] = persons[j];
	persons[j] = tmp;
}

void bubble_sort(std::vector<std::string>& persons)
{
	int size = persons.size();
	while (size > 1) {
		for (int i = 0; i < size - 1; ++i) {
			if (persons[i] > persons[i + 1]) {
				swap(persons[i], persons[i + 1]);
			}
		}
		--size;
	}
}

bool binary_search(const std::vector<std::string>& persons, const std::string target)
{
	int begin = 0;
	int end = persons.size() - 1;
	int mid = 0;
	while (end >= begin) {
		mid = begin + (end - begin) / 2;
		if (persons[mid] == target) {
			std::cout << "Uraa!" << target << "index" << mid <<  std::endl;
			return true;
		}
		if (target < persons[mid]) {
			end = mid - 1;
		}
		else {
			begin = mid + 1;
		}
	}
	return false;
}



/*
std::string remove_quotes(const std::string& word)
{
    std::string result;
    for (char ch : word) {
        if (ch != '\"') {
            result += ch;
        }
    }
    return result;
}
*/

void cleaner(std::vector<std::string>& words)
{
    for (std::string& word : words) {
        char last = word[word.size() - 1];
        if (last == ',' || last == '.') {
            word.pop_back(); //erase()
        }
    }
}

std::string cleaner_2(std::string& word)
{
	std::string s = "";
	for (const char& ch : word) {
		if (ch != '\"' && ch != ',' && ch != '.') {
			s += ch;
		}
	}
	return s;
}

void parsed_word(const std::string& str, std::vector<std::string>& words)
{
	std::string curr_word;
	for (char ch : str) {
		if (ch != ' ') {
			curr_word += ch;
		}
		else if (curr_word.size() != 0) {
			words.push_back(curr_word);
			curr_word = "";
		}
	}
}

void replacement(std::string& str, const std::vector<std::string>& persons) {
    std::vector<std::string> words;
    parsed_word(str, words);
    cleaner(words);

    for (int i = 0; i < words.size(); ++i) {
        for (const std::string& person : persons) {
            if (words[i] == person) {
                words[i] = "CODE";
                break;  
            }
        }
    }

    str.clear();
    for (const std::string& word : words) {
        str += word + " ";
    }
}



int main() {
    std::string str = "In the bustling coffee shop, Sarah greeted her friend Emily with a warm hug. They were joined by Michael, who had just finished his morning jog. After, Sarah and Emily chatted excitedly about their upcoming trip, while Michael listened intently, sipping on his latte. Soon, Jennifer arrived, followed by David and Amanda. The group laughed and exchanged stories, enjoying each other's company. Later that day, Sarah met up with Matthew for lunch at their favorite sandwich spot. They were surprised to see Emma and Kevin already there, enjoying a meal together. After lunch, Sarah ran into Maria at the grocery store, and they exchanged quick hellos before going their separate ways. As the evening approached, Sarah attended a party hosted by Thomas. Priya and Rajesh were there, along with a crowd of familiar faces. Sarah caught up with Jennifer and Michael, who introduced her to their friend, Amanda. The night was filled with laughter and good conversation, as the group shared stories and made memories together.";


    std::vector<std::string> words;
    parsed_word(str, words);
    cleaner(words);

    std::vector<std::string> persons;

  //to print the parsed words
 /*for (int i = 0; i < words.size(); ++i) {
		std::cout << words[i] << std::endl;
	}
  */
	std::string target = "";
	std::cout << "Enter target" << std::endl; 
	std::cin >> target;

	std::cout << binary_search(persons, target);

  //mecatrov sksox barer@
	std::vector<std::string> upper_words;
	for (const std::string& word : words) {
		if (word[0] >= 'A' && word[0] <= 'Z') {
			upper_words.push_back(word);
		}
	}
  //tpum em mecatarov sksox bolor barere
  /*for (const std::string& word : upper_words) {
		std::cout << word << std::endl;
	}
  */

  /*if (words[i][0] <= 'Z' && words[i][0] >= 'A') {
		upper_words.push_back(words[i]);
	}*/
  /*for (int i = 0; i < upper_words.size(); ++i) {
		if (upper_words[i].back() == '.' && upper_words[i].back() == ',')
			upper_words[back].erase();
			std::cout << upper_words[i] << std::endl;
	}*/

    std::ifstream file("database.txt");
    if (!file.is_open()) {
        std::cout << "Error" << std::endl;
    }
    std::string word_from_file;
	std::string clean_word;
    while (file >> word_from_file) {
        clean_word = cleaner_2(word_from_file);
        for (const std::string& word : upper_words) {
            if (clean_word == word) {
                persons.push_back(clean_word);
                break;
            }
        }
    }
    file.close();

    bubble_sort(persons);
	std::cout << binary_search(persons, target) << std::endl;

    for (std::string name : persons) {    
        std::cout << name << std::endl;
    }

    replacement(str, persons);

    std::cout << "Modified str: " << str << std::endl;

    return 0;
}	
