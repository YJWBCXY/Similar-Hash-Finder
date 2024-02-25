#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QString>

#include <string>
#include <vector>
#include <chrono>

#include "window.h"
#include "sha256.h"
#include "tools.h"

Window::Window(QWidget* parent) : 
	QWidget(parent) {
	setFixedSize(400,500);
	setWindowTitle("Similar Hash Finder - Client");

	vbox_main = new QVBoxLayout(this);
	hbox_buttons = new QHBoxLayout(this);

	butt_hash = new QPushButton("hash", this);
	butt_hash_test = new QPushButton("hash_test", this);

	btext_input = new QTextEdit(this);
	btext_input->setPlaceholderText("Input");
	btext_output = new QTextEdit(this);
	btext_output->setReadOnly(true);
	btext_output->setPlaceholderText("Input");


	vbox_main->addWidget(btext_input);
	vbox_main->addLayout(hbox_buttons);
	vbox_main->addWidget(btext_output);

	hbox_buttons->addWidget(butt_hash);
	hbox_buttons->addWidget(butt_hash_test);


	connect(butt_hash, SIGNAL(clicked()), this, SLOT(slot_hash()));
	connect(butt_hash_test, SIGNAL(clicked()), this, SLOT(slot_hash_test()));
}

void Window::slot_hash(){
	QString data;
	std::string text;

	data = btext_input->toPlainText();
	text = data.toStdString();
	text = sha256_to_base91(text);
	data = QString::fromStdString(text);

	btext_output->setPlainText(data);
}

void Window::slot_hash_test(){
	std::vector<std::string> data,
							out;
	for(int i = 0; i < 1000; i++){
		data.push_back(gen_random(128));
	}
	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();
	for(int i= 0; i < 1000; i++){
		out.push_back(sha256_to_base91(data[i]));
	}
	std::chrono::steady_clock::time_point stop = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	int dtime = 1000/(time.count()/1000);
	btext_output->setPlainText(QString::fromStdString(std::to_string(dtime)));
}