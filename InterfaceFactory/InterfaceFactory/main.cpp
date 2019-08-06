#include <iostream>

#include "InterfaceFactory.h"

struct IAction
{
	virtual ~IAction() = default;
	virtual void DoSomething() = 0;
};

struct Action : IAction
{
	virtual ~Action() override = default;

	virtual void DoSomething()
	{
		std::cout << "Action::DoSomething()\n";
	}
};

int main()
{
	std::function<std::unique_ptr<IAction>()> func = []
	{
		return std::make_unique<Action>();
	};

	//InterfaceFactory::Instance().Register <IAction, Action>();

	InterfaceFactory::Instance().Register(func);

	try
	{
		InterfaceFactory::Instance().Register <IAction, Action>();
	}
	catch (std::logic_error& exc)
	{
		std::cout << exc.what() << '\n';
	}

	//InterfaceFactory::Instance().Create<IAction>()->DoSomething();
	//...or:
	auto ptr = InterfaceFactory::Instance().CreateRaw<IAction>();
	ptr->DoSomething();
	delete ptr;

	InterfaceFactory::Instance().Unregister <IAction>();

	try
	{
		InterfaceFactory::Instance().Create<IAction>()->DoSomething();
	}
	catch (std::logic_error& exc)
	{
		std::cout << exc.what() << '\n';
	}

	{
		auto scopedUnreg(InterfaceFactory::Instance().RegisterScoped <IAction, Action>());

		InterfaceFactory::Instance().Create<IAction>()->DoSomething();
	}
	try
	{
		InterfaceFactory::Instance().Create<IAction>()->DoSomething();
	}
	catch (std::logic_error& exc)
	{
		std::cout << exc.what() << '\n';
	}

	//system("pause");
	return 0;
}