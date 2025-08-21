from src.domain.book import Book
from src.repository.memory_repository import MemoryRepository, RepositoryError, ISBNS_INDEX, AUTHORS_INDEX, TITLES_INDEX

LENGTH_IS_ZERO = 0
class TextFileRepository(MemoryRepository):
    def __init__(self, file_name: str ):
        super().__init__()
        self.__file = file_name
        try:
            self.__load_file()
        except FileNotFoundError:
            raise RepositoryError("File not found. ")
        except Exception:
            raise RepositoryError("Something went wrong. ")

    def __load_file(self):
        data_file = open(self.__file, "rt")
        data_line = data_file.readline()
        data_file.close()

        if len(data_line) == LENGTH_IS_ZERO:
            self.__generate_data()
        else:
            self._data = []
            data_items = data_line.split("; ")
            data_items.pop()
            for data_item in data_items:
                parameters = data_item.split(", ")
                isbn = parameters[ISBNS_INDEX].strip()
                author = parameters[AUTHORS_INDEX].strip()
                title = parameters[TITLES_INDEX].strip()

                self._data.append(Book(isbn, author, title))

    def __generate_data(self):
        super().generate_data()
        self.__save()

    def __save(self):
        data_file = open(self.__file, 'wt')
        for item in self._data:
            data_file.write(str(item) + "; ")
        data_file.close()

    def set_data(self, data):
        super().set_data(data)
        self.__save()

    def add_book(self, book: Book):
        super().add_book(book)
        self.__save()

    def remove_list_of_books(self, books_list):
        super().remove_list_of_books(books_list)
        self.__save()

