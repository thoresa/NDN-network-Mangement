#ifndef TYPE_FACTORY_HPP
#define TYPE_FACTORY_HPP

#include "chunkType.hpp"
#include "dataChunkType.hpp"
#include "commandType.hpp"
#include "endPointType.hpp"

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
				std::cout<<"data chunk type"<<std::endl;
				return new DataChunkType();
				break;
			case(COMMANDTYPE):
				return new CommandType();
				break;
			case(ENDPOINTTYPE):
				return new EndPointType();
				break;
			default:
				return NULL;
		}
	}

};
}
}
#endif

