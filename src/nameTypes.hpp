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
	
	friend std::ostream& operator<<(std::ostream&, const struct FACESTATUSSTRUCT&);
	friend std::istream& operator>>(std::istream&, struct FACESTATUSSTRUCT&);
};

typedef struct FACESTATUSSTRUCT FaceStatusStruct;

/*
class Serialization
{
public:
	static const char* 
	Serialize(const FaceStatusStruct& fs)
	{
		std::ostringstream os;
		boost::archive::binary_oarchive archive(os);
		archive<<fs;
		std::string content = os.str();
		return content.c_str();
	}
	
};
*/

/*
std::ostream& operator<<(std::ostream& out, struct FACESTATUSSTRUCT& currentStatus)
{
	out<<currentStatus.m_faceId<<" "
	<<currentStatus.m_remoteUri<<" "
	<<currentStatus.m_localUri<<" "
	<<currentStatus.m_InInterests<<" "
	<<currentStatus.m_InDatas<<" "
	<<currentStatus.m_OutInterests<<" "
	<<currentStatus.m_OutDatas<<" "
	<<currentStatus.m_InBytes<<" "
	<<currentStatus.m_OutBytes;
	return out;

}
*/
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
