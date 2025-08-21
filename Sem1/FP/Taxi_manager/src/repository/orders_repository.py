from src.domain.domain import Order


class OrdersRepository:
    def __init__(self, filename):
        self.__filename = filename

    def add_order(self, order):
        with open(self.__filename, 'a') as file:
            file.write(f"{order.driver_id},{order.distance}\n")

    def get_all_orders(self):
        orders = []
        with open(self.__filename, 'r') as file:
            for line in file:
                driver_id, distance = line.strip().split(',')
                orders.append(Order(driver_id, float(distance)))
        return orders



