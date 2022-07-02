-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description FROM crime_scene_reports WHERE day = "28" AND month = "7" AND year = "2020";
SELECT activity FROM courthouse_security_logs WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10";
SELECT activity,hour, minute, license_plate FROM courthouse_security_logs WHERE day = "28" AND month = "7" AND year = "2020" AND hour >= "9" AND hour <= "10";
SELECT name, transcript FROM interviews WHERE day = "28" AND month = "7" AND year = "2020";
SELECT account_number, transaction_type, amount FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = "28" AND month = "7" AND year = "2020";
SELECT name, license_plate FROM people WHERE id IN(SELECT person_id FROM bank_accounts WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = "28" AND month = "7" AND year = "2020"));
SELECT name, license_plate, phone_number FROM people WHERE id IN(SELECT person_id FROM bank_accounts WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = "28" AND month = "7" AND year = "2020")) AND license_plate IN(SELECT license_plate
FROM courthouse_security_logs WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute < "25" AND minute > "15");
SELECT caller, receiver,duration FROM phone_calls WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60";
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE caller = "(770) 555-1861");
SELECT caller, receiver, duration FROM phone_calls WHERE year = "2020" AND month = "7" AND day = "28" AND duration < "61";
SELECT name FROM people WHERE phone_number IN(SELECT caller FROM phone_calls WHERE year = "2020" AND month = "7" AND day = "28" AND duration < "60")AND passport_number IN(SELECT passport_number FROM passengers WHERE flight_id IN(SELECT id FROM flights WHERE day = "29" AND month = "7" AND year = "2020" AND hour = "8" AND origin_airport_id IN(SELECT id FROM airports WHERE full_name = "Fiftyville Regional Airport")))AND name IN(SELECT name FROM people WHERE id IN(SELECT person_id FROM bank_accounts WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = "28" AND month = "7" AND year = "2020")))AND license_plate IN(SELECT license_plate
FROM courthouse_security_logs WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute < "25" AND minute > "15" AND activity = "exit");
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE caller IN(SELECT caller FROM phone_calls WHERE caller IN(SELECT phone_number FROM people WHERE name = "Ernest")) AND year = "2020" AND month = "7" AND day = "28" AND duration < "60");
SELECT full_name FROM airports WHERE id IN(SELECT destination_airport_id FROM flights WHERE origin_airport_id IN(SELECT id FROM airports WHERE city = "Fiftyville"));
SELECT city FROM airports WHERE id IN(SELECT destination_airport_id FROM flights WHERE origin_airport_id IN(SELECT id FROM airports WHERE city = "Fiftyville")AND year = "2020" AND day = "29" AND month = "7" ORDER BY hour, minute);
SELECT name FROM people WHERE passport_number IN(SELECT passport_number FROM passengers WHERE flight_id IN(SELECT id FROM flights WHERE day = "29" AND month = "7" AND year = "2020" AND hour = "8" AND origin_airport_id IN(SELECT id FROM airports WHERE city = "Fiftyville")));
SELECT seat FROM passengers WHERE passport_number IN(SELECT passport_number FROM passengers WHERE flight_id IN(SELECT id FROM flights WHERE day = "29" AND month = "7" AND year = "2020" AND hour = "8" AND origin_airport_id IN(SELECT id FROM airports WHERE city = "Fiftyville")));
SELECT full_name FROM airports WHERE city = "Chicago";
SELECT name FROM people WHERE phone_number IN(SELECT receiver FROM phone_calls WHERE caller IN(SELECT phone_number FROM people WHERE name = "Ernest")AND day = "28" AND month = "7" AND duration < "61");
SELECT receiver,duration FROM phone_calls WHERE caller IN(SELECT phone_number FROM people WHERE name = "Ernest")AND day = "28" AND month = "7";
SELECT name FROM people WHERE license_plate IN(SELECT license_plate FROM courthouse_security_logs WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute > "15" AND minute < "25");
SELECT name FROM people WHERE id IN(SELECT person_id FROM bank_accounts WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND day = "28" AND month = "7" AND year = "2020"));
SELECT name FROM people WHERE phone_number IN(SELECT caller FROM phone_calls WHERE caller IN(SELECT phone_number FROM people WHERE name = "Ernest" OR name = "Elizabeth" OR name = "Danielle" OR name = "Russell" )AND day = "28" AND month = "7" AND duration < "61");
SELECT name FROM people WHERE passport_number IN(SELECT passport_number FROM passengers WHERE flight_id IN(SELECT id FROM flights WHERE origin_airport_id IN(SELECT id FROM airports WHERE city = "Fiftyville") AND day = "29" AND month = "7"AND hour = "8"));
SELECT city FROM airports WHERE id IN(SELECT destination_airport_id)
SELECT destination_airport_id,day,hour, minute FROM flights WHERE origin_airport_id IN(SELECT id FROM airports WHERE city = "Fiftyville")AND year = "2020" AND day = "29" AND month = "7" ORDER BY hour, minute;
SELECT city FROM airports WHERE id = "4";

Jose | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”
Eugene | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”
Barbara | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.
Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have se curity footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.


name | phone_number | passport_number | license_plate
Ernest | (367) 555-5533 | 5773159633 | 94KL13X




Russell
Ernest