from src.domain.book import Book

class RepositoryError(Exception):
    """
    Errors related to repository
    """
    pass

BOOKS = [
    ("12345-isbn", "Jane Austin", "Book1"),
    ("12346-isbn", "Jane Austin", "Book2"),
    ("12347-isbn", "Author1", "Book Black Cat"),
    ("12348-isbn", "Author2", "The Silent Night"),
    ("12349-isbn", "Author3", "Gone with the Wind"),
    ("12350-isbn", "Author4", "The Dark Horizon"),
    ("12351-isbn", "Author5", "The Lost World"),
    ("12352-isbn", "Author6", "The Shadow of Time"),
    ("12353-isbn", "Author7", "The Final Voyage"),
    ("12354-isbn", "Author8", "City of Dreams")
]
ISBNS_INDEX = 0
AUTHORS_INDEX = 1
TITLES_INDEX = 2

class MemoryRepository:
    def __init__(self):
        self._data = []

    def generate_data(self):
        for index in range(len(BOOKS)):
            book = BOOKS[index]
            isbn = book[ISBNS_INDEX]
            author = book[AUTHORS_INDEX]
            title = book[TITLES_INDEX]

            book = Book(isbn, author, title)

            self._data.append(book)

    def set_data(self, data):
        self._data = list(data)

    def add_book(self, book):
        self._data.append(book)

    def get_all_books(self):
        return self._data

    def remove_book(self, book):
        self._data.remove(book)

    def remove_list_of_books(self, list_books):
        for book in list_books:
            self.remove_book(book)

    def __len__(self):
        return len(self._data)

def test_memory_repository_add():
    repository = MemoryRepository()
    repository_length = 0

    assert repository_length == len(repository)

    for index in range(3):
        book = BOOKS[index]

        isbn = book[ISBNS_INDEX]
        author = book[AUTHORS_INDEX]
        title = book[TITLES_INDEX]

        book = Book(isbn, author, title)

        repository.add_book(book)
        repository_length += 1

    assert repository_length == len(repository)

    try:
        book1 = Book("12345", "Author1", "Book Black Cat")
        repository.add_book(book1)
        book2 = Book("12345", "Author2", "The Dark Horizon")
        repository.add_book(book2)

    except RepositoryError:
        assert True

if __name__ == "__main__":
    test_memory_repository_add()
