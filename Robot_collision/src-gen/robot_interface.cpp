#include "Robot_v1.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <list>
#include <iterator>
#include <utility>
#include <pthread.h>
//#include <boost/thread/thread.hpp>
#include "TimerInterface.h"
#include "sc_types.h"


using namespace std;

enum Comm_Packets{
	No_Message = 0, Cloud_Online = 1, Robot_Online = 2, Dead_End = 3, Path_sended = 4
};

char* mtx;
int n, m;
string path;

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

	
	int init_x, init_y, goal_x, goal_y;
  
	void process_data(){
		ifstream myfile;
		myfile.open("Map.txt");
		if(myfile.is_open()){
			string temp;
			getline(myfile,temp);
			n = (int)(temp[0]-'0');
			m = (int)(temp[2]-'0');
			//Map (mátrix) feldolgozás
			getline(myfile,temp);
			mtx = new char[n*m];
			int j=0;
			for(unsigned int i=0;temp[i]!='\n';i++){
				if(temp[i] == '\n') temp[i]='\0';
			}
			for(unsigned int i=0;i<temp.size();i++){
				if(temp[i] != ',') mtx[j++] = temp[i];
			}

			getline(myfile,temp);
			init_x = (int)(temp[0]-'0');
			init_y = (int)(temp[2]-'0');

			getline(myfile, temp);
			goal_x = (int)(temp[0]-'0');
			goal_y = (int)(temp[2]-'0');
			myfile.close();			
		}
	}

	void process_help(){
		ifstream myfile;
		myfile.open("Path.txt");
		if(myfile.is_open()){
			int db=0;
			string temp;
			getline(myfile,temp);
			temp = temp + "0";
			for(unsigned int i = 0;i<temp.size();i++) if(temp[i] >= '0' && temp[i] <= '4') db++;
			char* out = new char[db];
			int j=0;
			for(unsigned int i=1;i<temp.size();i++){
				if(temp[i] !=',') out[j++] = temp[i];
			}
			myfile.close();
			path = string(out);
			delete out;
		}
	}
	
	sc_integer waitMessage(){
		ifstream myfile;
		int output = 0;
		myfile.open("msgFromCloud.txt");
		if(myfile.is_open()){
			char message = '0';
			
			myfile.get(message);
			if(message == '1') process_data();
			if(message == '4') process_help();
			if(message >= '0' && message <= '4'){
				output = (int) (message-'0');
			}
			myfile.close();
		}
		return output;
	}

	sc_integer getInitX(){
		return init_x;
	}
				
	sc_integer getInitY(){
		return init_y;
	}
	
	sc_integer getMapX(){
		return n;
	}
	
	sc_integer getMapY(){
		return m;
	}
	
	sc_integer getGoalX(){
		return goal_x;
	}
	
	sc_integer getGoalY(){
		return goal_y;
	}
};

class RobotSensor : public Robot_v1::SCI_Sensor_OCB {
	public:		
		
		sc_boolean updateUp(sc_integer x, sc_integer y) {
			if(y == 0) return true;
			return (mtx[(int) (y*(n-1)+x)] == '1');
		}
		
		sc_boolean updateDown(sc_integer x, sc_integer y) {
			if(y == (m-1)) return true;
			return (mtx[(int)(y*(n+1)+x)] == '1');
		}
		
		sc_boolean updateLeft(sc_integer x, sc_integer y) {
			if(x == 0) return true;
			return (mtx[(int)(y*n+x-1)] == '1');
		}
		
		sc_boolean updateRight(sc_integer x, sc_integer y){
			if(x == n-1) return true;
			return (mtx[(int)(y*n+x+1)] == '1');
		}
};

class RobotUtility : public Robot_v1::InternalSCI_OCB {
public:
	
	sc_integer getStep(sc_integer i) {
		sc_integer len = path.size();
		if(i<len) return (int)(path[i]-'0');
		else return 0;
	}
};

class RobotTimerInterface : public TimerInterface {
	public:	
		pthread_t thread;
		
		RobotTimerInterface(){
			runnable = true;
			terminate = false;
			//TimerLoop th;
			//t1 = boost::thread(th,this);
			pthread_create(&thread,NULL,timerLoop,this);
		}

