#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#define DB_SIZE 35
#define NO_OF_DISHES 100
#define NO_OF_DAYS 7
#define MAX_ORDER_SIZE 20
#define ORDER_DB_SIZE 14

typedef struct address
{
    float x_coordinate;
    float y_coordinate;
    int plot_no; // assuming plot number to be an integer
    char area_name[100];
    char city_name[50];
    int pincode;
} address;

typedef struct
{
    char order_time[24];
    char user_name[100];
    char contact_no[10];
    address user_address;
    char food_order[MAX_ORDER_SIZE][100];
    int food_order_quantity[MAX_ORDER_SIZE];
    float service_time;
    char promised_delivery_time[24];
    char orderID[8];
} order;

typedef struct
{
    char name[100];
    address rst_address;
    struct generic
    {
        char food[NO_OF_DISHES][100];
        int price[NO_OF_DISHES];
        float service_time[NO_OF_DISHES];
    } generic;

    struct special
    {
        char food[NO_OF_DISHES][100];
        int price[NO_OF_DISHES];
        float service_time[NO_OF_DISHES];
    } special;

    struct item_of_the_day
    {
        char food[NO_OF_DAYS][100];
        int price[NO_OF_DAYS];
        float service_time[NO_OF_DAYS];
    } item_of_the_day;

    order ord[ORDER_DB_SIZE];

} restaurant;

void initializeDB(restaurant rst[])
{
    for (int i = 0; i < DB_SIZE; i++)
    {
        rst[i].name[0] = '\0';
        rst[i].rst_address.x_coordinate = 0.0;
        rst[i].rst_address.y_coordinate = 0.0;
        rst[i].rst_address.plot_no = 0;
        rst[i].rst_address.area_name[0] = '\0';
        rst[i].rst_address.city_name[0] = '\0';
        rst[i].rst_address.pincode = 0;

        for (int j = 0; j < NO_OF_DISHES; j++)
        {
            rst[i].generic.food[j][0] = '\0';
            rst[i].generic.price[j] = 0;
            rst[i].generic.service_time[j] = 0.0;
        }
        for (int j = 0; j < NO_OF_DISHES; j++)
        {
            rst[i].special.food[j][0] = '\0';
            rst[i].special.price[j] = 0;
            rst[i].special.service_time[j] = 0.0;
        }
        for (int j = 0; j < NO_OF_DAYS; j++)
        {
            rst[i].item_of_the_day.food[j][0] = '\0';
            rst[i].item_of_the_day.price[j] = 0;
            rst[i].item_of_the_day.service_time[j] = 0.0;
        }
        for (int j = 0; j < ORDER_DB_SIZE; j++)
        {
            rst[i].ord[j].service_time = 0.0;
            rst[i].ord[j].order_time[0] = '\0';
            rst[i].ord[j].promised_delivery_time[0] = '\0';
            rst[i].name[0] = '\0';
            rst[i].ord[j].user_address.x_coordinate = 0;
            rst[i].ord[j].user_address.y_coordinate = 0;
            rst[i].ord[j].user_address.plot_no = 0;
            rst[i].ord[j].user_address.area_name[0] = '\0';
            rst[i].ord[j].user_address.city_name[0] = '\0';
            rst[i].ord[j].user_address.pincode = 0;
            rst[i].ord[j].contact_no[0] = '\0';
            for (int k = 0; k < MAX_ORDER_SIZE; k++)
            {
                rst[i].ord[j].food_order[k][0] = '\0';
                rst[i].ord[j].food_order_quantity[k] = 0;
            }
        }
    }
}

void addtime(char deliverytime[], float service_time)
{
    service_time = service_time * 60;
    int minutes = 0, hours = 0;
    minutes = minutes + (int)(deliverytime[15] - '0');
    minutes = minutes + (int)(deliverytime[14] - '0') * 10;
    hours = hours + (int)(deliverytime[12] - '0');
    hours = hours + (int)(deliverytime[11] - '0') * 10;
    minutes = minutes + (int)service_time;
    if (minutes >= 60)
    {
        hours = hours + (minutes / 60);
        minutes = minutes % 60;
    }
    hours = hours % 24;
    deliverytime[11] = (char)(hours / 10 + '0');
    deliverytime[12] = (char)(hours % 10 + '0');
    deliverytime[14] = (char)(minutes / 10 + '0');
    deliverytime[15] = (char)(minutes % 10 + '0');
}

void sortRestaurants(restaurant rst[])
{
    int i = 0;
    int sorted = 0;
    while ((i < DB_SIZE) && (sorted == 0))
    {
        sorted = 1;
        int j = 0;
        while (j < DB_SIZE - i - 1 && rst[j].name[0] != '\0' && rst[j + 1].name[j + 1] != '\0')
        {
            if ((strcmp(rst[j].name, rst[j + 1].name) > 0))
            {
                restaurant temp = rst[j];
                rst[j] = rst[j + 1];
                rst[j + 1] = temp;
                sorted = 0;
            }
            else if ((strcmp(rst[j].name, rst[j + 1].name) == 0))
            {
                if ((strcmp(rst[j].rst_address.city_name, rst[j + 1].rst_address.city_name) > 0))
                {
                    restaurant temp = rst[j];
                    rst[j] = rst[j + 1];
                    rst[j + 1] = temp;
                    sorted = 0;
                }
                else if ((strcmp(rst[j].rst_address.city_name, rst[j + 1].rst_address.city_name) == 0))
                {
                    if ((strcmp(rst[j].rst_address.area_name, rst[j + 1].rst_address.area_name) > 0))
                    {
                        restaurant temp = rst[j];
                        rst[j] = rst[j + 1];
                        rst[j + 1] = temp;
                        sorted = 0;
                    }
                    else if ((strcmp(rst[j].rst_address.area_name, rst[j + 1].rst_address.area_name) == 0))
                    {
                        if (rst[j].rst_address.plot_no > rst[j + 1].rst_address.plot_no)
                        {
                            restaurant temp = rst[j];
                            rst[j] = rst[j + 1];
                            rst[j + 1] = temp;
                            sorted = 0;
                        }
                    }
                }
            }
            j++;
        }
        i++;
    }
}

