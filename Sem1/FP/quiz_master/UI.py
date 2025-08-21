import random
class Question:

    def __init__(self, id, text, answer1, answer2, answer3, correct_answer, difficulty):
        self.id = id
        self.text = text
        self.answer1 = answer1
        self.answer2 = answer2
        self.answer3 = answer3
        self.correct_answer = correct_answer
        self.difficulty = difficulty

    def __str__(self):
        string = str(self.id) + ";" + str(self.text) + ";" + str(self.answer1)
        string = string + ";" + str(self.answer2) + ";" + str(self.answer3) + ";" + str(self.correct_answer)
        string = string + ";" + str(self.difficulty)
        return string

    def getid(self):
        return self.id

    def gettext(self):
        return self.text

    def getanswers(self):
        return self.answer1, self.answer2, self.answer3

    def getcorrectanswer(self):
        return self.correct_answer

    def getdifficulty(self):
        return self.difficulty

class QuestionRepository:

    def __init__(self):
        self.data = []

    def add_question(self, question):
        self.data.append(question)



class QuestionController:

    def __init__(self, repo):
        self.repo = repo

    def get_questions_of_difficulty(self, difficulty, n):
        list_of_questions = []
        list_of_questions_of_difficulty = []
        for i in self.repo.data:
            if i.getdifficulty() == difficulty:
                list_of_questions_of_difficulty.append(i)
        i = 0
        while i < n/2:
            a = random.choice(list_of_questions_of_difficulty)
            if a not in list_of_questions:
                list_of_questions.append(a)
                i += 1

        while i < n:
            a = random.choice(self.repo.data)
            if a not in list_of_questions:
                list_of_questions.append(a)
                i += 1

        return list_of_questions

    def count_questions(self, difficulty):
        n = 0
        for i in self.repo.data:
            if i.getdifficulty() == difficulty:
                n += 1
        return n

    def writetofile(self, fname, questionlist):

        with open(fname, 'w') as f:
            for i in range(len(questionlist)):
                f.write(str(questionlist[i]))
                f.write("\n")
        f.close()

    def readquizfromfile(self, fname):

        quiz = []
        with open(fname, 'r') as f:
            lines = f.readlines()
            for i in lines:
                i = i.strip("\n")
                i = i.split(";")
                id = i[0]
                text = i[1]
                answer1 = i[2]
                answer2 = i[3]
                answer3 = i[4]
                correct_answer = i[5]
                difficulty = i[6]
                q = Question(id, text, answer1, answer2, answer3, correct_answer, difficulty)
                quiz.append(q)
        f.close()
        return quiz

class UI:

    def __init__(self, controller):
        self.controller = controller

    def read_command(self):
        cmd = input()
        cmd = cmd.split(" ", 1)
        if cmd[0] == "add":
            self.add_question(cmd[1])
        elif cmd[0] == "create":
            self.create_question(cmd[1])
        elif cmd[0] == "start":
            self.start_quiz(cmd[1])
        elif cmd[0] == "exit":
            return "break"
        elif cmd[0] == "display":
            self.display()
        else:
            print("There is no such command!")
            return False

    def add_question(self, parameters):
        params = parameters.split(";")
        if len(params) != 7:
            print("The format is wrong!")
            return False
        else:
            id = params[0]
            text = params[1]
            answer1 = params[2]
            answer2 = params[3]
            answer3 = params[4]
            correct_answer = params[5]
            difficulty = params[6]
            q = Question(id, text, answer1, answer2, answer3, correct_answer, difficulty)
            self.controller.repo.add_question(q)
            print("Question added")
            return True

    def create_question(self, parameters):
        params = parameters.split(" ")
        if len(params) != 3:
            print("The format is wrong!")
            return False
        else:
            params[1] = int(params[1])
            if params[1] > len(self.controller.repo.data):
                print("The number you provided is larger than the number of questions available!")
                return False
            else:
                if int(params[1])/2 > self.controller.count_questions(params[0]):
                    print("The number of questions with this level of difficulty is not enough!")
                else:
                    questions = self.controller.get_questions_of_difficulty(params[0], params[1])
                    self.controller.writetofile(params[2], questions)
                    print("Quiz created")
                    return True

    def start_quiz(self, parameters):
        questions = self.controller.readquizfromfile(parameters)
        questions_to_delete = []
        score = 0
        for q in questions:
            print(q.getdifficulty())
            if q.getdifficulty() == "easy":
                print(q.gettext())
                answers = q.getanswers()
                for a in range(len(answers)):
                    print(str(a+1) + ")" + str(answers[a]))
                answer = input()
                if answer == q.getcorrectanswer():
                    score += 1
                questions_to_delete.append(q)
        for q in questions_to_delete:
            questions.remove(q)
        questions_to_delete = []
        for q in questions:
            if q.getdifficulty() == "medium":
                print(q.gettext())
                answers = q.getanswers()
                for a in range(len(answers)):
                    print(str(a+1) + ")" + str(answers[a]))
                answer = input()
                if answer == q.getcorrectanswer():
                    score += 2
                questions_to_delete.append(q)
        for q in questions_to_delete:
            questions.remove(q)
        for q in questions:
            if q.getdifficulty() == "hard":
                print(q.gettext())
                answers = q.getanswers()
                for a in range(len(answers)):
                    print(str(a+1) + ")" + str(answers[a]))
                answer = input()
                if answer == q.getcorrectanswer():
                    score += 3
                questions_to_delete.append(q)
        print(score)
        return True

    def display(self):
        for i in self.controller.repo.data:
            print(i)
        return True

    def Menu(self):

        rsp = self.read_command()
        while rsp != "break":
            rsp = self.read_command()

Repo = QuestionRepository()
q1 = Question("1", "Which number is the biggest?", "1", "4", "3", "4", "easy")
Repo.add_question(q1)
q2 = Question("2", "Which number is the smallest?", "-3", "3", "0", "-3", "easy")
Repo.add_question(q2)
q3 = Question("3", "Which number is prime?", "2", "32", "9", "2", "easy")
Repo.add_question(q3)
q4 = Question("4", "Which country has the largest GDP?", "Brazil", "China", "UK", "China", "medium")
Repo.add_question(q4)
q5 = Question("5", "Which is not a fish?", "carp", "orca", "eel", "orca", "medium")
Repo.add_question(q5)
q6 = Question("6", "Name the first satellite:", "Apollo", "Sputnik", "Zaria", "Sputnik", "medium")
Repo.add_question(q6)
q7 = Question("7", "Which Apollo mission did not make it to the Moon?", "11", "13", "17", "13", "hard")
Repo.add_question(q7)
q8 = Question("8", "A mole can be a:", "animal", "quantity", "both", "both", "hard")
Repo.add_question(q8)
q9 = Question("9", "Name El Cid's horse:", "Babieca", "Abu", "Santiago", "Babieca", "hard")
Repo.add_question(q9)
q10 = Question("10", "The Western Roman Empire fell in:", "654", "546", "476", "476", "hard")
Repo.add_question(q10)
Ctrl = QuestionController(Repo)
ui = UI(Ctrl)
ui.Menu()