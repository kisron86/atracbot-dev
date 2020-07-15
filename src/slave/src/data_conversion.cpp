#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Range.h"
#include <std_msgs/Float64.h>
#include <iostream>

using namespace std;

static double jarakcm;
static int persen_level, persen_v_mtr, persen_v_pc;
static double v_motor, v_pc,i_motor,i_pc;

void baca_v_motor (const std_msgs::Float64::ConstPtr& v_motor_data)
{
  v_motor = v_motor_data->data;

  if (v_motor < 11.60){ persen_v_mtr = 0; }
    else if (v_motor < 11.70 && v_motor > 11.60){ persen_v_mtr = 10; }
    else if (v_motor < 11.80 && v_motor > 11.70){ persen_v_mtr = 20; }
    else if (v_motor < 11.90 && v_motor > 11.80){ persen_v_mtr = 30; }
    else if (v_motor < 12.00 && v_motor > 11.90){ persen_v_mtr = 40; }
    else if (v_motor < 12.10 && v_motor > 12.00){ persen_v_mtr = 50; }
    else if (v_motor < 12.20 && v_motor > 12.10){ persen_v_mtr = 60; }
    else if (v_motor < 12.30 && v_motor > 12.20){ persen_v_mtr = 70; }
    else if (v_motor < 12.40 && v_motor > 12.30){ persen_v_mtr = 80; }
    else if (v_motor < 12.50 && v_motor > 12.40){ persen_v_mtr = 90; }
    else if (v_motor < 12.60&& v_motor > 12.50){ persen_v_mtr = 100; }
    else { persen_v_mtr = 0; }
}

void baca_v_pc (const std_msgs::Float64::ConstPtr& v_pc_data)
{
  v_pc = v_pc_data->data;

  if (v_pc < 11.60){ persen_v_pc = 0; }
    else if (v_pc < 11.70 && v_pc > 11.60){ persen_v_pc = 10; }
    else if (v_pc < 11.80 && v_pc > 11.70){ persen_v_pc = 20; }
    else if (v_pc < 11.90 && v_pc > 11.80){ persen_v_pc = 30; }
    else if (v_pc < 12.00 && v_pc > 11.90){ persen_v_pc = 40; }
    else if (v_pc < 12.10 && v_pc > 12.00){ persen_v_pc = 50; }
    else if (v_pc < 12.20 && v_pc > 12.10){ persen_v_pc = 60; }
    else if (v_pc < 12.30 && v_pc > 12.20){ persen_v_pc = 70; }
    else if (v_pc < 12.40 && v_pc > 12.30){ persen_v_pc = 80; }
    else if (v_pc < 12.50 && v_pc > 12.40){ persen_v_pc = 90; }
    else if (v_pc < 12.60&& v_pc > 12.50){ persen_v_pc = 100; }
    else { persen_v_pc = 0; }

}
void baca_i_motor (const std_msgs::Float64::ConstPtr& i_motor_data)
{
  i_motor = i_motor_data->data;
}
void baca_i_pc (const std_msgs::Float64::ConstPtr& i_pc_data)
{
  i_pc = i_pc_data->data;
}

