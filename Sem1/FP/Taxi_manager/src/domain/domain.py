class Driver():
    def __init__(self, id, name):
        self.__id = id
        self.__name = name

    @property
    def id(self):
        return self.__id

    @property
    def name(self):
        return self.__name

    def __str__(self):
        return f"{self.__id},{self.__name}"

class Order():
    def __init__(self, driver_id, distance):
        self.__driver_id = driver_id
        self.__distance = distance

    @property
    def driver_id(self):
        return self.__driver_id

    @property
    def distance(self):
        return self.__distance

    def __str__(self):
        return f"{self.__driver_id},{self.distance}"
