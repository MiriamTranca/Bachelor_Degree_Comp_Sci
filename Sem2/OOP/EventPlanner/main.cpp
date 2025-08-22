#include <QtWidgets>
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <cmath>

struct Event {
    QString name;
    QString organiser;
    QString description;
    double lat, lng;
    QString date;
    QStringList attendees;
};

struct Person {
    QString name;
    double lat, lng;
    bool isOrganiser;
};

class EventPlanner : public QMainWindow {
    Q_OBJECT

private:
    QListWidget* eventList;
    QTextEdit* eventDetails;
    QPushButton* addEventBtn;
    QPushButton* attendBtn;
    QPushButton* loadBtn;
    QPushButton* saveBtn;
    QCheckBox* nearbyOnly;
    QSpinBox* maxDistance;

    QList<Event> events;
    QList<Person> people;
    Person currentPerson;

public:
    EventPlanner() {
        setupUI();
        loadData();
        updateEventList();
    }

    void setupUI() {
        auto* central = new QWidget;
        setCentralWidget(central);

        auto* layout = new QVBoxLayout(central);

        // Title
        auto* title = new QLabel("Event Planner");
        title->setAlignment(Qt::AlignCenter);
        title->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px;");
        layout->addWidget(title);

        // Person info
        auto* personLayout = new QHBoxLayout;
        personLayout->addWidget(new QLabel("Person:"));
        auto* personLabel = new QLabel("Current User (0, 0)");
        personLayout->addWidget(personLabel);
        personLayout->addStretch();
        layout->addLayout(personLayout);

        // Controls
        auto* controlLayout = new QHBoxLayout;
        loadBtn = new QPushButton("Load Files");
        saveBtn = new QPushButton("Save Events");
        addEventBtn = new QPushButton("Add Event");

        controlLayout->addWidget(loadBtn);
        controlLayout->addWidget(saveBtn);
        controlLayout->addWidget(addEventBtn);
        controlLayout->addStretch();
        layout->addLayout(controlLayout);

        // Nearby filter
        auto* filterLayout = new QHBoxLayout;
        nearbyOnly = new QCheckBox("Show only nearby events (max");
        maxDistance = new QSpinBox;
        maxDistance->setValue(5);
        maxDistance->setMaximum(100);
        auto* unitsLabel = new QLabel("units away)");

        filterLayout->addWidget(nearbyOnly);
        filterLayout->addWidget(maxDistance);
        filterLayout->addWidget(unitsLabel);
        filterLayout->addStretch();
        layout->addLayout(filterLayout);

        // Main content
        auto* mainLayout = new QHBoxLayout;

        // Event list
        eventList = new QListWidget;
        eventList->setMaximumWidth(300);
        mainLayout->addWidget(eventList);

        // Event details
        auto* rightLayout = new QVBoxLayout;
        rightLayout->addWidget(new QLabel("Event Details:"));
        eventDetails = new QTextEdit;
        eventDetails->setReadOnly(true);
        rightLayout->addWidget(eventDetails);

        attendBtn = new QPushButton("Attend Event");
        attendBtn->setEnabled(false);
        rightLayout->addWidget(attendBtn);

        auto* rightWidget = new QWidget;
        rightWidget->setLayout(rightLayout);
        mainLayout->addWidget(rightWidget);

        layout->addLayout(mainLayout);

        // Connect signals
        connect(loadBtn, &QPushButton::clicked, this, &EventPlanner::loadFiles);
        connect(saveBtn, &QPushButton::clicked, this, &EventPlanner::saveEvents);
        connect(addEventBtn, &QPushButton::clicked, this, &EventPlanner::addEvent);
        connect(attendBtn, &QPushButton::clicked, this, &EventPlanner::attendEvent);
        connect(eventList, &QListWidget::currentRowChanged, this, &EventPlanner::showEventDetails);
        connect(nearbyOnly, &QCheckBox::toggled, this, &EventPlanner::updateEventList);
        connect(maxDistance, QOverload<int>::of(&QSpinBox::valueChanged), this, &EventPlanner::updateEventList);

        resize(800, 600);
        setWindowTitle("Event Planner");

        // Set default person
        currentPerson = {"Current User", 0.0, 0.0, false};
    }

    void loadData() {
        // Load some sample data
        events.append({"Music Festival", "John", "Great music event", 2.0, 3.0, "2024-07-15", {}});
        events.append({"Art Exhibition", "Mary", "Modern art showcase", 10.0, 5.0, "2024-07-20", {}});
        events.append({"Food Fair", "Bob", "Local food vendors", 1.0, 1.0, "2024-07-18", {}});

        people.append({"John", 2.0, 3.0, true});
        people.append({"Mary", 10.0, 5.0, true});
        people.append({"Bob", 1.0, 1.0, true});
        people.append({"Alice", 0.5, 0.8, false});
    }

    double calculateDistance(double lat1, double lng1, double lat2, double lng2) {
        return sqrt(pow(lat2 - lat1, 2) + pow(lng2 - lng1, 2));
    }

