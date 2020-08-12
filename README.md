Niyuj Test Document

Design of Server and Client folder :
1. Structure of the directories consists of following :
 a. interface : Interface is used to communicate with other entity.
 b. controller : Controller is used to encode and decode the messages and direct them to the appropriate events. (used functor logic for directing the messages to the appropriate event classes)
 c. entities : A class which identifies the entitiy on which the action should be taken.
 d. dao : A permanent storage of the entity when its created for first time. (used unorderd map)
 e. events : This contains the commands that are to be performed on the server (ls, cd, pwd, bye);
 f. encdec : This contains the class which is used for data transfer between server and client.

2. Server Receiving :
 a. Interface : 
    Interface contains a receiving thread and sending thread in UdpServerSocket.hpp (server) and UdpSocket.hpp (client).
	UdpWorker is the class which hides the internal representation of the UdpServerSocket (server) and UdpSocket (client).
	UdpWorker is the singleton class which is invoked during the application start up, and contains the pointer of UdpServerSocket (server) UdpSocket (client)
	Anything data received on UdpServerSocket(server)/UdpSocket(client) will be forwarded to UdpWorker on_receive.

 b. Controller : 
	Controller is a singleton class which will be invoked at the application startup.
	Controller contains two queues and two threads (1 for sending / 1 for receiving). 1 thread waiting on receiving queue and 1 thread waiting on sending queue.
	When the UdpWorker on_receive is called, the UdpWorker pushes that data on to the receiving queue of the controller.
	When the queue contains the data, the receiving thread of the controller decodes the data using RespMessage in enc_dec folder and according to the mesg type received it calls the appropriate event class constructor and modifies the Client class in entities folder.
	According to the client no the server checks its dao map for already present client and that object is used, If client is not already present then server will create the new client with the client no and the client object.


3. Client Sending :
 a. main :
	startup function in main contains the menu loop which specifies the commands to be performed on server (ls, pwd, cd).
	For testing you need to enter the IP address of the server, port of the server and the unique client no which identifies the client object.
	According to the option pressed in menu, the appropriate event class is created with ip port and client no values, if the client is already present in dao map that client object will be used, or else new client will be created.
	The process function of that event is called in which it pushes the data on the sending queue of the controller.
 b. Controller :
	Singleton class.
	The Controller then populates the data according the struct in which the server decodes the data, which is located in ReqMessage.hpp in enc_dec folder.
	Then the controller gets the udp worker object and calls the on send method, which in turn calls the UdpSocket send method which creates the udp socket and sends the data to server.
	Sending of this data is done on controller send thread.

4. Server Sending :
 a. events : 
	When the appropriate event class is invoked after the receipt of the message, the event class performs the action on the client in the load function(either new client/already present client).
	After the action is performed the process function of event is called which pushes the data into the controller sending queue.
 b. Controller :
	When the sending thread receives the data from the event, it calls the on send function of the UdpWorker, which creates a udp socket and sends it to the client.

5. Client Receving :
 a. Interface :
	Client receives the data on the interface UdpSocket receving thread, passes the data to UdpWorker on_receive.
 b. Controller :
	UdpWorker pushes the data on the receving queue of the controller, the controller decodes the message in RespMessage class in enc_dec folder.
	Controller then according to the mesg type received calls the appropriate event class and the event identifies the valid client by using client no displays the data in load function of the event.
 c. After which the deletion of the event class is done.
	
	

Singleton classes :
1. ClientDao
2. MessageController
3. UdpWorker

Session is maintained in the client and server after connection and implications of cd command is also handled using the map in dao class.


Notable Assumptions :
	1. Port no of server = 1234.
	2. Port no of client = 4321.
	In the menu, when we have to mention the ip address and the port of the server, please mention 1234, no need to specify the client port no in server, as it is taken care in the code.
	This code is tested on the one machine by using 127.0.0.1 ip address.

Build Instructions : Pthread Library needs to install for building the client and server.
Server folder :
	1. Run the make command in server folder.

Client Folder :
	1. Run the make command in client folder


OS :
	1. Code is being written, built and tested on Ubuntu OS.
