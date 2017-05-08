# Loam Slam
## ROS的配置
配置的命令参考http://wiki.ros.org/indigo/Installation/Ubuntu：

	sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
	sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
	sudo apt-get update
	sudo apt-get install ros-indigo-desktop-full
	apt-cache search ros-indigo
	sudo rosdep init
	rosdep update
	echo "source /opt/ros/indigo/setup.bash" >> ~/.bashrc
	source ~/.bashrc
	source /opt/ros/indigo/setup.bash
	sudo apt-get install python-rosinstall
上面的命令是可以进行ros的配置的，如果想要看具体的配置，如下所示：
#### [ros的具体配置](https://github.com/sysuzyc/ES2016_14353404/blob/master/assignment/ES2016_14353404_ROS.pdf)

然后，我们可以看到catkin_ws的配置如下所示：
	mkdir ~/catkin_ws
	cd ~/catkin_ws
	catkin_init_workspace

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

	roslaunch velodyne_pointcloud VLP16_points.launch pcap:="/home/sysuzyc/research/loam_slam/velodyne.pcap"

然后再开另一个terminal，来运行上面的命令。其中最后的那句话，是处理[数据集](https://midas3.kitware.com/midas/folder/12979)，其中双引号内部的路径为自己存放恩东数据集的绝对路径。

这样的话，就完成了实验。效果如下所示：

![开始的图片](https://raw.githubusercontent.com/sysuzyc/Picture/master/velodyne_17-52-56.png)

## 图片展示
在这里，我们需要做的就是将构建的图片收集起来，并进行拼接，得到最后的完整的图形。
	pcl_viewer *.pcd
这个就是我们将保存下来的pcd文件拼接的命令。可以看到结果为：
![nsh](https://github.com/sysuzyc/Picture/blob/master/nsh.png?raw=true)

![nsh](https://github.com/sysuzyc/Picture/blob/master/nsh_small.png?raw=true)

这样就算你成功的运行了loam_slam了。