		/*
		 * Starts the timing for a time event.
		 */ 
		void setTimer(TimedStatemachineInterface* statemachine, sc_eventid event, sc_integer interval, sc_boolean isPeriodic) {
			clock_t now = clock();
			TimePair newTimer(now, interval);
			SMEvent newSMEvent(statemachine, event);
			EventTimer newEventTimer(newSMEvent,newTimer);
			timerList.insert(timerList.end(),newEventTimer);
		}
		
		/*
		 * Unsets the given time event.
		 */
		void unsetTimer(TimedStatemachineInterface* statemachine, sc_eventid event){
			if(event != NULL){
				runnable = false;
				pthread_join(thread,NULL);
				for(std::list<EventTimer>::iterator t = timerList.begin();t!=timerList.end();++t){
					if(t->first.second == event) {					
						timerList.erase(t);
					}
				}
				*(sc_boolean*)event = false;
				runnable=true;
				//TimerLoop th;
				//t1 = boost::thread(th,this);
				pthread_create(&thread,NULL,timerLoop,this);
			}
		}
	
		/*
		 * Cancel timer service. Use this to end possible timing threads and free
		 * memory resources.
		 */
		void cancel(){
			terminate = true;
			pthread_join(thread,NULL);
		}
		
		void* timerLoop(RobotTimerInterface* interF){
			while(interF->runnable && !(interF->terminate)){
				for(std::list<EventTimer>::iterator t = interF->timerList.begin();t!=interF->timerList.end();++t){
					if(!(interF->runnable)) break;
					EventTimer tempEvent = (*t);
					SMEvent tempSMEvent = tempEvent.first;
					TimedStatemachineInterface * statemachine = tempSMEvent.first;
					sc_eventid eventId = tempSMEvent.second;

					TimePair tempTimer = tempEvent.second;
					clock_t start = tempTimer.first;
					sc_integer interval = tempTimer.second;

					clock_t now = clock();
					if(now > (start + interval)) statemachine->raiseTimeEvent(eventId);
				}
			}
			pthread_exit(NULL);
		}
		

		typedef pair<clock_t, sc_integer> TimePair;
		typedef pair<TimedStatemachineInterface*,sc_eventid> SMEvent;
		typedef pair<SMEvent, TimePair> EventTimer;

		std::list<EventTimer> timerList;
		bool runnable;
		bool terminate; 

	private:
		
		//boost::thread t1;
};

static RobotTimerInterface staticCreator;

int main()
{
	Robot_v1 robot_obj;
	RobotComm robot_comm;
	RobotSensor robot_sensor;
	RobotUtility robot_util;

	robot_obj.setSCI_Comm_OCB(&robot_comm);
	robot_obj.setSCI_Sensor_OCB(&robot_sensor);
	robot_obj.setInternalSCI_OCB(&robot_util);

	try{
		std::cout << "Objektumok letrejottek" << std::endl;
		robot_obj.init();
		robot_obj.enter();
		robot_obj.runCycle();
	}
	catch(std::exception e){
		std::cout << e.what() << std::endl;
	}

  	return 0;
}

