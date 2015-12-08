
#ifndef ROBOT_V1_H_
#define ROBOT_V1_H_

#include "sc_types.h"
#include "StatemachineInterface.h"
#include "TimedStatemachineInterface.h"

/*! \file Header of the state machine 'robot_v1'.
*/

class Robot_v1 : public TimedStatemachineInterface, public StatemachineInterface {
	
	public:
		
		Robot_v1();
		
		~Robot_v1();
		
		//! enumeration of all states 
		typedef enum {
			main_region_Start,
			main_region_Comm_test,
			main_region_Comm_test_Comm_test_sd_Start,
			main_region_Comm_test_Comm_test_sd_WaitForCloud,
			main_region_Comm_test_Comm_test_sd_Link_Established,
			main_region_Robot_Logic,
			main_region_Robot_Logic_Robot_Logic_sd_Init,
			main_region_Robot_Logic_Robot_Logic_sd_Sensor_update,
			main_region_Robot_Logic_Robot_Logic_sd_Up,
			main_region_Robot_Logic_Robot_Logic_sd_Right,
			main_region_Robot_Logic_Robot_Logic_sd_Check_goals,
			main_region_Robot_Logic_Robot_Logic_sd_DeadEnd,
			main_region_Robot_Logic_Robot_Logic_sd__final_,
			main_region_Help_from_Cloud,
			main_region_Help_from_Cloud_Help_from_Cloud_sd_Send,
			main_region_Help_from_Cloud_Help_from_Cloud_sd_Wait_for_Message,
			main_region_Help_from_Cloud_Help_from_Cloud_sd_Help_received,
			main_region_Path_Walking,
			main_region_Path_Walking_Path_Walking_sd_Sensor_update,
			main_region_Path_Walking_Path_Walking_sd_Next_Step,
			main_region_Path_Walking_Path_Walking_sd_Init,
			main_region_Path_Walking_Path_Walking_sd_Up,
			main_region_Path_Walking_Path_Walking_sd_Right,
			main_region_Path_Walking_Path_Walking_sd_Down,
			main_region_Path_Walking_Path_Walking_sd_Left,
			Robot_Logic_Control_Wait_for_Command,
			Robot_Logic_Control_Go_Up,
			Robot_Logic_Control_Go_Down,
			Robot_Logic_Control_Go_Left,
			Robot_Logic_Control_Go_Right,
			Robot_v1_last_state
		} Robot_v1States;
		
		//! Inner class for Comm interface scope.
		class SCI_Comm {
			
			public:
				/*! Raises the in event 'message_received' that is defined in the interface scope 'Comm'. */ 
				void raise_message_received();
				
				/*! Checks if the out event 'message_sent' that is defined in the interface scope 'Comm' has been raised. */ 
				sc_boolean isRaised_message_sent();
				
				/*! Gets the value of the variable 'message' that is defined in the interface scope 'Comm'. */ 
				sc_integer get_message();
				
				/*! Sets the value of the variable 'message' that is defined in the interface scope 'Comm'. */ 
				void set_message(sc_integer value);
				
				/*! Gets the value of the variable 'comm' that is defined in the interface scope 'Comm'. */ 
				sc_boolean get_comm();
				
				/*! Sets the value of the variable 'comm' that is defined in the interface scope 'Comm'. */ 
				void set_comm(sc_boolean value);
				
				
			private:
				friend class Robot_v1;
				sc_boolean message_received_raised;
				sc_boolean message_sent_raised;
				sc_integer message;
				sc_boolean comm;
		};
		
		//! Inner class for Comm interface scope operation callbacks.
		class SCI_Comm_OCB {
			public:
				virtual ~SCI_Comm_OCB() = 0;
				
				virtual sc_integer sendMessage(sc_integer s1, sc_integer x, sc_integer y) = 0;
				
				virtual sc_integer waitMessage() = 0;
				
				virtual sc_integer getInitX() = 0;
				
				virtual sc_integer getInitY() = 0;
				
				virtual sc_integer getMapX() = 0;
				
				virtual sc_integer getMapY() = 0;
				
				virtual sc_integer getGoalX() = 0;
				
				virtual sc_integer getGoalY() = 0;
				
				virtual sc_string getPath() = 0;
		};
		
