#include "chunkType.hpp"

namespace ndnManage
{
namespace chunkType
{
const string nfdPrefix = "/localhost/nfd/faces/query";

class EndpointType:public ChunkType
{
public:
	void queryFaces(string filter);
	EndpointType(string localNDNMibName):
	ndnMib(localNDNMibName),
	retryTime(3)
	{
		
	}
	EndpointType(){}
private:
	void onData(const ndn::Interest& interest, ndn::Data& data);
	void onTimeout(const ndn::Interest& interest);
	void queryFib(string name);
	void queryHostInfo(string name);


private:
	nmib::NDNMib ndnMib;
	ndn::Face m_face;
	int retryTime;
};
}
}
