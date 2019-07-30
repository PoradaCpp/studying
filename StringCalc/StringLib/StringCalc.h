#pragma once

#include <string>
#include <vector>

class StringCalc
{
public:
	int add(std::string sNumbers);

//private:
	static constexpr const char* DELIMS = "<>,./ \n\t\r\'\"";                // Default delimetres for parsing
	std::vector<std::string> m_sDelimsVc;                                    // Custom delimetres for parsing

	void setDelims(const std::string &SourceStr, size_t& nPos);
	std::string getSubstrWithoutDelims(const std::string& SourceStr, const char* Delims, size_t& nBegPos);
	std::string getSubstrWithoutDelims(const std::string& SourceStr, size_t& nBegPos);
};

