#pragma once

#include <vector>

namespace My {
	template<typename T>class LimitSizeVector;
}


template<typename T>
class My::LimitSizeVector : public std::vector<T>
{
public:
	LimitSizeVector() {}
	LimitSizeVector(int limitSize)
		: limitSize(limitSize) {}

	void addElement(T element) {
		this->push_back(element);
		if (limitSize != -1 && this->size() > 20)
			this->erase(this->begin());
	}

	void cancelLimitSize() {
		limitSize = -1;
	}

private:
	int limitSize = -1;
};