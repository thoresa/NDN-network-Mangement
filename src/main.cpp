#include <iostream>
#include <ndn-cxx/face.hpp>
#include "../src/nmib.hpp"
#include "../src/nameTypes.hpp"
#include "../src/chunkType.hpp"
#include "../src/typeFactory.hpp"


using namespace std;
using namespace ndnManage;
using nameType::NameType;

int main(int argc, char** argv)
{/*
	string mibRepoPrefix = "/example/repo/1";
	ndn::Name mibNamePrefix(mibRepoPrefix);
	nmib::NDNMib ndnMib(mibNamePrefix);
	
	string dType = "ndn";
	string dataName = "management";
	string infoType(argv[1]);
	ndn::Name objectName = ndn::Name(dType).append(dataName).append(infoType);
	char buf[100] = "Hello Repo !";
	int size = strlen(buf);
	std::cout<<"start insert data into repo"<<std::endl;
	std::cout<<"the data is "<<buf<<std::endl;
	ndnMib.insert(objectName, reinterpret_cast<uint8_t*>(buf), size);
	std::cout<<"start get data from repo"<<std::endl;
	std::cout<<ndnMib.read(objectName)<<std::endl;
*/
	chunkType::ChunkType* type = chunkType::typeFactory::createType(chunkType::ENDPOINTTYPE, "/example/repo/1");
	char* filter = "";
	NameType nType;
	nType.infoType = nameType::FACES;
	type->queryInfoForChunk(nType, filter);
	return 0;
}
