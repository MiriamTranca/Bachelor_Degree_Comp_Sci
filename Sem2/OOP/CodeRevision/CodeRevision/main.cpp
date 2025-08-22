#include <QtWidgets>
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QInputDialog>
#include <QTextEdit>
#include <QGroupBox>
#include <QGridLayout>
#include <QPainter>
#include <QDialog>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <iostream>

// Domain Layer
enum class FileStatus {
    NOT_REVISED,
    REVISED
};

class Programmer {
public:
    std::string name;
    int revisedFiles;
    int totalFiles;

    Programmer(const std::string& n, int revised, int total)
        : name(n), revisedFiles(revised), totalFiles(total) {}

    bool hasReachedGoal() const {
        return revisedFiles >= totalFiles;
    }

    int filesToRevise() const {
        return totalFiles - revisedFiles;
    }
};

class SourceFile {
public:
    std::string name;
    FileStatus status;
    std::string creator;
    std::string reviewer;

    SourceFile(const std::string& n, FileStatus s, const std::string& c, const std::string& r = "")
        : name(n), status(s), creator(c), reviewer(r) {}

    bool isRevised() const {
        return status == FileStatus::REVISED;
    }

    bool canBeRevisedBy(const std::string& programmerName) const {
        return status == FileStatus::NOT_REVISED && creator != programmerName;
    }
};

// Repository Layer
class DataRepository {
private:
    const std::string TEAM_FILE = "team.txt";
    const std::string SOURCE_FILE = "source_files.txt";

public:
    std::vector<Programmer> loadTeamData() {
        std::vector<Programmer> programmers;
        std::ifstream file(TEAM_FILE);

        if (!file.is_open()) {
            // Create default data
            programmers = {
                Programmer("Alice", 2, 5),
                Programmer("Bob", 0, 3),
                Programmer("Charlie", 4, 4),
                Programmer("Diana", 1, 6)
            };
            saveTeamData(programmers);
            return programmers;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name, revisedStr, totalStr;

            if (std::getline(iss, name, ',') &&
                std::getline(iss, revisedStr, ',') &&
                std::getline(iss, totalStr)) {

                try {
                    int revised = std::stoi(revisedStr);
                    int total = std::stoi(totalStr);
                    programmers.emplace_back(name, revised, total);
                } catch (const std::exception& e) {
                    std::cerr << "Error parsing line: " << line << std::endl;
                }
            }
        }

        return programmers;
    }

    void saveTeamData(const std::vector<Programmer>& programmers) {
        std::ofstream file(TEAM_FILE);
        for (const auto& prog : programmers) {
            file << prog.name << "," << prog.revisedFiles << "," << prog.totalFiles << std::endl;
        }
    }

    std::vector<SourceFile> loadSourceFiles() {
        std::vector<SourceFile> files;
        std::ifstream file(SOURCE_FILE);

        if (!file.is_open()) {
            // Create default data
            files = {
                SourceFile("main.cpp", FileStatus::NOT_REVISED, "Alice"),
                SourceFile("utils.cpp", FileStatus::REVISED, "Bob", "Alice"),
                SourceFile("config.cpp", FileStatus::NOT_REVISED, "Charlie"),
                SourceFile("tests.cpp", FileStatus::REVISED, "Diana", "Charlie"),
                SourceFile("parser.cpp", FileStatus::NOT_REVISED, "Alice"),
                SourceFile("network.cpp", FileStatus::NOT_REVISED, "Bob")
            };
            saveSourceFiles(files);
            return files;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name, statusStr, creator, reviewer;

            if (std::getline(iss, name, ',') &&
                std::getline(iss, statusStr, ',') &&
                std::getline(iss, creator, ',')) {

                std::getline(iss, reviewer);

                FileStatus status = (statusStr == "revised") ? FileStatus::REVISED : FileStatus::NOT_REVISED;
                files.emplace_back(name, status, creator, reviewer);
            }
        }

        return files;
    }

    void saveSourceFiles(const std::vector<SourceFile>& files) {
        std::ofstream file(SOURCE_FILE);
        for (const auto& f : files) {
            std::string statusStr = (f.status == FileStatus::REVISED) ? "revised" : "not_revised";
            file << f.name << "," << statusStr << "," << f.creator << "," << f.reviewer << std::endl;
        }
    }
};

// Service Layer
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};

class CodeRevisionService {
private:
    std::unique_ptr<DataRepository> repository;
    std::vector<Observer*> observers;

public:
    std::vector<Programmer> programmers;
    std::vector<SourceFile> sourceFiles;