void getMinTime(restaurant rst[], char food_item[], int quantity)
{
    int found_in_type;
    int rst_no;
    int item_no;
    int flag1 = 1;
    float time = 50.0;

    for (int i = 0; i < DB_SIZE && flag1 == 1; i++)
    {
        if (rst[i].name[0] != '\0')
        {
            for (int j = 0; j < NO_OF_DISHES; j++)
            {
                if (strcmp(rst[i].generic.food[j], food_item) == 0)
                {
                    if (time > rst[i].generic.service_time[j])
                    {
                        rst_no = i;
                        item_no = j;
                        found_in_type = 1;
                        time = rst[i].generic.service_time[j];
                    }
                }
                if (strcmp(rst[i].special.food[j], food_item) == 0)
                {
                    if (time > rst[i].special.service_time[j])
                    {
                        rst_no = i;
                        item_no = j;
                        found_in_type = 2;
                        time = rst[i].special.service_time[j];
                    }
                }
                if (j < NO_OF_DAYS)
                {
                    if (strcmp(rst[i].item_of_the_day.food[j], food_item) == 0)
                    {
                        if (time > rst[i].item_of_the_day.service_time[j])
                        {
                            rst_no = i;
                            item_no = j;
                            found_in_type = 3;
                            time = rst[i].item_of_the_day.service_time[j];
                        }
                    }
                }
            }
        }
        else
            flag1 = 0;
    }

    if (found_in_type == 1)
    {
        printf("Restaurant: %s\n", rst[rst_no].name);
        printf("coordinates : %f , %f \n", rst[rst_no].rst_address.x_coordinate, rst[rst_no].rst_address.y_coordinate);
        printf("Plot no : %d\n", rst[rst_no].rst_address.plot_no);
        printf("Area name : %s\n", rst[rst_no].rst_address.area_name);
        printf("City name : %s\n", rst[rst_no].rst_address.city_name);
        printf("Pincode : %d\n", rst[rst_no].rst_address.pincode);
        printf("Delivery time: %0.2f hours\n", quantity * rst[rst_no].generic.service_time[item_no]);
    }
    else if (found_in_type == 2)
    {
        printf("Restaurant: %s\n", rst[rst_no].name);
        printf("coordinates : %f , %f \n", rst[rst_no].rst_address.x_coordinate, rst[rst_no].rst_address.y_coordinate);
        printf("Plot no : %d\n", rst[rst_no].rst_address.plot_no);
        printf("Area name : %s\n", rst[rst_no].rst_address.area_name);
        printf("City name : %s\n", rst[rst_no].rst_address.city_name);
        printf("Pincode : %d\n", rst[rst_no].rst_address.pincode);
        printf("Delivery time: %0.2f hours\n", quantity * rst[rst_no].special.service_time[item_no]);
    }
    else if (found_in_type == 3)
    {
        printf("Restaurant: %s\n", rst[rst_no].name);
        printf("coordinates : %f , %f \n", rst[rst_no].rst_address.x_coordinate, rst[rst_no].rst_address.y_coordinate);
        printf("Plot no : %d\n", rst[rst_no].rst_address.plot_no);
        printf("Area name : %s\n", rst[rst_no].rst_address.area_name);
        printf("City name : %s\n", rst[rst_no].rst_address.city_name);
        printf("Pincode : %d\n", rst[rst_no].rst_address.pincode);
        printf("Delivery time: %0.2f hours\n", quantity * rst[rst_no].item_of_the_day.service_time[item_no]);
    }
    else
        printf("%s is not available right now.\n", food_item);
}

