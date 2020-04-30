#ifndef _MYVISIBLE_H
#define _MYVISIBLE_H

#include <vector>

class MyExpr
{
public:
	enum Type { Equal, More, Less };
	enum Oper { Or, And };

	struct Expr
	{
		int type = Equal;
		int oper = And;
	};

	bool def = false;
	std::vector<Expr> vec;

	void addExpr(Expr expr) {
		vec.push_back(expr);
	}
	void setExpr(Expr expr) {
		vec.clear();
		vec.push_back(expr);
	}

	inline bool checkType(int num1, int num2, int type) {
		bool result = false;
		switch (type) {
		case Equal:
			result = num1 == num2;
			break;
		case More:
			result = num1 > num2;
			break;
		case Less:
			result = num1 < num2;
			break;
		}
		return result;
	}
	inline bool checkOper(bool num1, bool num2, int oper) {
		bool result = false;
		switch (oper) {
		case Or:
			result = num1 || num2;
			break;
		case And:
			result = num1 && num2;
			break;
		}
		return result;
	}

	bool checkNumber(int num1, int num2) {
		int size = vec.size();

		if (size == 0)
			return def;
		bool result = checkType(num1, num2, (*vec.begin()).type);

		if (size == 1)
			return result;
		for (auto it = vec.begin() + 1; it < vec.end(); it++) {
			Expr expr = *it;
			bool result2 = checkType(num1, num2, expr.type);
			result = checkOper(result, result2, expr.oper);
		}
		return result;
	}

	void clear() {
		vec.clear();
	}
};

#endif