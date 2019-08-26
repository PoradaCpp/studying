#ifndef PLUG_IN_MAIN
#define PLUG_IN_MAIN

#include <windows.h>
#include <cstdint>
#include <string>

#include "../PluginArc/plugin_export_interface.h"

class ObjectDescriptionTest: public IObjectDescription
{
public:
    virtual ~ObjectDescriptionTest() override = default;

	virtual const char* getId() const override;
	virtual const char* getHumanReadableName() const override;
	virtual void getObjectParam(IParamsFiller& paramsFiller) override;
	virtual double calculate(IParamsGetter& paramsGetter, double dX, double dY, double dZ) override;

private:
	const char* m_sID = "4AAB10FD-C377-4441-B4AC-AE97D827ED60";
    const char* m_sName = "Sphere";
};

class InterfaceExportTest: public InterfaceExport
{
public:
	virtual ~InterfaceExportTest() override = default;

	virtual IObjectDescription* getObject() const override;
};

#endif // PLUG_IN_MAIN