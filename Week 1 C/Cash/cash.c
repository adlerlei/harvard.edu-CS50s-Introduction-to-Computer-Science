#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    // 詢問積欠多少美分
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    // 計算要給顧客的25美分數量
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    // 計算要給顧客10美分的數量
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    // 計算要給顧客多少5美分硬幣
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    // 計算要給顧客多少1美分的硬幣
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    // 硬幣總和
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    // 打印出需要找給顧客的硬幣總數
    printf("%i\n", coins);
}
// 處理用戶輸入
int get_cents(void)
{
    // TODO - 初始化 cents 變數
    int cents;
    // 使用 do while 循環判斷用戶輸入是否符合，不符合就返回請用戶再次輸入
    do
    {
        cents = get_int("Change owed : ");
    }
    while (cents < 0);
    return cents;
}
// 25美分硬幣
int calculate_quarters(int cents)
{
    // TODO - 除以25計算要給幾個25美分硬幣
    int quarters = cents / 25;
    return quarters;
}
// 10美分
int calculate_dimes(int cents)
{
    // TODO - 除以10計算要給幾個10美分硬幣
    int dimes = cents / 10;
    return dimes;
}
// 5美分硬幣
int calculate_nickels(int cents)
{
    // TODO - 除以5計算要給幾個5美分硬幣
    int nickels = cents / 5;
    return nickels;
}
// 1美分硬幣
int calculate_pennies(int cents)
{
    // TODO - 除以1計算要給幾個1美分硬幣
    int pennies = cents / 1;
    return pennies;
}
