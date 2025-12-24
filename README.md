# CarSales

CarSales is a simple console application written in C for managing a fictional car dealership. It lets users browse inventory, purchase vehicles, record sales, and collect customer feedback. Data for sales are persisted between runs in a `sales.txt` file.

## Features

- Display available car models with pricing, model year, and current stock.
- Allow customers to choose a vehicle and quantity to purchase, with validation against stock levels.
- Apply an automatic discount equal to the buyer's age (for ages 18–25) and record the discounted sale amount.
- Persist sales information to `sales.txt` so it can be reloaded and sorted by sale amount.
- Collect short feedback entries with 1–5 star ratings and timestamps after successful purchases.

## Running

You will be greeted by name and shown a menu:

- **a** – View cars (sorted by model year, newest first)
- **b** – Buy cars (select a model, quantity, and provide your age for potential discounts)
- **c** – View sales info (loads `sales.txt`, sorts by sale amount, and displays each sale)
- **e** – View customer/visitor testimonials
- **f** – Exit the application

Most screens prompt you to press Enter to continue before returning to the menu.

## Data files

- **sales.txt** – Binary file that stores serialized `Customer` records. It is created automatically after the first successful sale.

## Notes
- The program uses simple bubble-sort logic to keep the car list ordered by year.
- Discounts are calculated as the buyer's age percentage (e.g., age 20 → 20% off) for ages between 18 and 25.
- Feedback collection occurs only after a valid purchase; if a buyer is under the minimum age, the transaction is blocked and no feedback is requested.
