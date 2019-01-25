/*
 * takeoff.cpp
 *
 *  Created on: 02/01/2019
 *      Author: falmeida
 *      Código para efetuar takeoff do drone TarotX6 HEIFU
 *     
 */
#include <ros/ros.h>
#include <mav_msgs/CommandMotorSpeed.h>
#include <std_msgs/Float64.h>
#include <sstream>


int main(int argc, char **argv)
{
	ros::init(argc, argv, "takeoff");
	ros::NodeHandle nh;
	double var = 0.0;
	float velocidade = 0.0;


	ros::Publisher pub = nh.advertise<mav_msgs::CommandMotorSpeed>("/myfirst/gazebo/command/motor_speed", 10);
	ros::Rate loopRate(10);
	mav_msgs::CommandMotorSpeed rotor_vel_msg;
	rotor_vel_msg.motor_speed = {0, 0, 0, 0, 0, 0};


	while (ros::ok())
	{
		nh.param<double>("/takeoff/var", var, 0.0);
		
		if(var == 1.0)
		{
			//sleep(5);
			//ROS_INFO("ENTROU: %f ", var);

			rotor_vel_msg.motor_speed = {500, 500, 500, 500, 500, 500};
			pub.publish(rotor_vel_msg);
			sleep(2);
			nh.setParam("/takeoff/var", 0.0);
			//ROS_INFO("SAIU: %f ", var);
			rotor_vel_msg.motor_speed = {0, 0, 0, 0, 0, 0};
			pub.publish(rotor_vel_msg);
			
		}
		else
		{
			//ROS_INFO("ESTA FORA: %f ", var);
			rotor_vel_msg.motor_speed = {0, 0, 0, 0, 0, 0};
			
		}

		pub.publish(rotor_vel_msg);
		//controle de loop
		ros::spinOnce();
		loopRate.sleep();
		//count++;
	}

	return 0;
}
