#include "ReTechCommonIncludes.h"
#include "ReTechOption.h"

namespace rt
{
	Option::Option()
	{

	}

	Option::~Option()
	{

	}

	Option& Option::operator=( const std::string& iValue )
	{
		mDataHolder = iValue;

		return *this;
	}

	Option& Option::operator=( int iValue )
	{
		mDataHolder = iValue;

		return *this;
	}

	Option& Option::operator=( float iValue )
	{
		mDataHolder = iValue;

		return *this;
	}

	std::string Option::ToString()
	{
		return Poco::AnyCast<std::string>(mDataHolder);
	}

	int Option::ToInt()
	{
		return Poco::AnyCast<int>(mDataHolder);
	}

	float Option::ToFloat()
	{
		return Poco::AnyCast<float>(mDataHolder);
	}
}