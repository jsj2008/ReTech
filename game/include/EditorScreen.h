#ifndef __EditorScreen_H__
#define __EditorScreen_H__

class EditorScreen : public rt::Screen
{
public:
	EditorScreen();
	virtual ~EditorScreen();

	virtual void Pushed();
	virtual void Poped();

	void Save();

protected:
};

#endif