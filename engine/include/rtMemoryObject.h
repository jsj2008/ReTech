#pragma once

namespace rt
{
	class MemoryObject
	{
	public:
		MemoryObject();
		virtual ~MemoryObject();

		void Destroy();

		bool IsValid();

	protected:
		bool mIsValid;
	};
}