from jproperties import Properties

class RepositoryLoader:
    def __init__(self):
        self.__repository_class = ""
        self.__repository_file = ""
        self.__repository_load()

    def get_repository_class(self):
        return self.__repository_class

    def get_repository_file(self):
        return self.__repository_file

    def __repository_load(self):
        repository_manager = Properties()
        settings_file = open("settings.properties", "rb")
        repository_manager.load(settings_file)
        settings_file.close()

        try:
            self.__repository_class = repository_manager.get("Active_repository").data
            self.__repository_file = repository_manager.get(self.__repository_class).data
        except:
            self.__repository_class = ("MemoryRepository")
