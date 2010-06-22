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

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		void SetString(const std::string& iString);
		void SetSize(int iSize);
		void SetFont(const std::string& iResourceName);
	};
}

#endif