		/*! Set the working instance of the operation callback interface 'SCI_Comm_OCB'. */
		void setSCI_Comm_OCB(SCI_Comm_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_Comm'. */
		SCI_Comm* getSCI_Comm();
		
		//! Inner class for Control interface scope.
		class SCI_Control {
			
			public:
				/*! Raises the in event 'goUp' that is defined in the interface scope 'Control'. */ 
				void raise_goUp();
				
				/*! Raises the in event 'goDown' that is defined in the interface scope 'Control'. */ 
				void raise_goDown();
				
				/*! Raises the in event 'goLeft' that is defined in the interface scope 'Control'. */ 
				void raise_goLeft();
				
				/*! Raises the in event 'goRight' that is defined in the interface scope 'Control'. */ 
				void raise_goRight();
				
				
			private:
				friend class Robot_v1;
				sc_boolean goUp_raised;
				sc_boolean goDown_raised;
				sc_boolean goLeft_raised;
				sc_boolean goRight_raised;
		};
		
		
		/*! Returns an instance of the interface class 'SCI_Control'. */
		SCI_Control* getSCI_Control();
		
		//! Inner class for Sensor interface scope.
		class SCI_Sensor {
			
			public:
				/*! Gets the value of the variable 'up' that is defined in the interface scope 'Sensor'. */ 
				sc_boolean get_up();
				
				/*! Sets the value of the variable 'up' that is defined in the interface scope 'Sensor'. */ 
				void set_up(sc_boolean value);
				
				/*! Gets the value of the variable 'down' that is defined in the interface scope 'Sensor'. */ 
				sc_boolean get_down();
				
				/*! Sets the value of the variable 'down' that is defined in the interface scope 'Sensor'. */ 
				void set_down(sc_boolean value);
				
				/*! Gets the value of the variable 'left' that is defined in the interface scope 'Sensor'. */ 
				sc_boolean get_left();
				
				/*! Sets the value of the variable 'left' that is defined in the interface scope 'Sensor'. */ 
				void set_left(sc_boolean value);
				
				/*! Gets the value of the variable 'right' that is defined in the interface scope 'Sensor'. */ 
				sc_boolean get_right();
				
				/*! Sets the value of the variable 'right' that is defined in the interface scope 'Sensor'. */ 
				void set_right(sc_boolean value);
				
				
			private:
				friend class Robot_v1;
				sc_boolean up;
				sc_boolean down;
				sc_boolean left;
				sc_boolean right;
		};
		
		//! Inner class for Sensor interface scope operation callbacks.
		class SCI_Sensor_OCB {
			public:
				virtual ~SCI_Sensor_OCB() = 0;
				
				virtual sc_boolean updateUp(sc_integer x, sc_integer y) = 0;
				
				virtual sc_boolean updateDown(sc_integer x, sc_integer y) = 0;
				
				virtual sc_boolean updateLeft(sc_integer x, sc_integer y) = 0;
				
				virtual sc_boolean updateRight(sc_integer x, sc_integer y) = 0;
		};
		
		/*! Set the working instance of the operation callback interface 'SCI_Sensor_OCB'. */
		void setSCI_Sensor_OCB(SCI_Sensor_OCB* operationCallback);
		
		/*! Returns an instance of the interface class 'SCI_Sensor'. */
		SCI_Sensor* getSCI_Sensor();
		
		
		//! Inner class for internal interface scope operation callbacks.
		class InternalSCI_OCB {
			public:
				virtual ~InternalSCI_OCB() = 0;
				
				virtual sc_integer getStep(sc_string path, sc_integer i) = 0;
		};
		
		/*! Set the working instance of the operation callback interface 'InternalSCI_OCB'. */
		void setInternalSCI_OCB(InternalSCI_OCB* operationCallback);
		
		void init();
		
		void enter();
		
		void exit();
		
		void runCycle();
		
		void setTimer(TimerInterface* timer);
		
		TimerInterface* getTimer();
		
		void raiseTimeEvent(sc_eventid event);
		
		/*! Checks if the specified state is active. */
		sc_boolean isActive(Robot_v1States state);
	
	private:
	
		//! Inner class for internal interface scope.
		class InternalSCI {
			
			public:
				/*! Gets the value of the variable 'init_x' that is defined in the internal scope. */ 
				sc_integer get_init_x();
				
				/*! Gets the value of the variable 'init_y' that is defined in the internal scope. */ 
				sc_integer get_init_y();
				
				/*! Gets the value of the variable 'map_x' that is defined in the internal scope. */ 
				sc_integer get_map_x();
				
				/*! Sets the value of the variable 'map_x' that is defined in the internal scope. */ 
				void set_map_x(sc_integer value);
				
				/*! Gets the value of the variable 'map_y' that is defined in the internal scope. */ 
				sc_integer get_map_y();
				
				/*! Sets the value of the variable 'map_y' that is defined in the internal scope. */ 
				void set_map_y(sc_integer value);
				
				/*! Gets the value of the variable 'goal_x' that is defined in the internal scope. */ 
				sc_integer get_goal_x();
				
				/*! Sets the value of the variable 'goal_x' that is defined in the internal scope. */ 
				void set_goal_x(sc_integer value);
				
				/*! Gets the value of the variable 'goal_y' that is defined in the internal scope. */ 
				sc_integer get_goal_y();
				
				/*! Sets the value of the variable 'goal_y' that is defined in the internal scope. */ 
				void set_goal_y(sc_integer value);
				
				/*! Gets the value of the variable 'pos_x' that is defined in the internal scope. */ 
				sc_integer get_pos_x();
				
				/*! Sets the value of the variable 'pos_x' that is defined in the internal scope. */ 
				void set_pos_x(sc_integer value);
				
				/*! Gets the value of the variable 'pos_y' that is defined in the internal scope. */ 
				sc_integer get_pos_y();
				
				/*! Sets the value of the variable 'pos_y' that is defined in the internal scope. */ 
				void set_pos_y(sc_integer value);
				
				/*! Raises the in event 'PathReceived' that is defined in the internal scope. */ 
				void raise_pathReceived();
				
				/*! Checks if the out event 'PathReceived' that is defined in the internal scope has been raised. */ 
				sc_boolean isRaised_pathReceived();
				
				/*! Raises the in event 'deadEnd' that is defined in the internal scope. */ 
				void raise_deadEnd();
				
				/*! Checks if the out event 'deadEnd' that is defined in the internal scope has been raised. */ 
				sc_boolean isRaised_deadEnd();
				
				/*! Gets the value of the variable 'deadEndPath' that is defined in the internal scope. */ 
				sc_string get_deadEndPath();
				
				/*! Sets the value of the variable 'deadEndPath' that is defined in the internal scope. */ 
				void set_deadEndPath(sc_string value);
				
				/*! Gets the value of the variable 'nextStep' that is defined in the internal scope. */ 
				sc_integer get_nextStep();
				
				/*! Sets the value of the variable 'nextStep' that is defined in the internal scope. */ 
				void set_nextStep(sc_integer value);
				
				/*! Gets the value of the variable 'index' that is defined in the internal scope. */ 
				sc_integer get_index();
				
				/*! Sets the value of the variable 'index' that is defined in the internal scope. */ 
				void set_index(sc_integer value);
				
				
			private:
				friend class Robot_v1;
				sc_integer init_x;
				sc_integer init_y;
				sc_integer map_x;
				sc_integer map_y;
				sc_integer goal_x;
				sc_integer goal_y;
				sc_integer pos_x;
				sc_integer pos_y;
				sc_boolean PathReceived_raised;
				sc_boolean deadEnd_raised;
				sc_string deadEndPath;
				sc_integer nextStep;
				sc_integer index;
		};
	
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc_integer maxOrthogonalStates = 2;
		//! dimension of the state configuration vector for history states
		static const sc_integer maxHistoryStates = 1;
		
		TimerInterface* timer;
		sc_boolean timeEvents[14];
		
		Robot_v1States stateConfVector[maxOrthogonalStates];
		
		Robot_v1States historyVector[maxHistoryStates];
		sc_ushort stateConfVectorPosition;
		
		SCI_Comm ifaceComm;
		SCI_Comm_OCB* ifaceComm_OCB;
		SCI_Control ifaceControl;
		SCI_Sensor ifaceSensor;
		SCI_Sensor_OCB* ifaceSensor_OCB;
		InternalSCI ifaceInternalSCI;
		InternalSCI_OCB* ifaceInternalSCI_OCB;
		
		// prototypes of all internal functions
		
		void enact_SequenceImpl();
		void exact_SequenceImpl();
		void shenseq_SequenceImpl();
		void react_main_region_Start();
		void react_main_region_Comm_test_Comm_test_sd_Start();
		void react_main_region_Comm_test_Comm_test_sd_WaitForCloud();
		void react_main_region_Comm_test_Comm_test_sd_Link_Established();
		void react_main_region_Robot_Logic_Robot_Logic_sd_Init();
		void react_main_region_Robot_Logic_Robot_Logic_sd_Sensor_update();
		void react_main_region_Robot_Logic_Robot_Logic_sd_Up();
		void react_main_region_Robot_Logic_Robot_Logic_sd_Right();
		void react_main_region_Robot_Logic_Robot_Logic_sd_Check_goals();
		void react_main_region_Robot_Logic_Robot_Logic_sd_DeadEnd();
		void react_main_region_Robot_Logic_Robot_Logic_sd__final_();
		void react_main_region_Help_from_Cloud_Help_from_Cloud_sd_Send();
		void react_main_region_Help_from_Cloud_Help_from_Cloud_sd_Wait_for_Message();
		void react_main_region_Help_from_Cloud_Help_from_Cloud_sd_Help_received();
		void react_main_region_Path_Walking_Path_Walking_sd_Sensor_update();
		void react_main_region_Path_Walking_Path_Walking_sd_Next_Step();
		void react_main_region_Path_Walking_Path_Walking_sd_Init();
		void react_main_region_Path_Walking_Path_Walking_sd_Up();
		void react_main_region_Path_Walking_Path_Walking_sd_Right();
		void react_main_region_Path_Walking_Path_Walking_sd_Down();
		void react_main_region_Path_Walking_Path_Walking_sd_Left();
		void react_Robot_Logic_Control_Wait_for_Command();
		void react_Robot_Logic_Control_Go_Up();
		void react_Robot_Logic_Control_Go_Down();
		void react_Robot_Logic_Control_Go_Left();
		void react_Robot_Logic_Control_Go_Right();
		void clearInEvents();
		void clearOutEvents();
		
};
inline Robot_v1::SCI_Comm_OCB::~SCI_Comm_OCB() {}
inline Robot_v1::SCI_Sensor_OCB::~SCI_Sensor_OCB() {}
inline Robot_v1::InternalSCI_OCB::~InternalSCI_OCB() {}
#endif /* ROBOT_V1_H_ */
