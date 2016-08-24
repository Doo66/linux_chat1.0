#include "udp_log.h"
//int init_fp()
//{
//	size_t ret = open("./log.txt",O_WRONLY | O_CREAT | O_TRUNC);
//	if(ret == -1)
//		exit(0);
//	dup2(2,ret);
//}

void print_log(std::string _log)
{
#ifdef _DEBUG_
	std::cerr << __FUNCTION__ << " : " << __LINE__<<" : "<< _log << std::endl;
#endif
}
