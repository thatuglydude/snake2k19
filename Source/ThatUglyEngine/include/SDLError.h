#pragma once

#include <stdexcept>
#include <sstream>

namespace tbd {

class SDLError : public std::exception
{
public:
	explicit SDLError(const std::string& msg, const std::string& sdlMsg)	// TODO: make stream friendly
	{
		std::stringstream errStream;
		errStream << msg << sdlMsg;
		m_msg = errStream.str();
	}

	const char* what() const override
	{
		return m_msg.data();
	}

private:
	std::string m_msg;

};

} // namespace tbd {
