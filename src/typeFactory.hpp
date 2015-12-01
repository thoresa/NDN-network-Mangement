#ifndef TYPE_FACTORY_HPP
#define TYPE_FACTORY_HPP

#include "chunkType.hpp"
#include "dataChunkType.hpp"
#include "commandType.hpp"
#include "endpointType.hpp"

namespace ndnManage
{
namespace chunkType
{
typedef enum
{
	DATACHUNKTYPE,
	COMMANDTYPE,
	ENDPOINTTYPE
}CHUNKTYPE;

class typeFactory
{
public:
	static ChunkType* createType(CHUNKTYPE type)
	{
		switch(type)
		{
			case(DATACHUNKTYPE):
				return new DataChunkType();
				break;
			case(COMMANDTYPE):
				return new CommandType();
				break;
			case(ENDPOINTTYPE):
				return new EndpointType();
				break;
			default:
				return NULL;
		}
	}

};
}
}
#endif

