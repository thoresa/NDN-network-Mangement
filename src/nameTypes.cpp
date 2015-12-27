#include "nameTypes.hpp"
#include <map>
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
	<<hostInfo.m_memoryRate<<" ";
	
	int interfaceNums = hostInfo.m_IOBandwidth.size();
	out<<interfaceNums<<" ";
	for(std::map<string, int>::const_iterator iter = hostInfo.m_IOBandwidth.begin(); iter!=hostInfo.m_IOBandwidth.end(); iter++)
	{
			out<<iter->first<<" "<<iter->second<<" ";
	}

	out<<hostInfo.m_hostName<<" "
	<<hostInfo.m_isVM<<" "
	<<hostInfo.m_vmHost;
	return out;
}

std::istream& operator>>(std::istream& in, struct HOSTINFO& hostInfo)
{
	in>>hostInfo.m_cpuRate
	>>hostInfo.m_memoryRate;
	
	int interfaceNums;
	in>>interfaceNums;
	string first;
	int second; 
	for(int i = 0; i<interfaceNums; i++)
	{
		in>>first>>second;
		hostInfo.m_IOBandwidth[first] = second;
	}
	
	in>>hostInfo.m_hostName
	>>hostInfo.m_isVM
	>>hostInfo.m_vmHost;
	return in;
}

}
}
