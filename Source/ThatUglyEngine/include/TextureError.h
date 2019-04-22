#pragma once

#include <stdexcept>
#include <sstream>
#include <string>

namespace tbd
{

class TextureError : public std::runtime_error	// TODO: fix this - should allow for writing in! (CRTP for the streamable errors)
{
public:
	TextureError()
		: std::runtime_error{""}
	{}

	template<class T>
	TextureError& operator<<(const T& msg)
	{
		m_buffer << msg;
		return *this;
	}

	const char* what() const override
	{
		m_message = m_buffer.str();
		return m_message.data();
	}

private:
	std::stringstream m_buffer;
	mutable std::string m_message; // TODO: fix the mutable
};

} // namespace tbd {
