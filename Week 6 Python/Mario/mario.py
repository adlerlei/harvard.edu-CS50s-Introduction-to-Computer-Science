# 宣告height變量並預設為0
height = 0

# 重複以下步驟，直到高度在 1 到 8（含）之間
# while height < 1 or height > 8:
#     height = int(input("Height : "))
while True:
    try:
        height = int(input("Height: "))
        if height < 1 or height > 8:
            raise ValueError
        break
    except ValueError:
        print("Please enter a valid height (1-8)")


for i in range(height):
    # 計算代碼需要輸出多少個空格
    for j in range(height - i - 1):
        print(" ", end="")
    # 輸出“#”和一個換行符
    for k in range(i + 1):
        print("#", end="")
    print()