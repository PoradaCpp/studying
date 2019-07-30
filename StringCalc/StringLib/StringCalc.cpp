#include "stdafx.h"
#include "StringCalc.h"

#include <stdexcept>

int StringCalc::add(std::string sNumbers)
{
	size_t nPos(0);

	std::string sNum;
	std::string sNegNum;

	setDelims(sNumbers, nPos);
	if (m_sDelimsVc.empty())
	{
		sNum = getSubstrWithoutDelims(sNumbers, DELIMS, nPos);
	}
	else
	{
		sNum = getSubstrWithoutDelims(sNumbers, ++nPos);
	}

	int nNum(0);
	int nSum(0);
	bool fNegative = false;

	while (nPos != std::string::npos && !sNum.empty())
	{
		nNum = stoi(sNum);
		if (nNum >= 0 && nNum <= 1000 && !fNegative)
		{
			nSum += nNum;
		}
		else if(nNum < 0)
		{
			fNegative = true;
			sNegNum += sNum + " ";
		}
		if (m_sDelimsVc.empty())
		{
			sNum = getSubstrWithoutDelims(sNumbers, DELIMS, nPos);
		}
		else
		{
			sNum = getSubstrWithoutDelims(sNumbers, ++nPos);
		}
	}
	if (fNegative)
	{
		throw std::logic_error("Negatives not allowed: " + sNegNum);
	}

	return nSum;
}

void StringCalc::setDelims(const std::string& SourceStr, size_t& nPos)
{
	if (SourceStr.size() > 2)
	{
		if ('/' == SourceStr[0] && '/' == SourceStr[1])
		{
			nPos = SourceStr.find_first_of("\n");

			if (nPos != std::string::npos && nPos > 2)
			{
				std::string Delims = SourceStr.substr(2, nPos - 2);

				if (1 == Delims.size())
				{
					m_sDelimsVc.push_back(Delims);
					return;
				}
				if ('[' == *Delims.begin() && ']' == *Delims.rbegin())
				{
					size_t nBegPos(0);
					size_t nNextPos = Delims.find_first_of(']');

					while (nNextPos != std::string::npos && nBegPos != std::string::npos)
					{
						if (nNextPos > nBegPos + 1)
						{
							m_sDelimsVc.push_back(Delims.substr(nBegPos + 1, nNextPos - nBegPos - 1));
						}
						nBegPos = Delims.find_first_of('[', nNextPos);
						nNextPos = Delims.find_first_of(']', nBegPos);
					}
				}
			}
		}
	}
}

std::string StringCalc::getSubstrWithoutDelims(const std::string &SourceStr, const char* Delims, size_t &nBegPos)
{
	nBegPos = SourceStr.find_first_not_of(Delims, nBegPos);
	size_t nPos = SourceStr.find_first_of(Delims, nBegPos);

	if (nPos != std::string::npos)
	{
		std::swap(nPos, nBegPos);
		return SourceStr.substr(nPos, nBegPos - nPos);
	}
	if (nBegPos != std::string::npos)
	{
		nPos = nBegPos;
		nBegPos = SourceStr.size();
		return SourceStr.substr(nPos, SourceStr.size() - nPos);
	}
	return std::string();
}

std::string StringCalc::getSubstrWithoutDelims(const std::string& SourceStr, size_t& nBegPos)
{
	size_t nPos(nBegPos);

	for (std::string Delim1: m_sDelimsVc)
	{
		nBegPos = SourceStr.find_first_not_of(Delim1, nBegPos);

		if (nBegPos != std::string::npos)
		{
			for (std::string Delim2 : m_sDelimsVc)
			{
				nPos = SourceStr.find(Delim2, nBegPos + 1);

				if (nPos != std::string::npos)
				{
					return SourceStr.substr(nBegPos, nPos - nBegPos);
				}
			}
			return SourceStr.substr(nBegPos, SourceStr.size() - nBegPos);
		}
	}
	return std::string();
}