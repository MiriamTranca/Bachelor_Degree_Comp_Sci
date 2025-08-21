from src.repository.drivers_repository import DriversRepository
from src.repository.orders_repository import OrdersRepository
from src.services.services import Services
from src.ui.ui import Ui
import os

if __name__ == '__main__':
    current_dir = os.path.dirname(__file__)
    drivers_path = os.path.join(current_dir, "drivers.txt")
    drivers_repository = DriversRepository(drivers_path)
    orders_path = os.path.join(current_dir, "orders.txt")
    orders_repository = OrdersRepository(orders_path)
    service = Services(drivers_repository, orders_repository)
    ui = Ui(service)
    ui.run()