/*

		NAME 	 - Global Planner Node 
		DESIGN - Yan Sleight
		PRIORITY - Feature - Not required for basic functionality, required for navigation
	
		--------OVERVIEW--------
This node takes in the map, current position, and goal position, and generates the
entire path for navigation using A* search algorithm. The next position in 
this path is sent out to the local planner.

		--------FUTURE WORK--------
This node has been tested with dummy data but never tested with real world data. 
Map integration has not been done yet and still need to be integrated. Maps are currently generated by
the premade gmapping process by taking in kinect data. This map will need to be fed into this node as
a 2x2 array.

*/

#include "ros/ros.h"
#include "GlobalPlanner.h"

using namespace std;


int main(int argc, char **argv)
{
	ros::init(argc, argv, "GlobalPlannerNode");
	
	GlobalPlanner planner;
	GCRobotics::Pose_msg data;
	
	planner.init(argc, argv);

	ros::Rate r(10); // 10 hz, decide appropriate value plz
	while (ros::ok())
	{
		ros::spinOnce();
		planner.send_next_step();
		data.x = planner.next_step[1];
		data.y = planner.next_step[0];
		planner.pub.publish(data);
		r.sleep();
	}


}


