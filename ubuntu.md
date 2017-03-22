
# velodyne Ubuntu下环境配置
## cmake
在terminal中输入以下指令，判断Ubuntu之中是否有cmake。
	
	 $ cmake --version
	 
需要的是cmake的版本至少在3.1以上，如果不在的话，则需要自己下载对应的cmake包来安装。

## OpenGL

	 $ sudo apt-get install buildessential
	 $ sudo apt-get install libgl1mesadev
	 $ sudo apt-get install libglu1mesadev
	 $ sudo apt-get install freeglut3dev
	
执行上面的命令，进行OpenGL的配置。

在配置完成之后，进行测试。测试样例代码testOpenGl.c

	 $ gcc -o testOpenGL testOpenGL.c -lGL -lGLU -lglut
	 $ ./testOpenGL

如果会出现一个茶壶的图片，则配置成功。

## 配置lcm

lcm是轻量级通信工具（Lightweight Communication and Marshalling），所以，我们这里进行的是直接解压包并安装利用。

	$ unzip lcm1.3.1.zip
	$ cd lcm1.3.1
	$ ./configure
	$ make
	$ sudo make install

## 编译及运行
	
	cd Velodyne_viewer/bin/Debug
	./run.sh
	cd Velodyne_viewer/bin/Debug/pcap
	replay_pcap.py temp1.pcap

通过进入到对应的文件夹中，运行相应的文件，来进行程序的运行。其中./run.sh是需要先运行的，然后在pcap文件夹中，找到想要运行的pcap文件的全称，利用replay_pcap.py xxx来进行数据的处理，就可以了。

最后，如果看到了图片的话，那么恭喜你，环境配置成功了，你可以尽情的玩耍了！

