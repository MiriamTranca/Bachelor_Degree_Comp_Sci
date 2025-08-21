class Book:
    def __init__(self, isbn: str, author: str, title: str):
        if not isbn or not author or not title:
            raise ValueError("No field can be empty. ")
        self.__isbn = isbn
        self.__author = author
        self.__title = title

    @property
    def isbn(self):
        return self.__isbn

    @property
    def author(self):
        return self.__author

    @property
    def title(self):
        return self.__title

    @author.setter
    def author(self, new_author):
        self.__author = new_author

    @title.setter
    def title(self, new_title):
        self.__title = new_title

    def __str__(self):
        return "ISBN: " + self.__isbn + ", Author: " + self.__author + ", Title:" + self.__title

def test_book():
    new_book = Book(isbn="123", author="<NAME>", title="My Book")
    assert new_book.isbn == "123"
    assert new_book.author == "<NAME>"
    assert new_book.title == "My Book"

if __name__ == "__main__":
    test_book()



