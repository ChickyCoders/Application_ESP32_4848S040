// /**
// @file

// */
// /*
//   Application example t

//   Library:: 

//   This version is

//   Copyright:: 2021 nguyentrinhtuan1996@gmail.com
// */

// #ifndef _Application_atApp_RDM_
// #define _Application_atApp_RDM_
// /* _____PROJECT INCLUDES____________________________________________________ */
// #include "..\\App.h"
// #include "..\src\services\modbus_master\atService_MB_TCP_MA.h"
// #include "..\src\obj\atObj_RDMs_Data.h"

// /* _____DEFINITIONS__________________________________________________________ */
// enum Status_of_device
// {
// 	Offline,
// 	Online
// };
// /* _____GLOBAL VARIABLES_____________________________________________________ */
// TaskHandle_t Task_atApp_RDM;  
// void atApp_RDM_Task_Func(void *parameter);
// ///////////////////////////////////////////////Testing part//
// /* _____GLOBAL FUNCTION______________________________________________________ */

// /* _____CLASS DEFINITION_____________________________________________________ */

// /**
//  * This Application class is the application to manage the 
//  */
// class App_RDM : public Application
// {
// public:
//   	App_RDM();
//  	~App_RDM();
//   	static void  App_RDM_Pend();
// 	static void  App_RDM_Start();
// 	static void  App_RDM_Restart();
// 	static void  App_RDM_Execute();
// 	static void  App_RDM_Suspend();
// 	static void  App_RDM_Resume();	  
// 	static void  App_RDM_End();
//   uint8_t number_of_try_to_connect = 3;
// protected:
//   uint8_t buffer;
//   uint8_t number_device;
// private:
// } atApp_RDM ;
// /**
//  * This function will be automaticaly called when a object is created by this class
//  */
// App_RDM::App_RDM(/* args */)
// {
//   	_Pend_User 	     = *App_RDM_Pend;
// 	_Start_User 	 = *App_RDM_Start;
// 	_Restart_User 	 = *App_RDM_Restart;
// 	_Execute_User 	 = *App_RDM_Execute;
// 	_Suspend_User	 = *App_RDM_Suspend;
// 	_Resume_User	 = *App_RDM_Resume;
// 	_End_User	     = *App_RDM_End;

// 	// change the ID of application
// 	ID_Application = 1;
// 	// change the application name
// 	Name_Application = (char*)"RDM Application";
// 	// change the ID of RDM
// }
// /**
//  * This function will be automaticaly called when the object of class is delete
//  */
// App_RDM::~App_RDM()
// {
	
// }
// /**
//  * Pend to start is the first task of this application it will do prerequisite condition. In the debit mode, task will send information of application to terminal to start the application.
//  */
// void  App_RDM::App_RDM_Pend()
// {
    
// }
// /**
//  * This start function will init some critical function 
//  */
// void  App_RDM::App_RDM_Start()
// {
// 	// init atXYZ Service in the fist running time
//   atService_MB_TCP_MA.Run_Service();
// }  
// /**
//  * Restart function of RDM  app
//  */
// void  App_RDM::App_RDM_Restart()
// {

