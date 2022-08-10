# YOLOX-TensorRT in C++

**1，pth转trt engine**
```shell
python tools/trt.py -f /path/to/your/yolox/exps/yolox_s.py -c your_ckpt.pth
```
会自动将trt_model.engine文件保存到`cpp`目录下

**2，修改配置**

检测类别数量 num_class

输入尺寸 size

**3，编译**
```shell
mkdir build
cd build
cmake ..
./yolox -i xxx
```

opencv如果打不开mp4
```shell
sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev ffmpeg
```
重新编译opencv即可

### Jeston 安装 torch 和 torchision

[链接](https://qengineering.eu/install-pytorch-on-jetson-nano.html)




**4，安装engine**
```shell
unzip eigen-3.3.9.zip
cd eigen-3.3.9
mkdir build
cd build
cmake ..
sudo make install
```