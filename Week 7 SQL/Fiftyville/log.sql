-- First, check the structure of the table.
-- 先檢查表的結構
.tables

-- Obtain all the following tables.
-- 獲得以下所有資料表
airports / crime_scene_reports / people / atm_transaction / flights / phone_calls / bakery_security_logs / interviews
bank_accounts / passengers

-- Check the structure of the table "crime_scene_reports".
-- 查看 crime_scene_reports 表的結構
PRAGMA table_info(crime_scene_reports);

-- Let's start solving this puzzle. First, we need to search for a crime scene report that matches the location and date of the crime.
-- 開始解決這個謎題。首先，我們要查找一個與案發地點和案發日期匹配的犯罪現場報告
-- Search for a crime scene report that matches the date and location of the crime.
-- 查找符合案發日期和地點的犯罪現場報告
SELECT * FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
-- From the query result, we can see that there are two events that match the date and location of the crime.
-- However, the second event is about littering, so we will focus on the first event.
-- 從查詢結果中，我們可以看到有兩個事件與案發日期和地點相符。但第二個事件是關於亂丟垃圾的，所以我們專注於第一個事件
-- Specifically, the theft of the CS50 rubber duck. This report mentions three witnesses
-- and their interview records all mention the bakery.
-- 即 CS50 鴨子被盜事件。這份報告提到了三名目擊者，他們的訪談記錄都提到了麵包店。

-- Search for interview records involving the bakery.
-- 查找涉及麵包店的訪談記錄
SELECT * FROM interviews
WHERE transcript LIKE '%bakery%';
-- Now there are three interview records related to the case.
-- 現在有三份與案件相關的訪談記錄
-- Ruth: The thief drove away from the bakery parking lot within ten minutes of the theft.
-- Checking the surveillance footage of the parking lot may yield some clues.
-- Ruth：小偷在盜竊後的十分鐘內開車離開了麵包店停車場。查看停車場的監控錄像可能會有所發現。
-- Eugene: He recognized the thief, but didn't know their name.
-- He saw the thief withdrawing money from an ATM on Leggett Street in the morning.
-- Eugene：他認出了小偷，但不知道名字。早上在 Leggett Street 的ATM看到小偷取錢。
-- Raymond: The thief made a phone call when leaving the bakery, and the response was less than a minute.
-- The thief mentioned planning to leave Fiftyville on the earliest flight tomorrow and asked the other party to buy a ticket.
-- Raymond：小偷在離開麵包店時打了個電話，對方回應少於一分鐘。小偷提到計劃明天最早的航班離開 Fiftyville，並要求對方購買機票。
-- According to Ruth's statement, we should check the surveillance footage of the bakery parking lot.
-- 根據 Ruth 的陳述，我們應該查看麵包店停車場的監控錄像。
-- Search for surveillance logs involving the bakery parking lot.
-- 查找涉及麵包店停車場的監控日誌
SELECT * FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 5 AND 25;
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | id  | year | month | day | hour | minute | activity | license_plate |
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | 258 | 2021 | 7     | 28  | 10   | 8      | entrance | R3G7486       |
-- | 259 | 2021 | 7     | 28  | 10   | 14     | entrance | 13FNH73       |
-- | 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
-- | 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
-- | 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
-- | 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
-- | 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
-- | 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
-- | 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
-- | 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- Now we have the license plates of the vehicles that entered and exited the bakery parking lot.
-- At around 10:15, the following vehicles left the parking lot:
-- 94KL13X / 6P58WS2 / 4328GD8 / G412CB7 / L93JTIZ / 322W7JE / 0NTHK55
-- 現在有了在麵包店停車場進入和離開的車輛的牌照。在 10:15 左右，以下車輛離開了停車場：
-- 94KL13X / 6P58WS2 / 4328GD8 / G412CB7 / L93JTIZ / 322W7JE / 0NTHK55
-- Now we can search for people related to the license plate numbers.
-- 現在我們可以通過車牌號碼查找相關的人
SELECT * FROM people
WHERE license_plate IN ('94KL13X', '6P58WS2', '4328GD8', 'G412CB7', 'L93JTIZ', '322W7JE', '0NTHK55');
-- According to the query results, the following are the relevant people of the vehicles that left the
-- bakery parking lot around the time of the crime:
-- Barry: License plate 6P58WS2, phone number (301) 555-4174, passport number 7526138472
-- Iman: License plate L93JTIZ, phone number (829) 555-5269, passport number 7049073643
-- Sofia: License plate G412CB7, phone number (130) 555-0289, passport number 1695452385
-- Luca: License plate 4328GD8, phone number (389) 555-5198, passport number 8496433585
-- Diana: License plate 322W7JE, phone number (770) 555-1861, passport number 3592750733
-- Kelsey: License plate 0NTHK55, phone number (499) 555-9472, passport number 8294398571
-- Bruce: License plate 94KL13X, phone number (367) 555-5533, passport number 5773159633
-- 根據查詢結果，以下是在案發時間附近離開麵包店停車場的車輛的相關人：
-- Barry: 車牌號 6P58WS2, 電話號碼 (301) 555-4174, 護照號碼 7526138472
-- Iman: 車牌號 L93JTIZ, 電話號碼 (829) 555-5269, 護照號碼 7049073643
-- Sofia: 車牌號 G412CB7, 電話號碼 (130) 555-0289, 護照號碼 1695452385
-- Luca: 車牌號 4328GD8, 電話號碼 (389) 555-5198, 護照號碼 8496433585
-- Diana: 車牌號 322W7JE, 電話號碼 (770) 555-1861, 護照號碼 3592750733
-- Kelsey: 車牌號 0NTHK55, 電話號碼 (499) 555-9472, 護照號碼 8294398571
-- Bruce: 車牌號 94KL13X, 電話號碼 (367) 555-5533, 護照號碼 5773159633

