#include <vector>
#include <iostream>

int main()
{
	std::vector<int> vec;
	vec.push_back(230);
	for (int x : vec) {
		std::cout << x << std::endl;
	}
	return 0;
}