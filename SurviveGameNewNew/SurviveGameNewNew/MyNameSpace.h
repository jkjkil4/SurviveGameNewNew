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


#endif