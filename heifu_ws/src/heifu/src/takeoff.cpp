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
#include <sensor_msgs/Imu.h>

ros::Publisher pub;

void chatterCallback(const sensor_msgs::Imu::ConstPtr& msg)
{
	float x = msg->orientation.x;
	float y = msg->orientation.y;
	float z = msg->orientation.z;

	float velEstab = 491.0;
	float erro = 0.01;
	float erro2 = -0.01;
	float acao = 10.0;
	
	float velXpos = velEstab;
	float velXneg = velEstab;
	float velYpos = velEstab;
	float velYneg = velEstab;

	//ROS_INFO("Imu Seq: x= %f // y= %f // z= %f", x, y, z);


	
	mav_msgs::CommandMotorSpeed rotor_vel_msg;
	rotor_vel_msg.motor_speed = {velYpos, velXneg, velXpos, velYneg, velXneg, velXpos};
	
	if(x > erro)
	{
		velXpos = velXpos + acao*x;
		velXneg = velXneg - acao*x;
	}
	else if(x < erro2)
	{
		velXpos = velXpos - (acao*x*(-1));
		velXneg = velXneg + (acao*x*(-1));
	}
	
	if(y > erro)
	{
		velYpos = velYpos + acao*y;
		velYneg = velYneg - acao*y;
	}
	else if(y < erro2)
	{
		velYpos = velYpos - (acao*y*(-1));
		velYneg = velYneg + (acao*y*(-1));
	}

	rotor_vel_msg.motor_speed = {velYpos, velXneg, velXpos, velYneg, velXneg, velXpos};
	pub.publish(rotor_vel_msg);


}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "takeoff");
	ros::NodeHandle nh;
	double var = 0.0;
	float velTakeoff = 500.0;
	float velEstab = 480.0;

	float velXpos = velTakeoff;
	float velXneg = velTakeoff;

	float velYpos = velTakeoff;
	float velYneg = velTakeoff;
	
	ros::Subscriber sub = nh.subscribe("/imu", 1000, chatterCallback);
	pub = nh.advertise<mav_msgs::CommandMotorSpeed>("/myfirst/gazebo/command/motor_speed", 10);

	mav_msgs::CommandMotorSpeed rotor_vel_msg;
	rotor_vel_msg.motor_speed = {0, 0, 0, 0, 0, 0};

	nh.param<double>("/takeoff/var", var, 0.0);
	
	if(var == 0.0)
	{

		sleep(5);
		rotor_vel_msg.motor_speed = {velYpos, velXneg, velXpos, velYneg, velXneg, velXpos};
		pub.publish(rotor_vel_msg);
		sleep(2);
		nh.setParam("/takeoff/var", 1.0);

		velXpos = velEstab;
		velXneg = velEstab;
		velYpos = velEstab;
		velYneg = velEstab;

		rotor_vel_msg.motor_speed = {velYpos, velXneg, velXpos, velYneg, velXneg, velXpos};
		pub.publish(rotor_vel_msg);
			
	}

	ros::spin();
/*
	double var = 0.0;
	float velocidade = 0.0;
	

	
	ros::Rate loopRate(10);
	

	



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
*/
	return 0;
}
