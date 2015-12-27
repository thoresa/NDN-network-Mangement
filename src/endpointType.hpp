#ifndef ENDPOINT_TYPE_HPP
#define ENDPOINT_TYPE_HPP
#include "chunkType.hpp"
#include <memory>
#include <ndn-cxx/encoding/buffer-stream.hpp>
#include <ndn-cxx/security/validator-null.hpp>
#include <ndn-cxx/management/nfd-face-status.hpp>
#include <ndn-cxx/util/segment-fetcher.hpp>
#include <boost/algorithm/string/replace.hpp>

namespace ndnManage
{
namespace chunkType
{

using namespace ndn;

class EndpointType:public ChunkType
{
public:
	EndpointType(string name):
	ChunkType(name),
	retryTime(3)
	{
		nfdPrefix = "/localhost/nfd/faces/list";
	}

	void collectInfoForChunk(NameType& nameType, string& name, void* args)
	{
		switch(nameType.infoType)
		{
			case nameType::CPURATE:
				name = name+"/cpurate";
				std::cout<<name<<std::endl;
				this->collectCpuRate(name, static_cast<char*>(args));	
				break;

			case nameType::HOSTINFO:
				name = name+"/hostinfo";
				this->collectHostInfo(name, static_cast<char*>(args));	
				break;

			case nameType::CHANNELS:
				break;
			case nameType::FACES:
				name = name+"/faces";
				this->collectFaces(name, static_cast<char*>(args));
				break;
			case nameType::FIB:

				break;
			case nameType::RIB:

				break;
			case nameType::STRATEGY:

				break;
			default:
				//std::cerr<<"no such info type"<<std::endl;
				break;
			
		}
	}

	std::shared_ptr<nameType::BaseType>
	queryInfoForChunk(NameType& nameType, string& name, void* args)
	{
		std::shared_ptr<nameType::BaseType> result;
		switch(nameType.infoType)
		{
			case nameType::CPURATE:
//				name = name+"/cpurate";
				result = std::make_shared<nameType::CpuRateStruct>(this->queryCpuRate(name));
				break;
			case nameType::HOSTINFO:
				result = std::make_shared<nameType::HostInfo>(this->queryHostInfo(name));
				break;
			case nameType::CHANNELS:

				break;
			case nameType::FACES:
				result = std::make_shared<nameType::FaceStatusStruct>(this->queryFaces(name));
				break;
			case nameType::FIB:

				break;
			case nameType::RIB:

				break;
			case nameType::STRATEGY:

				break;
			default:
				//std::cerr<<"no such info type"<<std::endl;
				break;
			
		}
		return result;
	}

private:
	void collectFaces(string& name, string filter);
	nameType::FaceStatusStruct queryFaces(string& name);
	
	void collectHostInfo(string& name, string args);
	nameType::HostInfo queryHostInfo(string& name);

	
	void collectCpuRate(string& name, string args);
	nameType::CpuRateStruct queryCpuRate(string& name);

	void onData(const ndn::Interest& interest, ndn::Data& data);
	void onTimeout(const ndn::Interest& interest);
	void queryChannels(){};
	void queryFIB(){};
	void queryRIB(){};
	void queryStrategy(){};
	
	void queryFib(string name);
	
	
void afterFetchData(const ndn::ConstBufferPtr& dataset);

void afterFetchTimeout(uint32_t errorCode, const string& errMsg);


private:
	string nfdPrefix;
	ndn::Face m_face;
//	ndn::FaceManager faceManager;
	int retryTime;
//	ndn::ValidatorNull m_validator;
	shared_ptr<OBufferStream> m_buffer;
	//format: /ndn/manage + host_name + /faces		
	string m_facesPrefix;
	//format: /ndn/manage + host_name + /hostinfo
	string m_hostInfoName;
};
}
}
#endif
