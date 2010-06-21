#ifndef __rtSerializeable_H__
#define __rtSerializeable_H__

namespace rt
{
	class Serializeable
	{
	public:
		Serializeable();
		virtual ~Serializeable() = 0;

		virtual void UnSerialize(DataChunk& iDataChunk){};
	};
}

#endif