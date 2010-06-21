#ifndef __rtDataChunk_H__
#define __rtDataChunk_H__

namespace rt
{
	class WorldObject;

	class DataChunk
	{
	public:
		DataChunk();
		DataChunk(Poco::XML::Node* iNode);
		~DataChunk();

		void SetNode(Poco::XML::Node* iNode);

		std::string GetName();
		std::string GetValue();
		std::string GetOption(const std::string& iOptionName);

		bool IsValid();

		bool HasSubChunks();
		void GetSubChunks(std::vector<DataChunk>& iSubChunks);

		WorldObject* CreateWorldObject();

	protected:
		Poco::XML::Node* mNode;
	};
}

#endif