/*
switch (state){
		case main_region_Start:
		std::cout << "main_region_Start"<< std::endl;
			break;
		case main_region_Comm_test:
		std::cout <<"main_region_Comm_test" << std::endl;
			break;
		case main_region_Comm_test_Comm_test_sd_Start:
		std::cout << "main_region_Comm_test_Comm_test_sd_Start"<< std::endl;
			break;
		case main_region_Comm_test_Comm_test_sd_WaitForCloud:
		std::cout << "main_region_Comm_test_Comm_test_sd_WaitForCloud"<< std::endl;
			break;
		case main_region_Comm_test_Comm_test_sd_Link_Established:
		std::cout << "main_region_Comm_test_Comm_test_sd_Link_Established"<< std::endl;
			break;
		case main_region_Robot_Logic:
		std::cout << "main_region_Robot_Logic"<< std::endl;
			break;
		case main_region_Robot_Logic_Robot_Logic_sd_Init:
		std::cout << "main_region_Robot_Logic_Robot_Logic_sd_Init"<< std::endl;
			break;
		case main_region_Robot_Logic_Robot_Logic_sd_Sensor_update:
		std::cout << "main_region_Robot_Logic_Robot_Logic_sd_Sensor_update"<< std::endl;
			break;
		case main_region_Robot_Logic_Robot_Logic_sd_Up:
		std::cout << "main_region_Robot_Logic_Robot_Logic_sd_Up"<< std::endl;
			break;
		case main_region_Robot_Logic_Robot_Logic_sd_Right:
		std::cout << "main_region_Robot_Logic_Robot_Logic_sd_Right"<< std::endl;
			break;
		case main_region_Robot_Logic_Robot_Logic_sd_Check_goals:
		std::cout << "main_region_Robot_Logic_Robot_Logic_sd_Check_goals"<< std::endl;
			break;
		case main_region_Robot_Logic_Robot_Logic_sd_DeadEnd:
		std::cout << "main_region_Robot_Logic_Robot_Logic_sd_DeadEnd"<< std::endl;
			break;
		case main_region_Robot_Logic_Robot_Logic_sd__final_:
		std::cout <<"main_region_Robot_Logic_Robot_Logic_sd__final_" << std::endl;
			break;
		case main_region_Help_from_Cloud:
		std::cout <<"main_region_Help_from_Cloud" << std::endl;
			break;
		case main_region_Help_from_Cloud_Help_from_Cloud_sd_Send:
		std::cout <<"main_region_Help_from_Cloud_Help_from_Cloud_sd_Send" << std::endl;
			break;
		case main_region_Help_from_Cloud_Help_from_Cloud_sd_Wait_for_Message:
		std::cout <<"main_region_Help_from_Cloud_Help_from_Cloud_sd_Wait_for_Message" << std::endl;
			break;
		case main_region_Help_from_Cloud_Help_from_Cloud_sd_Help_received:
		std::cout <<"main_region_Help_from_Cloud_Help_from_Cloud_sd_Help_received" << std::endl;
			break;
		case main_region_Path_Walking:
		std::cout <<"main_region_Path_Walking" << std::endl;
			break;
		case main_region_Path_Walking_Path_Walking_sd_Sensor_update:
		std::cout << "main_region_Path_Walking_Path_Walking_sd_Sensor_update"<< std::endl;
			break;
		case main_region_Path_Walking_Path_Walking_sd_Next_Step:
		std::cout <<"main_region_Path_Walking_Path_Walking_sd_Next_Step" << std::endl;
			break;
		case main_region_Path_Walking_Path_Walking_sd_Init:
		std::cout <<"ain_region_Path_Walking_Path_Walking_sd_Init" << std::endl;
			break;
		case main_region_Path_Walking_Path_Walking_sd_Up:
		std::cout << "main_region_Path_Walking_Path_Walking_sd_Up"<< std::endl;
			break;
		case main_region_Path_Walking_Path_Walking_sd_Right:
		std::cout <<"ain_region_Path_Walking_Path_Walking_sd_Right" << std::endl;
			break;
		case main_region_Path_Walking_Path_Walking_sd_Down:
		std::cout <<"main_region_Path_Walking_Path_Walking_sd_Down" << std::endl;
			break;
		case main_region_Path_Walking_Path_Walking_sd_Left:
		std::cout <<"main_region_Path_Walking_Path_Walking_sd_Left" << std::endl;
			break;
		case Robot_Logic_Control_Wait_for_Command:
		std::cout << "Robot_Logic_Control_Wait_for_Command"<< std::endl;
			break;
		case Robot_Logic_Control_Go_Up:
		std::cout << "Robot_Logic_Control_Go_Up"<< std::endl;
			break;
		case Robot_Logic_Control_Go_Down:
		std::cout <<"Robot_Logic_Control_Go_Down" << std::endl;
			break;
		case Robot_Logic_Control_Go_Left:
		std::cout << "Robot_Logic_Control_Go_Left"<< std::endl;
			break;
		case Robot_Logic_Control_Go_Right:
		std::cout <<"Robot_Logic_Control_Go_Right" << std::endl;
			break;
		case Robot_v1_last_state:
		std::cout <<"Robot_v1_last_state" << std::endl;
			break;
	}
*/