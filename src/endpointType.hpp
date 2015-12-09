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
		//format: /ndn/manage + host_name + faces		
		m_facesPrefix = "/ndn/manage/ndn/cn/edu/tongji/hosta/faces";
	}

	void collectInfoForChunk(NameType& nameType, void* args)
	{
		switch(nameType.infoType)
		{
			case nameType::HOST_INFO:
			
				break;
			case nameType::CHANNELS:

				break;
			case nameType::FACES:
				this->collectFaces(static_cast<char*>(args));
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

	std::string queryInfoForChunk(NameType& nameType, string& name, void* args)
	{
		std::string result;
		switch(nameType.infoType)
		{
			case nameType::HOST_INFO:
			
				break;
			case nameType::CHANNELS:

				break;
			case nameType::FACES:
				result = this->queryFaces(name).toString();
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
private:
	void collectFaces(string filter);
	nameType::FaceStatusStruct queryFaces(string& name);

	void onData(const ndn::Interest& interest, ndn::Data& data);
	void onTimeout(const ndn::Interest& interest);
	void queryHostInfo(){};
	void queryChannels(){};
	void queryFIB(){};
	void queryRIB(){};
	void queryStrategy(){};
	
	void queryFib(string name);
	void queryHostInfo(string name);
	
	
void afterFetchData(const ndn::ConstBufferPtr& dataset);

void afterFetchTimeout(uint32_t errorCode, const string& errMsg);


private:
	string nfdPrefix;
	ndn::Face m_face;
//	ndn::FaceManager faceManager;
	int retryTime;
//	ndn::ValidatorNull m_validator;
	shared_ptr<OBufferStream> m_buffer;
	string m_facesPrefix;
};
}
}
#endif
