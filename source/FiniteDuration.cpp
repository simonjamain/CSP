#include "FiniteDuration.hpp"
//TODO: make FiniteDuration and Duration inherit the same class to avoid throw warning
namespace CSP
{
	void
    FiniteDuration::setValue(unsigned int length)
	{
		_duration.setValue(length);
	}

    unsigned int
    FiniteDuration::getLength() const
	{
        return _duration.getLength();
	}
}
