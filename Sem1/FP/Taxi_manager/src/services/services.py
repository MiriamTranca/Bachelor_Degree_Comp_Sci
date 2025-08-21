from src.domain.domain import Order


class Services:
    def __init__(self, drivers_repository, orders_repository):
        self.__drivers_repository = drivers_repository
        self.__orders_repository = orders_repository

    def add_order(self, driver_id, distance):
        if not self.__drivers_repository.driver_exists(driver_id):
            raise ValueError('Driver does not exist')
        if distance < 1:
            raise ValueError('Distance must be greater or equal to 1')
        order =  Order(driver_id, distance)
        self.__orders_repository.add_order(order)

    def display_all_drivers(self):
        return self.__drivers_repository.get_all_drivers()

    def display_all_orders(self):
        return self.__orders_repository.get_all_orders()

    def display_driver_income(self, driver_id):
        for driver in self.__drivers_repository.get_all_drivers():
            if driver.id == driver_id:
                name = driver.name

        income = 0
        for order in self.__orders_repository.get_all_orders():
            if order.driver_id == driver_id:
                income += order.distance

        income *= 2.5

        print(f"The driver with Id {driver_id} and name {name} has an income {income}")

