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
	string prefix(argv[2]);

	if(strcmp(argv[1], "query") == 0)
	{
		char* filter = "";
		NameType nType;
		nType.infoType = nameType::CPURATE;
		std::string value = type->queryInfoForChunk(nType, prefix, filter)->toString();
		std::cout<<"hostInfo:"<<value<<std::endl;
	}
	else
	{
		char* filter = "";
		NameType nType;
		nType.infoType = nameType::CPURATE;
		std::cout<<"prefix"<<prefix<<std::endl;
		type->collectInfoForChunk(nType, prefix, filter);
	}
	return 0;
}

