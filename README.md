# Traceroute
Traceroute tracks the route packets taken from an IP network on their way to a given host.

<img src="https://www.lumen.com/content/dam/lumen/help/network/traceroute/traceroute-nine.png">

## Introduction
Welcome to my `ft_traceroute` project repository! In this project, I've implemented a custom version of the traceroute command. This project allowed me to dive into network protocols, socket programming, and Linux system calls.

## Project Summary
The `ft_traceroute` project focuses on creating a traceroute command from scratch. Traceroute is a utility that tracks the route a data packet takes from one machine to another within an IP network. The goal of the project is to gain a deeper understanding of networking and network diagnostics.

## Table of Contents
- [Introduction](#introduction)
- [Project Summary](#project-summary)
- [How to Compile](#how-to-compile)
- [Usage and Options](#usage-and-options)
- [Mandatory Part](#mandatory-part)
- [Bonus Part](#bonus-part)
- [Folder Structure](#folder-structure)
- [Submission and Peer-Evaluation](#submission-and-peer-evaluation)
- [Conclusion](#conclusion)

## How to Compile
1. Ensure you have a Linux machine with a core version of >= 4.0.
2. Clone this repository to your local machine using:```git clone <repository-url>```
3. Navigate to the repository's directory: ```cd traceroute```
4. Compile the program using the provided Makefile: ```make```

   
## Usage and Options
To run the `traceroute` program, use the following format:

```bash
./ft_traceroute [options] <destination>
```

Available options:
- `-f <ttl>`: Set the starting time-to-live (TTL) value.
- `-m <max_ttl>`: Set the maximum number of hops (TTL).
- `-w <timeout>`: Set the timeout for waiting for a response in seconds.
- `-?`: Display help and usage information.
- `-t <tos>`: Set the Type of Service (ToS) value.
- `-p <port>`: Specify the destination port number.

Replace `<destination>` with the DNS name or IP address of the target.

## Mandatory Part
In the mandatory part of the project, I implemented the core functionality of the traceroute command. I created a C program named `ft_traceroute` that calculates and displays the route of IP packets from the source to the destination.

## Bonus Part
For the bonus section, I added additional features to enhance the functionality of `ft_traceroute`. These features include DNS management and the implementation of various command-line options.

## Folder Structure
The repository's structure is organized as follows:

```bash
traceroute/
├── includes/ # Header files
├── srcs/ # Source code files
├── LICENSE # Project's license
├── Makefile # Makefile for compilation
└── README.md # Project README
```
## Conclusion

Creating the `traceroute` project has been an exciting journey into the world of networking and system programming. I've gained a deeper understanding of how data packets travel across networks and the intricacies of network diagnostics. By implementing the traceroute command from scratch, I've not only improved my C programming skills but also learned how to manage sockets, interact with IP addresses, and handle various network-related tasks.

Through this project, I've had the opportunity to explore both the mandatory and bonus parts, enhancing the traceroute functionality beyond its core implementation. From managing DNS resolution to implementing command-line options, I've expanded my programming toolkit and problem-solving abilities.

I'm proud to present my implementation of `ft_traceroute` and am confident that it showcases my dedication to learning and implementing complex concepts. This project has truly helped me develop a solid foundation in network programming and system calls, which will undoubtedly be valuable in my future endeavors.

Thank you for taking the time to explore my project and its capabilities. If you have any questions or feedback, feel free to reach out.