void Baca_jarak(const sensor_msgs::Range::ConstPtr& us_data)
{
  float jarakcmtmp = us_data->range;
  jarakcm = (jarakcmtmp*-1)+35;
  //printf("jarak new:%.2f\n",jarakcm);
  if(jarakcm > 0.0 && jarakcm < 1.0){persen_level = 0;}
  else if(jarakcm > 1.0 && jarakcm < 2.0){persen_level = 3;}
  else if(jarakcm > 2.0 && jarakcm < 3.0){persen_level = 6;}
  else if(jarakcm > 3.0 && jarakcm < 4.0){persen_level = 9;}
  else if(jarakcm > 4.0 && jarakcm < 5.0){persen_level = 12;}
  else if(jarakcm > 5.0 && jarakcm < 6.0){persen_level = 15;}
  else if(jarakcm > 6.0 && jarakcm < 7.0){persen_level = 18;}
  else if(jarakcm > 7.0 && jarakcm < 8.0){persen_level = 21;}
  else if(jarakcm > 8.0 && jarakcm < 9.0){persen_level = 24;}
  else if(jarakcm > 9.0 && jarakcm < 10.0){persen_level = 27;}
  else if(jarakcm > 10.0 && jarakcm < 11.0){persen_level = 30;}
  else if(jarakcm > 11.0 && jarakcm < 12.0){persen_level = 33;}
  else if(jarakcm > 12.0 && jarakcm < 13.0){persen_level = 36;}
  else if(jarakcm > 13.0 && jarakcm < 14.0){persen_level = 39;}
  else if(jarakcm > 14.0 && jarakcm < 15.0){persen_level = 42;}
  else if(jarakcm > 15.0 && jarakcm < 16.0){persen_level = 45;}
  else if(jarakcm > 16.0 && jarakcm < 17.0){persen_level = 48;}
  else if(jarakcm > 17.0 && jarakcm < 18.0){persen_level = 51;}
  else if(jarakcm > 18.0 && jarakcm < 19.0){persen_level = 54;}
  else if(jarakcm > 19.0 && jarakcm < 20.0){persen_level = 57;}
  else if(jarakcm > 20.0 && jarakcm < 21.0){persen_level = 60;}
  else if(jarakcm > 21.0 && jarakcm < 22.0){persen_level = 63;}
  else if(jarakcm > 22.0 && jarakcm < 23.0){persen_level = 66;}
  else if(jarakcm > 23.0 && jarakcm < 24.0){persen_level = 69;}
  else if(jarakcm > 24.0 && jarakcm < 25.0){persen_level = 72;}
  else if(jarakcm > 25.0 && jarakcm < 26.0){persen_level = 75;}
  else if(jarakcm > 26.0 && jarakcm < 27.0){persen_level = 78;}
  else if(jarakcm > 27.0 && jarakcm < 28.0){persen_level = 81;}
  else if(jarakcm > 28.0 && jarakcm < 29.0){persen_level = 84;}
  else if(jarakcm > 29.0 && jarakcm < 30.0){persen_level = 87;}
  else if(jarakcm > 30.0 && jarakcm < 31.0){persen_level = 90;}
  else if(jarakcm > 31.0 && jarakcm < 32.0){persen_level = 93;}
  else if(jarakcm > 32.0 && jarakcm < 33.0){persen_level = 96;}
  else if(jarakcm > 33.0 && jarakcm < 34.0){persen_level = 99;}
  else if(jarakcm > 34.0){persen_level = 100;}
  //printf("level : %d persen\n",persen_level);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "data_conversion");
  ros::NodeHandle nh;
  ros::Subscriber sub1 = nh.subscribe("us_topic", 1000, Baca_jarak);
  ros::Subscriber sub2 = nh.subscribe("v_motor_topic", 1000, baca_v_motor);
  ros::Subscriber sub3 = nh.subscribe("v_pc_topic", 1000, baca_v_pc);
  ros::Subscriber sub4 = nh.subscribe("i_motor_topic", 1000, baca_i_motor);
  ros::Subscriber sub5 = nh.subscribe("i_pc_topic", 1000, baca_i_pc);
  ros::Rate loop_rate(1);

  while(ros::ok()){
    //cout << "v_motor" << v_motor << endl;
    //printf("v_motor=[%.2f]->v_pc=[%.2f]->i_mtr=[%.2f]->i_pc=[%.2f]->us=[%.2f]\n",v_motor,v_pc,i_motor,i_pc,jarakcm);
    printf("persen : v_motor=%d->v_pc=%d->us=%d\n",persen_v_mtr,persen_v_pc,persen_level);
    
    ros::spinOnce();
    loop_rate.sleep();
}
  ros::spin();


  return 0;
}
