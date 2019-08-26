#pragma once

#include <variant>
#include <vector>
#include <string>
#include <memory>

#include "plugin_export_interface.h"

struct ObjectData
{
	ObjectData(std::string sHumanReadableName, std::string sMemberID, double Data)
		: m_sHumanReadableName(sHumanReadableName)
		, m_sMemberID(sMemberID)
	{
		m_Member.emplace<double>(Data);
	}

	ObjectData(std::string sHumanReadableName, std::string sMemberID, int32_t Data)
		: m_sHumanReadableName(sHumanReadableName)
		, m_sMemberID(sMemberID)
	{
		m_Member.emplace<int32_t>(Data);
	}

	ObjectData(std::string sHumanReadableName, std::string sMemberID, bool Data)
		: m_sHumanReadableName(sHumanReadableName)
		, m_sMemberID(sMemberID)
	{
		m_Member.emplace<bool>(Data);
	}

	std::string m_sHumanReadableName;
	std::string m_sMemberID;
	std::variant<double, int32_t, bool> m_Member;
};


class ObjectModel
{
public:
	ObjectModel(IObjectDescription* pObjectDesctiption);

	class ObjectParamsFiller : public IParamsFiller
	{
	public:
		ObjectParamsFiller(ObjectModel& model);
		virtual ~ObjectParamsFiller() override = default;

		virtual void addBool(const char* sHumanReadableName, const char* sID) override;
		virtual void addInt(const char* sHumanReadableName, const char* sID) override;
		virtual void addDouble(const char* sHumanReadableName, const char* sID) override;

	private:
		ObjectModel& m_Model;
	};

	class ObjectParamsGetter: public IParamsGetter
	{
	public:
		ObjectParamsGetter(ObjectModel& model);
		virtual ~ObjectParamsGetter() override = default;

		virtual bool getBool(const char* sID) override;
		virtual int32_t getInt(const char* sID) override;
		virtual double getDouble(const char* sID) override;

	private:
		ObjectModel& m_Model;
	};

	std::string getId() const;
	std::string getHumanReadableName() const;
	double calculate(double dX, double dY, double dZ);

private:
	std::vector<ObjectData> m_Data;
	std::unique_ptr<IObjectDescription> m_pObjectDesctiption;
	std::unique_ptr<ObjectParamsGetter> m_pParamsGetter;
};

