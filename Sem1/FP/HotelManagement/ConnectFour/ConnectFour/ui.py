from board import ConnectFourBoard
from exceptions import InvalidPositionException, GameOverException, BoardException
from game import GameConnectFour

FIRST_COLUMN = 0
LAST_COLUMN = 6
class UI:
    def __init__(self):
        self.__board = ConnectFourBoard()
        self.__game_connect_four = GameConnectFour(self.__board)

    def print_board(self):
        print("Board: ")
        print(self.__board)

    def start_game(self):
        print("Welcome to Connect Four: ")
        self.print_board()

        player_turn = True
        while True:
            if player_turn:
                try:
                    column = int(input("Choose a column between 0-6: "))


                    if column < FIRST_COLUMN or column > LAST_COLUMN:
                        raise InvalidPositionException



                    row, column = self.__game_connect_four.player_drop_token(column)
                    self.print_board()


                    if self.__board.check_for_win(row, column, 'x'):
                        print("You have won!")
                        break
                    player_turn = False

                except GameOverException:
                    print("Game over!")
                    break
                except (InvalidPositionException, BoardException) as exception:
                    print(exception)
                    continue

            else:
                try:
                    # Computer's turn
                    row, column = self.__game_connect_four.computer_drop_token()
                    self.print_board()

                    # Check for win on computer's turn
                    if self.__board.check_for_win(row, column, 'o'):
                        print("Computer has won!")
                        break
                    player_turn = True

                except GameOverException:
                    print("Game over!")
                    break
