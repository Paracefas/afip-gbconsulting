#ifndef PAR_CSV_H
#define PAR_CSV_H
#include <fstream>
#include <vector>

namespace paracefas {
	class CSV {
		std::ifstream raw_data;
		size_t row_size = 0;
		size_t last_line = 0;
		std::vector<std::string> data;
		std::string file_name;

		void process();
		int findByValue(std::string);
		void processTitles(std::string);
		void processValues(std::string);
		bool checkInput(std::string);

	public:
		CSV(std::string);
		CSV(char const*);
		~CSV();
		std::string Get(std::string, size_t); /* Name of column, number of row */
		void Post(std::string); /* Data src, number of row */
		size_t GetLineCount();
	};
} // end namespace 

#endif