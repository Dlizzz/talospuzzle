#pragma once

#include <exception>

class HelpParams : public std::exception {
	public:
		const char* what() const noexcept
		{
			return "Help requested from command line.";
		}
};
