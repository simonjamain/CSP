#ifndef DURATION_HPP_
#define DURATION_HPP_

#define DEFAULT_VALUE -1

namespace CSP
{
class PositiveInfinity{};

class IsInfiniteException
{
public:
    IsInfiniteException(){}
    ~IsInfiniteException(){}
};

class Duration
{
private:
    unsigned int
    _length;

    bool
    _finite;
public:
    ~Duration(){}

    Duration(unsigned int value)
        :_length(value),_finite(true)
    {}

    Duration(PositiveInfinity value)
        :_length(DEFAULT_VALUE),_finite(false)
    {}

    void
    setValue(unsigned int value);

    void
    setValue(PositiveInfinity value);

    unsigned int
    getLength() const throw(IsInfiniteException);

    bool
    isFinite() const;

};
}
#endif /* DURATION_HPP_ */
