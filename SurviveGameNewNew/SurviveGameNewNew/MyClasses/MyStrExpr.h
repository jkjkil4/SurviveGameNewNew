#ifndef _MYSTREXPR_H
#define _MYSTREXPR_H

#include "../utility.h"

class MyStrExpr
{
public:
	void setExpr(std::wstring expr, bool isAccept) {
		this->expr = expr;
		this->isAccept = isAccept;
		isNull = false;
	}
	bool checkAccept(WCHAR ch) {
		bool ok = false;
		if (isAccept) {
			for (auto it = expr.begin(); it < expr.end(); it++) {
				if (ch == *it) {
					ok = true;
					break;
				}
			}
		}
		else {
			ok = true;
			for (auto it = expr.begin(); it < expr.end(); it++) {
				if (ch == *it) {
					ok = false;
					break;
				}
			}
		}
		return ok;
	}
	std::wstring expr = TEXT("");
	bool isAccept = true;
	bool isNull = true;
};

#endif