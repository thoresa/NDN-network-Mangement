#include <iostream>
#include <ndn-cxx/face.hpp>
#include "../src/nmib.hpp"
#include "../src/nameTypes.hpp"
#include "../src/chunkType.hpp"
#include "../src/typeFactory.hpp"


using namespace std;
using namespace ndnManage;

int main()
{
	string mibRepoPrefix = "/example/repo/1";
	ndn::Name mibNamePrefix(mibRepoPrefix);
	nmib::NDNMib ndnMib(mibNamePrefix);
	
	string dType = "example";
	string dataName = "data";
	string infoType = "1/b";
	//ndn::Name objectName = nameType::NameType::formatName(namePrefix, dType, dataName, infoType);
	ndn::Name objectName = ndn::Name(dType).append(dataName).append(infoType);
	cout<<objectName<<endl;

	chunkType::ChunkType* type = chunkType::typeFactory::createType(chunkType::DATACHUNKTYPE);
	char buf[100] = "Hello World";
	int size = strlen(buf);
	ndnMib.insert(objectName, reinterpret_cast<uint8_t*>(buf), size);
	//ndnMib.insert(objectName, buf, size);

	return 0;
}
