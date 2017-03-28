# Loam Slam
## ROS的配置
配置的命令如下所示：

	sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
	sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 0xB01FA116
	sudo apt-get update
	sudo apt-get install ros-kinetic-desktop-full
	apt-cache search ros-kinetic
	sudo rosdep init
	rosdep update
	echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
	source ~/.bashrc
	source /opt/ros/kinetic/setup.bash
	sudo apt-get install python-rosinstall
上面的命令是可以进行ros的配置的，如果想要看具体的配置，如下所示：
#### [ros的具体配置](https://github.com/sysuzyc/ES2016_14353404/blob/master/assignment/ES2016_14353404_ROS.pdf)

## cartographer的配置
### Install wstool and rosdep
	sudo apt-get update
	sudo apt-get install -y python-wstool python-rosdep ninja-build
首先是对于在上一次的实验中安装的工具的初始化。

![](http://p1.bpimg.com/567571/812e34e8c0ca9705.png)

#### Create a new workspace in 'catkin_ws'
	mkdir catkin_ws
	cd catkin_ws
	wstool init src
	wstool merge -t src https://raw.githubusercontent.com/googlecartographer/cartographer_ros/master/cartographer_ros.rosinstall
	wstool update -t src
	
![wstool](http://img.blog.csdn.net/20161108211656943)

### Install deb dependencies

	rosdep init
	rosdep update
	rosdep install --from-paths src --ignore-src --rosdistro=${ROS_DISTRO} -y

![](http://p1.bpimg.com/567571/36d96534dd73084a.png)

### build and install

	catkin_make_isolated --install --use-ninja
	source install_isolated/setup.bash
本来按照google的官方网站的做法，是需要翻墙才可以的，不然的话，就会报错。但是如果不想翻墙的话，需要采用以下方法：
#### Build and install Ceres.
	git clone https://ceres-solver.googlesource.com/ceres-solver
	cd ceres-solver
	mkdir build
	cd build
	cmake .. -G Ninja
	ninja
	ninja test
	sudo ninja install
这一步得到的是ceres的建立和初始化，通过从导入对应的文件，可以很好的避免翻墙这种方法。结果也是比较正常的。

![这里写图片描述](http://img.blog.csdn.net/20161108211610379)

然后进行下最后一步，可以看到：

![](http://p1.bqimg.com/567571/c760bf5c26f46b0b.png)

#### Build and install Cartographer

	git clone https://github.com/hitcm/cartographer.git
	cd cartographer
	mkdir build
	cd build
	cmake .. -G Ninja
	ninja
	ninja test
	sudo ninja install
在自己下载的cartographer文件夹中，执行上述的命令，就可以很好的完成这次的实验了。

![cat](http://img.blog.csdn.net/20161108211844663)

同样的最后的一步执行如下：

![这里写图片描述](http://img.blog.csdn.net/20161108212858555)

上面的命令执行完了之后，我们需要做的就是安装cartographer_ros。

为了安装的方便，我们都并没有下载到catkin_ws文件夹下面，所以，自己下载到任意路径之后，执行以下的操作。

	cd catkin_ws/src
	git clone https://github.com/hitcm/artographer_ros.git
	cd catkin_ws
	catkin_make

![cm1](http://img.blog.csdn.net/20161108211959105)

等这些语句运行完之后，看下catkin_ws的src文件夹下都有哪些内容：

![](http://p1.bqimg.com/567571/4be3e72f858ff82d.png)

如果是上面这些内容的话，那么结果就是正确的了。

### Running the demos
	# Download the 2D backpack example bag.
	wget -P ~/Downloads https://storage.googleapis.com/cartographer-public-data/bags/backpack_2d/cartographer_paper_deutsches_museum.bag
	
	# Launch the 2D backpack demo.
	roslaunch cartographer_ros demo_backpack_2d.launch bag_filename:=${HOME}/Downloads/cartographer_paper_deutsches_museum.bag

如果前面的步骤都是正确的话，这一步是可以正确的完成的。

初次运行如下所示：

![](http://p1.bqimg.com/567571/33dfb3d10f32be03.png)
![cm3](http://img.blog.csdn.net/20161108212312180)

看到结果如下所示：

![这里写图片描述](http://img.blog.csdn.net/20161108211147596)

这个是最开始的界面图。

下面的是运行了半个小时之后的效果图：

![这里写图片描述](http://img.blog.csdn.net/20161108211123078)

所以，结果是正确的。

## ros_velodyne的配置
因为要进行velodyne的数据的读取和处理，所以，我们需要进行ros_velodyne的配置

	source /opt/ros/indigo/setup.bash
	mkdir -p ~/catkin_ws/src
	cd ~/catkin_ws/src
	git clone https://github.com/ros-drivers/velodyne.git
	cd ..
	sudo apt-get -f install
	rosdep install --from-paths src --ignore-src --rosdistro indigo -y
	catkin_make
	source devel/setup.bash
其中sudo apt-get -f install是根据自己的Ubuntu而定，我的Ubuntu为16.04，所以，需要加入这样的命令，才能执行下一句。

以上，我们的配置过程就结束了。剩下的就是运行[loam_slam](https://github.com/sysuzyc/loam_velodyne)

## 运行
首先是进入到catkin_ws文件夹。

	cd ~/catkin_ws/src/
	git clone https://github.com/laboshinl/loam_velodyne.git
	cd ~/catkin_ws
	catkin_make -DCMAKE_BUILD_TYPE=Release 
	source ~/catkin_ws/devel/setup.bash

然后，在成功完成了之后，我们需要的就是运行对应的程序了。

	roslaunch loam_velodyne loam_velodyne.launch	

首先开一个terminal来运行上面的命令。

	roslaunch velodyne_pointcloud VLP16_points.launch pcap:="/home/laboshinl/Downloads/velodyne.pcap"

然后再开另一个terminal，来运行上面的命令。其中最后的那句话，是处理[数据集](https://midas3.kitware.com/midas/folder/12979)，其中双引号内部的路径为自己存放恩东数据集的绝对路径。

这样的话，就完成了实验。效果如下所示：

![开始的图片](https://raw.githubusercontent.com/sysuzyc/Picture/master/velodyne_17-52-56.png)

这样就算你成功的运行了这个程序。
