#ifndef _GUI_H
#define _GUI_H
#pragma once
#include <cstdio>


namespace c8gui {
	static constexpr int w {1024};
	static constexpr int h {768};
	static const char* window_title = "Chip8 Interpreter";
	static const void error(const char * str, const char * err)
	{
		fprintf(stderr, "%s - %s", str, err);
	}
}




#endif // _GUI_H
