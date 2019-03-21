#ifndef _GUI_H
#define _GUI_H
#pragma once


namespace c8gui {
	static constexpr int w {1024};
	static constexpr int h {768};
	static const char* window_title = "Chip8 Interpreter";
	static const void error(const std::string& str, const char* err) 
	{
		std::cerr << str << err << std::endl;
	}
}




#endif