-- Now we can continue the investigation based on this information.
-- First, let's check who among these people used the ATM on the day of the crime.
-- 現在我們可以根據這些信息繼續調查。首先，讓我們檢查這些人中誰在案發當天使用了ATM
SELECT * FROM atm_transactions
WHERE year = 2021 AND month = 7 AND day = 28 AND account_number IN (
  SELECT account_number FROM bank_accounts WHERE person_id IN (
    SELECT id FROM people WHERE license_plate IN ('94KL13X', '6P58WS2', '4328GD8', 'G412CB7', 'L93JTIZ', '322W7JE', '0NTHK55')
  )
);
-- The following are relevant information on ATM usage records on the day of the crime:
-- Transaction ID 246: Account number 28500762, Date July 28, 2021, ATM location Leggett Street, Transaction type Withdrawal, Amount 48
-- Transaction ID 267: Account number 49610011, Date July 28, 2021, ATM location Leggett Street, Transaction type Withdrawal, Amount 50
-- Transaction ID 288: Account number 25506511, Date July 28, 2021, ATM location Leggett Street, Transaction type Withdrawal, Amount 20
-- Transaction ID 292: Account number 56171033, Date July 28, 2021, ATM location Daboin Sanchez Drive, Transaction type Deposit, Amount 70
-- Transaction ID 336: Account number 26013199, Date July 28, 2021, ATM location Leggett Street, Transaction type Withdrawal, Amount 35
-- 以下是案發當天在ATM使用記錄的相關信息：
-- 交易ID 246: 賬戶號 28500762, 日期 2021年7月28日, ATM地點 Leggett Street, 交易類型 提款, 金額 48
-- 交易ID 267: 賬戶號 49610011, 日期 2021年7月28日, ATM地點 Leggett Street, 交易類型 提款, 金額 50
-- 交易ID 288: 賬戶號 25506511, 日期 2021年7月28日, ATM地點 Leggett Street, 交易類型 提款, 金額 20
-- 交易ID 292: 賬戶號 56171033, 日期 2021年7月28日, ATM地點 Daboin Sanchez Drive, 交易類型 存款, 金額 70
-- 交易ID 336: 賬戶號 26013199, 日期 2021年7月28日, ATM地點 Leggett Street, 交易類型 提款, 金額 35

