# 引入cs50
from cs50 import get_float

# 初始化硬幣數量和每個硬幣的價值
quarters = 25
dimes = 10
nickels = 5
pennies = 1

# 取得用戶輸入
while True:
    dollars = get_float("Change owed : ")
    if dollars >= 0:
        break

# 把美元轉換美分
cents = round(dollars * 100)

# 計算需要多少硬幣
num_quarters = cents // quarters
cents = cents % quarters

num_dimes = cents // dimes
cents = cents % dimes

num_nickels = cents // nickels
cents = cents % nickels

num_pennies = cents // pennies
cents = cents % pennies

# 輸出結果
print(num_quarters + num_dimes + num_nickels + num_pennies)