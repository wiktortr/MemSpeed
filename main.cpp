#include <iostream>
#include <chrono>

using namespace std;

int main() {

	uint32_t size_of_sample = 5000;
	uint32_t size_of_data_to_alloc = 32768;
	uint64_t t_new = 0;
	uint64_t t_malloc = 0;
	uint64_t t_allocator = 0;

	std::allocator<uint8_t> a1;


	for (int i = 0; i < size_of_sample; i++) {
		{
			auto start = std::chrono::high_resolution_clock::now();
			uint8_t* d = new uint8_t[size_of_data_to_alloc];
			auto finish = std::chrono::high_resolution_clock::now();
			t_new += chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
			delete d;
		}

		{
			auto start = std::chrono::high_resolution_clock::now();
			uint8_t* d = (uint8_t*)malloc(size_of_data_to_alloc);
			auto finish = std::chrono::high_resolution_clock::now();
			t_malloc += chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();

		}

		{
			auto start = std::chrono::high_resolution_clock::now();
			uint8_t* a = a1.allocate(size_of_data_to_alloc);
			auto finish = std::chrono::high_resolution_clock::now();
			t_allocator += chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count();
		}
	}



	cout << "New        T: " << t_new / size_of_sample << "\n";
	cout << "Malloc     T: " << t_malloc / size_of_sample << "\n";
	cout << "Allocator  T: " << t_allocator / size_of_sample << "\n";


	system("pause");
	return 0;
}