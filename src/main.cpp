#include <iostream>
#include <ndn-cxx/face.hpp>
#include "../src/nmib.hpp"
#include "../src/nameTypes.hpp"
#include "../src/chunkType.hpp"
#include "../src/typeFactory.hpp"


using namespace std;
using namespace ndnManage;

int main(int argc, char** argv)
{
	/*string mibRepoPrefix = "/example/repo/1";
	ndn::Name mibNamePrefix(mibRepoPrefix);
	nmib::NDNMib ndnMib(mibNamePrefix);
	
	string dType = "example";
	string dataName = "data";
	string infoType(argv[1]);
	//ndn::Name objectName = nameType::NameType::formatName(namePrefix, dType, dataName, infoType);
	ndn::Name objectName = ndn::Name(dType).append(dataName).append(infoType);
	std::cout<<objectName<<std::endl;
	chunkType::ChunkType* type = chunkType::typeFactory::createType(chunkType::DATACHUNKTYPE);
	char buf[100] = "Hello Repo !";
	int size = strlen(buf);
	ndnMib.start();
	std::cout<<"start insert data into repo"<<std::endl;
	std::cout<<"the data is "<<buf<<std::endl;
	ndnMib.insert(objectName, reinterpret_cast<uint8_t*>(buf), size);
	std::cout<<"start get data from repo"<<std::endl;
	std::cout<<ndnMib.read(objectName)<<std::endl;
	*/
	chunkType::EndpointType type("/example/repo/1");
	std::cout<<"here"<<std::endl;
	
	type.queryFaces("");
	std::cout<<"here"<<std::endl;
	sleep(5);
	return 0;
}
