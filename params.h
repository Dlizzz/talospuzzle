// Header file for Class Params
#pragma once
#include <string>
#include <memory>

#pragma warning (push)
#include <boost/program_options.hpp>
#pragma warning (pop)

class Params: 
    private boost::program_options::options_description, 
    private boost::program_options::variables_map {
public:
	Params() noexcept;
	bool readParams(int ac, char* av[]);
	void printHelp() const;
    int getPieceCount(const std::string &piece) const;
  
private:
    unsigned int _lineLength;
    unsigned int _descriptionLength;
};
