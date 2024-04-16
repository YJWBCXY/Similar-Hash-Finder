#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QTextEdit>
#include <QVBoxLayout>

#include <chrono>
#include <string>
#include <vector>

#include "request.hpp"
#include "sha256.h"
#include "tools.h"
#include "window.h"

Window::Window(QWidget* parent) : QWidget(parent) {
    setFixedSize(400, 500);
    setWindowTitle("Similar Hash Finder - Client");

    vbox_main = new QVBoxLayout(this);
    hbox_buttons = new QHBoxLayout(this);

    butt_hash = new QPushButton("hash", this);
    butt_hash_test = new QPushButton("hash_test", this);
    butt_get_task = new QPushButton("get task", this);

    ltext_name = new QLineEdit(this);
    ltext_name->setPlaceholderText("Input");
    btext_output = new QTextEdit(this);
    btext_output->setReadOnly(true);
    btext_output->setPlaceholderText("Output");


    vbox_main->addWidget(ltext_name);
    vbox_main->addLayout(hbox_buttons);
    vbox_main->addWidget(btext_output);

    hbox_buttons->addWidget(butt_hash);
    hbox_buttons->addWidget(butt_hash_test);
    hbox_buttons->addWidget(butt_get_task);


    connect(butt_hash, SIGNAL(clicked()), this, SLOT(slot_hash()));
    connect(butt_hash_test, SIGNAL(clicked()), this, SLOT(slot_hash_test()));
    connect(butt_get_task, SIGNAL(clicked()), this, SLOT(slot_get_task()));
}

void Window::slot_hash() {
    QString data;
    std::string text;

    data = ltext_name->text();
    text = data.toStdString();
    text = sha256_to_base91(text);
    data = QString::fromStdString(text);

    btext_output->setPlainText(data);
}

void Window::slot_hash_test() {
    std::vector<std::string> data, out;
    for (int i = 0; i < 1000; i++) {
        data.push_back(gen_random(128));
    }
    std::chrono::time_point start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++) {
        out.push_back(sha256_to_base91(data[i]));
    }
    std::chrono::time_point stop = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds time =
        std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    int dtime = 1000 / (time.count() / 1000);
    btext_output->setPlainText(QString::fromStdString(std::to_string(dtime)));
}

void Window::slot_get_task() {
    QString data;
    std::string text;

    text = Request_handler("127.0.0.1", "8080").get_task();
    data = QString::fromStdString(text);
    btext_output->setPlainText(data);
}