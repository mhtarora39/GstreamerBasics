
#ifndef _RTSP_WORKER_H_INCLUDED_
#define _RTSP_WORKER_H_INCLUDED_
#include "common.h"

/*
Worker Interface,
*/
class IRTSPWorker {

public:
    virtual void run() = 0;
    virtual void show() = 0;

};

/*
Worker class,
*/
class RTSPWorker : public IRTSPWorker
{

private:
    using Codec = int;
    cv::VideoWriter m_writer;
    cv::VideoCapture m_cap;
    std::string m_uri;
    Codec codec;
    std::mutex mtx;
    int width, height;
    bool create_connection();
    void release_resources();
    void initalize_recorder(const std::string &filepath);
    bool initialize(const std::string &filepath);
    bool m_initialized = false;
    cv::Mat m_frame;
    int m_height, m_width;

public:
    RTSPWorker(const RTSPWorker& ) = delete;
    void operator=(const RTSPWorker& ) = delete;
    RTSPWorker(const std::string& uri,const std::string &recorder_filepath = "");
    virtual ~RTSPWorker();
    virtual void run();
    virtual void show();
};

#endif

