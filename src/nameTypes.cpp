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
}
}