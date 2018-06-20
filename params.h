// Header file for Class Params
#pragma once
#include <string>
#include <memory>

#if defined(_WIN32)
#include <codeanalysis\warnings.h>
#include <CppCoreCheck\Warnings.h>
#endif
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#pragma warning ( disable: ALL_CPPCORECHECK_WARNINGS)
#include <boost/program_options.hpp>
#pragma warning( pop )

class Params: 
    private boost::program_options::options_description, 
    private boost::program_options::variables_map {
public:
	Params() noexcept;
	bool readParams(int ac, char* av[]);
	void printHelp(bool printDesc = true) const;
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

inline int Params::getRows() const { return (*this)["rows"].as<int>(); }
inline int Params::getColumns() const { return (*this)["columns"].as<int>(); }
inline bool Params::getVerbose() const { return (*this)["verbose"].as<bool>(); }
inline bool Params::getFirst() const { return (*this)["first"].as<bool>(); }
inline bool Params::getStats() const { return (*this)["stats"].as<bool>(); }
