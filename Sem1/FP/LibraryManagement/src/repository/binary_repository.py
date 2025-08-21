import pickle
from src.domain.book import Book
from src.repository.memory_repository import MemoryRepository, RepositoryError

class BinaryRepository(MemoryRepository):
    def __init__(self, file_name: str):
        super().__init__()
        self.__file_name = file_name
        try:
            self.__load()
        except FileNotFoundError:
            raise RepositoryError("File not found.")
        except Exception:
            raise RepositoryError("Something went wrong.")

    def __load(self):
        try:
            with open(self.__file_name, "rb") as data_file:
                self._data = pickle.load(data_file)
        except EOFError:
            self.__generate_data()
        except FileNotFoundError:
            self.__generate_data()
        except Exception :
            raise RepositoryError(f"Error loading data")

    def __generate_data(self):
        super().generate_data()
        self.__save()

    def __save(self):
        with open(self.__file_name, "wb") as data_file:
            pickle.dump(self._data, data_file)

    def set_data(self, data):
        super().set_data(data)
        self.__save()

    def add_book(self, book: Book):
        super().add_book(book)
        self.__save()

    def remove_list_of_books(self, books_list):
        super().remove_list_of_books(books_list)
        self.__save()
