#include <string>
#include <iostream>
#include "rtsp_client.h"
#include "rtsp_worker.h"
#include <unistd.h>


void RTSPOpenCvClient::stream() {
  /*
  Streaming the RTSP connections.
  */
  std::thread stream_thread(&IRTSPWorker::run, m_worker);
  stream_thread.detach();
  while (true)
  {
    m_worker->show();
    char c = (char)cv::waitKey(1);
    if (c == 27)
    {
      break;
    }
  }
}

RTSPOpenCvClient::RTSPOpenCvClient(std::shared_ptr<IRTSPWorker>& worker) : m_worker(worker) {
  /*
  creating the RTSP connections.
  */
}

RTSPOpenCvClient::~RTSPOpenCvClient() {
  /*
  RTSP Client destructor.
  */
}











