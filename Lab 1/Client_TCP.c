#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int s, r, sntb;
    int x;
    printf("Enter the port number: ");
    scanf("%d", &x);

    socklen_t len;
    struct sockaddr_in server;
    char buff[100];

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
    {
        printf("\nSocket creation error");
        exit(1);
    }
    printf("\nSocket created");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(x);

    r = connect(s, (struct sockaddr *)&server, sizeof(server));
    if (r == -1)
    {
        printf("\nConnection error");
        close(s);
        exit(1);
    }
    printf("\nSocket connected");
    int choice;
    int n;
    int arr[100];
    do
    {
        printf("\nEnter the choice:\n1.Search for a number\n2.Sort the array\n3.Split even and odd numbers\n4.Exit\n");
        scanf("%d", &choice);
        send(s, &choice, sizeof(choice), 0);
        switch (choice)
        {
        case 1:
            printf("\nEnter the number of elements in the array: ");
            scanf("%d", &n);
            printf("\nEnter the elements of the array: ");
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &arr[i]);
            }
            send(s, &n, sizeof(n), 0);
            send(s, arr, n * sizeof(int), 0);
            int num, found;
            printf("\nEnter the numeber to be searched:");
            scanf("%d", &num);
            send(s, &num, sizeof(num), 0);
            recv(s, &found, sizeof(found), 0);
            if (found)
            {
                printf("\nNumber %d is found in the array: ", num);
            }
            else
            {
                printf("\nNumber %d was not found in the array: ", num);
            }
            break;
        case 2:
            printf("Enter the number of elements in the array: ");
            scanf("%d", &n);
            printf("Enter the elements of the array: ");
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &arr[i]);
            }

            send(s, &n, sizeof(n), 0);
            send(s, arr, n * sizeof(int), 0);

            int order;
            printf("Enter the order of sorting (1 for Ascending, 2 for Descending): ");
            scanf("%d", &order);

            send(s, &order, sizeof(order), 0);
            recv(s, arr, n * sizeof(int), 0);

            printf("The sorted array is: ");
            for (int i = 0; i < n; i++)
            {
                printf("%d ", arr[i]);
            }
            printf("\n");

            break;

        case 3:
            printf("\nEnter the number of elements in the array: ");
            scanf("%d", &n);
            printf("\nEnter the elements of the array: ");
            for (int i = 0; i < n; i++)
            {
                scanf("%d", &arr[i]);
            }
            send(s, &n, sizeof(n), 0);
            send(s, arr, n * sizeof(int), 0);
            int even_count, odd_count;
            recv(s, &even_count, sizeof(even_count), 0);
            int even[even_count];
            recv(s, even, even_count * sizeof(int), 0);

            printf("Even numbers: ");
            for (int i = 0; i < even_count; i++)
            {
                printf("%d ", even[i]);
            }
            printf("\n");

            recv(s, &odd_count, sizeof(odd_count), 0);
            int odd[odd_count];
            recv(s, odd, odd_count * sizeof(int), 0);

            printf("Odd numbers: ");
            for (int i = 0; i < odd_count; i++)
            {
                printf("%d ", odd[i]);
            }
            printf("\n");

            break;
        }
    } while (choice != 4);

    close(s);
    return 0;
}
