#include "CSV.h"
#include <iostream>
#include <string>
#include <algorithm>

namespace paracefas {
	CSV::CSV(std::string source)
		: file_name{ source }
	{
		process();
	}

	CSV::CSV(char const* source) 
		: file_name{ source }
	{
		process();
	}

	CSV::~CSV()
	{
		if(raw_data.is_open()) raw_data.close();
	}

	int CSV::findByValue(std::string value) 
	{
		for(int i = 0; i < data.size(); ++i) 
			if(data[i] == value) 
				return i;
		return -1;
	}

	void CSV::processTitles(std::string titles) 
	{
		std::string title;
		for (int i = 0; i < titles.size(); ++i) {
			if(titles[i] == ',') continue;
				title += titles[i];
			if (titles[i+1] == ',' || titles[i+1] == '\0') {
				data.push_back(title);
				row_size++;
				title.clear();
			}
		}
	}

	void CSV::processValues(std::string line) 
	{
		std::string value;
		for (int i = 0; i < line.size(); ++i) {
			if(line[i] == ',') continue;
				value += line[i];
			if (line[i+1] == ',' || line[i+1] == '\0') {
				data.push_back(value);
				value.clear();
			}
		}
	}

	void CSV::process()
	{
		raw_data.open(file_name);
		if (!raw_data.is_open()) {
			std::cerr << "[Error]: The file is not open\n";
			return;
		}	std::string titles;

		std::getline(raw_data, titles);
		processTitles(titles);
		while(!raw_data.eof()) {
			std::string line;
			std::getline(raw_data, line);
			processValues(line);
			last_line++;
		}
	}

	std::string CSV::Get(std::string column_name, size_t n_row)
	{
		int pos = findByValue(column_name);
		return pos != -1 ? data[pos + (n_row + 1) * row_size] : "[Error]: Invalid column";
	}

	bool CSV::checkInput(std::string input)
	{
		size_t commaCntr = 0;
		for(int i = 0; i < input.size(); ++i)
			if(input[i] == ',') ++commaCntr;
		return commaCntr == row_size - 1;
	}

	void CSV::Post(std::string src)
	{
		if(!checkInput(src)) {
			std::cerr << "[Error]: Invalid input\n";
			return;
		}
		std::ofstream new_file(file_name, std::ios::app);
		new_file << '\n' << src;
		new_file.close();
		processValues(src);
	}
	size_t CSV::GetLineCount()
	{
		return data.size();
	}
} // end namespace