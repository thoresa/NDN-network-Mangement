#ifndef NAME_DEFINE_HPP
#define NAME_DEFINE_HPP
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <ndn-cxx/face.hpp>


namespace ndnManage
{
namespace nameType
{


using std::map;
using std::string;

enum INFORMATIONTYPES
{
	//Common
	SIGNATURE=0,
	CHUNKSIZE,
	BORNTIME,
	DIETIME,

	//EndpointType
	HOST_INFO,
	CHANNELS,
	FACES,
	FIB,
	RIB,
	STRATEGY,

	//CommandType
	OPERATOR,
	OPERAND,
	ARGUMENTS,

	//DataChunkType
	CACHENODES,
	ACCESSNUMBER,
	LASTACCESSTIME,
	OWNER
};

struct HOSTINFO
{
	float m_cpuRate;
	float m_memoryRate;
	float m_IORate;
	int totalMemory;
	
	string hostName;
	bool isVM;
	string vmHost;

	const std::string toString();

	friend std::ostream& operator<<(std::ostream&, const struct HOSTINFO&);
	friend std::istream& operator>>(std::istream&, struct HOSTINFO&);
	
};

struct FACESTATUSSTRUCT
{
	uint64_t  m_faceId;

	string  m_remoteUri;
	string  m_localUri;

	uint64_t  m_InInterests;
	uint64_t  m_InDatas;
	uint64_t  m_OutInterests;
	uint64_t  m_OutDatas;
	uint64_t  m_InBytes;
	uint64_t  m_OutBytes;

	ndn::time::milliseconds  m_expirationPeriod;
	
	const std::string toString();
	friend std::ostream& operator<<(std::ostream&, const struct FACESTATUSSTRUCT&);
	friend std::istream& operator>>(std::istream&, struct FACESTATUSSTRUCT&);

};

typedef struct FACESTATUSSTRUCT FaceStatusStruct;
typedef struct HOSTINFO HostInfo;


class NameType
{
public:
	static ndn::Name formatName(string nmibPrefix,
								string dataType,
								string dataName,
								string informationType)
	{
		return realFormatName(ndn::Name(nmibPrefix),
							  ndn::Name(dataType),
							  ndn::Name(dataName),
							  ndn::Name(informationType));
	}


	typedef enum INFORMATIONTYPES InformationTypes;

	InformationTypes infoType;
private:
	static ndn::Name realFormatName(ndn::Name nmibPrefix,
 			   					    ndn::Name dataType,
							        ndn::Name dataName,
							        ndn::Name informationType)
	{
		ndn::Name combinationName;
		combinationName.append(nmibPrefix)
					   .append(dataType)
					   .append(dataName)
					   .append(informationType);
		return combinationName;
	}
};

}
}
#endif