-- Now, let's find out who withdrew money from the ATM on Leggett Street.
-- 現在，讓我們找出在Leggett Street的ATM提款的人。
SELECT p.* FROM people p
JOIN bank_accounts ba ON p.id = ba.person_id
WHERE ba.account_number IN (28500762, 49610011, 25506511, 26013199);
-- According to the query results, we found the following people who withdrew money from the ATM on Leggett Street:
-- ID 686048: Name Bruce, phone number (367) 555-5533, passport number 5773159633, license plate number 94KL13X
-- ID 514354: Name Diana, phone number (770) 555-1861, passport number 3592750733, license plate number 322W7JE
-- ID 396669: Name Iman, phone number (829) 555-5269, passport number 7049073643, license plate number L93JTIZ
-- ID 467400: Name Luca, phone number (389) 555-5198, passport number 8496433585, license plate number 4328GD8
-- 根據查詢結果，我們找到了在Leggett Street的ATM提款的人：
-- ID 686048: 名字 Bruce, 電話號碼 (367) 555-5533, 護照號碼 5773159633, 車牌號碼 94KL13X
-- ID 514354: 名字 Diana, 電話號碼 (770) 555-1861, 護照號碼 3592750733, 車牌號碼 322W7JE
-- ID 396669: 名字 Iman, 電話號碼 (829) 555-5269, 護照號碼 7049073643, 車牌號碼 L93JTIZ
-- ID 467400: 名字 Luca, 電話號碼 (389) 555-5198, 護照號碼 8496433585, 車牌號碼 4328GD8

-- Now we need to check if these people received a phone call from the thief.
-- 現在我們需要查看這些人是否收到了一通來自竊賊的電話。
SELECT * FROM phone_calls
WHERE (year = 2021 AND month = 7 AND day = 28) AND (caller IN ('Bruce', 'Diana', 'Iman', 'Luca') OR receiver IN ('Bruce', 'Diana', 'Iman', 'Luca'));
-- The above query had no results, indicating that there were no phone call records between these people we found on that day.
-- Looking back at the previous clues, one of the witnesses mentioned that the thief immediately made a phone call to
-- someone after the crime, and said that they would take the earliest flight from Fiftyville the next day (July 29).
-- 以上查詢沒有結果，表示在這一天我們找到的這些人之間沒有任何通話記錄。回顧之前的線索，其中一名目擊者提到竊賊在犯罪後立即打電話給某人
-- 並表示他們將在第二天（7月29日）搭乘從Fiftyville出發的最早航班。

