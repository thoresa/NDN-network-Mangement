#include "endpointType.hpp"
#include "serialization.hpp"
#include <vector>
using std::vector;

namespace ndnManage
{
namespace chunkType
{
	
using namespace nameType;

void
EndpointType::queryFaces(string filter)
{
	try
	{
		m_buffer = make_shared<OBufferStream>();
		ndn::Name realName(ndn::Name(nfdPrefix).append(filter));
		ndn::Interest interest(realName);
		interest.setChildSelector(1);
		interest.setMustBeFresh(true);

		ndn::util::SegmentFetcher::fetch(m_face, interest,
							  util::DontVerifySegment(),
							  bind(&EndpointType::afterFetchData, this, _1),
							  bind(&EndpointType::afterFetchTimeout, this, _1, _2));
		m_face.processEvents();
	}
	catch(std::exception& e)
	{

	}
}

void
EndpointType::afterFetchData(const ndn::ConstBufferPtr& dataset)
{
	size_t offset = 0;
	vector<nameType::FaceStatusStruct> faceStatuses;
	
	while(offset<dataset->size())
	{
		nmib::NDNMib ndnMib(localNDNMibName);
		bool isOk = false;
		ndn::Block block;
		std::tie(isOk, block) = ndn::Block::fromBuffer(dataset, offset);
		if(!isOk)
		{
			break;
		}
		offset += block.size();
		nfd::FaceStatus faceStatus(block);
		FaceStatusStruct faceStatusStru;

		faceStatusStru.m_faceId = faceStatus.getFaceId();
		faceStatusStru.m_remoteUri = faceStatus.getRemoteUri();
		faceStatusStru.m_localUri = faceStatus.getLocalUri();

		faceStatusStru.m_InInterests = faceStatus.getNInInterests();
		faceStatusStru.m_InDatas = faceStatus.getNInDatas();
		faceStatusStru.m_OutInterests = faceStatus.getNOutInterests();
		faceStatusStru.m_OutDatas = faceStatus.getNOutDatas();
		faceStatusStru.m_InBytes = faceStatus.getNInBytes();
		faceStatusStru.m_OutBytes = faceStatus.getNOutBytes();

		if(faceStatus.hasExpirationPeriod())
		{
			faceStatusStru.m_expirationPeriod = faceStatus.getExpirationPeriod();
		}
		faceStatuses.push_back(faceStatusStru);
		//name: /ndn/manage/dataType/data_name/objectInfo
		ndn::Name name(ndn::Name(m_facesPrefix).append(std::to_string(faceStatusStru.m_faceId)));
		int size;
		const char* buf = nameType::Serialization::Serialize(faceStatusStru, size);	
		ndnMib.insert(name, reinterpret_cast<const uint8_t*>(buf), size);
	}

}



void
EndpointType::afterFetchTimeout(uint32_t errorCode, const string& errMsg)
{

}

void
EndpointType::onData(const ndn::Interest& interest, ndn::Data& data)
{
	return ;
}

void
EndpointType::onTimeout(const ndn::Interest& interest)
{
	//call collectfaces() for three times.
	return;
}

void
EndpointType::queryFib(string name)
{

}

void 
EndpointType::queryHostInfo(string name)
{

}


}
}
