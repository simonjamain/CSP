#include "Duration.hpp"

namespace CSP
{
	void
    Duration::setValue(unsigned int value)
	{
		_length = value;
		_finite = true;
	}

	void
	Duration::setValue(PositiveInfinity value)
	{
        _length = DEFAULT_VALUE;
		_finite = false;
	}

    unsigned int
	Duration::getLength() throw(IsInfiniteException)
	{
		if(! _finite)
		{
			throw(IsInfiniteException());
		}else
		{
			return _length;
		}
	}

	bool
	Duration::isFinite()
	{
		return _finite;
	}
}
