#ifndef __rtFont_H__
#define __rtFont_H__

namespace rt
{
	class Font : public Resource, public sf::Font
	{
	public:
		Font();
		Font(const std::string& iResourceName);
		virtual ~Font();

		virtual void Load();
		virtual void Unload();

		virtual bool IsLoaded();

	protected:
		bool mIsLoaded;
	};
}

#endif