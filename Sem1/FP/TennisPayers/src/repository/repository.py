from src.domain.domain import Player

class Repository:
    def __init__(self, filename):
        self.__filename = filename

    def read_players_from_file(self):
        players = []
        with open(self.__filename, 'r') as file:
            for line in file:
                player_id, name, strength = line.strip().split(',')
                players.append(Player(player_id, name, int(strength)))
        return players

