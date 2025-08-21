import random
import datetime
import os

class Room:
    def __init__(self, number, type_):
        self.number = number
        self.type_ = type_

class Reservation:
    def __init__(self, room_number, guest_name, guests, arrival, departure):
        self.room_number = room_number
        self.guest_name = guest_name
        self.guests = guests
        self.arrival = arrival
        self.departure = departure

class Repository:
    def __init__(self, room_file, reservation_file):
        self.room_file = room_file
        self.reservation_file = reservation_file
        self.rooms = self.load_rooms()
        self.reservations = self.load_reservations()

    def load_rooms(self):
        rooms = {}
        with open(self.room_file, 'r') as file:
            for line in file:
                number, type_ = line.strip().split(', ')
                rooms[number] = Room(number, type_)
        return rooms

    def load_reservations(self):
        reservations = []
        if os.path.exists(self.reservation_file):
            with open(self.reservation_file, 'r') as file:
                for line in file:
                    room_number, guest_name, guests, arrival, departure = line.strip().split(', ')
                    reservations.append(Reservation(room_number, guest_name, int(guests), arrival, departure))
        return reservations

    def save_reservations(self):
        with open(self.reservation_file, 'w') as file:
            for res in self.reservations:
                file.write(f"{res.room_number}, {res.guest_name}, {res.guests}, {res.arrival}, {res.departure}\n")

    def add_reservation(self, reservation):
        self.reservations.append(reservation)
        self.save_reservations()

    def delete_reservation(self, reservation_number):
        for res in self.reservations:
            if res.room_number == reservation_number:
                self.reservations.remove(res)
                self.save_reservations()
                return True
        return False

class Controller:
    def __init__(self, repo):
        self.repo = repo

    def create_reservation(self, room_number, guest_name, guests, arrival, departure):
        if not guest_name or guests <= 0:
            return "Invalid reservation details."
        reservation = Reservation(room_number, guest_name, guests, arrival, departure)
        self.repo.add_reservation(reservation)
        return "Reservation created successfully."

    def delete_reservation(self, room_number):
        if self.repo.delete_reservation(room_number):
            return "Reservation deleted successfully."
        return "Reservation not found."

    def display_reservations(self, month):
        print(f"Reservations for month {month}:")
        for res in self.repo.reservations:
            if res.arrival.startswith(f"{month}."):
                print(f"Room {res.room_number}: {res.guest_name}, {res.guests} guests, {res.arrival} - {res.departure}")

class UI:
    def __init__(self, controller):
        self.controller = controller

    def menu(self):
        while True:
            print("1. Create reservation\n2. Delete reservation\n3. Show reservations.txt\n4. Exit")
            choice = input("Choose an option: ")
            if choice == "1":
                room_number = input("Room number: ")
                guest_name = input("Guest name: ")
                guests = int(input("Number of guests: "))
                arrival = input("Arrival date (mm.dd): ")
                departure = input("Departure date (mm.dd): ")
                print(self.controller.create_reservation(room_number, guest_name, guests, arrival, departure))
            elif choice == "2":
                room_number = input("Room number: ")
                print(self.controller.delete_reservation(room_number))
            elif choice == "3":
                month = input("Enter month (mm): ")
                self.controller.display_reservations(month)
            elif choice == "4":
                break

if __name__ == "__main__":
    path_file = os.path.dirname(os.path.abspath(__file__))
    room_file = os.path.join(path_file, "rooms.txt")
    reservation_file = os.path.join(path_file, "reservations.txt")
    repo = Repository(room_file, reservation_file)
    controller = Controller(repo)
    ui = UI(controller)
    ui.menu()
