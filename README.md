# <p align="center"> Computer Networks Assignment</p>
##  <p align="center">Video File Transfer over TCP Sockets</p>
## Introduction

In this assignment, we implement a sender/receiver program to facilitate the transmission of video file contents over TCP sockets using GNU C on the Linux operating system. This application leverages the TCP/IP protocol to ensure reliable, ordered, and error-checked delivery of data between the sender and receiver. The sender program reads a video file, segments the data into manageable packets, and transmits these packets to the receiver. The receiver, on the other hand, captures these packets and reconstructs the original video file. This process demonstrates fundamental networking concepts and the practicality of socket programming in C.

## Requirements

* GCC compiler
* Linux operating system
* Basic knowledge of TCP/IP networking

## Components
* Sender Program : Reads a video file, segments it , and sends it over TCP. 
* Receiver Program : Receives segments from the sender and writes them into a new video file.

## _**Sender Functions :**_

The sender program performs the following key functions:

### Socket Creation:
   - A TCP socket is created using the `socket()` function, which specifies the address family (IPv4), socket type (stream), and protocol (TCP).

### Server Connection:
   - The program sets up the server address structure and uses `connect()` to establish a connection to the server, where the receiver is running.

### File Handling:
   - The sender opens the specified video file in binary mode using `fopen()`. This allows for direct reading of the file contents without data translation.

### Data Transmission:
   - The file is read in chunks (packets) using `fread()`, which reads a defined number of bytes (e.g., 1024 bytes) into a buffer. The program then sends these packets to the receiver using the `send()` function. 
   - This process continues until the end of the file is reached. After sending all data, the sender transmits an EOF message to indicate the completion of the file transfer.

### Cleanup:
   - Once the entire file is sent, the sender closes the file and the socket using `fclose()` and `close()` respectively.

## _**Reciever Functions :**_ 

The receiver program includes the following functionalities:

### Socket Creation and Binding:
   - Similar to the sender, a TCP socket is created and bound to a specific port using `bind()`, allowing it to listen for incoming connections.

### Listening for Connections:
   - The receiver calls `listen()` to accept incoming connection requests from the sender.

### Accepting Connections:
   - Once a connection is established with a client (sender), the receiver calls `accept()` to create a new socket for communication.

### File Creation:
   - A new file is opened for writing (in binary mode) using `fopen()`, where the received video data will be stored.

### Receiving Data:
   - The receiver uses `recv()` to receive incoming data packets from the sender. Each packet is written to the newly created file using `fwrite()`.
   - The program checks for the EOF message to determine when to stop receiving data. If this message is detected, it terminates the receiving loop.

### Cleanup:
   - After all data has been received and the EOF message has been processed, the receiver closes both the file and the socket.