    CodeRevisionService() : repository(std::make_unique<DataRepository>()) {
        loadData();
    }

    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void notifyObservers() {
        for (auto observer : observers) {
            observer->update();
        }
    }

    void loadData() {
        programmers = repository->loadTeamData();
        sourceFiles = repository->loadSourceFiles();
    }

    void saveData() {
        repository->saveTeamData(programmers);
        repository->saveSourceFiles(sourceFiles);
    }

    bool addFile(const std::string& fileName, const std::string& creatorName) {
        // Check if file already exists
        for (const auto& file : sourceFiles) {
            if (file.name == fileName) {
                return false; // File already exists
            }
        }

        // Check if creator exists
        bool creatorExists = false;
        for (const auto& prog : programmers) {
            if (prog.name == creatorName) {
                creatorExists = true;
                break;
            }
        }

        if (!creatorExists || fileName.empty()) {
            return false;
        }

        sourceFiles.emplace_back(fileName, FileStatus::NOT_REVISED, creatorName);
        saveData();
        notifyObservers();
        return true;
    }

    bool reviseFile(const std::string& fileName, const std::string& reviewerName) {
        // Find the file
        auto fileIt = std::find_if(sourceFiles.begin(), sourceFiles.end(),
            [&fileName](const SourceFile& f) { return f.name == fileName; });

        if (fileIt == sourceFiles.end()) {
            return false; // File not found
        }

        // Check if file can be revised
        if (!fileIt->canBeRevisedBy(reviewerName)) {
            return false;
        }

        // Find the reviewer
        auto progIt = std::find_if(programmers.begin(), programmers.end(),
            [&reviewerName](const Programmer& p) { return p.name == reviewerName; });

        if (progIt == programmers.end()) {
            return false; // Reviewer not found
        }

        // Perform revision
        fileIt->status = FileStatus::REVISED;
        fileIt->reviewer = reviewerName;
        progIt->revisedFiles++;

        saveData();
        notifyObservers();
        return true;
    }

    std::vector<std::string> getProgrammerNames() const {
        std::vector<std::string> names;
        for (const auto& prog : programmers) {
            names.push_back(prog.name);
        }
        return names;
    }

    const Programmer* getProgrammer(const std::string& name) const {
        auto it = std::find_if(programmers.begin(), programmers.end(),
            [&name](const Programmer& p) { return p.name == name; });
        return (it != programmers.end()) ? &(*it) : nullptr;
    }
};

// UI Layer - Statistics Window
class StatisticsWindow : public QDialog {
    Q_OBJECT

private:
    CodeRevisionService* service;
    QVBoxLayout* layout;

    void paintEvent(QPaintEvent* event) override {
        QDialog::paintEvent(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        int startY = 50;
        int circleSize = 30;
        int spacing = 50;

        for (size_t i = 0; i < service->programmers.size(); ++i) {
            const auto& prog = service->programmers[i];

            int x = 50 + (i % 3) * 150;
            int y = startY + (i / 3) * 80;

            // Draw circle
            QColor color = prog.hasReachedGoal() ? Qt::blue : Qt::gray;
            painter.setBrush(QBrush(color));
            painter.setPen(QPen(Qt::black, 2));

            // Calculate circle radius based on files revised
            int radius = std::max(15, (prog.revisedFiles * circleSize) / std::max(1, prog.totalFiles));
            painter.drawEllipse(x - radius, y - radius, radius * 2, radius * 2);

            // Draw name
            painter.setPen(Qt::black);
            painter.drawText(x - 30, y + radius + 15, prog.name.c_str());

            // Draw stats
            QString stats = QString("%1/%2").arg(prog.revisedFiles).arg(prog.totalFiles);
            painter.drawText(x - 20, y + radius + 30, stats);
        }
    }

public:
    StatisticsWindow(CodeRevisionService* svc, QWidget* parent = nullptr)
        : QDialog(parent), service(svc) {
        setWindowTitle("Programmer Statistics");
        setFixedSize(500, 400);

        layout = new QVBoxLayout(this);

        QLabel* title = new QLabel("Programmer Statistics");
        title->setAlignment(Qt::AlignCenter);
        title->setStyleSheet("font-size: 16px; font-weight: bold; margin: 10px;");
        layout->addWidget(title);

        layout->addStretch();

        QPushButton* closeBtn = new QPushButton("Close");
        connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
        layout->addWidget(closeBtn);
    }
};

// UI Layer - Programmer Window
class ProgrammerWindow : public QMainWindow, public Observer {
    Q_OBJECT

private:
    CodeRevisionService* service;
    std::string programmerName;
    QListWidget* filesList;
    QLineEdit* newFileInput;
    QPushButton* addFileBtn;
    QPushButton* reviseBtn;
    QLabel* statusLabel;

