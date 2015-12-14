#include <map>
namespace ndnManage
{
namespace chunkType
{

float
collectCpuOccupyRate();

std::map<string, int>
collectMemoryOccupyRate();

float
collectIOBandwidth();

}
}

