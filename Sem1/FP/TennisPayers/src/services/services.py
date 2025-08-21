import random
STEP = 2
FIRST_PLAYER = 0
SECOND_PLAYER = 1
NUMBER_FIRST_PLAYER = 1
NUMBER_SECOND_PLAYER = 2
START = 0
class Service:
    def __init__(self, players):
        self.__players = players

    def get_players(self):
        return self.__players

    def sort_players_by_strength(self):
        self.__players.sort(key=lambda player: player.strength, reverse=True)
        return self.__players

    def create_pairs(self):
        random.shuffle(self.__players)
        pairs = [(self.__players[index], self.__players[index+1]) for index in range (START, len(self.__players), STEP)]
        return pairs

    def play_qualifying_round(self):
        while len(self.__players) & (len(self.__players) - 1) != 0:
            lowest_strength_player = min(self.__players, key=lambda player: player.strength)
            self.__players.remove(lowest_strength_player)

    def play_round(self):
        try:
            round_name = {8: "quarter-finals", 4: "semi-finals", 2: "final"}.get(len(self.__players))
            print(f"\nPlaying {round_name}")

            pairs = self.create_pairs()
            for pair in pairs:
                print(f"Match: {pair[FIRST_PLAYER].name} (Strength: {pair[FIRST_PLAYER].strength}) vs {pair[SECOND_PLAYER].name} (Strength: {pair[SECOND_PLAYER].strength})")
                winner = int(input(f"Enter winner (1 for {pair[FIRST_PLAYER].name}, 2 for {pair[SECOND_PLAYER].name}): "))

                if winner == NUMBER_FIRST_PLAYER:
                    pair[FIRST_PLAYER].increase_strength()
                    self.__players.remove(pair[SECOND_PLAYER])
                elif winner == NUMBER_SECOND_PLAYER:
                    pair[SECOND_PLAYER].increase_strength()
                    self.__players.remove(pair[FIRST_PLAYER])
                else:
                    raise ValueError(f"Invalid winner: {winner}")
        except ValueError as error:
            print(error)
    def get_winner(self):
        if len(self.__players) == 1:
            return self.__players[FIRST_PLAYER]
        else:
            raise ValueError("Tournament is not over yet.")