    void setupUI() {
        setWindowTitle(QString("Code Revision - %1").arg(programmerName.c_str()));
        setMinimumSize(600, 400);

        QWidget* centralWidget = new QWidget;
        setCentralWidget(centralWidget);

        QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

        // Status label
        statusLabel = new QLabel;
        statusLabel->setStyleSheet("font-weight: bold; padding: 10px; background-color: #f0f0f0;");
        mainLayout->addWidget(statusLabel);

        // Files list
        QGroupBox* filesGroup = new QGroupBox("Source Files");
        QVBoxLayout* filesLayout = new QVBoxLayout(filesGroup);

        filesList = new QListWidget;
        filesList->setSelectionMode(QAbstractItemView::SingleSelection);
        filesLayout->addWidget(filesList);

        mainLayout->addWidget(filesGroup);

        // Add file section
        QGroupBox* addGroup = new QGroupBox("Add New File");
        QHBoxLayout* addLayout = new QHBoxLayout(addGroup);

        newFileInput = new QLineEdit;
        newFileInput->setPlaceholderText("Enter file name...");
        addLayout->addWidget(newFileInput);

        addFileBtn = new QPushButton("Add");
        connect(addFileBtn, &QPushButton::clicked, this, &ProgrammerWindow::addFile);
        addLayout->addWidget(addFileBtn);

        mainLayout->addWidget(addGroup);

        // Revise button
        reviseBtn = new QPushButton("Revise Selected File");
        reviseBtn->setEnabled(false);
        connect(reviseBtn, &QPushButton::clicked, this, &ProgrammerWindow::reviseFile);
        connect(filesList, &QListWidget::itemSelectionChanged, this, &ProgrammerWindow::onSelectionChanged);
        mainLayout->addWidget(reviseBtn);

        // Enter key support
        connect(newFileInput, &QLineEdit::returnPressed, this, &ProgrammerWindow::addFile);

        updateDisplay();
    }

private slots:
    void addFile() {
        QString fileName = newFileInput->text().trimmed();
        if (fileName.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Please enter a file name.");
            return;
        }

        if (service->addFile(fileName.toStdString(), programmerName)) {
            newFileInput->clear();
            QMessageBox::information(this, "Success", "File added successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Failed to add file. File may already exist or name is invalid.");
        }
    }

    void reviseFile() {
        QListWidgetItem* item = filesList->currentItem();
        if (!item) return;

        QString fileName = item->text().split(" - ")[0];

        if (service->reviseFile(fileName.toStdString(), programmerName)) {
            QMessageBox::information(this, "Success", "File revised successfully!");
        } else {
            QMessageBox::warning(this, "Error", "Cannot revise this file. You cannot revise your own files or files already revised.");
        }
    }

    void onSelectionChanged() {
        QListWidgetItem* item = filesList->currentItem();
        if (!item) {
            reviseBtn->setEnabled(false);
            return;
        }

        QString fileName = item->text().split(" - ")[0];

        // Check if file can be revised
        bool canRevise = false;
        for (const auto& file : service->sourceFiles) {
            if (file.name == fileName.toStdString()) {
                canRevise = file.canBeRevisedBy(programmerName);
                break;
            }
        }

        reviseBtn->setEnabled(canRevise);
    }

public:
    ProgrammerWindow(CodeRevisionService* svc, const std::string& name, QWidget* parent = nullptr)
        : QMainWindow(parent), service(svc), programmerName(name) {
        service->addObserver(this);
        setupUI();
    }

    ~ProgrammerWindow() {
        // Note: In a real application, you'd want to remove observer properly
    }

    void update() override {
        updateDisplay();
    }

