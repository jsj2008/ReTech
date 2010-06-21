#ifndef __rtText_H__
#define __rtText_H__

#include "ReTechDrawable.h"

namespace rt
{
	class Text : public Drawable
	{
	public:
		Text();
		virtual ~Text();

		virtual void UnSerialize(DataChunk& iDataChunk);

		void SetResource(const std::string& iResourceName);
	};
}

#endif