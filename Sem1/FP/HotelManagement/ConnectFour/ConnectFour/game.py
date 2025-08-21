from random import randint

from exceptions import BoardException, FullColumnException

FIRST_ROW = 0
FIRST_COLUMN = 0
INCREMENT_UNIT = 1
COUNT_FOR_WIN = 4
ROW_STEP_VERTICAL = 0
COLUMN_STEP_VERTICAL = 1
ROW_STEP_HORIZONTAL = 1
COLUMN_STEP_HORIZONTAL = 0
ROW_STEP_DIAGONAL_1 = 1
COLUMN_STEP_DIAGONAL_1 = 1
ROW_STEP_DIAGONAL_2 = 1
COLUMN_STEP_DIAGONAL_2 = -1

class GameConnectFour:
    def __init__(self, board):
        self.__board = board

    def player_drop_token(self, column):
        try:
            row, column = self.__board.drop_token(column, 'x')
            return row, column
        except BoardException as exception:
            print(exception)
            return None

    def computer_drop_token(self):
        blocking_column = self.find_blocking_move()
        if blocking_column is not None:
            try:
                row, column = self.__board.drop_token(blocking_column, 'o')
                return row, blocking_column
            except BoardException:
                pass

        while True:
            column = randint(FIRST_COLUMN, self.__board.number_columns - 1)
            try:
                row, column = self.__board.drop_token(column, 'o')
                return row, column
            except BoardException:
                continue

    def simulate_drop_token(self, column, board, token):
        if column < 0 or column >= board.number_columns:
            raise BoardException("Invalid column")

        temporary_board = [row[:] for row in board._board]
        for row in range(board.number_rows - 1, -1, -1):
            if temporary_board[row][column] == " ":
                temporary_board[row][column] = token
                return temporary_board, row
        raise FullColumnException()

    def find_blocking_move(self):
        for column in range(self.__board.number_columns):
            try:
                temporary_board, row = self.simulate_drop_token(column, self.__board, 'x')
                if self.check_for_win_temporary_board(temporary_board, row, column, 'x'):
                    return column
            except BoardException:
                continue
        return None

    def count_tokens(self, board, row, column, token, row_step, column_step):
        count = 0
        while FIRST_ROW <= row < len(board) and FIRST_COLUMN <= column < len(board[FIRST_ROW]) and board[row][column] == token:
            count += INCREMENT_UNIT
            row += row_step
            column += column_step
        return count

    def check_for_win_temporary_board(self, temporary_board, row, column, token):
        directions = [
            (ROW_STEP_VERTICAL, COLUMN_STEP_VERTICAL),
            (ROW_STEP_HORIZONTAL, COLUMN_STEP_HORIZONTAL),
            (ROW_STEP_DIAGONAL_1, COLUMN_STEP_DIAGONAL_1),
            (ROW_STEP_DIAGONAL_2, COLUMN_STEP_DIAGONAL_2)
        ]
        for row_step, column_step in directions:
            count = self.count_tokens(temporary_board, row, column, token, row_step, column_step)
            count += self.count_tokens(temporary_board, row, column, token, -row_step, -column_step) -1
            if count >= COUNT_FOR_WIN:
                return True
        return False
