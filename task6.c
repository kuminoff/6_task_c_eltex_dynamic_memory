#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Subscriber
{
    char name[30];
    char second_name[30];
    char tel[11];
};

struct Subscriber *subscriberBook = NULL;
int currentSize = 0;

void initSubscriberBook();
void drawMenu();
void addSubscriber();
void deleteSubscriber();
void findSubscriber();
void drawSubscriber(const struct Subscriber *member);
void printAllSubscribers();

void initSubscriberBook()
{
    subscriberBook = (struct Subscriber *)malloc(sizeof(struct Subscriber));
    if (subscriberBook == NULL)
    {
        printf("\nОшибка выделения памяти\n");
        exit(1);
    }
}

void resizeSubscriberBook(int newSize)
{
    subscriberBook = (struct Subscriber *)realloc(subscriberBook, newSize * sizeof(struct Subscriber));
    if (subscriberBook == NULL)
    {
        printf("\nОшибка перевыделения памяти\n");
        exit(1);
    }
}

void drawMenu()
{
    int taskNumber;
    printf("\nПожалуйста, выберите действие от 1 до 5\n\n");
    printf("1. Добавить нового абонента\n");
    printf("2. Удалить абонента\n");
    printf("3. Найти абонента по имени\n");
    printf("4. Показать всех абонентов\n");
    printf("5. Выйти\n");
    scanf("%d", &taskNumber);

    switch (taskNumber)
    {
    case 1:
        addSubscriber();
        break;
    case 2:
        deleteSubscriber();
        break;
    case 3:
        findSubscriber();
        break;
    case 4:
        printAllSubscribers();
        break;
    case 5:
        free(subscriberBook); // Освободить память перед выходом
        exit(0);
    default:
        printf("\nЗадача с номером %d не существует\n", taskNumber);
    }
}

void addSubscriber()
{
    resizeSubscriberBook(currentSize + 1);

    printf("\nВведите имя, фамилию и номер телефона абонента (через пробел): ");
    scanf("%s %s %s", subscriberBook[currentSize].name, subscriberBook[currentSize].second_name, subscriberBook[currentSize].tel);
    currentSize++;

    drawMenu();
}

void deleteSubscriber()
{
    int id;
    printf("\nВведите ID абонента, которого нужно удалить: ");
    scanf("%d", &id);

    if (id >= currentSize)
    {
        printf("\nПревышен лимит (%d) абонентов\n", currentSize);
    }
    else
    {
        subscriberBook[id] = subscriberBook[currentSize - 1];
        resizeSubscriberBook(currentSize - 1);
        currentSize--;
    }

    drawMenu();
}

void findSubscriber()
{
    char searchName[30];
    printf("\nВведите имя абонента для поиска: ");
    scanf("%s", searchName);

    for (int i = 0; i < currentSize; i++)
    {
        if (strcmp(subscriberBook[i].name, searchName) == 0)
        {
            drawSubscriber(&subscriberBook[i]);
        }
    }

    drawMenu();
}

void drawSubscriber(const struct Subscriber *member)
{
    printf("%s %s, %s\n", member->name, member->second_name, member->tel);
}

void printAllSubscribers()
{
    printf("\nСписок абонентов:\n");

    for (int i = 0; i < currentSize; i++)
    {
        drawSubscriber(&subscriberBook[i]);
    }

    drawMenu();
}

int main()
{
    initSubscriberBook();
    drawMenu();
    return 0;
}
