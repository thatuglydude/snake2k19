#pragma once

namespace tbd {

// TODO: try to avoid singletons - how viable that is for self-registering types?
template<class T>
class Singleton
{
public:
	static T& instance()
	{
		static T s_instance;
		return s_instance;
	}

	operator T&()
	{
		return instance();
	}
};

} // namespace tbd {
