# **Background**
</br>
This is the dummy assignment where we are creating simple gstreamer plugin then we are deploying it on RTSP server.We are also building RTSP client for connecting to the server.
</br>
</br>

# **Dependencies**
* opencv  4.x: Here we are building open cv from source.Please follow the [instructions](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html)

* [Gstreamer](https://gstreamer.freedesktop.org/documentation/installing/on-linux.html?gi-language=c):

* [Simple RTSP Server](https://github.com/aler9/rtsp-simple-server)


# Compilation.
  1. create build directory i.e mkdir ./build
  2. cd ./build
  3. cmake ..
  4. make
  ### Verifying plugin :
  Please execute gst-inspect-1.0 ./libgstbackgroundsub.so . You should be getting below outputs.
  ```
  Plugin Details:
  Name                     backgroundsub
  Description              Background Sunstraction Plugin.
  Filename                 ./libgstbackgroundsub.so
  Version                  0.0.0
  License                  LGPL
  Source module            backgroundsub
  Binary package           GStreamer Mohit
  Origin URL               https://github.com/mhtarora39

  backgroundsub: Background Subtraction with Open CV
  ```
  ##  Verifying rtsp_client :
  You will find other artifacts also inside the build directory. I have built rtsp_client , Which is nothing but a sample rtsp client which will be hitting to the server. Please check ./rtsp_client --help for usage.


# Demo:
1. Please go to your server directory and please copy line 225 to 227 from [rtsp-simple-server.yml] (./artifacts/rtsp-simple-server.yml#L225).
2. Run rtsp-server 
    ```
    ./rtsp-simple-server ./rtsp-simple-server.yml. 
    ```
    This is basically running below command on the rtsp server.
    ```
    gst-launch-1.0 -v v4l2src device=/dev/video0 ! video/x-raw, width=640, height=360, format=YUY2, framerate=30/1 ! queue ! videoconvert ! video/x-raw, format=BGR ! queue ! backgroundsub ! queue ! videoconvert !  vaapih264enc ! h264parse ! rtspclientsink location=rtsp://localhost:$RTSP_PORT/$RTSP_PATH
    ``` 
3. Run RTSP client 
    ```
    ./rtsp_client rtsp://localhost:8554/mystream ./out.avi
    ```

* You should be getting output from your webcam as below.
</br>
<img src="./artifacts/out.gif"/>

# Miscellaneous:
* Steps to build plugin : 
1. Clone the GStreamer plugins-bad repository
    ```
    git clone https://github.com/GStreamer/gst-plugins-bad.git
    ``` 
2. Create the plugin from the video filter template.
    ```
    mkdir -p yourplugin 
    cd yourplugin
    ../gst-plugins-bad/tools/gst-element-maker yourplugin videofilter
    rm *.so *.o
    mv gstyourplugin.c gstyourplugin.cpp
    ```
3. Please customize methods from above generated plugin.
4. copy the plugin to gstreamer plugin path, In my case it was /usr/lib/x86_64-linux-gnu/gstreamer-1.0/.


### Please feel free to use compiled binaries in [artifacts] (./artifacts)

# ToDo :
1. Create Build Script for the environments setup
2. Enhance RTSP client.
3. Code Cleanup and tests.
4. Improve the Background Subtraction plugin accuracy.



