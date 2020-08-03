#pragma once

#include <vector>

class OperationClass {
public:
	virtual ~OperationClass() = default;
	virtual bool check(int*) { return false; }
};

class OperationClass_Equal : public OperationClass
{
public:
	OperationClass_Equal(int visibleNum)
		: visibleNum(visibleNum) {}
	~OperationClass_Equal() override = default;

	bool check(int* pVisibleNum) override {
		return visibleNum == *pVisibleNum;
	}

	int visibleNum;
};

class OperationClass_AnyEqual : public OperationClass
{
public:
	OperationClass_AnyEqual(std::vector<int> nums)
		: nums(nums) {}
	~OperationClass_AnyEqual() override = default;

	bool check(int* pVisibleNum) override {
		for (int num : nums)
			if (num == *pVisibleNum)
				return true;
		return false;
	}

	std::vector<int> nums;
};