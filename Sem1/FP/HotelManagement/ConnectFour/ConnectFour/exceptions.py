class BoardException(Exception):
    def __init__(self, message):
        self.__message = message

    def __str__(self):
        return self.__message

class InvalidPositionException(BoardException):
    def __init__(self):
        super().__init__("Invalid position, out of bounds. Try another one.")

class FullColumnException(BoardException):
    def __init__(self):
        super().__init__("Column is full. Try another one.")

class GameOverException(BoardException):
    pass