#include <QtWidgets>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <memory>

// --- Domain ---
class User {
    std::string name, type;
public:
    User(const std::string& n, const std::string& t) : name(n), type(t) {}
    const std::string& getName() const { return name; }
    const std::string& getType() const { return type; }
    bool isTester() const { return type == "tester"; }
    bool isProgrammer() const { return type == "programmer"; }
};

class Issue {
    std::string description, status, reporter, solver;
public:
    Issue(const std::string& d, const std::string& r, const std::string& s="open", const std::string& sol="")
        : description(d), status(s), reporter(r), solver(sol) {}
    const std::string& getDescription() const { return description; }
    const std::string& getStatus() const { return status; }
    const std::string& getReporter() const { return reporter; }
    const std::string& getSolver() const { return solver; }
    void setStatus(const std::string& s) { status = s; }
    void setSolver(const std::string& s) { solver = s; }
    bool isOpen() const { return status == "open"; }
    bool isClosed() const { return status == "closed"; }
};

// --- Exception ---
class IssueTrackerException : public std::exception {
    std::string msg;
public:
    IssueTrackerException(const std::string& m) : msg(m) {}
    const char* what() const noexcept override { return msg.c_str(); }
};

// --- Repository ---
class IssueRepository {
    std::vector<User> users;
    std::vector<Issue> issues;
    std::string usersFile, issuesFile;
public:
    IssueRepository(const std::string& uf, const std::string& isf) : usersFile(uf), issuesFile(isf) {
        loadUsers(); loadIssues();
    }
    void loadUsers() {
        std::ifstream f(usersFile);
        std::string line;
        while (getline(f, line)) {
            std::istringstream iss(line); std::string n, t;
            if (iss >> n >> t) users.emplace_back(n, t);
        }
    }
    void loadIssues() {
        std::ifstream f(issuesFile);
        std::string line;
        while (getline(f, line)) {
            std::istringstream iss(line);
            std::string d, s, r, sol;
            if (iss >> d >> s >> r >> sol)
                issues.emplace_back(d, r, s, sol == "none" ? "" : sol);
        }
    }
    void saveIssues() {
        std::ofstream f(issuesFile);
        for (auto& i : issues)
            f << i.getDescription() << " " << i.getStatus() << " " << i.getReporter() << " "
              << (i.getSolver().empty() ? "none" : i.getSolver()) << "\n";
    }
    const std::vector<User>& getUsers() const { return users; }
    const std::vector<Issue>& getIssues() const { return issues; }
    std::vector<Issue> getSortedIssues() const {
        auto v = issues;
        std::sort(v.begin(), v.end(),
            [](const Issue& a, const Issue& b) { return a.getDescription() < b.getDescription(); });
        return v;
    }
    bool issueExists(const std::string& desc) const {
        return std::any_of(issues.begin(), issues.end(),
            [&](const Issue& i) { return i.getDescription() == desc; });
    }
    Issue* findIssue(const std::string& desc) {
        for (auto& i : issues)
            if (i.getDescription() == desc) return &i;
        return nullptr;
    }
    void addIssue(const Issue& issue) {
        if (issue.getDescription().empty())
            throw IssueTrackerException("Description cannot be empty");
        if (issueExists(issue.getDescription()))
            throw IssueTrackerException("Issue already exists");
        issues.push_back(issue);
    }
    void removeIssue(const std::string& desc) {
        auto it = std::find_if(issues.begin(), issues.end(),
            [&](const Issue& i) { return i.getDescription() == desc; });
        if (it == issues.end()) return;
        if (!it->isClosed())
            throw IssueTrackerException("Can only remove closed issues");
        issues.erase(it);
    }
    void resolveIssue(const std::string& desc, const std::string& programmer) {
        Issue* i = findIssue(desc);
        if (!i) throw IssueTrackerException("Issue not found");
        if (!i->isOpen())
            throw IssueTrackerException("Can only resolve open issues");
        i->setStatus("closed");
        i->setSolver(programmer);
    }
};

