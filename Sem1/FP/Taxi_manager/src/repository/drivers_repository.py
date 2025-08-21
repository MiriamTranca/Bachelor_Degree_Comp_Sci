from src.domain.domain import Driver


class DriversRepository:
    def __init__(self, filename):
        self.__filename = filename

    def get_all_drivers(self):
        drivers = []
        with open(self.__filename, 'r') as file:
            for line in file:
                id, name = line.strip().split(',')
                drivers.append(Driver(id, name))
        return drivers

    def driver_exists(self, driver_id):
        return any(driver_id == driver.id for driver in self.get_all_drivers())

