#ifndef _RTSP_CLENT_H_
#define _RTSP_CLENT_H_

#include "common.h"
#include "rtsp_worker.h"
#include <iostream>
#include <thread>
#include <mutex>

/*RTSP Interface*/
class IRTSPClient {
    public:
    virtual void stream() = 0;
    virtual ~IRTSPClient() {}

};

/*Overloaded RTSPOpenCvClient*/
class RTSPOpenCvClient : public IRTSPClient {
    std::shared_ptr<IRTSPWorker> m_worker;
    public:
    RTSPOpenCvClient(std::shared_ptr<IRTSPWorker>& worker);
    virtual ~RTSPOpenCvClient();
    virtual void stream();
};



#endif 
