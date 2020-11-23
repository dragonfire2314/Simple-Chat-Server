# Simple-Chat-Server

Worlds 3758th coolest chat server!
Better than flour.

//////////////////////////////////////////////////
//
// Names: Tanner Kern, Matt Masak, Andrew Zammetti
// Creation Date: November 15, 2020
// Due Date: November 24, 2020
// Course: CSC328 - Network Programming
// Professor Name: Dr. Frye
// Assignment: Simple Chat Server
// Filename: README.md
// Purpose: The README file for the project, including
//          folder manifest, responsibility matrix, and 
//          more.
//  
///////////////////////////////////////////////////

FOLDER MANIFEST:

client.cpp - Client side program, handles everything strictly client side
library.cpp - implementations of all functions in library.h 
library.h - declarations of all functions used by both server and client
server.cpp - All serverside operations occur here, such as displaying messages and writing to a log file
makefile - used to compile and run the project.
writeFile.txt - the log file
README.md - hmm, I wonder what this could be? 


RESPONSIBILITY MATRIX

Tanner Kern - Server side implementation (sending messages to other users, keeping track of IDs),
some client side implementation, editing the library
Matt Masak - Client side implementation, such as sending messages and accepting port CLA
Andrew Zammetti - Server side implementation, Logging messages, error checking, commentary and ID blocks, README editing


PROTOCOL

We used a series of infinite loops to wait for clients to send messages. The server initially
sends a HELLO message, then asks for a nickname. Once the nickname is sent (and is unique) the server
will begin waiting for messages to be sent. Once one is sent, it will send that message
to all other clients. It will also log the message in a separate file. 

We send the message to other clients by going through the list of socket IDs. If the socketID matches
the ID of the original message, it will not send this message that user. There is also a check here. 
If the message is "BYE" then the client will disconnect. 


ASSUMPTIONS

It is assumed that the server is running before a client operation is started. Otherwise, nothing will happen,
and the screen will display nothing. It is also assumed that there will not be multiple
client operations running on one machine. 


DEVELOPMENT PROCESS

The development went extremely smoothly. Tanner found this project fun, and wrote a large
portion of the server code in one night, simply because he was enjoying his time. Matt and Andrew
also found the project enjoyable, so working on it was not something we had to force ourselves to do.
Very few bugs were present during testing. The foundation that Tanner left Matt and Andrew to work with
was very well made, and any mistakes we made were very quickly taken out. Unfortunately, we all 
were extremely busy with other schoolwork and jobs, so we were only able to work on this project
in larger sections on fewer nights. In other words, we couldn't work a little day by day, but rather 
long sessions on fewer nights. 

