#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/time.h>

#define SERIAL_PORT "/dev/ttyUSB0" // Change this to match the serial port of your Arduino

int configure_serial_port(int serial_port)
{
    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(serial_port, &tty) != 0)
    {
        perror("Error getting serial port attributes");
        return -1;
    }

    cfsetospeed(&tty, B115200); // Set the baud rate of the serial port to 9600
    cfsetispeed(&tty, B115200);

    tty.c_cflag |= (CLOCAL | CREAD); // Enable receiver and set local mode
    tty.c_cflag &= ~PARENB;          // Disable parity
    tty.c_cflag &= ~CSTOPB;          // Set one stop bit
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8; // Set data bits to 8

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Disable canonical mode and echoing
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);         // Disable flow control
    tty.c_iflag &= ~(INLCR | ICRNL | IGNCR);        // Disable newline translation
    tty.c_oflag &= ~(ONLCR | OCRNL);                // Disable newline translation

    tty.c_cc[VMIN] = 0;    // Set the minimum number of characters to read
    tty.c_cc[VTIME] = 100; // Set the timeout to 10 seconds

    if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
    {
        perror("Error setting serial port attributes");
        return -1;
    }
    return 0;
}

char *read_serial_line(int serial_port)
{
    char buffer[256];
    char c;
    int pos = 0;
    while (1)
    {
        int n = read(serial_port, &c, 1);
        if (n > 0)
        {
            if (c == '\n')
            {
                buffer[pos] = '\0';
                return strdup(buffer);
            }
            else if (pos < sizeof(buffer) - 1)
            {
                buffer[pos++] = c;
            }
        }
    }
}

void setup_arduino(int *serial_port)
{
    *serial_port = open(SERIAL_PORT, O_RDWR); // Open the serial port in read/write mode
    if (serial_port < 0)
    {
        perror("Error opening serial port");
        exit(EXIT_FAILURE);
    }

    if (configure_serial_port(*serial_port) != 0)
    {
        exit(EXIT_FAILURE);
    }

    printf("Reading data from serial port...\n");
}
void getInputs(int x[], int serial_port)
{

    char *line = read_serial_line(serial_port);
    // printf("%s",line);
    int val = atoi(line);

    for (int i = 0; i < 8; i++)
        if (val & (0x01 << i))
        {
            x[i] = 1;
        }
        else
        {
            x[i] = 0;
        }
    free(line);
}
