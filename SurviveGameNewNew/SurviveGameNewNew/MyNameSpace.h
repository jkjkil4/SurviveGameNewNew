#ifndef _MYNAMESPACE_H
#define _MYNAMESPACE_H

#define VERSION_SAVE 0

enum AlignFlags {
	Left	=	1,
	Right	=	2,
	Top		=	4,
	Bottom	=	8
};

enum MouseFlags { Press, Release };

struct MyKey {
	bool isForWidget;
	bool flag;
	int key;
};

class MyExpr
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

class MyGlobal
{
public:
	//所显示的控件
	int visibleFlag = 0;

	//新建存档
	void resetCreateSave() {
		createSaveName = TEXT("NULL");
		createSaveWidth = 400;
		createSaveHeight = 400;
		createSaveSeed = 114514;
		visibleFlag = 0;
	}
	std::wstring createSaveName = TEXT("NULL");
	int createSaveWidth = 400;
	int createSaveHeight = 400;
	int createSaveSeed = 114514;
};

#endif