from texttable import Texttable

from exceptions import InvalidPositionException, FullColumnException

FIRST_ROW = 0
FIRST_COLUMN = 0
NUMBER_ROWS = 6
NUMBER_COLUMNS = 7
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

class ConnectFourBoard:
    def __init__(self, number_rows = NUMBER_ROWS, number_columns = NUMBER_COLUMNS):
        self.__number_rows =  number_rows
        self.__number_columns = number_columns
        self._board = [[" " for _ in range(self.__number_columns)] for _ in range(self.__number_rows)]

    @property
    def number_rows(self):
        return self.__number_rows

    @property
    def number_columns(self):
        return self.__number_columns

    def __str__(self):
        table = Texttable()
        table.header([" "] + [str(index_column) for index_column in range(self.number_columns)])
        for index_row, row in enumerate(self._board):
            table.add_row([str(index_row)] + row)
        return table.draw()

    def drop_token(self, column, token):

        if not (FIRST_COLUMN <= column < self.number_columns):
            raise InvalidPositionException()

        for row in range(self.number_rows - 1, -1, -1):
            if self._board[row][column] == " ":
                self._board[row][column] = token
                return row, column
        raise  FullColumnException()

    def check_win_by_direction(self, row, column, token, row_step, column_step):
        count = 0
        copy_row, copy_column = row, column
        while FIRST_ROW <= copy_row < self.number_rows and FIRST_COLUMN <= copy_column < self.number_columns and self._board[copy_row][copy_column] == token:
            count += INCREMENT_UNIT
            copy_row += row_step
            copy_column += column_step

        copy_row, copy_column = row - row_step, column - column_step

        while FIRST_ROW <= copy_row < self.number_rows and FIRST_COLUMN <= copy_column < self.number_columns and self._board[copy_row][copy_column] == token:
            count += INCREMENT_UNIT
            copy_row -= row_step
            copy_column += column_step

        return count >= COUNT_FOR_WIN

    def check_for_win(self, row, column, token):
        #check horizontal, vertical, diagonal 1, diagonal 2
        return (
            self.check_win_by_direction(row, column, token, ROW_STEP_VERTICAL, COLUMN_STEP_VERTICAL) or
            self.check_win_by_direction(row, column, token, ROW_STEP_HORIZONTAL, COLUMN_STEP_HORIZONTAL) or
            self.check_win_by_direction(row, column, token, ROW_STEP_DIAGONAL_1, COLUMN_STEP_DIAGONAL_1) or
            self.check_win_by_direction(row, column, token, ROW_STEP_DIAGONAL_2, COLUMN_STEP_DIAGONAL_2)
        )


