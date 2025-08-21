from Domain import Board, AI
from random import randint

class UI:

    @staticmethod
    def PrintMenu():
        string = "Choose one of the following: \n"
        string += "1. Start a new game \n"
        string += "2. Continue an old one \n"
        string += "0. Exit"
        print(string)

    @staticmethod
    def ValidCommands(command):
        availablecommands = ['1', '2', '0']
        return command in availablecommands

    @staticmethod
    def checkinteger(msg):

        if msg.isdigit():
            return int(msg)
        return "fals"

    def NewGame(self):
        b = Board()
        ai = AI()

        print(b)

        while b.isGameWon("O") == False and b.isGameWon("X") == False:
            ok = False
            while ok == False:
                line = input("Choose your line: ")
                column = input("Choose your column: ")
                piece = input("Choose your piece: X or O: ")
                if self.checkinteger(line) == "fals":
                    print("Line is not an integer!")
                else:
                    if self.checkinteger(column) == "fals":
                        print("Column is not an integer!")
                    else:
                        line = self.checkinteger(line)
                        column = self.checkinteger(column)
                        if 0 <= line <= 5 and 0 <= column <= 5:
                            if b.data[line][column] == " ":
                                if piece == "X" or piece ==  "O":
                                    b.move(piece, line, column)
                                    ok = True
                                else:
                                    print("The chosen piece is not available!")
                            else:
                                print("The chosen position is not available!")
                        else:
                            print("Give adequate coordinates! (between 0 and 5)")

            print(b)

            if b.isGameWon("O") == True or b.isGameWon("X") == True:
                print("You won")
                break
            if b.nospacesleft() == True:
                print("Computer wins")
                break

            ai.move("X", "O", b)
            print(b)

            if b.isGameWon("O") == True or b.isGameWon("X") == True:
                print("You won")
                break
            if b.nospacesleft() == True:
                print("Computer wins")
                break

            print("Do you want to save the game? Type: Yes")
            decision = input()
            if decision == "Yes":
                b.writetofile("Order_And_Chaos_File")
                break

        print("\n")
        print("\n")

    def OldGame(self):
        b = Board()

        b.readfromfile("Order_And_Chaos_File")

        ai = AI()

        print(b)

        while b.isGameWon("O") == False and b.isGameWon("X") == False:
            ok = False
            while ok == False:
                line = input("Choose your line: ")
                column = input("Choose your column: ")
                piece = input("Choose your piece: X or O: ")
                if self.checkinteger(line) == "fals":
                    print("Line is not an integer!")
                else:
                    if self.checkinteger(column) == "fals":
                        print("Column is not an integer!")
                    else:
                        line = self.checkinteger(line)
                        column = self.checkinteger(column)
                        if 0 <= line <= 5 and 0 <= column <= 5:
                            if b.data[line][column] == " ":
                                if piece == "X" or piece == "O":
                                    b.move(piece, line, column)
                                    ok = True
                                else:
                                    print("The chosen piece is not available!")
                            else:
                                print("The chosen position is not available!")
                        else:
                            print("Give adequate coordinates! (between 0 and 5)")

            print(b)

            if b.isGameWon("O") == True or b.isGameWon("X") == True:
                print("You won")
                break
            if b.nospacesleft() == True:
                print("Computer wins")
                break

            ai.move("X", "O", b)
            print(b)

            if b.isGameWon("O") == True or b.isGameWon("X") == True:
                print("You won")
                break
            if b.nospacesleft() == True:
                print("Computer wins")
                break

            print("Do you want to save the game? Type: Yes")
            decision = input()
            if decision == "Yes":
                b.writetofile("Order_And_Chaos_File")
                break

        print("\n")
        print("\n")

    def MainMenu(self):
        commandDict = {'1': self.NewGame,
                       '2': self.OldGame}
        while True:
            UI.PrintMenu()
            command = input("Please choose: ")
            while not UI.ValidCommands(command):
                command = input("Please type a valid command!")
            if command == '0':
                break
            commandDict[command]()

ui = UI()
ui.MainMenu()