-- Let's search for early flights departing from Fiftyville on July 29.
-- 讓我們查找7月29日從Fiftyville出發的早期航班
SELECT * FROM flights
WHERE origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') AND year = 2021 AND month = 7 AND day = 29
ORDER BY hour, minute ASC;
-- We have found the flights departing from Fiftyville on July 29. Now let's search for the passengers on these flights
-- especially those on the list of suspected thieves.
-- 我們已經找到了7月29日從Fiftyville出發的航班，現在讓我們查找這些航班上的乘客，特別是我懷疑的竊賊名單中的人
SELECT p.*, f.id AS flight_id, a.city AS destination_city
FROM passengers p
JOIN flights f ON p.flight_id = f.id
JOIN airports a ON f.destination_airport_id = a.id
WHERE p.passport_number IN (5773159633, 3592750733, 7049073643, 8496433585) AND f.year = 2021 AND f.month = 7 AND f.day = 29;
-- According to the query results, we can see the flight information for the following three suspects:
-- 3592750733 (Diana): Flight ID 18, destination is Boston, seat number is 4C.
-- 5773159633 (Bruce): Flight ID 36, destination is New York City, seat number is 4A.
-- 8496433585 (Luca): Flight ID 36, destination is New York City, seat number is 7B.
-- Now we have enough information to investigate these suspects. According to previous testimony, the thief planned to take the earliest flight from Fiftyville, so we need to pay attention to the suspect who takes the earliest flight.
-- In this case, the earliest flight is Flight ID 36, with the destination of New York City. On this flight, we have two suspects: Bruce (seat 4A) and Luca (seat 7B).
-- We have now found the possible thief, Bruce, and his accomplice, Luca.
-- But the answer is incorrect!
-- 根據查詢結果，我們可以看到以下三名嫌疑人的航班信息：
-- 3592750733（Diana）：航班ID 18，目的地是波士頓，座位編號是4C。
-- 5773159633（Bruce）：航班ID 36，目的地是紐約市，座位編號是4A。
-- 8496433585（Luca）：航班ID 36，目的地是紐約市，座位編號是7B。
-- 現在我們有了足夠的信息來追查這些嫌疑人。根據之前的證詞，竊賊計劃搭乘從Fiftyville出發的最早航班，所以我們需要注意的是那位搭乘最早航班的嫌疑人。
-- 在這種情況下，最早的航班是航班ID 36，目的地為紐約市。在此航班上，我們有兩位嫌疑人：Bruce（座位4A）和Luca（座位7B）。
-- 現在我們已經找到了可能的竊賊 Bruce。同謀是 Luca。
-- 但是答案不正確！

-- Searching for people who had a phone call with Bruce or Luca on July 28, 2021.
-- 我們需要找出在2021年7月28日與Bruce或Luca通話的人
-- 查找與Bruce或Luca通話的人
SELECT p1.name AS caller, p2.name AS receiver, phone_calls.duration
FROM phone_calls
JOIN people p1 ON p1.phone_number = phone_calls.caller
JOIN people p2 ON p2.phone_number = phone_calls.receiver
WHERE (phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28)
AND (p1.name IN ('Bruce', 'Luca') OR p2.name IN ('Bruce', 'Luca'))
ORDER BY phone_calls.duration;
-- 有線索了！
-- +---------+----------+----------+
-- | caller  | receiver | duration |
-- +---------+----------+----------+
-- | Bruce   | Robin    | 45       |
-- | Kathryn | Luca     | 60       |
-- | Bruce   | Carl     | 75       |
-- | Bruce   | Deborah  | 120      |
-- | Bruce   | Gregory  | 241      |
-- | Walter  | Luca     | 595      |
-- +---------+----------+----------+
-- Based on these clues, we can see that on July 28th, 2021, Bruce and Luca each had a phone call with someone else. We need to find the person who had the shortest phone call with either Bruce or Luca to identify a possible accomplice. According to the query result, the shortest calls were:
-- Bruce and Robin, duration 45 seconds
-- Kathryn and Luca, duration 60 seconds
-- Since Bruce is the thief, we will focus on Robin, who had the shortest call with him.
-- Therefore, the answer should be:
-- Thief: Bruce
-- City where the thiyef fled: New York City
-- Accomplice: Robin
-- 根據這些線索，我們可以看到在2021年7月28日，Bruce和Luca分別與其他人通話。在這些通話中，我們需要找到與Bruce或Luca通話時間最短的人
-- 以找到可能的幫兇。根據查詢結果，最短的通話是：
-- Bruce 和 Robin，時長 45 秒
-- Kathryn 和 Luca，時長 60 秒
-- 由於Bruce 是小偷，我們將關注與他通話時間最短的Robin。
-- 因此，答案應該是：
-- 小偷：Bruce
-- 小偷逃往的城市：New York City
-- 幫兇：Robin