#include "endpointType.hpp"
#include "serialization.hpp"
#include "collectHostInformation.hpp"
#include <vector>
using std::vector;

namespace ndnManage
{
namespace chunkType
{
	
using namespace nameType;

void
EndpointType::collectFaces(string& name, string filter)
{
	try
	{
		m_buffer = make_shared<OBufferStream>();
		ndn::Name realName(ndn::Name(nfdPrefix).append(filter));
		ndn::Interest interest(realName);
		interest.setChildSelector(1);
		interest.setMustBeFresh(true);
		
		m_facesPrefix = name;
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
EndpointType::collectHostInfo(string& name, string filter)
{
	try
	{
		m_hostInfoName = name;
		float cpuRate = collectCpuOccupyRate();
		float memoryRate = collectMemoryOccupyRate();
		std::map<string, int> IOBandwidth = collectIOBandwidth();

		string hostName = "TODO";
		/*
		for(std::map<string, int>::iterator iter = IOBandwidth.begin(); iter!=IOBandwidth.end(); iter++)
		{
			std::cout<<iter->first<<" "<<iter->second<<std::endl;
		}
		*/
		
		nameType::HostInfo hostInfo;
		hostInfo.assign(cpuRate, memoryRate, IOBandwidth, hostName);
		
		nmib::NDNMib ndnMib(localNDNMibName);
		ndn::Name hostInfoName = ndn::Name(m_hostInfoName);
		int size;
		const char* buf = nameType::Serialization<nameType::HostInfo>::Serialize(hostInfo, size);	
		ndnMib.insert(hostInfoName, reinterpret_cast<const uint8_t*>(buf), size);
	}
	catch(std::exception& e)
	{
		std::cout<<e.what()<<std::endl;
	}
}

void
EndpointType::collectCpuRate(string& name, string filter)
{
	try
	{
		float cpuRate = collectCpuOccupyRate();
		string cpuRateStr = std::to_string(cpuRate);

		nmib::NDNMib ndnMib(localNDNMibName);
		ndn::Name cpuRateName = ndn::Name(name);
		int size = cpuRateStr.length();
		const char* buf = cpuRateStr.c_str();	
		ndnMib.insert(cpuRateName, reinterpret_cast<const uint8_t*>(buf), size);
		
	}
	catch(std::exception& e)
	{
		std::cout<<e.what()<<std::endl;
	}
}

void
EndpointType::collectIOBandwidthOccupy(string& name, string filter)
{
	try
	{
		std::map<string, int> IOBandwidth = collectIOBandwidth();
	
		for(std::map<string, int>::iterator iter = IOBandwidth.begin(); iter!=IOBandwidth.end(); iter++)
		{
			nmib::NDNMib ndnMib(localNDNMibName);
			string iobandwidthStr = std::to_string(iter->second);
			string ethNameStr = name + "/" +iter->first;
			ndn::Name ethName = ndn::Name(ethNameStr);
			int size = iobandwidthStr.length();
			const char* buf = iobandwidthStr.c_str();	
			ndnMib.insert(ethName, reinterpret_cast<const uint8_t*>(buf), size);
		}
	}
	catch(std::exception& e)
	{
		std::cout<<e.what()<<std::endl;
	}
}

void
EndpointType::collectMemoryRate(string& name, string filter)
{
	try
	{
		float memoryRate = collectMemoryOccupyRate();
		string memoryRateStr = std::to_string(memoryRate);

		nmib::NDNMib ndnMib(localNDNMibName);
		ndn::Name memoryRateName = ndn::Name(name);
		int size = memoryRateStr.length();
		const char* buf = memoryRateStr.c_str();	
		ndnMib.insert(memoryRateName, reinterpret_cast<const uint8_t*>(buf), size);
		
	}
	catch(std::exception& e)
	{
		std::cout<<e.what()<<std::endl;
	}
}

nameType::CpuRateStruct
EndpointType::queryCpuRate(string& name)
{
	ndn::Name queryName = ndn::Name(name);
	nmib::NDNMib ndnMib;
	int size;
	const uint8_t* buf = ndnMib.read(queryName, size);

	std::string cpurateStr(reinterpret_cast<const char*>(buf));
	nameType::CpuRateStruct cpurate;
	cpurate.setCpuRate(atof(cpurateStr.c_str()));
	
	return cpurate;
}

nameType::MemoryRateStruct
EndpointType::queryMemoryRate(string& name)
{
	ndn::Name queryName = ndn::Name(name);
	nmib::NDNMib ndnMib;
	int size;
	const uint8_t* buf = ndnMib.read(queryName, size);

	std::string memoryrateStr(reinterpret_cast<const char*>(buf));
	nameType::MemoryRateStruct memoryrate;
	memoryrate.setMemoryRate(atof(memoryrateStr.c_str()));
	
	return memoryrate;
}

nameType::IOBandwidthStruct
EndpointType::queryIOBandwidth(string& name)
{
	ndn::Name queryName = ndn::Name(name);
	nmib::NDNMib ndnMib;
	int size;
	const uint8_t* buf = ndnMib.read(queryName, size);

	std::string IOBandwidthStr(reinterpret_cast<const char*>(buf));
	nameType::IOBandwidthStruct iobandwidth;
	iobandwidth.setIOBandth(atoi(IOBandwidthStr.c_str()));
	
	return iobandwidth;
}
nameType::FaceStatusStruct
EndpointType::queryFaces(string& name)
{
	ndn::Name queryName = ndn::Name(name);
	nmib::NDNMib ndnMib;
	int size;
	const uint8_t* buf = ndnMib.read(queryName, size);
	nameType::FaceStatusStruct fstatus = nameType::Serialization<FaceStatusStruct>::DeSerialize(reinterpret_cast<const char*>(buf));
	return fstatus;
}

nameType::HostInfo
EndpointType::queryHostInfo(string& name)
{
	ndn::Name queryName = ndn::Name(name);
	nmib::NDNMib ndnMib;
	int size;
	const uint8_t* buf = ndnMib.read(queryName, size);
	nameType::HostInfo hostInfo = nameType::Serialization<HostInfo>::DeSerialize(reinterpret_cast<const char*>(buf));
	return hostInfo;
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
		const char* buf = nameType::Serialization<FaceStatusStruct>::Serialize(faceStatusStru, size);	
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



}
}
