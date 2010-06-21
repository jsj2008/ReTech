#ifndef __rtOption_H__
#define __rtOption_H__

namespace rt
{
	class Option
	{
	public:
		Option();
		~Option();

		Option& operator=(const std::string& iValue);
		Option& operator=(int iValue);
		Option& operator=(float iValue);

		std::string ToString();
		int			ToInt();
		float		ToFloat();

	protected:
		Poco::Any mDataHolder;
	};
}

#endif