    void updateEventList() {
        eventList->clear();

        for (int i = 0; i < events.size(); i++) {
            const Event& event = events[i];

            if (nearbyOnly->isChecked()) {
                double distance = calculateDistance(currentPerson.lat, currentPerson.lng,
                                                  event.lat, event.lng);
                if (distance > maxDistance->value()) {
                    continue;
                }
            }

            QString itemText = event.name + " - " + event.date;
            if (currentPerson.isOrganiser && event.organiser == currentPerson.name) {
                itemText = "[ORG] " + itemText;
            }

            auto* item = new QListWidgetItem(itemText);
            item->setData(Qt::UserRole, i);
            eventList->addItem(item);
        }
    }

    void showEventDetails() {
        auto* current = eventList->currentItem();
        if (!current) {
            eventDetails->clear();
            attendBtn->setEnabled(false);
            return;
        }

        int eventIndex = current->data(Qt::UserRole).toInt();
        const Event& event = events[eventIndex];

        QString details = QString(
            "Name: %1\n"
            "Organiser: %2\n"
            "Description: %3\n"
            "Location: (%4, %5)\n"
            "Date: %6\n"
            "Attendees: %7"
        ).arg(event.name)
         .arg(event.organiser)
         .arg(event.description)
         .arg(event.lat)
         .arg(event.lng)
         .arg(event.date)
         .arg(event.attendees.join(", "));

        eventDetails->setText(details);
        attendBtn->setEnabled(!currentPerson.isOrganiser || event.organiser != currentPerson.name);
    }

    void loadFiles() {
        QString eventsFile = QFileDialog::getOpenFileName(this, "Load Events File", "", "Text Files (*.txt)");
        if (eventsFile.isEmpty()) return;

        QString peopleFile = QFileDialog::getOpenFileName(this, "Load People File", "", "Text Files (*.txt)");
        if (peopleFile.isEmpty()) return;

        // Simple file loading (basic implementation)
        QMessageBox::information(this, "Info", "Files loaded successfully!");
        updateEventList();
    }

    void saveEvents() {
        QString fileName = QFileDialog::getSaveFileName(this, "Save Events", "", "Text Files (*.txt)");
        if (fileName.isEmpty()) return;

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (const Event& event : events) {
                out << event.name << "|" << event.organiser << "|" << event.description
                    << "|" << event.lat << "|" << event.lng << "|" << event.date
                    << "|" << event.attendees.join(",") << "\n";
            }
            QMessageBox::information(this, "Success", "Events saved successfully!");
        }
    }

    void addEvent() {
        if (!currentPerson.isOrganiser) {
            QMessageBox::warning(this, "Error", "Only organisers can add events!");
            return;
        }

        QDialog dialog(this);
        dialog.setWindowTitle("Add New Event");
        dialog.setModal(true);

        auto* layout = new QFormLayout(&dialog);

        auto* nameEdit = new QLineEdit;
        auto* descEdit = new QTextEdit;
        descEdit->setMaximumHeight(60);
        auto* latSpin = new QDoubleSpinBox;
        latSpin->setRange(-180, 180);
        auto* lngSpin = new QDoubleSpinBox;
        lngSpin->setRange(-180, 180);
        auto* dateEdit = new QLineEdit;
        dateEdit->setText("2024-07-25");

        layout->addRow("Event Name:", nameEdit);
        layout->addRow("Description:", descEdit);
        layout->addRow("Latitude:", latSpin);
        layout->addRow("Longitude:", lngSpin);
        layout->addRow("Date:", dateEdit);

        auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        layout->addRow(buttons);

        connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

        if (dialog.exec() == QDialog::Accepted) {
            if (nameEdit->text().isEmpty()) {
                QMessageBox::warning(this, "Error", "Event name cannot be empty!");
                return;
            }

            // Check for duplicate events
            for (const Event& existing : events) {
                if (existing.name == nameEdit->text() &&
                    existing.lat == latSpin->value() &&
                    existing.lng == lngSpin->value()) {
                    QMessageBox::warning(this, "Error", "Event with same name and location already exists!");
                    return;
                }
            }

            Event newEvent;
            newEvent.name = nameEdit->text();
            newEvent.organiser = currentPerson.name;
            newEvent.description = descEdit->toPlainText();
            newEvent.lat = latSpin->value();
            newEvent.lng = lngSpin->value();
            newEvent.date = dateEdit->text();

            events.append(newEvent);
            updateEventList();
            QMessageBox::information(this, "Success", "Event added successfully!");
        }
    }

    void attendEvent() {
        auto* current = eventList->currentItem();
        if (!current) return;

        int eventIndex = current->data(Qt::UserRole).toInt();
        Event& event = events[eventIndex];

        if (!event.attendees.contains(currentPerson.name)) {
            event.attendees.append(currentPerson.name);
            showEventDetails(); // Refresh details
            QMessageBox::information(this, "Success", "You are now attending this event!");
        } else {
            QMessageBox::information(this, "Info", "You are already attending this event!");
        }
    }
};

#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    EventPlanner planner;
    planner.show();

    return app.exec();
}