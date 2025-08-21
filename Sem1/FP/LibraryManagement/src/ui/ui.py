from src.services.services import Services

ADD_BOOK = "1"
DISPLAY_BOOKS = "2"
FILTER_BOOKS_BY_WORD = "3"
UNDO_LAST_OPERATION = "4"
EXIT_PROGRAM = "0"

class UI:
    def __init__(self):
        self.__services = Services()

    def print_menu(self):
        print(ADD_BOOK + ". Add new book.")
        print(DISPLAY_BOOKS + ". Display all books.")
        print(FILTER_BOOKS_BY_WORD + ". Filter books by given word.")
        print(UNDO_LAST_OPERATION + ". Undo last operation.")
        print(EXIT_PROGRAM + ". Exit.")

    def start(self):
        while True:
            self.print_menu()
            try:
                user_choice = input("Enter your choice: ")
                if user_choice == EXIT_PROGRAM:
                    break
                elif user_choice == ADD_BOOK:
                    self.__add_book_ui()
                elif user_choice == DISPLAY_BOOKS:
                    self.__display_books_ui()
                elif user_choice == FILTER_BOOKS_BY_WORD:
                    self.__filter_by_word_ui()
                elif user_choice == UNDO_LAST_OPERATION:
                    self.__undo_last_operation_ui()
            except Exception as error:
                print(error)

    def __add_book_ui(self):
        isbn = input("Enter ISBN: ")
        author = input("Enter author: ")
        title = input("Enter title: ")
        self.__services.add_book(isbn, author, title)

    def __display_books_ui(self):
        books = self.__services.get_all_books()
        if books:
            for book in books:
                print(book)
        else:
            print("No books found.")

    def __filter_by_word_ui(self):
        word_to_filter_books = input("Enter word by which we filter books: ")
        filtered_books = self.__services.filter_books(word_to_filter_books)
        if filtered_books:
            for book in filtered_books:
                print(book)

    def __undo_last_operation_ui(self):
        self.__services.undo_last_operation()

if __name__ == "__main__":
    ui = UI()
    ui.start()

