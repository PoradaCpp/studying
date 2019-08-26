#include "object_model.h"

#include <algorithm>

ObjectModel::ObjectModel(IObjectDescription* pObjectDesctiption)
	: m_pObjectDesctiption(pObjectDesctiption)
{
	ObjectParamsFiller paramFiller(*this);
	pObjectDesctiption->getObjectParam(paramFiller);
	m_pParamsGetter = std::make_unique<ObjectParamsGetter>(*this);
}

std::string ObjectModel::getId() const
{
	return m_pObjectDesctiption->getId();
}

std::string ObjectModel::getHumanReadableName() const
{
	return m_pObjectDesctiption->getHumanReadableName();
}

double ObjectModel::calculate(double dX, double dY, double dZ)
{
	return m_pObjectDesctiption->calculate(*m_pParamsGetter, dX, dY, dZ);
}

ObjectModel::ObjectParamsFiller::ObjectParamsFiller(ObjectModel& model)
	: m_Model(model)
{}

void ObjectModel::ObjectParamsFiller::addBool(const char* sHumanReadableName, const char* sID)
{
	m_Model.m_Data.emplace_back(sHumanReadableName, sID, true);
}

void ObjectModel::ObjectParamsFiller::addInt(const char* sHumanReadableName, const char* sID)
{
	m_Model.m_Data.emplace_back(sHumanReadableName, sID, 0);
}

void ObjectModel::ObjectParamsFiller::addDouble(const char* sHumanReadableName, const char* sID)
{
	m_Model.m_Data.emplace_back(sHumanReadableName, sID, 0.0);
}

ObjectModel::ObjectParamsGetter::ObjectParamsGetter(ObjectModel& model)
	: m_Model(model)
{}

bool ObjectModel::ObjectParamsGetter::getBool(const char* sID)
{
	auto Iter = std::find_if(m_Model.m_Data.begin(), m_Model.m_Data.end(), [sID] (ObjectData& data)
	{
		return strcmp(data.m_sMemberID.c_str(), sID) == 0;
	});

	return std::get<bool>(Iter->m_Member);
}

int32_t ObjectModel::ObjectParamsGetter::getInt(const char* sID)
{
	auto Iter = std::find_if(m_Model.m_Data.begin(), m_Model.m_Data.end(), [sID](ObjectData& data)
	{
		return strcmp(data.m_sMemberID.c_str(), sID) == 0;
	});

	return std::get<int32_t>(Iter->m_Member);
}

double ObjectModel::ObjectParamsGetter::getDouble(const char* sID)
{
	auto Iter = std::find_if(m_Model.m_Data.begin(), m_Model.m_Data.end(), [sID](ObjectData& data)
	{
		return strcmp(data.m_sMemberID.c_str(), sID) == 0;
	});

	return std::get<double>(Iter->m_Member);
}