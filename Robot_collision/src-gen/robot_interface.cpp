#include "Robot_v1.h"
#include <iostream>
#include <fstream>

using namespace std;

enum Comm_Packets{
	No_Message = 0, Cloud_Online = 1, Robot_Online = 2, Dead_End = 3, Path_sended = 4
};

class RobotComm : public Robot_v1::SCI_Comm_OCB{
public:	
	sc_integer sendMessage(sc_integer s1, sc_integer x = 0, sc_integer y = 0) {
		ofstream myfile;
		myfile.open("sendToCloud.txt");
		if(myfile.is_open()){
			myfile << s1 << " " << (int)x << " " << (int)y << endl;
			myfile.close();
			return 1;
		}
		else return 0;
	}
	
	sc_integer waitMessage(){
		ifstream myfile;
		int output = 0;
		myfile.open("msgFromCloud.txt");
		if(myfile.is_open()){
			char message = '0';
			
			myfile.get(message);
			if(message >= '0' && message <= '4'){
				output = (int) (message-'0');
			}
			myfile.close();
		}
		return output;
	}

	sc_integer getInitX(){

	}
				
	sc_integer getInitY(){

	}
	
	sc_integer getMapX(){

	}
	
	sc_integer getMapY(){

	}
	
	sc_integer getGoalX(){

	}
	
	sc_integer getGoalY(){

	}
				
	
	sc_string getPath(){

	}
};

class RobotSensor : public SCI_Sensor_OCB {
	public:		
		sc_boolean updateUp(sc_integer x, sc_integer y) {

		}
		
		sc_boolean updateDown(sc_integer x, sc_integer y) {

		}
		
		sc_boolean updateLeft(sc_integer x, sc_integer y) {

		}
		
		sc_boolean updateRight(sc_integer x, sc_integer y){

		}
};

class RobotUtility : public InternalSCI_OCB {
public:
	
	sc_integer getStep(sc_string path, sc_integer i) {

	}
};

int main()
{
	Robot_v1 robot_obj;
	RobotComm robot_comm;
	RobotSensor robot_sensor;
	RobotUtility robot_util;

	setSCI_Comm_OCB(&robot_comm);
	setSCI_Sensor_OCB(&robot_sensor);
	setInternalSCI_OCB(robot_util);

	robot_obj
  	return 0;
}