#include <iostream>
#include <ndn-cxx/face.hpp>
#include "../src/nmib.hpp"
#include "../src/nameTypes.hpp"
#include "../src/chunkType.hpp"
#include "../src/typeFactory.hpp"
#include "serialization.hpp"

using namespace std;
using namespace ndnManage;
using nameType::NameType;

int main(int argc, char** argv)
{
	chunkType::ChunkType* type = chunkType::typeFactory::createType(chunkType::ENDPOINTTYPE, "/example/repo/1");
	string infoType(argv[2]);
	if(strcmp(argv[1], "query") == 0)
	{
		char* filter = "";
		NameType nType;
		nType.infoType = nameType::FACES;
		std::string faceStatus = type->queryInfoForChunk(nType, infoType, filter)->toString();
		std::cout<<"face:"<<faceStatus<<std::endl;
	}
	else
	{
		char* filter = "";
		NameType nType;
		nType.infoType = nameType::FACES;
		type->collectInfoForChunk(nType, infoType, filter);
	}
	return 0;
}
