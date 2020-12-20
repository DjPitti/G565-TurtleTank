The code was created by the group G565 [AAU Robotics 5th semester 10.12.2020]
It contains 4 codes files.

1) PaintControll_full_functionallities.ino - Is the arduino code and was run on a Arduino Mega.
	* the ros.h library is needed. 
	[note: A Arduino Uno does not have sufficiant memory available to run the code]

2) main.cpp will be added in the ros_workspace
 	* remember to add the code in the CMakeList.txt

3) turtlebot_teleop_key is a modified python.
 	* replace it with the original turtlebot_teleop_key locaded in:
	  Computer/opt/ros/kinetic/lib/turtlebot_teleop
	* The original code only provides the driving and speed control for the manual driving,
	  while these codes add additional functionality, such as the paint system and autonumous
	  driving.

4) keyboard_teleop.launch is a modified launch file which will start everything.
	* to be able to use its full functionality it is important to follow those steps first.
		a) open a terminal
		b) move to you workspace 	(cd ros_ws)
		c) compile the workspace	(catkin build)
		d) source the workspace		(source devel/setup.bash)
		e) launch the keyboard_teleop	(roslaunch turtlebot_teleop keyboard_teleop.launch)
	* make sure you connect the Turtlebot before connecting the arduino, otherwise the USB
	  ports will be missmachted.
