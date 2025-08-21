class Player():
    def __init__(self, player_id, name, strength):
        self.__player_id = player_id
        self.__name = name
        self.__strength = strength

    def __str__(self):
        return f"{self.__player_id},{self.__name},{self.__strength}"

    @property
    def player_id(self):
        return self.__player_id

    @property
    def name(self):
        return self.__name

    @property
    def strength(self):
        return self.__strength

    def increase_strength(self):
        self.__strength += 1
