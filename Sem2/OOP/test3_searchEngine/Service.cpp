#include "Service.h"

std::vector<Domain> Service::sortAll()
{
    std::vector<Domain> docs = repo.readFile();

    for (size_t i = 0; i < docs.size() - 1; ++i) {
        for (size_t j = i + 1; j < docs.size(); ++j) {
            if (docs[i].getName() > docs[j].getName()) {
                std::swap(docs[i], docs[j]);
            }
        }
    }

    return docs;
}

double Service::similarity(std::string text, std::string text2)
{
    double lenT, lenT2;
    double similar=0;
    lenT = std::strlen(text.c_str());
    lenT2 = std::strlen(text2.c_str());
    for (int i = 0; i < lenT; i++) {
        if (text[i] == text2[i]) {
            similar++;
        }
    }
    return similar/lenT2;
}

bool Service::findNameOrList(std::string text, std::string name)
{
    return name.find(text) != std::string::npos;
}
