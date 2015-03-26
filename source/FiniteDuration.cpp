#include "FiniteDuration.hpp"

namespace CSP
{
	void
    FiniteDuration::setValue(unsigned int length)
	{
		_duration.setValue(length);
	}

    unsigned int
	FiniteDuration::getLength()
	{
        return _duration.getLength();
	}
}
