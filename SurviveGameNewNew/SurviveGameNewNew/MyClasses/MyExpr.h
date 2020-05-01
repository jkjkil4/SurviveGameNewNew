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
		int num = 0;
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

	inline bool checkType(int num1, Expr expr) {
		bool result = false;
		switch (expr.type) {
		case Equal:
			result = num1 == expr.num;
			break;
		case More:
			result = num1 > expr.num;
			break;
		case Less:
			result = num1 < expr.num;
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

	bool checkNumber(int num) {
		int size = vec.size();

		if (size == 0)
			return def;
		bool result = checkType(num, *vec.begin());
		
		if (size == 1)
			return result;
		for (auto it = vec.begin() + 1; it < vec.end(); it++) {
			Expr expr = *it;
			bool result2 = checkType(num, expr);
			result = checkOper(result, result2, expr.oper);
		}
		return result;
	}

	void clear() {
		vec.clear();
	}
};

#endif