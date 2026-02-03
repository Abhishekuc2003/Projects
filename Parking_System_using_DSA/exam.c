#include<stdio.h>
#include<stdlib.h>

typedef struct queue {
    int rear;
    int front;
    int capacity;
    int *arr;
}queue;

void init_queue(queue *car, int size);
void create_queue(queue *car,int size);
void enter_car(queue *car , int token);
int exit_car(queue *car);
void display_parking(queue *car);
int resize(queue *car, int size);
int queue_full(queue *car);
int queue_empty(queue *car);

int main(){
    int choice,size = 0;
    queue Q;
    Q.arr = NULL;
    init_queue(&Q,size); //initialize queue

    do{
    printf("-------------------------------------------\n");
    printf("\n0.Exit\n1.Enter Size of Parking Lot\n2.Enter Car\n3.Exit Car\n4.Display Car\n5.Resize Parking\n");
    printf("-------------------------------------------\n");
    printf("Enter your choice : ");
    scanf("%d",&choice);
    printf("-------------------------------------------\n");
    printf("\n\n");    
    switch(choice){

        case 0 :
                exit(0);
            break;
        case 1 : //enter size of parking lot     
            printf("Enter the size of parking lot : ");
            scanf("%d",&size);
            printf("-------------------------------------------\n");
            init_queue(&Q,size);
            break;
        case 2 ://enter car
                if(queue_full(&Q)){
                    printf("Parking is full wait for some time \n");
                    printf("-------------------------------------------\n");
                }
                else if(size <= 0){
                    printf("Please set parking lot size first\n");
                    printf("-------------------------------------------\n");
                }
                else{
                int token;
                printf("Enter Car Token : ");
                scanf("%d",&token);
                printf("-------------------------------------------\n");
                enter_car(&Q,token);
                }
                break;
        case 3 : //exit car
                if(queue_empty(&Q)) // if(0)
                {
                    printf("Parking Lot is empty !\n");
                    printf("-------------------------------------------\n");
                }
                else
                {
                    int car = exit_car(&Q); // 10
                    printf("Car with token no.: %d exited\n",car);
                    printf("-------------------------------------------\n");
                }
                break;
        case 4 :  //display parking
                if(queue_empty(&Q)){
                printf("Parking is empty !!\n");
                printf("-------------------------------------------\n");
                }
            else
            {
                display_parking(&Q);
                printf("-------------------------------------------\n");
            }
                break;
        case 5 : //resize
                if(!queue_empty(&Q)){
                    printf("Empty the parking lot to resize\n");
                    printf("-------------------------------------------\n");
                }
                else{
                printf("Enter the new size : ");
                scanf("%d",&size);
                printf("-------------------------------------------\n");
                int val = resize(&Q,size);
                if(val != 0){
                    printf("Parking Lot resized\n");
                    printf("-------------------------------------------\n");
                }
                else{
                    printf("Enter valid size\n");
                    printf("-------------------------------------------\n");
                }
                }
                break;
        default :
                printf("Invalid Entry..!!\n");
    }
}while(choice != 0);
    return 0;
}
void init_queue(queue *car, int size){//init queue

    car->front = -1;
    car->rear = -1;
    car->capacity = size;
    car->arr = malloc(size*(sizeof(int)));
}

void enter_car(queue *car , int token){ //enqueue

    if(token <= 0){
        printf("Please set parking lot size first\n");
    }
    else if(queue_full(car)){
        printf("Parking lot is full...\n");
        return;
    }
    else{
    car->rear = (car->rear+1) % car->capacity; 
    car->arr[car->rear] = token;
    printf("Car with Token No:- %d entered\n",token);
        if(car->front == -1)
            car->front = 0;
    }
}

int exit_car(queue *car){ //dequeue
    
    int token = car->arr[car->front];

    if(car->front == car->rear) 
    {
        car->rear = -1; 
        car->front = -1;
        return token;
    }
    else
    {
        car->front = (car->front+1) % car->capacity; 
        return token;
    }
}

void display_parking(queue *car){ //peek

    if (queue_empty(car)) {
        printf("Parking is empty,no cars\n");
        return;
    }

    int count; //calculate the no. of cars
    if (car->rear >= car->front) {
        count = car->rear - car->front + 1;
    } else { //circular wrap
        count = (car->capacity - car->front) + (car->rear + 1); 
    }
    for (int i = 0; i < count; i++) { //print cars
        printf("Position %d : Car Token %d\n", i + 1, car->arr[car->front]);
        car->front = (car->front + 1) % car->capacity;
    }
}

int resize(queue *car, int new_size){

    if(new_size < 1){
        printf("Enter size greater than 1\n");
        return 0;
    }
    else if(!queue_empty(car)){
            printf("Cannot resize, Empty the parking lot\n");
            return 0;
        }
    else{
        int *temp =(int *)realloc(car->arr,new_size *(sizeof(int)));
        if(temp != NULL){
            car->arr = temp;
            car->capacity = new_size;
            car->front = -1;
            car->rear = -1;
            return new_size;
        }
    }
return 0;
}

int queue_empty(queue *car) //empty 
{
    if(car->front == -1)
        return 1;
    else
        return 0;
}

int queue_full(queue *car) //full
{
    if(car->front == (car->rear+1) % car->capacity)
        return 1;
    else
        return 0;
}