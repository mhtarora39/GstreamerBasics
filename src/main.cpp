#include <gst/gst.h>
#include "rtsp_client.h"
#include "rtsp_worker.h"
#include <string>
#include <memory>

void help()
{
  std::cout << "USAGE : \n"
            << "rtsp_client /rtsp/uri path/to/save/video(optional)\n";
}

int main(gint argc,
         gchar *argv[])
{
  std::string rtsp_uri;
  std::string output_path = "";
  std::shared_ptr<IRTSPWorker> rtsp_worker;
  if (argc == 1)
  {
    help();
    return -1;
  }
  else if (argc >= 2)
  {
    rtsp_uri = std::string(argv[1]);
    if (rtsp_uri == "--help" || rtsp_uri == "-h")
    {
      help();
      return 0;
    }

    if (argc > 2)
    {
      output_path = argv[2];
    }
  }

  rtsp_worker = std::make_shared<RTSPWorker>(rtsp_uri, output_path);
  std::shared_ptr<IRTSPClient> rtsp_client = std::make_shared<RTSPOpenCvClient>(rtsp_worker);
  rtsp_client->stream();
}
