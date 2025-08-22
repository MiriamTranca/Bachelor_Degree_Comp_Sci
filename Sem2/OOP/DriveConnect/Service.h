
#ifndef SERVICE_H
#define SERVICE_H
#include <qlistwidget.h>

#include "Repository.h"
using namespace std;

class Service {
private:
    Repository repo;
public:
    Service(){};
    vector<Driver> getAllDrivers();
    vector<Report> getAllReports();
    vector<Report> getAllReportsForDriver(const string& nameDr);
    vector<string> chatMessages;
    void addChatMessage(const string& message) {
        chatMessages.push_back(message);
    }
    vector<string> getChatMessages() {
        return chatMessages;
    }
    void addReport(int lat, int lon, const string& desc, const string& nameDr);
    void validateReport(QListWidgetItem* item, const string& currentDriver);
};



#endif //SERVICE_H
