FIRST_ELEMENT = 0
SECOND_ELEMENT = 1
THIRD_ELEMENT = 2

class Ui:
    def __init__(self, service):
        self.__service = service

    def run(self):
        while True:
            command = input("> ").strip()
            command_parts = command.split()

            if not command_parts:
                print("Invalid command")

            if command_parts[FIRST_ELEMENT] == 'exit':
                break

            elif command_parts[FIRST_ELEMENT] == 'add':
                try:
                    driver_id, distance = command_parts[SECOND_ELEMENT].split(',')
                    distance = int(distance)
                    self.__service.add_order(driver_id, distance)
                except ValueError:
                    print("Invalid command and distance must be a number")

            elif command_parts[FIRST_ELEMENT] == 'display':
                drivers = self.__service.display_all_drivers()
                orders = self.__service.display_all_orders()

                for driver in drivers:
                    print(driver)

                for order in orders:
                    print(order)

            elif command_parts[FIRST_ELEMENT] == 'income':
                try:
                    driver_id = command_parts[SECOND_ELEMENT]
                    print(self.__service.display_driver_income(driver_id))
                except ValueError:
                    print("Invalid command. Try again.")
            else:
                print("Invalid command. Try again.")