// --- Service ---
class IssueService : public QObject {
    Q_OBJECT
    IssueRepository repo;
public:
    IssueService(const std::string& uf, const std::string& isf) : repo(uf, isf) {}
    const std::vector<User>& getUsers() const { return repo.getUsers(); }
    std::vector<Issue> getSortedIssues() const { return repo.getSortedIssues(); }
    void addIssue(const std::string& desc, const std::string& rep) {
        repo.addIssue(Issue(desc, rep));
        emit issuesChanged();
    }
    void removeIssue(const std::string& desc) {
        repo.removeIssue(desc);
        emit issuesChanged();
    }
    void resolveIssue(const std::string& desc, const std::string& prog) {
        repo.resolveIssue(desc, prog);
        emit issuesChanged();
    }
    void saveData() { repo.saveIssues(); }
signals:
    void issuesChanged();
};

// --- UI ---
class UserWindow : public QMainWindow {
    Q_OBJECT
    User user;
    IssueService* service;
    QListWidget* list;
    QLineEdit* descEdit;
    QPushButton *addBtn, *removeBtn, *resolveBtn;
public:
    UserWindow(const User& u, IssueService* s) : user(u), service(s) {
        setWindowTitle(QString::fromStdString(user.getName() + " (" + user.getType() + ")"));
        QWidget* c = new QWidget; setCentralWidget(c);
        QVBoxLayout* lay = new QVBoxLayout(c);
        lay->addWidget(new QLabel(QString("User: %1, Type: %2")
            .arg(QString::fromStdString(user.getName()))
            .arg(QString::fromStdString(user.getType()))));
        list = new QListWidget; lay->addWidget(list);

        QHBoxLayout* btnLay = new QHBoxLayout;
        if (user.isTester()) {
            descEdit = new QLineEdit; descEdit->setPlaceholderText("Issue description...");
            btnLay->addWidget(descEdit);
            addBtn = new QPushButton("Add"); btnLay->addWidget(addBtn);
            connect(addBtn, &QPushButton::clicked, this, &UserWindow::onAdd);
        }
        removeBtn = new QPushButton("Remove"); btnLay->addWidget(removeBtn);
        connect(removeBtn, &QPushButton::clicked, this, &UserWindow::onRemove);
        if (user.isProgrammer()) {
            resolveBtn = new QPushButton("Resolve"); btnLay->addWidget(resolveBtn);
            connect(resolveBtn, &QPushButton::clicked, this, &UserWindow::onResolve);
        }
        lay->addLayout(btnLay);
        connect(list, &QListWidget::itemSelectionChanged, this, &UserWindow::onSelection);
        connect(service, &IssueService::issuesChanged, this, &UserWindow::refresh);
        refresh();
    }
    void refresh() {
        list->clear();
        for (const auto& i : service->getSortedIssues()) {
            QString s = QString("%1 | %2 | Reporter: %3 | Solver: %4")
                .arg(QString::fromStdString(i.getDescription()))
                .arg(QString::fromStdString(i.getStatus()))
                .arg(QString::fromStdString(i.getReporter()))
                .arg(i.getSolver().empty() ? "None" : QString::fromStdString(i.getSolver()));
            list->addItem(s);
        }
        onSelection();
    }
    void onAdd() {
        try {
            QString d = descEdit->text().trimmed();
            service->addIssue(d.toStdString(), user.getName());
            descEdit->clear();
        } catch (const IssueTrackerException& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    }
    void onRemove() {
        auto* item = list->currentItem();
        if (!item) return;
        QString desc = item->text().split(" | ")[0];
        try {
            service->removeIssue(desc.toStdString());
        } catch (const IssueTrackerException& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    }
    void onResolve() {
        auto* item = list->currentItem();
        if (!item) return;
        QString desc = item->text().split(" | ")[0];
        try {
            service->resolveIssue(desc.toStdString(), user.getName());
        } catch (const IssueTrackerException& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    }
    void onSelection() {
        auto* item = list->currentItem();
        bool has = item;
        bool closed = false, open = false;
        if (has) {
            QString status = item->text().split(" | ")[1].trimmed();
            open = (status == "open");
            closed = (status == "closed");
        }
        if (removeBtn) removeBtn->setEnabled(has && closed);
        if (resolveBtn) resolveBtn->setEnabled(has && open);
    }
};

// --- main ---
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    IssueService service("users.txt", "issues.txt");
    std::vector<std::unique_ptr<UserWindow>> windows;
    for (const auto& u : service.getUsers()) {
        auto w = std::make_unique<UserWindow>(u, &service);
        w->show();
        windows.push_back(std::move(w));
    }
    int res = app.exec();
    service.saveData();
    return res;
}

#include "main.moc"
