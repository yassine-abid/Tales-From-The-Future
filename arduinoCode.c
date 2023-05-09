#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define SERIAL_PORT "/dev/ttyACM0" // Change this to match the serial port of your Arduino

int arduino()
{
    FILE* f = fopen("arduino.txt", "a");
    int serial_port = open(SERIAL_PORT, O_RDWR); // Open the serial port in read/write mode
    if (serial_port < 0) {
        perror("Error opening serial port");
        perror("NO CONTROLLER SUPPORT");
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(serial_port, &tty) != 0) {
        perror("Error getting serial port attributes");
        perror("NO CONTROLLER SUPPORT");
    }

    cfsetospeed(&tty, B9600); // Set the baud rate of the serial port to 9600
    cfsetispeed(&tty, B9600);

    tty.c_cflag |= (CLOCAL | CREAD); // Enable receiver and set local mode
    tty.c_cflag &= ~PARENB; // Disable parity
    tty.c_cflag &= ~CSTOPB; // Set one stop bit
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8; // Set data bits to 8

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Disable canonical mode and echoing
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable flow control
    tty.c_iflag &= ~(INLCR | ICRNL | IGNCR); // Disable newline translation
    tty.c_oflag &= ~(ONLCR | OCRNL); // Disable newline translation

    tty.c_cc[VMIN] = 0; // Set the minimum number of characters to read
    tty.c_cc[VTIME] = 100; // Set the timeout to 10 seconds

    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
        perror("Error setting serial port attributes");
        
    }

    printf("Reading data from serial port...\n");
    int input = 0;
    while (input != 1) {
        char buffer[256];
        int n = read(serial_port, buffer, sizeof(buffer));
        if (n > 0) {
            buffer[n] = '\0';
            fprintf(f,"Received data: %s\n", buffer);
            input = 1;
        }
    }

    close(serial_port);
    return 0;
}