#pragma once
#ifndef GUI_H
#define GUI_H


namespace c8gui {
	constexpr int w {1024};
	constexpr int h {768};
	const char* window_title = "Chip8 Interpreter";
	static void error(const std::string& str, const char* err) 
	{
		std::cerr << str << err << std::endl;
	}
}




#endif