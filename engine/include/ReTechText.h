#ifndef __rtText_H__
#define __rtText_H__

#include "ReTechWorldObject.h"

namespace rt
{
	class Text : public WorldObject
	{
	public:
		Text();
		virtual ~Text();

		virtual void UnSerialize(const YAML::Node& iNode);
		virtual void Serialize(YAML::Emitter& iEmitter) const;

		virtual void Draw(sf::RenderWindow* iRenderWindow);

		void SetString(const std::string& iString);
		void SetSize(int iSize);
		void SetFont(const std::string& iResourceName);

		protected:
			sf::Text mText;
	};
}

#endif