// }
// /**
//  * Execute fuction of RDM app
//  */
// void  App_RDM::App_RDM_Execute()
// {	
//   if(atObject_RDMs_Data.RDM_number >= 1)
//   {
//     if(atApp_RDM.User_Mode == APP_USER_MODE_DEBUG)
//     {
//       Serial.println("RDM number |I0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|O_0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15");
//     }
//     for( atApp_RDM.number_device = 1; atApp_RDM.number_device <= atObject_RDMs_Data.RDM_number;
//                                                                     atApp_RDM.number_device++ )
//     {	
//       IPAddress IP_module( 	atObject_RDMs_Data.RDM[atApp_RDM.number_device].IP[0], 
//                          	  atObject_RDMs_Data.RDM[atApp_RDM.number_device].IP[1],
//                          	  atObject_RDMs_Data.RDM[atApp_RDM.number_device].IP[2],
// 		  					            atObject_RDMs_Data.RDM[atApp_RDM.number_device].IP[3]);         
//       // try to connect slave device
//       for( uint8_t try_connect = 1; try_connect <= atApp_RDM.number_of_try_to_connect; try_connect++)
//       {     
//         if(mb_TCP.isConnected(IP_module))
// 		    {    
//           // try to read
//           // for( uint8_t try_read = 0; try_read <= 2; try_read++)
//           // {
//             mb_TCP.writeHreg(IP_module, GENERAL_REGISTER_RW_DEVICE_ID, atApp_RDM.number_device);
//             mb_TCP.readCoil(IP_module,RDM_REGISTER_RW_INPUT_0, 
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].In0);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_INPUT_1,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].In1);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_INPUT_2,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].In2);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_INPUT_3,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].In3);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_INPUT_4,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].In4);  
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_INPUT_5,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].In5);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_INPUT_6,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].In6);
//             mb_TCP.readCoil(IP_module,RDM_REGISTER_RW_INPUT_7, 
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].In7);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_INPUT_8,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].In8);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_INPUT_9,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].In9);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_INPUT_10,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].In10);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_INPUT_11,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].In11);  
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_INPUT_12,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].In12);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_INPUT_13,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].In13);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_INPUT_14,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].In14);  
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_INPUT_15,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].In15);
//             mb_TCP.readCoil(IP_module,RDM_REGISTER_RW_OUTPUT_0, 
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out0);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_OUTPUT_1,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out1);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_OUTPUT_2,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out2);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_OUTPUT_3,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out3);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_OUTPUT_4,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out4);  
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_OUTPUT_5,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out5);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_OUTPUT_6,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out6);
//             mb_TCP.readCoil(IP_module,RDM_REGISTER_RW_OUTPUT_7, 
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out7);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_OUTPUT_8,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out8);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_OUTPUT_9,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out9);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_OUTPUT_10,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out10);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_OUTPUT_11,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out11);  
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_OUTPUT_12,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out12);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_OUTPUT_13,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out13);
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_OUTPUT_14,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out14);  
//             mb_TCP.readCoil(IP_module, RDM_REGISTER_RW_OUTPUT_15,
//                             &atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out15);
                       
//             atService_MB_TCP_MA.check_In();   
//             atService_MB_TCP_MA.Run_Service();
//             atService_MB_TCP_MA.check_Out();
//           // }     
//           atObject_RDMs_Data.RDM[atApp_RDM.number_device].Status_of_RDMs = Online;
//           atApp_RDM.buffer = 0;
//         }
//         else
//         {
//           atService_MB_TCP_MA.check_In();   
//           atService_MB_TCP_MA.Run_Service();
//           atService_MB_TCP_MA.check_Out();
//           mb_TCP.connect(IP_module);
//           atApp_RDM.buffer++;
//         }                                                                                                                   
//       }
      
//     if(atApp_RDM.buffer >= 1)
//     {
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].Status_of_RDMs = Offline;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].In1 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].In2 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].In3 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].In4 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].In5 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].In6 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].In7 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].In8 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].In9 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].In10 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].In11 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].In12 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].In13 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].In14 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].In15 = 0;

//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out1 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out2 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out3 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out4 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out5 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out6 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out7 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out8 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out9 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out10 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out11 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out12 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out13 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out14 = 0;
//       atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out15 = 0;
//       // atObject_RDMs_Data.RDM[atApp_RDM.number_device].IP[0] = 0; 
//       // atObject_RDMs_Data.RDM[atApp_RDM.number_device].IP[1] = 0;    
//       // atObject_RDMs_Data.RDM[atApp_RDM.number_device].IP[2] = 0;    
//       // atObject_RDMs_Data.RDM[atApp_RDM.number_device].IP[3] = 0;     
//       // atObject_RDMs_Data.RDM_number = atObject_RDMs_Data.RDM_number - 1 ;  
//     }
    
//     if(atApp_RDM.User_Mode == APP_USER_MODE_DEBUG)
//     {
//       Serial.printf("   RDM %d ",atApp_RDM.number_device);
//       Serial.print("   |");
// 			Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].In0);
//       Serial.print(" |");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].In1);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].In2);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].In3);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].In4);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].In5);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].In6);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].In7);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].In8);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].In9);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].In10);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].In11);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].In12);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].In13);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].In14);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].In15);
//       Serial.print("| ");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out0);
//       Serial.print(" |");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out1);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out2);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out3);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out4);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out5);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out6);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out7);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out8);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out9);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out10);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out11);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out12);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out13);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out14);
//       Serial.print("|");
//       Serial.print(atObject_RDMs_Data.RDM[atApp_RDM.number_device].Out15);
//       Serial.print("|");
//       Serial.print("\n");
      
//     }
//   }
// }
// }
// void  App_RDM::App_RDM_Suspend(){}
// void  App_RDM::App_RDM_Resume(){}	  
// void  App_RDM::App_RDM_End(){}
// void atApp_RDM_Task_Func(void *parameter)
// {
//   while (1)
//   {
//     atApp_RDM.Run_Application(APP_RUN_MODE_AUTO);
//     vTaskDelay(1000/ portTICK_PERIOD_MS);
//   }
// }
// #endif