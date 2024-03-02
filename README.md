# minitalk
Mandatory Part
a communication program in the form of a client and a server.
The server must be started first. After its launch, it has to print its PID.
• The client takes two parameters:
◦ The server PID.
◦ The string to send.
The client sends the string passed as a parameter to the server. Once the string has been received, the server prints it.
• The server receives strings from several clients in a row without
needing to restart.
• The communication between the client and the server is done only using
UNIX signals: SIGUSR1 and SIGUSR2.

Bonus part (is not fully implemented)
• The server acknowledges every message received by sending back a signal to the client.
• Unicode characters support! 