#ifndef NAME_DEFINE_HPP
#define NAME_DEFINE_HPP

#include <map>
#include <string>
#include <function>
#include <ndn-cxx/face.hpp>
#include <boost/timer.hpp>
#include <vector>

namespace ndnManage
{
namespace nameType
{
using std::map;
using std::string;
using std::function;
using boost::timer::date;
using std::vector;

class basicObjectName
{
public;
	//typedef function<void*(string)> colllectFunction;
	//typedef function<bool(string, char*)> updateFunction;
	//typedef function<bool(string, char*)> removeFunction;
	
	//map<string, collectFunction*> collectOperator;
	//map<string, Function*> updateOperator;
	//map<string, Function*> removeOperator;
	
	basicObjectName()
	{
		infoType[bornTime] = datePointer;
		infoType[dieTime] = datePointer;
		infoType[state] = stringPointer;
		infoType[lastVisit] = datePointer;
		infoType[totalVisit] = unsignedIntPointer;
		infoType[signature] = charArrayPointer;
		infoType[name] = charAarrayPointer;
	}
	
	void*
	getPointer(string name)
	{
		return infoType[name];
	}

protected:
	map<string, void*> infoType;
	
	//chunkType *operation;
	const string bornTime = "borntime";
	const string dieTime = "dietime";
	const string state = "state";
	const string lastVisit = "lastvisit";
	const string totalVisit = "totalvisit";
	const string signature = "signature";
	const string name = "name";
	
	int* intPointer;
	unsigned int* unsignedIntPointer;
	bool* boolPointer;
	char* charArrayPointer;
	date* datePointer;

	//string* stringPointer;


};

class dataChunkObjectName:public basicObjectName
{
public:
	dataChunkObjectName()
	{
		infoType[cacheNode] = vectorPointer;
		infoType[owner] = charArrayPointer;
		infoType[size] = unsignedIntPointer;
		infoType[TotalSegments] = unsignedIntPointer;
		infoType[startSegments] = intPointer;

		//operation = typeFactory("dataChunk");

		//collectOperator[cacheNode] = operation->collectCacheNodes();
	}

private:
	const string cacheNode = "cacheNodes";
	const string owner = "owner";
	const string size = "size";
	const string totalSegments = "totalSegments";
	const string startSegments = "startSegments";

public:
	vector<string>* vectorPointer;

};

class commandObjectName:public basicObjectName
{
public:
	commandObjectName()
	{
		infoType[operator] = charArratPointer;
		infoType[operand] = charArrayPointer;
		infoType[arguments] = charArrayPointer;
		infoType[liveTime] = intPointer;


		operation = typeFactory("command");
	}
private:
	const string operator = "operator";
	const string operand = "operand";
	const string arguments = "arguments";
	const string liveTime = "livetime";
};

struct hostInfoStruct
{
	float cpuRate;
	float memoryRate;
	float IORate;
	int cpuNums;
	int memorySize;
	int swapSize;
};

class endpointObjectName:public basicObjectName
{
public:
	endpointObjectName()
	{
		infoType[fib] = vectorPointer;
		infoType[pit] = vectorPointer;
		infoType[rib] = vectorPointer;
		infoType[faces] = vectorPointer;
		infoType[channel] = vectorPointer;
		infoType[strategy] = vectorPointer;
		infoType[hostInfo] = hostInfoPointer;


		operation = typeFactory("endpoint");
	}	
private:
	const string fib = "fib";
	const string pit = "pit";
	const string rib = "rib";
	const string faces = "faces";
	const string channel = "channel";
	const string strategy = "strategy";
	const string hostInfo = "hostInfo";

public:
	struct hostInfoStruct* hostInfoPointer;
};



#endif
