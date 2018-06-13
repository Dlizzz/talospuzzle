// Header file for Class Params
#pragma once
#include <string>
#include <memory>

#include <boost/program_options.hpp>

class Params: 
    private boost::program_options::options_description, 
    private boost::program_options::variables_map {
public:
	Params() noexcept;
	bool readParams(int ac, char* av[]);
	void printHelp() const;
    int getPieceCount(const std::string& piece) const;
    int getRows() const;
    int getColumns() const;
    bool getVerbose() const;
    bool getFirst() const;
    bool getStats() const;
  
private:
    unsigned int _lineLength;
    unsigned int _descriptionLength;
};

inline int Params::getRows() const { return (*this)["rows"].as<int>(); };
inline int Params::getColumns() const { return (*this)["columns"].as<int>(); };
inline bool Params::getVerbose() const { return (*this)["verbose"].as<bool>(); };
inline bool Params::getFirst() const { return (*this)["first"].as<bool>(); };
inline bool Params::getStats() const { return (*this)["stats"].as<bool>(); };
