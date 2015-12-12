#include "nameTypes.hpp"
using namespace std;

namespace ndnManage
{
namespace nameType
{ 

std::ostream& operator<<(std::ostream& out, const struct FACESTATUSSTRUCT& currentStatus)
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


std::istream& operator>>(std::istream& in, struct FACESTATUSSTRUCT& currentStatus)
{
	in>>currentStatus.m_faceId
	>>currentStatus.m_remoteUri
	>>currentStatus.m_localUri
	>>currentStatus.m_InInterests
	>>currentStatus.m_InDatas
	>>currentStatus.m_OutInterests
	>>currentStatus.m_OutDatas
	>>currentStatus.m_InBytes
	>>currentStatus.m_OutBytes;
	return in;
}

std::ostream& operator<<(std::ostream& out, const struct HOSTINFO& hostInfo)
{
	out<<hostInfo.m_cpuRate<<" "
	<<hostInfo.m_memoryRate<<" "
	<<hostInfo.m_IORate<<" "
	<<hostInfo.totalMemory<<" "
	
	<<hostInfo.hostName<<" "
	<<hostInfo.isVM<<" "
	<<hostInfo.vmHost;
	return out;
}

std::istream& operator>>(std::istream& in, struct HOSTINFO& hostInfo)
{
	in>>hostInfo.m_cpuRate
	>>hostInfo.m_memoryRate
	>>hostInfo.m_IORate
	>>hostInfo.totalMemory
	
	>>hostInfo.hostName
	>>hostInfo.isVM
	>>hostInfo.vmHost;
	return in;
}

const std::string 
FaceStatusStruct::toString()
{
	std::ostringstream os;
	os<<*this;
	return os.str();
}

const std::string 
HostInfo::toString()
{
	std::ostringstream os;
	os<<*this;
	return os.str();
}

}
}
