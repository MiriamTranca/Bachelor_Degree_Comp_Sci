from src.repository.repository import Repository
from src.services.services import Service
from src.ui.ui import Ui
import os

if __name__ == "__main__":
    file_path = os.path.dirname(__file__)
    input_file_path = os.path.join(file_path, "players.txt")

    player_repository = Repository(input_file_path)
    players = player_repository.read_players_from_file()

    tournament_service = Service(players)
    ui = Ui(tournament_service)
    ui.start_tournament()