#include <iostream>
#include <thread>
#include <vector>
#include <ctime>
#include <chrono>
#include <atomic>

class Data
{
public:
	void increment()
	{
		dFirst += 1;
		fSecond += 1;
	}

	//private:
	double dFirst = 0;
	float fSecond = 0;
};

int main()
{
	std::atomic<Data> data;

	const size_t CORES = std::thread::hardware_concurrency();

	std::cout << "hardware_concurrency(): " << CORES << '\n';
	std::vector<std::thread> threadsVc;
	threadsVc.reserve(CORES);

	for (size_t i = 0; i < CORES; ++i)
	{
		threadsVc.emplace_back([&data]
		{
			for (size_t j = 0; j < 100; ++j)
			{
				Data temp = data.load();
				Data temp1;
				do
				{
					temp1 = temp;
					temp1.increment();
				} while (!data.compare_exchange_weak(temp, temp1));
			}
		});
	}

	for (std::thread& thread : threadsVc)
	{
		thread.join();
	}

	std::cout << data.load().dFirst << " " << data.load().fSecond << '\n';

	system("pause");

	return 0;
}
