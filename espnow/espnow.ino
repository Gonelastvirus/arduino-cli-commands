#include "painlessMesh.h"
#include <Arduino_JSON.h>
#include<HardwareSerial.h>
#define   MESH_PREFIX     "sensornetwork"
#define   MESH_PASSWORD   "sensor123"
#define   MESH_PORT       5555
HardwareSerial MySerial(1);
//Number for this node
int nodeNumber = 3;

//String to send to other nodes with sensor readings
String readings;

Scheduler userScheduler; // to control your personal task

//Create a painlessMesh object called mesh to handle the mesh network.
painlessMesh  mesh;
void sendMessage() ;
String getReadings();
//Create a task called taskSendMessage responsible for calling the sendMessage() function every five seconds as long as the program is running.
Task taskSendMessage( TASK_SECOND * 5 , TASK_FOREVER, &sendMessage );

String getReadings () {
  JSONVar jsonReadings;
  jsonReadings["node"] = nodeNumber;
  jsonReadings["temp"] = 60;
   // get soil sensor reading
 int soilReading = analogRead(A0);
  jsonReadings["hum"] =soilReading;
  readings = JSON.stringify(jsonReadings);
  return readings;//return in json
}
void sendMessage () {
  String msg = getReadings();//store as string that json
  mesh.sendBroadcast(msg);//send to other dvices
 
}
/**
// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
  JSONVar myObject = JSON.parse(msg.c_str());
  int node = myObject["node"];
  double temp = myObject["temp"];
  double hum = myObject["hum"];
  Serial.print("Node: ");
  Serial.println(node);
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %");
  MySerial.write(msg.c_str());
 
}
**/
//The newConnectionCallback() function runs whenever a new node joins the network. This function simply prints the chip ID of the new node. You can modify the function to do any other task.
void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}
//The changedConnectionCallback() function runs whenever a connection changes on the network (when a node joins or leaves the network).

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}
//The nodeTimeAdjustedCallback() function runs when the network adjusts the time, so that all nodes are synchronized. It prints the offset.

void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setup() {
	Serial.begin(115200);
	  //mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  MySerial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY, 2); // Tx17 Rx16 D4=17
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages
	mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
	//mesh.onReceive(&receivedCallback);
	mesh.onNewConnection(&newConnectionCallback);
	mesh.onChangedConnections(&changedConnectionCallback);
	mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
//Finally, add the taskSendMessage function to the userScheduler. The scheduler is responsible for handling and running the tasks at the right time.
	userScheduler.addTask(taskSendMessage);
	taskSendMessage.enable();
	}
void loop() {
  // it will run the user scheduler as well
 	 mesh.update();
}

