#ifndef PLUG_IN_EXPORT_INTERFACE
#define PLUG_IN_EXPORT_INTERFACE

#include <string>

class IParamsFiller
{
public:
	virtual ~IParamsFiller() = default;

	virtual void addBool(const char* sHumanReadableName, const char* sID) = 0;
	virtual void addInt(const char* sHumanReadableName, const char* sID) = 0;
	virtual void addDouble(const char* sHumanReadableName, const char* sID) = 0;
};

class IParamsGetter
{
public:
	virtual ~IParamsGetter() = default;

	virtual bool getBool(const char* sID) = 0;
	virtual int32_t getInt(const char* sID) = 0;
	virtual double getDouble(const char* sID) = 0;
};

class IObjectDescription
{
public:
    virtual ~IObjectDescription() = default;

	virtual const char* getId() const = 0;
	virtual const char* getHumanReadableName() const = 0;
	virtual void getObjectParam(IParamsFiller& paramsFiller) = 0;
    virtual double calculate(IParamsGetter& paramsGetter, double dX, double dY, double dZ) = 0;
};


class InterfaceExport
{
public:
    virtual ~InterfaceExport() = default;

    virtual IObjectDescription* getObject() const = 0;
};

extern "C"
{
	__declspec(dllexport) InterfaceExport* getInterface();
}

#endif // PLUG_IN_EXPORT_INTERFACE
