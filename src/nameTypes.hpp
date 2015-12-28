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
	CPURATE,
	MEMORYRATE,

	HOSTINFO,
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

struct BASETYPE
{
public:
	const virtual std::string toString() = 0;
	virtual string getElementByKey(int key = 0)
	{
		return NULL;
	}

};

struct CPURATESTRUCT:public BASETYPE
{
private:
	float m_cpurate;
public:
	float getCpuRate()
	{
		return m_cpurate;
	}
	void setCpuRate(float rate)
	{
		m_cpurate = rate;		
	}
	const virtual std::string toString()
	{
		return std::to_string(getCpuRate());
	}
	virtual string getElementByKey(int key=0)
	{
		return toString();
	}

};

struct MEMORYRATESTRUCT:public BASETYPE
{
private:
	float m_memoryrate;
public:
	float getMemoryRate()
	{
		return m_memoryrate;
	}
	void setMemoryRate(float rate)
	{
		m_memoryrate = rate;		
	}
	const virtual std::string toString()
	{
		return std::to_string(getMemoryRate());
	}
	virtual string getElementByKey(int key=0)
	{
		return toString();
	}

};

struct HOSTINFO:public BASETYPE
{
	float m_cpuRate;
	float m_memoryRate;
	std::map<string, int> m_IOBandwidth;
	string m_hostName;

	bool m_isVM;
	string m_vmHost;
private:
	float getCpuRate()
	{
		return m_cpuRate;
	}
	float getMemoryRate()
	{
		return m_memoryRate;
	}
	int getIOBandwidth(string eth)
	{
		return m_IOBandwidth[eth];
	}
public:
	static enum 
	{
		CPURATE=0,
		MEMORYRATE,
		IOBANDWIDTH
	}HostInfoElementKeys;
	void assign(float cpuRate,
				float memoryRate,
				std::map<string, int>& IOBandwidth,
				string& hostName,

				bool isVM = false,
				string vmHost = "")
	{
		m_cpuRate = cpuRate;
		m_memoryRate = memoryRate;
		m_IOBandwidth = IOBandwidth;	
		m_hostName = hostName;

		m_isVM = isVM;
		m_vmHost = vmHost;
		

	}
	virtual string getElementByKey(int key)
	{
		string element;
		switch(key)
		{
			case(CPURATE):
				element = std::to_string(getCpuRate());
				break;
			case(MEMORYRATE):
				element = std::to_string(getMemoryRate());
				break;
			case(IOBANDWIDTH):
				element = std::to_string(getIOBandwidth("eth0"));
				break;
			default:
				break;
		} 
		return  element;
	}
	const virtual std::string toString()
	{
		std::ostringstream os;
		os<<*this;
		return os.str();
	}

	friend std::ostream& operator<<(std::ostream&, const struct HOSTINFO&);
	friend std::istream& operator>>(std::istream&, struct HOSTINFO&);
	
};

struct FACESTATUSSTRUCT:public BASETYPE
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
	
	const virtual std::string toString()
	{
		std::ostringstream os;
		os<<*this;
		return os.str();
	}
	
	friend std::ostream& operator<<(std::ostream&, const struct FACESTATUSSTRUCT&);
	friend std::istream& operator>>(std::istream&, struct FACESTATUSSTRUCT&);

};

typedef struct BASETYPE BaseType;
typedef struct CPURATESTRUCT CpuRateStruct;
typedef struct MEMORYRATESTRUCT MemoryRateStruct;
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
