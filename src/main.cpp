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
	nmib::NDNMib ndnMib;
	
	//string dType = "ndn";
	//string dataName = "manage";
	string infoType(argv[1]);
	ndn::Name objectName = ndn::Name(infoType);
	std::cout<<"start get data from repo"<<std::endl;
	const uint8_t* buf;
	int size=0;
	buf = ndnMib.read(objectName, size);
	std::streambuf* ob;
	ob=std::cout.rdbuf();
	std::ostream out(ob);
	nameType::FaceStatusStruct fs;
	fs = nameType::Serialization::DeSerialize(reinterpret_cast<const char*>(buf));
	cout<<fs<<endl;
/*
	chunkType::ChunkType* type = chunkType::typeFactory::createType(chunkType::ENDPOINTTYPE, "/example/repo/1");
	char* filter = "";
	NameType nType;
	nType.infoType = nameType::FACES;
	type->queryInfoForChunk(nType, filter);
*/	return 0;
}
