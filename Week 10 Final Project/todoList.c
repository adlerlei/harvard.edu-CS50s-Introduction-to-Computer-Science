#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TODO 100
#define MAX_LEN 100

char todos[MAX_TODO][MAX_LEN];
int numTodos = 0;

void saveToFile(char fileName[]) {
    FILE *fp;
    fp = fopen(fileName, "w");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return;
    }
    for (int i = 0; i < numTodos; i++) {
        fprintf(fp, "%s\n", todos[i]);
    }
    fclose(fp);
    //改成自動儲存代辦事項列表
    //printf("Todo list saved to file.\n");
}

void loadFromFile(char fileName[]) {
    FILE *fp;
    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return;
    }
    char line[MAX_LEN];
    while (fgets(line, MAX_LEN, fp) != NULL) {
        line[strcspn(line, "\n")] = 0; // 去除換行符
        strcpy(todos[numTodos], line);
        numTodos++;
    }
    fclose(fp);
    //printf("Todo list loaded from file.\n");
}

void addTodo() {
    char todo[MAX_LEN];
    printf("Enter a todo: ");
    getchar(); // 解决输入缓冲区冲突
    if (fgets(todo, MAX_LEN, stdin) == NULL) {
        printf("Failed to read input.\n");
        return;
    }
    todo[strcspn(todo, "\n")] = 0; // 去除換行符
    strcpy(todos[numTodos], todo);
    numTodos++;
    printf("Todo added: %s\n", todo);
}

void showTodos() {
    printf("**** Todo List: ****\n");
    for (int i = 0; i < numTodos; i++) {
        printf("%d. %s\n", i+1, todos[i]);
    }
}

void editTodo() {
    int index;
    char todo[MAX_LEN];
    printf("Enter the index of the todo you want to edit: ");
    scanf("%d", &index);
    index--; //將索引從1-based 轉為 0-based
    if (index < 0 || index >= numTodos) {
        printf("Invalid index.\n");
        return;
    }
    printf("Enter the new todo: ");
    getchar();
    if (fgets(todo, MAX_LEN, stdin) == NULL) {
        printf("Failed to read input.\n");
        return;
    }
    todo[strcspn(todo, "\n")] = 0;
    strcpy(todos[index], todo);
    printf("Todo edited: %s\n", todo);
}

void deleteTodo(){
    int choice;
    printf("Enter the index of the todo you want to delete: ");
    scanf("%d", &choice);

    if (choice > 0 && choice <= numTodos) {
        printf("Todo deleted: %s\n", todos[choice - 1]);
        for (int i = choice - 1; i < numTodos - 1; i++)
        {
            strcpy(todos[i], todos[i + 1]);
        }
        memset(todos[numTodos - 1], 0, sizeof(todos[numTodos - 1]));
        numTodos--;
    } else {
        printf("Invalid choice.\n");
    }
}

int main(void) {
    char fileName[] = "todo.txt";
    loadFromFile(fileName);
    int choice = 0;
    while (choice != 5) {
        printf("** Hello World!This is CS50 Final Project! **\n");
        printf("Please enter 1.Add, 2.Show, 3.Edit, 4.Delete, 5.Exit: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addTodo();
                saveToFile(fileName);
                break;
            case 2:
                showTodos();
                break;
            case 3:
                editTodo();
                saveToFile(fileName);
                break;
            case 4:
                deleteTodo();
                saveToFile(fileName);
                break;
            case 5:
                printf("Goodbye! This is CS50!\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
    return 0;
}