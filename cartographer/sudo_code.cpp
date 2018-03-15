需求：
	已知当前点，输入任务点，规划一条路段，根据规划的路段，load其闭环优化所需要的子图。
设定：
	当前点为current_node,下一个任务点为task_node。
	子图划分为submap[],第i子图为submap[i]。
	子图上的每个点都有对应所属子图区域的编号，记为tag，可以对应多个子图，默认tag数目不少于1。
	子图存在一个标志位used。如果被load过，则used为1，否则为0.
	全局地图和轨迹信息为all_map。
	设定拐点信息为turn，该信息为已知信息。


代码：
	/*根据当前点current_node，任务点task_node，以及全局地图，得到规划路径*/
	trajectory = path_plan(current_node,task_node,all_map);
	/*
		根据轨迹trajectory和拐点turn，算出路中经过拐点的个数num，
		并将拐点信息以及任务点（不包含当前点）按照顺序存放在vector格式的turn_node之中。
	*/
	{turn_node,num} = turn_calculate(trajector,turn);
	/*将当前点赋予current，方便下面进行迭代*/
	current = current_node.
	/*迭代处理turn_node中的数据*/
	for(int i=0;i<=num;i++)
	{
		/*依次处理turn_node里面的点*/
		next = turn_node[i];
		/*通过当前点和下一个要去往的点来生成一段轨迹*/
		new_trajectory = CreateTrajectory(current,next);
		/*在生成完轨迹之后，将下一个点赋值给当前点，进行下一次的迭代*/
		current = turn_node[i];
		/*针对new_trajectory所属子图的标签tag进行所需load子图的选取*/
		if(get_num(new_trajectory.tag) == 1)//tag数目为1
		{
			load(submap[new_trajectory.tag[0]]);//load该子图
		}
		else//tag数目大于1
		{
			/*对于子图的tag进行判断，如果有被调用过的子图，则load*/
			for(int j=0;j<get_num(new_trajectory.tag);j++)
			{
				if(submap[new_trajectory.tag[j]].used == 1)
				{
					load(submap[new_trajectory.tag[j]]);
					break;//跳出循环
				}
				else//不存在被调用过的子图
				{
					/*随机选取一个子图*/
					index = random(get_num(new_trajectory.tag));
					load(submap[new_trajectory.tag[index]]);
				}
			}
		}
	}
