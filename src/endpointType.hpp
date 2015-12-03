#include "chunkType.hpp"

namespace ndnManage
{
namespace chunkType
{
#ifndef MANAGE_NFD_PREFIX
#define MANAGE_NFD_PREFIX
#endif

class EndpointType:public ChunkType
{
public:
	void queryFaces(string filter);
	EndpointType():
	retryTime(3)
	{
		nfdPrefix = "/localhost/nfd/faces/list";
	}
	EndpointType(){}
private:
	void queryInfoForChunk(NameType){}
	void onData(const ndn::Interest& interest, ndn::Data& data);
	void onTimeout(const ndn::Interest& interest);
	void queryFib(string name);
	void queryHostInfo(string name);


private:
	string nfdPrefix;
	ndn::Face m_face;
	ndn::FaceManager faceManager;
	int retryTime;
};
}
}
