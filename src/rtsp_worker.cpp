#include "rtsp_worker.h"
#include <opencv2/videoio/registry.hpp>
#include <exception>

/*
ToDo: This logic is very temporary.Will optimize this in future. 
*/
void RTSPWorker::run()
{

    if (!m_initialized)
    {
        LOG_ERROR << "Object is not initialize \n";
        return;
    }
    while (true)
    {

        // Capture frame-by-frame
        // mtx.lock();
        m_cap >> m_frame;
        // mtx.unlock();

        if (m_frame.empty())
        {
            break;
        }
        if (m_writer.isOpened())
        {
            m_writer.write(m_frame);
        }
        char c = (char)cv::waitKey(1);
        if (c == 27)
        {
            break;
        }
    }
}

//
void RTSPWorker::show()
{
    /*
    This is responsible for showing current frame.This method must be call from main thread.
    */

    // mtx.lock();
    while (m_frame.empty())
        ;
    cv::imshow("stream", m_frame);
    // mtx.unlock();
}

void RTSPWorker::initalize_recorder(const std::string &filepath)
{
    /*
    Initialing Writer class for wring video to disk.
    */

    try
    {
        codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
        m_writer = cv::VideoWriter(filepath, codec, FPS, {m_width, m_height});
    }
    catch (...)
    {
        LOG_WARNING << "Recorder Object Failed \n";
    }
}

bool RTSPWorker::create_connection()
{
    /*
    Connecting to RTSP server.
    */
    try
    {
        m_cap = cv::VideoCapture(m_uri);
        if (m_cap.isOpened())
        {
            LOG_INFO << " Connected to " << m_uri << " Backend Name " << m_cap.getBackendName() << std::endl;
        }
        return true;
    }
    catch (const std::exception& e)
    {
        LOG_ERROR << "Failed to connect " << m_uri << " " << e.what() << std::endl;
        return false;
    }
}

bool RTSPWorker::initialize(const std::string &filepath)
{
    /*
    Initializing RTSP client Connections and Disk Writers. 
    */
    try
    {

        if (create_connection())
        {
             m_width = int(m_cap.get(3));
             m_height = int(m_cap.get(4));
             m_initialized = true;
             if (filepath != "")
             {
                 initalize_recorder(filepath);
             }
             return true;
        }
        throw std::runtime_error("");
    }
    catch (...)
    {
        m_initialized = false;
        release_resources();
        throw std::runtime_error("Failed to create connection\n");
    }
}

void RTSPWorker::release_resources()
{
    /*
    Releasing the acquired resources safely.
    */
    TRY_RELEASE(m_cap.release(), "Not able to release video cature device")
    TRY_RELEASE(m_writer.release(), "Not able to release writer device")
    TRY_RELEASE(cv::destroyAllWindows(), "Not able to release the window")
}

RTSPWorker::RTSPWorker(const std::string &uri, const std::string &recorder_filepath) : m_uri(uri)
{
    /*
    Constructor for the RTSP worker class.
    */
    initialize(recorder_filepath);
}

RTSPWorker::~RTSPWorker()
{
    /*
    Destructor releasing all the resources.
    */
    release_resources();
}

