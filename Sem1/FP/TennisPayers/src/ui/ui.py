class Ui:
    def __init__(self, service):
        self.__service = service

    def display_players(self):
        print("\nPlayers sorted by strength:")
        for player in self.__service.sort_players_by_strength():
            print(player)

    def start_tournament(self):
        print("\nStarting tournament...")
        self.__service.sort_players_by_strength()
        self.display_players()

        self.__service.play_qualifying_round()
        while len(self.__service.get_players()) > 1:
            self.__service.play_round()

        winner = self.__service.get_winner()
        print(f"\nTournament Winner: {winner.name} with strength {winner.strength}!")

