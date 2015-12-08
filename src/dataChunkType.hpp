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
private:
	ndn::Face m_face;
};
}
}
