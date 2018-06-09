// Header file for Class Params
#pragma once
#include <string>
#include <memory>

#pragma warning (push)
#include <boost/program_options.hpp>
#pragma warning (pop)

class Params {
public:
	Params() noexcept;
	bool getParams(int ac, char* av[]);
	void printHelp() const;
    int getPieceCount(const std::string &piece);
  
private:
	std::unique_ptr<boost::program_options::options_description> _options;
    std::unique_ptr<boost::program_options::variables_map> _vm;
    int _lineLenght;
    int _descriptionLength;
};
