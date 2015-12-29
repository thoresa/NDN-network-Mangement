#include <iostream>
#include <memory>
#include <ndn-cxx/face.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <unistd.h>
#include <string>
#include <ndn-cxx/security/key-chain.hpp>

#include "../src/nmib.hpp"
#include "../src/nameTypes.hpp"
#include "../src/chunkType.hpp"
#include "../src/typeFactory.hpp"
#include "serialization.hpp"

#define cache_size 1000

FILE *fd;
#define VMM_MAX_SIZE 8196
#define COMMAND_BUFFER_SIZE 512

namespace ndnManage {

using namespace ndn;
using namespace std;
using namespace ndnManage;
using namespace nameType;

class Producer
{
public:
	void
	onInterest(const Name& name, const Interest& interest)
	{
		string infoName = interest.getName().toUri().substr(interest.getName().toUri().find("/ndn/manage/"));
		chunkType::ChunkType* type = chunkType::typeFactory::createType(chunkType::ENDPOINTTYPE, "/example/repo/1");
		
		char* filter = "";
		NameType nType;
		if(interest.getName().toUri().find("/cpurate") != std::string::npos)
		{
			nType.infoType = nameType::CPURATE;
		}else if(interest.getName().toUri().find("/memoryrate") != std::string::npos)
		{
			nType.infoType = nameType::MEMORYRATE;
		}else if(interest.getName().toUri().find("/iobandwidth") != std::string::npos)
		{
			nType.infoType = nameType::IOBANDWIDTH;
		}
	    shared_ptr<BaseType> information = type->queryInfoForChunk(nType, infoName, filter);
		string cpurate = information->getElementByKey();
			
		Name dataName(interest.getName());
		dataName
		.append("manage") 
		.appendVersion();  
		
		int size;
	    size = cpurate.length();
		shared_ptr<Data> data = make_shared<Data>(dataName);
	    data->setFreshnessPeriod(time::milliseconds(1000)); 
		data->setContent(reinterpret_cast<const uint8_t*>(cpurate.c_str()), size);

	    m_keyChain.sign(*data);

		m_face.put(*data);
	}	


	void
	onRegisterFailed(const std::string& reason)
	{
		m_face.shutdown();
	}
	void
	run()
	{
	    m_face.setInterestFilter("/ndn/cn/edu/tongji/hosta/manage/server",
	                             bind(&Producer::onInterest, this, _1, _2),
	                             RegisterPrefixSuccessCallback(),
		                         bind(&Producer::onRegisterFailed, this, _2));
	    m_face.processEvents();
	}

private:
	Face m_face;
	KeyChain m_keyChain;
};

} // namespace ndnManage

int
main(int argc, char** argv){
	try {
		ndnManage::Producer producer;
		producer.run();
	}
	catch (std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
	return 0;
}