void getItemAvailability(restaurant rst[], char food_item[])
{
    int flag1 = 1;
    int found = 0;
    printf("\n%s is available at: \n\n", food_item);
    for (int i = 0; i < DB_SIZE && flag1 == 1; i++)
    {
        int flag2 = 1;
        if (strlen(rst[i].name) != 0)
        {
            int no_of_generic = 0;
            int no_of_special = 0;
            int j = 0;
            while (rst[i].generic.food[j][0] != '\0')
            {
                no_of_generic++;
                j++;
            }
            j = 0;
            while (rst[i].special.food[j][0] != '\0')
            {
                no_of_special++;
                j++;
            }
            int low = 0, high = no_of_generic;
            while (low <= high && flag2 == 1)
            {
                int mid = (low + high) / 2;
                if (strcmp(rst[i].generic.food[mid], food_item) == 0)
                {
                    flag2 = 0;
                    found = 1;
                    printf("-- %s for Rs %d / plate.\n", rst[i].name, rst[i].generic.price[mid]);
                }
                else if (strcmp(rst[i].generic.food[mid], food_item) > 0)
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            if (flag2 == 1)
            {
                low = 0, high = no_of_special;
                while (low <= high && flag2 == 1)
                {
                    int mid = (low + high) / 2;
                    if (strcmp(rst[i].special.food[mid], food_item) == 0)
                    {
                        flag2 = 0;
                        found = 1;
                        printf("-- %s for Rs %d / plate.\n", rst[i].name, rst[i].special.price[mid]);
                    }
                    else if (strcmp(rst[i].special.food[mid], food_item) > 0)
                        high = mid - 1;
                    else
                        low = mid + 1;
                }
            }
            if (flag2 == 1)
            {
                for (int j = 0; j < NO_OF_DAYS; j++)
                {
                    if (strcmp(rst[i].item_of_the_day.food[j], food_item) == 0)
                        printf("-- %s for Rs %d / plate.\n", rst[i].name, rst[i].item_of_the_day.price[j]);
                }
            }
        }
        else
            flag1 = 0;
    }
    if (found == 0)
        printf("None of the restaurants.\n");
}

void sortGenericDishes(restaurant rst[])
{
    // Sorting generic food items
    for (int idx = 0; idx < DB_SIZE; idx++)
    {
        int i = 0;
        int sorted = 0;
        while (i < NO_OF_DISHES && rst[idx].generic.food[i][0] != '\0' && sorted == 0)
        {
            int j = 0;
            sorted = 1;
            while (j < NO_OF_DISHES - i - 1 && rst[idx].generic.food[j][0] != '\0' && rst[idx].generic.food[j + 1][0] != '\0')
            {
                if (strcmp(rst[idx].generic.food[j], rst[idx].generic.food[j + 1]) > 0)
                {
                    char temp[100];
                    strcpy(temp, rst[idx].generic.food[j]);
                    strcpy(rst[idx].generic.food[j], rst[idx].generic.food[j + 1]);
                    strcpy(rst[idx].generic.food[j + 1], temp);

                    int itemp = rst[idx].generic.price[j];
                    rst[idx].generic.price[j] = rst[idx].generic.price[j + 1];
                    rst[idx].generic.price[j + 1] = itemp;

                    float ftemp = rst[idx].generic.service_time[j];
                    rst[idx].generic.service_time[j] = rst[idx].generic.service_time[j + 1];
                    rst[idx].generic.service_time[j + 1] = ftemp;
                    sorted = 0;
                }
                j++;
            }
            i++;
        }
    }
}

void sortSpecialDishes(restaurant rst[])
{
    // Sorting special food items
    for (int idx = 0; idx < DB_SIZE; idx++)
    {
        int i = 0;
        int sorted = 0;
        while (i < NO_OF_DISHES && rst[idx].special.food[i][0] != '\0')
        {
            int j = 0;
            sorted = 1;
            while (j < NO_OF_DISHES - i - 1 && rst[idx].special.food[j][0] != '\0' && rst[idx].special.food[j + 1][0] != '\0')
            {
                if (strcmp(rst[idx].special.food[j], rst[idx].special.food[j + 1]) > 0)
                {
                    char temp[100];
                    strcpy(temp, rst[idx].special.food[j]);
                    strcpy(rst[idx].special.food[j], rst[idx].special.food[j + 1]);
                    strcpy(rst[idx].special.food[j + 1], temp);

                    int itemp = rst[idx].special.price[j];
                    rst[idx].special.price[j] = rst[idx].special.price[j + 1];
                    rst[idx].special.price[j + 1] = itemp;

                    float ftemp = rst[idx].special.service_time[j];
                    rst[idx].special.service_time[j] = rst[idx].special.service_time[j + 1];
                    rst[idx].special.service_time[j + 1] = ftemp;
                    sorted = 0;
                }
                j++;
            }
            i++;
        }
    }
}

void getItemListInSortedOrder(restaurant rst[], char restaurant_name[], int noofrst)
{
    int found = -1;
    int low = 0;
    int high = noofrst;
    while (low <= high && found == -1)
    {
        int mid = (low + high) / 2;
        if (strcmp(rst[mid].name, restaurant_name) == 0)
        {
            found = mid;
        }
        else if (strcmp(rst[mid].name, restaurant_name) > 0)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    int flag = 0;

    if (found > -1)
    {
        printf("\nGeneric Food:\n");
        for (int j = 0; j < NO_OF_DISHES && flag == 0; j++)
        {
            if (rst[found].generic.price[j] != 0)
                printf("%d) %s, Rs %d / plate\n", j + 1, rst[found].generic.food[j], rst[found].generic.price[j]);
            else
                flag = 1;
        }
        printf("\n");
        flag = 0;
        printf("Special Food:\n");
        for (int j = 0; j < NO_OF_DISHES && flag == 0; j++)
        {
            if (rst[found].special.price[j] != 0)
                printf("%d) %s, Rs %d / plate\n", j + 1, rst[found].special.food[j], rst[found].special.price[j]);
            else
                flag = 1;
        }
        printf("\n");
        printf("Item of the day:\n");
        printf("Sunday:    %s, Rs %d / plate\n", rst[found].item_of_the_day.food[0], rst[found].item_of_the_day.price[0]);
        printf("Monday:    %s, Rs %d / plate\n", rst[found].item_of_the_day.food[1], rst[found].item_of_the_day.price[1]);
        printf("Tuesday:   %s, Rs %d / plate\n", rst[found].item_of_the_day.food[2], rst[found].item_of_the_day.price[2]);
        printf("Wednesday: %s, Rs %d / plate\n", rst[found].item_of_the_day.food[3], rst[found].item_of_the_day.price[3]);
        printf("Thursday:  %s, Rs %d / plate\n", rst[found].item_of_the_day.food[4], rst[found].item_of_the_day.price[3]);
        printf("Friday:    %s, Rs %d / plate\n", rst[found].item_of_the_day.food[5], rst[found].item_of_the_day.price[4]);
        printf("Saturday:  %s, Rs %d / plate\n", rst[found].item_of_the_day.food[6], rst[found].item_of_the_day.price[5]);
    }
    else
    {
        printf("\n%s is not available in our Database.\n", restaurant_name);
    }
}

void getItemListInAreaSortedOrder(restaurant rst[], char area[])
{
    int flag1 = 1;
    int flag2 = 0;
    int found = 0;
    printf("List of restaurants in the specified area -- %s\n\n", area);
    for (int i = 0; i < DB_SIZE && flag1 == 1; i++)
    {
        if (rst[i].name[0] != '\0')
        {
            if (strcmp(rst[i].rst_address.area_name, area) == 0)
            {
                printf("[ %s ]\n", rst[i].name);
                for (int j = 0; j < NO_OF_DISHES && flag2 == 0; j++)
                {
                    if (rst[found].generic.price[j] != 0)
                        printf("%d) %s, Rs %d / plate\n", j + 1, rst[i].generic.food[j], rst[i].generic.price[j]);
                    else
                        flag2 = 1;
                }
                printf("\n");
                flag2 = 0;
                printf("Special Food:\n");
                for (int j = 0; j < NO_OF_DISHES && flag2 == 0; j++)
                {
                    if (rst[i].special.price[j] != 0)
                        printf("%d) %s, Rs %d / plate\n", j + 1, rst[i].special.food[j], rst[i].special.price[j]);
                    else
                        flag2 = 1;
                }
                printf("\n");
                printf("Item of the day:\n");
                printf("Sunday:    %s, Rs %d / plate\n", rst[i].item_of_the_day.food[0], rst[i].item_of_the_day.price[0]);
                printf("Monday:    %s, Rs %d / plate\n", rst[i].item_of_the_day.food[1], rst[i].item_of_the_day.price[1]);
                printf("Tuesday:   %s, Rs %d / plate\n", rst[i].item_of_the_day.food[2], rst[i].item_of_the_day.price[2]);
                printf("Wednesday: %s, Rs %d / plate\n", rst[i].item_of_the_day.food[3], rst[i].item_of_the_day.price[3]);
                printf("Thursday:  %s, Rs %d / plate\n", rst[i].item_of_the_day.food[4], rst[i].item_of_the_day.price[3]);
                printf("Friday:    %s, Rs %d / plate\n", rst[i].item_of_the_day.food[5], rst[i].item_of_the_day.price[4]);
                printf("Saturday:  %s, Rs %d / plate\n", rst[i].item_of_the_day.food[6], rst[i].item_of_the_day.price[5]);
                printf("\n");
                found = 1;
            }
        }
        else
            flag1 = 0;
    }

    if (found == 0)
        printf("None\n");
}

void getAllSpecialItemListinSortedOrder(restaurant rst[], char rst_list[][100], int n)
{
    int flag;
    int j = 0;
    int done;
    int found;
    while (j < n)
    {
        flag = 1;
        found = 0;
        for (int i = 0; i < DB_SIZE && flag == 1; i++)
        {
            if (rst[i].name[0] != '\0')
            {
                if (strcmp(rst[i].name, rst_list[j]) == 0)
                {
                    printf("Restaurant: %s\n", rst[i].name);
                    printf("coordinates : %f , %f \n", rst[i].rst_address.x_coordinate, rst[i].rst_address.y_coordinate);
                    printf("Plot no : %d\n", rst[i].rst_address.plot_no);
                    printf("Area name : %s\n", rst[i].rst_address.area_name);
                    printf("City name : %s\n", rst[i].rst_address.city_name);
                    printf("Pincode : %d\n", rst[i].rst_address.pincode);
                    printf("Special Items:\n");
                    done = 0;
                    for (int k = 0; k < NO_OF_DISHES && done == 0; k++)
                    {
                        if (strlen(rst[i].special.food[k]) != 0)
                        {
                            printf("%d) %s for %d / plate\n", k + 1, rst[i].special.food[k], rst[i].special.price[k]);
                        }
                        else
                            done = 1;
                    }
                    found = 1;
                    printf("\n");
                }
            }
            else
                flag = 0;
        }
        if (found == 0)
            printf("%s Restaurant not found in your region.\n\n", rst_list[j]);
        j++;
    }
}

void sort_item_of_the_day(restaurant rst)
{
    char food[NO_OF_DAYS][100];
    int prices[NO_OF_DAYS];
    float serviceTime[NO_OF_DAYS];
    for (int i = 0; i < NO_OF_DAYS; i++)
    {
        strcpy(food[i], rst.item_of_the_day.food[i]);
        prices[i] = rst.item_of_the_day.price[i];
        serviceTime[i] = rst.item_of_the_day.service_time[i];
    }
    int i = 0;
    int sorted = 0;
    while ((i < NO_OF_DAYS) && (sorted == 0))
    {
        int j = 0;
        sorted = 1;
        while (j < NO_OF_DAYS - i - 1)
        {
            if (strcmp(food[j], food[j + 1]) > 0)
            {
                char temp[100];
                strcpy(temp, food[j]);
                strcpy(food[j], food[j + 1]);
                strcpy(food[j + 1], temp);

                int itemp = prices[j];
                prices[j] = prices[j + 1];
                prices[j + 1] = itemp;

                float ftemp = serviceTime[j];
                serviceTime[j] = serviceTime[j + 1];
                serviceTime[j + 1] = ftemp;

                sorted = 0;
            }
            else if (strcmp(food[j], food[j + 1]) == 0)
            {
                if (prices[j] > prices[j + 1])
                {
                    char temp[100];
                    strcpy(temp, food[j]);
                    strcpy(food[j], food[j + 1]);
                    strcpy(food[j + 1], temp);

                    int itemp = prices[j];
                    prices[j] = prices[j + 1];
                    prices[j + 1] = itemp;

                    float ftemp = serviceTime[j];
                    serviceTime[j] = serviceTime[j + 1];
                    serviceTime[j + 1] = ftemp;

                    sorted = 0;
                }
            }
            j++;
        }
        i++;
    }
    printf("Restaurant Name : %s\n", rst.name);
    printf("coordinates : %f , %f \n", rst.rst_address.x_coordinate, rst.rst_address.y_coordinate);
    printf("Plot no : %d\n", rst.rst_address.plot_no);
    printf("Area name : %s\n", rst.rst_address.area_name);
    printf("City name : %s\n", rst.rst_address.city_name);
    printf("Pincode : %d\n", rst.rst_address.pincode);
    for (int i = 0; i < NO_OF_DAYS; i++)
    {
        printf("%d) %s Price: %d / plate\n", i + 1, food[i], prices[i]);
    }
    printf("\n");
}

void getItemofDayListinSortedOrder(restaurant rst[], char area[])
{
    int found = 0;
    printf("\nYour specified area : %s\n", area);
    for (int i = 0; i < DB_SIZE; i++)
    {
        if (strcmp(rst[i].rst_address.area_name, area) == 0)
        {
            sort_item_of_the_day(rst[i]); // as declared the function also prints the result needed
            found = 1;
        }
    }
    if (found == 0)
    {
        printf("No restaurant in our database in the specified area\n");
    }
}

float isAvailable(restaurant rst[], char items[][100], char usr_city[], int x, int no_of_items)
{
    int no_of_generic = 0;
    int no_of_special = 0;
    int i = 0;
    int result = 0;
    float delivery_time = 0.0;
    if (strcmp(rst[x].rst_address.city_name, usr_city) == 0)
    {
        while (rst[x].generic.food[i][0] != '\0')
        {
            no_of_generic++;
            i++;
        }
        i = 0;
        while (rst[x].special.food[i][0] != '\0')
        {
            no_of_special++;
            i++;
        }

        for (int i = 0; i < no_of_items; i++)
        {
            int low = 0;
            int high = no_of_generic;
            int found = 0;
            while (low <= high && found == 0)
            {
                int mid = (low + high) / 2;
                if ((strcmp(items[i], rst[x].generic.food[mid]) == 0))
                {
                    found = 1;
                    delivery_time = delivery_time + rst[x].generic.service_time[mid];
                }
                else if (strcmp(items[i], rst[x].generic.food[mid]) > 0)
                    low = mid + 1;
                else
                    high = mid - 1;
            }
            if (found == 0)
            {
                low = 0;
                high = no_of_special;
                while (low <= high && found == 0)
                {
                    int mid = (low + high) / 2;
                    if (strcmp(items[i], rst[x].special.food[mid]) == 0)
                    {
                        found = 1;
                        delivery_time = delivery_time + rst[x].special.service_time[mid];
                    }
                    else if (strcmp(items[i], rst[x].special.food[mid]) > 0)
                        low = mid + 1;
                    else
                        high = mid - 1;
                }
            }
            if (found == 0)
            {
                for (int j = 0; j < NO_OF_DAYS && found == 0; j++)
                {
                    if (strcmp(items[i], rst[x].item_of_the_day.food[j]) == 0)
                    {
                        found = 1;
                        delivery_time = delivery_time + rst[x].item_of_the_day.service_time[j];
                    }
                }
            }
            if (found == 1)
                result++;
        }
    }
    if (result == no_of_items)
        return delivery_time;
    else
        return 0.0;
}

void placeOrder(restaurant rst[], char items[][100], int quantity[], char usr_name[], char phone_no[], address usr_address, int no_of_items, int ordidx[])
{
    int flag = 1;
    int found = 0;
    int idx;
    float delivery_time = 0.0;
    for (int i = 0; i < DB_SIZE && flag == 1; i++)
    {
        if (rst[i].name[0] != '\0')
        {
            delivery_time = isAvailable(rst, items, usr_address.city_name, i, no_of_items);
            if (delivery_time > 0)
            {
                found = 1;
                flag = 0;
                idx = i;
            }
        }
        else
            flag = 0;
    }
    if (found)
    {
        int ord_idx = ordidx[idx];
        strcpy(rst[idx].ord[ord_idx].user_name, usr_name);
        strcpy(rst[idx].ord[ord_idx].user_address.area_name, usr_address.area_name);
        strcpy(rst[idx].ord[ord_idx].user_address.city_name, usr_address.city_name);
        rst[idx].ord[ord_idx].user_address.pincode = usr_address.pincode;
        rst[idx].ord[ord_idx].user_address.plot_no = usr_address.plot_no;
        rst[idx].ord[ord_idx].user_address.x_coordinate = usr_address.x_coordinate;
        rst[idx].ord[ord_idx].user_address.y_coordinate = usr_address.y_coordinate;
        strcpy(rst[idx].ord[ord_idx].contact_no, phone_no);
        for (int i = 0; i < no_of_items; i++)
        {
            strcpy(rst[idx].ord[ord_idx].food_order[i], items[i]);
            rst[idx].ord[ord_idx].food_order_quantity[i] = quantity[i];
        }
        float x_d = usr_address.x_coordinate - rst[idx].rst_address.x_coordinate;
        float y_d = usr_address.y_coordinate - rst[idx].rst_address.y_coordinate;
        double distance = (double)sqrt((x_d * x_d) + (y_d * y_d));
        distance = (int)distance;
        float travel_time = distance * 1.0 / (40 * 1.0); // assuming coordinates are in km and economy speed to be 40km/h
        rst[idx].ord[ord_idx].service_time = delivery_time + travel_time;
        time_t t;
        time(&t);
        strcpy(rst[idx].ord[ord_idx].order_time, ctime(&t));
        strcpy(rst[idx].ord[ord_idx].promised_delivery_time, ctime(&t));
        addtime(rst[idx].ord[ord_idx].promised_delivery_time, rst[idx].ord[ord_idx].service_time);
        printf("\nOrder placed succesfully with the below details.\n");
        printf("Expected Delivery Time: %s", rst[idx].ord[ord_idx].promised_delivery_time);
        strcpy(rst[idx].ord[ord_idx].orderID, "ODID");
        for (int i = 4; i < 8; i++)
        {
            rst[idx].ord[ord_idx].orderID[i] = phone_no[i - 4];
        }
        printf("Order Placed at the restaurant: %s\n", rst[idx].name);
        printf("ORDER ID : %s\n", rst[idx].ord[ord_idx].orderID);
        ordidx[idx]++;
    }
    else
        printf("Required items are not available in any of the restaurants in your locality.\n");
}

void sortStringAndArrays(char list[][100], int prices[], int size, int flag)
{
    if (flag == 0)
    {
        int sorted = 1;
        for (int i = 0; i < size && sorted == 1; i++)
        {
            sorted = 0;
            for (int j = 0; j < size && list[j][0] != '\0' && list[j + 1][0] != '\0'; j++)
            {
                if (strcmp(list[j], list[j + 1]) > 0)
                {
                    char temp[100];
                    strcpy(temp, list[j]);
                    strcpy(list[j], list[j + 1]);
                    strcpy(list[j + 1], temp);
                    int itemp = prices[j];
                    prices[j] = prices[j + 1];
                    prices[j + 1] = itemp;
                    sorted = 1;
                }
            }
        }
    }
    else
    {
        int sorted = 1;
        for (int i = 0; i < size && sorted == 1; i++)
        {
            sorted = 0;
            for (int j = 0; j < size && list[j][0] != '\0' && list[j + 1][0] != '\0'; j++)
            {
                if (strcmp(list[j], list[j + 1]) > 0)
                {
                    char temp[100];
                    strcpy(temp, list[j]);
                    strcpy(list[j], list[j + 1]);
                    strcpy(list[j + 1], temp);
                    int itemp = prices[j];
                    prices[j] = prices[j + 1];
                    prices[j + 1] = itemp;
                    sorted = 1;
                }
                else if (strcmp(list[j], list[j + 1]) == 0)
                {
                    if (prices[j] > prices[j + 1])
                    {
                        char temp[100];
                        strcpy(temp, list[j]);
                        strcpy(list[j], list[j + 1]);
                        strcpy(list[j + 1], temp);
                        int itemp = prices[j];
                        prices[j] = prices[j + 1];
                        prices[j + 1] = itemp;
                        sorted = 1;
                    }
                }
            }
        }
    }
}

void getCommonItems(restaurant rst[], char rstlist[][100], int noofRst)
{
    char generic[NO_OF_DISHES * noofRst][100];
    char special[NO_OF_DISHES * noofRst][100];
    char ITOD[NO_OF_DAYS * noofRst][100];
    int genprices[NO_OF_DISHES * noofRst];
    int specialprices[NO_OF_DISHES * noofRst];
    int itodprices[NO_OF_DAYS * noofRst];
    int genidx = 0;
    int specidx = 0;
    int itodidx = 0;
    for (int i = 0; i < NO_OF_DISHES * noofRst; i++)
    {
        generic[i][0] = '\0';
        genprices[i] = 0;
    }
    for (int i = 0; i < NO_OF_DISHES * noofRst; i++)
    {
        special[i][0] = '\0';
        specialprices[i] = 0;
    }
    for (int i = 0; i < NO_OF_DAYS * noofRst; i++)
    {
        generic[i][0] = '\0';
        genprices[i] = 0;
    }

    for (int i = 0; i < DB_SIZE && rst[i].name[0] != '\0'; i++)
    {
        for (int j = 0; j < noofRst; j++)
        {
            if (strcmp(rst[i].name, rstlist[j]) == 0)
            {
                for (int k = 0; k < NO_OF_DISHES && rst[i].generic.food[k][0] != '\0'; k++)
                {
                    strcpy(generic[genidx], rst[i].generic.food[k]);
                    genprices[genidx] = rst[i].generic.price[k];
                    genidx++;
                }
                for (int k = 0; k < NO_OF_DISHES && rst[i].special.food[k][0] != '\0'; k++)
                {
                    strcpy(special[specidx], rst[i].special.food[k]);
                    specialprices[specidx] = rst[i].special.price[k];
                    specidx++;
                }
                for (int k = 0; k < NO_OF_DAYS && rst[i].item_of_the_day.food[k][0] != '\0'; k++)
                {
                    strcpy(ITOD[itodidx], rst[i].item_of_the_day.food[k]);
                    itodprices[itodidx] = rst[i].item_of_the_day.price[k];
                    itodidx++;
                }
            }
        }
    }
    sortStringAndArrays(generic, genprices, genidx, 0);
    sortStringAndArrays(special, specialprices, specidx, 0);
    sortStringAndArrays(ITOD, itodprices, itodidx, 0);
    int outstatus = 0;
    for (int i = 0; i < NO_OF_DISHES * noofRst && generic[i][0] != '\0'; i++)
    {
        int idx = i;
        int freq = 1;
        while (strcmp(generic[i], generic[i + 1]) == 0)
        {
            freq++;
            i++;
        }
        if (freq == noofRst)
        {
            printf("Dish name: %s\n", generic[idx]);
            printf("Restaurant: \n");
            for (int itr = idx; itr < idx + noofRst; itr++)
            {
                printf("  %s -- Price -- %d\n", rstlist[itr - idx], genprices[itr]);
                outstatus = 1;
            }
            printf("\n");
        }
    }
    for (int i = 0; i < NO_OF_DISHES * noofRst && special[i][0] != '\0'; i++)
    {
        int idx = i;
        int freq = 1;
        while (strcmp(special[i], special[i + 1]) == 0)
        {
            freq++;
            i++;
        }
        if (freq == noofRst)
        {
            printf("\nDish Name: %s\n", special[idx]);
            printf("Restaurant: \n");

            for (int itr = idx; itr < idx + noofRst; itr++)
            {
                printf("  %s -- Price -- %d\n", rstlist[itr - idx], specialprices[itr]);
                outstatus = 1;
            }
            printf("\n");
        }
    }
    for (int i = 0; i < NO_OF_DAYS * noofRst && ITOD[i][0] != '\0'; i++)
    {
        int idx = i;
        int freq = 1;
        while (strcmp(ITOD[i], ITOD[i + 1]) == 0)
        {
            freq++;
            i++;
        }
        if (freq == noofRst)
        {
            printf("Dish Name: %s\n", ITOD[idx]);
            printf("Restaurant: \n");

            for (int itr = idx; itr < idx + noofRst; itr++)
            {
                printf("  %s -- Price -- %d\n", rstlist[itr - idx], itodprices[itr]);
                outstatus = 1;
            }
            printf("\n");
        }
    }
    if (outstatus == 0)
    {
        printf("\nNo common items in the restaraunt list you have provided.\n");
    }
}

void getAllUniqueItem(restaurant rst[], char rst_list[][100], int no_of_rst)
{
    printf("\n");
    int flag1 = 1;
    int flag2;
    int gCount = 0;
    int sCount = 0;
    int ITODcount = 0;
    int found = 0;
    char generic[NO_OF_DISHES * no_of_rst][100];
    char special[NO_OF_DISHES * no_of_rst][100];
    char ITOD[NO_OF_DAYS * no_of_rst][100];
    int genprices[NO_OF_DISHES * no_of_rst];
    int specialprices[NO_OF_DISHES * no_of_rst];
    int itodprices[NO_OF_DAYS * no_of_rst];

    for (int i = 0; i < DB_SIZE && flag1 == 1; i++)
    {
        if (rst[i].name[0] != '\0')
        {
            for (int j = 0; j < no_of_rst; j++)
            {
                if (strcmp(rst[i].name, rst_list[j]) == 0)
                {
                    printf("-- %s\n", rst[i].name);
                    printf("coordinates : %f , %f \n", rst[i].rst_address.x_coordinate, rst[i].rst_address.y_coordinate);
                    printf("Plot no : %d\n", rst[i].rst_address.plot_no);
                    printf("Area name : %s\n", rst[i].rst_address.area_name);
                    printf("City namr : %s\n", rst[i].rst_address.city_name);
                    printf("Pincode : %d\n", rst[i].rst_address.pincode);
                    flag2 = 1;
                    for (int k = 0; k < NO_OF_DISHES && flag2 == 1; k++)
                    {
                        if (rst[i].generic.food[k][0] != '\0')
                        {
                            strcpy(generic[gCount], rst[i].generic.food[k]);
                            genprices[gCount] = rst[i].generic.price[k];
                            gCount++;
                        }
                        else
                            flag2 = 0;
                    }
                    flag2 = 1;
                    for (int k = 0; k < NO_OF_DISHES && flag2 == 1; k++)
                    {
                        if (rst[i].special.food[k][0] != '\0')
                        {
                            strcpy(special[sCount], rst[i].special.food[k]);
                            specialprices[sCount] = rst[i].special.price[k];
                            sCount++;
                        }
                        else
                            flag2 = 0;
                    }
                    for (int k = 0; k < NO_OF_DAYS; k++)
                    {
                        strcpy(ITOD[ITODcount], rst[i].item_of_the_day.food[k]);
                        itodprices[ITODcount] = rst[i].item_of_the_day.price[k];
                        ITODcount++;
                    }
                    found = 1;
                }
            }
        }
        else
            flag1 = 0;
    }
    if (found == 1)
    {
        sortStringAndArrays(generic, genprices, gCount, 1);
        sortStringAndArrays(special, specialprices, sCount, 1);
        sortStringAndArrays(ITOD, itodprices, ITODcount, 1);

        for (int i = 0; i < gCount; i++)
        {
            while (strcmp(generic[i], generic[i + 1]) == 0)
            {
                strcpy(generic[i], "\0");
                i++;
            }
        }
        for (int i = 0; i < sCount; i++)
        {
            while (strcmp(special[i], special[i + 1]) == 0)
            {
                strcpy(special[i], "\0");
                i++;
            }
        }
        for (int i = 0; i < ITODcount; i++)
        {
            while (strcmp(ITOD[i], ITOD[i + 1]) == 0)
            {
                strcpy(ITOD[i], "\0");
                i++;
            }
        }

        int count = 1;
        printf("\nUnique Generic items:\n\n");
        for (int i = 0; i <= gCount; i++)
        {
            if (generic[i][0] != '\0')
                printf("%d) %s -- Rs %d\n", count++, generic[i], genprices[i]);
        }
        count = 1;
        printf("\nUnique Special items:\n\n");
        for (int i = 0; i <= sCount; i++)
        {
            if (special[i][0] != '\0')
                printf("%d) %s -- Rs %d\n", count++, special[i], specialprices[i]);
        }
        count = 1;
        printf("\nUnique Item of the day:\n\n");
        for (int i = 0; i <= ITODcount; i++)
        {
            if (ITOD[i][0] != '\0')
                printf("%d) %s -- Rs %d\n", count++, ITOD[i], itodprices[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Restaurant not found.\n");
    }
}

int isvalidphoneno(char user_phoneno[])
{
    // assuming that user provides 10 digit indian mobile no
    int count = 0;
    int ans = 0;
    for (int i = 0; i < 10; i++)
    {
        int temp = (int)user_phoneno[i];
        if (temp >= 48 && temp <= 57)
        {
            count++;
        }
    }
    ans = (count == 10);
    return ans;
}
int main()
{
    system("cls");
    int i = -1;
    int j = 0;
    int mode = 1;
    char line[1024];
    restaurant rst[DB_SIZE];
    {
        initializeDB(rst);

        FILE *file;

        file = fopen("database.txt", "r");
        if (file == NULL)
        {
            printf("Error opening file.\n");
            return 1;
        }
        while (fgets(line, sizeof(line), file) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            if (line[0] == '/')
            {
                i++;
                j = 0;
                mode = 1;
            }
            else
            {
                if (line[0] != '\0')
                {
                    switch (mode)
                    {
                    case 1:
                        strcpy(rst[i].name, line);
                        break;
                    case 2:
                        strcpy(rst[i].rst_address.area_name, line);
                        break;
                    case 3:
                        strcpy(rst[i].rst_address.city_name, line);
                        break;
                    case 4:
                        rst[i].rst_address.pincode = atoi(line);
                        break;
                    case 5:
                        rst[i].rst_address.plot_no = atoi(line);
                        break;
                    case 6:
                        rst[i].rst_address.x_coordinate = atof(line);
                        break;
                    case 7:
                        rst[i].rst_address.y_coordinate = atof(line);
                        break;
                    case 8:
                        strcpy(rst[i].generic.food[j], line);
                        j++;
                        break;
                    case 9:
                        rst[i].generic.price[j] = atoi(line);
                        j++;
                        break;
                    case 10:
                        rst[i].generic.service_time[j] = atof(line);
                        j++;
                        break;
                    case 11:
                        strcpy(rst[i].special.food[j], line);
                        j++;
                        break;
                    case 12:
                        rst[i].special.price[j] = atoi(line);
                        j++;
                        break;
                    case 13:
                        rst[i].special.service_time[j] = atof(line);
                        j++;
                        break;
                    case 14:
                        strcpy(rst[i].item_of_the_day.food[j], line);
                        j++;
                        break;
                    case 15:
                        rst[i].item_of_the_day.price[j] = atoi(line);
                        j++;
                        break;
                    case 16:
                        rst[i].item_of_the_day.service_time[j] = atof(line);
                        j++;
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    j = 0;
                    mode++;
                }
            }
        }

        fclose(file);

        sortRestaurants(rst);
        sortGenericDishes(rst);
        sortSpecialDishes(rst);
    }
    char fooditem[100];
    fooditem[0] = '\0';
    int quantity = 0;
    char listofitems[MAX_ORDER_SIZE][100];
    for (int i = 0; i < MAX_ORDER_SIZE; i++)
    {
        listofitems[i][0] = '\0';
    }
    int quantity_of_items[MAX_ORDER_SIZE];
    for (int i = 0; i < MAX_ORDER_SIZE; i++)
    {
        quantity_of_items[i] = 0;
    }
    int noofItems = 0;
    char user_name[100];
    user_name[0] = '\0';
    char user_phoneno[100];
    user_phoneno[0] = '\0';
    char user_address[100];
    user_address[0] = '\0';
    char restaurant_name[100];
    restaurant_name[0] = '\0';
    char area_name[100];
    area_name[0] = '\0';
    char listofrestaraunts[DB_SIZE][100];
    for (int i = 0; i < DB_SIZE; i++)
    {
        listofrestaraunts[i][0] = '\0';
    }
    int ordidx[DB_SIZE];
    for (int i = 0; i < DB_SIZE; i++)
    {
        ordidx[i] = 0;
    }
    int noofrst = 0;
    char operationstatus, rststatus, itemstatus;
    int operation;
    address user_add;
    printf("Welcome to the ONLINE FOOD ENQUIRY and ORDER PLATFORM\n\n");
    printf("Do you like to perform an operation(Y/N) : ");
    scanf("%c", &operationstatus);
    while (operationstatus == 'Y')
    {
        printf("\nChoose a operation you would like to perform by entering the integer corresponding in the dropdown menu \n\n");
        printf("List of operations that you can perform\n\n");
        printf(" 1 -- GET MIN TIME \n");
        printf(" 2 -- GET AVAILABILITY \n");
        printf(" 3 -- PLACE ORDER \n");
        printf(" 4 -- GET ITEM LIST IN SORTED ORDER \n");
        printf(" 5 -- GET ITEM LIST IN AREA SORTED ORDER \n");
        printf(" 6 -- GET ALL SPECIAL ITEM LIST IN SORTED ORDER \n");
        printf(" 7 -- GET ITEM OF THE DAY LIST IN SORTED ORDER \n");
        printf(" 8 -- GET COMMON ITEM \n");
        printf(" 9 -- GET ALL UNIQUE ITEM \n");
        printf("\nEnter : ");
        scanf("%d", &operation);
        while (operation < 1 || operation > 9)
        {
            printf("You Have entered an INCORRECT integer value for performing this operation\n");
            printf("Please enter a valid Integer to continue: ");
            scanf("%d", &operation);
        }
        printf("\n");
        fflush(stdin);
        switch (operation)
        {
        case 1:
            printf("Furnish the below information for fetching min time.\n\n");
            printf("Enter the dish name : ");
            gets(fooditem);
            printf("\n");
            printf("Enter quantity : ");
            scanf("%d", &quantity);
            printf("\n");
            getMinTime(rst, fooditem, quantity);
            break;
        case 2:
            printf("Furnish the following details for fetching item Avaialability.\n\n");
            printf("Enter the food name: ");
            gets(fooditem);
            getItemAvailability(rst, fooditem);
            break;
        case 3:
            itemstatus = 'Y';
            printf("Furnish the below information for placing an order.\n\n");
            printf("Enter your name : ");
            gets(user_name);
            printf("\n");
            while (strlen(user_name) == 0)
            {
                printf("Please enter a VALID name to continue: \n");
                fflush(stdin);
                gets(user_name);
                printf("\n");
            }
            printf("Enter your contact no : ");
            gets(user_phoneno);
            printf("\n");
            while (isvalidphoneno(user_phoneno) == 0)
            {
                printf("Please enter a VALID phone no to continue: ");
                fflush(stdin);
                gets(user_phoneno);
                printf("\n");
            }
            printf("Enter coordinates of your current location : \n");
            scanf("%f %f", &user_add.x_coordinate, &user_add.y_coordinate);
            printf("\n");
            printf("Enter Plot-no : ");
            scanf("%d", &user_add.plot_no);
            printf("\n");
            printf("Enter Area name : ");
            fflush(stdin);
            gets(user_add.area_name);
            printf("\n");
            printf("Enter city name : ");
            fflush(stdin);
            gets(user_add.city_name);
            printf("\n");
            printf("Enter Pincode : ");
            scanf("%d", &user_add.pincode);
            printf("\n");
            while ((itemstatus == 'Y') && noofItems < MAX_ORDER_SIZE)
            {
                char temp[100];
                printf("Enter food name : ");
                fflush(stdin);
                gets(temp);
                strcpy(listofitems[noofItems], temp);
                printf("\nEnter Quantity : ");
                fflush(stdin);
                scanf("%d", &quantity_of_items[noofItems]);
                noofItems++;
                printf("\nWould like to order an other item(Y/N) : ");
                fflush(stdin);
                scanf("%c", &itemstatus);
                printf("\n");
            }
            placeOrder(rst, listofitems, quantity_of_items, user_name, user_phoneno, user_add, noofItems, ordidx);
            noofItems = 0;
            break;
        case 4:
            printf("Furnish the following details for fetching ItemListInSortedOrder\n\n");
            printf("Enter restaurant name: ");
            gets(restaurant_name);
            getItemListInSortedOrder(rst, restaurant_name, i);
            break;
        case 5:
            printf("Furnish the following details for fetching ItemListInAreaSortedOrder\n\n");
            printf("Enter the Region: ");
            gets(area_name);
            printf("\n");
            getItemListInAreaSortedOrder(rst, area_name);
            break;
        case 6:
            printf("Furnish the following details for fetching AllSpecialItemListinSortedOrder\n\n");
            rststatus = 'Y';
            while ((rststatus == 'Y') && noofrst < DB_SIZE)
            {
                char temp[100];
                printf("Enter restaurant name : ");
                fflush(stdin);
                gets(temp);
                strcpy(listofrestaraunts[noofrst], temp);
                printf("\n");
                noofrst++;
                printf("Would like to add an other rst(Y/N) : ");
                fflush(stdin);
                scanf("%c", &rststatus);
                printf("\n");
            }
            printf("\n");
            getAllSpecialItemListinSortedOrder(rst, listofrestaraunts, noofrst);
            noofrst = 0;
            break;
        case 7:
            printf("Furnish the following details for fetching ItemofDayListinSortedOrder\n\n");
            printf("Enter area name : ");
            gets(area_name);
            getItemofDayListinSortedOrder(rst, area_name);
            break;
        case 8:
            printf("Furnish the following details for fetching common items\n\n");
            rststatus = 'Y';
            while (rststatus == 'Y' && noofrst < DB_SIZE)
            {
                char temp[100];
                printf("Enter restaurant name : ");
                fflush(stdin);
                gets(temp);
                strcpy(listofrestaraunts[noofrst], temp);
                printf("\n");
                noofrst++;
                printf("Would like to add an other rst(Y/N) : ");
                fflush(stdin);
                scanf("%c", &rststatus);
                printf("\n");
                if (rststatus == 'N' && noofrst == 1)
                {
                    printf("Since you have entered a Single restaruant, Enter alteast one more restaurant :\n\n");
                    fflush(stdin);
                    gets(temp);
                    strcpy(listofrestaraunts[noofrst], temp);
                    noofrst++;
                    printf("Would like to add an other rst(Y/N) : ");
                    fflush(stdin);
                    scanf("%c", &rststatus);
                }
            }
            getCommonItems(rst, listofrestaraunts, noofrst);
            noofrst = 0;
            break;
        case 9:
            printf("Furnish the following details for fetching unique items\n\n");
            rststatus = 'Y';
            while ((rststatus == 'Y') && noofrst < DB_SIZE)
            {
                char temp[100];
                printf("Enter restaurant name : ");
                fflush(stdin);
                gets(temp);
                strcpy(listofrestaraunts[noofrst], temp);
                printf("\n");
                noofrst++;
                printf("Would like to add an other rst(Y/N) : ");
                fflush(stdin);
                scanf("%c", &rststatus);
                printf("\n");
                if (rststatus == 'N' && noofrst == 1)
                {
                    printf("Since you have entered a Single restaruant, Enter alteast one more restaurant :\n");
                    fflush(stdin);
                    gets(temp);
                    strcpy(listofrestaraunts[noofrst], temp);
                    noofrst++;
                    printf("Would like to add an other rst(Y/N) : ");
                    fflush(stdin);
                    scanf("%c", &rststatus);
                }
            }
            getAllUniqueItem(rst, listofrestaraunts, noofrst);
            noofrst = 0;
            break;
        }
        printf("\n");
        printf("Would you like to perform an operation(Y/N): ");
        fflush(stdin);
        scanf("%c", &operationstatus);
        system("cls");
    }

    printf("\n\n\n\n\n\nThank you for choosing us, Have a nice day\n\n\n\n\n\n");
    return 0;
}