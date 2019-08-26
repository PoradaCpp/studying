// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

#include <cmath>

#include "plugin_main.h"


const char* ObjectDescriptionTest::getId() const
{
	return m_sID;
}

const char* ObjectDescriptionTest::getHumanReadableName() const
{
	return m_sName;
}

void ObjectDescriptionTest::getObjectParam(IParamsFiller& paramsFiller)
{
	paramsFiller.addDouble("Centre_x", "11111");
	paramsFiller.addDouble("Centre_y", "11112");
	paramsFiller.addDouble("Centre_z", "11113");
	paramsFiller.addDouble("Radius",   "11114");
}

double ObjectDescriptionTest::calculate(IParamsGetter& paramsGetter, double dX, double dY, double dZ)
{
	double dCentreX = paramsGetter.getDouble("11111");
	double dCentreY = paramsGetter.getDouble("11112");
	double dCentreZ = paramsGetter.getDouble("11113");
	double dRadius  = paramsGetter.getDouble("11114");

	return dCentreX + dCentreY + dCentreZ + dRadius - dX - dY - dZ;
}

IObjectDescription* InterfaceExportTest::getObject() const
{
	return new ObjectDescriptionTest;
}

InterfaceExport* getInterface()
{
	return new InterfaceExportTest;
}