import unittest

from board import ConnectFourBoard
from exceptions import InvalidPositionException, FullColumnException

NUMBER_OF_TOKENS_TO_WIN = 4

class TestConnectFourBoard(unittest.TestCase):
    def setUp(self):
        self.board = ConnectFourBoard()

    def test_drop_token(self):
        row, column = self.board.drop_token(0, 'x')
        self.assertEqual(row, 5)
        self.assertEqual(column, 0)
        self.assertEqual(self.board._board[row][column], 'x')

    def test_drop_token_invalid_position(self):
        with self.assertRaises(InvalidPositionException):
            self.board.drop_token(7, 'x')

        with self.assertRaises(InvalidPositionException):
            self.board.drop_token(-1, 'x')

    def test_drop_token_on_full_column(self):
        for _ in range (self.board.number_rows):
            self.board.drop_token(0, 'x')

        with self.assertRaises(FullColumnException):
            self.board.drop_token(0, 'x')

    def test_check_win_by_direction_horizontal(self):
        for column in range(NUMBER_OF_TOKENS_TO_WIN):
            self.board.drop_token(column, 'x')
        self.assertFalse(self.board.check_for_win(5,3,'x'))

    def test_check_win_by_direction_vertical(self):
        for _ in range(NUMBER_OF_TOKENS_TO_WIN):
            self.board.drop_token(0, 'x')
        self.assertTrue(self.board.check_for_win(2,0,'x'))

if __name__ == '__main__':
    unittest.main()