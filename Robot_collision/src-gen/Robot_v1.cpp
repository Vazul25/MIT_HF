
#include "Robot_v1.h"
#include <string.h>
#include <iostream>
#include <exception>
/*! \file Implementation of the state machine 'robot_v1'
*/

Robot_v1::Robot_v1() {
	
	ifaceComm_OCB = null;
	ifaceSensor_OCB = null;
	ifaceInternalSCI_OCB = null;
	
	for (int i = 0; i < maxHistoryStates; ++i)
		historyVector[i] = Robot_v1_last_state;
	
	stateConfVectorPosition = 0;
	
	timer = NULL;
}

Robot_v1::~Robot_v1() {
}

void Robot_v1::init()
{
	for (int i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = Robot_v1_last_state;
	
	for (int i = 0; i < maxHistoryStates; ++i)
		historyVector[i] = Robot_v1_last_state;
	
	stateConfVectorPosition = 0;

	clearInEvents();
	clearOutEvents();
	
	/* Default init sequence for statechart robot_v1 */
	ifaceComm.message = 0;
	ifaceComm.comm = false;
	ifaceSensor.up = false;
	ifaceSensor.down = false;
	ifaceSensor.left = false;
	ifaceSensor.right = false;
	ifaceInternalSCI.init_x = 0;
	ifaceInternalSCI.init_y = 0;
	ifaceInternalSCI.map_x = 5;
	ifaceInternalSCI.map_y = 5;
	ifaceInternalSCI.goal_x = 2;
	ifaceInternalSCI.goal_y = 2;
	ifaceInternalSCI.pos_x = 0;
	ifaceInternalSCI.pos_y = 0;
	ifaceInternalSCI.nextStep = 0;
	ifaceInternalSCI.index = 0;
	std::cout << "Init rendben" << std::endl;

}

void Robot_v1::enter()
{
	try{
		std::cout << "Enter" << std::endl;
		/* Default enter sequence for statechart robot_v1 */
		enact_SequenceImpl();
		/* 'default' enter sequence for region main region */
		/* Default react sequence for initial entry  */
		/* 'default' enter sequence for state Start */
		/* Entry action for state 'Start'. */
		std::cout << "Enter Timer init" << std::endl;
		timer->setTimer(this, &timeEvents[0], 1 * 1000, false);
		stateConfVector[0] = main_region_Start;
		stateConfVectorPosition = 0;
		std::cout << "Timer Okay" << std::endl;
		/* 'default' enter sequence for region Robot_Logic_Control */
		/* Default react sequence for initial entry  */
		/* 'default' enter sequence for state Wait_for Command */
		stateConfVector[1] = Robot_Logic_Control_Wait_for_Command;
		stateConfVectorPosition = 1;
		std::cout << "Enter Okay" << std::endl;
	}
	catch(std::exception e){
		std::cout <<"My Exception Handler: " << e.what() << std::endl;
	}
}

void Robot_v1::exit()
{
	std::cout << "Exit Init" << std::endl;
	/* Default exit sequence for statechart robot_v1 */
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of main region) at position 0... */
	switch(stateConfVector[ 0 ]) {
		case main_region_Start : {
			/* Default exit sequence for state Start */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			/* Exit action for state 'Start'. */
			timer->unsetTimer(this, &timeEvents[0]);
			break;
		}
		case main_region_Comm_test_Comm_test_sd_Start : {
			/* Default exit sequence for state Start */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		case main_region_Comm_test_Comm_test_sd_WaitForCloud : {
			/* Default exit sequence for state WaitForCloud */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			/* Exit action for state 'WaitForCloud'. */
			timer->unsetTimer(this, &timeEvents[1]);
			break;
		}
		case main_region_Comm_test_Comm_test_sd_Link_Established : {
			/* Default exit sequence for state Link_Established */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Init : {
			/* Default exit sequence for state Init */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Sensor_update : {
			/* Default exit sequence for state Sensor_update */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Up : {
			/* Default exit sequence for state Up */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			/* Exit action for state 'Up'. */
			timer->unsetTimer(this, &timeEvents[2]);
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Right : {
			/* Default exit sequence for state Right */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			/* Exit action for state 'Right'. */
			timer->unsetTimer(this, &timeEvents[3]);
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Check_goals : {
			/* Default exit sequence for state Check_goals */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_DeadEnd : {
			/* Default exit sequence for state DeadEnd */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd__final_ : {
			/* Default exit sequence for final state. */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		case main_region_Help_from_Cloud_Help_from_Cloud_sd_Send : {
			/* Default exit sequence for state Send */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		case main_region_Help_from_Cloud_Help_from_Cloud_sd_Wait_for_Message : {
			/* Default exit sequence for state Wait_for_Message */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			/* Exit action for state 'Wait_for_Message'. */
			timer->unsetTimer(this, &timeEvents[4]);
			break;
		}
		case main_region_Help_from_Cloud_Help_from_Cloud_sd_Help_received : {
			/* Default exit sequence for state Help_received */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		case main_region_Path_Walking_Path_Walking_sd_Sensor_update : {
			/* Default exit sequence for state Sensor_update */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		case main_region_Path_Walking_Path_Walking_sd_Next_Step : {
			/* Default exit sequence for state Next_Step */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		case main_region_Path_Walking_Path_Walking_sd_Init : {
			/* Default exit sequence for state Init */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			/* Exit action for state 'Init'. */
			timer->unsetTimer(this, &timeEvents[5]);
			break;
		}
		case main_region_Path_Walking_Path_Walking_sd_Up : {
			/* Default exit sequence for state Up */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			/* Exit action for state 'Up'. */
			timer->unsetTimer(this, &timeEvents[6]);
			break;
		}
		case main_region_Path_Walking_Path_Walking_sd_Right : {
			/* Default exit sequence for state Right */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			/* Exit action for state 'Right'. */
			timer->unsetTimer(this, &timeEvents[7]);
			break;
		}
		case main_region_Path_Walking_Path_Walking_sd_Down : {
			/* Default exit sequence for state Down */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			/* Exit action for state 'Down'. */
			timer->unsetTimer(this, &timeEvents[8]);
			break;
		}
		case main_region_Path_Walking_Path_Walking_sd_Left : {
			/* Default exit sequence for state Left */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			/* Exit action for state 'Left'. */
			timer->unsetTimer(this, &timeEvents[9]);
			break;
		}
		default: break;
	}
	/* Default exit sequence for region Robot_Logic_Control */
	/* Handle exit of all possible states (of Robot_Logic_Control) at position 1... */
	switch(stateConfVector[ 1 ]) {
		case Robot_Logic_Control_Wait_for_Command : {
			/* Default exit sequence for state Wait_for Command */
			stateConfVector[1] = Robot_v1_last_state;
			stateConfVectorPosition = 1;
			break;
		}
		case Robot_Logic_Control_Go_Up : {
			/* Default exit sequence for state Go_Up */
			stateConfVector[1] = Robot_v1_last_state;
			stateConfVectorPosition = 1;
			/* Exit action for state 'Go_Up'. */
			timer->unsetTimer(this, &timeEvents[10]);
			break;
		}
		case Robot_Logic_Control_Go_Down : {
			/* Default exit sequence for state Go_Down */
			stateConfVector[1] = Robot_v1_last_state;
			stateConfVectorPosition = 1;
			/* Exit action for state 'Go_Down'. */
			timer->unsetTimer(this, &timeEvents[11]);
			break;
		}
		case Robot_Logic_Control_Go_Left : {
			/* Default exit sequence for state Go_Left */
			stateConfVector[1] = Robot_v1_last_state;
			stateConfVectorPosition = 1;
			/* Exit action for state 'Go_Left'. */
			timer->unsetTimer(this, &timeEvents[12]);
			break;
		}
		case Robot_Logic_Control_Go_Right : {
			/* Default exit sequence for state Go_Right */
			stateConfVector[1] = Robot_v1_last_state;
			stateConfVectorPosition = 1;
			/* Exit action for state 'Go_Right'. */
			timer->unsetTimer(this, &timeEvents[13]);
			break;
		}
		default: break;
	}
	exact_SequenceImpl();
}

void Robot_v1::runCycle() {
	std::cout << "RunCycle Init" << std::endl;
	
	clearOutEvents();
	
	for (stateConfVectorPosition = 0;
		stateConfVectorPosition < maxOrthogonalStates;
		stateConfVectorPosition++) {
		
		std::cout << "state: " << stateConfVector[stateConfVectorPosition] << std::endl;

		switch (stateConfVector[stateConfVectorPosition]){
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
			
		switch (stateConfVector[stateConfVectorPosition]) {
		case main_region_Start : {
			react_main_region_Start();
			break;
		}
		case main_region_Comm_test_Comm_test_sd_Start : {
			react_main_region_Comm_test_Comm_test_sd_Start();
			break;
		}
		case main_region_Comm_test_Comm_test_sd_WaitForCloud : {
			react_main_region_Comm_test_Comm_test_sd_WaitForCloud();
			break;
		}
		case main_region_Comm_test_Comm_test_sd_Link_Established : {
			react_main_region_Comm_test_Comm_test_sd_Link_Established();
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Init : {
			react_main_region_Robot_Logic_Robot_Logic_sd_Init();
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Sensor_update : {
			react_main_region_Robot_Logic_Robot_Logic_sd_Sensor_update();
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Up : {
			react_main_region_Robot_Logic_Robot_Logic_sd_Up();
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Right : {
			react_main_region_Robot_Logic_Robot_Logic_sd_Right();
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Check_goals : {
			react_main_region_Robot_Logic_Robot_Logic_sd_Check_goals();
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_DeadEnd : {
			react_main_region_Robot_Logic_Robot_Logic_sd_DeadEnd();
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd__final_ : {
			react_main_region_Robot_Logic_Robot_Logic_sd__final_();
			break;
		}
		case main_region_Help_from_Cloud_Help_from_Cloud_sd_Send : {
			react_main_region_Help_from_Cloud_Help_from_Cloud_sd_Send();
			break;
		}
		case main_region_Help_from_Cloud_Help_from_Cloud_sd_Wait_for_Message : {
			react_main_region_Help_from_Cloud_Help_from_Cloud_sd_Wait_for_Message();
			break;
		}
		case main_region_Help_from_Cloud_Help_from_Cloud_sd_Help_received : {
			react_main_region_Help_from_Cloud_Help_from_Cloud_sd_Help_received();
			break;
		}
		case main_region_Path_Walking_Path_Walking_sd_Sensor_update : {
			react_main_region_Path_Walking_Path_Walking_sd_Sensor_update();
			break;
		}
		case main_region_Path_Walking_Path_Walking_sd_Next_Step : {
			react_main_region_Path_Walking_Path_Walking_sd_Next_Step();
			break;
		}
		case main_region_Path_Walking_Path_Walking_sd_Init : {
			react_main_region_Path_Walking_Path_Walking_sd_Init();
			break;
		}
		case main_region_Path_Walking_Path_Walking_sd_Up : {
			react_main_region_Path_Walking_Path_Walking_sd_Up();
			break;
		}
		case main_region_Path_Walking_Path_Walking_sd_Right : {
			react_main_region_Path_Walking_Path_Walking_sd_Right();
			break;
		}
		case main_region_Path_Walking_Path_Walking_sd_Down : {
			react_main_region_Path_Walking_Path_Walking_sd_Down();
			break;
		}
		case main_region_Path_Walking_Path_Walking_sd_Left : {
			react_main_region_Path_Walking_Path_Walking_sd_Left();
			break;
		}
		case Robot_Logic_Control_Wait_for_Command : {
			react_Robot_Logic_Control_Wait_for_Command();
			break;
		}
		case Robot_Logic_Control_Go_Up : {
			react_Robot_Logic_Control_Go_Up();
			break;
		}
		case Robot_Logic_Control_Go_Down : {
			react_Robot_Logic_Control_Go_Down();
			break;
		}
		case Robot_Logic_Control_Go_Left : {
			react_Robot_Logic_Control_Go_Left();
			break;
		}
		case Robot_Logic_Control_Go_Right : {
			react_Robot_Logic_Control_Go_Right();
			break;
		}
		default:
			break;
		}
	}
	
	clearInEvents();
	std::cout << "runCycle Okay" << std::endl;
}

void Robot_v1::clearInEvents() {
	ifaceComm.message_received_raised = false;
	ifaceControl.goUp_raised = false;
	ifaceControl.goDown_raised = false;
	ifaceControl.goLeft_raised = false;
	ifaceControl.goRight_raised = false;
	ifaceInternalSCI.PathReceived_raised = false; 
	ifaceInternalSCI.deadEnd_raised = false; 
	timeEvents[0] = false; 
	timeEvents[1] = false; 
	timeEvents[2] = false; 
	timeEvents[3] = false; 
	timeEvents[4] = false; 
	timeEvents[5] = false; 
	timeEvents[6] = false; 
	timeEvents[7] = false; 
	timeEvents[8] = false; 
	timeEvents[9] = false; 
	timeEvents[10] = false; 
	timeEvents[11] = false; 
	timeEvents[12] = false; 
	timeEvents[13] = false; 
}

void Robot_v1::clearOutEvents() {
	ifaceComm.message_sent_raised = false;
}


void Robot_v1::setTimer(TimerInterface* timer){
	this->timer = timer;
}

TimerInterface* Robot_v1::getTimer(){
	return timer;
}

void Robot_v1::raiseTimeEvent(sc_eventid evid) {
	if ((evid >= &timeEvents) && (evid < &timeEvents + sizeof(timeEvents))) {
		*(sc_boolean*)evid = true;
	}
}

sc_boolean Robot_v1::isActive(Robot_v1States state) {
	switch (state) {
		case main_region_Start : 
			return (sc_boolean) (stateConfVector[0] == main_region_Start
			);
		case main_region_Comm_test : 
			return (sc_boolean) (stateConfVector[0] >= main_region_Comm_test
				&& stateConfVector[0] <= main_region_Comm_test_Comm_test_sd_Link_Established);
		case main_region_Comm_test_Comm_test_sd_Start : 
			return (sc_boolean) (stateConfVector[0] == main_region_Comm_test_Comm_test_sd_Start
			);
		case main_region_Comm_test_Comm_test_sd_WaitForCloud : 
			return (sc_boolean) (stateConfVector[0] == main_region_Comm_test_Comm_test_sd_WaitForCloud
			);
		case main_region_Comm_test_Comm_test_sd_Link_Established : 
			return (sc_boolean) (stateConfVector[0] == main_region_Comm_test_Comm_test_sd_Link_Established
			);
		case main_region_Robot_Logic : 
			return (sc_boolean) (stateConfVector[0] >= main_region_Robot_Logic
				&& stateConfVector[0] <= main_region_Robot_Logic_Robot_Logic_sd__final_);
		case main_region_Robot_Logic_Robot_Logic_sd_Init : 
			return (sc_boolean) (stateConfVector[0] == main_region_Robot_Logic_Robot_Logic_sd_Init
			);
		case main_region_Robot_Logic_Robot_Logic_sd_Sensor_update : 
			return (sc_boolean) (stateConfVector[0] == main_region_Robot_Logic_Robot_Logic_sd_Sensor_update
			);
		case main_region_Robot_Logic_Robot_Logic_sd_Up : 
			return (sc_boolean) (stateConfVector[0] == main_region_Robot_Logic_Robot_Logic_sd_Up
			);
		case main_region_Robot_Logic_Robot_Logic_sd_Right : 
			return (sc_boolean) (stateConfVector[0] == main_region_Robot_Logic_Robot_Logic_sd_Right
			);
		case main_region_Robot_Logic_Robot_Logic_sd_Check_goals : 
			return (sc_boolean) (stateConfVector[0] == main_region_Robot_Logic_Robot_Logic_sd_Check_goals
			);
		case main_region_Robot_Logic_Robot_Logic_sd_DeadEnd : 
			return (sc_boolean) (stateConfVector[0] == main_region_Robot_Logic_Robot_Logic_sd_DeadEnd
			);
		case main_region_Robot_Logic_Robot_Logic_sd__final_ : 
			return (sc_boolean) (stateConfVector[0] == main_region_Robot_Logic_Robot_Logic_sd__final_
			);
		case main_region_Help_from_Cloud : 
			return (sc_boolean) (stateConfVector[0] >= main_region_Help_from_Cloud
				&& stateConfVector[0] <= main_region_Help_from_Cloud_Help_from_Cloud_sd_Help_received);
		case main_region_Help_from_Cloud_Help_from_Cloud_sd_Send : 
			return (sc_boolean) (stateConfVector[0] == main_region_Help_from_Cloud_Help_from_Cloud_sd_Send
			);
		case main_region_Help_from_Cloud_Help_from_Cloud_sd_Wait_for_Message : 
			return (sc_boolean) (stateConfVector[0] == main_region_Help_from_Cloud_Help_from_Cloud_sd_Wait_for_Message
			);
		case main_region_Help_from_Cloud_Help_from_Cloud_sd_Help_received : 
			return (sc_boolean) (stateConfVector[0] == main_region_Help_from_Cloud_Help_from_Cloud_sd_Help_received
			);
		case main_region_Path_Walking : 
			return (sc_boolean) (stateConfVector[0] >= main_region_Path_Walking
				&& stateConfVector[0] <= main_region_Path_Walking_Path_Walking_sd_Left);
		case main_region_Path_Walking_Path_Walking_sd_Sensor_update : 
			return (sc_boolean) (stateConfVector[0] == main_region_Path_Walking_Path_Walking_sd_Sensor_update
			);
		case main_region_Path_Walking_Path_Walking_sd_Next_Step : 
			return (sc_boolean) (stateConfVector[0] == main_region_Path_Walking_Path_Walking_sd_Next_Step
			);
		case main_region_Path_Walking_Path_Walking_sd_Init : 
			return (sc_boolean) (stateConfVector[0] == main_region_Path_Walking_Path_Walking_sd_Init
			);
		case main_region_Path_Walking_Path_Walking_sd_Up : 
			return (sc_boolean) (stateConfVector[0] == main_region_Path_Walking_Path_Walking_sd_Up
			);
		case main_region_Path_Walking_Path_Walking_sd_Right : 
			return (sc_boolean) (stateConfVector[0] == main_region_Path_Walking_Path_Walking_sd_Right
			);
		case main_region_Path_Walking_Path_Walking_sd_Down : 
			return (sc_boolean) (stateConfVector[0] == main_region_Path_Walking_Path_Walking_sd_Down
			);
		case main_region_Path_Walking_Path_Walking_sd_Left : 
			return (sc_boolean) (stateConfVector[0] == main_region_Path_Walking_Path_Walking_sd_Left
			);
		case Robot_Logic_Control_Wait_for_Command : 
			return (sc_boolean) (stateConfVector[1] == Robot_Logic_Control_Wait_for_Command
			);
		case Robot_Logic_Control_Go_Up : 
			return (sc_boolean) (stateConfVector[1] == Robot_Logic_Control_Go_Up
			);
		case Robot_Logic_Control_Go_Down : 
			return (sc_boolean) (stateConfVector[1] == Robot_Logic_Control_Go_Down
			);
		case Robot_Logic_Control_Go_Left : 
			return (sc_boolean) (stateConfVector[1] == Robot_Logic_Control_Go_Left
			);
		case Robot_Logic_Control_Go_Right : 
			return (sc_boolean) (stateConfVector[1] == Robot_Logic_Control_Go_Right
			);
		default: return false;
	}
}

Robot_v1::SCI_Comm* Robot_v1::getSCI_Comm() {
	return &ifaceComm;
}

void Robot_v1::SCI_Comm::raise_message_received() {
	message_received_raised = true;
}

sc_boolean Robot_v1::SCI_Comm::isRaised_message_sent() {
	return message_sent_raised;
}


sc_integer Robot_v1::SCI_Comm::get_message() {
	return message;
}

void Robot_v1::SCI_Comm::set_message(sc_integer value) {
	message = value;
}

sc_boolean Robot_v1::SCI_Comm::get_comm() {
	return comm;
}

void Robot_v1::SCI_Comm::set_comm(sc_boolean value) {
	comm = value;
}

void Robot_v1::setSCI_Comm_OCB(SCI_Comm_OCB* operationCallback) {
	ifaceComm_OCB = operationCallback;
}
Robot_v1::SCI_Control* Robot_v1::getSCI_Control() {
	return &ifaceControl;
}

void Robot_v1::SCI_Control::raise_goUp() {
	goUp_raised = true;
}

void Robot_v1::SCI_Control::raise_goDown() {
	goDown_raised = true;
}

void Robot_v1::SCI_Control::raise_goLeft() {
	goLeft_raised = true;
}

void Robot_v1::SCI_Control::raise_goRight() {
	goRight_raised = true;
}


Robot_v1::SCI_Sensor* Robot_v1::getSCI_Sensor() {
	return &ifaceSensor;
}


sc_boolean Robot_v1::SCI_Sensor::get_up() {
	return up;
}

void Robot_v1::SCI_Sensor::set_up(sc_boolean value) {
	up = value;
}

sc_boolean Robot_v1::SCI_Sensor::get_down() {
	return down;
}

void Robot_v1::SCI_Sensor::set_down(sc_boolean value) {
	down = value;
}

sc_boolean Robot_v1::SCI_Sensor::get_left() {
	return left;
}

void Robot_v1::SCI_Sensor::set_left(sc_boolean value) {
	left = value;
}

sc_boolean Robot_v1::SCI_Sensor::get_right() {
	return right;
}

void Robot_v1::SCI_Sensor::set_right(sc_boolean value) {
	right = value;
}

void Robot_v1::setSCI_Sensor_OCB(SCI_Sensor_OCB* operationCallback) {
	ifaceSensor_OCB = operationCallback;
}

void Robot_v1::InternalSCI::raise_pathReceived() {
	PathReceived_raised = true;
}

sc_boolean Robot_v1::InternalSCI::isRaised_pathReceived() {
	return PathReceived_raised;
}

void Robot_v1::InternalSCI::raise_deadEnd() {
	deadEnd_raised = true;
}

sc_boolean Robot_v1::InternalSCI::isRaised_deadEnd() {
	return deadEnd_raised;
}

sc_integer Robot_v1::InternalSCI::get_init_x() {
	return init_x;
}

sc_integer Robot_v1::InternalSCI::get_init_y() {
	return init_y;
}

sc_integer Robot_v1::InternalSCI::get_map_x() {
	return map_x;
}

void Robot_v1::InternalSCI::set_map_x(sc_integer value) {
	map_x = value;
}

sc_integer Robot_v1::InternalSCI::get_map_y() {
	return map_y;
}

void Robot_v1::InternalSCI::set_map_y(sc_integer value) {
	map_y = value;
}

sc_integer Robot_v1::InternalSCI::get_goal_x() {
	return goal_x;
}

void Robot_v1::InternalSCI::set_goal_x(sc_integer value) {
	goal_x = value;
}

sc_integer Robot_v1::InternalSCI::get_goal_y() {
	return goal_y;
}

void Robot_v1::InternalSCI::set_goal_y(sc_integer value) {
	goal_y = value;
}

sc_integer Robot_v1::InternalSCI::get_pos_x() {
	return pos_x;
}

void Robot_v1::InternalSCI::set_pos_x(sc_integer value) {
	pos_x = value;
}

sc_integer Robot_v1::InternalSCI::get_pos_y() {
	return pos_y;
}

void Robot_v1::InternalSCI::set_pos_y(sc_integer value) {
	pos_y = value;
}

sc_integer Robot_v1::InternalSCI::get_nextStep() {
	return nextStep;
}

void Robot_v1::InternalSCI::set_nextStep(sc_integer value) {
	nextStep = value;
}

sc_integer Robot_v1::InternalSCI::get_index() {
	return index;
}

void Robot_v1::InternalSCI::set_index(sc_integer value) {
	index = value;
}

void Robot_v1::setInternalSCI_OCB(InternalSCI_OCB* operationCallback) {
	ifaceInternalSCI_OCB = operationCallback;
}

// implementations of all internal functions

/* Entry action for statechart 'robot_v1'. */
void Robot_v1::enact_SequenceImpl() {
}

/* Exit action for state 'robot_v1'. */
void Robot_v1::exact_SequenceImpl() {
}

/* shallow enterSequence with history in child Robot_Logic_sd */
void Robot_v1::shenseq_SequenceImpl() {
	/* shallow enterSequence with history in child Robot_Logic_sd */
	/* Handle shallow history entry of Robot_Logic_sd */
	switch(historyVector[ 0 ]) {
		case main_region_Robot_Logic_Robot_Logic_sd_Init : {
			/* 'default' enter sequence for state Init */
			/* Entry action for state 'Init'. */
			ifaceInternalSCI.pos_x = ifaceComm_OCB->getInitX();
			ifaceInternalSCI.pos_y = ifaceComm_OCB->getInitY();
			ifaceInternalSCI.map_x = ifaceComm_OCB->getMapX();
			ifaceInternalSCI.map_y = ifaceComm_OCB->getMapY();
			ifaceInternalSCI.goal_x = ifaceComm_OCB->getGoalX();
			ifaceInternalSCI.goal_y = ifaceComm_OCB->getGoalY();
			stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd_Init;
			stateConfVectorPosition = 0;
			historyVector[0] = stateConfVector[0];
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Sensor_update : {
			/* 'default' enter sequence for state Sensor_update */
			/* Entry action for state 'Sensor_update'. */
			ifaceSensor.up = ifaceSensor_OCB->updateUp(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
			ifaceSensor.down = ifaceSensor_OCB->updateDown(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
			ifaceSensor.left = ifaceSensor_OCB->updateLeft(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
			ifaceSensor.right = ifaceSensor_OCB->updateRight(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
			stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd_Sensor_update;
			stateConfVectorPosition = 0;
			historyVector[0] = stateConfVector[0];
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Up : {
			/* 'default' enter sequence for state Up */
			/* Entry action for state 'Up'. */
			timer->setTimer(this, &timeEvents[2], 1 * 1000, false);
			ifaceControl.goUp_raised = true;
			stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd_Up;
			stateConfVectorPosition = 0;
			historyVector[0] = stateConfVector[0];
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Right : {
			/* 'default' enter sequence for state Right */
			/* Entry action for state 'Right'. */
			timer->setTimer(this, &timeEvents[3], 1 * 1000, false);
			ifaceControl.goRight_raised = true;
			stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd_Right;
			stateConfVectorPosition = 0;
			historyVector[0] = stateConfVector[0];
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Check_goals : {
			/* 'default' enter sequence for state Check_goals */
			stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd_Check_goals;
			stateConfVectorPosition = 0;
			historyVector[0] = stateConfVector[0];
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_DeadEnd : {
			/* 'default' enter sequence for state DeadEnd */
			/* Entry action for state 'DeadEnd'. */
			ifaceInternalSCI.deadEnd_raised = true;
			stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd_DeadEnd;
			stateConfVectorPosition = 0;
			historyVector[0] = stateConfVector[0];
			break;
		}
		default: break;
	}
}

/* The reactions of state Start. */
void Robot_v1::react_main_region_Start() {
	/* The reactions of state Start. */
	if (timeEvents[0]) { 
		/* Default exit sequence for state Start */
		stateConfVector[0] = Robot_v1_last_state;
		stateConfVectorPosition = 0;
		/* Exit action for state 'Start'. */
		timer->unsetTimer(this, &timeEvents[0]);
		/* 'default' enter sequence for state Comm_test */
		/* 'default' enter sequence for region Comm_test_sd */
		/* Default react sequence for initial entry  */
		/* 'default' enter sequence for state Start */
		/* Entry action for state 'Start'. */
		ifaceComm_OCB->sendMessage(2, 0, 0);
		ifaceComm.message = 0;
		stateConfVector[0] = main_region_Comm_test_Comm_test_sd_Start;
		stateConfVectorPosition = 0;
	} 
}

/* The reactions of state Start. */
void Robot_v1::react_main_region_Comm_test_Comm_test_sd_Start() {
	/* The reactions of state Start. */
	if (ifaceComm.comm) { 
		/* Default exit sequence for state Comm_test */
		/* Default exit sequence for region Comm_test_sd */
		/* Handle exit of all possible states (of Comm_test_sd) at position 0... */
		switch(stateConfVector[ 0 ]) {
			case main_region_Comm_test_Comm_test_sd_Start : {
				/* Default exit sequence for state Start */
				stateConfVector[0] = Robot_v1_last_state;
				stateConfVectorPosition = 0;
				break;
			}
			case main_region_Comm_test_Comm_test_sd_WaitForCloud : {
				/* Default exit sequence for state WaitForCloud */
				stateConfVector[0] = Robot_v1_last_state;
				stateConfVectorPosition = 0;
				/* Exit action for state 'WaitForCloud'. */
				timer->unsetTimer(this, &timeEvents[1]);
				break;
			}
			case main_region_Comm_test_Comm_test_sd_Link_Established : {
				/* Default exit sequence for state Link_Established */
				stateConfVector[0] = Robot_v1_last_state;
				stateConfVectorPosition = 0;
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state Robot_Logic */
		/* 'default' enter sequence for region Robot_Logic_sd */
		/* Default react sequence for shallow history entry  */
		/* Enter the region with shallow history */
		if (historyVector[0] != Robot_v1_last_state) {
			shenseq_SequenceImpl();
		} else {
			/* 'default' enter sequence for state Init */
			/* Entry action for state 'Init'. */
			ifaceInternalSCI.pos_x = ifaceComm_OCB->getInitX();
			ifaceInternalSCI.pos_y = ifaceComm_OCB->getInitY();
			ifaceInternalSCI.map_x = ifaceComm_OCB->getMapX();
			ifaceInternalSCI.map_y = ifaceComm_OCB->getMapY();
			ifaceInternalSCI.goal_x = ifaceComm_OCB->getGoalX();
			ifaceInternalSCI.goal_y = ifaceComm_OCB->getGoalY();
			stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd_Init;
			stateConfVectorPosition = 0;
			historyVector[0] = stateConfVector[0];
		} 
	}  else {
		/* Default exit sequence for state Start */
		stateConfVector[0] = Robot_v1_last_state;
		stateConfVectorPosition = 0;
		ifaceComm.message_sent_raised = true;
		/* 'default' enter sequence for state WaitForCloud */
		/* Entry action for state 'WaitForCloud'. */
		timer->setTimer(this, &timeEvents[1], 5 * 1000, false);
		ifaceComm_OCB->waitMessage();
		stateConfVector[0] = main_region_Comm_test_Comm_test_sd_WaitForCloud;
		stateConfVectorPosition = 0;
	}
}

/* The reactions of state WaitForCloud. */
void Robot_v1::react_main_region_Comm_test_Comm_test_sd_WaitForCloud() {
	/* The reactions of state WaitForCloud. */
	if (ifaceComm.comm) { 
		/* Default exit sequence for state Comm_test */
		/* Default exit sequence for region Comm_test_sd */
		/* Handle exit of all possible states (of Comm_test_sd) at position 0... */
		switch(stateConfVector[ 0 ]) {
			case main_region_Comm_test_Comm_test_sd_Start : {
				/* Default exit sequence for state Start */
				stateConfVector[0] = Robot_v1_last_state;
				stateConfVectorPosition = 0;
				break;
			}
			case main_region_Comm_test_Comm_test_sd_WaitForCloud : {
				/* Default exit sequence for state WaitForCloud */
				stateConfVector[0] = Robot_v1_last_state;
				stateConfVectorPosition = 0;
				/* Exit action for state 'WaitForCloud'. */
				timer->unsetTimer(this, &timeEvents[1]);
				break;
			}
			case main_region_Comm_test_Comm_test_sd_Link_Established : {
				/* Default exit sequence for state Link_Established */
				stateConfVector[0] = Robot_v1_last_state;
				stateConfVectorPosition = 0;
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state Robot_Logic */
		/* 'default' enter sequence for region Robot_Logic_sd */
		/* Default react sequence for shallow history entry  */
		/* Enter the region with shallow history */
		if (historyVector[0] != Robot_v1_last_state) {
			shenseq_SequenceImpl();
		} else {
			/* 'default' enter sequence for state Init */
			/* Entry action for state 'Init'. */
			ifaceInternalSCI.pos_x = ifaceComm_OCB->getInitX();
			ifaceInternalSCI.pos_y = ifaceComm_OCB->getInitY();
			ifaceInternalSCI.map_x = ifaceComm_OCB->getMapX();
			ifaceInternalSCI.map_y = ifaceComm_OCB->getMapY();
			ifaceInternalSCI.goal_x = ifaceComm_OCB->getGoalX();
			ifaceInternalSCI.goal_y = ifaceComm_OCB->getGoalY();
			stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd_Init;
			stateConfVectorPosition = 0;
			historyVector[0] = stateConfVector[0];
		} 
	}  else {
		if (timeEvents[1]) { 
			/* Default exit sequence for state WaitForCloud */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			/* Exit action for state 'WaitForCloud'. */
			timer->unsetTimer(this, &timeEvents[1]);
			/* The reactions of state null. */
			if (ifaceComm.message == 1) { 
				/* 'default' enter sequence for state Link_Established */
				/* Entry action for state 'Link_Established'. */
				ifaceComm.comm = true;
				stateConfVector[0] = main_region_Comm_test_Comm_test_sd_Link_Established;
				stateConfVectorPosition = 0;
			}  else {
				/* 'default' enter sequence for state WaitForCloud */
				/* Entry action for state 'WaitForCloud'. */
				timer->setTimer(this, &timeEvents[1], 5 * 1000, false);
				ifaceComm_OCB->waitMessage();
				stateConfVector[0] = main_region_Comm_test_Comm_test_sd_WaitForCloud;
				stateConfVectorPosition = 0;
			}
		} 
	}
}

/* The reactions of state Link_Established. */
void Robot_v1::react_main_region_Comm_test_Comm_test_sd_Link_Established() {
	/* The reactions of state Link_Established. */
	if (ifaceComm.comm) { 
		/* Default exit sequence for state Comm_test */
		/* Default exit sequence for region Comm_test_sd */
		/* Handle exit of all possible states (of Comm_test_sd) at position 0... */
		switch(stateConfVector[ 0 ]) {
			case main_region_Comm_test_Comm_test_sd_Start : {
				/* Default exit sequence for state Start */
				stateConfVector[0] = Robot_v1_last_state;
				stateConfVectorPosition = 0;
				break;
			}
			case main_region_Comm_test_Comm_test_sd_WaitForCloud : {
				/* Default exit sequence for state WaitForCloud */
				stateConfVector[0] = Robot_v1_last_state;
				stateConfVectorPosition = 0;
				/* Exit action for state 'WaitForCloud'. */
				timer->unsetTimer(this, &timeEvents[1]);
				break;
			}
			case main_region_Comm_test_Comm_test_sd_Link_Established : {
				/* Default exit sequence for state Link_Established */
				stateConfVector[0] = Robot_v1_last_state;
				stateConfVectorPosition = 0;
				break;
			}
			default: break;
		}
		/* 'default' enter sequence for state Robot_Logic */
		/* 'default' enter sequence for region Robot_Logic_sd */
		/* Default react sequence for shallow history entry  */
		/* Enter the region with shallow history */
		if (historyVector[0] != Robot_v1_last_state) {
			shenseq_SequenceImpl();
		} else {
			/* 'default' enter sequence for state Init */
			/* Entry action for state 'Init'. */
			ifaceInternalSCI.pos_x = ifaceComm_OCB->getInitX();
			ifaceInternalSCI.pos_y = ifaceComm_OCB->getInitY();
			ifaceInternalSCI.map_x = ifaceComm_OCB->getMapX();
			ifaceInternalSCI.map_y = ifaceComm_OCB->getMapY();
			ifaceInternalSCI.goal_x = ifaceComm_OCB->getGoalX();
			ifaceInternalSCI.goal_y = ifaceComm_OCB->getGoalY();
			stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd_Init;
			stateConfVectorPosition = 0;
			historyVector[0] = stateConfVector[0];
		} 
	}  else {
	}
}

/* The reactions of state Init. */
void Robot_v1::react_main_region_Robot_Logic_Robot_Logic_sd_Init() {
	/* The reactions of state Init. */
	/* Default exit sequence for state Init */
	stateConfVector[0] = Robot_v1_last_state;
	stateConfVectorPosition = 0;
	/* 'default' enter sequence for state Check_goals */
	stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd_Check_goals;
	stateConfVectorPosition = 0;
	historyVector[0] = stateConfVector[0];
}

/* The reactions of state Sensor_update. */
void Robot_v1::react_main_region_Robot_Logic_Robot_Logic_sd_Sensor_update() {
	/* The reactions of state Sensor_update. */
	/* Default exit sequence for state Sensor_update */
	stateConfVector[0] = Robot_v1_last_state;
	stateConfVectorPosition = 0;
	/* The reactions of state null. */
	if (ifaceSensor.up == true && ifaceSensor.right == false) { 
		/* 'default' enter sequence for state Right */
		/* Entry action for state 'Right'. */
		timer->setTimer(this, &timeEvents[3], 1 * 1000, false);
		ifaceControl.goRight_raised = true;
		stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd_Right;
		stateConfVectorPosition = 0;
		historyVector[0] = stateConfVector[0];
	}  else {
		if (ifaceSensor.up == false) { 
			/* 'default' enter sequence for state Up */
			/* Entry action for state 'Up'. */
			timer->setTimer(this, &timeEvents[2], 1 * 1000, false);
			ifaceControl.goUp_raised = true;
			stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd_Up;
			stateConfVectorPosition = 0;
			historyVector[0] = stateConfVector[0];
		}  else {
			/* 'default' enter sequence for state DeadEnd */
			/* Entry action for state 'DeadEnd'. */
			ifaceInternalSCI.deadEnd_raised = true;
			stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd_DeadEnd;
			stateConfVectorPosition = 0;
			historyVector[0] = stateConfVector[0];
		}
	}
}

/* The reactions of state Up. */
void Robot_v1::react_main_region_Robot_Logic_Robot_Logic_sd_Up() {
	/* The reactions of state Up. */
	if (timeEvents[2]) { 
		/* Default exit sequence for state Up */
		stateConfVector[0] = Robot_v1_last_state;
		stateConfVectorPosition = 0;
		/* Exit action for state 'Up'. */
		timer->unsetTimer(this, &timeEvents[2]);
		/* 'default' enter sequence for state Check_goals */
		stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd_Check_goals;
		stateConfVectorPosition = 0;
		historyVector[0] = stateConfVector[0];
	} 
}

/* The reactions of state Right. */
void Robot_v1::react_main_region_Robot_Logic_Robot_Logic_sd_Right() {
	/* The reactions of state Right. */
	if (timeEvents[3]) { 
		/* Default exit sequence for state Right */
		stateConfVector[0] = Robot_v1_last_state;
		stateConfVectorPosition = 0;
		/* Exit action for state 'Right'. */
		timer->unsetTimer(this, &timeEvents[3]);
		/* 'default' enter sequence for state Check_goals */
		stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd_Check_goals;
		stateConfVectorPosition = 0;
		historyVector[0] = stateConfVector[0];
	} 
}

/* The reactions of state Check_goals. */
void Robot_v1::react_main_region_Robot_Logic_Robot_Logic_sd_Check_goals() {
	/* The reactions of state Check_goals. */
	if (ifaceInternalSCI.pos_x != ifaceInternalSCI.goal_x || ifaceInternalSCI.pos_y != ifaceInternalSCI.goal_y) { 
		/* Default exit sequence for state Check_goals */
		stateConfVector[0] = Robot_v1_last_state;
		stateConfVectorPosition = 0;
		/* 'default' enter sequence for state Sensor_update */
		/* Entry action for state 'Sensor_update'. */
		ifaceSensor.up = ifaceSensor_OCB->updateUp(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.down = ifaceSensor_OCB->updateDown(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.left = ifaceSensor_OCB->updateLeft(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.right = ifaceSensor_OCB->updateRight(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd_Sensor_update;
		stateConfVectorPosition = 0;
		historyVector[0] = stateConfVector[0];
	}  else {
		/* Default exit sequence for state Check_goals */
		stateConfVector[0] = Robot_v1_last_state;
		stateConfVectorPosition = 0;
		/* Default enter sequence for state null */
		stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd__final_;
		stateConfVectorPosition = 0;
	}
}

/* The reactions of state DeadEnd. */
void Robot_v1::react_main_region_Robot_Logic_Robot_Logic_sd_DeadEnd() {
	/* The reactions of state DeadEnd. */
	/* Default exit sequence for state DeadEnd */
	stateConfVector[0] = Robot_v1_last_state;
	stateConfVectorPosition = 0;
	/* The reactions of exit default. */
	/* Default exit sequence for state Robot_Logic */
	/* Default exit sequence for region Robot_Logic_sd */
	/* Handle exit of all possible states (of Robot_Logic_sd) at position 0... */
	switch(stateConfVector[ 0 ]) {
		case main_region_Robot_Logic_Robot_Logic_sd_Init : {
			/* Default exit sequence for state Init */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Sensor_update : {
			/* Default exit sequence for state Sensor_update */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Up : {
			/* Default exit sequence for state Up */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			/* Exit action for state 'Up'. */
			timer->unsetTimer(this, &timeEvents[2]);
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Right : {
			/* Default exit sequence for state Right */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			/* Exit action for state 'Right'. */
			timer->unsetTimer(this, &timeEvents[3]);
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_Check_goals : {
			/* Default exit sequence for state Check_goals */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd_DeadEnd : {
			/* Default exit sequence for state DeadEnd */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		case main_region_Robot_Logic_Robot_Logic_sd__final_ : {
			/* Default exit sequence for final state. */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		default: break;
	}
	/* 'default' enter sequence for state Help_from_Cloud */
	/* 'default' enter sequence for region Help_from_Cloud_sd */
	/* Default react sequence for initial entry  */
	/* 'default' enter sequence for state Send */
	/* Entry action for state 'Send'. */
	ifaceComm_OCB->sendMessage(3, ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
	ifaceComm.message = 0;
	stateConfVector[0] = main_region_Help_from_Cloud_Help_from_Cloud_sd_Send;
	stateConfVectorPosition = 0;
}

/* The reactions of state null. */
void Robot_v1::react_main_region_Robot_Logic_Robot_Logic_sd__final_() {
	/* The reactions of state null. */
}

/* The reactions of state Send. */
void Robot_v1::react_main_region_Help_from_Cloud_Help_from_Cloud_sd_Send() {
	/* The reactions of state Send. */
	/* Default exit sequence for state Send */
	stateConfVector[0] = Robot_v1_last_state;
	stateConfVectorPosition = 0;
	ifaceComm.message_sent_raised = true;
	/* 'default' enter sequence for state Wait_for_Message */
	/* Entry action for state 'Wait_for_Message'. */
	timer->setTimer(this, &timeEvents[4], 5 * 1000, false);
	ifaceComm.message = ifaceComm_OCB->waitMessage();
	stateConfVector[0] = main_region_Help_from_Cloud_Help_from_Cloud_sd_Wait_for_Message;
	stateConfVectorPosition = 0;
}

/* The reactions of state Wait_for_Message. */
void Robot_v1::react_main_region_Help_from_Cloud_Help_from_Cloud_sd_Wait_for_Message() {
	/* The reactions of state Wait_for_Message. */
	if (timeEvents[4]) { 
		/* Default exit sequence for state Wait_for_Message */
		stateConfVector[0] = Robot_v1_last_state;
		stateConfVectorPosition = 0;
		/* Exit action for state 'Wait_for_Message'. */
		timer->unsetTimer(this, &timeEvents[4]);
		/* The reactions of state null. */
		if (ifaceComm.message == 4) { 
			/* 'default' enter sequence for state Help_received */
			/* Entry action for state 'Help_received'. */
			ifaceInternalSCI.PathReceived_raised = true;
			stateConfVector[0] = main_region_Help_from_Cloud_Help_from_Cloud_sd_Help_received;
			stateConfVectorPosition = 0;
		}  else {
			/* 'default' enter sequence for state Wait_for_Message */
			/* Entry action for state 'Wait_for_Message'. */
			timer->setTimer(this, &timeEvents[4], 5 * 1000, false);
			ifaceComm.message = ifaceComm_OCB->waitMessage();
			stateConfVector[0] = main_region_Help_from_Cloud_Help_from_Cloud_sd_Wait_for_Message;
			stateConfVectorPosition = 0;
		}
	} 
}

/* The reactions of state Help_received. */
void Robot_v1::react_main_region_Help_from_Cloud_Help_from_Cloud_sd_Help_received() {
	/* The reactions of state Help_received. */
	/* Default exit sequence for state Help_received */
	stateConfVector[0] = Robot_v1_last_state;
	stateConfVectorPosition = 0;
	/* The reactions of exit default. */
	/* Default exit sequence for state Help_from_Cloud */
	/* Default exit sequence for region Help_from_Cloud_sd */
	/* Handle exit of all possible states (of Help_from_Cloud_sd) at position 0... */
	switch(stateConfVector[ 0 ]) {
		case main_region_Help_from_Cloud_Help_from_Cloud_sd_Send : {
			/* Default exit sequence for state Send */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		case main_region_Help_from_Cloud_Help_from_Cloud_sd_Wait_for_Message : {
			/* Default exit sequence for state Wait_for_Message */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			/* Exit action for state 'Wait_for_Message'. */
			timer->unsetTimer(this, &timeEvents[4]);
			break;
		}
		case main_region_Help_from_Cloud_Help_from_Cloud_sd_Help_received : {
			/* Default exit sequence for state Help_received */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			break;
		}
		default: break;
	}
	/* 'default' enter sequence for state Path_Walking */
	/* 'default' enter sequence for region Path_Walking_sd */
	/* Default react sequence for initial entry  */
	/* 'default' enter sequence for state Init */
	/* Entry action for state 'Init'. */
	timer->setTimer(this, &timeEvents[5], 1 * 1000, false);
	ifaceInternalSCI.index = 0;
	ifaceInternalSCI.nextStep = 0;
	stateConfVector[0] = main_region_Path_Walking_Path_Walking_sd_Init;
	stateConfVectorPosition = 0;
}

/* The reactions of state Sensor_update. */
void Robot_v1::react_main_region_Path_Walking_Path_Walking_sd_Sensor_update() {
	/* The reactions of state Sensor_update. */
	/* Default exit sequence for state Sensor_update */
	stateConfVector[0] = Robot_v1_last_state;
	stateConfVectorPosition = 0;
	/* 'default' enter sequence for state Next_Step */
	/* Entry action for state 'Next_Step'. */
	ifaceInternalSCI.nextStep = ifaceInternalSCI_OCB->getStep(ifaceInternalSCI.index);
	stateConfVector[0] = main_region_Path_Walking_Path_Walking_sd_Next_Step;
	stateConfVectorPosition = 0;
}

/* The reactions of state Next_Step. */
void Robot_v1::react_main_region_Path_Walking_Path_Walking_sd_Next_Step() {
	/* The reactions of state Next_Step. */
	if (ifaceInternalSCI.nextStep != 0) { 
		/* Default exit sequence for state Next_Step */
		stateConfVector[0] = Robot_v1_last_state;
		stateConfVectorPosition = 0;
		ifaceInternalSCI.index += 1;
		/* The reactions of state null. */
		if (ifaceInternalSCI.nextStep == 1) { 
			/* 'default' enter sequence for state Up */
			/* Entry action for state 'Up'. */
			timer->setTimer(this, &timeEvents[6], 20, false);
			ifaceControl.goUp_raised = true;
			stateConfVector[0] = main_region_Path_Walking_Path_Walking_sd_Up;
			stateConfVectorPosition = 0;
		}  else {
			if (ifaceInternalSCI.nextStep == 2) { 
				/* 'default' enter sequence for state Right */
				/* Entry action for state 'Right'. */
				timer->setTimer(this, &timeEvents[7], 20, false);
				ifaceControl.goRight_raised = true;
				stateConfVector[0] = main_region_Path_Walking_Path_Walking_sd_Right;
				stateConfVectorPosition = 0;
			}  else {
				if (ifaceInternalSCI.nextStep == 3) { 
					/* 'default' enter sequence for state Down */
					/* Entry action for state 'Down'. */
					timer->setTimer(this, &timeEvents[8], 20, false);
					ifaceControl.goDown_raised = true;
					stateConfVector[0] = main_region_Path_Walking_Path_Walking_sd_Down;
					stateConfVectorPosition = 0;
				}  else {
					if (ifaceInternalSCI.nextStep == 4) { 
						/* 'default' enter sequence for state Left */
						/* Entry action for state 'Left'. */
						timer->setTimer(this, &timeEvents[9], 20, false);
						ifaceControl.goLeft_raised = true;
						stateConfVector[0] = main_region_Path_Walking_Path_Walking_sd_Left;
						stateConfVectorPosition = 0;
					}  else {
						/* 'default' enter sequence for state Sensor_update */
						/* Entry action for state 'Sensor_update'. */
						ifaceSensor.up = ifaceSensor_OCB->updateUp(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
						ifaceSensor.down = ifaceSensor_OCB->updateDown(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
						ifaceSensor.left = ifaceSensor_OCB->updateLeft(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
						ifaceSensor.right = ifaceSensor_OCB->updateRight(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
						stateConfVector[0] = main_region_Path_Walking_Path_Walking_sd_Sensor_update;
						stateConfVectorPosition = 0;
					}
				}
			}
		}
	}  else {
		if (ifaceInternalSCI.nextStep == 0) { 
			/* Default exit sequence for state Next_Step */
			stateConfVector[0] = Robot_v1_last_state;
			stateConfVectorPosition = 0;
			/* The reactions of exit default. */
			/* Default exit sequence for state Path_Walking */
			/* Default exit sequence for region Path_Walking_sd */
			/* Handle exit of all possible states (of Path_Walking_sd) at position 0... */
			switch(stateConfVector[ 0 ]) {
				case main_region_Path_Walking_Path_Walking_sd_Sensor_update : {
					/* Default exit sequence for state Sensor_update */
					stateConfVector[0] = Robot_v1_last_state;
					stateConfVectorPosition = 0;
					break;
				}
				case main_region_Path_Walking_Path_Walking_sd_Next_Step : {
					/* Default exit sequence for state Next_Step */
					stateConfVector[0] = Robot_v1_last_state;
					stateConfVectorPosition = 0;
					break;
				}
				case main_region_Path_Walking_Path_Walking_sd_Init : {
					/* Default exit sequence for state Init */
					stateConfVector[0] = Robot_v1_last_state;
					stateConfVectorPosition = 0;
					/* Exit action for state 'Init'. */
					timer->unsetTimer(this, &timeEvents[5]);
					break;
				}
				case main_region_Path_Walking_Path_Walking_sd_Up : {
					/* Default exit sequence for state Up */
					stateConfVector[0] = Robot_v1_last_state;
					stateConfVectorPosition = 0;
					/* Exit action for state 'Up'. */
					timer->unsetTimer(this, &timeEvents[6]);
					break;
				}
				case main_region_Path_Walking_Path_Walking_sd_Right : {
					/* Default exit sequence for state Right */
					stateConfVector[0] = Robot_v1_last_state;
					stateConfVectorPosition = 0;
					/* Exit action for state 'Right'. */
					timer->unsetTimer(this, &timeEvents[7]);
					break;
				}
				case main_region_Path_Walking_Path_Walking_sd_Down : {
					/* Default exit sequence for state Down */
					stateConfVector[0] = Robot_v1_last_state;
					stateConfVectorPosition = 0;
					/* Exit action for state 'Down'. */
					timer->unsetTimer(this, &timeEvents[8]);
					break;
				}
				case main_region_Path_Walking_Path_Walking_sd_Left : {
					/* Default exit sequence for state Left */
					stateConfVector[0] = Robot_v1_last_state;
					stateConfVectorPosition = 0;
					/* Exit action for state 'Left'. */
					timer->unsetTimer(this, &timeEvents[9]);
					break;
				}
				default: break;
			}
			/* 'default' enter sequence for state Robot_Logic */
			/* 'default' enter sequence for region Robot_Logic_sd */
			/* Default react sequence for shallow history entry  */
			/* Enter the region with shallow history */
			if (historyVector[0] != Robot_v1_last_state) {
				shenseq_SequenceImpl();
			} else {
				/* 'default' enter sequence for state Init */
				/* Entry action for state 'Init'. */
				ifaceInternalSCI.pos_x = ifaceComm_OCB->getInitX();
				ifaceInternalSCI.pos_y = ifaceComm_OCB->getInitY();
				ifaceInternalSCI.map_x = ifaceComm_OCB->getMapX();
				ifaceInternalSCI.map_y = ifaceComm_OCB->getMapY();
				ifaceInternalSCI.goal_x = ifaceComm_OCB->getGoalX();
				ifaceInternalSCI.goal_y = ifaceComm_OCB->getGoalY();
				stateConfVector[0] = main_region_Robot_Logic_Robot_Logic_sd_Init;
				stateConfVectorPosition = 0;
				historyVector[0] = stateConfVector[0];
			} 
		} 
	}
}

/* The reactions of state Init. */
void Robot_v1::react_main_region_Path_Walking_Path_Walking_sd_Init() {
	/* The reactions of state Init. */
	if (timeEvents[5]) { 
		/* Default exit sequence for state Init */
		stateConfVector[0] = Robot_v1_last_state;
		stateConfVectorPosition = 0;
		/* Exit action for state 'Init'. */
		timer->unsetTimer(this, &timeEvents[5]);
		/* 'default' enter sequence for state Sensor_update */
		/* Entry action for state 'Sensor_update'. */
		ifaceSensor.up = ifaceSensor_OCB->updateUp(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.down = ifaceSensor_OCB->updateDown(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.left = ifaceSensor_OCB->updateLeft(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.right = ifaceSensor_OCB->updateRight(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		stateConfVector[0] = main_region_Path_Walking_Path_Walking_sd_Sensor_update;
		stateConfVectorPosition = 0;
	} 
}

/* The reactions of state Up. */
void Robot_v1::react_main_region_Path_Walking_Path_Walking_sd_Up() {
	/* The reactions of state Up. */
	if (timeEvents[6]) { 
		/* Default exit sequence for state Up */
		stateConfVector[0] = Robot_v1_last_state;
		stateConfVectorPosition = 0;
		/* Exit action for state 'Up'. */
		timer->unsetTimer(this, &timeEvents[6]);
		/* 'default' enter sequence for state Sensor_update */
		/* Entry action for state 'Sensor_update'. */
		ifaceSensor.up = ifaceSensor_OCB->updateUp(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.down = ifaceSensor_OCB->updateDown(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.left = ifaceSensor_OCB->updateLeft(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.right = ifaceSensor_OCB->updateRight(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		stateConfVector[0] = main_region_Path_Walking_Path_Walking_sd_Sensor_update;
		stateConfVectorPosition = 0;
	} 
}

/* The reactions of state Right. */
void Robot_v1::react_main_region_Path_Walking_Path_Walking_sd_Right() {
	/* The reactions of state Right. */
	if (timeEvents[7]) { 
		/* Default exit sequence for state Right */
		stateConfVector[0] = Robot_v1_last_state;
		stateConfVectorPosition = 0;
		/* Exit action for state 'Right'. */
		timer->unsetTimer(this, &timeEvents[7]);
		/* 'default' enter sequence for state Sensor_update */
		/* Entry action for state 'Sensor_update'. */
		ifaceSensor.up = ifaceSensor_OCB->updateUp(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.down = ifaceSensor_OCB->updateDown(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.left = ifaceSensor_OCB->updateLeft(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.right = ifaceSensor_OCB->updateRight(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		stateConfVector[0] = main_region_Path_Walking_Path_Walking_sd_Sensor_update;
		stateConfVectorPosition = 0;
	} 
}

/* The reactions of state Down. */
void Robot_v1::react_main_region_Path_Walking_Path_Walking_sd_Down() {
	/* The reactions of state Down. */
	if (timeEvents[8]) { 
		/* Default exit sequence for state Down */
		stateConfVector[0] = Robot_v1_last_state;
		stateConfVectorPosition = 0;
		/* Exit action for state 'Down'. */
		timer->unsetTimer(this, &timeEvents[8]);
		/* 'default' enter sequence for state Sensor_update */
		/* Entry action for state 'Sensor_update'. */
		ifaceSensor.up = ifaceSensor_OCB->updateUp(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.down = ifaceSensor_OCB->updateDown(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.left = ifaceSensor_OCB->updateLeft(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.right = ifaceSensor_OCB->updateRight(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		stateConfVector[0] = main_region_Path_Walking_Path_Walking_sd_Sensor_update;
		stateConfVectorPosition = 0;
	} 
}

/* The reactions of state Left. */
void Robot_v1::react_main_region_Path_Walking_Path_Walking_sd_Left() {
	/* The reactions of state Left. */
	if (timeEvents[9]) { 
		/* Default exit sequence for state Left */
		stateConfVector[0] = Robot_v1_last_state;
		stateConfVectorPosition = 0;
		/* Exit action for state 'Left'. */
		timer->unsetTimer(this, &timeEvents[9]);
		/* 'default' enter sequence for state Sensor_update */
		/* Entry action for state 'Sensor_update'. */
		ifaceSensor.up = ifaceSensor_OCB->updateUp(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.down = ifaceSensor_OCB->updateDown(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.left = ifaceSensor_OCB->updateLeft(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		ifaceSensor.right = ifaceSensor_OCB->updateRight(ifaceInternalSCI.pos_x, ifaceInternalSCI.pos_y);
		stateConfVector[0] = main_region_Path_Walking_Path_Walking_sd_Sensor_update;
		stateConfVectorPosition = 0;
	} 
}

/* The reactions of state Wait_for Command. */
void Robot_v1::react_Robot_Logic_Control_Wait_for_Command() {
	/* The reactions of state Wait_for Command. */
	if (ifaceInternalSCI.pos_y > 0 && ifaceControl.goUp_raised) { 
		/* Default exit sequence for state Wait_for Command */
		stateConfVector[1] = Robot_v1_last_state;
		stateConfVectorPosition = 1;
		/* 'default' enter sequence for state Go_Up */
		/* Entry action for state 'Go_Up'. */
		timer->setTimer(this, &timeEvents[10], 200, false);
		ifaceInternalSCI.pos_y = ifaceInternalSCI.pos_y - 1;
		stateConfVector[1] = Robot_Logic_Control_Go_Up;
		stateConfVectorPosition = 1;
	}  else {
		if (ifaceInternalSCI.pos_x < (ifaceInternalSCI.map_x - 1) && ifaceControl.goRight_raised) { 
			/* Default exit sequence for state Wait_for Command */
			stateConfVector[1] = Robot_v1_last_state;
			stateConfVectorPosition = 1;
			/* 'default' enter sequence for state Go_Right */
			/* Entry action for state 'Go_Right'. */
			timer->setTimer(this, &timeEvents[13], 200, false);
			ifaceInternalSCI.pos_x = ifaceInternalSCI.pos_x + 1;
			stateConfVector[1] = Robot_Logic_Control_Go_Right;
			stateConfVectorPosition = 1;
		}  else {
			if (ifaceInternalSCI.pos_y < (ifaceInternalSCI.map_y - 1) && ifaceControl.goDown_raised) { 
				/* Default exit sequence for state Wait_for Command */
				stateConfVector[1] = Robot_v1_last_state;
				stateConfVectorPosition = 1;
				/* 'default' enter sequence for state Go_Down */
				/* Entry action for state 'Go_Down'. */
				timer->setTimer(this, &timeEvents[11], 200, false);
				ifaceInternalSCI.pos_y = ifaceInternalSCI.pos_y + 1;
				stateConfVector[1] = Robot_Logic_Control_Go_Down;
				stateConfVectorPosition = 1;
			}  else {
				if (ifaceInternalSCI.pos_x > 0 && ifaceControl.goLeft_raised) { 
					/* Default exit sequence for state Wait_for Command */
					stateConfVector[1] = Robot_v1_last_state;
					stateConfVectorPosition = 1;
					/* 'default' enter sequence for state Go_Left */
					/* Entry action for state 'Go_Left'. */
					timer->setTimer(this, &timeEvents[12], 200, false);
					ifaceInternalSCI.pos_x = ifaceInternalSCI.pos_x - 1;
					stateConfVector[1] = Robot_Logic_Control_Go_Left;
					stateConfVectorPosition = 1;
				}  else {
					if (ifaceControl.goUp_raised || ifaceControl.goDown_raised || ifaceControl.goLeft_raised || ifaceControl.goRight_raised) { 
						/* Default exit sequence for state Wait_for Command */
						stateConfVector[1] = Robot_v1_last_state;
						stateConfVectorPosition = 1;
						/* 'default' enter sequence for state Wait_for Command */
						stateConfVector[1] = Robot_Logic_Control_Wait_for_Command;
						stateConfVectorPosition = 1;
					} 
				}
			}
		}
	}
}

/* The reactions of state Go_Up. */
void Robot_v1::react_Robot_Logic_Control_Go_Up() {
	/* The reactions of state Go_Up. */
	if (timeEvents[10]) { 
		/* Default exit sequence for state Go_Up */
		stateConfVector[1] = Robot_v1_last_state;
		stateConfVectorPosition = 1;
		/* Exit action for state 'Go_Up'. */
		timer->unsetTimer(this, &timeEvents[10]);
		/* 'default' enter sequence for state Wait_for Command */
		stateConfVector[1] = Robot_Logic_Control_Wait_for_Command;
		stateConfVectorPosition = 1;
	} 
}

/* The reactions of state Go_Down. */
void Robot_v1::react_Robot_Logic_Control_Go_Down() {
	/* The reactions of state Go_Down. */
	if (timeEvents[11]) { 
		/* Default exit sequence for state Go_Down */
		stateConfVector[1] = Robot_v1_last_state;
		stateConfVectorPosition = 1;
		/* Exit action for state 'Go_Down'. */
		timer->unsetTimer(this, &timeEvents[11]);
		/* 'default' enter sequence for state Wait_for Command */
		stateConfVector[1] = Robot_Logic_Control_Wait_for_Command;
		stateConfVectorPosition = 1;
	} 
}

/* The reactions of state Go_Left. */
void Robot_v1::react_Robot_Logic_Control_Go_Left() {
	/* The reactions of state Go_Left. */
	if (timeEvents[12]) { 
		/* Default exit sequence for state Go_Left */
		stateConfVector[1] = Robot_v1_last_state;
		stateConfVectorPosition = 1;
		/* Exit action for state 'Go_Left'. */
		timer->unsetTimer(this, &timeEvents[12]);
		/* 'default' enter sequence for state Wait_for Command */
		stateConfVector[1] = Robot_Logic_Control_Wait_for_Command;
		stateConfVectorPosition = 1;
	} 
}

/* The reactions of state Go_Right. */
void Robot_v1::react_Robot_Logic_Control_Go_Right() {
	/* The reactions of state Go_Right. */
	if (timeEvents[13]) { 
		/* Default exit sequence for state Go_Right */
		stateConfVector[1] = Robot_v1_last_state;
		stateConfVectorPosition = 1;
		/* Exit action for state 'Go_Right'. */
		timer->unsetTimer(this, &timeEvents[13]);
		/* 'default' enter sequence for state Wait_for Command */
		stateConfVector[1] = Robot_Logic_Control_Wait_for_Command;
		stateConfVectorPosition = 1;
	} 
}


