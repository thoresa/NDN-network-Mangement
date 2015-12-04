#include "chunkType.hpp"

namespace ndnManage
{
namespace chunkType
{
class DataChunkType:public ChunkType
{

public:
	DataChunkType(string name):
	ChunkType(name){}
	void collectBornTime(){}
	void collectFib();
	void collectFaces();

private:
	ndn::Face m_face;
};
}
}
