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
		std::cout<<"query data name: "<<prefix<<std::endl;
		std::string value = type->queryInfoForChunk(nType, prefix, filter)->toString();
		std::cout<<value<<std::endl;
	}
	else if(strcmp(argv[1], "collect") == 0)
	{
		char* filter = "";
		NameType nType;
		nType.infoType = nameType::CPURATE;
		string cpuratePrefix = prefix + "/cpurate";
		string memoryratePrefix = prefix + "/memoryrate";
		string iobandwidthPrefix = prefix + "/iobandwidth";

		while(true)
		{
			nType.infoType = nameType::CPURATE;
			type->collectInfoForChunk(nType, cpuratePrefix, filter);
			nType.infoType = nameType::MEMORYRATE;
			type->collectInfoForChunk(nType, memoryratePrefix, filter);
			nType.infoType = nameType::IOBANDWIDTH;
			type->collectInfoForChunk(nType, iobandwidthPrefix, filter);
			sleep(5);
		}
	}
	else if(strcmp(argv[1], "delete") == 0)
	{
		std::cout<<"delete data name: "<<prefix<<std::endl;
		type->deleteInfoInMib(prefix);

	}
	else 
	{

	}
	return 0;
}

