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
	
private:
	
	const static map<string, ndn::Name> dataTypes;
	const static map<string, ndn::Name> informationTypes;

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
	static map<string, ndn::Name> createDataTypesMap()
	{
		map<string, ndn::Name> realDataTypes;
		realDataTypes["dataChunk"] = ndn::Name("datachunk");
		realDataTypes["command"] = ndn::Name("command");
		realDataTypes["endPoint"] = ndn::Name("endpoint");
		return realDataTypes;
	}
	static map<string, ndn::Name> createInformationTypesMap()
	{
		map<string, ndn::Name> realInformationTypes;
		
		//common info
		realInformationTypes["Owner"] = ndn::Name("owner");
		realInformationTypes["BornTime"] = ndn::Name("borntime");
		realInformationTypes["dieTime"] = ndn::Name("dietime");
		realInformationTypes["cacheNodes"] = ndn::Name("cachenodes");

		//data chunk info
		realInformationTypes["dataChunkSize"] = ndn::Name("datachunksize");
		
		//command info
		realInformationTypes["commandOperator"] = ndn::Name("commandOperator");

		//endPoint info
		realInformationTypes["endPointFIB"] = ndn::Name("endpointfib");

		return realInformationTypes;
	}
	
};

const map<string, ndn::Name> NameType::dataTypes = NameType::createDataTypesMap();
const map<string, ndn::Name> NameType::informationTypes = NameType::createInformationTypesMap();

}
}
#endif
