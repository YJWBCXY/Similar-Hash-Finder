#ifndef WINDOW_H
#define WINDOW_H

#pragma once
#include <QWidget>
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QTextEdit;
class Window : public QWidget {
		Q_OBJECT
	public:
		explicit Window(QWidget* parent = 0);

	private slots:
		void slot_hash();
		void slot_hash_test();

	private:
	QVBoxLayout
		* vbox_main;
	QHBoxLayout
		* hbox_buttons;
	QPushButton
		* butt_hash,
		* butt_hash_test;
	QTextEdit
		* btext_input,
		* btext_output;
};

#endif // WINDOW_H