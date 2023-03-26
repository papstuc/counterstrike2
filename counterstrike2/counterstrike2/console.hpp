#pragma once

namespace console
{
	void initialize(const wchar_t* console_title);
	void release();

	void log(const wchar_t* message...);
	void log(const char* message...);
}