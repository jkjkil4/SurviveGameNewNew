#pragma once

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