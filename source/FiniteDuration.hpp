#ifndef FINITEDURATION_HPP_
#define FINITEDURATION_HPP_

#include "Duration.hpp"

namespace CSP
{
	class FiniteDuration 
	{
	private:
		Duration _duration;
	public:
        ~FiniteDuration(){};
        
        FiniteDuration(unsigned int length)
		:_duration(length)
		{};

		void
        setValue(unsigned int value);

        unsigned int
		getLength();
	};
}
#endif /* FINITEDURATION_HPP_ */
