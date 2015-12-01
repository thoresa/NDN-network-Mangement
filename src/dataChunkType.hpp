#include "chunkType.hpp"

namespace ndnManage
{
namespace chunkType
{
class DataChunkType:public ChunkType
{

public:
	void collectBornTime(){}
	void collectFib();
	void collectFaces();

private:
	ndn::Face m_face;
};
}
}
