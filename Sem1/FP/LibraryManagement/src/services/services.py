

from src.domain.book import Book
from src.repository.binary_repository import BinaryRepository
from src.repository.memory_repository import MemoryRepository
from src.repository.repository_loader import RepositoryLoader
from src.repository.text_file_repository import TextFileRepository

REPOSITORIES = {"BinaryRepository": BinaryRepository, "MemoryRepository": MemoryRepository, "TextFileRepository": TextFileRepository}

LENGTH_IS_ZERO = 0

class ISBNError(Exception):
    """
    Error if ISBN not unique
    """
    pass

class UndoError(Exception):
    """
    Error if 'undo' command cannot be executed
    """
    pass

class Services:
    def __init__(self):
        repository_loaded = RepositoryLoader()
        repository_class = repository_loaded.get_repository_class()
        repository_file = repository_loaded.get_repository_file()

        if repository_class == "MemoryRepository":
            self.__repository = REPOSITORIES["MemoryRepository"]()
            self.__repository.generate_data()
        else:
            self.__repository = REPOSITORIES[repository_class](repository_file)

        self._history = []

    def _load_history(self):
        """
        Update the history list
        :return: None
        """
        self._history.append(list(self.__repository.get_all_books()))

    def get_all_books(self):
        return self.__repository.get_all_books()

    def _is_book_valid(self, isbn) -> bool:
        """
        Check if a book is valid - checking if ISBN is unique
        :param book: Book object
        :return: True if ISBN is valid
        :raise: ISBNError if ISBN is not unique
        """
        if  any(book.isbn == isbn for book in self.__repository.get_all_books()):
            raise ValueError("ISBN must be unique.")
        return True

    def add_book(self, isbn, author, title):
        if self._is_book_valid(isbn):
            new_book = Book(isbn, author, title)
            self._load_history()
            self.__repository.add_book(new_book)

    def filter_books(self, word_to_filter_books):
        list_books = self.__repository.get_all_books()
        list_books_to_be_removed = []
        for book in list_books:
            if book.title.startswith(word_to_filter_books):
                list_books_to_be_removed.append(book)

        self._load_history()
        self.__repository.remove_list_of_books(list_books_to_be_removed)

    def undo_last_operation(self):
        if len(self._history) == LENGTH_IS_ZERO:
            raise UndoError("Undo operation cannot be executed anymore.")
        self.__repository.set_data(self._history.pop())
