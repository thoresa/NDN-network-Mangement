#ifndef NAME_DEFINE_HPP
#define NAME_DEFINE_HPP

#include <map>
#include <string>
#include <ndn-cxx/face.hpp>

namespace ndnManage
{
namespace nameType
{
using std::map;
using std::string;
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
	static enum InformationTypes
	{
		//common
		SIGNATURE,
		CHUNKSIZE,
		BORNTIME,
		DIETIME,

		//endpointType
		HOST_INFO,
		CHANNELS,
		FACES,
		FIB,
		RIB,
		STRATEGY,

		//commandType
		OPERATOR,
		OPERAND,
		ARGUMENTS,

		//dataChunkType
		CACHENODES,
		ACCESSNUMBER,
		LASTACCESSTIME,
		OWNER,

	};
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
