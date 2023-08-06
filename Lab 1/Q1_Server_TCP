#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

void searchNumber(int ns, int n, int arr[])
{
    int searchnum = 0;
    int found = 0;
    recv(ns, &searchnum, sizeof(searchnum), 0);
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == searchnum)
        {
            found = 1;
            break;
        }
    }
    send(ns, &found, sizeof(found), 0);
}

void sortarray(int ns, int n, int arr[])
{
    int sort_order = 0;
    recv(ns, &sort_order, sizeof(sort_order), 0);
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if ((sort_order == 1 && arr[j] > arr[j + 1]) || (sort_order == 2 && arr[j] < arr[j + 1]))
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    send(ns, arr, n * sizeof(int), 0);
}

void splitarray(int ns, int n, int arr[])
{
    int even_count = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] % 2 == 0)
        {
            even_count++;
        }
    }
    int odd_count = n - even_count;
    int even[even_count];
    int odd[odd_count];
    int x = 0;
    int y = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] % 2 == 0)
        {
            even[x] = arr[i];
            x++;
        }
        else
        {
            odd[y] = arr[i];
            y++;
        }
    }
    send(ns, &even_count, sizeof(even_count), 0);
    send(ns, even, even_count * sizeof(int), 0);
    send(ns, &odd_count, sizeof(odd_count), 0);
    send(ns, odd, odd_count * sizeof(int), 0);
}

int main()
{
    int s, r, recb, sntb, x, ns, a = 0;
    printf("Enter the port number: ");
    scanf("%d", &x);

    socklen_t len;
    struct sockaddr_in server, client;
    char buff[100];

    s = socket(AF_INET, SOCK_STREAM, 0); // socket is created
    if (s == -1)
    {
        printf("\nSocket creation error");
        exit(1);
    }
    printf("\nSocket created");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY); // server will listen to all available network interfaces
    server.sin_port = htons(x);                 // port number is set to the value entered by the user

    r = bind(s, (struct sockaddr *)&server, sizeof(server)); // binds the socket to the server address
    if (r == -1)
    {
        printf("\nBinding error");
        close(s);
        exit(1);
    }
    printf("\nBinding successful");

    r = listen(s, 1);
    if (r == -1)
    {
        close(s);
        exit(1);
    }
    printf("\nSocket listening");

    len = sizeof(client);
    ns = accept(s, (struct sockaddr *)&client, &len);
    if (ns == -1)
    {
        printf("\nAccept error");
        close(s);
        exit(1);
    }
    printf("\nConnection accepted");

    while (1)
    {
        int choice, n;
        int arr[100];
        recb = recv(ns, &choice, sizeof(choice), 0);
        if (recb == -1)
        {
            printf("\nMessage not received");
            close(ns);
            close(s);
            exit(1);
        }
        if (recb == 0)
        {
            printf("\nClient disconnected");
            close(ns);
            break;
        }
        switch (choice)
        {
        case 1: // search for a number
            recb = recv(ns, &n, sizeof(n), 0);
            if (recb == -1)
            {
                printf("\nMessage not received");
                close(ns);
                close(s);
                exit(1);
            }
            recb = recv(ns, arr, n * sizeof(int), 0);
            if (recb == -1)
            {
                printf("\nMessage not received");
                close(ns);
                close(s);
                exit(1);
            }
            searchNumber(ns, n, arr);
            break;

        case 2: // sort the array
            recb = recv(ns, &n, sizeof(n), 0);
            if (recb == -1)
            {
                printf("\nMessage not received");
                close(ns);
                close(s);
                exit(1);
            }
            recb = recv(ns, arr, n * sizeof(int), 0);
            if (recb == -1)
            {
                printf("\nMessage not received");
                close(ns);
                close(s);
                exit(1);
            }
            sortarray(ns, n, arr);
            break;

        case 3: // split even and odd arrays
            recb = recv(ns, &n, sizeof(n), 0);
            if (recb == -1)
            {
                printf("\nMessage not received");
                close(ns);
                close(s);
                exit(1);
            }
            recb = recv(ns, arr, n * sizeof(int), 0);
            if (recb == -1)
            {
                printf("\nMessage not received");
                close(ns);
                close(s);
                exit(1);
            }
            splitarray(ns, n, arr);
            break;

        default:
            // Invalid choice
            break;
        }
    }

    close(ns);
    close(s);
    return 0;
}
