/*
需求：
	已知当前点，输入任务点，规划一条路段，根据规划的路段，load其闭环优化所需要的子图。
设定：
	当前点为current_node,下一个任务点为task_node。
	子图划分为submap[],第i子图为submap[i]。
	子图上的每个点都有对应所属子图区域的编号，记为tag，可以对应多个子图，默认tag数目不少于1。
	子图存在一个标志位used。如果被load过，则used为1，否则为0.
	全局地图和轨迹信息为all_map。
	设定拐点信息为turn，该信息为已知信息。
	针对三个点的处理方法
输出：
	输出一个map，为整个轨迹中的起始点，拐点，任务点和子图的映射
*/

代码：
	/*构建一个子图映射，第一位为turn_node的下标，第二位为submap的标签*/
	map<int,int> submap_mapping;
	/*根据当前点current_node，任务点task_node，以及全局地图，得到规划路径*/
	trajectory = path_plan(current_node,task_node,all_map);
	/*
		根据轨迹trajectory和拐点turn，算出路中经过拐点的个数num，
		并将拐点信息以及任务点（不包含当前点）按照顺序存放在vector格式的turn_node之中。
	*/
	{turn_node,num} = turn_calculate(trajectory,turn);
	/*将当前点赋予current，方便下面进行迭代*/
	current = current_node.
	/*迭代处理turn_node中的数据*/
	for(int i=0;i<num;i++)
	{
		/*依次处理turn_node里面的点，得到任务点和任务点后面的一个点*/
		task = turn_node[i];
		next = turn_node[i+1];
		/*
			通过当前点和下一个要去往的点来生成一段轨迹,
			得到当前轨迹和接下来要走的轨迹。
		*/
		current_trajectory = CreateTrajectory(current,task);
		next_trajectory = CreateTrajectory(task,next);
		// 在生成完轨迹之后，将下一个点赋值给当前点，进行下一次的迭代
		// current = task;
		/*针对两端路径的tag是否存在交集，决定后面需要load的子图*/
		//IsEmpty(a,b)对于轨迹a和b的tag进行判断，如果含有相同的tag，则为1，否则为0.
		if(IsEmpty(current_trajectory,next_trajectory))
		{
			/*获取两端路径相同tag的数值，并将其存入到repeat_submap之中*/
			repeat_submap[] = get_repeat_tag(current_trajectory,next_trajectory);
			/*只有一个重复子图*/
			if(get_num(repeat_submap) == 1)
			{
				/*
					将该子图映射到对应的turn_node信息中。
					current点对应submap[repeat_submap[0]]，则load该子图
					task点对应submap[repeat_submap[0]]，则load该子图
				*/
				submap_mapping[current] = submap[repeat_submap[0]];
				submap_mapping[task] = submap[repeat_submap[0]];
				/*将该子图的标志位设定为1，代表已经被调用过*/
				submap[repeat_submap[0]].used = 1;
				break;
			}
			else//相同tag数目大于1，代表有多个重复子图
			{
				/*对于子图的tag进行判断，如果有被调用过的子图，则load*/
				for(int j=0;j<get_num(repeat_submap);j++)
				{
					if(submap[repeat_submap[j]].used == 1)//之前被调用过
					{
						/*建立turn_node和submap之间的映射*/
						submap_mapping[current] = submap[repeat_submap[j]];
						submap_mapping[task] = submap[repeat_submap[j]];
						break;//跳出循环
					}
					else//不存在被调用过的子图
					{
						/*随机选取一个子图*/
						index = random(get_num(repeat_submap));
						/*建立turn_node和submap之间的映射*/
						submap_mapping[current] = submap[repeat_submap[index]];
						submap_mapping[task] = submap[repeat_submap[index]];
						/*将盖子图的标志位设定为1*/
						submap[repeat_submap[index]].used = 1;
						break;
					}
				}
			}
			/*由于两个点的映射都已经定好了，所以，直接调到第三个点*/
			current = next;
			i++;
		}
		else//两段轨迹并不处于一个子图之中
		{
			/*按照两点的操作方法来选取子图*/
			//获取当前轨迹的标签tag
			submap_tag[] = get_tag(current_trajectory);
			if(get_num(submap_tag) == 1)//只有一个子图
			{
				/*建立turn_node和submap的映射关系*/
				submap_mapping[current] = submap[submap_tag[0]];
				/*设置标志位为1，代表已经被调用过了*/
				submap[submap_tag[0]].used = 1;
			}
			else//存在两个及以上的子图
			{
				/*对于子图的标志位进行判断*/
				for(int j=0;j<get_num(submap_tag);j++)
				{
					if(submap[submap_tag[j]].used == 1)//有被用过的子图
					{
						/*建立映射关系*/
						submap_mapping[current] = submap[submap_tag[j]];
						break;
					}
					else//不存在被调用过的子图
					{
						/*随机选取一个子图*/
						index = random(get_num(submap_tag));
						/*建立turn_node和submap的映射关系*/
						submap_mapping[current] = submap[submap_tag[index]];
						/*标志位设定为1*/
						submap[submap_tag[index]].used = 1;
						break;
					}
				}
			}
			/*将task复制给current，由于只建立了current的映射关系*/
			current = task;
		}
	}
	/*返回一个映射关系*/
	return submap_mapping;
