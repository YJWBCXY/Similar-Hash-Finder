#ifndef WINDOW_H
#define WINDOW_H

#pragma once
#include <QWidget>
class QHBoxLayout;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QVBoxLayout;
class Window : public QWidget {
    Q_OBJECT
    public:
    explicit Window(QWidget* parent = 0);

    private slots:
    void slot_hash();
    void slot_hash_test();
    void slot_get_task();

    private:
    QHBoxLayout* hbox_buttons;
    QLineEdit* ltext_name;
    QPushButton *butt_hash, *butt_hash_test, *butt_get_task;
    QTextEdit *btext_input, *btext_output;
    QVBoxLayout* vbox_main;
};

#endif // WINDOW_H