/*#include <iostream>
#include <ndn-cxx/face.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <unistd.h>
#include <string>
#include <ndn-cxx/security/key-chain.hpp>

#define cache_size 1000

FILE *fd;
#define VMM_MAX_SIZE 8196
#define COMMAND_BUFFER_SIZE 512

// Enclosing code in ndn simplifies coding (can also use )
namespace ndn {
// Additional nested namespace could be used to prevent/limit name contentions
namespace examples {
char buf[VMM_MAX_SIZE];
int vmmNums = 0;
//std::map<Name, char[VMM_MAX_SIZE]> cacheBuf;
struct cacheNode{
//Name key;
int n;
char value[VMM_MAX_SIZE];
};
struct cacheNode cache[cache_size];
using std::string;
using namespace ndn;

class Producer
{
public:
	void
	onInterest(const Name& name, const Interest& interest)
	{
		Name dataName(interest.getName());
		string infoName = interest.getName().toUri().substr(interest.getName().toUri().find("/ndn/manage/"));
		
		dataName
		.append("testApp") 
		.appendVersion();  
		
		memset(buf, '\0', VMM_MAX_SIZE);
	    vmmNums = fread(buf, sizeof(char), VMM_MAX_SIZE, stdin);
		shared_ptr<Data> data = make_shared<Data>(dataName);
	    data->setFreshnessPeriod(time::milliseconds(10000)); // 10 sec
		data->setContent(reinterpret_cast<const uint8_t*>(buf), vmmNums);

	    m_keyChain.signWithSha256(*data);

		m_face.put(*data);
	}	


	void
	onRegisterFailed(const std::string& reason){
	    std::cerr << "ERROR: Failed to register prefix in local hub's daemon (" << reason << ")"
	              << std::endl;
		m_face.shutdown();
	}
	void
	run(){
	    m_face.setInterestFilter("/ndn/cn/edu/tongji/hosta/manage/server",
	                             bind(&Producer::onInterest, this, _1, _2),
	                             RegisterPrefixSuccessCallback(),
		                         bind(&Producer::onRegisterFailed, this, _2));
	    m_face.processEvents();
	}

private:
	Face m_face;
	struct timeval vmm_start, vmm_end;
	KeyChain m_keyChain;
	int seg;
};

} // namespace examples
} // namespace ndn
*/
/*
int
main(int argc, char** argv){
	try {
		ndn::examples::Producer producer;
		producer.run();
	}
	catch (std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
	return 0;
}*/
