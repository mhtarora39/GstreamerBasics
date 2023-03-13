
#ifndef _COMMON_H_INCLUDED_
#define  _COMMON_H_INCLUDED_

#include "opencv2/opencv.hpp"
#include <opencv2/videoio.hpp>
#define LOG_ERROR std::cout << "[ERROR] : "
#define LOG_WARNING std::cout << "[WARNING] : " 
#define LOG_INFO std::cout << "[INFO] : " 
#define FPS 30.0

#define TRY_RELEASE(FUNC, MSG)      \
    try                             \
    {                               \
        FUNC;                       \
    }                               \
    catch (...)                     \
    {                               \
        LOG_WARNING << MSG << "\n"; \
    }                               
#endif
