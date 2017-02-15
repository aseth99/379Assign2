#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	MY_PORT	8081

/* ---------------------------------------------------------------------
 This	is  a sample server which opens a stream socket and then awaits
 requests coming from client processes. In response for a request, the
 server sends an integer number  such	 that  different  processes  get
 distinct numbers. The server and the clients may run on different ma-
 chines.
 --------------------------------------------------------------------- */

int main()
{
	int	sock, snew, fromlength, number, outnum;

	char str[100];

	struct	sockaddr_in	master, from;
	printf("start\n");


	sock = socket (AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror ("Server: cannot open master socket");
		exit (1);
	}

	master.sin_family = AF_INET; //UNIX
	master.sin_addr.s_addr = inet_addr("127.0.0.1"); //INADDR_ANY;
	master.sin_port = htons (MY_PORT);

	if (bind (sock, (struct sockaddr*) &master, sizeof (master))) {
		perror ("Server: cannot bind master socket");
		exit (1);
	}

	number = 0;

	listen (sock, 5);

	// while (1) {
	// 	fromlength = sizeof (from);
	// 	snew = accept (sock, (struct sockaddr*) & from, & fromlength);
	// 	if (snew < 0) {
	// 		perror ("Server: accept failed");
	// 		exit (1);
	// 	}
	// 	outnum = htonl (number);
	// 	// write (snew, &outnum, sizeof (outnum));
	// 	close (snew);
	// 	number++;
	// }
	while (1) {
		snew = accept (sock, (struct sockaddr*) & from, & fromlength);
		read (snew, &str, sizeof (str));
		//server_function(str, snew); 
		fprintf (stderr, "The client sent you %s\n", str);

		if (str[0] == 'e') {
			break; 
		}

	}


	close (snew);
}

// void server_function (char str[], int socket) {

// 	// parse string: exit or command?
// 		// call command function



// 	return; 
// }