    void updateDisplay() {
        filesList->clear();

        // Update status
        const Programmer* prog = service->getProgrammer(programmerName);
        if (prog) {
            QString status = QString("Files revised: %1/%2").arg(prog->revisedFiles).arg(prog->totalFiles);
            if (prog->hasReachedGoal()) {
                status += " - GOAL REACHED!";
                statusLabel->setStyleSheet("font-weight: bold; padding: 10px; background-color: #90EE90;");
            } else {
                statusLabel->setStyleSheet("font-weight: bold; padding: 10px; background-color: #f0f0f0;");
            }
            statusLabel->setText(status);
        }

        // Update files list
        for (const auto& file : service->sourceFiles) {
            QString itemText = QString("%1 - %2 - Creator: %3")
                .arg(file.name.c_str())
                .arg(file.isRevised() ? "REVISED" : "NOT REVISED")
                .arg(file.creator.c_str());

            if (file.isRevised() && !file.reviewer.empty()) {
                itemText += QString(" - Reviewer: %1").arg(file.reviewer.c_str());
            }

            QListWidgetItem* item = new QListWidgetItem(itemText);

            // Style the item
            if (file.isRevised()) {
                item->setBackground(QBrush(QColor(144, 238, 144))); // Light green
            } else {
                item->setFont(QFont("", -1, QFont::Bold));
            }

            filesList->addItem(item);
        }

        onSelectionChanged();
    }
};

// UI Layer - Main Window
class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    std::unique_ptr<CodeRevisionService> service;
    std::vector<std::unique_ptr<ProgrammerWindow>> programmerWindows;
    QListWidget* programmersList;
    QPushButton* openWindowBtn;
    QPushButton* statisticsBtn;

    void setupUI() {
        setWindowTitle("Code Revision System - Main");
        setMinimumSize(400, 300);

        QWidget* centralWidget = new QWidget;
        setCentralWidget(centralWidget);

        QVBoxLayout* layout = new QVBoxLayout(centralWidget);

        QLabel* title = new QLabel("Code Revision Management System");
        title->setAlignment(Qt::AlignCenter);
        title->setStyleSheet("font-size: 18px; font-weight: bold; margin: 20px;");
        layout->addWidget(title);

        QGroupBox* programmersGroup = new QGroupBox("Development Team");
        QVBoxLayout* programmersLayout = new QVBoxLayout(programmersGroup);

        programmersList = new QListWidget;
        programmersList->setSelectionMode(QAbstractItemView::SingleSelection);
        programmersLayout->addWidget(programmersList);

        layout->addWidget(programmersGroup);

        QHBoxLayout* buttonsLayout = new QHBoxLayout;

        openWindowBtn = new QPushButton("Open Programmer Window");
        openWindowBtn->setEnabled(false);
        connect(openWindowBtn, &QPushButton::clicked, this, &MainWindow::openProgrammerWindow);
        buttonsLayout->addWidget(openWindowBtn);

        statisticsBtn = new QPushButton("Show Statistics");
        connect(statisticsBtn, &QPushButton::clicked, this, &MainWindow::showStatistics);
        buttonsLayout->addWidget(statisticsBtn);

        layout->addLayout(buttonsLayout);

        connect(programmersList, &QListWidget::itemSelectionChanged,
                this, &MainWindow::onProgrammerSelectionChanged);
        connect(programmersList, &QListWidget::itemDoubleClicked,
                this, &MainWindow::openProgrammerWindow);

        updateProgrammersList();
    }

private slots:
    void openProgrammerWindow() {
        QListWidgetItem* item = programmersList->currentItem();
        if (!item) return;

        QString programmerName = item->text().split(" - ")[0];

        // Check if window already exists
        for (const auto& window : programmerWindows) {
            if (window->windowTitle().contains(programmerName)) {
                window->show();
                window->raise();
                window->activateWindow();
                return;
            }
        }

        // Create new window
        auto window = std::make_unique<ProgrammerWindow>(service.get(), programmerName.toStdString(), this);
        window->show();
        programmerWindows.push_back(std::move(window));
    }

    void showStatistics() {
        StatisticsWindow* statsWindow = new StatisticsWindow(service.get(), this);
        statsWindow->exec();
        delete statsWindow;
    }

    void onProgrammerSelectionChanged() {
        openWindowBtn->setEnabled(programmersList->currentItem() != nullptr);
    }

public:
    MainWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
        service = std::make_unique<CodeRevisionService>();
        setupUI();
    }

    void updateProgrammersList() {
        programmersList->clear();

        for (const auto& prog : service->programmers) {
            QString itemText = QString("%1 - Files: %2/%3")
                .arg(prog.name.c_str())
                .arg(prog.revisedFiles)
                .arg(prog.totalFiles);

            QListWidgetItem* item = new QListWidgetItem(itemText);
            if (prog.hasReachedGoal()) {
                item->setBackground(QBrush(QColor(173, 216, 230))); // Light blue
            }

            programmersList->addItem(item);
        }
    }
};

// Application Entry Point
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}

#include "main.moc"