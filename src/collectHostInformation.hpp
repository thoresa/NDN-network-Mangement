#include <map>
namespace ndnManage
{
namespace chunkType
{

float
collectCpuOccupyRate();

float
collectMemoryOccupyRate();

std::map<string, int>
collectIOBandwidth();

}
}

