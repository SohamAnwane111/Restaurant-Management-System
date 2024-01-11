# Restaurant-Management-System

Problem Statement:

Online ordering of food now-a-days is common. Managing the system is a tedious task. The goal here is to design a system which performs the task.

Create a list of restaurants in a city. Each restaurant is with attributes:
a. Listing of generic food items and their respective prices for given quantity.
b. Special items available at the restaurant and their prices
c. Special Item of the day and its price.
d. Service time required for a given quantity of every food item.

The list of restaurant records has to be in sorted order based on the key (Name and Address) i.e. the list of restaurants is primarily sorted on name-of-restaurant. If two or more restaurants are having same name, then they are sorted on their address.

Also, users are placing orders with the restaurants. Maintain a live record of orders for each restaurant. For every order, the order time, user-name, user-phone number, user-address, food-item ordered, quantity of food items ordered and expected delivery time are to be maintained. The delivery time can be calculated by considering service time for all the food items (make appropriate assumptions in this calculation). The list of active/live orders should be in the sorted order of first the order time and then the delivery time.

The list of restaurant records has to be in sorted order based on the key (Name and Address).
Also, maintain a database of live records of orders for each restaurant. Every order comes with order-time, food-item ordered, quantity of food items ordered and the expected delivery time. The live records should be sorted with respect to order-time and for same order- times, based on delivery time.
The following operations are to be defined so as to make the system function properly.

a. getMinTime() – Given food item and quantity, outputs the name, address and delivery time of the restaurant taking minimum time to deliver the food order.
Input: food order and quantity
Output: restaurant-name, restaurant-address, time required to deliver.

b. getItemAvailability() – For the given food item, outputs the list of restaurants having the food item and respective prices.
Input: food item
Output: list of restaurants and item with price at every restaurant

c. placeOrder() – Places an order for the food item.
Input: list of items, quantity, user-name, user-phone-number, user-address
Output: orderID

d. getItemListInSortedOrder() – For a given restaurant, outputs list of items in the sorted order of names.
Input: restaurant name
Output: list of items in restaurant in sorted order based on name

e. getItemListInAreaSortedOrder() – For a given area, prints list of food-items available in that area in the sorted order of restaurants.
Input: Area
Output: list of items available items in sorted order based on name of restaurant for restaurants in the given area

f. getAllSpecialItemListinSortedOrder() - Gives list of special items in a list of restaurants
Input: restaurant list
Output: list of special items in the restaurants of input restaurant-list in sorted order based on item-name and price, also print the corresponding restaurant-name and its address

g. getItemofDayListinSortedOrder() – Gives a list of “Items-of-day” in the restaurants in the given area
Input: area
Output: list of all “item of the day” in all restaurant in sorted order based on food-item-name and food-item-price

h. getCommonItem() – Finds common food-item in the restaurant list
Input: restaurant list
Output: Common items present in the restaurants of the input restaurant-list given in the sorted order based on item-name. List prices of the items in different restaurants.

i. getAllUniqueItem()
Input: restaurant list
Output: unique items present in each restaurant of input restaurant-list in sorted order based on item-name and price. Also print name of the restaurant and its address.
